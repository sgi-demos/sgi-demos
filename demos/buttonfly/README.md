# Buttonfly

Wade Olsen, SGI, late 1980s. The user-configurable 3D hierarchical menu that fronted the demo tape: buttons tumble to reveal sub-menus or run a command. The demo-tape slide is in [buttonfly.info](buttonfly.info), and this port's menus (which launch the other web demos) are under [menus/](menus/).

## Provenance

Source is `sgi/buttonfly` from the IRIS 4D demo tape as archived at bitsavers (sgidemos.tar.Z; hash in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives)). Changes for this port: the menu file path and exit handling (buttonfly.c), event-callback prototypes for modern C (event.c, event.h), and small parser and lexer fixes; the bison-generated parser.tab.c and parser.tab.h replace the tape's y.tab.h, and the tape's unused fly.c is not included (about 60 changed lines).

The files carry no copyright or license notice. SGI shipped this source to its customers on the demo tape, and it is used here under fair use as a noncommercial preservation port; see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md) section 3.2. Every original author line is retained.

Every change against the archive copy is recorded in git; `git log -p` on a file shows each one, and the archive copy can be diffed directly from the tarball cited above.
