// One-off interaction driver for newave + cedit (menus, mesh editing,
// slider drags). Not part of the smoke gate; run manually:
//   node interact.mjs [--only newave,cedit]
// Screenshots land in results/interact/.
import { chromium } from "playwright";
import { startServer } from "./lib/server.mjs";
import fs from "node:fs";
import path from "node:path";

const OUT = path.resolve("results/interact");
fs.mkdirSync(OUT, { recursive: true });

const only = (() => {
  const i = process.argv.indexOf("--only");
  return i >= 0 ? process.argv[i + 1].split(",") : ["newave", "cedit"];
})();

const repo = path.resolve("../..");
const server = await startServer(repo);
const browser = await chromium.launch();
const context = await browser.newContext({ viewport: { width: 1024, height: 768 } });

async function load(page, demoPath) {
  const url = `${server.url}/${demoPath}`;
  const errors = [];
  page.on("console", (m) => { if (m.type() === "error") errors.push(m.text()); });
  page.on("pageerror", (e) => errors.push(String(e)));
  await page.goto(url, { waitUntil: "domcontentloaded", timeout: 30000 });
  await page.waitForTimeout(4000);
  return errors;
}

async function shot(page, name) {
  await page.screenshot({ path: path.join(OUT, name) });
  console.log(`  shot: ${name}`);
}

// Sample one canvas pixel's RGB (WebGL back buffer readback)
async function pixel(page, x, y) {
  return await page.evaluate(async ([px, py]) => {
    const c = document.getElementById("canvas");
    const gl = c.getContext("webgl") || c.getContext("webgl2");
    if (gl) {
      const scaleX = gl.drawingBufferWidth / c.clientWidth;
      const scaleY = gl.drawingBufferHeight / c.clientHeight;
      const p = new Uint8Array(4);
      gl.readPixels(Math.round(px * scaleX), Math.round(gl.drawingBufferHeight - 1 - py * scaleY),
                    1, 1, gl.RGBA, gl.UNSIGNED_BYTE, p);
      return [p[0], p[1], p[2]];
    }
    return null;
  }, [x, y]);
}

// Open the right-mouse menu at (x, y); the menu's top-left lands there.
async function rightClick(page, x, y) {
  await page.mouse.move(x, y);
  await page.waitForTimeout(120);
  await page.mouse.down({ button: "right" });
  await page.waitForTimeout(150);
  await page.mouse.up({ button: "right" });
  await page.waitForTimeout(700);
}

// Click item k (0-based) of a pup menu whose top-left is at (mx, my).
// Layout (gl.c): title fill 24px, gap 10, item pitch 22. Returns the click
// point — a submenu opened by this selection has its top-left there.
async function pickMenuItem(page, mx, my, k) {
  const x = mx + 40;
  const y = my + 24 + 10 + 22 * k + 11;
  await page.mouse.move(x, y);
  await page.waitForTimeout(400);
  await page.mouse.down();
  await page.waitForTimeout(150);
  await page.mouse.up();
  await page.waitForTimeout(900);
  return { x, y };
}

// newave: right-click menu -> "display menu" (item 3) -> display item k
async function newaveDisplayMode(page, k) {
  await rightClick(page, 350, 250);
  const p = await pickMenuItem(page, 350, 250, 3);
  await pickMenuItem(page, p.x, p.y, k);
  await page.waitForTimeout(1200);
}

if (only.includes("newave")) {
  console.log("newave:");
  const page = await context.newPage();
  const errors = await load(page, "demos/newave/web/newave_full.html");
  await shot(page, "newave-0-initial.png");

  await rightClick(page, 350, 250);
  await shot(page, "newave-1-menu.png");
  const p = await pickMenuItem(page, 350, 250, 3); // "display menu"
  await shot(page, "newave-2-displaymenu.png");
  await pickMenuItem(page, p.x, p.y, 2); // "flat shaded"
  await page.waitForTimeout(1200);
  await shot(page, "newave-3-flatshaded.png");

  await newaveDisplayMode(page, 3); // gouraud shaded
  await shot(page, "newave-4-gouraud.png");

  await newaveDisplayMode(page, 1); // depthcued
  await shot(page, "newave-5-depthcued.png");

  await newaveDisplayMode(page, 4); // top view
  await shot(page, "newave-6-topview.png");

  await newaveDisplayMode(page, 5); // antialias toggle (stays in top view? no: toggles AA for normal/depthcued)
  await newaveDisplayMode(page, 0); // normal (now antialiased path: MYCYAN ramp)
  await shot(page, "newave-6b-normal-antialias.png");
  await newaveDisplayMode(page, 5); // antialias off again
  await newaveDisplayMode(page, 0); // normal

  // edit the mesh: enter edit mode, pull a point up, then "go"
  await rightClick(page, 350, 250);
  await pickMenuItem(page, 350, 250, 0); // "edit"
  await page.waitForTimeout(600);
  await page.mouse.move(512, 400);
  await page.waitForTimeout(600);
  await shot(page, "newave-7-editmode.png");
  await page.mouse.down();
  await page.mouse.move(512, 200, { steps: 10 });
  await page.waitForTimeout(800);
  await shot(page, "newave-8-editing.png");
  await page.mouse.up();
  await page.waitForTimeout(300);

  await rightClick(page, 200, 550);
  await pickMenuItem(page, 200, 550, 1); // "go"
  await page.waitForTimeout(1500);
  await shot(page, "newave-9-wave-running.png");

  // spring (speed) menu and grid menu round-trips
  await rightClick(page, 350, 250);
  const s = await pickMenuItem(page, 350, 250, 4); // "spring menu"
  await shot(page, "newave-10-springmenu.png");
  await pickMenuItem(page, s.x, s.y, 2); // "strong"
  await page.waitForTimeout(600);

  await rightClick(page, 350, 250);
  const g = await pickMenuItem(page, 350, 250, 5); // "grid menu"
  await shot(page, "newave-11-gridmenu.png");
  await pickMenuItem(page, g.x, g.y, 2); // "large"
  await page.waitForTimeout(1000);
  await shot(page, "newave-12-largegrid.png");

  console.log("  console errors:", errors.length ? errors.slice(0, 5) : "none");
  await page.close();
}

if (only.includes("cedit")) {
  console.log("cedit:");
  const page = await context.newPage();
  const errors = await load(page, "demos/cedit/web/cedit_full.html");
  await shot(page, "cedit-0-initial.png");

  // cedit declares keepaspect(1,1): the framebuffer is a square centered in
  // the canvas (768x768 in a 1024x768 window, x offset 128). World 0..10
  // maps across that square; page y is flipped.
  const S = 768, XOFF = (1024 - S) / 2;
  const gx = (wx) => XOFF + (wx / 10) * S;
  const gy = (wy) => S - (wy / 10) * S;

  const swatchBefore = await pixel(page, gx(8), gy(5.5));

  // drag the R slider (track wx 1..2) up to ~0.8 (wy = 2 + 7*0.8 = 7.6)
  await page.mouse.move(gx(1.5), gy(3.0));
  await page.mouse.down();
  await page.mouse.move(gx(1.5), gy(7.6), { steps: 15 });
  await page.waitForTimeout(500);
  await page.mouse.up();
  await page.waitForTimeout(800);
  await shot(page, "cedit-1-red-dragged.png");
  const swatchRed = await pixel(page, gx(8), gy(5.5));

  // drag the B slider (track wx 5..6) to ~0.4
  await page.mouse.move(gx(5.5), gy(3.0));
  await page.mouse.down();
  await page.mouse.move(gx(5.5), gy(2 + 7 * 0.4), { steps: 10 });
  await page.waitForTimeout(500);
  await page.mouse.up();
  await page.waitForTimeout(800);
  await shot(page, "cedit-2-blue-dragged.png");
  const swatchRB = await pixel(page, gx(8), gy(5.5));

  // colorsys menu: rgb | cmy | hsv | hls — switch to hsv, sliders reposition
  await rightClick(page, 300, 300);
  await shot(page, "cedit-3-menu.png");
  await pickMenuItem(page, 300, 300, 2); // hsv
  await page.waitForTimeout(800);
  await shot(page, "cedit-4-hsv.png");

  console.log("  swatch before:", swatchBefore, "after R:", swatchRed, "after R+B:", swatchRB);
  console.log("  console errors:", errors.length ? errors.slice(0, 5) : "none");
  await page.close();
}

await browser.close();
await server.close();
console.log("done; shots in", OUT);
