// Runtime renderer for baked BDF bitmap fonts (see bake_bdf.py).
//
// This is the pixel-exact path: it draws the authentic Adobe X11 bitmap
// glyphs through libgl's 1bpp rasterizer_bitmap(), the same primitive the
// built-in fixed font uses.
#ifndef __BDFFONT_H__
#define __BDFFONT_H__

#include <stdint.h>
#include "rasterizer.h"   // screen_vertex
// The generated font header defines BdfGlyph / BdfFont. Any baked BDF
// header (e.g. helvO14.h) provides the same struct layout; we only need
// the type here, so forward-declare via a representative include is avoided
// to keep this font-agnostic. The structs are defined by the generated .h,
// so callers include that before using a specific font. To let this module
// compile standalone, the struct definitions are mirrored here under a
// guard the generated header also respects.

#ifndef BDF_STRUCTS_DEFINED
#define BDF_STRUCTS_DEFINED
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
    const BdfGlyph *glyphs;
    const uint8_t  *bitmap_blob;
} BdfFont;
#endif

// Look up a glyph by character code; returns NULL if absent.
const BdfGlyph *bdf_find_glyph(const BdfFont *font, int c);

// Total horizontal advance (in pixels) of a string.
int bdf_string_width(const BdfFont *font, const char *str);

// Render `str` with its baseline origin at the pen position carried in *sv
// Draws each glyph via rasterizer_bitmap with color taken from sv's color fields.
void bdf_render_string(const BdfFont *font, screen_vertex *sv, const char *str);

#endif /* __BDFFONT_H__ */
