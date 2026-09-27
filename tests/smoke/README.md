# Visual smoke tests (web targets)

Loads each demo's web page (`demos/<name>/web/`, its `index.html`) in headless Chromium — once per rendering mode (`?rast=ref` CPU reference rasterizer, `?rast=gles` GPU rasterizer) — waits for the WASM to load and the animation to settle, screenshots the canvas, and fails the capture if the page threw, aborted, printed `ERROR:`, or rendered a blank frame.

This is a smoke gate, not a pixel-diff: the demos animate (some randomize), so the automated check is "did it load and draw real content in both modes." For rasterizer-level pixel comparison, see `scripts/ppm_compare.py`.

## Usage

From the repo root (web targets must be built first — `make browser`):

    make smoke              # run the gate; exits non-zero on any failure
    make smoke-baseline     # also promote current frames to baseline/

Directly, for finer control:

    cd tests/smoke
    node smoke.mjs --only insect,jello      # subset of demos
    node smoke.mjs --modes gles             # one rendering mode only

First run installs node deps + headless Chromium (`npm install`, `npx playwright install chromium`), triggered automatically by `make smoke`.

## The demos

Every demo the root Makefile builds is tested: `make list` (`lib/demos.mjs` reads it), which is every demo directory with a Makefile except drafts. A variant in a subdirectory is named with a dash: `ep-1994/decomp` is `ep-1994-decomp`.

## The review gallery

Every run writes `report/index.html`: one card per demo with the ref (CPU) and gles (GPU) captures side by side, clickable thumbnails to the full PNGs, per-mode PASS/FAIL badges, the placard's note on what the port does not do yet, and any captured console errors. This is the human eyeball pass before a commit.

Baselines (`baseline/`, created by `make smoke-baseline`) are shown in a collapsible row per card for drift-spotting; they are NOT part of the pass/fail gate.

## Tuning

`demos.json` holds the settings: `settleMs` (wait for first real frames), `modes`, and `minContent` (the non-blank threshold; the default 0.02 means more than 2% of pixels must differ from the dominant color). Its `demos` object overrides them for the demos that need it (the sparse Electropaints, newave, and cedit), and can add an `arg`.

## Frame rate (perf)

`perf.mjs` runs every demo for 10 seconds with the gles (GPU) rasterizer and reports its frame rate — native (Windows, macOS, Linux) or web (Chromium). The ref (CPU) rasterizer is the reference for correctness, not speed, so it is left out; `--modes ref` measures it anyway.

    make perf-native        # needs `make native`
    make perf-web           # needs `make browser`
    make perf               # both

With `IRISGL_FPS=1` (`?fps=1` on the web), libgl prints `IRISGL_FPS <fps> <frames> <ms>` once a second from the one place every frame is presented (`sdl_events_frame_complete`). The runner drops the first second (warmup: first frames, shader builds) and reports, per demo, LOW (the slowest one-second window), AVG (total frames over total time), and HIGH (the fastest window), and WARNs when LOW is under 15 fps. The demos are paced to 30 fps, so ~30 is the ceiling. The PERF SUMMARY table is printed and written to `perf/<platform>.txt` (platform is `web`, `win`, `mac`, or `linux`), with the numbers in `perf/<platform>.json` and each run's output in `perf/logs/<platform>/`. It exits non-zero only if a demo produced no frames; warnings are a report, not a gate.

A native demo runs from its directory with its placard's `web_arg`, as on the web. Native builds are `-O0 -g -fsanitize=undefined`, so they are slower than the `-O2` web builds. The web report names the WebGL renderer Chromium gave it: if that is SwiftShader (software), the gles numbers measure the CPU, not the GPU — try `--headed`.

    cd tests/smoke
    node perf.mjs --target web --only insect,jello --seconds 5 --headed

`perf.json` holds the settings: `seconds`, `warnFps`, `modes`, and per-demo `modes` overrides.

## Interaction driver

`interact.mjs` drives real mouse interactions headlessly — newave's popup menus, display modes and mesh editing; cedit's slider drags and colorsys menu — and drops annotated screenshots in `results/interact/`. It is a manual verification tool, not part of the smoke gate:

    node interact.mjs                     # both demos
    node interact.mjs --only newave      # subset
