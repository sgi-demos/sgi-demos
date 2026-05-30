// Auto-generated from helvBO14.bdf by bake_bdf.py.
#ifndef __HELVBO14_BDF_H__
#define __HELVBO14_BDF_H__

#include <stdint.h>

// Struct layout shared with bdffont.h; guarded so either header
// may be included first.
#ifndef BDF_STRUCTS_DEFINED
#define BDF_STRUCTS_DEFINED
// One glyph's metrics + a slice into the font's bitmap blob.
// width/height/xoff/yoff are the BDF BBX; advance is DWIDTH x;
// rowbytes is ceil(width/8); bits points at MSB-first rows.
typedef struct {
    int16_t encoding;
    uint8_t width, height;
    int8_t  xoff, yoff;
    int8_t  advance;
    uint8_t rowbytes;
    uint32_t bitmap_offset;
} BdfGlyph;

typedef struct {
    int16_t ascent, descent;
    int16_t min_encoding, max_encoding;
    int16_t num_glyphs;
    const BdfGlyph *glyphs;       // num_glyphs, sorted by encoding
    const uint8_t  *bitmap_blob;  // all glyph rows concatenated
} BdfFont;
#endif /* BDF_STRUCTS_DEFINED */

extern const BdfFont helvBO14_bdf;

#endif /* __HELVBO14_BDF_H__ */
