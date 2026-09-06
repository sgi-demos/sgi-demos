# libdemo

The demo tape's shared library of colormap helpers (Paul Haeberli, 1984): colormod.c, gamma.c, getset.c, grey.c, and demolib.h, plus getapixel.c from portlib (byte-identical to the copy in the GL2-W3.6 gifts package; see libs/portlib/README.md).

## Provenance

Source is `sgi/lib/libdemo` from the IRIS 4D demo tape as archived at bitsavers (sgidemos.tar.Z; hash in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives)); colormod.c and grey.c are byte-identical to the tape and gamma.c, getset.c, and demolib.h differ by a dozen lines of build fixes. `Makefile_orig` is SGI's. The files carry only their author lines, no copyright or license notice, and are used here under fair use as part of a noncommercial preservation port; see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md) section 3.2.
