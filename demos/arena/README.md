# Arena

SGI, late 1980s. "Simulates a future sport": MECH combat in a maze, drawn in colorindex mode, with optional multi-player play over Ethernet (`-n`). The demo-tape slide is in [arena.info](arena.info).

## Provenance

Source is `sgi/arena` from the IRIS 4D demo tape as archived at bitsavers (sgidemos.tar.Z; hash in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives)). Changes for this port: the startup text is reflowed and the startup screen disabled (startup.c), the UDP network code is fenced behind `NETWORKING` and its IRIX-only headers replaced (udpbrdcst.c, comm.c), K&R float-pasting macros such as `XMAXSCREEN.0` are spelled out, and missing includes and prototypes were added (about 230 changed lines across 15 files, mostly the network and startup code). No network play yet.

The files carry no copyright or license notice. SGI shipped this source to its customers on the demo tape, and it is used here under fair use as a noncommercial preservation port; see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md) section 3.2. Every original author line is retained.

Every change against the archive copy is recorded in git; `git log -p` on a file shows each one, and the archive copy can be diffed directly from the tarball cited above.
