#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>

#include <gl.h>
#include "rasterizer.h"

// Framebuffer size tracks the window (ref_rasterizer_resize); buffers are
// heap-allocated at that size. Zero until the window exists.
static int32_t DISPLAY_WIDTH = 0;
static int32_t DISPLAY_HEIGHT = 0;

// SDL wants BGRA
#define BLUE_BYTE 0
#define GREEN_BYTE 1
#define RED_BYTE 2

static int gen_ppm_frame_files = 0;
static int snap_vertices = 0;

static float the_linewidth;
static uint16_t the_pattern[16];
static int pattern_enabled = 0;
static int blend_enabled = 0;   // BF_SA/BF_MSA source-alpha blending
// current texture (REPEAT wrap, modulate)
static int texture_enabled = 0;
static int tex_width = 0, tex_height = 0, tex_bilinear = 0;
static uint8_t *tex_rgb = NULL;
static int zwrite_enabled = 1;  // depth writes (zwritemask); test is zbuffer_enabled
static int colormask_enabled = 1;  // color writes (wmpack); off = z-only draws
static int rgb_mode = 0; // color map mode by default
static int text_antialias_enabled = 1;

// double color buffers
static int backbuffer_draw_enabled = 1;
static int frontbuffer_draw_enabled = 0;
static uint8_t *c_buffer[2] = {NULL, NULL};   // BGRA, DISPLAY_WIDTH*DISPLAY_HEIGHT*4 each
static uint8_t *gl_c_backbuffer = NULL;       // render to back buffer
static uint8_t *gl_c_frontbuffer = NULL;      // display from front buffer

// double color-index buffers, written in parallel with the RGB buffers in CI
// mode. The CI front buffer is the source of truth for palette (mapcolor)
// changes: rasterizer_resolve_ci_to_rgb re-derives front RGB from it, which
// is how the SGI hardware palette LUT is emulated. One uint16_t per pixel,
// same row order as the RGB buffers (row 0 = top).
static uint16_t *ci_buffer[2] = {NULL, NULL};
static uint16_t *gl_ci_backbuffer = NULL;
static uint16_t *gl_ci_frontbuffer = NULL;

// IRIS layer planes (rasterizer_layer): single-buffered BGRA side buffers;
// a pixel's alpha byte records "layer index != 0" (0 = transparent/erased).
// Layer draws bypass the z-buffer (the hardware layers had no z). Once any
// layer is selected, presents go through display_buffer, the per-frame
// composite of overlay-over-front-over-underlay (underlay shows where the
// front pixel is exactly black — the SGI display priority); the GL layer
// picks it up through ref_rasterizer_frontbuffer at each present.
static int layer_target = 0;        // 0 = normal planes, 1 = underlay, 2 = overlay
static int layers_in_use = 0;
static uint8_t *layer_buffer[2] = {NULL, NULL};   // [0] = underlay, [1] = overlay
static uint8_t *display_buffer = NULL;
#define LAYER_ALPHA_BYTE 3

// Per-draw IRIS writemask (CI mode): while partial, drawn pixels composite
// against the CI buffer instead of overwriting it (see write_pixel). the
// colormap points at the GL layer's live palette (stable static array).
static uint16_t the_writemask = 0xffff;
static uint8_t (*the_colormap)[3] = NULL;

void ref_rasterizer_writemask(uint16_t wm, uint8_t colormap[][3])
{
    the_writemask = wm;
    the_colormap = colormap;
}

static size_t color_buffer_bytes(void) { return (size_t)DISPLAY_WIDTH * DISPLAY_HEIGHT * 4; }

// Address of pixel (x, y) in a color buffer (y is buffer row, 0 = top)
static uint8_t* buffer_pixel(uint8_t *buffer, int x, int y)
{
    return buffer + ((size_t)y * DISPLAY_WIDTH + x) * 4;
}

// z buffer — full 32-bit precision (IRIS hardware had 24-bit z; 16 bits
// visibly z-fights on flight 3.4's near=4..far=1e6 scene projection, e.g.
// the F-14 cockpit interior poking through the canopy glass)
static int zbuffer_enabled = 0;
typedef uint32_t z_t;
static const int Z_SHIFT = 0;
static const unsigned int Z_MAX = 0xffffffff;
static z_t *z_buffer = NULL; // DISPLAY_WIDTH*DISPLAY_HEIGHT, 16 bits per pixel

static float min(float a, float b)
{
    return (a < b) ? a : b;
}

static float clamp(float v, float low, float high)
{
    return v > high ? high : (v < low ? low : v);
}

static void clear_cbuffer(int draw_enabled, uint8_t *buffer, uint8_t r, uint8_t g, uint8_t b)
{
    if (draw_enabled && buffer) {
        for (int j = 0; j < DISPLAY_HEIGHT; j++)
            for (int i = 0; i < DISPLAY_WIDTH; i++) {
                uint8_t *p = buffer_pixel(buffer, i, j);
                p[RED_BYTE] = r;
                p[GREEN_BYTE] = g;
                p[BLUE_BYTE] = b;
            }
    }
}

static void clear_cibuffer(int draw_enabled, uint16_t *buffer, short color_index)
{
    if (draw_enabled && buffer) {
        size_t n = (size_t)DISPLAY_WIDTH * DISPLAY_HEIGHT;
        for (size_t i = 0; i < n; i++)
            buffer[i] = (uint16_t)color_index;
    }
}

void ref_rasterizer_clear(uint8_t r, uint8_t g, uint8_t b, short color_index)
{
    clear_cbuffer(backbuffer_draw_enabled, gl_c_backbuffer, r, g, b);
    clear_cbuffer(frontbuffer_draw_enabled, gl_c_frontbuffer, r, g, b);
    if (!rgb_mode) {
        clear_cibuffer(backbuffer_draw_enabled, gl_ci_backbuffer, color_index);
        clear_cibuffer(frontbuffer_draw_enabled, gl_ci_frontbuffer, color_index);
    }
}

// IRIS colormap-plane masked clear, exact form: every pixel's INDEX takes
// (oldIndex & ~wm) | (clear_index & wm) — index-plane arithmetic through
// the per-pixel CI buffer, RGB re-resolved through the colormap. Unlike
// the RGB-matching approximation (gles2, and the fallback below), this is
// immune to palette collisions and never strands a pixel whose RGB drifted
// off-palette. Pixels whose index is unchanged keep their RGB bytes as-is,
// so RGB-only shim overlays (popup menus, which record no CI) survive
// where the demo's writemask protects the underlying planes.
static void masked_clear_ci(int draw_enabled, uint8_t *buffer, uint16_t *cibuf,
                            int x0, int y0, int x1, int y1,
                            uint16_t wm, uint16_t clear_index, uint8_t colormap[][3])
{
    if (!draw_enabled || !buffer || !cibuf)
        return;
    for (int y = y0; y <= y1; y++) {
        int buffer_y = DISPLAY_HEIGHT - 1 - y;
        if (buffer_y < 0 || buffer_y >= DISPLAY_HEIGHT)
            continue;
        for (int x = x0; x <= x1; x++) {
            if (x < 0 || x >= DISPLAY_WIDTH)
                continue;
            // clear() honors the current pattern (flight 1988's crashed-
            // meters effect is a patterned clear through writemask(white))
            if (pattern_enabled && !(the_pattern[y % 16] & (1 << (x % 16))))
                continue;
            size_t i = (size_t)buffer_y * DISPLAY_WIDTH + x;
            uint16_t ci = cibuf[i];
            uint16_t nci = (uint16_t)(((ci & ~wm) | (clear_index & wm)) & 0xfff);
            if (nci == ci)
                continue;
            cibuf[i] = nci;
            uint8_t *p = buffer_pixel(buffer, x, buffer_y);
            p[RED_BYTE]   = colormap[nci][0];
            p[GREEN_BYTE] = colormap[nci][1];
            p[BLUE_BYTE]  = colormap[nci][2];
        }
    }
}

// RGB-matching fallback for the (shouldn't-happen) case of a masked clear
// with no CI buffers allocated: recolor pixels matching rgb_from to rgb_to.
static void masked_clear_buffer(int draw_enabled, uint8_t *buffer,
                                int x0, int y0, int x1, int y1,
                                uint32_t n, const uint32_t *rgb_from, const uint32_t *rgb_to)
{
    if (!draw_enabled || !buffer)
        return;
    for (int y = y0; y <= y1; y++) {
        int buffer_y = DISPLAY_HEIGHT - 1 - y;
        if (buffer_y < 0 || buffer_y >= DISPLAY_HEIGHT)
            continue;
        for (int x = x0; x <= x1; x++) {
            if (x < 0 || x >= DISPLAY_WIDTH)
                continue;
            if (pattern_enabled && !(the_pattern[y % 16] & (1 << (x % 16))))
                continue;
            uint8_t *p = buffer_pixel(buffer, x, buffer_y);
            uint32_t rgb = ((uint32_t)p[RED_BYTE] << 16) | ((uint32_t)p[GREEN_BYTE] << 8) | p[BLUE_BYTE];
            for (uint32_t i = 0; i < n; i++)
                if (rgb == rgb_from[i]) {
                    p[RED_BYTE]   = (rgb_to[i] >> 16) & 0xff;
                    p[GREEN_BYTE] = (rgb_to[i] >> 8) & 0xff;
                    p[BLUE_BYTE]  = rgb_to[i] & 0xff;
                    break;
                }
        }
    }
}

void ref_rasterizer_masked_clear(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                                 uint16_t wm, uint16_t clear_index, uint8_t colormap[][3],
                                 uint32_t n, const uint32_t *rgb_from, const uint32_t *rgb_to)
{
    if (gl_ci_backbuffer && gl_ci_frontbuffer) {
        masked_clear_ci(backbuffer_draw_enabled, gl_c_backbuffer, gl_ci_backbuffer,
                        x0, y0, x1, y1, wm, clear_index, colormap);
        masked_clear_ci(frontbuffer_draw_enabled, gl_c_frontbuffer, gl_ci_frontbuffer,
                        x0, y0, x1, y1, wm, clear_index, colormap);
        return;
    }
    masked_clear_buffer(backbuffer_draw_enabled, gl_c_backbuffer, x0, y0, x1, y1, n, rgb_from, rgb_to);
    masked_clear_buffer(frontbuffer_draw_enabled, gl_c_frontbuffer, x0, y0, x1, y1, n, rgb_from, rgb_to);
}

void ref_rasterizer_teximage(int width, int height, const uint8_t *rgb, int bilinear)
{
    free(tex_rgb);
    tex_rgb = (uint8_t *)malloc((size_t)width * height * 3);
    memcpy(tex_rgb, rgb, (size_t)width * height * 3);
    tex_width = width;
    tex_height = height;
    tex_bilinear = bilinear;
}

void ref_rasterizer_texture(int enable)
{
    texture_enabled = enable;
}

// sample with REPEAT wrap; point or bilinear per the bound filter
static void tex_sample(float s, float t, int *tr, int *tg, int *tb)
{
    if (!tex_rgb) { *tr = *tg = *tb = 255; return; }

    float x = s * tex_width;
    float y = t * tex_height;

    if (!tex_bilinear) {
        int xi = ((int)floorf(x)) % tex_width;  if (xi < 0) xi += tex_width;
        int yi = ((int)floorf(y)) % tex_height; if (yi < 0) yi += tex_height;
        const uint8_t *p = tex_rgb + (yi * tex_width + xi) * 3;
        *tr = p[0]; *tg = p[1]; *tb = p[2];
        return;
    }

    x -= 0.5f;
    y -= 0.5f;
    int x0 = (int)floorf(x), y0 = (int)floorf(y);
    float ax = x - x0, ay = y - y0;
    int xs[2] = { x0 % tex_width, (x0 + 1) % tex_width };
    int ys[2] = { y0 % tex_height, (y0 + 1) % tex_height };
    if (xs[0] < 0) xs[0] += tex_width;
    if (xs[1] < 0) xs[1] += tex_width;
    if (ys[0] < 0) ys[0] += tex_height;
    if (ys[1] < 0) ys[1] += tex_height;
    float acc[3] = {0, 0, 0};
    float wgt[2][2] = {{(1 - ax) * (1 - ay), ax * (1 - ay)}, {(1 - ax) * ay, ax * ay}};
    for (int j = 0; j < 2; j++)
        for (int i = 0; i < 2; i++) {
            const uint8_t *p = tex_rgb + (ys[j] * tex_width + xs[i]) * 3;
            acc[0] += p[0] * wgt[j][i];
            acc[1] += p[1] * wgt[j][i];
            acc[2] += p[2] * wgt[j][i];
        }
    *tr = (int)acc[0]; *tg = (int)acc[1]; *tb = (int)acc[2];
}

void ref_rasterizer_blend(int enable)
{
    blend_enabled = enable;
}

void ref_rasterizer_colormask(int enable)
{
    colormask_enabled = enable;
}

void ref_rasterizer_zwrite(int enable)
{
    zwrite_enabled = enable;
}

void ref_rasterizer_linewidth(float w)
{
    the_linewidth = w;
}

void ref_rasterizer_setpattern(uint16_t pattern[16])
{
    for (int i = 0; i < 16; i++) {
        the_pattern[i] = pattern[i];
    }
}

void ref_rasterizer_pattern(int enable)
{
    pattern_enabled = enable;
}

// composite the SGI layer priority into display_buffer: overlay where its
// index bit (alpha) is set, else the given front buffer, else the underlay
// where the front pixel is exactly black (all planes 0)
static void composite_layers_into_display(const uint8_t *front)
{
    if (!display_buffer || !front || !layer_buffer[0] || !layer_buffer[1])
        return;
    size_t n = (size_t)DISPLAY_WIDTH * DISPLAY_HEIGHT;
    for (size_t i = 0; i < n; i++) {
        const uint8_t *f = front + i * 4;
        const uint8_t *o = layer_buffer[1] + i * 4;
        const uint8_t *u = layer_buffer[0] + i * 4;
        const uint8_t *src = f;
        if (o[LAYER_ALPHA_BYTE])
            src = o;
        else if (u[LAYER_ALPHA_BYTE] &&
                 f[RED_BYTE] == 0 && f[GREEN_BYTE] == 0 && f[BLUE_BYTE] == 0)
            src = u;
        uint8_t *d = display_buffer + i * 4;
        d[RED_BYTE] = src[RED_BYTE];
        d[GREEN_BYTE] = src[GREEN_BYTE];
        d[BLUE_BYTE] = src[BLUE_BYTE];
        d[LAYER_ALPHA_BYTE] = 255;
    }
}

void ref_rasterizer_layer(int layer)
{
    layer_target = layer;
    if (layer > 0)
        layers_in_use = 1;
}

unsigned char* ref_rasterizer_frontbuffer()
{
    // once layers are in use the display reads the per-present composite
    // (refreshed in ref_rasterizer_frame_sync), not the raw front buffer
    if (layers_in_use && display_buffer)
        return display_buffer;
    return gl_c_frontbuffer;
}

unsigned short* ref_rasterizer_ci_frontbuffer()
{
    return gl_ci_frontbuffer;
}

// Bake the front CI buffer through the given colormap into the front RGB
// buffer (the SGI hardware palette LUT emulation). Every pixel is rewritten
// from its recorded index, so anything painted RGB-only (shim UI such as an
// open popup menu) is overwritten with the underlying scene — which is why
// the GL layer only calls this at "demo finished a frame" present points,
// never from inside dopup's modal loop.
void ref_rasterizer_resolve_ci_to_rgb(uint8_t colormap[][3])
{
    if (!gl_ci_frontbuffer || !gl_c_frontbuffer)
        return;
    size_t n = (size_t)DISPLAY_WIDTH * DISPLAY_HEIGHT;
    for (size_t i = 0; i < n; i++) {
        uint16_t ci = gl_ci_frontbuffer[i];
        uint8_t *p = gl_c_frontbuffer + i * 4;
        p[RED_BYTE]   = colormap[ci][0];
        p[GREEN_BYTE] = colormap[ci][1];
        p[BLUE_BYTE]  = colormap[ci][2];
    }
}

static size_t ci_buffer_bytes(void) { return (size_t)DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint16_t); }

void ref_rasterizer_copy_front_to_back()
{
    if (gl_c_backbuffer)
        memcpy(gl_c_backbuffer, gl_c_frontbuffer, color_buffer_bytes());
    if (gl_ci_backbuffer)
        memcpy(gl_ci_backbuffer, gl_ci_frontbuffer, ci_buffer_bytes());
}

void ref_rasterizer_copy_back_to_front()
{
    if (gl_c_frontbuffer)
        memcpy(gl_c_frontbuffer, gl_c_backbuffer, color_buffer_bytes());
    if (gl_ci_frontbuffer)
        memcpy(gl_ci_frontbuffer, gl_ci_backbuffer, ci_buffer_bytes());
}

void ref_rasterizer_swap()
{
    // swap back buffer (buffer being rasterized) and front buffer (buffer being displayed)
    uint8_t *_gl_backbuffer = gl_c_backbuffer; gl_c_backbuffer = gl_c_frontbuffer; gl_c_frontbuffer = _gl_backbuffer;
    uint16_t *_gl_ci_backbuffer = gl_ci_backbuffer; gl_ci_backbuffer = gl_ci_frontbuffer; gl_ci_frontbuffer = _gl_ci_backbuffer;

    // optionally dump frames to ppm files (through the layer composite when
    // layers are in use, so dumps show what the display shows)
    static int frame = 0;
    if (gen_ppm_frame_files && gl_c_backbuffer)
    {
        uint8_t *dump = gl_c_backbuffer;
        if (layers_in_use && display_buffer) {
            composite_layers_into_display(gl_c_backbuffer);
            dump = display_buffer;
        }
        unsigned char rgb_pixel[3];
        char name[128];
        sprintf(name, "frame%04d.ppm", frame);
        FILE *fp = fopen(name, "wb");
        fprintf(fp, "P6 %d %d 255\n", DISPLAY_WIDTH, DISPLAY_HEIGHT);
            for (int j = 0; j < DISPLAY_HEIGHT; j++) {
                for (int i = 0; i < DISPLAY_WIDTH; i++) {
                    // PPM expects RGB format
                    uint8_t *p = buffer_pixel(dump, i, j);
                    rgb_pixel[0] = p[RED_BYTE];
                    rgb_pixel[1] = p[GREEN_BYTE];
                    rgb_pixel[2] = p[BLUE_BYTE];
                    fwrite(rgb_pixel, 1, 3, fp);
                }
            }
        fclose(fp);
    }

    frame++;
}

int32_t ref_rasterizer_winopen(char *title)
{
    void ref_rasterizer_zclear(uint32_t z);
    ref_rasterizer_clear(0, 0, 0, 0);
    ref_rasterizer_zclear(Z_MAX);

    if (getenv("GEN_FRAME_PPM_FILES") != NULL) {
        gen_ppm_frame_files = 1;
        printf("Generating .PPM file for each frame\n");
    }

    if (getenv("SNAP_VERTICES") != NULL) {
        snap_vertices = 1;
        printf("Vertex values in X and Y will be rounded to nearest pixel corner\n");
    }

    return 1;
}

void ref_rasterizer_rgbmode(int enable)
{
    rgb_mode = enable;
}

void ref_rasterizer_cbuffer_draw(int enable_front, int enable_back)
{
    frontbuffer_draw_enabled = enable_front;
    backbuffer_draw_enabled = enable_back;
}

void ref_rasterizer_zbuffer(int enable)
{
    zbuffer_enabled = enable;
}

void ref_rasterizer_zclear(uint32_t z)
{
    if (!z_buffer)
        return;
    size_t n = (size_t)DISPLAY_WIDTH * DISPLAY_HEIGHT;
    for (size_t i = 0; i < n; i++)
        z_buffer[i] = z;
}

void ref_rasterizer_zclear_rect(uint32_t z, int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    if (!z_buffer)
        return;
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 >= DISPLAY_WIDTH)  x1 = DISPLAY_WIDTH - 1;
    if (y1 >= DISPLAY_HEIGHT) y1 = DISPLAY_HEIGHT - 1;
    for (int32_t y = y0; y <= y1; y++) {
        z_t *row = z_buffer + (size_t)(DISPLAY_HEIGHT - 1 - y) * DISPLAY_WIDTH;   // rect is y-up
        for (int32_t x = x0; x <= x1; x++)
            row[x] = z;
    }
}

void ref_rasterizer_czclear(uint8_t r, uint8_t g, uint8_t b, short color_index, uint32_t z)
{
    ref_rasterizer_zclear(z);
    ref_rasterizer_clear(r, g, b, color_index);
}

static void boxi2DClear(int bbox[4])
{
    bbox[0] = INT_MAX;
    bbox[1] = INT_MIN;
    bbox[2] = INT_MAX;
    bbox[3] = INT_MIN;
}

static void boxi2DGrow(int bbox[4], float *v)
{
    if (floor(v[0]) < bbox[0]) bbox[0] = floor(v[0]);
    if (ceil(v[0]) > bbox[1]) bbox[1] = ceil(v[0]);
    if (floor(v[1]) < bbox[2]) bbox[2] = floor(v[1]);
    if (ceil(v[1]) > bbox[3]) bbox[3] = ceil(v[1]);
}

static void boxi2DIsect(int bb1[4], int bb2[4], int r[4])
{
    r[0] = (bb1[0] < bb2[0]) ? bb1[0] : bb1[0];
    r[1] = (bb1[1] > bb2[1]) ? bb1[1] : bb1[1];
    r[2] = (bb1[2] < bb2[2]) ? bb1[2] : bb1[2];
    r[3] = (bb1[3] > bb2[3]) ? bb1[3] : bb1[3];
}

static float evalHalfPlane(float v0[2], float v1[2], float v2[2], float x, float y)
{
    float n[2];

    n[0] = - (v1[1] - v0[1]);
    n[1] = v1[0] - v0[0];

    return ((x - v0[0]) * n[0] + (y - v0[1]) * n[1]) /
        ((v2[0] - v0[0]) * n[0] + (v2[1] - v0[1]) * n[1]);
}

static void calcHalfPlaneDiffs(float v0[2], float v1[2], float v2[2],
    float *dx, float *dy)
{
    *dx = evalHalfPlane(v0, v1, v2, 1, 0) - evalHalfPlane(v0, v1, v2, 0, 0);
    *dy = evalHalfPlane(v0, v1, v2, 0, 1) - evalHalfPlane(v0, v1, v2, 0, 0);
}

static void set_buffer_pixel(int draw_enabled, uint8_t *buffer, int y, int x, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (draw_enabled)
    {
        uint8_t *p = buffer_pixel(buffer, x, y);
        if (blend_enabled && a < 255) {
            // src-alpha / one-minus-src-alpha (the only IRIS mode demos use)
            p[RED_BYTE]   = (r * a + p[RED_BYTE]   * (255 - a)) / 255;
            p[GREEN_BYTE] = (g * a + p[GREEN_BYTE] * (255 - a)) / 255;
            p[BLUE_BYTE]  = (b * a + p[BLUE_BYTE]  * (255 - a)) / 255;
        } else {
            p[RED_BYTE] = r;
            p[GREEN_BYTE] = g;
            p[BLUE_BYTE] = b;
        }
    }
}

static void set_ci_buffer_pixel(int draw_enabled, uint16_t *buffer, int y, int x, uint16_t ci)
{
    if (draw_enabled)
        buffer[(size_t)y * DISPLAY_WIDTH + x] = ci;
}

// Record the color index of a drawn pixel, parallel to the RGB write. CI
// mode in this shim is flat-shaded per primitive (index taken from the
// primitive's first vertex): real SGI hardware could Gouraud-interpolate
// indices, but for non-ramp palettes the result was nonsense and the demos
// in this corpus don't rely on it. Vertices carrying SCREEN_VERTEX_CI_NONE
// (shim UI, RGB mode) leave the CI buffer untouched.
static void write_ci_pixel(int buffer_y, int x, uint16_t ci)
{
    if (!rgb_mode && ci != SCREEN_VERTEX_CI_NONE) {
        set_ci_buffer_pixel(backbuffer_draw_enabled, gl_ci_backbuffer, buffer_y, x, ci);
        set_ci_buffer_pixel(frontbuffer_draw_enabled, gl_ci_frontbuffer, buffer_y, x, ci);
    }
}

// IRIS per-draw writemask compositing, exact form: a drawn pixel's index
// becomes (oldIndex & ~wm) | (drawnIndex & wm), RGB re-resolved through the
// colormap. flight 1988 leaves writemask(wm_allplanes-3) up while drawing
// its meter bars, compass needle, and readout text, so the scale art in
// planes 0-1 composites through them (blue bar over an orange tick -> index
// blue|orange, mapcolor'd back to orange). Each buffer composites against
// its own CI planes, exactly like the hardware did per-bitplane.
static int masked_draw_active(uint16_t ci)
{
    return !rgb_mode && ci != SCREEN_VERTEX_CI_NONE && the_colormap != NULL &&
           (~the_writemask & 0xfff) != 0;
}

static void write_masked_ci_pixel(int draw_enabled, uint8_t *buffer, uint16_t *cibuf,
                                  int buffer_y, int x, uint16_t ci)
{
    if (!draw_enabled || !buffer || !cibuf)
        return;
    size_t i = (size_t)buffer_y * DISPLAY_WIDTH + x;
    uint16_t nci = (uint16_t)(((cibuf[i] & ~the_writemask) | (ci & the_writemask)) & 0xfff);
    cibuf[i] = nci;
    uint8_t *p = buffer_pixel(buffer, x, buffer_y);
    p[RED_BYTE]   = the_colormap[nci][0];
    p[GREEN_BYTE] = the_colormap[nci][1];
    p[BLUE_BYTE]  = the_colormap[nci][2];
}

// IRIS scrmask (rasterizer_scissor): scissor rows are precomputed top-down
// (buffer_y space) so write_pixel compares directly
static int scissor_enabled = 0;
static int32_t scissor_x0, scissor_x1, scissor_row0, scissor_row1;

void ref_rasterizer_scissor(int enable, int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    scissor_enabled = enable;
    scissor_x0 = x0;
    scissor_x1 = x1;
    scissor_row0 = DISPLAY_HEIGHT - 1 - y1;   // rect is y-up; rows are top-down
    scissor_row1 = DISPLAY_HEIGHT - 1 - y0;
}

// Single pixel-write entry for all primitives: masked CI compositing when a
// partial writemask is up in CI mode, the plain RGB(+CI) write otherwise.
// A selected layer plane captures the write instead (alpha = its index bit).
static void write_pixel(int buffer_y, int x, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint16_t ci)
{
    if (scissor_enabled &&
        (x < scissor_x0 || x > scissor_x1 || buffer_y < scissor_row0 || buffer_y > scissor_row1))
        return;
    if (!colormask_enabled)     // wmpack(0): z-only draws (z written by the caller)
        return;
    if (layer_target > 0) {
        uint8_t *buf = layer_buffer[layer_target - 1];
        if (!buf)
            return;
        uint8_t *p = buf + ((size_t)buffer_y * DISPLAY_WIDTH + x) * 4;
        p[RED_BYTE] = r;
        p[GREEN_BYTE] = g;
        p[BLUE_BYTE] = b;
        p[LAYER_ALPHA_BYTE] = a;
        return;
    }
    if (masked_draw_active(ci)) {
        write_masked_ci_pixel(backbuffer_draw_enabled, gl_c_backbuffer, gl_ci_backbuffer, buffer_y, x, ci);
        write_masked_ci_pixel(frontbuffer_draw_enabled, gl_c_frontbuffer, gl_ci_frontbuffer, buffer_y, x, ci);
        return;
    }
    set_buffer_pixel(backbuffer_draw_enabled, gl_c_backbuffer, buffer_y, x, r, g, b, a);
    set_buffer_pixel(frontbuffer_draw_enabled, gl_c_frontbuffer, buffer_y, x, r, g, b, a);
    write_ci_pixel(buffer_y, x, ci);
}

static z_t sz_to_zbuffer(float screenz)
{
    uint32_t z_ = (uint32_t)clamp(screenz, 0.0, (float)0xFFFFFF7F); // largest float <= UINT_MAX
    z_t z = z_ >> Z_SHIFT;
    return z;
}

static void triPixel(int x, int y, float bary[3], screen_vertex s[3])
{
    if (pattern_enabled) {
        int px = x % 16;
        int py = y % 16;
        if (!(the_pattern[py] & (1 << px)))
            return;
    }

    // Round, don't truncate: the barycentric weights only sum to ~1.0, so
    // truncation turned flat fills (all three vertices the same color) into
    // off-by-one pixels — off-palette values in CI-mode demos.
    uint8_t r = (uint8_t)clamp(bary[0] * s[0].r + bary[1] * s[1].r + bary[2] * s[2].r + 0.5f, 0.0, UCHAR_MAX);
    uint8_t g = (uint8_t)clamp(bary[0] * s[0].g + bary[1] * s[1].g + bary[2] * s[2].g + 0.5f, 0.0, UCHAR_MAX);
    uint8_t b = (uint8_t)clamp(bary[0] * s[0].b + bary[1] * s[1].b + bary[2] * s[2].b + 0.5f, 0.0, UCHAR_MAX);
    uint8_t a = (uint8_t)clamp(bary[0] * s[0].a + bary[1] * s[1].a + bary[2] * s[2].a + 0.5f, 0.0, UCHAR_MAX);

    if (texture_enabled) {
        // modulate (IRIS TV_MODULATE); affine like the color interpolation
        float ts = bary[0] * s[0].s + bary[1] * s[1].s + bary[2] * s[2].s;
        float tt = bary[0] * s[0].t + bary[1] * s[1].t + bary[2] * s[2].t;
        int tr, tg, tb;
        tex_sample(ts, tt, &tr, &tg, &tb);
        r = (uint8_t)(r * tr / 255);
        g = (uint8_t)(g * tg / 255);
        b = (uint8_t)(b * tb / 255);
    }

    z_t z = sz_to_zbuffer(bary[0] * s[0].z + bary[1] * s[1].z + bary[2] * s[2].z);

    int buffer_y = DISPLAY_HEIGHT - 1 - y;

    // z <= : LEQUAL, the IRIS GL default z-function. Later geometry at equal
    // depth overwrites — newave's edit-mode crosshair redraws mesh lines in
    // green at the same z and must win, as it did on the real hardware.
    // IRIS zbuffer(FALSE) neither tests nor WRITES z (flight 3.4's horizon
    // depends on that — see the gles2 rasterizer's depth-mask comment).
    // Layer planes carry no z: their draws neither test nor write it.
    size_t zi = (size_t)buffer_y * DISPLAY_WIDTH + x;
    if (layer_target > 0 || !zbuffer_enabled || (z <= z_buffer[zi])) {
        write_pixel(buffer_y, x, r, g, b, a, s[0].ci);
        if (zbuffer_enabled && zwrite_enabled && layer_target == 0)
            z_buffer[zi] = z;
    }
}

static void draw_screen_triangle(screen_vertex *s0, screen_vertex *s1, screen_vertex *s2)
{
    float v0[2];
    float v1[2];
    float v2[2];
    v0[0] = s0->x / (float)SCREEN_VERTEX_V2_SCALE;
    v0[1] = s0->y / (float)SCREEN_VERTEX_V2_SCALE;
    v1[0] = s1->x / (float)SCREEN_VERTEX_V2_SCALE;
    v1[1] = s1->y / (float)SCREEN_VERTEX_V2_SCALE;
    v2[0] = s2->x / (float)SCREEN_VERTEX_V2_SCALE;
    v2[1] = s2->y / (float)SCREEN_VERTEX_V2_SCALE;
    if (snap_vertices) {
        v0[0] = floor(v0[0]);
        v0[1] = floor(v0[1]);
        v1[0] = floor(v1[0]);
        v1[1] = floor(v1[1]);
        v2[0] = floor(v2[0]);
        v2[1] = floor(v2[1]);
    }
    int viewport[4] = {0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT};
    screen_vertex s[3] = {*s0, *s1, *s2};

    int bbox[4];
    int i, j;
    float bary[3];
    float dxa, dxb, dxc;
    float dya, dyb, dyc;
    float rowa, rowb, rowc;

    boxi2DClear(bbox);
    boxi2DGrow(bbox, v0);
    boxi2DGrow(bbox, v1);
    boxi2DGrow(bbox, v2);
    boxi2DIsect(bbox, viewport, bbox);

    calcHalfPlaneDiffs(v1, v2, v0, &dxa, &dya);
    rowa = evalHalfPlane(v1, v2, v0, bbox[0] + 0.5f, bbox[2] + 0.5f);

    calcHalfPlaneDiffs(v2, v0, v1, &dxb, &dyb);
    rowb = evalHalfPlane(v2, v0, v1, bbox[0] + 0.5f, bbox[2] + 0.5f);

    calcHalfPlaneDiffs(v0, v1, v2, &dxc, &dyc);
    rowc = evalHalfPlane(v0, v1, v2, bbox[0] + 0.5f, bbox[2] + 0.5f);

    for (j = bbox[2]; j < bbox[3]; j++) {
        bary[0] = rowa;
        bary[1] = rowb;
        bary[2] = rowc;
        for (i = bbox[0]; i < bbox[1]; i++) {
            if ((bary[0] > -0.001 && bary[0] < 1.001f) &&
                (bary[1] > -0.001 && bary[1] < 1.001f) &&
                (bary[2] > -0.001 && bary[2] < 1.001f))
                triPixel(i, j, bary, s);
            bary[0] += dxa;
            bary[1] += dxb;
            bary[2] += dxc;
        }
        rowa += dya;
        rowb += dyb;
        rowc += dyc;
    }
}

static void screen_vertex_offset_with_clamp(screen_vertex* v, float dx, float dy)
{
    v->x = clamp(v->x + dx * SCREEN_VERTEX_V2_SCALE, 0, (DISPLAY_WIDTH - 1) * SCREEN_VERTEX_V2_SCALE);
    v->y = clamp(v->y + dy * SCREEN_VERTEX_V2_SCALE, 0, (DISPLAY_HEIGHT - 1) * SCREEN_VERTEX_V2_SCALE);
}

void ref_rasterizer_bitmap(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *bits)
{
    screen_vertex s[4];
    if (!gl_c_backbuffer)
        return;

    for (int j = 0; j < height; j++) {
        int prevbit = 0;
        int count;
        for (int i = 0; i < width; i++) {
            int bit = (bits[j * rowbytes + i / 8] >> (7 - i % 8)) & 1;

            if (bit) {

                if (!prevbit && bit) {
                    // Previous bit was 0 and this bit is 1, so start a
                    // run
                    for (int k = 0; k < 4; k++) {
                        s[k] = *sv; // Copy color
                        s[k].x = sv->x + SCREEN_VERTEX_V2_SCALE * i;
                        s[k].y = sv->y + (height - j - 1) * SCREEN_VERTEX_V2_SCALE;
                        s[k].z = sv->z;
                    }

                    screen_vertex_offset_with_clamp(&s[0], 0, 0);
                    screen_vertex_offset_with_clamp(&s[1], 0, 1);
                    count = 0;
                }

                // Add this bit to current run
                count++;

            } else if (prevbit) {

                // The previous bit was 1 and this bit is 0, so
                // finish the run
                screen_vertex_offset_with_clamp(&s[2], count, 1);
                screen_vertex_offset_with_clamp(&s[3], count, 0);
                draw_screen_triangle(&s[0], &s[1], &s[2]);
                draw_screen_triangle(&s[2], &s[3], &s[0]);
            }

            prevbit = bit;
        }

        if (prevbit) {
            // the end of the row was a 1 bit, so finish run
            screen_vertex_offset_with_clamp(&s[2], count, 1);
            screen_vertex_offset_with_clamp(&s[3], count, 0);
            draw_screen_triangle(&s[0], &s[1], &s[2]);
            draw_screen_triangle(&s[2], &s[3], &s[0]);
        }
    }
}

// Blit an 8-bit alpha source over the framebuffer at sv, in color (r,g,b),
// using source-over blending. Like ref_rasterizer_bitmap but with grayscale
// coverage instead of 1bpp, for antialiased glyph rendering.
void ref_rasterizer_alpha_blit(uint32_t width, uint32_t rowbytes, uint32_t height,
                           screen_vertex *sv, uint8_t *alpha,
                           uint8_t r, uint8_t g, uint8_t b)
{
    if (!gl_c_backbuffer)
        return;

    // Anchor in pixel coords (sv is in fixed-point).
    // Mirrors ref_rasterizer_bitmap's coordinate conventions: sv->x and sv->y are in
    // SCREEN_VERTEX_V2_SCALE fixed-point
    int base_x = sv->x / SCREEN_VERTEX_V2_SCALE;
    int base_y = sv->y / SCREEN_VERTEX_V2_SCALE;

    for (int j = 0; j < (int)height; j++) {
        // Matches ref_rasterizer_bitmap: the source is drawn Y-flipped so
        // that increasing j in source goes downward on screen (with Y-up).
        int y = base_y + (int)(height - j - 1);
        if (y < 0 || y >= DISPLAY_HEIGHT) continue;

        for (int i = 0; i < (int)width; i++) {
            int x = base_x + i;
            if (x < 0 || x >= DISPLAY_WIDTH) continue;

            uint8_t a = alpha[j * rowbytes + i];
            if (a == 0) continue;
            if (!text_antialias_enabled) {
                // Hard 50% threshold: opaque or nothing.
                if (a < 128) continue; // 128
                a = 255;
            }

            // Source-over blend: dst = src*a + dst*(1-a), with a in [0,255].
            // The (x + 127) / 255 rounded-divide form is exact for the
            // integer math; the cheaper (x*a + x) >> 8 is a near-equivalent
            // approximation we could use if this turns out to be a hot spot.
            if (backbuffer_draw_enabled) {
                uint8_t *p = buffer_pixel(gl_c_backbuffer, x, y);
                p[RED_BYTE]   = (uint8_t)((r * a + p[RED_BYTE]   * (255 - a) + 127) / 255);
                p[GREEN_BYTE] = (uint8_t)((g * a + p[GREEN_BYTE] * (255 - a) + 127) / 255);
                p[BLUE_BYTE]  = (uint8_t)((b * a + p[BLUE_BYTE]  * (255 - a) + 127) / 255);
            }
            if (frontbuffer_draw_enabled) {
                uint8_t *p = buffer_pixel(gl_c_frontbuffer, x, y);
                p[RED_BYTE]   = (uint8_t)((r * a + p[RED_BYTE]   * (255 - a) + 127) / 255);
                p[GREEN_BYTE] = (uint8_t)((g * a + p[GREEN_BYTE] * (255 - a) + 127) / 255);
                p[BLUE_BYTE]  = (uint8_t)((b * a + p[BLUE_BYTE]  * (255 - a) + 127) / 255);
            }
        }
    }
}

static void draw_point(screen_vertex *sv)
{
    screen_vertex s = *sv;

    float v[2];
    v[0] = s.x / (float)SCREEN_VERTEX_V2_SCALE;
    v[1] = s.y / (float)SCREEN_VERTEX_V2_SCALE;
    if (snap_vertices) {
        v[0] = floor(v[0]);
        v[1] = floor(v[1]);
    }

    int x = clamp(v[0], 0, DISPLAY_WIDTH - 1);
    int y = clamp(v[1], 0, DISPLAY_HEIGHT - 1);
    z_t z = sz_to_zbuffer(s.z);

    int buffer_y = DISPLAY_HEIGHT - 1 - y;
    // z <= : LEQUAL, the IRIS GL default (see triPixel); layers carry no z,
    // and zbuffer(FALSE) neither tests nor writes
    size_t zi = (size_t)buffer_y * DISPLAY_WIDTH + x;
    if (layer_target > 0 || !zbuffer_enabled || (z <= z_buffer[zi])) {
        write_pixel(buffer_y, x, s.r, s.g, s.b, s.a, s.ci);
        if (zbuffer_enabled && zwrite_enabled && layer_target == 0)
            z_buffer[zi] = z;
    }
}

static void draw_line(screen_vertex *v0, screen_vertex *v1)
{
    float dx = (v1->x - v0->x);
    float dy = (v1->y - v0->y);
    float d = sqrt(dx * dx + dy * dy);

    if (d == 0.0) {
        draw_point(v0);
        return;
    }

    screen_vertex q[4] = {*v0, *v0, *v1, *v1};

    if (fabs(dx) > fabs(dy)) {
        screen_vertex_offset_with_clamp(&q[0], 0, -the_linewidth * .5);
        screen_vertex_offset_with_clamp(&q[1], 0,  the_linewidth * .5);
        screen_vertex_offset_with_clamp(&q[2], 0,  the_linewidth * .5);
        screen_vertex_offset_with_clamp(&q[3], 0, -the_linewidth * .5);
    } else {
        screen_vertex_offset_with_clamp(&q[0], -the_linewidth * .5, 0);
        screen_vertex_offset_with_clamp(&q[1],  the_linewidth * .5, 0);
        screen_vertex_offset_with_clamp(&q[2],  the_linewidth * .5, 0);
        screen_vertex_offset_with_clamp(&q[3], -the_linewidth * .5, 0);
    }

    draw_screen_triangle(&q[0], &q[1], &q[2]);
    draw_screen_triangle(&q[2], &q[3], &q[0]);
}

void ref_rasterizer_draw(uint32_t type, uint32_t count, screen_vertex *screenverts)
{
    int i;
    if (!gl_c_backbuffer)
        return;
    switch(type) {
        case DRAW_POINTS:
            for (i = 0; i < count; ++i)
                draw_point(&screenverts[i]);
            break;
        case DRAW_LINES:
            for (i = 0; i < count / 2; i++) {
                draw_line(&screenverts[i * 2 + 0], &screenverts[i * 2 + 1]);
            }
            break;
        case DRAW_TRIANGLES:
            for (i = 0; i < count / 3; i++)
                draw_screen_triangle(&screenverts[i * 3], &screenverts[i * 3 + 1], &screenverts[i * 3 + 2]);
            break;
    }
}

void ref_rasterizer_frame_sync(void)
{
    // CPU rasterizer renders directly into the front/back buffers; nothing
    // to flush — but refresh the layer composite the display reads
    if (layers_in_use)
        composite_layers_into_display(gl_c_frontbuffer);
}

// The framebuffer tracks the window size: reallocate the color and z
// buffers at the new size and clear them. The caller (gl.c) re-registers
// the new front buffer pointer with the display afterwards.
void ref_rasterizer_resize(uint32_t width, uint32_t height)
{
    if ((int32_t)width == DISPLAY_WIDTH && (int32_t)height == DISPLAY_HEIGHT)
        return;

    free(c_buffer[0]);
    free(c_buffer[1]);
    free(ci_buffer[0]);
    free(ci_buffer[1]);
    free(layer_buffer[0]);
    free(layer_buffer[1]);
    free(display_buffer);
    free(z_buffer);

    DISPLAY_WIDTH = width;
    DISPLAY_HEIGHT = height;

    c_buffer[0] = calloc(1, color_buffer_bytes()); // calloc = cleared to black
    c_buffer[1] = calloc(1, color_buffer_bytes());
    ci_buffer[0] = calloc(1, ci_buffer_bytes());   // calloc = cleared to index 0
    ci_buffer[1] = calloc(1, ci_buffer_bytes());
    layer_buffer[0] = calloc(1, color_buffer_bytes()); // calloc = transparent (alpha 0)
    layer_buffer[1] = calloc(1, color_buffer_bytes());
    display_buffer = calloc(1, color_buffer_bytes());
    z_buffer = malloc((size_t)DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(z_t));
    gl_c_backbuffer = c_buffer[0];
    gl_c_frontbuffer = c_buffer[1];
    gl_ci_backbuffer = ci_buffer[0];
    gl_ci_frontbuffer = ci_buffer[1];

    ref_rasterizer_zclear(Z_MAX);

    printf("INFO: ref rasterizer framebuffer %dx%d\n", DISPLAY_WIDTH, DISPLAY_HEIGHT);
}

const rasterizer_funcs* ref_rasterizer_get_funcs(void)
{
    static const rasterizer_funcs funcs =
    {
        .winopen            = ref_rasterizer_winopen,
        .rgbmode            = ref_rasterizer_rgbmode,
        .clear              = ref_rasterizer_clear,
        .zclear             = ref_rasterizer_zclear,
        .zclear_rect        = ref_rasterizer_zclear_rect,
        .czclear            = ref_rasterizer_czclear,
        .swap               = ref_rasterizer_swap,
        .copy_front_to_back = ref_rasterizer_copy_front_to_back,
        .copy_back_to_front = ref_rasterizer_copy_back_to_front,
        .frontbuffer        = ref_rasterizer_frontbuffer,
        .draw               = ref_rasterizer_draw,
        .bitmap             = ref_rasterizer_bitmap,
        .alpha_blit         = ref_rasterizer_alpha_blit,
        .masked_clear       = ref_rasterizer_masked_clear,
        .writemask          = ref_rasterizer_writemask,
        .setpattern         = ref_rasterizer_setpattern,
        .pattern            = ref_rasterizer_pattern,
        .scissor            = ref_rasterizer_scissor,
        .layer              = ref_rasterizer_layer,
        .cbuffer_draw       = ref_rasterizer_cbuffer_draw,
        .zbuffer            = ref_rasterizer_zbuffer,
        .blend              = ref_rasterizer_blend,
        .teximage           = ref_rasterizer_teximage,
        .texture            = ref_rasterizer_texture,
        .zwrite             = ref_rasterizer_zwrite,
        .colormask          = ref_rasterizer_colormask,
        .linewidth          = ref_rasterizer_linewidth,
        .frame_sync         = ref_rasterizer_frame_sync,
        .resize             = ref_rasterizer_resize,
        .ci_frontbuffer     = ref_rasterizer_ci_frontbuffer,
        .resolve_ci_to_rgb  = ref_rasterizer_resolve_ci_to_rgb,
    };
    return &funcs;
}
