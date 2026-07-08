import { chromium } from "playwright";
import { startServer } from "./lib/server.mjs";
import { writeFileSync } from "node:fs";
setTimeout(() => { console.log("watchdog"); process.exit(2); }, 120000);
const server = await startServer("../..");
const browser = await chromium.launch();
const page = await browser.newPage({ viewport: { width: 1024, height: 768 } });
const cdp = await page.context().newCDPSession(page);
async function shot(name){ const s = await cdp.send("Page.captureScreenshot",{format:"png"}); writeFileSync(`/tmp/${name}.png`, Buffer.from(s.data,"base64")); console.log(name); }
await page.goto(server.url + "/demos/flight-1994/web/?rast=gles2");
await page.waitForTimeout(7000);
await page.keyboard.press("g"); await page.waitForTimeout(3000);
await page.keyboard.press("5");                 // F-18
await page.waitForTimeout(20000); await shot("s1");
for (let i=0;i<8;i++) await page.keyboard.press("a");
for (let i=0;i<40;i++) await page.keyboard.press("N");   // advance time of day to daylight
await page.waitForTimeout(15000); await shot("s2");
await page.waitForTimeout(15000); await shot("s3");
await browser.close(); console.log("done"); process.exit(0);
