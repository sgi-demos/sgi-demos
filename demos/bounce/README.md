# Bounce

SGI, late 1980s. Three lit, shaded balls bouncing inside a wire-grid room, with a menu of alternative object files (`*.bin`: martini glass, doughnut, VW, X-29, candlestick, SGI logo).

## Provenance

Source is `sgi/bounce` from the IRIS 4D demo tape as archived at bitsavers (sgidemos.tar.Z; hash in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives)); that pristine copy is kept as [versions/bitsavers/bounce.c](versions/bitsavers/bounce.c), alongside the Alice 4 adaptation and the Developer Toolbox 4.0 version for comparison. The built [bounce.c](bounce.c) is the most adapted demo in the collection: about 170 changed lines against the tape (identity and view matrices, spin defaulting on, standard includes, prototype fixes), largely inherited from the Alice 4 port.

The files carry no copyright or license notice. SGI shipped this source to its customers on the demo tape, and it is used here under fair use as a noncommercial preservation port; see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md) section 3.2. Every original author line is retained. The Alice 4 changes are Apache License 2.0.

Every change against the archive copy is recorded in git; `git log -p` on a file shows each one, and the archive copy can be diffed directly from the tarball cited above.
