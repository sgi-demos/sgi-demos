# Ideas in Motion

SGI, c. 1987, written for the 4D/70GT. Letters spell "ideas" on a lit tabletop under a lamp with a spotlight and the SGI logo; motion and lighting computed per frame, with hardware lighting on the logo and lamp and software per-vertex lighting on the table. The demo-tape slide is in [ideas.info](ideas.info).

## Provenance

Source is `sgi/ideas` from the IRIS 4D demo tape as archived at bitsavers (sgidemos.tar.Z; hash in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives)). Changes for this port: K&R float-pasting macros (`TIME.0`, `TABLERES.0`) spelled out and a stray argument removed in track.c, plus two one-line fixes in a.c and d.c (about 28 changed lines across 3 files).

The files carry no copyright or license notice. This source is used under fair use, like the rest of the demo tape SGI shipped to its customers; see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md#3-categories-of-material-and-the-basis-for-using-each). Every original author line is retained.
