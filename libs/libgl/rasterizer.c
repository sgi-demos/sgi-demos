//
// Rasterizer dispatch — dual rendering modes
//
// Selects between the two rasterizer implementations at startup:
//   - gles: GPU rasterizer on OpenGL ES2, ES3 where available
//           (gles2_rasterizer.c) — DEFAULT
//   - ref:  CPU scanline rasterizer from the Alice 4 project
//           (reference_rasterizer.c), kept for reference/debugging
//           (CPU-rasterizing large framebuffers is slow now that the
//           framebuffer tracks the window size)
//
// IRISGL_RAST=ref selects the CPU reference rasterizer (on the web, ?rast=ref:
// demos/switches.js passes URL switches in as environment variables). Any
// other value is the default, so a typo or an old ?rast=gles2 link still gets
// the GPU rasterizer.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include "rasterizer.h"
#include "sdl_framebuffer.h"

static const rasterizer_funcs *rast_funcs = NULL;

static const char* rasterizer_mode(void)
{
    const char *mode = getenv("IRISGL_RAST");
    return mode ? mode : "gles";
}

static const rasterizer_funcs* rast(void)
{
    if (rast_funcs == NULL)
    {
        // Both rasterizers display through the same GL texture-quad present
        // path (sdl_framebuffer.c); this only selects who produces the pixels.
        const char *mode = rasterizer_mode();
        if (strcmp(mode, "ref") == 0)
        {
            rast_funcs = ref_rasterizer_get_funcs();
            printf("INFO: rasterizer: ref (CPU)\n");
        }
        else
        {
            rast_funcs = gles2_rasterizer_get_funcs();
            printf("INFO: rasterizer: gles (GPU)\n");
        }
    }
    return rast_funcs;
}

int32_t rasterizer_winopen(char *title)                 { return rast()->winopen(title); }
void rasterizer_rgbmode(int enable)                     { rast()->rgbmode(enable); }
void rasterizer_clear(uint8_t r, uint8_t g, uint8_t b, short color_index) { rast()->clear(r, g, b, color_index); }
void rasterizer_zclear(uint32_t z)                      { rast()->zclear(z); }
void rasterizer_zclear_rect(uint32_t z, int32_t x0, int32_t y0, int32_t x1, int32_t y1) { rast()->zclear_rect(z, x0, y0, x1, y1); }
void rasterizer_czclear(uint8_t r, uint8_t g, uint8_t b, short color_index, uint32_t z) { rast()->czclear(r, g, b, color_index, z); }
void rasterizer_swap()                                  { rast()->swap(); }
void rasterizer_copy_front_to_back()                    { rast()->copy_front_to_back(); }
void rasterizer_copy_back_to_front()                    { rast()->copy_back_to_front(); }
unsigned char* rasterizer_frontbuffer()                 { return rast()->frontbuffer(); }
void rasterizer_draw(uint32_t type, uint32_t count, screen_vertex *v) { rast()->draw(type, count, v); }
void rasterizer_bitmap(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *bits) { rast()->bitmap(width, rowbytes, height, sv, bits); }
void rasterizer_alpha_blit(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *alpha, uint8_t r, uint8_t g, uint8_t b) { rast()->alpha_blit(width, rowbytes, height, sv, alpha, r, g, b); }
void rasterizer_masked_clear(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint16_t wm, uint16_t clear_index, uint8_t colormap[][3], uint32_t n, const uint32_t *rgb_from, const uint32_t *rgb_to) { rast()->masked_clear(x0, y0, x1, y1, wm, clear_index, colormap, n, rgb_from, rgb_to); }
void rasterizer_writemask(uint16_t wm, uint8_t colormap[][3]) { rast()->writemask(wm, colormap); }
void rasterizer_setpattern(uint16_t pattern[16])        { rast()->setpattern(pattern); }
void rasterizer_pattern(int enable)                     { rast()->pattern(enable); }
void rasterizer_scissor(int enable, int32_t x0, int32_t y0, int32_t x1, int32_t y1) { rast()->scissor(enable, x0, y0, x1, y1); }
void rasterizer_layer(int layer)                        { rast()->layer(layer); }
void rasterizer_cbuffer_draw(int enable_front, int enable_back) { rast()->cbuffer_draw(enable_front, enable_back); }
void rasterizer_zbuffer(int enable)                     { rast()->zbuffer(enable); }
void rasterizer_blend(int enable)                       { rast()->blend(enable); }
void rasterizer_teximage(int width, int height, const uint8_t *rgb, int bilinear) { rast()->teximage(width, height, rgb, bilinear); }
void rasterizer_texture(int enable)                     { rast()->texture(enable); }
void rasterizer_zwrite(int enable)                      { rast()->zwrite(enable); }
void rasterizer_colormask(int enable)                   { rast()->colormask(enable); }
void rasterizer_linewidth(float w)                      { rast()->linewidth(w); }
void rasterizer_frame_sync(void)                        { rast()->frame_sync(); }
void rasterizer_resize(uint32_t width, uint32_t height) { rast()->resize(width, height); }
unsigned short* rasterizer_ci_frontbuffer(void)         { return rast()->ci_frontbuffer(); }
void rasterizer_resolve_ci_to_rgb(uint8_t colormap[][3]) { rast()->resolve_ci_to_rgb(colormap); }
