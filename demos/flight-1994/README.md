# flight-1994 — SGI Flight Simulator Version 3.4

Rob "Mr. Flight" Mace's unified Developer Toolbox flight (banner: `SGI Flight Simulator Version 3.4`, copyright 1984–1994). This is the version everyone remembers from IRIX: RGB mode with lighting (`light.c`), fog (`fog.c`), terrain texture (`tex.c`), AIFF sound (`aifflib.c`/`sound.c`), collision (`collision.c`), time-based physics (`ftime.c`), and the companion programs `dog`, `radar`, and `shadow` — all built as **one binary** that dispatches on argv[0] (SGI's Makefile symlinked `dog`/`radar`/`shadow` to `flight`).

It is a separate demo from [flight-1988](../flight-1988), the 1988–89 colormap-mode original — this is a historical preservation project, so each significantly different version gets its own port.

## Provenance

Imported unmodified (byte-identical to the archive; see `~/Downloads/sgi-flight-versions/CATALOG.md` for the full version catalog):

- **Sources, `defs/` data, `COPYRIGHT`, `README.orig`, `Makefile.orig`** — SGI Linux Toolbox, March 2003 (`toolbox.sgi.com/linux/src/demos/GL/flight`). This copy carries SGI's **permissive free-use license** ("Permission to use, copy, modify, and distribute this software for any purpose and without fee is hereby granted…"); the IRIX Developer Toolbox trees of the same code are marked proprietary. The model/sound data is byte-identical to the Developer Toolbox 6.1 copies.
- **`defs/hills.grid`, `defs/hills.t`** (terrain grid + texture) — Developer Toolbox 6.1 tree (absent from the Linux Toolbox mirror).
- **`libgobj/`** — the object-file library flight 3.4 loads its `defs/*.d` models with (`objext.c` → `readobj()` etc.), from the Linux Toolbox scrape, also under the permissive license. SGI built it as a sibling `../libgobj/libgobj.a`.

`Makefile.orig` is SGI's smake file: 27 CFILES, `-DAUDIO`, `-I../libgobj`, links `libgobj.a -lgl -lX11 -lbsd -lm -laudio`.

## Port status

**Runs (WIP).** Builds native + web, renders the Version 3.4 splash, the 8-plane selection menu, the instrument panel, and the 3D sky/ground world, and reaches the main flight loop. In the top-level `DEMOS` list; smoke test passes in both rasterizer modes.

What the port needed (all done):

- **Build wiring** — `make_demo.mk` gained `DEMO_EXTRA_SRC`/`DEMO_EXTRA_HDRS`/`DEMO_EXCLUDE_SRC` hooks so this demo compiles `libgobj/*.c` alongside the root sources. `defs/` is preloaded at the IRIX path (`--preload-file defs@/usr/demos/data/flight`) so no `-D` argument is needed.
- **libgl surface** — added the IRIS GL calls 3.4 uses that flight-1988 didn't: `circ`/`circf`, `cmov`/`cmov2`, `v2i`/`v3i`, `getcpos`, `getviewport`, `strwidth`/`getheight`/`getdescender`, `swaptmesh`, `fasin`/`fcos`/`fexp`/`fsqrt`, and `getgdesc()` inquiries. Real lighting (`lmdef`/`lmbind`) was already in libgl. Texturing (`texdef2d`/`texbind`/`tevdef`), fog (`fogvertex`), and blending (`blendfunction`) are **stubs** for now — built with `-DNO_MS` (no multisample), so terrain texture and fog are absent.
- **Vintage-C fixes** — K&R `main()`, 3-arg `strcat`, `&register` vars, `%i` vs LP64 (`long` is 64-bit now, not IRIX's 32), and wasm call-signature strictness (function prototypes for `set_text_meter`, `draw_infinite_world`, `feedback`, `lseek`, `bzero`/`bcopy`).
- **libgobj loader bugs** (would corrupt the heap / hang on any host): a 500-entry `numbuf` overflow and a non-advancing default case in `readnumlist`, and `read_grid()` reading the big-endian IRIX `hills.grid` without byte-swapping (plus a `sizeof * n+1` precedence bug that under-allocated the elevation grid).
- **Blocking `qread`** — real IRIS GL `qread` blocks until an event arrives; the Alice4 libgl returned 0 on an empty queue, so flight 3.4's `wait_for_input` splash-wait busy-spun and starved the browser. `qread` now waits for an event via a new `events_qread_block()` yield point. On web this is not a real main-thread block: each iteration pumps events and calls `emscripten_sleep`, which cooperatively yields to the browser via Asyncify (the same per-frame yield path `swapbuffers` already uses); on native it's a real `SDL_Delay`.
- **Projection matrix in MVIEWING mode** — `perspective()`/`ortho2()` in libgl loaded the *current* stack, which in `MVIEWING` mode (what flight runs in) is the modelview, not the projection. flight's per-frame `perspective` was landing in the modelview and then getting overwritten by the next `loadmatrix`, so the projection stayed identity and the whole world collapsed into a narrow center strip. Real IRIS GL always targets the projection matrix here (as libgl's own `window()` already did); fixed both to match. Other demos were unaffected — MPROJECTION demos already had `current_stack` == projection stack, and the MVIEWING demos (ideas, ep-1989) happened to set perspective in MSINGLE first, so their projection was already correct.

### Known remaining glitches (the WIP part)

- No texture (terrain `hills.t`), no fog, no blending — stubbed in libgl.
- No sound (`-DAUDIO` off; `aifflib.c` excluded — needs an SDL2 backend).
- No network play (`dog`) — same as flight-1988.
- `dog`/`radar`/`shadow` companions aren't wired up (3.4 builds them from the same binary via argv[0]; the web demo is `flight` only).
