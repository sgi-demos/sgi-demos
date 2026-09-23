# flight-1994 — SGI Flight Simulator Version 3.4

Rob "Mr. Flight" Mace's unified Developer Toolbox flight (banner: `SGI Flight Simulator Version 3.4`, copyright 1984–1994). This is the version everyone remembers from IRIX: RGB mode with lighting (`light.c`), fog (`fog.c`), terrain texture (`tex.c`), AIFF sound (`aifflib.c`/`sound.c`), collision (`collision.c`), time-based physics (`ftime.c`), and the companion programs `dog`, `radar`, and `shadow` — all built as **one binary** that dispatches on argv[0] (SGI's Makefile symlinked `dog`/`radar`/`shadow` to `flight`).

It is a separate demo from [flight-1988](../flight-1988), the 1988–89 colormap-mode original — this is a historical preservation project, so each significantly different version gets its own port.

## Provenance

Imported byte-identical to the archives (this port's changes, under Port status, are on top, in git):

- **Sources, `defs/` data, `COPYRIGHT`, `README.orig`, `Makefile.orig`** — SGI Linux Toolbox, March 2003 (`toolbox.sgi.com/linux/src/demos/GL/flight`). This copy carries SGI's **permissive free-use license** ("Permission to use, copy, modify, and distribute this software for any purpose and without fee is hereby granted…"); the IRIX Developer Toolbox trees of the same code are marked proprietary. The model/sound data is byte-identical to the Developer Toolbox 6.1 copies.
- **`defs/hills.grid`, `defs/hills.t`** (terrain grid + texture) — Developer Toolbox 6.1 tree (absent from the Linux Toolbox mirror). The Developer Toolbox sources carry SGI's proprietary legend rather than the permissive license, but these two files are data and carry no notice; they are the same terrain the permissively licensed flight loads, and are used here on the same fair-use basis as the demo-tape data (see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md#3-categories-of-material-and-the-basis-for-using-each)). If a copy in a permissively licensed tree turns up, it should replace these.
- **`libgobj/`** — the object-file library flight 3.4 loads its `defs/*.d` models with (`objext.c` → `readobj()` etc.), from the Linux Toolbox scrape, also under the permissive license. SGI built it as a sibling `../libgobj/libgobj.a`.

Where 3.4 sits in the flight lineage, from the version catalog of every known release:

| Version | Year | Shipped in | Source |
|---|---|---|---|
| 1.0 | 1984 | IRIS 1400 (68k) | binary only |
| 2.4 | 1988 | IRIS 4D demo tape (CLOVER1); Developer Toolbox 2.0 (1991, WINGMAN revision) | source, proprietary legend (flight-1988) |
| 3.3 | 1991 | Developer Toolbox 2.0 (CLOVER2) | source, proprietary legend |
| 3.4 | 1994 | Developer Toolbox 4.0, 4.1, 4.2 (1994), 6.1 (1996), and the 1997 release; revisions 1.1 and 1.31 differ only in copyright wording | source, proprietary legend |
| 3.4 | 1994 | Linux Developer Toolbox (2003) | source, SGI permissive license (this demo) |
| 3.4.1 | 1997 | Windows, Cosmo OpenGL | binary only |

`Makefile.orig` is SGI's smake file: 27 CFILES, `-DAUDIO`, `-I../libgobj`, links `libgobj.a -lgl -lX11 -lbsd -lm -laudio`.

## Port status

Native and web: the Version 3.4 splash, plane menu, instrument panel, and the lit, fogged, textured world with its heads-up display and explosions; the smoke test passes in both rasterizers.

Changes for this port:

- **Vintage-C fixes** — K&R `main()`, 3-arg `strcat`, `&register` vars, `%i` vs LP64 (`long` is 64-bit now, not IRIX's 32), and wasm call-signature strictness (function prototypes for `set_text_meter`, `draw_infinite_world`, `feedback`, `lseek`, `bzero`/`bcopy`).
- **libgobj loader bugs** (would corrupt the heap / hang on any host): a 500-entry `numbuf` overflow and a non-advancing default case in `readnumlist`, and `read_grid()` reading the big-endian IRIX `hills.grid` without byte-swapping (plus a `sizeof * n+1` precedence bug that under-allocated the elevation grid).
- **Build** — the [Makefile](Makefile) compiles `libgobj/*.c` alongside the root sources (`DEMO_EXTRA_SRC`), leaves out `aifflib.c` (`DEMO_EXCLUDE_SRC`), builds with `-DNO_MS` (no multisample), and preloads `defs/` at the IRIX path (`--preload-file defs@/usr/demos/data/flight`), so no `-D` argument is needed.

It relies on libgl's lighting, per-vertex fog, alpha blending, texturing with a texture matrix, blocking `qread`, and a web `times()` that advances (see `libs/libgl/times.c`).

Keys worth knowing: F1 toggles fog and m/M change its density, F2 toggles the terrain texture, H the heads-up display, and n/N move the time of day ±5 minutes; it starts at the local clock time, so expect night in the evening.

Not yet: sound (`-DAUDIO` is off; `aifflib.c` needs an SDL2 backend), network play (`dog`), and the `radar` and `shadow` companions (3.4 builds them from the same binary via argv[0]; the web demo is `flight` only).
