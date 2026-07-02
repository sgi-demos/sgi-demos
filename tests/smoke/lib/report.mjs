// Builds the human-review gallery (tests/smoke/report/index.html) from a
// results array. One card per demo, with its rendering modes (ref CPU,
// gles2 GPU) side by side as clickable thumbnails, a PASS/FAIL badge per
// mode, the measured content number, and any captured errors. If baseline
// images exist they're shown in a collapsible row so you can eyeball drift,
// but the PASS/FAIL gate does NOT depend on them.
import { writeFile, mkdir } from "node:fs/promises";
import { existsSync } from "node:fs";
import { join } from "node:path";

const esc = (s) =>
  String(s).replace(/[&<>"]/g, (c) => ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;" }[c]));

export async function writeReport(reportDir, results, meta) {
  await mkdir(reportDir, { recursive: true });

  // Group captures by demo, preserving run order.
  const byDemo = new Map();
  for (const r of results) {
    if (!byDemo.has(r.name)) byDemo.set(r.name, []);
    byDemo.get(r.name).push(r);
  }

  const cards = [...byDemo.entries()]
    .map(([name, captures]) => {
      const allPass = captures.every((r) => r.pass);

      const figures = captures
        .map((r) => {
          const shot = `../results/${r.id}.png`;
          const badge = r.pass
            ? `<span class="badge pass">PASS</span>`
            : `<span class="badge fail">FAIL</span>`;
          return `<figure>
            <figcaption>${esc(r.mode)} ${badge} <span class="content">content ${(r.content ?? 0).toFixed(4)}</span></figcaption>
            <a href="${shot}" target="_blank"><img src="${shot}" loading="lazy"></a>
          </figure>`;
        })
        .join("");

      const baselineFigures = captures
        .filter((r) => existsSync(join(reportDir, `../baseline/${r.id}.png`)))
        .map(
          (r) => `<figure>
            <figcaption>${esc(r.mode)} baseline</figcaption>
            <a href="../baseline/${r.id}.png" target="_blank"><img src="../baseline/${r.id}.png" loading="lazy"></a>
          </figure>`
        )
        .join("");
      const baseline = baselineFigures
        ? `<details><summary>baseline</summary><div class="pair">${baselineFigures}</div></details>`
        : "";

      const reasons = captures
        .flatMap((r) => r.reasons.map((x) => `<li><b>${esc(r.mode)}</b>: ${esc(x)}</li>`))
        .join("");
      const reasonsHtml = reasons ? `<ul class="reasons">${reasons}</ul>` : "";

      const errs = captures
        .filter((r) => r.errors?.length)
        .map(
          (r) => `<details><summary>${esc(r.mode)}: ${r.errors.length} console/page error(s)</summary><pre>${esc(
            r.errors.join("\n")
          )}</pre></details>`
        )
        .join("");

      const status = captures[0]?.status || "?";
      return `<div class="card ${allPass ? "ok" : "bad"}">
        <h2>${esc(name)}</h2>
        <div class="meta">status: ${esc(status)} &middot; min content ${captures[0]?.minContent}</div>
        <div class="pair">${figures}</div>
        ${baseline}
        ${reasonsHtml}
        ${errs}
      </div>`;
    })
    .join("\n");

  const passed = results.filter((r) => r.pass).length;
  const html = `<!doctype html><html lang="en"><head><meta charset="utf-8">
<title>sgi-demos smoke report</title>
<style>
  :root { color-scheme: dark; }
  body { font: 14px/1.4 system-ui, sans-serif; margin: 0; padding: 24px; background:#111; color:#eee; }
  header { margin-bottom: 20px; }
  h1 { margin: 0 0 4px; font-size: 20px; }
  .summary { color:#aaa; }
  .grid { display:grid; grid-template-columns: repeat(auto-fill, minmax(480px,1fr)); gap:16px; }
  .card { background:#1b1b1b; border:1px solid #333; border-radius:8px; padding:12px; }
  .card.bad { border-color:#a33; }
  .card h2 { font-size:15px; margin:0 0 6px; display:flex; align-items:center; gap:8px; }
  .meta { color:#999; font-size:12px; margin-bottom:8px; }
  img { width:100%; height:auto; display:block; border-radius:4px; background:#000; border:1px solid #2a2a2a; }
  .pair { display:grid; grid-template-columns:1fr 1fr; gap:8px; }
  figure { margin:0; }
  figcaption { font-size:11px; color:#888; margin-bottom:2px; display:flex; align-items:center; gap:6px; }
  .content { color:#666; }
  .badge { font-size:10px; padding:1px 7px; border-radius:999px; font-weight:600; }
  .badge.pass { background:#0a3; color:#fff; }
  .badge.fail { background:#c33; color:#fff; }
  .reasons { color:#f99; margin:8px 0 0; padding-left:18px; }
  details { margin-top:8px; }
  summary { cursor:pointer; color:#888; font-size:12px; }
  pre { white-space:pre-wrap; background:#000; padding:8px; border-radius:4px; max-height:200px; overflow:auto; font-size:12px; }
</style></head><body>
<header>
  <h1>sgi-demos visual smoke report</h1>
  <div class="summary">${passed}/${results.length} captures passed &middot; modes: ${esc(
    (meta.modes || []).join(", ")
  )} &middot; ${esc(meta.timestamp)} &middot; viewport ${meta.viewport.width}&times;${
    meta.viewport.height
  } &middot; settle ${meta.settleMs}ms</div>
</header>
<div class="grid">
${cards}
</div>
</body></html>`;

  const out = join(reportDir, "index.html");
  await writeFile(out, html);
  return out;
}
