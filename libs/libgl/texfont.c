#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "texfont.h"

// On-disk magic, format codes, and field width assumptions follow Kilgard.
#define TXF_FORMAT_BYTE   0
#define TXF_FORMAT_BITMAP 1

static const char *last_error;

const char *txf_error_string(void) {
    return last_error;
}

// --- byte swapping for cross-endian .txf files -------------------------

static void byte_swap_32(void *p) {
    unsigned char *b = (unsigned char *)p;
    unsigned char t;
    t = b[0]; b[0] = b[3]; b[3] = t;
    t = b[1]; b[1] = b[2]; b[2] = t;
}

static void byte_swap_16(void *p) {
    unsigned char *b = (unsigned char *)p;
    unsigned char t = b[0]; b[0] = b[1]; b[1] = t;
}

// --- glyph lookup, with case fallback ----------------------------------

static TexGlyphInfo *find_glyph(TexFont *txf, int c) {
    if (c >= txf->min_glyph && c < txf->min_glyph + txf->range) {
        TexGlyphInfo *g = txf->lut[c - txf->min_glyph];
        if (g) return g;

        // Try opposite case if requested case isn't available.
        if (islower(c)) {
            int u = toupper(c);
            if (u >= txf->min_glyph && u < txf->min_glyph + txf->range)
                return txf->lut[u - txf->min_glyph];
        } else if (isupper(c)) {
            int l = tolower(c);
            if (l >= txf->min_glyph && l < txf->min_glyph + txf->range)
                return txf->lut[l - txf->min_glyph];
        }
    }
    fprintf(stderr, "texfont: unavailable glyph '%c' (%d)\n",
            isprint(c) ? c : '?', c);
    return NULL;
}

// --- load --------------------------------------------------------------

// Parse a .txf from an already-open stream. Does not fopen or fclose
// `file`; the caller owns the stream's lifecycle. Returns NULL on failure
// (with last_error set). Shared by txf_load_font (file path) and
// txf_load_font_mem (in-memory buffer via fmemopen).
static TexFont *txf_load_from_stream(FILE *file) {
    // _Static_assert lives in the header concept but is cleaner here next
    // to the fread() that depends on it.
    _Static_assert(sizeof(TexGlyphInfo) == 12,
                   "TexGlyphInfo must be 12 bytes to match .txf file format");

    TexFont *txf = NULL;
    unsigned char *texbitmap = NULL;

    txf = (TexFont *)calloc(1, sizeof(TexFont));
    if (!txf) {
        last_error = "txf: out of memory";
        goto fail;
    }

    // Magic: must start with 0xFF 't' 'x' 'f'.
    char fileid[4];
    if (fread(fileid, 1, 4, file) != 4 ||
        memcmp(fileid, "\377txf", 4) != 0) {
        last_error = "txf: not a texture font file";
        goto fail;
    }

    // Endianness marker.
    int endian_marker;
    if (fread(&endian_marker, sizeof(int), 1, file) != 1) {
        last_error = "txf: premature EOF (endianness)";
        goto fail;
    }
    int swap;
    if (endian_marker == 0x12345678) swap = 0;
    else if (endian_marker == 0x78563412) swap = 1;
    else {
        last_error = "txf: bad endianness marker";
        goto fail;
    }

    // Header fields.
    int format;
    if (fread(&format, sizeof(int), 1, file) != 1 ||
        fread(&txf->tex_width, sizeof(int), 1, file) != 1 ||
        fread(&txf->tex_height, sizeof(int), 1, file) != 1 ||
        fread(&txf->max_ascent, sizeof(int), 1, file) != 1 ||
        fread(&txf->max_descent, sizeof(int), 1, file) != 1 ||
        fread(&txf->num_glyphs, sizeof(int), 1, file) != 1) {
        last_error = "txf: premature EOF (header)";
        goto fail;
    }
    if (swap) {
        byte_swap_32(&format);
        byte_swap_32(&txf->tex_width);
        byte_swap_32(&txf->tex_height);
        byte_swap_32(&txf->max_ascent);
        byte_swap_32(&txf->max_descent);
        byte_swap_32(&txf->num_glyphs);
    }

    if (txf->num_glyphs <= 0 || txf->tex_width <= 0 || txf->tex_height <= 0) {
        last_error = "txf: invalid header values";
        goto fail;
    }

    // Glyph table.
    txf->tgi = (TexGlyphInfo *)malloc(sizeof(TexGlyphInfo) * txf->num_glyphs);
    if (!txf->tgi) {
        last_error = "txf: out of memory (glyph table)";
        goto fail;
    }
    if ((int)fread(txf->tgi, sizeof(TexGlyphInfo), txf->num_glyphs, file)
        != txf->num_glyphs) {
        last_error = "txf: premature EOF (glyph table)";
        goto fail;
    }
    if (swap) {
        for (int i = 0; i < txf->num_glyphs; i++) {
            byte_swap_16(&txf->tgi[i].c);
            byte_swap_16(&txf->tgi[i].x);
            byte_swap_16(&txf->tgi[i].y);
        }
    }

    // Compute min_glyph and range, then build the lookup table.
    int min_g = txf->tgi[0].c;
    int max_g = min_g;
    for (int i = 1; i < txf->num_glyphs; i++) {
        if (txf->tgi[i].c < min_g) min_g = txf->tgi[i].c;
        if (txf->tgi[i].c > max_g) max_g = txf->tgi[i].c;
    }
    txf->min_glyph = min_g;
    txf->range = max_g - min_g + 1;

    txf->lut = (TexGlyphInfo **)calloc(txf->range, sizeof(TexGlyphInfo *));
    if (!txf->lut) {
        last_error = "txf: out of memory (lut)";
        goto fail;
    }
    for (int i = 0; i < txf->num_glyphs; i++)
        txf->lut[txf->tgi[i].c - txf->min_glyph] = &txf->tgi[i];

    // Atlas image. Two storage formats on disk; we always end up with an
    // 8bpp grayscale buffer in memory (one byte per pixel, 0 or 255 for
    // the bitmap format, 0..255 for the byte format).
    int npixels = txf->tex_width * txf->tex_height;
    txf->teximage = (unsigned char *)malloc(npixels);
    if (!txf->teximage) {
        last_error = "txf: out of memory (atlas)";
        goto fail;
    }

    switch (format) {
        case TXF_FORMAT_BYTE: {
            if ((int)fread(txf->teximage, 1, npixels, file) != npixels) {
                last_error = "txf: premature EOF (byte atlas)";
                goto fail;
            }
            break;
        }
        case TXF_FORMAT_BITMAP: {
            int stride = (txf->tex_width + 7) >> 3;
            int packed_bytes = stride * txf->tex_height;
            texbitmap = (unsigned char *)malloc(packed_bytes);
            if (!texbitmap) {
                last_error = "txf: out of memory (bitmap atlas)";
                goto fail;
            }
            if (fread(texbitmap, 1, packed_bytes, file) != (size_t)packed_bytes) {
                last_error = "txf: premature EOF (bitmap atlas)";
                goto fail;
            }
            // Expand 1bpp to 8bpp: bit set -> 255, bit clear -> 0.
            for (int j = 0; j < txf->tex_height; j++) {
                for (int i = 0; i < txf->tex_width; i++) {
                    int set = (texbitmap[j * stride + (i >> 3)] >> (i & 7)) & 1;
                    txf->teximage[j * txf->tex_width + i] = set ? 255 : 0;
                }
            }
            free(texbitmap);
            texbitmap = NULL;
            break;
        }
        default:
            last_error = "txf: unknown atlas format";
            goto fail;
    }

    last_error = NULL;
    return txf;

fail:
    if (texbitmap) free(texbitmap);
    txf_unload_font(txf);
    return NULL;
}

// Load a .txf from a file path.
TexFont *txf_load_font(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        last_error = "txf: file open failed";
        return NULL;
    }
    TexFont *txf = txf_load_from_stream(file);
    fclose(file);
    return txf;
}

// Load a .txf from an in-memory buffer (e.g. a font baked into the binary
// via xxd -i). Uses fmemopen so the existing stream parser is reused
// unchanged. `data` must remain valid only for the duration of this call.
TexFont *txf_load_font_mem(const unsigned char *data, size_t len) {
    FILE *file = fmemopen((void *)data, len, "rb");
    if (!file) {
        last_error = "txf: fmemopen failed";
        return NULL;
    }
    TexFont *txf = txf_load_from_stream(file);
    fclose(file);

    // // TEMP: dump atlas coverage for 'o' (good) and 'c' (high) — remove after.
    // {
    //     int chars[] = {'o', 'c'};
    //     for (int ci = 0; ci < 2; ci++) {
    //         TexGlyphInfo *g = find_glyph(txf, chars[ci]);
    //         if (!g) continue;
    //         fprintf(stderr, "=== '%c' atlas_y=%d height=%d width=%d ===\n",
    //                 chars[ci], g->y, g->height, g->width);
    //         for (int row = 0; row < g->height; row++) {
    //             for (int col = 0; col < g->width; col++) {
    //                 unsigned char a =
    //                     txf->teximage[(g->y + row) * txf->tex_width + (g->x + col)];
    //                 fputc(a > 128 ? '#' : (a > 32 ? '.' : ' '), stderr);
    //             }
    //             fputc('\n', stderr);
    //         }
    //     }
    // }

    return txf;
}

// --- unload ------------------------------------------------------------

void txf_unload_font(TexFont *txf) {
    if (!txf) return;
    free(txf->teximage);
    free(txf->tgi);
    free(txf->lut);
    free(txf);
}

// --- string metrics ----------------------------------------------------

void txf_string_metrics(TexFont *txf, const char *str,
                        int *width, int *max_ascent, int *max_descent) {
    int w = 0;
    for (const char *p = str; *p; p++) {
        TexGlyphInfo *g = find_glyph(txf, (unsigned char)*p);
        if (g) w += g->advance;
    }
    if (width)       *width       = w;
    if (max_ascent)  *max_ascent  = txf->max_ascent;
    if (max_descent) *max_descent = txf->max_descent;
}

// --- render ------------------------------------------------------------

// Per-glyph baseline nudge in fixed-point units (SCREEN_VERTEX_V2_SCALE = 1px).
// Round-bottomed glyphs lack atlas overshoot, so push them down a fraction
// of a pixel to sit optically on the baseline. Tuned by eye for this font.
static int txf_glyph_ynudge(int c) {
    switch (c) {
        case 'c': return SCREEN_VERTEX_V2_SCALE / 2;
        case 'e': return SCREEN_VERTEX_V2_SCALE / 2;
        case 'b': return SCREEN_VERTEX_V2_SCALE - 4;
        default:  return 0;
    }
}

void txf_render_string(TexFont *txf, screen_vertex *sv,
                       uint8_t r, uint8_t g, uint8_t b,
                       const char *str) {
    if (!txf || !sv || !str) return;

    // Pen position, in the screen_vertex fixed-point convention.
    screen_vertex pen = *sv;
    // fprintf(stderr, "txf: pen.y=%d base_y(px)=%d first buffer_y=%d DH=%d\n",
    //         sv->y, sv->y / SCREEN_VERTEX_V2_SCALE,
    //         480 - 1 - (sv->y / SCREEN_VERTEX_V2_SCALE), 480);

    for (const char *p = str; *p; p++) {
        TexGlyphInfo *gi = find_glyph(txf, (unsigned char)*p);
        if (!gi) continue;

        // Place the glyph's top-left at pen + (xoffset, yoffset). Note
        // yoffset is the bearing below the baseline (negative for most
        // glyphs), measured in pixels.
        int ynudge = txf_glyph_ynudge((unsigned char)*p);
        screen_vertex glyph_sv = pen;
        glyph_sv.x = pen.x + gi->xoffset * SCREEN_VERTEX_V2_SCALE;
        glyph_sv.y = pen.y - (gi->yoffset + gi->height) * SCREEN_VERTEX_V2_SCALE + ynudge;

        // Source pointer into the atlas at this glyph's top-left.
        uint8_t *src = txf->teximage + (int)gi->y * txf->tex_width + (int)gi->x;

        rasterizer_alpha_blit(gi->width, txf->tex_width, gi->height,
                              &glyph_sv, src, r, g, b);

        // Advance pen.
        pen.x += gi->advance * SCREEN_VERTEX_V2_SCALE;
    }
}
