//
// Rasterizer dispatch — dual rendering modes
//
// Selects between the two rasterizer implementations at startup:
//   - gles2:     GPU rasterizer on OpenGL ES2  (gles2_rasterizer.c) — DEFAULT
//   - reference: CPU scanline rasterizer  (reference_rasterizer.c), kept for
//                reference/debugging (CPU-rasterizing large framebuffers is
//                slow now that the framebuffer tracks the window size)
//
// Native: set GLES2_RASTERIZER=ref to select the CPU reference rasterizer.
// Web:    add ?rast=ref to the URL (or set GLES2_RASTERIZER in Module ENV).
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include "rasterizer.h"
#include "sdl_framebuffer.h"

static const rasterizer_funcs *rast_funcs = NULL;

// Shim-preferred mode (per-demo quirks in gl.c — e.g. cedit needs the
// reference rasterizer's color-index buffer). Weaker than an explicit
// GLES2_RASTERIZER env or ?rast= URL choice; must be set before the first
// rasterizer_* call locks the selection in.
static const char *preferred_mode = NULL;

void rasterizer_prefer(const char *mode)
{
    preferred_mode = mode;
}

static const char* rasterizer_mode(void)
{
    const char *mode = getenv("GLES2_RASTERIZER");

#ifdef __EMSCRIPTEN__
    // Allow ?rast=gles2 / ?rast=ref in the page URL to override
    int url_mode = EM_ASM_INT({
        var q = (typeof window !== 'undefined' && window.location) ? window.location.search : "";
        if (q.indexOf('rast=gles2') >= 0) return 2;
        if (q.indexOf('rast=ref') >= 0) return 1;
        return 0;
    });
    if (url_mode == 2) mode = "gles2";
    else if (url_mode == 1) mode = "ref";
#endif

    // The legacy SDL-renderer display path creates no GL context, which the
    // gles2 rasterizer requires; force the CPU reference rasterizer there
    if (getenv("SGI_SDL_FRAMEBUFFER") != NULL)
        mode = "ref";

    if (mode == NULL)
        mode = preferred_mode;

    return mode ? mode : "gles2";
}

static const rasterizer_funcs* rast(void)
{
    if (rast_funcs == NULL)
    {
        // Both rasterizers display through the same GL texture-quad present
        // path (sdl_framebuffer.c); this only selects who produces the pixels.
        const char *mode = rasterizer_mode();
        if (strcmp(mode, "gles2") == 0)
        {
            rast_funcs = gles2_rasterizer_get_funcs();
            printf("INFO: rasterizer: gles2 (GPU)\n");
        }
        else
        {
            rast_funcs = ref_rasterizer_get_funcs();
            printf("INFO: rasterizer: reference (CPU)\n");
        }
    }
    return rast_funcs;
}

int32_t rasterizer_winopen(char *title)                 { return rast()->winopen(title); }
void rasterizer_rgbmode(int enable)                     { rast()->rgbmode(enable); }
void rasterizer_clear(uint8_t r, uint8_t g, uint8_t b, short color_index) { rast()->clear(r, g, b, color_index); }
void rasterizer_zclear(uint32_t z)                      { rast()->zclear(z); }
void rasterizer_czclear(uint8_t r, uint8_t g, uint8_t b, short color_index, uint32_t z) { rast()->czclear(r, g, b, color_index, z); }
void rasterizer_swap()                                  { rast()->swap(); }
void rasterizer_copy_front_to_back()                    { rast()->copy_front_to_back(); }
void rasterizer_copy_back_to_front()                    { rast()->copy_back_to_front(); }
unsigned char* rasterizer_frontbuffer()                 { return rast()->frontbuffer(); }
void rasterizer_draw(uint32_t type, uint32_t count, screen_vertex *v) { rast()->draw(type, count, v); }
void rasterizer_bitmap(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *bits) { rast()->bitmap(width, rowbytes, height, sv, bits); }
void rasterizer_alpha_blit(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *alpha, uint8_t r, uint8_t g, uint8_t b) { rast()->alpha_blit(width, rowbytes, height, sv, alpha, r, g, b); }
void rasterizer_setpattern(uint16_t pattern[16])        { rast()->setpattern(pattern); }
void rasterizer_pattern(int enable)                     { rast()->pattern(enable); }
void rasterizer_cbuffer_draw(int enable_front, int enable_back) { rast()->cbuffer_draw(enable_front, enable_back); }
void rasterizer_zbuffer(int enable)                     { rast()->zbuffer(enable); }
void rasterizer_linewidth(float w)                      { rast()->linewidth(w); }
void rasterizer_frame_sync(void)                        { rast()->frame_sync(); }
void rasterizer_resize(uint32_t width, uint32_t height) { rast()->resize(width, height); }
unsigned short* rasterizer_ci_frontbuffer(void)         { return rast()->ci_frontbuffer(); }
void rasterizer_resolve_ci_to_rgb(uint8_t colormap[][3]) { rast()->resolve_ci_to_rgb(colormap); }
