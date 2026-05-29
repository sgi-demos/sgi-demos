#ifndef __TEXFONT_H__
#define __TEXFONT_H__

// Loads SGI/GLUT TexFont (.txf) files and renders strings into the libgl
// software framebuffer via rasterizer_alpha_blit.
//
// This is a fork of Mark Kilgard's GLUT TexFont:
//   https://github.com/markkilgard/glut/tree/master/progs/texfont
//   https://web.archive.org/web/20010616211947/http://reality.sgi.com/opengl/tips/TexFont/TexFont.html
//
// The GL/texture-atlas rendering path from the original has been has been
// replaced with software rendering through libgl's rasterizer (see
// rasterizer_alpha_blit in rasterizer.h).
#include <stddef.h>        // size_t
#include "basic_types.h"
#include "rasterizer.h"   // screen_vertex

// On-disk per-glyph record. The file format guarantees this is exactly 12
// bytes; the on-disk fields are read directly into an array of these. Do
// NOT add fields or reorder; load relies on sizeof(TexGlyphInfo) == 12.
typedef struct {
    short         c;        // Unicode code point of glyph
    unsigned char width;    // glyph width in pixels
    unsigned char height;   // glyph height in pixels
    signed char   xoffset;  // pen-relative x offset of glyph origin
    signed char   yoffset;  // pen-relative y offset of glyph origin
    signed char   advance;  // pen advance after drawing this glyph
    char          _dummy;   // padding to 12 bytes
    short         x;        // top-left x in atlas
    short         y;        // top-left y in atlas
} TexGlyphInfo;

typedef struct {
    int           tex_width;     // atlas pixel width
    int           tex_height;    // atlas pixel height
    int           max_ascent;
    int           max_descent;
    int           num_glyphs;
    int           min_glyph;     // smallest glyph code in this font
    int           range;         // largest code - smallest code + 1; size of lut
    unsigned char *teximage;     // 8bpp grayscale alpha, row-major, tex_width * tex_height bytes
    TexGlyphInfo  *tgi;          // num_glyphs entries
    TexGlyphInfo **lut;          // range entries; lut[c - min_glyph] -> &tgi[i] or NULL
} TexFont;

// Load a .txf file. Returns NULL on failure; call txf_error_string() to get
// a human-readable reason. The returned pointer must be released with
// txf_unload_font().
TexFont *txf_load_font(const char *filename);

// Load a .txf from an in-memory buffer (e.g. a font baked into the binary
// via xxd -i). Same return contract as txf_load_font()
TexFont *txf_load_font_mem(const unsigned char *data, size_t len);

// Free all memory owned by a TexFont. Safe to call with NULL.
void txf_unload_font(TexFont *txf);

// Returns a static string describing the last txf_load_font() failure, or
// NULL if no failure has been recorded. Not thread-safe.
const char *txf_error_string(void);

// Compute the width in pixels of `str` rendered with `txf`. *width is the
// total horizontal pen advance; *max_ascent and *max_descent are copied
// from the font as a whole. Any of the out-pointers may be NULL.
void txf_string_metrics(TexFont *txf, const char *str,
                        int *width, int *max_ascent, int *max_descent);

// Render `str` with `txf` at screen position `sv`, using RGB color (r, g, b).
// Each glyph is blitted via rasterizer_alpha_blit. sv is interpreted in the
// same fixed-point convention used by the rest of the rasterizer (see
// screen_vertex_set_position()). Edge antialiasing follows the rasterizer's
// text_antialias_enabled flag.
void txf_render_string(TexFont *txf, screen_vertex *sv,
                       uint8_t r, uint8_t g, uint8_t b,
                       const char *str);

#endif /* __TEXFONT_H__ */
