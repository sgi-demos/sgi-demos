# gview (Barcelona)

An IRIS GL viewer for GFO radiosity model files, from Silicon Graphics, late 1980s. Displays Gouraud-shaded polygons whose per-vertex colors come from a precomputed radiosity solution; the Barcelona database is Mies van der Rohe's 1929 German Pavilion, the Sphere database a simple test room. Both `.gfo` files, their `.info` slides, and the man page came from the same IRIX 3 distribution as the binary.

## Provenance

No source for gview is known to survive. [gview.c](gview.c) was reconstructed from the IRIX 3 MIPS ECOFF executable: Capstone disassembly, the m2c MIPS-to-C decompiler, Ghidra 11 for the event loop and popup menu, then iterative rewriting into readable C. Key bindings were confirmed against the IRIX 3.3 man page (April 1990). The reconstructed file is original C; it contains no SGI object code. See [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md) section 3.4 for the legal basis.

The original executable, the Ghidra project databases, the disassembly and m2c output, the man page, and the `.info` slides moved out of this repository on 2026-09-05 and are kept offline. The executable's hash in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives). It was extracted from an IRIX 3 installation tape. The SGI GFO format description is in [sgi-docs](https://github.com/sgi-demos/sgi-docs).

## Status

Fly-through (`-f`) and turntable modes work, native and web. Not implemented: materials, movie loops, the binary model cache (`-R`/`-W`), image save.
