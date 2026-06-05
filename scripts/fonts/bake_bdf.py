#!/usr/bin/env python3
"""Bake an X11 BDF bitmap font into a C source + header pair for libgl.

Run offline, once, and commit the generated .c/.h alongside libgl sources.
The build's `wildcard *.c` picks up the .c automatically; no Makefile or
runtime BDF parser needed.

This targets the authentic Adobe X11 bitmaps (e.g. helvO14.bdf from
freedesktop/xorg-font-adobe-75dpi) so the menu text can be pixel-exact to
the historic SGI/X11 look. Only ASCII (and optionally Latin-1) glyphs are
needed for menus; by default we bake encodings 32..126.

Usage:
    bake_bdf.py helvO14.bdf
    bake_bdf.py helvO14.bdf --name helv_o_14 --outdir libs/libgl
    bake_bdf.py helvO14.bdf --first 32 --last 255

Emits (in --outdir, default = input's dir):
    <name>.c  : the glyph table + packed 1bpp bitmap blob + font metrics
    <name>.h  : the BdfFont/BdfGlyph structs and an `extern const BdfFont <name>;`

The on-disk BDF bitmap rows are already MSB-first and padded to whole
bytes per row -- exactly what libgl's rasterizer_bitmap() consumes -- so the
packed bytes are copied through unchanged.
"""

import argparse
import os
import re
import sys


def sanitize(filename: str) -> str:
    """Turn a filename into a valid C identifier."""
    name = re.sub(r'[^A-Za-z0-9_]', '_', filename)
    if name and name[0].isdigit():
        name = '_' + name
    return name


class Glyph:
    __slots__ = ("encoding", "dwidth", "bbx_w", "bbx_h", "bbx_xoff",
                 "bbx_yoff", "rows")

    def __init__(self):
        self.encoding = -1
        self.dwidth = 0
        self.bbx_w = self.bbx_h = self.bbx_xoff = self.bbx_yoff = 0
        self.rows = []  # list of int, one per scanline, MSB-first


def parse_bdf(path, first, last):
    font_ascent = None
    font_descent = None
    glyphs = []

    with open(path, "r", encoding="latin-1") as f:
        cur = None
        in_bitmap = False
        for raw in f:
            line = raw.strip()
            if not line:
                continue
            tok = line.split()
            kw = tok[0]

            if in_bitmap:
                if kw == "ENDCHAR":
                    in_bitmap = False
                    if cur and first <= cur.encoding <= last:
                        glyphs.append(cur)
                    cur = None
                else:
                    # A row of hex; keep as integer (value already left-
                    # aligned/MSB-first within ceil(w/8) bytes).
                    cur.rows.append(int(line, 16))
                continue

            if kw == "FONT_ASCENT":
                font_ascent = int(tok[1])
            elif kw == "FONT_DESCENT":
                font_descent = int(tok[1])
            elif kw == "STARTCHAR":
                cur = Glyph()
            elif kw == "ENCODING":
                if cur is not None:
                    cur.encoding = int(tok[1])
            elif kw == "DWIDTH":
                if cur is not None:
                    cur.dwidth = int(tok[1])  # x advance
            elif kw == "BBX":
                if cur is not None:
                    cur.bbx_w = int(tok[1])
                    cur.bbx_h = int(tok[2])
                    cur.bbx_xoff = int(tok[3])
                    cur.bbx_yoff = int(tok[4])
            elif kw == "BITMAP":
                in_bitmap = True

    if font_ascent is None or font_descent is None:
        raise ValueError("BDF missing FONT_ASCENT/FONT_DESCENT properties")

    glyphs.sort(key=lambda g: g.encoding)
    return font_ascent, font_descent, glyphs


def pack_bitmap_bytes(g):
    """Return the glyph's bitmap as a flat list of bytes, ceil(w/8) per row,
    MSB-first -- matching rasterizer_bitmap's expectation."""
    rowbytes = (g.bbx_w + 7) // 8
    out = []
    for r in g.rows:
        # r is the integer for this row; it occupies rowbytes bytes,
        # MSB-first. BDF rows are already padded to whole bytes.
        for byteidx in range(rowbytes):
            shift = (rowbytes - 1 - byteidx) * 8
            out.append((r >> shift) & 0xFF)
    return out, rowbytes


def emit(name, ascent, descent, glyphs, src_filename):
    # Build the packed bitmap blob and per-glyph offsets into it.
    blob = []
    recs = []  # (encoding, w, h, xoff, yoff, advance, rowbytes, bitmap_offset)
    for g in glyphs:
        data, rowbytes = pack_bitmap_bytes(g)
        offset = len(blob)
        blob.extend(data)
        recs.append((g.encoding, g.bbx_w, g.bbx_h, g.bbx_xoff, g.bbx_yoff,
                     g.dwidth, rowbytes, offset))

    min_enc = recs[0][0] if recs else 0
    max_enc = recs[-1][0] if recs else 0

    h = []
    guard = f"__{name.upper()}_H__"
    h.append(f"// Auto-generated from {src_filename} by bake_bdf.py.")
    h.append(f"#ifndef {guard}")
    h.append(f"#define {guard}")
    h.append("")
    h.append("#include <stdint.h>")
    h.append("")
    h.append("// Struct layout shared with bdffont.h; guarded so either header")
    h.append("// may be included first.")
    h.append("#ifndef BDF_STRUCTS_DEFINED")
    h.append("#define BDF_STRUCTS_DEFINED")
    h.append("// One glyph's metrics + a slice into the font's bitmap blob.")
    h.append("// width/height/xoff/yoff are the BDF BBX; advance is DWIDTH x;")
    h.append("// rowbytes is ceil(width/8); bits points at MSB-first rows.")
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
    c.append(f"// Auto-generated from {src_filename} by bake_bdf.py.")
    c.append("// Committed as static source data (not a build product);")
    c.append("// regenerate only if the source BDF changes.")
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
    c.append(f"    {min_enc}, {max_enc},")
    c.append(f"    {len(recs)},")
    c.append(f"    {name}_glyphs,")
    c.append(f"    {name}_blob,")
    c.append("};")
    body = "\n".join(c) + "\n"
    return header, body


def main():
    ap = argparse.ArgumentParser(description="Bake a BDF font into C.")
    ap.add_argument("input", help="BDF file (e.g. helvO14.bdf)")
    ap.add_argument("--name", help="C identifier (default: sanitized filename)")
    ap.add_argument("--outdir", help="output dir (default: input's dir)")
    ap.add_argument("--first", type=int, default=32, help="first encoding (default 32)")
    ap.add_argument("--last", type=int, default=126, help="last encoding (default 126)")
    args = ap.parse_args()

    if not os.path.isfile(args.input):
        print(f"error: no such file: {args.input}", file=sys.stderr)
        return 1

    src_filename = os.path.basename(args.input)
    name = args.name or sanitize(src_filename)
    outdir = args.outdir or (os.path.dirname(args.input) or ".")

    ascent, descent, glyphs = parse_bdf(args.input, args.first, args.last)
    if not glyphs:
        print(f"error: no glyphs in range {args.first}..{args.last}", file=sys.stderr)
        return 1

    header, body = emit(name, ascent, descent, glyphs, src_filename)
    open(os.path.join(outdir, f"{name}.h"), "w").write(header)
    open(os.path.join(outdir, f"{name}.c"), "w").write(body)

    print(f"wrote {name}.c / {name}.h: {len(glyphs)} glyphs, "
          f"ascent={ascent} descent={descent}, "
          f"encodings {glyphs[0].encoding}..{glyphs[-1].encoding}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
