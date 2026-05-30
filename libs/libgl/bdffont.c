// Runtime renderer for baked BDF bitmap fonts. See bdffont.h.

#include <stddef.h>        // NULL
#include "bdffont.h"
#include "basic_types.h"   // SCREEN_VERTEX_V2_SCALE

const BdfGlyph *bdf_find_glyph(const BdfFont *font, int c) {
    if (!font || c < font->min_encoding || c > font->max_encoding)
        return NULL;
    // Glyphs are sorted by encoding; binary search.
    int lo = 0, hi = font->num_glyphs - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int e = font->glyphs[mid].encoding;
        if (e == c) return &font->glyphs[mid];
        if (e < c) lo = mid + 1;
        else hi = mid - 1;
    }
    return NULL;
}

int bdf_string_width(const BdfFont *font, const char *str) {
    if (!font || !str) return 0;
    int w = 0;
    for (const char *p = str; *p; p++) {
        const BdfGlyph *g = bdf_find_glyph(font, (unsigned char)*p);
        if (g) w += g->advance;
    }
    return w;
}

void bdf_render_string(const BdfFont *font, screen_vertex *sv, const char *str) {
    if (!font || !sv || !str) return;

    screen_vertex pen = *sv;  // carries baseline origin + color

    for (const char *p = str; *p; p++) {
        const BdfGlyph *g = bdf_find_glyph(font, (unsigned char)*p);
        if (!g) continue;

        if (g->width > 0 && g->height > 0) {
            // BBX yoff is the offset from the baseline to the BOTTOM of the
            // glyph box (negative when the glyph descends below baseline).
            // rasterizer_bitmap places row j at sv->y + (height-1-j), i.e.
            // it builds upward from sv->y, so anchor sv->y at the glyph's
            // bottom: baseline + yoff. x anchor is pen + xoff.
            screen_vertex glyph_sv = pen;
            glyph_sv.x = pen.x + g->xoff * SCREEN_VERTEX_V2_SCALE;
            glyph_sv.y = pen.y + g->yoff * SCREEN_VERTEX_V2_SCALE;

            // const blob -> rasterizer takes non-const; it only reads.
            uint8_t *bits = (uint8_t *)(font->bitmap_blob + g->bitmap_offset);
            rasterizer_bitmap(g->width, g->rowbytes, g->height,
                              &glyph_sv, bits);
        }
        pen.x += g->advance * SCREEN_VERTEX_V2_SCALE;
    }
}
