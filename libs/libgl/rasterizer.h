#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include "basic_types.h"

#define DRAW_TRIANGLES 0
#define DRAW_LINES 1
#define DRAW_POINTS 2

int32_t rasterizer_winopen(char *title);
void rasterizer_rgbmode(int enable);
void rasterizer_clear(uint8_t r, uint8_t g, uint8_t b, short color_index);
void rasterizer_zclear(uint32_t z);
// Viewport-scoped depth clear (IRIS zclear only clears the viewport): set z
// across the inclusive screen rect (y up) only. flight 3.4 depends on this —
// its per-frame scene zclear must not wipe the instrument panel's plate z,
// which occludes the horizon ball inside its bezel.
void rasterizer_zclear_rect(uint32_t z, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void rasterizer_czclear(uint8_t r, uint8_t g, uint8_t b, short color_index, uint32_t z);
void rasterizer_swap();
void rasterizer_copy_front_to_back();
void rasterizer_copy_back_to_front();

unsigned char* rasterizer_frontbuffer();
void rasterizer_draw(uint32_t type, uint32_t count, screen_vertex *v); // count is the number of primitives.
void rasterizer_bitmap(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *bits);
void rasterizer_alpha_blit(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *alpha, uint8_t r, uint8_t g, uint8_t b);
// Colormap-plane masked clear (IRIS writemask): every pixel in the
// inclusive screen rect (y up) takes the index (oldIndex & ~wm) |
// (clear_index & wm). The reference rasterizer applies that math exactly
// through its per-pixel CI buffer, resolving RGB through colormap[]. The
// gles2 rasterizer has no CI buffer and approximates by RGB matching:
// recolor pixels matching rgb_from[n] to rgb_to[n] (pairs precomputed by
// gl.c from the same index math over the mapcolor'd palette). Applies to
// whichever of front/back drawing is enabled; never touches z.
void rasterizer_masked_clear(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                             uint16_t wm, uint16_t clear_index, uint8_t colormap[][3],
                             uint32_t n, const uint32_t *rgb_from, const uint32_t *rgb_to);
// Per-draw IRIS writemask (CI mode): while wm is partial, every drawn pixel's
// index becomes (oldIndex & ~wm) | (drawnIndex & wm), RGB re-resolved through
// colormap[] — so art protected in the masked-off planes shows through new
// primitives (flight 1988 draws its meter bars and compass needle this way
// over scale art living in planes 0-1). colormap points at the GL layer's
// live palette; the reference rasterizer composites exactly through its CI
// buffer. The gles2 rasterizer has no CI buffer and ignores this — masked
// draws there keep their flat color (a known approximation).
void rasterizer_writemask(uint16_t wm, uint8_t colormap[][3]);
void rasterizer_setpattern(uint16_t pattern[16]);
void rasterizer_pattern(int enable);
// IRIS scrmask: clip all subsequent primitive drawing to the inclusive
// screen rect (y up). Applies to draws only — the full-screen clear
// fast path is not masked (no demo clears with a partial scrmask up).
void rasterizer_scissor(int enable, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
// IRIS layer planes (drawmode): route subsequent draws to 0 = the normal
// front/back planes, 1 = the underlay layer, 2 = the overlay/pup layer.
// Layers are single-buffered RGBA side buffers with no depth; a drawn
// pixel's alpha records whether its layer index was non-zero (alpha 0 =
// transparent/erased). The display composites per pixel with the SGI
// priority: overlay where its alpha is set, else the normal planes, else
// the underlay where the normal planes are exactly black (all planes 0).
void rasterizer_layer(int layer);
void rasterizer_cbuffer_draw(int enable_front, int enable_back);
void rasterizer_zbuffer(int enable);
void rasterizer_blend(int enable);   // src-alpha / one-minus-src-alpha only (IRIS BF_SA/BF_MSA)
// One current texture (all the demos need): RGB8 image, REPEAT wrap,
// point or bilinear filtering, modulating the base color (IRIS TV_MODULATE).
void rasterizer_teximage(int width, int height, const uint8_t *rgb, int bilinear);
void rasterizer_texture(int enable);
void rasterizer_zwrite(int enable);  // depth WRITES; the z test stays per rasterizer_zbuffer
void rasterizer_linewidth(float w);
void rasterizer_frame_sync(void);

// Color-index buffer (SGI hardware palette LUT emulation, CI mode only).
//
// rasterizer_ci_frontbuffer: read accessor for the front color-index buffer
// (one uint16_t per pixel, row 0 = top, same layout as the RGB buffer). In
// CI mode the CI buffer is the source of truth; the RGB front buffer is a
// cache populated from it by rasterizer_resolve_ci_to_rgb. Used by
// readpixels()/getapixel() to read back the index under a screen position.
// Returns NULL when the rasterizer keeps no CI buffer (gles2).
unsigned short* rasterizer_ci_frontbuffer(void);

// Walk the front CI buffer and write colormap[ci] into the front RGB buffer
// for each pixel. Called by the GL layer just before presenting, when in CI
// mode and the colormap has changed. This emulates the SGI hardware palette
// LUT: a mapcolor() call is reflected on screen on the next present without
// the demo redrawing anything. No-op when there is no CI buffer (gles2).
void rasterizer_resolve_ci_to_rgb(uint8_t colormap[][3]);

// The framebuffer tracks the window size: called once after the window
// exists (with its initial size) and again on every window resize. The
// rasterizer (re)allocates its buffers at the new size; contents are
// cleared. The transition is atomic: by the time this returns, the new
// buffers are the active draw/display targets.
void rasterizer_resize(uint32_t width, uint32_t height);

//
// Dual rendering modes: the rasterizer_* API above dispatches through a
// function table to one of two implementations, selected at startup in
// rasterizer.c:
//   - gles2:     GPU rasterizer on OpenGL ES2  (gles2_rasterizer.c) — default
//   - reference: CPU scanline rasterizer  (reference_rasterizer.c) — for
//                reference/debugging (GLES2_RASTERIZER=ref / ?rast=ref)
//
typedef struct rasterizer_funcs
{
    int32_t (*winopen)(char *title);
    void (*rgbmode)(int enable);
    void (*clear)(uint8_t r, uint8_t g, uint8_t b, short color_index);
    void (*zclear)(uint32_t z);
    void (*zclear_rect)(uint32_t z, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
    void (*czclear)(uint8_t r, uint8_t g, uint8_t b, short color_index, uint32_t z);
    void (*swap)(void);
    void (*copy_front_to_back)(void);
    void (*copy_back_to_front)(void);
    unsigned char* (*frontbuffer)(void);
    void (*draw)(uint32_t type, uint32_t count, screen_vertex *v);
    void (*bitmap)(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *bits);
    void (*alpha_blit)(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *alpha, uint8_t r, uint8_t g, uint8_t b);
    void (*masked_clear)(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                         uint16_t wm, uint16_t clear_index, uint8_t colormap[][3],
                         uint32_t n, const uint32_t *rgb_from, const uint32_t *rgb_to);
    void (*writemask)(uint16_t wm, uint8_t colormap[][3]);
    void (*setpattern)(uint16_t pattern[16]);
    void (*pattern)(int enable);
    void (*scissor)(int enable, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
    void (*layer)(int layer);
    void (*cbuffer_draw)(int enable_front, int enable_back);
    void (*zbuffer)(int enable);
    void (*blend)(int enable);
    void (*teximage)(int width, int height, const uint8_t *rgb, int bilinear);
    void (*texture)(int enable);
    void (*zwrite)(int enable);
    void (*linewidth)(float w);
    void (*frame_sync)(void);
    void (*resize)(uint32_t width, uint32_t height);
    unsigned short* (*ci_frontbuffer)(void);
    void (*resolve_ci_to_rgb)(uint8_t colormap[][3]);
} rasterizer_funcs;

const rasterizer_funcs* ref_rasterizer_get_funcs(void);
const rasterizer_funcs* gles2_rasterizer_get_funcs(void);

// Set the shim-preferred implementation ("ref" or "gles2") before the first
// rasterizer_* call. Overridden by an explicit GLES2_RASTERIZER env var or
// ?rast= URL parameter. Used by per-demo quirks (gl.c) — e.g. cedit needs
// the reference rasterizer's color-index buffer.
void rasterizer_prefer(const char *mode);

#endif /* __RASTERIZER_H__ */
