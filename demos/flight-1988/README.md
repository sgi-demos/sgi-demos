# flight-1988 — the original SGI Flight Simulator (1988–89)

Gary Tarolli's flight as shipped on the late-80s IRIS 4D demo tape: colormap-mode IRIS GL, one aircraft module per file (Cessna 150, 747, F-15, F-16, F-18, P-38), `dog` networked multiplayer as a sibling build, and the recorded `airshow`. The version banner is the unsubstituted `Version vnum` placeholder — this source never numbers itself (it sits between the binary-only V2.4 and Version 3.4; see the version table in [flight-1994's README](../flight-1994/README.md#provenance)).

## Faithful source

Sources are the pristine 1988–89 tree (byte-identical to the archive, flat layout as SGI shipped it, including `airshow`, the `m_*` menus, `iconize.cps`, and SGI's `Makefile` as `Makefile.orig`) except **25 diff lines across 4 files**, each an unavoidable modern-C/64-bit/wasm fix, commented in place:

- `main.c` — K&R untyped `main(argc,argv)`; clang requires the `char **` signature (5 lines).
- `flight.c` — arg-less `exit()` needs a status; the non-DOGFIGHT `broadcast()`/`lookup_plane()` stubs declared no parameters while callers pass one, which traps wasm's call-signature checking (6 lines).
- `meters.c` — `#define X_ADJUST (XMAXSCREEN.0 / 1024.0)`: the IRIX preprocessor pasted `.0` onto the expanded constant; modern cpp can't (4 lines).
- `uflight.c` — the depth-sort tags plane pointers by OR-ing `PLANE_BIT` into an `(int)` cast of the pointer; 64-bit pointers don't fit. The tag now lives in the low bit of the aligned pointer via `(long)` casts — same algorithm, same array (10 lines).

Everything else is handled outside the source:

- The original `flight()` — one big function with `goto start:`/`pickit:` labels and its own event loop — runs as-is: on the web, Asyncify yields inside `swapbuffers`/`qread`.
- `register` is erased with `-Dregister=`, and flight's own `random(range)` (which collides with libc's) is renamed with `-Drandom=flight_random`, both in the [Makefile](Makefile).
- IRIX `<psio.h>` and the cps-generated `iconize.h` (NeWS PostScript window-iconify, "thanks to Mark Callow") are satisfied by stubs in `include/shim/`.
- `comm.c`/`udpcomm.c`/`udpbrdcst.c`/`shadow.c` are present but excluded from the build (`DEMO_EXCLUDE_SRC`), exactly matching SGI's own Makefile: the `flight` binary never linked them — they belong to the separate `dog` and `shadow` targets.

flight leans on more of libgl than most demos: colormap writemask clears (its meters' scale art lives in planes 0–1 under bars erased through `writemask(wm_allplanes-3)`), `clear()` scoped to the viewport, the IRIS font 0 metrics for its labels, a 12-plane `getplanes()` (24 overflows its writemask math), raw keys queued only when `qdevice()`d, coalesced REDRAWs, and `prefposition()`'s fixed 1280×1024 framebuffer.

## Earlier versions

A `flight` version 1.0 executable for the Motorola 68k IRIS 1400, contributed uuencoded by @ara4n ([issue #4](https://github.com/sgi-demos/sgi-demos/issues/4)), was kept under `versions/` until 2026-09-05, when it was removed from the repository along with the other SGI executables (see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md)). It is kept offline for a future reconstruction; its hash is in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives).

## Status

Native and web: splash, plane menu, takeoff, flight, and crash messages, at the designed resolution. It is built with `-D_4D` (SGI's own LCOPTS) and `-DHZ=100`; without `_4D` the IRIS-3000 fallback physics assumes a 60 Hz clock and runs about 40% slow.

No network play: `dog` is a separate build target that isn't linked, the same as SGI's `flight` binary.
