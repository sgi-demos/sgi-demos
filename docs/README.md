# Docs

- [ARCHITECTURE.md](ARCHITECTURE.md): how the original IRIS GL demo source runs on modern hardware and in the browser.
- [IRIS_GL_API.md](IRIS_GL_API.md): the IRIS GL API surface, as a single text file generated from SGI's Technical Reference (see below).
- [COPYRIGHT.md](COPYRIGHT.md): provenance, licensing, and fair-use record for every demo and library.
- [COPYRIGHT_TODO.md](COPYRIGHT_TODO.md): open items from that record.

## IRIS GL manuals

SGI's Graphics Library Programming Guide, Reference Manual, Technical Reference, and IRIS GL to OpenGL Porting Guide are kept in the separate [sgi-docs](https://github.com/sgi-demos/sgi-docs) repository (moved there on 2026-09-05). The same manuals are archived at [bitsavers](https://bitsavers.org/pdf/sgi/) and the [Internet Archive](https://archive.org/search?query=silicon+graphics+graphics+library). `scripts/docs2md.sh` regenerates IRIS_GL_API.md from a sibling checkout of sgi-docs.
