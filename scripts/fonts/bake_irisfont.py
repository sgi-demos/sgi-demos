#!/usr/bin/env python3
"""Bake an IRIX 3 (GL2-era) raster screen font into a C source + header pair
for libgl, in the same BdfFont/BdfGlyph shape bake_bdf.py emits.

The input is a binary font as recovered from an IRIS running IRIX 3
(scripts/fonts/defaultfont = the system default screen font — IRIS GL
font 0, the font charstr() used unless a demo loaded its own). The format
is a 68k in-memory structure dumped to disk; all values big-endian:

    offset  size  field
    0x00    4     0x00005532 magic
    0x04    4     0x00005532 magic (repeated)
    0x08    2     type/version (2)
    0x0a    2     cell width   (9)
    0x0c    2     cell height  (15)
    0x0e    2     character count (128)
    0x10    4     address of free space past the last record (header field,
                  NOT a char pointer — it precedes the table)
    0x16    4*n   per-char record ADDRESSES (chars 0..n-1)

Addresses are 68k memory addresses; the file is the structure dumped from
its load address, so file_offset = address - BASE. BASE is recovered by
anchoring a known glyph bitmap (see --base; 0x18056 for this dump).

Each 18-byte char record:

    0x00    2     ? (0)
    0x02    2     ? (1)
    0x04    4     bitmap address (rows, bottom-up — IRIS rasters are y-up)
    0x08    2     ink width in pixels
    0x0a    2     ink height in rows
    0x0c    2     x offset, NEGATED vs BDF ('!' stores -3: indent 3 right)
    0x0e    2     y offset, NEGATED vs BDF (descenders store +2: 2 below
                  baseline)
    0x10    2     x advance (9 for every char — fixed pitch)

Bitmap rows are 16-bit big-endian words, ink left-justified at the MSB.
Rows are stored bottom-up; the BdfFont blob wants top row first, so rows
are reversed here. Cell height 15 with max descent 2 gives ascent 13.

Usage:
    bake_irisfont.py defaultfont --name irisfont0 --outdir ../../libs/libgl
"""

import argparse
import os
import struct
import sys


def parse(path, base):
    data = open(path, 'rb').read()
    magic1, magic2, ftype, cell_w, cell_h, nchars = struct.unpack('>IIHHHH', data[:16])
    if magic1 != 0x5532 or magic2 != 0x5532:
        sys.exit(f"bad magic: {magic1:#x} {magic2:#x}")

    glyphs = []
    max_descent = 0
    for c in range(nchars):
        (addr,) = struct.unpack('>I', data[0x16 + 4 * c: 0x1a + 4 * c])
        off = addr - base
        f0, f1, bmp_addr, w, h, xoff, yoff, adv = struct.unpack('>HHIHHhhH', data[off:off + 18])
        bmp = bmp_addr - base
        if not (0 <= bmp and bmp + 2 * h <= len(data)):
            sys.exit(f"char {c}: bitmap out of range ({bmp:#x})")
        rows = [struct.unpack('>H', data[bmp + 2 * r: bmp + 2 * r + 2])[0] for r in range(h)]
        rows.reverse()  # stored bottom-up; blob wants top row first
        rowbytes = (w + 7) // 8
        packed = []
        for v in rows:
            packed.append((v >> 8) & 0xff)
            if rowbytes == 2:
                packed.append(v & 0xff)
        # IRIS offsets are negated relative to the BDF BBX convention
        glyphs.append((c, w, h, -xoff, -yoff, adv, rowbytes, packed))
        max_descent = max(max_descent, yoff)

    return cell_w, cell_h, nchars, max_descent, glyphs


def emit(name, src_filename, cell_h, max_descent, glyphs):
    blob = []
    recs = []
    for (enc, w, h, xoff, yoff, adv, rowbytes, packed) in glyphs:
        offset = len(blob)
        blob.extend(packed)
        recs.append((enc, w, h, xoff, yoff, adv, rowbytes, offset))

    descent = max_descent
    ascent = cell_h - descent

    guard = f"__{name.upper()}_H__"
    h = []
    h.append(f"// Auto-generated from {src_filename} by bake_irisfont.py.")
    h.append(f"#ifndef {guard}")
    h.append(f"#define {guard}")
    h.append("")
    h.append("#include <stdint.h>")
    h.append("")
    h.append("// Struct layout shared with bdffont.h; guarded so either header")
    h.append("// may be included first.")
    h.append("#ifndef BDF_STRUCTS_DEFINED")
    h.append("#define BDF_STRUCTS_DEFINED")
    h.append("typedef struct {")
    h.append("    int16_t encoding;")
    h.append("    uint8_t width, height;")
    h.append("    int8_t  xoff, yoff;")
    h.append("    int8_t  advance;")
    h.append("    uint8_t rowbytes;")
    h.append("    uint32_t bitmap_offset;")
    h.append("} BdfGlyph;")
    h.append("")
    h.append("typedef struct {")
    h.append("    int16_t ascent, descent;")
    h.append("    int16_t min_encoding, max_encoding;")
    h.append("    int16_t num_glyphs;")
    h.append("    const BdfGlyph *glyphs;       // num_glyphs, sorted by encoding")
    h.append("    const uint8_t  *bitmap_blob;  // all glyph rows concatenated")
    h.append("} BdfFont;")
    h.append("#endif /* BDF_STRUCTS_DEFINED */")
    h.append("")
    h.append(f"extern const BdfFont {name};")
    h.append("")
    h.append(f"#endif /* {guard} */")
    header = "\n".join(h) + "\n"

    c = []
    c.append(f"// Auto-generated from {src_filename} by bake_irisfont.py.")
    c.append("// The IRIX 3 system default screen font — IRIS GL font 0, the font")
    c.append("// every charstr() went through unless the demo loaded its own.")
    c.append("// Committed as static source data (not a build product);")
    c.append("// regenerate only if the recovered font file changes.")
    c.append(f'#include "{name}.h"')
    c.append("")
    c.append(f"static const uint8_t {name}_blob[] = {{")
    for i in range(0, len(blob), 12):
        chunk = blob[i:i + 12]
        c.append("    " + ", ".join(f"0x{b:02x}" for b in chunk) + ",")
    c.append("};")
    c.append("")
    c.append(f"static const BdfGlyph {name}_glyphs[] = {{")
    for (enc, w, ht, xo, yo, adv, rb, off) in recs:
        c.append(f"    {{ {enc}, {w}, {ht}, {xo}, {yo}, {adv}, {rb}, {off} }},")
    c.append("};")
    c.append("")
    c.append(f"const BdfFont {name} = {{")
    c.append(f"    {ascent}, {descent},")
    c.append(f"    {recs[0][0]}, {recs[-1][0]},")
    c.append(f"    {len(recs)},")
    c.append(f"    {name}_glyphs,")
    c.append(f"    {name}_blob,")
    c.append("};")
    body = "\n".join(c) + "\n"
    return header, body


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("fontfile")
    ap.add_argument("--name", default="irisfont0")
    ap.add_argument("--outdir", default=None)
    ap.add_argument("--base", type=lambda v: int(v, 0), default=0x18056,
                    help="68k load address of the dump (default 0x18056)")
    args = ap.parse_args()

    cell_w, cell_h, nchars, max_descent, glyphs = parse(args.fontfile, args.base)
    print(f"{args.fontfile}: cell {cell_w}x{cell_h}, {nchars} chars, max descent {max_descent}")

    outdir = args.outdir or os.path.dirname(os.path.abspath(args.fontfile))
    header, body = emit(args.name, os.path.basename(args.fontfile), cell_h, max_descent, glyphs)
    hpath = os.path.join(outdir, args.name + ".h")
    cpath = os.path.join(outdir, args.name + ".c")
    open(hpath, "w").write(header)
    open(cpath, "w").write(body)
    print(f"wrote {hpath}\nwrote {cpath}")


if __name__ == "__main__":
    main()
