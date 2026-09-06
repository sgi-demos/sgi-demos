# Sunflower

Paul Haeberli, SGI, 1984. Draws a sunflower-like pattern of circles: `sunflower <nseeds> <seedsize> <growth>`, for example `sunflower 400 .05 1.1`. Not in the built demo list yet.

## Provenance

Source is `mextools/tools/sunflower.c` from the gifts package (`/usr/people/gifts/mextools`) that SGI installed with GL2-W3.6, its May 1989 system release for the IRIS 2400/3000 series, archived at bitsavers as [gl2-w3.6+options.tar.gz](https://bitsavers.org/bits/SGI/iris/gl2-w3.6+options.tar.gz) (Standard System (usr) image; hashes in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives)). SGI installed gifts as source on every IRIS 2400/3000, and its README invites the customer to read it. About 45 changed lines for modern C (main signature, prototypes, and window setup stubbed for the single-window emulator, marked `TODO`). The file carries only its author line, no copyright or license notice (the mextools directory it came from has a Notice file with SGI's 1986 proprietary legend, kept in libs/portlib). It is used here under fair use as a noncommercial preservation port; see [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md) section 3.2. The author line is retained.

Every change against the archive copy is recorded in git; `git log -p` on a file shows each one, and the archive copy can be diffed directly from the tarball cited above.
