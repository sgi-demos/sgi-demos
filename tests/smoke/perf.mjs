// sgi-demos performance smoke runner: frame rate per demo, native or web.
//
// Runs every demo (`make list`) in each configured rendering mode (by
// default gles, the GPU rasterizer the demos ship with; ref, the CPU
// reference rasterizer, is for correctness, not speed) for a fixed time with IRISGL_FPS=1, which makes libgl print
// "IRISGL_FPS <fps> <frames> <ms>" once a second from the single present
// point (sdl_events_frame_complete). The first sample is warmup (first
// frames, shader builds) and is dropped; from the rest each run reports
//   LOW   the slowest one-second window
//   AVG   total frames / total time
//   HIGH  the fastest one-second window
// and WARNs when LOW is under the threshold. The demos are paced to 30 fps
// (DEMO_FPS in sdl_events.c), so ~30 is the ceiling.
//
// Targets:
//   native  demos/<name>/bin-<os>-<hw>/<APPNAME>, run from the demo's
//           directory (its data files are there) with the placard's web_arg
//   web     demos/<name>/web/?rast=<mode>&fps=1 in Chromium, from a local
//           server; stdout is console.log
//
// Writes perf/<platform>.txt (the summary table, as printed) and
// perf/<platform>.json, where platform is web or win/mac/linux, and each
// run's output to perf/logs/<platform>/<name>.<mode>.log. Exits 1 if any
// demo produced no frames (crashed, hung, or never started); warnings alone
// exit 0 — this is a report, not a gate.
//
// Usage:
//   node perf.mjs --target native|web [--repo <path>] [--only a,b,c]
//                 [--modes ref,gles] [--seconds 10] [--warn 15] [--headed]
//                 [--config perf.json]
import { readFile, writeFile, mkdir, rm } from "node:fs/promises";
import { existsSync, readdirSync, readFileSync } from "node:fs";
import { spawn } from "node:child_process";
import { fileURLToPath } from "node:url";
import { dirname, join, resolve } from "node:path";
import os from "node:os";
import { listDemos } from "./lib/demos.mjs";
import { startServer } from "./lib/server.mjs";

const HERE = dirname(fileURLToPath(import.meta.url));
const SAMPLE = /^IRISGL_FPS ([\d.]+) (\d+) (\d+)/;
const NATIVE_OS = { win32: "win", darwin: "mac", linux: "linux" };

function parseArgs(argv) {
  const args = {
    target: null,
    repo: resolve(HERE, "../.."),
    config: join(HERE, "perf.json"),
    only: null,
    modes: null,
    seconds: null,
    warn: null,
    headed: false,
  };
  for (let i = 2; i < argv.length; i++) {
    const a = argv[i];
    if (a === "--target") args.target = argv[++i];
    else if (a === "--repo") args.repo = resolve(argv[++i]);
    else if (a === "--config") args.config = resolve(argv[++i]);
    else if (a === "--only") args.only = argv[++i].split(",").map((s) => s.trim()).filter(Boolean);
    else if (a === "--modes") args.modes = argv[++i].split(",").map((s) => s.trim()).filter(Boolean);
    else if (a === "--seconds") args.seconds = Number(argv[++i]);
    else if (a === "--warn") args.warn = Number(argv[++i]);
    else if (a === "--headed") args.headed = true;
    else throw new Error(`unknown arg: ${a}`);
  }
  if (args.target !== "native" && args.target !== "web") throw new Error("--target native|web is required");
  return args;
}

// Collects IRISGL_FPS samples from a run's output lines. done() resolves
// once the measurement window (measureMs after the first sample) closes, or
// with no samples if the first never arrives within startMs.
function sampler(measureMs, startMs) {
  const samples = [];
  const lines = [];
  let first = null;
  let finish;
  const finished = new Promise((r) => (finish = r));
  const startTimer = setTimeout(() => finish("no frames within " + startMs / 1000 + "s"), startMs);
  return {
    line(text) {
      lines.push(text);
      const m = SAMPLE.exec(text);
      if (!m) return;
      const s = { fps: Number(m[1]), frames: Number(m[2]), ms: Number(m[3]), at: Date.now() };
      samples.push(s);
      if (first === null) {
        first = s.at;
        clearTimeout(startTimer);
        setTimeout(() => finish(null), measureMs);
      }
    },
    // an early end (the demo exited, or the page crashed)
    end(reason) {
      clearTimeout(startTimer);
      finish(reason);
    },
    done: () => finished,
    samples,
    lines,
  };
}

// LOW/AVG/HIGH from the samples after warmup. A demo that stopped presenting
// partway through prints nothing more, so a trailing gap of over two seconds
// counts as a 0 fps window.
function stats(samples, warmup, windowEnd) {
  const kept = samples.slice(warmup);
  const fps = kept.map((s) => s.fps);
  const last = samples.length ? samples[samples.length - 1].at : null;
  const stalled = last !== null && windowEnd - last > 2000;
  if (stalled) fps.push(0);
  if (!fps.length) return null;
  const frames = kept.reduce((n, s) => n + s.frames, 0);
  const ms = kept.reduce((n, s) => n + s.ms, 0) + (stalled ? windowEnd - last : 0);
  return {
    low: Math.min(...fps),
    avg: ms ? (frames * 1000) / ms : 0,
    high: Math.max(...fps),
    samples: fps.length,
    stalled,
  };
}

// The native executable: APPNAME (from the Makefile, or a sub-makefile such
// as buttonfly's Make_demo) in bin-<os>-<hw>/ from make_demo.mk (preferring
// this machine's arch), else in the bin/ link to it
function nativeExe(repo, demoName) {
  const dir = join(repo, "demos", demoName);
  const makefiles = readdirSync(dir).filter((f) => f === "Makefile" || f.startsWith("Make_"));
  const app = makefiles
    .map((f) => /^APPNAME\s*=\s*(\S+)/m.exec(readFileSync(join(dir, f), "utf8"))?.[1])
    .find(Boolean);
  if (!app) return null;
  const osName = NATIVE_OS[process.platform];
  const hw = { x64: "x86_64", arm64: process.platform === "darwin" ? "arm64" : "aarch64" }[process.arch];
  const exe = app + (process.platform === "win32" ? ".exe" : "");
  const bins = readdirSync(dir).filter((d) => d.startsWith(`bin-${osName}-`));
  bins.sort((a, b) => (b === `bin-${osName}-${hw}`) - (a === `bin-${osName}-${hw}`));
  for (const b of [...bins, "bin"]) {
    if (existsSync(join(dir, b, exe))) return { dir, exe: join(dir, b, exe) };
  }
  return null;
}

async function runNative(repo, demo, mode, cfg) {
  const found = nativeExe(repo, demo.name);
  if (!found) return { skip: "no native build (make native)", lines: [] };
  const s = sampler(cfg.measureMs, cfg.startMs);
  const args = demo.placard.web_arg ? String(demo.placard.web_arg).split(/\s+/) : [];
  const child = spawn(found.exe, args, {
    cwd: found.dir,
    env: { ...process.env, IRISGL_FPS: "1", IRISGL_RAST: mode, SGI_PLACARD: "0" },
    stdio: ["ignore", "pipe", "pipe"],
  });
  let exited = false;
  // whole lines only: a chunk can end mid-line
  const reader = () => {
    let rest = "";
    return (buf) => {
      const parts = (rest + buf.toString()).split(/\r?\n/);
      rest = parts.pop();
      for (const l of parts) if (l) s.line(l);
    };
  };
  child.stdout.on("data", reader());
  child.stderr.on("data", reader());
  child.on("error", (e) => s.end(`spawn failed: ${e.message}`));
  child.on("exit", (code, sig) => {
    exited = true;
    s.end(`exited early (${sig ?? "code " + code})`);
  });
  const reason = await s.done();
  const windowEnd = Date.now();
  if (!exited) child.kill();
  return { reason, samples: s.samples, lines: s.lines, windowEnd };
}

async function runWeb(context, baseUrl, demo, mode, cfg) {
  const s = sampler(cfg.measureMs, cfg.startMs);
  const errors = [];
  const page = await context.newPage();
  page.on("console", (msg) => {
    s.line(msg.text());
    if (msg.type() === "error") errors.push(msg.text());
  });
  page.on("pageerror", (e) => errors.push(`pageerror: ${e.message}`));
  page.on("crash", () => s.end("page crashed"));
  let reason = null;
  try {
    await page.goto(`${baseUrl}/demos/${demo.name}/web/?rast=${encodeURIComponent(mode)}&fps=1`, {
      waitUntil: "domcontentloaded",
      timeout: 30000,
    });
    reason = await s.done();
  } catch (e) {
    reason = `exception: ${e.message}`;
  }
  const windowEnd = Date.now();
  await page.close();
  // console errors are noted in the report, not failed on
  return { reason, samples: s.samples, lines: s.lines, errors, windowEnd };
}

// The WebGL renderer the browser gives the demos: hardware GPU, or
// SwiftShader (software), which makes gles numbers meaningless
async function webRenderer(context) {
  const page = await context.newPage();
  const r = await page.evaluate(() => {
    const gl = document.createElement("canvas").getContext("webgl2") || document.createElement("canvas").getContext("webgl");
    if (!gl) return "no WebGL";
    const ext = gl.getExtension("WEBGL_debug_renderer_info");
    return ext ? gl.getParameter(ext.UNMASKED_RENDERER_WEBGL) : gl.getParameter(gl.RENDERER);
  });
  await page.close();
  return r;
}

const fmt = (n) => (n === undefined || n === null ? "-" : n.toFixed(1));

// The summary table, in the style of the root Makefile's BUILD SUMMARY
function summary(platform, header, rows, warnFps) {
  const line = (a, b, c, d, e, f) =>
    a.padEnd(22) + b.padStart(6) + c.padStart(9) + d.padStart(9) + e.padStart(9) + f.padStart(9);
  const width = line("", "", "", "", "", "").length;
  const title = ` PERF SUMMARY: ${platform} `;
  const bar = "=".repeat(Math.floor((width - title.length) / 2));
  const out = [];
  out.push(bar + title + "=".repeat(width - bar.length - title.length));
  for (const h of header) out.push(h);
  out.push("");
  out.push(line("TARGET", "RAST", "LOW", "AVG", "HIGH", "STATUS"));
  for (const r of rows) out.push(line(r.name, r.mode, fmt(r.low), fmt(r.avg), fmt(r.high), r.status));
  out.push("=".repeat(width));
  const fails = rows.filter((r) => r.status === "FAIL");
  const warns = rows.filter((r) => r.status === "WARN");
  for (const r of rows.filter((r) => r.note)) out.push(`${r.name} [${r.mode}]: ${r.note}`);
  if (fails.length) out.push(`PERF FAILED: ${fails.length} run(s) produced no frames. See perf/logs/${platform}/.`);
  else if (warns.length) out.push(`PERF WARN: ${warns.length} run(s) dropped below ${warnFps} fps.`);
  else out.push(`PERF OK: every run stayed at or above ${warnFps} fps.`);
  const skips = rows.filter((r) => r.status === "SKIP").length;
  if (skips) out.push(`${skips} run(s) skipped: not built for this platform.`);
  return out.join("\n");
}

async function main() {
  const args = parseArgs(process.argv);
  const cfg = JSON.parse(await readFile(args.config, "utf8"));
  const seconds = args.seconds ?? cfg.seconds ?? 10;
  const warnFps = args.warn ?? cfg.warnFps ?? 15;
  const warmup = cfg.warmupSamples ?? 1;
  let modes = cfg.modes ?? ["gles"];
  if (args.modes) modes = args.modes;
  // the first sample is the first warmup one: wait for the rest of the
  // warmup and the measured seconds after it, and up to startSeconds for it
  const runCfg = {
    measureMs: (warmup - 1 + seconds) * 1000 + 500,
    startMs: (cfg.startSeconds ?? 30) * 1000,
  };

  let demos = listDemos(args.repo).map((d) => ({ name: d.name, id: d.id, placard: d.placard }));
  if (args.only) demos = demos.filter((d) => args.only.includes(d.id));
  if (!demos.length) throw new Error("no demos selected");

  const platform = args.target === "web" ? "web" : NATIVE_OS[process.platform];
  const outDir = join(HERE, "perf");
  const logDir = join(outDir, "logs", platform);
  await rm(logDir, { recursive: true, force: true });
  await mkdir(logDir, { recursive: true });

  const header = [
    `date: ${new Date().toISOString()}`,
    `host: ${os.type()} ${os.release()} ${os.arch()}, ${os.cpus()[0]?.model.trim()}`,
    `each run: ${warmup}s warmup + ${seconds}s measured; WARN when LOW < ${warnFps} fps (paced to 30)`,
  ];

  let browser, context, server;
  if (args.target === "web") {
    const { chromium } = await import("playwright");
    const viewport = cfg.viewport ?? { width: 1024, height: 768 };
    browser = await chromium.launch({ headless: !args.headed, args: cfg.chromiumArgs ?? [] });
    context = await browser.newContext({ viewport, deviceScaleFactor: 1 });
    server = await startServer(args.repo);
    header.push(`browser: Chromium ${browser.version()}${args.headed ? "" : " (headless)"}, ${viewport.width}x${viewport.height}`);
    header.push(`WebGL: ${await webRenderer(context)}`);
  }

  const rows = [];
  try {
    for (const demo of demos) {
      for (const mode of cfg.demos?.[demo.id]?.modes ?? modes) {
        process.stdout.write(`• ${demo.id} [${mode}] … `);
        const run =
          args.target === "web"
            ? await runWeb(context, server.url, demo, mode, runCfg)
            : await runNative(args.repo, demo, mode, runCfg);
        const st = run.samples ? stats(run.samples, warmup, run.windowEnd) : null;
        const row = { name: demo.id, mode, ...(st ?? {}) };
        const notes = [];
        if (run.skip) {
          // not built for this platform: the build summary reports that
          row.status = "SKIP";
          notes.push(run.skip);
        } else if (!st) {
          row.status = "FAIL";
          notes.push(run.reason ?? "no frames");
        } else {
          row.status = st.low < warnFps ? "WARN" : "OK";
          if (run.reason) notes.push(run.reason);
          if (st.stalled) notes.push("stopped presenting frames before the end");
          if (st.samples < seconds - 1) notes.push(`only ${st.samples} samples`);
        }
        if (run.errors?.length) notes.push(`${run.errors.length} console error(s)`);
        if (notes.length) row.note = notes.join("; ");
        rows.push(row);
        await writeFile(join(logDir, `${demo.id}.${mode}.log`), run.lines.join("\n") + "\n");
        console.log(st ? `${row.status}  low ${fmt(st.low)}  avg ${fmt(st.avg)}  high ${fmt(st.high)}` : `${row.status} (${row.note})`);
      }
    }
  } finally {
    await context?.close();
    await browser?.close();
    await server?.close();
  }

  const text = summary(platform, header, rows, warnFps);
  console.log("\n" + text);
  await writeFile(join(outDir, `${platform}.txt`), text + "\n");
  await writeFile(join(outDir, `${platform}.json`), JSON.stringify({ header, warnFps, seconds, rows }, null, 2) + "\n");
  process.exit(rows.some((r) => r.status === "FAIL") ? 1 : 0);
}

main().catch((e) => {
  console.error(e);
  process.exit(2);
});
