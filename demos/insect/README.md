# Insect

Thant Tessman, SGI, mid-1980s, originally for the IRIS 2400; colormap and window handling additions by David B. Ligon, 1988. Tessman's name is not in the source (Ligon's is the only one); the attribution comes from the [Alice 4 project page](https://lkesteloot.github.io/alice/alice4/), whose authors met him and record insect as "one of the classic demos that Thant wrote in the mid-1980s". A six-legged walker demonstrating a joint-motion algorithm, with backface removal, painter's-algorithm hidden surfaces, software lighting, and a projected shadow. The demo-tape slide is in [insect.info](insect.info).

## Provenance

Source is `sgi/insect` from the IRIS 4D demo tape as archived at bitsavers (sgidemos.tar.Z; hash in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives)), restored against that copy in 2023. Changes for this port: the globals defined in insect.h became `extern` declarations with the definitions moved into insect.c, because the wasm linker rejects the K&R common-symbol idiom, and one float-pasting macro (`RES.0`) is spelled out (about 160 changed lines, almost all the extern/definition split).

The files carry no copyright or license notice. SGI shipped this source to its customers on the demo tape, and it is used here under fair use as a noncommercial preservation port; see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md) section 3.2. Every original author line is retained.

Every change against the archive copy is recorded in git; `git log -p` on a file shows each one, and the archive copy can be diffed directly from the tarball cited above.
