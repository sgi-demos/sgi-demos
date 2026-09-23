# Buttonfly

Wade Olsen, SGI, late 1980s. The user-configurable 3D hierarchical menu that fronted the demo tape: buttons tumble to reveal sub-menus or run a command. The demo-tape slide is in [buttonfly.info](buttonfly.info), and this port's menus (which launch the other web demos) are under [menus/](menus/).

## Provenance

Source is `sgi/buttonfly` from the IRIS 4D demo tape as archived at bitsavers (sgidemos.tar.Z; hash in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives)). Changes for this port: the menu file path and exit handling (buttonfly.c), event-callback prototypes for modern C (event.c, event.h), and small parser and lexer fixes; the bison-generated parser.tab.c and parser.tab.h replace the tape's y.tab.h, and the tape's unused fly.c is not included (about 60 changed lines).

The files carry no copyright or license notice. This source is used under fair use, like the rest of the demo tape SGI shipped to its customers; see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md#3-categories-of-material-and-the-basis-for-using-each). Every original author line is retained.
