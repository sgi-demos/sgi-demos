// sgi-demos visual smoke runner (web targets, headless Chromium).
//
// Captures every configured demo in every configured rendering mode
// (?rast=ref CPU reference rasterizer, ?rast=gles2 GPU rasterizer). For each
// demo x mode it:
//   1. loads demos/<name>/web/?rast=<mode> from a local server (web/ serves
//      the demo's index.html),
//   2. waits for the .wasm to load, then lets the animation settle,
//   3. captures the <canvas> via the browser compositor,
//   4. fails if it threw / aborted / printed "ERROR:", or the frame is blank.
//
// Writes results/<name>.<mode>.png, results/results.json, and the review
// gallery at report/index.html (each demo's modes side by side). Exits 1 if
// any capture fails, so `make smoke` gates a commit.
//
// Usage:
//   node smoke.mjs [--repo <path>] [--only a,b,c] [--modes ref,gles2]
//                  [--config demos.json] [--update-baseline]
import { chromium } from "playwright";
import { readFile, writeFile, mkdir, copyFile, rm } from "node:fs/promises";
import { existsSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { dirname, join, resolve } from "node:path";
import { startServer } from "./lib/server.mjs";
import { analyzePng } from "./lib/analyze.mjs";
import { writeReport } from "./lib/report.mjs";

const HERE = dirname(fileURLToPath(import.meta.url));

function parseArgs(argv) {
  const args = {
    repo: resolve(HERE, "../.."),
    config: join(HERE, "demos.json"),
    only: null,
    modes: null,
    updateBaseline: false,
  };
  for (let i = 2; i < argv.length; i++) {
    const a = argv[i];
    if (a === "--repo") args.repo = resolve(argv[++i]);
    else if (a === "--config") args.config = resolve(argv[++i]);
    else if (a === "--only") args.only = argv[++i].split(",").map((s) => s.trim()).filter(Boolean);
    else if (a === "--modes") args.modes = argv[++i].split(",").map((s) => s.trim()).filter(Boolean);
    else if (a === "--update-baseline") args.updateBaseline = true;
    else throw new Error(`unknown arg: ${a}`);
  }
  return args;
}

async function captureOne(context, baseUrl, demo, mode, cfg) {
  const id = `${demo.name}.${mode}`;
  const errors = [];
  const page = await context.newPage();
  page.on("pageerror", (e) => errors.push(`pageerror: ${e.message}`));
  page.on("console", (msg) => {
    const t = msg.text();
    if (msg.type() === "error") errors.push(`console.error: ${t}`);
    // Emscripten abort() prints "Aborted(...)"; the rasterizers print
    // "ERROR: ..." on shader build / FBO / texture failures.
    else if (/\bAborted\b/.test(t) || /^ERROR:/.test(t)) errors.push(`runtime: ${t}`);
  });

  let url = `${baseUrl}/${demo.path}?rast=${encodeURIComponent(mode)}`;
  if (demo.arg) url += `&arg=${encodeURIComponent(demo.arg)}`;

  const reasons = [];
  let content = 0;
  let pngBuffer = null;

  try {
    await page.goto(url, { waitUntil: "domcontentloaded", timeout: 30000 });
    // The shell loads <name>.js which fetches <name>.wasm. Wait for that, but
    // don't hard-fail if the demo has no separate .wasm response in time.
    await page
      .waitForResponse((r) => /\.wasm(\?|$)/.test(r.url()), { timeout: 15000 })
      .catch(() => reasons.push("no .wasm response seen within 15s"));

    const canvas = page.locator("#canvas");
    await canvas.waitFor({ state: "attached", timeout: 10000 }).catch(() => {
      reasons.push("no #canvas element found");
    });

    // Let the animation produce frames.
    await page.waitForTimeout(cfg.settleMs);

    if (await page.locator("#canvas").count()) {
      pngBuffer = await page.locator("#canvas").screenshot();
      const a = analyzePng(pngBuffer);
      content = a.content;
      if (content < demo.minContent) {
        reasons.push(`blank/near-blank frame (content ${content.toFixed(4)} < ${demo.minContent})`);
      }
    } else {
      reasons.push("canvas missing at capture time");
    }
  } catch (e) {
    reasons.push(`exception: ${e.message}`);
  } finally {
    await page.close();
  }

  if (errors.length) reasons.unshift(`${errors.length} runtime error(s)`);
  const pass = reasons.length === 0;
  return {
    id,
    name: demo.name,
    mode,
    status: demo.status,
    minContent: demo.minContent,
    content,
    pass,
    reasons,
    errors,
    pngBuffer,
  };
}

async function main() {
  const args = parseArgs(process.argv);
  const cfgRaw = JSON.parse(await readFile(args.config, "utf8"));
  const defaults = cfgRaw.defaults || { minContent: 0.02 };
  const settleMs = cfgRaw.settleMs ?? 3000;
  const viewport = cfgRaw.viewport ?? { width: 1024, height: 768 };
  let modes = cfgRaw.modes ?? ["ref"];
  if (args.modes) modes = modes.filter((m) => args.modes.includes(m));
  if (!modes.length) throw new Error("no modes selected");

  let demos = cfgRaw.demos.map((d) => ({ minContent: defaults.minContent, ...d }));
  if (args.only) demos = demos.filter((d) => args.only.includes(d.name));
  if (!demos.length) throw new Error("no demos selected");

  // Sanity: warn (don't fail yet) about missing pages so the error is obvious.
  // d.path is the demo's web/ directory; the served page is its index.html.
  for (const d of demos) {
    if (!existsSync(join(args.repo, d.path, "index.html"))) {
      console.warn(`! ${d.name}: ${d.path}index.html not found under repo (did you run 'make browser'?)`);
    }
  }

  const resultsDir = join(HERE, "results");
  const reportDir = join(HERE, "report");
  const baselineDir = join(HERE, "baseline");
  await rm(resultsDir, { recursive: true, force: true });
  await mkdir(resultsDir, { recursive: true });

  const server = await startServer(args.repo);
  const browser = await chromium.launch();
  const context = await browser.newContext({ viewport, deviceScaleFactor: 1 });

  const results = [];
  try {
    for (const demo of demos) {
      for (const mode of demo.modes ?? modes) {
        process.stdout.write(`• ${demo.name} [${mode}] … `);
        let r = await captureOne(context, server.url, demo, mode, { settleMs });
        if (!r.pass) {
          // One retry: headless SwiftShader occasionally drops the WebGL
          // context on a cold first page (CONTEXT_LOST_WEBGL); a genuine
          // breakage fails both attempts.
          const r2 = await captureOne(context, server.url, demo, mode, { settleMs });
          if (r2.pass) {
            r2.retried = true;
            r = r2;
          }
        }
        if (r.pngBuffer) await writeFile(join(resultsDir, `${r.id}.png`), r.pngBuffer);
        delete r.pngBuffer;
        results.push(r);
        console.log(r.pass ? (r.retried ? "PASS (on retry)" : "PASS") : `FAIL (${r.reasons.join("; ")})`);
      }
    }
  } finally {
    await context.close();
    await browser.close();
    await server.close();
  }

  if (args.updateBaseline) {
    await mkdir(baselineDir, { recursive: true });
    for (const r of results) {
      const src = join(resultsDir, `${r.id}.png`);
      if (existsSync(src)) await copyFile(src, join(baselineDir, `${r.id}.png`));
    }
    console.log(`Updated baseline images in ${baselineDir}`);
  }

  const meta = { timestamp: new Date().toISOString(), settleMs, viewport, modes };
  await writeFile(join(resultsDir, "results.json"), JSON.stringify({ meta, results }, null, 2));
  const reportPath = await writeReport(reportDir, results, meta);

  const passed = results.filter((r) => r.pass).length;
  console.log(`\n${passed}/${results.length} captures passed. Review: ${reportPath}`);
  process.exit(passed === results.length ? 0 : 1);
}

main().catch((e) => {
  console.error(e);
  process.exit(2);
});
