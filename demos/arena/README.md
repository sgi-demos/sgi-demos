# Arena

Rob Mace, SGI, 1988. "Simulates a future sport": MECH combat in a maze, drawn in colorindex mode, with optional multi-player play over Ethernet (`-n`). The demo-tape slide is in [arena.info](arena.info).

## Provenance

Source is `sgi/arena` from the IRIS 4D demo tape as archived at bitsavers (sgidemos.tar.Z; hash in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives)). Changes for this port: the startup text is reflowed and the startup screen disabled (startup.c), the UDP network code is fenced behind `NETWORKING` and its IRIX-only headers replaced (udpbrdcst.c, comm.c), K&R float-pasting macros such as `XMAXSCREEN.0` are spelled out, and missing includes and prototypes were added (about 230 changed lines across 15 files, mostly the network and startup code). No network play yet; the [Makefile](Makefile) has the switch and run target for working on it.

The files carry no copyright or license notice. This source is used under fair use, like the rest of the demo tape SGI shipped to its customers; see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md#3-categories-of-material-and-the-basis-for-using-each). Every original author line is retained.
