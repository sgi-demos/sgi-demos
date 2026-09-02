// Thumbnail generator for the browse page (sgi-demos.github.io/browse/).
//
// Loads each demo's web build (demos/<name>/web/) in headless Chromium, waits
// for it to settle, optionally drives keys/mouse to get past splash screens
// and menus (scripts/thumbs.json), and writes media/<name>.png — a 512x384
// (4:3) PNG, box-filtered down from the 1024x768 capture.
//
// Reuses the smoke suite's Chromium + static server: run `make thumbs` (which
// installs tests/smoke/node_modules on first use), or directly:
//   node scripts/thumbs.mjs [--only a,b,c] [--out media] [--full <dir>]
// --full also writes the unscaled 1024x768 capture per demo (for tuning steps).
import { createRequire } from "node:module";
import { readFile, writeFile, mkdir } from "node:fs/promises";
import { existsSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { dirname, join, resolve } from "node:path";
import { startServer } from "../tests/smoke/lib/server.mjs";

// playwright + pngjs live in tests/smoke/node_modules (both are CommonJS).
const require = createRequire(new URL("../tests/smoke/package.json", import.meta.url));
const { chromium } = require("playwright");
const { PNG } = require("pngjs");

const HERE = dirname(fileURLToPath(import.meta.url));
const REPO = resolve(HERE, "..");

function parseArgs(argv) {
  const args = { only: null, out: join(REPO, "media"), full: null, config: join(HERE, "thumbs.json") };
  for (let i = 2; i < argv.length; i++) {
    const a = argv[i];
    if (a === "--only") args.only = argv[++i].split(",").map((s) => s.trim()).filter(Boolean);
    else if (a === "--out") args.out = resolve(argv[++i]);
    else if (a === "--full") args.full = resolve(argv[++i]);
    else if (a === "--config") args.config = resolve(argv[++i]);
    else throw new Error(`unknown arg: ${a}`);
  }
  return args;
}

// Halve a PNG with a 2x2 box filter (exact for our even-sized capture).
function downscale2x(buffer) {
  const src = PNG.sync.read(buffer);
  const w = src.width >> 1, h = src.height >> 1;
  const dst = new PNG({ width: w, height: h });
  for (let y = 0; y < h; y++) {
    for (let x = 0; x < w; x++) {
      const o = (y * w + x) * 4;
      const i0 = ((2 * y) * src.width + 2 * x) * 4, i1 = i0 + 4;
      const i2 = i0 + src.width * 4, i3 = i2 + 4;
      for (let c = 0; c < 3; c++) {
        dst.data[o + c] = (src.data[i0 + c] + src.data[i1 + c] + src.data[i2 + c] + src.data[i3 + c] + 2) >> 2;
      }
      dst.data[o + 3] = 255;
    }
  }
  return PNG.sync.write(dst);
}

// Pup menu geometry (libs/libgl gl.c): title 24px, gap 10, item pitch 22.
async function pickMenuItem(page, mx, my, k) {
  const x = mx + 40, y = my + 24 + 10 + 22 * k + 11;
  await page.mouse.move(x, y);
  await page.waitForTimeout(400);
  await page.mouse.down();
  await page.waitForTimeout(150);
  await page.mouse.up();
  await page.waitForTimeout(400);
}

async function runSteps(page, steps) {
  for (const s of steps) {
    if (s.key !== undefined) {
      for (let i = 0; i < (s.repeat ?? 1); i++) await page.keyboard.press(s.key);
    } else if (s.timeOfDay) {
      // The demo seeded its clock from the machine's local time of day
      // (Playwright's fake clock doesn't reach Emscripten's time()); press
      // the forward/back key enough times to land on the target minute.
      const { target, forward, back, step } = s.timeOfDay;
      const now = new Date();
      let delta = target - (now.getHours() * 60 + now.getMinutes());
      if (delta > 720) delta -= 1440;
      if (delta < -720) delta += 1440;
      const n = Math.round(Math.abs(delta) / step);
      for (let i = 0; i < n; i++) await page.keyboard.press(delta >= 0 ? forward : back);
    } else if (s.wait !== undefined) {
      await page.waitForTimeout(s.wait);
    } else if (s.rightClick) {
      const [x, y] = s.rightClick;
      await page.mouse.move(x, y);
      await page.waitForTimeout(120);
      await page.mouse.down({ button: "right" });
      await page.waitForTimeout(150);
      await page.mouse.up({ button: "right" });
      await page.waitForTimeout(700);
    } else if (s.click) {
      const [x, y] = s.click;
      await page.mouse.click(x, y);
      await page.waitForTimeout(300);
    } else if (s.pick) {
      await pickMenuItem(page, ...s.pick);
    } else if (s.drag) {
      const [x1, y1, x2, y2] = s.drag;
      await page.mouse.move(x1, y1);
      await page.waitForTimeout(300);
      await page.mouse.down();
      await page.mouse.move(x2, y2, { steps: 10 });
      await page.waitForTimeout(300);
      await page.mouse.up();
    } else {
      throw new Error(`unknown step: ${JSON.stringify(s)}`);
    }
  }
}

async function capture(context, baseUrl, demo, cfg) {
  const page = await context.newPage();
  const errors = [];
  page.on("pageerror", (e) => errors.push(e.message));
  page.on("console", (m) => { if (m.type() === "error") errors.push(m.text()); });
  try {
    let url = `${baseUrl}/demos/${demo.name}/web/?rast=${encodeURIComponent(demo.rast ?? "gles2")}`;
    if (demo.arg) url += `&arg=${encodeURIComponent(demo.arg)}`;
    await page.goto(url, { waitUntil: "domcontentloaded", timeout: 30000 });
    await page.waitForResponse((r) => /\.wasm(\?|$)/.test(r.url()), { timeout: 15000 });
    await page.waitForTimeout(demo.settleMs ?? cfg.settleMs);
    await runSteps(page, demo.steps ?? []);
    const png = await page.screenshot({ type: "png" });
    return { png, errors };
  } finally {
    await page.close();
  }
}

async function main() {
  const args = parseArgs(process.argv);
  const cfg = JSON.parse(await readFile(args.config, "utf8"));
  let demos = cfg.demos;
  if (args.only) demos = demos.filter((d) => args.only.includes(d.name));
  if (!demos.length) throw new Error("no demos selected");
  for (const d of demos) {
    if (!existsSync(join(REPO, "demos", d.name, "web", "index.html"))) {
      console.warn(`! ${d.name}: demos/${d.name}/web/index.html not found (run 'make browser'?)`);
    }
  }
  await mkdir(args.out, { recursive: true });
  if (args.full) await mkdir(args.full, { recursive: true });

  const server = await startServer(REPO);
  const browser = await chromium.launch();
  const context = await browser.newContext({ viewport: cfg.viewport, deviceScaleFactor: 1 });
  let failed = 0;
  try {
    for (const demo of demos) {
      process.stdout.write(`• ${demo.name} … `);
      try {
        const { png, errors } = await capture(context, server.url, demo, cfg);
        if (args.full) await writeFile(join(args.full, `${demo.name}.png`), png);
        await writeFile(join(args.out, `${demo.name}.png`), downscale2x(png));
        console.log(errors.length ? `ok (${errors.length} console error(s): ${errors[0]})` : "ok");
      } catch (e) {
        failed++;
        console.log(`FAILED: ${e.message}`);
      }
    }
  } finally {
    await context.close();
    await browser.close();
    await server.close();
  }
  console.log(`\n${demos.length - failed}/${demos.length} thumbnails written to ${args.out}`);
  process.exit(failed ? 1 : 0);
}

main().catch((e) => { console.error(e); process.exit(2); });
