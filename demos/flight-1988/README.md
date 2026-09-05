# flight-1988 — the original SGI Flight Simulator (1988–89)

Gary Tarolli's flight as shipped on the late-80s IRIS 4D demo tape: colormap-mode IRIS GL, one aircraft module per file (Cessna 150, 747, F-15, F-16, F-18, P-38), `dog` networked multiplayer as a sibling build, and the recorded `airshow`. The version banner is the unsubstituted `Version vnum` placeholder — this source never numbers itself (it sits between the binary-only V2.4 and Version 3.4; see the archive catalog in `~/Downloads/sgi-flight-versions/CATALOG.md`).

## Faithful source

Sources are the pristine 1988–89 tree (byte-identical to the archive, flat layout as SGI shipped it, including `airshow`, the `m_*` menus, `iconize.cps`, and SGI's `Makefile` as `Makefile.orig`) except **25 diff lines across 4 files**, each an unavoidable modern-C/64-bit/wasm fix, commented in place:

- `main.c` — K&R untyped `main(argc,argv)`; clang requires the `char **` signature (5 lines).
- `flight.c` — arg-less `exit()` needs a status; the non-DOGFIGHT `broadcast()`/`lookup_plane()` stubs declared no parameters while callers pass one, which traps wasm's call-signature checking (6 lines).
- `meters.c` — `#define X_ADJUST (XMAXSCREEN.0 / 1024.0)`: the IRIX preprocessor pasted `.0` onto the expanded constant; modern cpp can't (4 lines).
- `uflight.c` — the depth-sort tags plane pointers by OR-ing `PLANE_BIT` into an `(int)` cast of the pointer; 64-bit pointers don't fit. The tag now lives in the low bit of the aligned pointer via `(long)` casts — same algorithm, same array (10 lines).

Everything else the old port changed at the source level is handled by the runtime instead:

- **The pre-Asyncify main-loop restructure is gone.** The original `flight()` — one big function with `goto start:`/`pickit:` labels and an internal event loop — runs as-is: on web, Emscripten ASYNCIFY yields inside `swapbuffers`/`qread`, so the loop never needed to be inverted.
- `register` is erased with `-Dregister=`, and flight's own `random(range)` (which collides with libc's) is renamed with `-Drandom=flight_random` — both in the [Makefile](Makefile), zero source lines.
- IRIX `<psio.h>` and the cps-generated `iconize.h` (NeWS PostScript window-iconify, "thanks to Mark Callow") are satisfied by stubs in `include/shim/`.
- `comm.c`/`udpcomm.c`/`udpbrdcst.c`/`shadow.c` are present but excluded from the build (`DEMO_EXCLUDE_SRC`), exactly matching SGI's own Makefile: the `flight` binary never linked them — they belong to the separate `dog` and `shadow` targets.

## libgl fixes this port drove (benefit every demo)

- **Colormap writemask clears.** flight composites its meters in bitplanes: scale art (brown/orange/grey2) lives in planes 0–1 and the moving bars/text (blue/red/white) in planes 2–3, erased per frame by `clear()` through `writemask(wm_allplanes-3)`. libgl's RGB framebuffer has no index planes, so a masked cmode clear is now an exact palette recoloring of the viewport rect (oldRGB → RGB[(oldIndex & ~wm) | (clearIndex & wm)], both rasterizers), honoring the current pattern (the crashed-meters effect is a patterned clear through `writemask(white)`).
- **`clear()` actually clears the viewport.** The partial-viewport path drew a unit polygon through the current matrices, which only covered the viewport if the projection mapped 0..1 onto it — flight's `CLEAR_*` objects set world-coordinate `ortho2` ranges, so every per-frame erase was a no-op: the thrust/speed bars accumulated into solid blocks over the gauge ticks, the altitude status line smeared, and the compass rose ghosted. It now fills the exact viewport rectangle in screen space.
- **Authentic 9×15 text font.** `charstr` now renders the X11 Misc-Fixed 9×15 (public domain, ascent 12/descent 3 — the classic IRIS terminal-font metrics) instead of an 8×16 zero-descent bitmap whose glyphs extended 16 px above the baseline: meter labels ("Speed"/"knots") bled into each other and "Front view" at the top viewport edge lost its upper rows. `strwidth`/`getheight`/`getdescender` report the new metrics.
- **`getplanes()` returns 12** (deepest IRIS cmode config, and what SGI documented flight for) instead of 24, which overflowed flight's `(1 << getplanes()) - 1` writemask math in a `short`.
- **`qdevice(KEYBD)` no longer leaks raw key devices.** Every keypress used to enqueue both the raw IRIS key device (GKEY, …) and the KEYBD ASCII event; real IRIS GL queues raw keys only when individually `qdevice()`d. flight's `wait_for_input` treats unknown devices as buttons and drains the queue "until release" — eating real keystrokes.
- **REDRAW pulses are coalesced** (at most one outstanding): the events layer pulses REDRAW to waiting demos in lieu of a window system, and flight handles one event per redraw, so an uncoalesced 30 Hz backlog buried keypresses seconds deep.
- **`prefposition()` is honored as a fixed-size framebuffer**: flight hard-codes its layout to the classic screen and never queries the window size, so it gets exactly the framebuffer it asks for, scaled to the canvas. With `XMAXSCREEN`/`YMAXSCREEN` corrected to the real IRIS 4D 1280×1024 (they were an Alice4-era 800×480 — `meters.c`'s `/1024.0` scale factors give it away), flight renders at its designed resolution.

## Earlier versions

A `flight` version 1.0 executable for the Motorola 68k IRIS 1400, contributed uuencoded by @ara4n (issue #4), was kept under `versions/` until 2026-09-05, when it was removed from the repository along with the other SGI executables (see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md)). It is kept offline for a future reconstruction; SHA-256 of the decoded binary (176,660 bytes): a0c5d96d634d863f072213e120f3ea64e481fa114a723594c59e3912fb9a9c49.

## Status

Native + web build; splash → plane menu → takeoff → crash messages all work with the authentic flow (the old port skipped the splash and plane selection entirely and started as a hardcoded 747, with a leftover "extra high tower for debugging" eye offset). The old port's other README issues are fixed:

- **"planes too slow in web version"** — the old port didn't compile with `-D_4D` (it's in SGI's own LCOPTS, see `Makefile.orig`), so it ran the IRIS-3000 fallback physics whose `CLOCKRATE` assumes a 60 Hz `times()` clock; ours ticks at 100 Hz, so the sim computed ticks-per-second ~40% low. Built with `-D_4D -DHZ=100`, the F-18 reaches takeoff speed in seconds.
- **"night mode 'shimmers'"** — gone; consecutive night frames are pixel-identical (the shimmer was the old non-blocking `qread` spinning full-screen redraws).
- **"cockpit glitches"** — the panel and views render cleanly at the design resolution.

Remaining known issue: no network play (`dog` is a separate build target and isn't linked, same as SGI's `flight` binary).
