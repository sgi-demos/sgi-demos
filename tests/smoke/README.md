# Visual smoke tests (web targets)

Loads each demo's `demos/<name>/web/<name>_full.html` in headless Chromium —
once per rendering mode (`?rast=ref` CPU reference rasterizer, `?rast=gles2`
GPU rasterizer) — waits for the WASM to load and the animation to settle,
screenshots the canvas, and fails the capture if the page threw, aborted,
printed `ERROR:`, or rendered a blank frame.

This is a smoke gate, not a pixel-diff: the demos animate (some randomize),
so the automated check is "did it load and draw real content in both modes."
For rasterizer-level pixel comparison, see `scripts/ppm_compare.py`.

## Usage

From the repo root (web targets must be built first — `make browser`):

    make smoke              # run the gate; exits non-zero on any failure
    make smoke-baseline     # also promote current frames to baseline/

Directly, for finer control:

    cd tests/smoke
    node smoke.mjs --only insect,jello      # subset of demos
    node smoke.mjs --modes gles2            # one rendering mode only

First run installs node deps + headless Chromium (`npm install`,
`npx playwright install chromium`), triggered automatically by `make smoke`.

## The review gallery

Every run writes `report/index.html`: one card per demo with the CPU and
GLES2 captures side by side, clickable thumbnails to the full PNGs, per-mode
PASS/FAIL badges, and any captured console errors. This is the human eyeball
pass before a commit.

Baselines (`baseline/`, created by `make smoke-baseline`) are shown in a
collapsible row per card for drift-spotting; they are NOT part of the
pass/fail gate.

## Tuning

- `demos.json` — `settleMs` (global wait for first real frames), `modes`
  (global; per-demo override via a `modes` array on the entry), `minContent`
  (per-demo non-blank threshold; the default 0.02 means >2% of pixels must
  differ from the dominant color).
- `cedit` is intentionally absent: it has no web page yet. Add it to
  `demos.json` once `cedit_full.html` exists.
