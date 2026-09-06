// Forked from the Alice 4 project's libgl (https://github.com/lkesteloot/alice),
// Copyright Lawrence Kesteloot and contributors, Apache License 2.0.
// Modified by the sgi-demos project (https://github.com/sgi-demos/sgi-demos),
// Copyright 2023-2026 the sgi-demos contributors, Apache License 2.0.
// See NOTICE at the repository root.
// make all implemented functions have trace
// make all tracefunctions look like C-ish
// RECORD macro checks display list mode, make, store object...?
// fix all int usage
// make trace() function
// consistent function start
// Need display-listing:
//      reshapeviewport?
//      swapbuffers?
//      linewidth
//      rdr2i
//      rmv2i
//      zbuffer
//      zclear

// software libgl implementation - fork of Alice 4

#include <stdio.h>
#include <stdlib.h>
#include "bsd_string.h" // includes <string.h>
#include <math.h>
#include <stdarg.h>
#include <signal.h>
#include <gl.h>
#include <device.h>
#include "basic_types.h"
#include "vector.h"
#include "rasterizer.h"
#include "bdffont.h"
#include "irisfont0.h"      // default charstr font: the recovered IRIX 3 system screen font (IRIS GL font 0)
#include "events.h"
#include "font.h"

//----------------------------------------------------------------------------
// Tracing
/*
 * Define NDEBUG for targets with optimization.  Tracing will not be enable-able.
 *
 * In order to show a GL function trace, DON'T enable NDEBUG and
 * set TRACE_GL environment variable to anything.
 *
 * If NDEBUG is defined or if TRACE_GL environment variable is not
 * set, you'll see no tracing.
 */

#if !defined(NDEBUG)
static int trace_functions = 0;
#else
const int trace_functions = 0;
#endif
static int trace_network = 0;
static int trace_indent = 0;

void trace_func(const char *func, const char *fmt, ...)
{
    va_list args;
    static char dummy[512];
    char *dp = dummy;

    if(!trace_functions)
        return;

    for(int i = 0 ; i < trace_indent; i++)
        *dp++ = ' ';

    dp = stpcpy(dp, func);
    *dp++ = '(';

    va_start(args, fmt);
    dp += vsprintf(dp, fmt, args);
    va_end(args);

    dp = stpcpy(dp, ");\n");

    fputs(dummy, stdout);
}

#define TRACEF(fmt, ...) trace_func(__FUNCTION__, fmt, __VA_ARGS__)
#define TRACE() trace_func(__FUNCTION__, "")

//----------------------------------------------------------------------------
// GL state
// Display (framebuffer) size tracks the window: set via
// gl_framebuffer_resized() at window creation and on window resizes.
// XMAXSCREEN+1 x YMAXSCREEN+1 is only the pre-window default.
static int DISPLAY_WIDTH = XMAXSCREEN + 1;
static int DISPLAY_HEIGHT = YMAXSCREEN + 1;


static vec3ub colormap[4096];
static int colormap_max_mapped = 0;
static uint8_t colormap_mapped[4096];   // indices explicitly set by mapcolor. Unset
                                        // entries are all black and must not join the
                                        // masked-clear remap (a black->X pair would
                                        // recolor the background)
static vec4f current_color = {1.0f, 1.0f, 1.0f, 1.0f};
static unsigned short current_color_index = 0;
static unsigned short current_writemask = 0xffff;

// IRIS layer planes (drawmode): UNDERDRAW/OVERDRAW/PUPDRAW route color(),
// mapcolor(), clear() and all drawing to a side layer the rasterizer
// composites at present time — overlay wherever its own index != 0, then
// the normal planes, then the underlay where the normal planes are exactly
// black (the SGI display priority; flight 3.4's gauge faces live in the
// underlay and show through the black dial interiors). Layer drawing
// carries its "index != 0" bit in the vertex alpha: color(0) draws
// transparent (erases the layer). CURSORDRAW is folded into the overlay
// layer — the only demo touching it (flight 1988) just clears it to 0.
// Hardware layer colormaps were 2 bits; 256 entries is roomy.
static int current_drawmode = NORMALDRAW;
static uint8_t layer_colormap[2][256][3];   // [0] = underlay, [1] = overlay/pup

// -1 = normal planes, 0 = underlay, 1 = overlay
static int drawmode_layer(int mode) {
    switch (mode) {
        case UNDERDRAW:  return 0;
        case OVERDRAW:
        case PUPDRAW:
        case CURSORDRAW: return 1;
        default:         return -1;
    }
}
// set in winopen; also gates rasterizer calls that would otherwise lock in
// the rasterizer selection before apply_demo_quirks runs (see writemask)
static int window_is_open = 0;
static vec3f current_normal = {1.0f, 1.0f, 1.0f};
static vec4f current_position = {0.0f, 0.0f, 0.0f, 1.0};
static vec4f current_character_position = {0.0f, 0.0f, 0.0f, 1.0f};
static int current_font = 0;
static int current_pattern = 0;
static int backbuffer_draw_enabled = 1;
static int frontbuffer_draw_enabled = 0;
static int zbuffer_enabled = 0;
static int backface_enabled = 0;
static int the_linewidth = 1;
static int rgb_mode = 0;

// Per-buffer staleness of the RGB cache vs. the CI buffer: set on both when
// a colormap entry changes (mapcolor), swapped along with the buffers at
// swapbuffers, cleared on the front flag by gl_resolve_ci_if_needed. Pixels
// carry draw-time-resolved RGB, so a buffer is only stale if the colormap
// changed since its pixels were drawn — demos with a static palette resolve
// once and never again. (Writemask masked clears keep CI and RGB in step —
// the reference rasterizer applies them through the CI buffer — so a later
// resolve reproduces, not undoes, them.) Start 1 so the first presents
// resolve.
static int ci_rgb_cache_stale = 1;       // front buffer
static int ci_rgb_cache_stale_back = 1;  // back buffer
void gl_resolve_ci_if_needed(void); // defined near mapcolor

// Depth-cueing (CI mode): depthcue() + lshaderange() shade vertices by
// depth through a colormap ramp. The SGI did this per pixel; this shim
// computes the ramp index per vertex in project_vertex and lets the
// rasterizer interpolate the resolved RGB — visually equivalent for the
// smooth ramps depth-cued demos use. lsetdepth() defines the screen-z units
// that lshaderange's znear/zfar are expressed in.
static int depthcue_enabled = 0;
static int shade_lowin = 0, shade_highin = 7;
static long shade_znear = 0, shade_zfar = 0x7fffff;
static long ls_znear = 0, ls_zfar = 0x7fffff;

// smoothline() (CI mode): IRIS GL drew antialiased lines by adding pixel
// coverage (0..15) to the base color index inside a 16-entry intensity
// ramp. Without per-pixel coverage we approximate a fully-covered line:
// index | 15 selects the ramp's brightest entry (ramps are 16-aligned).
static int smoothline_enabled = 0;

// zsource(ZSRC_COLOR) makes z-comparisons use color values instead of
// depth (newave's antialiased mode uses it as a painter's trick). We can't
// emulate color-sourced z, so z-testing is suspended while it's selected.
static int zsource_color = 0;

static int matrix_mode = MSINGLE;
static matrix4x4f_stack modelview_stack;
static matrix4x4f_stack projection_stack;
static matrix4x4f_stack texture_stack; // mmode(MTEXTURE): transforms t2f coords
static matrix4x4f_stack *current_stack;

static viewport_t the_viewport;
static viewport_stack_t viewport_stack;

#define MAX_PATTERNS 128   /* flight 3.4 defines explosion patterns at 80+ */
static Pattern16 patterns[MAX_PATTERNS];

#define CIRCLE_SEGMENTS 80
static float circle_verts[CIRCLE_SEGMENTS][2];

static int pup_active = 0; // popup menu active

// The device-event queue and the IRIS GL event API (qdevice/qread/qtest/...)
// now live at bottom of this file.


//------------------------------------------------------------------------
// Lighting & materials

typedef struct material {
    vec3f emission;
    vec3f ambient;
    vec3f specular;
    vec3f diffuse;
    float shininess;
    float alpha;
} material;

typedef struct light {
    vec4f position;
    vec3f ambient;
    vec3f color;
    vec3f spotdirection;
    float spotlight[2];
} light;

typedef struct lmodel {
    int local;
    vec3f ambient;
    float attenuation[2];
} lmodel;

#define MAX_MATERIALS 4352  /* flight 3.4's light.h uses indices up to 52, and its
                               libgobj registers .d-file materials at 0x1000 + n */
#define MAX_LIGHTS 8
#define MAX_LMODELS 2
static material materials[MAX_MATERIALS];
static light lights[MAX_LIGHTS];
static lmodel lmodels[MAX_LMODELS];

static int lighting_enabled = 0;
// texdef2d()/texbind()/t2f() state. One bound texture with REPEAT wrap and
// modulate env — all flight 3.4 (the only texturing demo) uses.
#define MAX_TEXTURES 8
typedef struct {
    int defined;
    int width, height;
    int bilinear;
    uint8_t *rgb;       // width*height*3
} gl_texture;
static gl_texture textures[MAX_TEXTURES];
static float current_texcoord[2] = {0.0f, 0.0f};
static int texture_bound = 0;   // texture index, 0 = none

// fogvertex() state (FG_VTX_EXP model: factor = e^(-density * eye_z))
static int fog_enabled = 0;
static float fog_density = 0.0f;
static vec3f fog_color = {0.5f, 0.5f, 0.5f};
static int normalize_enabled = 1;
static material *material_bound = NULL;
static light *lights_bound[MAX_LIGHTS];
static lmodel *lmodel_bound = NULL;

void material_init(material *m)
{
    // Do these reasonable defaults like OpenGL?
    vec3f_set(m->ambient, 0.2, 0.2, 0.2);
    vec3f_set(m->specular, 0.0, 0.0, 0.0);
    vec3f_set(m->emission, 0.0, 0.0, 0.0);
    vec3f_set(m->diffuse, 0.8, 0.8, 0.8);
    m->shininess = 0.0;
    m->alpha = 1.0;
}

void light_init(light *l)
{
    // Are these reasonable defaults like OpenGL or just 0's?
    vec4f_set(l->position, 0.0, 0.0, 1.0, 0.0);
    vec3f_set(l->ambient, 0.0, 0.0, 0.0);
    vec3f_set(l->color, 1.0, 1.0, 1.0);
    vec3f_set(l->spotdirection, 0.0, 0.0, -1.0);
    l->spotlight[0] = 0;
    l->spotlight[1] = 180.0;
}

void lmodel_init(lmodel *l)
{
    vec3f_set(l->ambient, 0.2, 0.2, 0.2);
    l->local = 0;
    l->attenuation[0] = 1.0;
    l->attenuation[1] = 0.0;
}

//----------------------------------------------------------------------------
// Transformation, lighting, clipping

// ci carries the color index alongside the resolved RGB in CI mode
// (stamped from current_color_index wherever color is stamped), so the
// rasterizer can maintain its per-pixel index buffer. It rides through
// lighting and projection untouched — there is no "lit color index".
typedef struct world_vertex
{
    vec4f coord;
    vec3f normal;
    vec4f color;
    float st[2];    // texture coords (t2f)
    uint16_t ci;
} world_vertex;

typedef struct lit_vertex
{
    vec4f coord;
    vec4f color;
    float st[2];
    uint16_t ci;
} lit_vertex;

void light_vertex(material *mtl, vec4f coord, vec3f normal, vec4f color_)
{
    vec3f color;
    vec3f_mult(mtl->ambient, lmodel_bound->ambient, color);
    vec3f_add(mtl->emission, color, color);

    for(int i = 0; i < MAX_LIGHTS; i++) {

        light *l = lights_bound[i];

        if(l != NULL) {

            // XXX no spotlight
            // XXX for reference - OpenGL 1.1: 2.13.1 Lighting
            // https://www.opengl.org/documentation/specs/version1.1/glspec1.1/node32.html
            vec4f vertex_to_light;
            vec4f vertex_to_light_dir;
            float attenuation;

            if(l->position[3] == 0.0)  {
                vec4f_copy(vertex_to_light, l->position);
                attenuation = 1.0f;
            } else {
                vec4f_subtract(l->position, coord, vertex_to_light);
                attenuation = 1.0f / (
                    lmodel_bound->attenuation[0] +
                    lmodel_bound->attenuation[1] * vec4f_length(vertex_to_light)
                    );
            }


            vec4f_normalize(vertex_to_light, vertex_to_light_dir);

            float n_dot_l = vec3f_dot(normal, vertex_to_light_dir);
            vec3f t1;

            /* ambient calculation */
            vec3f_mult(mtl->ambient, l->ambient, t1);
            vec3f_scale(t1, attenuation, t1);
            vec3f_add(t1, color, color);

            if(n_dot_l >= 0) {
                /* diffuse calculation */
                vec3f_mult(mtl->diffuse, l->color, t1);
                vec3f_scale(t1, attenuation * n_dot_l, t1);
                vec3f_add(t1, color, color);

                /* specular calculation */
                vec4f h;
                if(0 && lmodel_bound->local) {
                    /* XXX eyepoint in local coordinates */
                } else {
                    h[0] = vertex_to_light[0];
                    h[1] = vertex_to_light[1];
                    h[2] = vertex_to_light[2] + 1;
                    h[3] = 0;
                }
                vec4f_normalize(h, h);
                float n_dot_h = vec3f_dot(normal, h);
                if(n_dot_h > 0.0) {
                    float spec_part = powf(n_dot_h, mtl->shininess);
                    vec3f_mult(mtl->specular, l->color, t1);
                    vec3f_scale(t1, attenuation * spec_part, t1);
                    vec3f_add(t1, color, color);
                }
            }
        }
    }
    vec4f_set(color_, color[0], color[1], color[2], mtl->alpha);
}

void transform_and_light_vertex(world_vertex *wv, lit_vertex *lv)
{
    vec4f tv;
    vec3f normal;

    matrix4x4f_mult_vec4f_(matrix4x4f_stack_top(&modelview_stack), wv->coord, tv);

    if(lighting_enabled) {
        vec3f_mult_matrix4x4f(wv->normal, matrix4x4f_stack_get_inverse(&modelview_stack), normal);
        if(normalize_enabled)
            vec3f_normalize(normal, normal);
        light_vertex(material_bound, tv, normal, lv->color);
    } else {
        vec4f_copy(lv->color, wv->color);
    }

    if (texture_bound) {
        // texture matrix (flight 3.4 scrolls its cloud layer with it)
        vec4f stv = { wv->st[0], wv->st[1], 0.0f, 1.0f }, str;
        matrix4x4f_mult_vec4f(matrix4x4f_stack_top(&texture_stack), stv, str);
        lv->st[0] = str[0];
        lv->st[1] = str[1];
    } else {
        lv->st[0] = wv->st[0];
        lv->st[1] = wv->st[1];
    }

    if(fog_enabled) {
        // IRIS per-vertex fog: blend toward the fog color by e^(-density*z),
        // z in eye units (tv is the eye-space position here)
        float fz = tv[2] < 0.0f ? -tv[2] : tv[2];
        float f = expf(-fog_density * fz);
        if(f > 1.0f) f = 1.0f;
        lv->color[0] = f * lv->color[0] + (1.0f - f) * fog_color[0];
        lv->color[1] = f * lv->color[1] + (1.0f - f) * fog_color[1];
        lv->color[2] = f * lv->color[2] + (1.0f - f) * fog_color[2];
    }

    matrix4x4f_mult_vec4f_(matrix4x4f_stack_top(&projection_stack), tv, lv->coord);

    lv->ci = wv->ci;
}

void screen_vertex_set_color(screen_vertex *sv, unsigned short r, unsigned short g, unsigned short b, unsigned short a)
{
    sv->r = r;
    sv->g = g;
    sv->b = b;
    sv->a = a;
    sv->ci = SCREEN_VERTEX_CI_NONE; // shim UI paints RGB directly; no index
}

void screen_vertex_set_position(screen_vertex* v, float x, float y)
{
    v->x = x * SCREEN_VERTEX_V2_SCALE;
    v->y = y * SCREEN_VERTEX_V2_SCALE;
    v->z = 0;
}

static float unitclamp(float v)
{
    return v > 1.0f ? 1.0f : (v < 0.0f ? 0.0f : v);
}

static float clamp(float v, float low, float high)
{
    return v > high ? high : (v < low ? low : v);
}

void project_vertex(lit_vertex *lv, screen_vertex *sv)
{
    // XXX could pre-compute
    int viewport_width = the_viewport[1] - the_viewport[0] + 1;
    int viewport_height = the_viewport[3] - the_viewport[2] + 1;

    float xndc, yndc, zndc;
    xndc = lv->coord[0] / lv->coord[3];
    yndc = lv->coord[1] / lv->coord[3];
    zndc = lv->coord[2] / lv->coord[3];

    float xw, yw, zw;
    // XXX could pre-compute half width and height
    xw = viewport_width / 2.0 * xndc + (the_viewport[0] + viewport_width / 2.0);
    yw = viewport_height / 2.0 * yndc + (the_viewport[2] + viewport_height / 2.0);
    zw = (the_viewport[5] - the_viewport[4]) / 2.0 * zndc + (the_viewport[5] + the_viewport[4]) / 2.0;

    sv->x = clamp(xw, 0, DISPLAY_WIDTH - 1) * SCREEN_VERTEX_V2_SCALE;
    sv->y = clamp(yw, 0, DISPLAY_HEIGHT - 1) * SCREEN_VERTEX_V2_SCALE;
    sv->z = clamp(zw * (float)0xFFFFFFFF, // NOTE: ****Must link with -lm or else this always returns zero***
                  0.0,
                  (float)0xFFFFFF7F); // largest float <= UINT_MAX;
    // Round, don't truncate: clipping lerps colors in float, and a result
    // one ULP under N/255 must still convert to N — screen-edge-clipped
    // flat polygons otherwise land a whole shade off their palette color
    // (154,150,150 walls amid 155,150,150), which the masked-clear RGB
    // remap can never re-match.
    sv->r = unitclamp(lv->color[0]) * 255 + 0.5f;
    sv->g = unitclamp(lv->color[1]) * 255 + 0.5f;
    sv->b = unitclamp(lv->color[2]) * 255 + 0.5f;
    sv->a = unitclamp(lv->color[3]) * 255 + 0.5f;
    sv->s = lv->st[0];
    sv->t = lv->st[1];
    sv->ci = rgb_mode ? SCREEN_VERTEX_CI_NONE : lv->ci;

    // Depth-cueing (CI mode): replace the vertex color with the lshaderange
    // ramp index for this vertex's depth. zw is window z in [0,1]; scale it
    // into lsetdepth units to compare against lshaderange's znear/zfar.
    // Vertices at shade_znear get highin (brightest), at shade_zfar lowin.
    if (depthcue_enabled && !rgb_mode) {
        float zscr = ls_znear + zw * (float)(ls_zfar - ls_znear);
        float t = (shade_zfar == shade_znear) ? 0.0f :
                  unitclamp((zscr - shade_znear) / (float)(shade_zfar - shade_znear));
        int index = (int)(shade_highin - t * (shade_highin - shade_lowin) + 0.5f);
        sv->ci = index;
        sv->r = colormap[index][0];
        sv->g = colormap[index][1];
        sv->b = colormap[index][2];
    }
}

enum {
    CLIP_ALL_IN = 0x00,
    CLIP_NEG_X = 0x01,
    CLIP_POS_X = 0x02,
    CLIP_NEG_Y = 0x04,
    CLIP_POS_Y = 0x08,
    CLIP_NEG_Z = 0x10,
    CLIP_POS_Z = 0x20,
};

#define CLIP_EPSILON .001

void plane_to_clip_params(int plane, int *sign, int *index)
{
    switch(plane) {
        case CLIP_NEG_X: *sign = -1; *index = 0; break;
        case CLIP_POS_X: *sign = 1; *index = 0; break;
        case CLIP_NEG_Y: *sign = -1; *index = 1; break;
        case CLIP_POS_Y: *sign = 1; *index = 1; break;
        case CLIP_NEG_Z: *sign = -1; *index = 2; break;
        case CLIP_POS_Z: *sign = 1; *index = 2; break;
    }
}

int clip_line_against_plane(int plane, lit_vertex *input, lit_vertex *output)
{
    int sign;
    int index;

    plane_to_clip_params(plane, &sign, &index);

    float p0 = input[0].coord[index] * sign;
    float p1 = input[1].coord[index] * sign;
    float w0 = input[0].coord[3];
    float w1 = input[1].coord[3];

    if(p0 > w0 && p1 > w1)
        return 0;

    int n = 0;

    if(p0 < w0) {
        output[n++] = input[0];
    }

    if((p0 < w0 && p1 >= w1) || (p0 >= w0 && p1 < w1)) {
        float denom = -p0 + p1 + w0 - w1;
        if(fabs(denom) > CLIP_EPSILON) {
            float t = (-p0 + w0) / denom;
            vec4f_blend(input[0].coord, input[1].coord, t, output[n].coord);
            // Should other attributes be hyperbolically interpolated?
            vec4f_blend(input[0].color, input[1].color, t, output[n].color);
            output[n].st[0] = input[0].st[0] + (input[1].st[0] - input[0].st[0]) * t;
            output[n].st[1] = input[0].st[1] + (input[1].st[1] - input[0].st[1]) * t;
            output[n].ci = input[0].ci; // CI is flat per primitive
            n++;
        }
    }

    if(p1 < w1) {
        output[n++] = input[1];
    }

    return 1;
}

int clip_polygon_against_plane(int plane, int n, lit_vertex *input, lit_vertex *output)
{
    int sign;
    int index;

    plane_to_clip_params(plane, &sign, &index);

    int n2 = 0;
    lit_vertex* v0;
    lit_vertex* v1 = &input[n - 1];

    for(int i = 0; i < n; i++) {
        v0 = v1;
        v1 = &input[i];

        float p0 = v0->coord[index] * sign;
        float p1 = v1->coord[index] * sign;
        float w0 = v0->coord[3];
        float w1 = v1->coord[3];

        if(p0 < w0) {
            output[n2++] = *v0;
        }

        if((p0 < w0 && p1 >= w1) || (p0 >= w0 && p1 < w1)) {
            float denom = -p0 + p1 + w0 - w1;
            if(fabs(denom) > CLIP_EPSILON) {
                float t = (-p0 + w0) / denom;
                vec4f_blend(v0->coord, v1->coord, t, output[n2].coord);
                // Should other attributes be hyperbolically interpolated?
                vec4f_blend(v0->color, v1->color, t, output[n2].color);
                output[n2].st[0] = v0->st[0] + (v1->st[0] - v0->st[0]) * t;
                output[n2].st[1] = v0->st[1] + (v1->st[1] - v0->st[1]) * t;
                output[n2].ci = v0->ci; // CI is flat per primitive
                n2++;
            }
        }
    }
    return n2;
}

int classify_vertex(float *c)
{
    int code = 0;
    if(c[0] < -c[3]) code |= CLIP_NEG_X;
    if(c[0] > c[3]) code |= CLIP_POS_X;
    if(c[1] < -c[3]) code |= CLIP_NEG_Y;
    if(c[1] > c[3]) code |= CLIP_POS_Y;
    if(c[2] < -c[3]) code |= CLIP_NEG_Z;
    if(c[2] > c[3]) code |= CLIP_POS_Z;
    return code;
}

enum {
    CLIP_TRIVIAL_REJECT = 0,
    CLIP_TRIVIAL_ACCEPT = -1, // If clip_polygon() returns this, it stored nothing in "output".
};

int clip_line(lit_vertex *input, lit_vertex *output)
{
    static int code[2];
    static lit_vertex tmp[2];
    int all_neg[3] = {1, 1, 1};
    int all_pos[3] = {1, 1, 1};
    int all_inside = 1;
    int all_outside_one = 0xff;

    for(int i = 0; i < 2; i++) {
        code[i] = classify_vertex(input[i].coord);
        all_inside = all_inside && (code[i] == CLIP_ALL_IN);
        all_outside_one &= code[i];
    }

    if(all_inside)
        return CLIP_TRIVIAL_ACCEPT;

    if(all_outside_one)
        return CLIP_TRIVIAL_REJECT;

    int n;

    n = clip_line_against_plane(CLIP_NEG_X, input, tmp);
    if(n == 0) return 0;
    n = clip_line_against_plane(CLIP_POS_X, tmp, output);
    if(n == 0) return 0;
    n = clip_line_against_plane(CLIP_NEG_Y, output, tmp);
    if(n == 0) return 0;
    n = clip_line_against_plane(CLIP_POS_Y, tmp, output);
    if(n == 0) return 0;
    n = clip_line_against_plane(CLIP_NEG_Z, output, tmp);
    if(n == 0) return 0;
    n = clip_line_against_plane(CLIP_POS_Z, tmp, output);

    return n;
}

#define POLY_MAX 512

int clip_polygon(int n, lit_vertex *input, lit_vertex *output)
{
    static int code[POLY_MAX];
    static lit_vertex tmp[POLY_MAX];
    int all_neg[3] = {1, 1, 1};
    int all_pos[3] = {1, 1, 1};
    int all_inside = 1;
    int all_outside_one = 0xff;

    for(int i = 0; i < n; i++) {
        code[i] = classify_vertex(input[i].coord);
        all_inside = all_inside && (code[i] == CLIP_ALL_IN);
        all_outside_one &= code[i];
    }

    if(all_inside)
        return CLIP_TRIVIAL_ACCEPT;

    if(all_outside_one)
        return CLIP_TRIVIAL_REJECT;

    n = clip_polygon_against_plane(CLIP_NEG_X, n, input, tmp);
    if(n == 0) return 0;
    n = clip_polygon_against_plane(CLIP_POS_X, n, tmp, output);
    if(n == 0) return 0;
    n = clip_polygon_against_plane(CLIP_NEG_Y, n, output, tmp);
    if(n == 0) return 0;
    n = clip_polygon_against_plane(CLIP_POS_Y, n, tmp, output);
    if(n == 0) return 0;
    n = clip_polygon_against_plane(CLIP_NEG_Z, n, output, tmp);
    if(n == 0) return 0;
    n = clip_polygon_against_plane(CLIP_POS_Z, n, tmp, output);

    return n;
}

void process_point(world_vertex *wv)
{
    static lit_vertex litvert;
    static screen_vertex screenvert;

    int save_lighting = lighting_enabled;
    lighting_enabled = 0;

    transform_and_light_vertex(wv, &litvert);

    if (classify_vertex(litvert.coord) == CLIP_ALL_IN) {
        project_vertex(&litvert, &screenvert);
        rasterizer_draw(DRAW_POINTS, 1, &screenvert);
    }

    lighting_enabled = save_lighting;
}

void process_line(world_vertex *wv0, world_vertex *wv1)
{
    static lit_vertex litverts[2], *vp;
    static lit_vertex clipped[2];
    static screen_vertex screenverts[2];

    transform_and_light_vertex(wv0, &litverts[0]);
    transform_and_light_vertex(wv1, &litverts[1]);

    int r = clip_line(litverts, clipped);
    if(r == CLIP_TRIVIAL_REJECT)
        return;
    else if(r == CLIP_TRIVIAL_ACCEPT) {
        vp = litverts;
    } else {
        vp = clipped;
    }

    project_vertex(&vp[0], &screenverts[0]);
    project_vertex(&vp[1], &screenverts[1]);

    // smoothline (CI mode): stand in for the hardware's coverage-added
    // index by drawing with the brightest entry of the vertex's 16-entry
    // intensity ramp (see smoothline_enabled). Composes with depthcue,
    // which selects the ramp by depth in project_vertex.
    if (smoothline_enabled && !rgb_mode) {
        for (int i = 0; i < 2; i++) {
            if (screenverts[i].ci == SCREEN_VERTEX_CI_NONE)
                continue;
            int index = screenverts[i].ci | 15;
            screenverts[i].ci = index;
            screenverts[i].r = colormap[index][0];
            screenverts[i].g = colormap[index][1];
            screenverts[i].b = colormap[index][2];
        }
    }

    rasterizer_draw(DRAW_LINES, 2, screenverts);
}

static int backface_cull(const screen_vertex* s)
{
    float area =
        /* .5 * */ // Don't bother multiplying by .5, only checking the sign.
        s[0].x * s[1].y - s[1].x * s[0].y +
        s[1].x * s[2].y - s[2].x * s[1].y +
        s[2].x * s[0].y - s[0].x * s[2].y;
    return (area < 0);
}

void process_tmesh(int n, world_vertex *worldverts)
{
    int ccw = 1;

    static lit_vertex litverts[POLY_MAX];

    for(int i = 0; i < n; i++)
        transform_and_light_vertex(&worldverts[i], &litverts[i]);

    for(int j = 0; j < n - 2; j++) {
        static lit_vertex clipped[POLY_MAX];
        static lit_vertex *vp;
        static screen_vertex screenverts[POLY_MAX];

        // Clip the next triangle, potentially making a polygon
        int r = clip_polygon(3, litverts + j, clipped);
        if(r != CLIP_TRIVIAL_REJECT) {
	    if(r == CLIP_TRIVIAL_ACCEPT) {
		vp = litverts + j;
		r = 3;
	    } else {
		vp = clipped;
	    }

	    for(int i = 0; i < r; i++)
		project_vertex(&vp[i], &screenverts[i]);

	    // XXX break into a single draw of TRIANGLES instead of a single function call per triangle:
	    static screen_vertex triangle[3];
	    triangle[0] = screenverts[0];

	    for(int i = 0; i < r - 2; i++) {
		triangle[1] = screenverts[i + 1];
		triangle[2] = screenverts[i + 2];
		if(!backface_enabled || (ccw ^ !backface_cull(triangle)))
		    rasterizer_draw(DRAW_TRIANGLES, 3, triangle);
	    }
	}
	ccw = !ccw;
    }
}

// XXX rasterizer_draw() make into TRIANGLES
void process_polygon(int n, world_vertex *worldverts)
{
    static lit_vertex litverts[POLY_MAX];
    static lit_vertex clipped[POLY_MAX];
    static lit_vertex *vp;
    static screen_vertex screenverts[POLY_MAX];

    // early return when building display list
    if (n == 0)
        return;

    for(int i = 0; i < n; i++)
        transform_and_light_vertex(&worldverts[i], &litverts[i]);

    int r = clip_polygon(n, litverts, clipped);
    if(r == CLIP_TRIVIAL_REJECT)
        return;
    else if(r == CLIP_TRIVIAL_ACCEPT) {
        vp = litverts;
    } else {
        vp = clipped;
        n = r;
    }

    for(int i = 0; i < n; i++)
        project_vertex(&vp[i], &screenverts[i]);

    // XXX break into a single draw of TRIANGLES instead of a single function call per triangle:
    static screen_vertex triangle[3];
    triangle[0] = screenverts[0];

    for(int i = 0; i < n - 2; i++) {
        triangle[1] = screenverts[i + 1];
        triangle[2] = screenverts[i + 2];
	    if(!backface_enabled || !backface_cull(triangle))
            rasterizer_draw(DRAW_TRIANGLES, 3, triangle);
    }
}

//------------------------------------------------------------------------
// Popup menus ("pup" in GL lingo)

#define MAX_PUPS 16
#define MAX_PUP_ITEMS 16

typedef struct { Icoord x, y; } Icoord2;
typedef struct { Icoord left, top, right, bottom; } IcoordRect; // Y-up: top > bottom

// %f/%F callbacks are invoked with NO arguments even though IRIS GL passed
// the item value: the vintage demos that use them define K&R functions with
// an empty parameter list (newave's normal_mode() etc.), and on WebAssembly
// an indirect call must match the callee's exact signature — passing an
// argument to a zero-arg function is a runtime trap there, while ignoring
// extra args was harmless on MIPS. No demo in this corpus reads the value.
typedef int (*pup_func)(void);

typedef struct pup_item {
    char *label;
    int value;
    int submenu;
    pup_func func;
} pup_item;

typedef struct pup {
    int defd;
    char *title;
    pup_func func;
    int item_count;
    struct pup_item items[MAX_PUP_ITEMS];
} pup;
static struct pup pups[MAX_PUPS];

// Font used by pup rendering. Two parallel options:
//  - BMP - built-in bitmap font (font_bits / rasterizer_bitmap).
//  - BDF (authentic 1-bit X11 Helvetica Oblique bitmap), for pixel-exact
//    historic fidelity; chunky aliased edges like the original SGI menus.
typedef enum { PUP_FONT_BMP, PUP_FONT_BDF } pup_font_mode_t;
static pup_font_mode_t pup_font_mode = PUP_FONT_BDF;
static const BdfFont *pup_bdffont = NULL;
static int pup_use_bdf(void) {
    return pup_font_mode == PUP_FONT_BDF && pup_bdffont != NULL;
}

void pup_init(pup *menu)
{
    menu->defd = 0;
    menu->title = NULL;
    menu->func = NULL;
    menu->item_count = 0;
}

void pup_free(pup *menu)
{
    if(menu->title != NULL) {
        free(menu->title);
    }
    for(int i = 0; i < menu->item_count; i++) {
        pup_item *item = menu->items + i;
        if(item->label != NULL) {
            free(item->label);
        }
    }
    pup_init(menu);
}

void pup_set_title(pup *menu, char *title)
{
    if(menu->title != NULL) {
        free(menu->title);
    }
    menu->title = NULL;
    if(title != NULL) {
        menu->title = strdup(title);
    }
}

void pup_add(pup *menu, char *label, int value, int submenu, pup_func func)
{
    pup_item *item = menu->items + menu->item_count++;

    if(label != NULL)
        item->label = strdup(label);
    else
        item->label = NULL;
    item->value = value;
    item->submenu = submenu;
    item->func = func;
}

// Parse a defpup/addtopup menu string. ap supplies the varargs that %f, %F
// and %m consume, in order of appearance (IRIS GL semantics).
static void pup_parse_string(pup *thepup, const char *menu, va_list ap)
{
    char *menu2 = strdup(menu);
    char *menu3 = menu2;
    int nextvalue = thepup->item_count + 1;

    while(menu3) {
        char *item = strsep(&menu3, "|");
        int is_title = 0;
        pup_func func = NULL;
        int value = -1;
        int submenu = -1;

        char *p = item;
        while(*p) {
            while(*p && *p != '%')
                p++;

            char *w = p;
            while(w >= item && *w == ' ')
                *w-- = '\0';

            if(*p == '\0')          // no flag found; done with this item
                break;

            *p++ = '\0';            // terminate label, step past '%'

            if(*p == 't') {
                is_title = 1;
                pup_set_title(thepup, item);
            } else if(*p == 'F') {
                // menu-wide function, run on any selection (after any %f)
                thepup->func = va_arg(ap, pup_func);
            } else if(*p == 'f') {
                // per-item function, run when the item is selected; its
                // return value becomes dopup's result
                func = va_arg(ap, pup_func);
            } else if(*p == 'n') {
                printf("addtopup/defpup argument %%n ignored\n");
            } else if(*p == 'm') {
                printf("addtopup/defpup argument %%m ignored\n");
                submenu = (int)va_arg(ap, long); // consume to keep later args aligned
            } else if(*p == 'l') {
                /* %l: underline/separator — not yet rendered */
            } else if(*p == 'x') {
                value = 0;
                p++;
                while(*p >= '0' && *p <= '9') {   // was: *p <= 9  (tab) — broke %x
                    value = value * 10 + (*p - '0');
                    p++;
                }
                continue;           // p already advanced past digits
            }
            p++;
        }

        if(!is_title) {
            if(value == -1)
                value = nextvalue++;
            pup_add(thepup, item, value, submenu, func);
        }
    }

    free(menu2);
}

int menu_corner_top = YMAXSCREEN - 1 - 10; // refreshed by gl_framebuffer_resized
int menu_corner_left = 10;
// Horizontal text insets, in pixels. Left is from the fill's left edge to the
// text pen origin; right is from the widest label's pen advance to the fill's
// right edge. Separate so the left can be tighter than the right (per the SGI
// reference). Vertical layout is anchor-based, so these are horizontal only.
const int menu_pad_left  = 5;
const int menu_pad_right = 9;
// Vertical gap between the bottom of the title FILL rect and the top of the
// items FILL rect, in pixels. (The outline-to-outline placement below backs
// out the two bevels so this fill-to-fill figure is exact.)
const int menu_items_gap = 10;

// Beveled "3D lit" menu frame. Light from upper-left: top/left edges use the
// highlight color, bottom/right edges use the shadow color. menu_bevel is the
// frame thickness in pixels on each side. Tune the grays by eye.
const int menu_bevel = 2;
const int menu_face_r = 165, menu_face_g = 165, menu_face_b = 165;   // title fill
const int menu_hilite_r = 230, menu_hilite_g = 230, menu_hilite_b = 230; // top/left bevel
const int menu_shadow_r = 96,  menu_shadow_g = 96,  menu_shadow_b = 96;  // bottom/right bevel
// Items pane fill: lighter than the title (menu_face) but darker than the
// selected-row highlight (menu_select). Three tiers, lightening downward.
const int menu_items_face_r = 205, menu_items_face_g = 205, menu_items_face_b = 205;
// Selected item: bright fill with dark text (a "lit" row), per the SGI refs.
const int menu_select_r = 245, menu_select_g = 245, menu_select_b = 245;

// Title pane geometry, set to match the reference exactly: the title fill is
// a fixed height, and the title baseline sits a fixed number of pixels up
// from the bottom of that fill (rather than being derived from padding +
// line height like the items area).
const int menu_title_fill_height = 24;  // title fill box height in pixels
const int menu_title_text_up     = 7;   // baseline, pixels up from fill bottom

// Item rows are spaced this many pixels baseline-to-baseline. (The row pitch;
// must be >= pup_line_height() or rows would overlap.) The items-box height
// and the per-row advance both derive from this so they can't desync.
const int menu_item_pitch = 22;
// Baseline of the FIRST item row, measured in pixels down from the top of the
// items fill rectangle. Subsequent rows step down by menu_item_pitch.
const int menu_items_text_down = 17;
// Gap in pixels from the LAST item row's baseline down to the bottom of the
// items fill rectangle. Together with menu_items_text_down and menu_item_pitch
// this fully determines the items fill height.
const int menu_items_text_bottom = 7;

static int str_width_in_pixels(const char *str) {
    int width = 0;

    if (pup_use_bdf())
        width = bdf_string_width(pup_bdffont, str);
    else {
        for(int i = 0; i < strlen(str); i++) {
            if (str[i] == '\t') {
                width += font_width * 8;
            } else {
                width += font_width;
            }
        }
    }

    return width;
}

void string_draw(screen_vertex* screenvert_, const char *str) {
    // Default text font: the recovered IRIX 3 system screen font (IRIS GL
    // font 0) — the actual bitmap font charstr() drew through on the real
    // machines, unless a demo loaded its own. 9x15 charcell, fixed 9px
    // pitch, ascent 13 / descent 2. Replaces the X11 Misc-Fixed 9x15
    // stand-in that was chosen as a metric-matched guess for exactly this.
    static screen_vertex screenvert;

    screenvert = *screenvert_;

    for(int i = 0; i < strlen(str); i++) {
        if (str[i] == '\t') {
            // I don't know whether the original charstr() supported tabs (I can't find
            // a man page), but arena/startup.c uses them. --LK
            screenvert.x += 9 * SCREEN_VERTEX_V2_SCALE * 8;
        } else {
            char one[2] = { str[i], 0 };
            bdf_render_string(&irisfont0, &screenvert, one);
            screenvert.x += 9 * SCREEN_VERTEX_V2_SCALE;
        }
    }
}

// XXX rasterizer_draw() enqueue triangles
void draw_screen_aarect_filled(int r, int g, int b, IcoordRect rect)
{
    screen_vertex q[4];

    for(int i = 0; i < 4; i++)
        screen_vertex_set_color(&q[i], r, g, b, 255);

    screen_vertex_set_position(&q[0], rect.left,  rect.bottom);
    screen_vertex_set_position(&q[1], rect.right, rect.bottom);
    screen_vertex_set_position(&q[2], rect.right, rect.top);
    screen_vertex_set_position(&q[3], rect.left,  rect.top);

    // XXX break into a single draw of TRIANGLES instead of a single function call per triangle:
    static screen_vertex triangle[3];
    triangle[0] = q[0];

    for(int i = 0; i < 2; i++) {
        triangle[1] = q[i + 1];
        triangle[2] = q[i + 2];
	    if(!backface_enabled || !backface_cull(triangle))
            rasterizer_draw(DRAW_TRIANGLES, 3, triangle);
    }
}

// XXX rasterizer_draw() enqueue triangles
void draw_screen_aarect_outline(int r, int g, int b, IcoordRect rect)
{
    // draw four sides as four 1-pixel wide filled rects
    draw_screen_aarect_filled(r, g, b, (IcoordRect){rect.left,      rect.top,       rect.left + 1,  rect.bottom });
    draw_screen_aarect_filled(r, g, b, (IcoordRect){rect.right - 1, rect.top,       rect.right,     rect.bottom });
    draw_screen_aarect_filled(r, g, b, (IcoordRect){rect.left,      rect.top,       rect.right,     rect.top - 1 });
    draw_screen_aarect_filled(r, g, b, (IcoordRect){rect.left,      rect.bottom + 1, rect.right,    rect.bottom });
}

// Draw a beveled ("3D lit") frame around `rect`, `thickness` pixels wide on
// each side, then fill the interior. The light comes from the upper-left:
// the top and left edges get the highlight color, the bottom and right edges
// get the shadow color. Pass highlight lighter than fill and shadow darker
// than fill for a raised look; swap them for an inset/sunken look.
//
// Drawn as filled rects following the IcoordRect {left,top,right,bottom}
// (Y-up, top > bottom) convention used by the other helpers. The top-left
// highlight owns the top-left corner; the bottom-right shadow owns the
// bottom-right corner (the diagonal split is the conventional bevel look).
// Fill a single triangle in screen space (three Icoord2 corners).
static void draw_screen_aatri(int r, int g, int b,
                              Icoord2 a, Icoord2 c, Icoord2 d)
{
    screen_vertex tri[3];
    screen_vertex_set_color(&tri[0], r, g, b, 255);
    screen_vertex_set_color(&tri[1], r, g, b, 255);
    screen_vertex_set_color(&tri[2], r, g, b, 255);
    screen_vertex_set_position(&tri[0], a.x, a.y);
    screen_vertex_set_position(&tri[1], c.x, c.y);
    screen_vertex_set_position(&tri[2], d.x, d.y);
    if(!backface_enabled || !backface_cull(tri))
        rasterizer_draw(DRAW_TRIANGLES, 3, tri);
}

static void draw_screen_aabevel(IcoordRect rect, int thickness,
                                int hi_r, int hi_g, int hi_b,
                                int sh_r, int sh_g, int sh_b,
                                int fill_r, int fill_g, int fill_b)
{
    // Top edge (full width) and left edge (full height): highlight.
    draw_screen_aarect_filled(hi_r, hi_g, hi_b,
        (IcoordRect){ rect.left, rect.top, rect.right, rect.top - thickness });
    draw_screen_aarect_filled(hi_r, hi_g, hi_b,
        (IcoordRect){ rect.left, rect.top, rect.left + thickness, rect.bottom });

    // Bottom edge (full width) and right edge (full height): shadow.
    draw_screen_aarect_filled(sh_r, sh_g, sh_b,
        (IcoordRect){ rect.left, rect.bottom + thickness, rect.right, rect.bottom });
    draw_screen_aarect_filled(sh_r, sh_g, sh_b,
        (IcoordRect){ rect.right - thickness, rect.top, rect.right, rect.bottom });

    // Interior fill, inset by thickness on all sides.
    draw_screen_aarect_filled(fill_r, fill_g, fill_b,
        (IcoordRect){ rect.left + thickness, rect.top - thickness,
                      rect.right - thickness, rect.bottom + thickness });

    // The two "mixed" corners (lower-left and upper-right) currently have one
    // color squared off over the whole corner square. Redraw each as a
    // diagonal split: the edge along that corner keeps its color on its side
    // of the 45-degree miter, the perpendicular edge gets the other triangle.
    int t = thickness;

    // Lower-left: diagonal from outer (left,bottom) to inner (left+t,bottom+t).
    //  upper-left triangle -> highlight (left edge); lower-right -> shadow (bottom edge).
    //  Vertices wound to match draw_screen_aarect_filled (positive area) so
    //  they survive backface culling if an app enables it.
    draw_screen_aatri(hi_r, hi_g, hi_b,
        (Icoord2){ rect.left,     rect.bottom     },
        (Icoord2){ rect.left + t, rect.bottom + t },
        (Icoord2){ rect.left,     rect.bottom + t });
    draw_screen_aatri(sh_r, sh_g, sh_b,
        (Icoord2){ rect.left,     rect.bottom     },
        (Icoord2){ rect.left + t, rect.bottom     },
        (Icoord2){ rect.left + t, rect.bottom + t });

    // Upper-right: diagonal from outer (right,top) to inner (right-t,top-t).
    //  lower-right triangle -> shadow (right edge); upper-left -> highlight (top edge).
    draw_screen_aatri(sh_r, sh_g, sh_b,
        (Icoord2){ rect.right,     rect.top     },
        (Icoord2){ rect.right - t, rect.top - t },
        (Icoord2){ rect.right,     rect.top - t });
    draw_screen_aatri(hi_r, hi_g, hi_b,
        (Icoord2){ rect.right,     rect.top     },
        (Icoord2){ rect.right - t, rect.top     },
        (Icoord2){ rect.right - t, rect.top - t });
}

void draw_screen_string(int r, int g, int b, Icoord2 origin, const char *str) {
    screen_vertex sv;
    screen_vertex_set_color(&sv, r, g, b, 255);
    screen_vertex_set_position(&sv, origin.x, origin.y);
    string_draw(&sv, str);
}

typedef struct pup_layout {
    // Title pane
    IcoordRect title_outline;
    IcoordRect title_fill;
    Icoord2    title_pane;     // top-left text origin

    // Items pane
    IcoordRect items_outline;
    IcoordRect items_fill;
    Icoord2    items_pane;     // top-left text origin

    // Per-item row pitch (= menu_item_pitch, baseline-to-baseline), used both
    // for advancing rows when drawing and for hit-testing the cursor against
    // item slots.
    int item_slot_height;
} pup_layout;

// Returns the line height in pixels (full ascent + descent) of the
// current pup font.
static int pup_line_height(void) {
    if (pup_use_bdf())
        return pup_bdffont->ascent + pup_bdffont->descent;
    else
        return font_height;
}

// Draws str with the current pup font. The (x, y) point is the baseline-
// equivalent origin: for the bitmap font, it's the bottom-left of the
// glyph block (which has no separate baseline / descender). The BDF
// path uses rasterizer_bitmap (same primitive as draw_screen_string), so
// it takes the baseline origin directly, no Y-flip.
static void pup_draw_string(int r, int g, int b, Icoord2 baseline, const char *str) {
    if (pup_use_bdf()) {
        screen_vertex sv;
        screen_vertex_set_color(&sv, r, g, b, 255);
        screen_vertex_set_position(&sv, baseline.x, baseline.y);
        bdf_render_string(pup_bdffont, &sv, str);
    } else {
        draw_screen_string(r, g, b, baseline, str);
    }
}

static void pup_compute_layout(pup *menu, int menu_left, int menu_top, pup_layout *layout)
{
    int menu_text_pane_width = 0;
    int line_height = pup_line_height();

    // Title width (the title fill height is fixed: menu_title_fill_height).
    int has_title = (menu->title != NULL);
    if (has_title)
        menu_text_pane_width = str_width_in_pixels(menu->title);

    // Size of items area. The fill height is fully determined by the explicit
    // anchors: menu_items_text_down (fill top -> first baseline) + (N-1) row
    // pitches (first -> last baseline) + menu_items_text_bottom (last baseline
    // -> fill bottom).
    int items_text_pane_height = 0;
    for (int i = 0; i < menu->item_count; i++) {
        int w = str_width_in_pixels(menu->items[i].label);
        if (w > menu_text_pane_width)
            menu_text_pane_width = w;
    }
    if (menu->item_count > 0)
        items_text_pane_height = menu_items_text_down
                               + (menu->item_count - 1) * menu_item_pitch
                               + menu_items_text_bottom;

    int title_fill_width  = menu_pad_left + menu_text_pane_width + menu_pad_right;
    int title_fill_height = menu_title_fill_height;

    if (has_title) {
        layout->title_outline = (IcoordRect){
            menu_left,
            menu_top,
            menu_left + 2 * menu_bevel + title_fill_width,
            menu_top  - 2 * menu_bevel - title_fill_height
        };
        layout->title_fill = (IcoordRect){
            layout->title_outline.left   + menu_bevel,
            layout->title_outline.top    - menu_bevel,
            layout->title_outline.right  - menu_bevel,
            layout->title_outline.bottom + menu_bevel
        };
        layout->title_pane = (Icoord2){
            layout->title_fill.left + menu_pad_left,
            // Chosen so that (title_pane.y - line_height), the baseline used at
            // the draw site, sits menu_title_text_up pixels above the fill bottom.
            layout->title_fill.bottom + menu_title_text_up + line_height
        };
    } else {
        // No title: collapse the title pane to a zero-area point at the top-
        // left corner. It contributes nothing to the menu extents (which read
        // title_outline.top/.left), and the items pane starts at menu_top.
        layout->title_outline = (IcoordRect){ menu_left, menu_top, menu_left, menu_top };
        layout->title_fill    = layout->title_outline;
        layout->title_pane    = (Icoord2){ menu_left, menu_top };
    }

    int items_fill_width  = menu_pad_left + menu_text_pane_width + menu_pad_right;
    // Height already includes the top/bottom baseline gaps via the anchors.
    int items_fill_height = items_text_pane_height;

    // menu_items_gap is the fill-to-fill gap. Each fill is inset from its
    // outline by menu_bevel, so the outline-to-outline distance is the desired
    // fill gap minus the two bevels that sit between the fills. With no title,
    // the items pane begins right at the top-left corner.
    int items_outline_top = has_title
        ? layout->title_outline.bottom - (menu_items_gap - 2 * menu_bevel)
        : menu_top;
    layout->items_outline = (IcoordRect){
        menu_left,
        items_outline_top,
        menu_left + 2 * menu_bevel + items_fill_width,
        items_outline_top - 2 * menu_bevel - items_fill_height
    };
    layout->items_fill = (IcoordRect){
        layout->items_outline.left   + menu_bevel,
        layout->items_outline.top    - menu_bevel,
        layout->items_outline.right  - menu_bevel,
        layout->items_outline.bottom + menu_bevel
    };
    layout->items_pane = (Icoord2){
        layout->items_fill.left + menu_pad_left,
        // Chosen so that (items_pane.y - line_height), the first row's baseline
        // at the draw site, sits menu_items_text_down pixels below fill top.
        layout->items_fill.top - menu_items_text_down + line_height
    };

    layout->item_slot_height = menu_item_pitch;
}

// Place the menu's upper-left corner at the cursor, then nudge it left
// and/or up so the whole menu stays inside the framebuffer. The menu's
// pixel extents are independent of the anchor (every layout coord is just
// anchor +/- a constant), so probe a layout at the origin to measure them.
void pup_menu_topleft_corner_from_mouse(pup *thepup)
{
    pup_layout probe;
    pup_compute_layout(thepup, 0, 0, &probe);
    int menu_w = probe.items_outline.right - probe.title_outline.left;
    int menu_h = probe.title_outline.top   - probe.items_outline.bottom;

    int menu_left = getvaluator(MOUSEX);   // upper-left X at cursor
    int menu_top  = getvaluator(MOUSEY);   // upper-left Y at cursor (Y-up)

    // Right edge can't pass the screen; if it would, slide left. If the
    // menu is wider than the screen, pin it to the left edge.
    if (menu_left + menu_w > DISPLAY_WIDTH - 1) menu_left = DISPLAY_WIDTH - 1 - menu_w;
    if (menu_left < 0) menu_left = 0;

    // Bottom edge (menu_top - menu_h) can't drop below 0; if it would,
    // slide up. If the menu is taller than the screen, pin it to the top.
    if (menu_top - menu_h < 0) menu_top = menu_h;
    if (menu_top > DISPLAY_HEIGHT - 1) menu_top = DISPLAY_HEIGHT - 1;

    menu_corner_left = menu_left;
    menu_corner_top = menu_top;
}

// Returns the index 0..item_count-1 of the item slot at screen coords
// `pt`, or -1 if `pt` is not over any item slot (i.e. outside the items
// pane, in the bottom padding past the last item, etc.).
static int pup_item_at(pup *menu, const pup_layout *layout, Icoord2 pt)
{
    if (pt.x < layout->items_outline.left   || pt.x > layout->items_outline.right ||
        pt.y < layout->items_outline.bottom || pt.y > layout->items_outline.top)
        return -1;
    int dy = layout->items_pane.y - pt.y;
    if (dy < 0) return -1;
    int idx = dy / layout->item_slot_height;
    if (idx < 0 || idx >= menu->item_count) return -1;
    return idx;
}

void pup_draw(pup *menu, int menu_left, int menu_top, int selected)
{
    pup_layout layout;
    pup_compute_layout(menu, menu_left, menu_top, &layout);
    int line_height = pup_line_height();

    // draw title: beveled raised frame + title string (only when present)
    if (menu->title) {
        draw_screen_aabevel(layout.title_outline, menu_bevel,
                            menu_hilite_r, menu_hilite_g, menu_hilite_b,
                            menu_shadow_r, menu_shadow_g, menu_shadow_b,
                            menu_face_r, menu_face_g, menu_face_b);
        pup_draw_string(0, 0, 0,
            (Icoord2){ layout.title_pane.x, layout.title_pane.y - line_height }, menu->title);
    }

    // draw items: beveled raised frame + item strings
    draw_screen_aabevel(layout.items_outline, menu_bevel,
                        menu_hilite_r, menu_hilite_g, menu_hilite_b,
                        menu_shadow_r, menu_shadow_g, menu_shadow_b,
                        menu_items_face_r, menu_items_face_g, menu_items_face_b);
    int item_top = layout.items_pane.y;
    for (int i = 0; i < menu->item_count; i++) {
        if (i == selected) {
            // Selected row: bright "lit" fill with dark text. The highlight
            // rect is nudged vertically (menu_select_dy, screen-space Y-up so
            // negative = down) to sit centered on the glyphs; the text origin
            // is left unchanged.
            const int menu_select_dy = -3;
            int hl_bottom = item_top - line_height - 2 + menu_select_dy;
            draw_screen_aarect_filled(menu_select_r, menu_select_g, menu_select_b,
                (IcoordRect){
                    layout.items_fill.left  + 1,
                    item_top + 2 + menu_select_dy,
                    layout.items_fill.right - 1,
                    hl_bottom,
                });
            // Dark rule along the bottom edge of the highlight (shadow gray).
            draw_screen_aarect_filled(menu_shadow_r, menu_shadow_g, menu_shadow_b,
                (IcoordRect){
                    layout.items_fill.left  + 1,
                    hl_bottom + 1,
                    layout.items_fill.right - 1,
                    hl_bottom,
                });
            pup_draw_string(0, 0, 0,
                (Icoord2){ layout.items_pane.x, item_top - line_height }, menu->items[i].label);
        }
        else
            pup_draw_string(0, 0, 0,
                (Icoord2){ layout.items_pane.x, item_top - line_height }, menu->items[i].label);
        item_top -= layout.item_slot_height;
    }
}

//----------------------------------------------------------------------------
// Display list ("Object" and "Tag") management

/*
implementing a display-listable function:
    add to enum in struct dl_element
    if parameters, add new struct to union
    if needed, add free()/dtor in element_free()
    in callobj, add case entry with actual call
    in function, add preamble like one in rotate()
*/

typedef struct dl_element
{
    enum object_type
    {
        SETPATTERN,
        DRAW,
        MOVE,
        TAG,
        CALLOBJ,
        COLOR,
        PNT,
        POLF,
        POLY,
        CLEAR,
        CIRCI,
        PUSHMATRIX,
        POPMATRIX,
        PUSHVIEWPORT,
        POPVIEWPORT,
        ROTATE,
        TRANSLATE,
        SCALE,
        MULTMATRIX,
        LOOKAT,
        LOADMATRIX,
        PERSPECTIVE,
        WINDOW,
        ORTHO2,
        VIEWPORT,
        RGBCOLOR,
        BGNPOLYGON,
        ENDPOLYGON,
        BGNLINE,
        ENDLINE,
        BGNCLOSEDLINE,
        ENDCLOSEDLINE,
        BGNTMESH,
        ENDTMESH,
        BGNPOINT,
        ENDPOINT,
        C3F,
        C3I,
        N3F,
        V4F,
        MMODE,
        LMBIND,
        CMOV2I,
        CHARSTR,
        WRITEMASK,
    } type;

    union
    {
        struct {
            int pattern;
        } setpattern;

        struct {
            Coord x, y, z;
        } draw;

        struct {
            Coord x, y, z;
        } move;

        struct {
            Coord left, right, bottom, top;
        } ortho2;

        struct {
            char *str;
        } charstr;

        struct {
            Icoord x, y;
        } cmov2i;

        struct {
            Icoord x, y, r;
        } circi;

        struct {
            int target;
            int index;
        } lmbind;

        struct {
            int mode;
        } mmode;

        struct {
            float v[4];
        } v4f;

        struct {
            float n[3];
        } n3f;

        struct {
            int c[3];
        } c3i;

        struct {
            float c[3];
        } c3f;

        struct {
            int r, g, b;
        } rgbcolor;

        struct {
            Tag tag;
        } tag;

        struct {
            Object obj;
        } callobj;

        struct {
            Colorindex mask;
        } writemask;

        struct {
            Colorindex color;
        } color;

        struct {
            Coord x, y, z;
        } pnt;

        struct {
            int n;
            Coord (*p)[3];
        } poly;

        struct {
            int n;
            Coord (*parray)[3];
        } polf;

        struct {
            Angle angle;
            char axis;
        } rotate;

        struct {
            Coord x, y, z;
        } scale;

        struct {
            Coord x, y, z;
        } translate;

        struct {
            Coord viewx;
            Coord viewy;
            Coord viewz;
            Coord pointx;
            Coord pointy;
            Coord pointz;
            Angle twist;
        } lookat;

        struct {
            Matrix m;
        } multmatrix;

        struct {
            Matrix m;
        } loadmatrix;

        struct {
            Angle fovy;
            float aspect;
            Coord near, far;
        } perspective;

        struct {
            Coord left, right;
            Coord bottom, top;
            Coord near, far;
        } window;

        struct {
            Screencoord left, right;
            Screencoord bottom, top;
        } viewport;
    };

    struct dl_element *next;
} dl_element;

#define OBJ_MAX 2048
unsigned char object_allocation[OBJ_MAX];
dl_element *objects[OBJ_MAX];
unsigned char tag_allocation[OBJ_MAX];
dl_element **ptrs_to_tagptrs[OBJ_MAX];
dl_element **cur_ptr_to_nextptr;
int replace_mode;

dl_element *element_new()
{
    dl_element *e = malloc(sizeof(dl_element));
    return e;
}

void element_insert(dl_element ***ptr_to_nextptr, dl_element *n)
{
    n->next = **ptr_to_nextptr;
    **ptr_to_nextptr = n;
    *ptr_to_nextptr = &n->next;
}

void element_free(dl_element *p)
{
    while(p != NULL) {
        switch(p->type) {
            case TAG:
                tag_allocation[p->tag.tag] = 0;
                ptrs_to_tagptrs[p->tag.tag] = NULL;
                break;
            case POLY:
                free(p->poly.p);
                break;
            case POLF:
                free(p->polf.parray);
                break;
            case CHARSTR:
                free(p->charstr.str);
                break;
            default:
                break;
        }
        dl_element *np = p->next;
        free(p);
        p = np;
    }
}

dl_element *element_next_in_object(enum object_type t)
{
    dl_element *e;

    if(!replace_mode) {
        e = element_new();
        element_insert(&cur_ptr_to_nextptr, e);
        // XXX Need to skip tags?
    } else {
        e = *cur_ptr_to_nextptr;
        cur_ptr_to_nextptr = &(*cur_ptr_to_nextptr)->next;
    }
    e->type = t;

    return e;
}

static enum object_type bgn_object_type;

//----------------------------------------------------------------------------
// GL API calls

void callobj(Object obj) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(CALLOBJ);
        e->callobj.obj = obj;
        return;
    }

    TRACEF("%d", obj);

    trace_indent += 4;
    dl_element *p = objects[obj];
    while(p) {
        switch(p->type) {
            case DRAW:
                draw(p->draw.x, p->draw.y, p->draw.z);
                break;
            case MOVE:
                move(p->move.x, p->move.y, p->move.z);
                break;
            case LMBIND:
                lmbind(p->lmbind.target, p->lmbind.index);
                break;
            case MMODE:
                mmode(p->mmode.mode);
                break;
            case V4F:
                v4f(p->v4f.v);
                break;
            case C3I:
                c3i(p->c3i.c);
                break;
            case C3F:
                c3f(p->c3f.c);
                break;
            case N3F:
                n3f(p->n3f.n);
                break;
            case ENDPOLYGON:
                endpolygon();
                break;
            case BGNPOLYGON:
                bgnpolygon();
                break;
            case ENDTMESH:
                endtmesh();
                break;
            case BGNTMESH:
                bgntmesh();
                break;
            case ENDLINE:
                endline();
                break;
            case BGNLINE:
                bgnline();
                break;
            case ENDCLOSEDLINE:
                endclosedline();
                break;
            case BGNCLOSEDLINE:
                bgnclosedline();
                break;
            case ENDPOINT:
                endpoint();
                break;
            case BGNPOINT:
                bgnpoint();
                break;
            case RGBCOLOR:
                RGBcolor(
                    p->rgbcolor.r,
                    p->rgbcolor.g,
                    p->rgbcolor.b
                );
                break;
            case VIEWPORT:
                viewport(
                    p->viewport.left,
                    p->viewport.right,
                    p->viewport.bottom,
                    p->viewport.top
                );
                break;
            case ORTHO2:
                ortho2(
                    p->ortho2.left,
                    p->ortho2.right,
                    p->ortho2.bottom,
                    p->ortho2.top);
                break;
            case WINDOW:
                window(
                    p->window.left,
                    p->window.right,
                    p->window.bottom,
                    p->window.top,
                    p->window.near,
                    p->window.far
                );
                break;
            case PERSPECTIVE:
                perspective(
                    p->perspective.fovy,
                    p->perspective.aspect,
                    p->perspective.near,
                    p->perspective.far
                );
                break;
            case POPMATRIX:
                popmatrix();
                break;
            case POPVIEWPORT:
                popviewport();
                break;
            case CIRCI:
                circi(p->circi.x, p->circi.y, p->circi.r);
                break;
            case CLEAR:
                clear();
                break;
            case PUSHMATRIX:
                pushmatrix();
                break;
            case PUSHVIEWPORT:
                pushviewport();
                break;
            case LOADMATRIX:
                loadmatrix(p->loadmatrix.m);
                break;
            case LOOKAT:
                lookat(
                    p->lookat.viewx,
                    p->lookat.viewy,
                    p->lookat.viewz,
                    p->lookat.pointx,
                    p->lookat.pointy,
                    p->lookat.pointz,
                    p->lookat.twist
                );
                break;
            case MULTMATRIX:
                multmatrix(p->multmatrix.m);
                break;
            case TRANSLATE:
                translate(p->translate.x, p->translate.y, p->translate.z);
                break;
            case SCALE:
                scale(p->scale.x, p->scale.y, p->scale.z);
                break;
            case ROTATE:
                rotate(p->rotate.angle, p->rotate.axis);
                break;
            case PNT:
                pnt(p->pnt.x, p->pnt.y, p->pnt.z);
                break;
            case POLY:
                poly(p->poly.n, p->poly.p);
                break;
            case POLF:
                polf(p->polf.n, p->polf.parray);
                break;
            case COLOR:
                color(p->color.color);
                break;
            case SETPATTERN:
                setpattern(p->setpattern.pattern);
                break;
            case CALLOBJ:
                callobj(p->callobj.obj);
                break;
            case CHARSTR:
                charstr(p->charstr.str);
                break;
            case WRITEMASK:
                writemask(p->writemask.mask);
                break;
            case CMOV2I:
                cmov2i(p->cmov2i.x, p->cmov2i.y);
                break;
            case TAG:
                TRACEF("%d", p->tag.tag);
                break;
            default:
                printf("encountered unknown Object type, %s:%d\n", __FILE__, __LINE__);
                abort();
        }
        p = p->next;
    }
    trace_indent -= 4;
}

Boolean	isobj(Object obj) {
    return object_allocation[obj];
}

void delobj(Object obj) {
    if (isobj(obj)) {
        element_free(objects[obj]);
        objects[obj] = NULL;
        object_allocation[obj] = 0;
    }
}

void icontitle(char *name) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void backface(int enable) {
    backface_enabled = enable;
}

// Whether the viewport is the full screen.
static int is_full_viewport() {
    return the_viewport[0] == 0 && the_viewport[1] == DISPLAY_WIDTH - 1 &&
           the_viewport[2] == 0 && the_viewport[3] == DISPLAY_HEIGHT - 1;
}

void clear() {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(CLEAR);
        return;
    }

    TRACE();

    // The clear() command must only clear the viewport.
    int vx0 = (int)the_viewport[0], vx1 = (int)the_viewport[1];
    int vy0 = (int)the_viewport[2], vy1 = (int)the_viewport[3];

    // Layer clear (drawmode UNDERDRAW/OVERDRAW/PUPDRAW): fill the viewport
    // rect of the layer buffer with the current layer color; index 0 means
    // alpha 0 — erase the layer to transparent. Routed through the same
    // rect-fill draw path as partial normal clears (the rasterizer's layer
    // target is already selected by drawmode), skipping the cmode/masked
    // machinery which is normal-planes-only.
    int clear_layer = drawmode_layer(current_drawmode);

    // Colormap-plane masked clear (IRIS writemask): a clear through a partial
    // writemask only writes the writable planes of each pixel's INDEX:
    // newIndex = (oldIndex & ~wm) | (clearIndex & wm). flight 1988's meters
    // depend on this — the scale art lives in planes 0-1 (brown/orange/grey2)
    // and survives the per-frame writemask(wm_allplanes-3) clear that erases
    // the blue/red bars. The reference rasterizer applies the index math
    // exactly, per pixel, through its CI buffer (it gets wm, the clear
    // index, and the colormap below). The GPU rasterizer has no index
    // planes, so it approximates with a palette recoloring of the viewport
    // rect: for every mapped index, oldRGB -> RGB[newIndex]. (Exact for the
    // GPU's flat cmode fills; pixels whose RGB collides across indices take
    // the first match.)
    if (clear_layer < 0 && !rgb_mode && (~current_writemask & 0xfff) != 0) {
        static uint32_t rgb_from[4096], rgb_to[4096];
        uint32_t n = 0;
        int wm = current_writemask & 0xfff;
        for (int idx = 0; idx <= colormap_max_mapped; idx++) {
            if (!colormap_mapped[idx])
                continue;   // unmapped entries are all black; remapping them would recolor the background
            int nidx = (idx & ~wm) | (current_color_index & wm);
            uint32_t from = ((uint32_t)colormap[idx][0] << 16) | ((uint32_t)colormap[idx][1] << 8) | colormap[idx][2];
            uint32_t to   = ((uint32_t)colormap[nidx][0] << 16) | ((uint32_t)colormap[nidx][1] << 8) | colormap[nidx][2];
            if (from == to)
                continue;
            int dup = 0;
            for (uint32_t i = 0; i < n; i++)
                if (rgb_from[i] == from) { dup = 1; break; }
            if (!dup) {
                rgb_from[n] = from;
                rgb_to[n] = to;
                n++;
            }
        }
        rasterizer_masked_clear(vx0, vy0, vx1, vy1,
                                (uint16_t)wm, current_color_index, colormap,
                                n, rgb_from, rgb_to);
        return;
    }

    if (clear_layer < 0 && is_full_viewport()) {
        // Full screen, we can use the optimized version.
        rasterizer_clear(current_color[0] * 255.0,
                current_color[1] * 255.0,
                current_color[2] * 255.0,
                current_color_index);
    } else {
        // Partial viewport: fill exactly the viewport rectangle in screen
        // space. (The old approach drew a unit polygon through the current
        // matrices, which only covered the viewport when the projection
        // happened to map 0..1 onto it — flight 1988's CLEAR_* objects set
        // world-coordinate ortho2 ranges, so their per-frame erases were
        // no-ops and text/gauges smeared.) Clear ignores the z test but
        // honors the current pattern, like IRIS GL.
        screen_vertex q[6];
        for (int i = 0; i < 6; i++) {
            q[i].z = 0xffffffff;
            q[i].r = (uint8_t)(current_color[0] * 255.0);
            q[i].g = (uint8_t)(current_color[1] * 255.0);
            q[i].b = (uint8_t)(current_color[2] * 255.0);
            // layer clears carry the transparency bit (alpha 0 = layer erased)
            q[i].a = clear_layer >= 0 ? (uint8_t)(current_color[3] * 255.0) : 255;
            q[i].ci = (rgb_mode || clear_layer >= 0) ? SCREEN_VERTEX_CI_NONE : current_color_index;
        }
        int32_t sx0 = vx0 * SCREEN_VERTEX_V2_SCALE, sx1 = (vx1 + 1) * SCREEN_VERTEX_V2_SCALE;
        int32_t sy0 = vy0 * SCREEN_VERTEX_V2_SCALE, sy1 = (vy1 + 1) * SCREEN_VERTEX_V2_SCALE;
        q[0].x = sx0; q[0].y = sy0;
        q[1].x = sx1; q[1].y = sy0;
        q[2].x = sx1; q[2].y = sy1;
        q[3].x = sx0; q[3].y = sy0;
        q[4].x = sx1; q[4].y = sy1;
        q[5].x = sx0; q[5].y = sy1;
        if (zbuffer_enabled)
            rasterizer_zbuffer(0);
        rasterizer_draw(DRAW_TRIANGLES, 6, q);  // 6 vertices = 2 triangles (draw takes vertex counts)
        if (zbuffer_enabled)
            rasterizer_zbuffer(1);
    }
}

void closeobj() {
    TRACE();
    cur_ptr_to_nextptr = NULL;
}

// Possible SGI hardware bit plane capabilities:
//
// For colormap mode (cmode()), getplanes() <= 12-bit:
// 4-bit, 16 colors
// 8-bit, 256 colors    ---> "new for ECLIPSE 8 bit"
// 12-bit, 4096 colors
//
// For RGB mode (RGBmode()), getplanes() >= 12-bit required:
// 12-bit, dithered RGB 444
// 24-bit, RGB 888
//
// cmode (4 or 8 bit) used by: arena, insect
// cmode (8 or 12 bit) used by: flight (does *not* work with 24 bitplanes, due to use of 1 << getplanes() into a short)
// RGBmode used by: bounce, buttonfly, ideas, jello, logo (exit on getplanes() < 12)
//
// Color index apps had to save and restore the current color map, since customizing it
// would customize the colors for other apps too. Imagine the entire desktop changing
// simultaneously to the same set of colors as the currently running app.
//
// 12 = the deepest IRIS colormap config (4096 entries, matching our
// colormap[]). flight 1988 shifts (1 << getplanes()) into a short, so 24
// overflowed; SGI documented flight for 8- or 12-plane cmode. Demos whose
// <=12-plane path needs per-draw writemask compositing this shim can't
// emulate get a different config in apply_demo_quirks (arena -> 24).
static int planes_config = 12;

int getplanes() {
    TRACE();
    return planes_config;
}

void cmode() {
    rgb_mode = 0;
    rasterizer_rgbmode(rgb_mode);
}

void RGBmode() {
    rgb_mode = 1;
    rasterizer_rgbmode(rgb_mode);
}

void RGBcolor(int r, int g, int b) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(RGBCOLOR);
        e->rgbcolor.r = r;
        e->rgbcolor.g = g;
        e->rgbcolor.b = b;
        return;
    }

    TRACEF("%d, %d, %d", r, g, b);

    current_color[0] = r / 255.0;
    current_color[1] = g / 255.0;
    current_color[2] = b / 255.0;
    current_color[3] = 1.0;
}

void color(Colorindex color) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(COLOR);
        e->color.color = color;
        return;
    }

    TRACEF("%u", color);

    current_color_index = color;

    int layer = drawmode_layer(current_drawmode);
    if (layer >= 0) {
        for(int i = 0; i < 3; i++)
            current_color[i] = layer_colormap[layer][color & 0xff][i] / 255.0;
        // layer index 0 erases to transparent (see drawmode)
        current_color[3] = color ? 1.0f : 0.0f;
        return;
    }

    for(int i = 0; i < 3; i++)
        current_color[i] = colormap[color][i] / 255.0;
    // XXX alpha in color map?
}

int getcolor()
{
    return current_color_index;
}

void writemask(Colorindex mask) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(WRITEMASK);
        e->writemask.mask = mask;
        return;
    }

    TRACEF("%u", mask);

    current_writemask = mask;
    // Per-draw compositing lives in the rasterizers (the reference through
    // its CPU CI buffer, gles2 through the GPU CI buffer on ES3) — clear()
    // keeps its own masked path above. Before the
    // window exists don't touch the rasterizer: the first rasterizer_* call
    // locks in the implementation ahead of apply_demo_quirks; winopen
    // re-sends the current mask once the choice is made.
    //
    // Only forward the mask for real cmode configs (<=12 planes). cmode
    // never exceeded 12 planes on SGI hardware, so a demo quirked to a
    // deeper config (arena -> 24) is running a fallback path whose mask
    // constants were dead code on the real machines — compositing through
    // them wrecks the picture (arena's HUD indicators draw through
    // MASK_HUD=0x00f, contributing no bits). Those demos get the legacy
    // semantics in both rasterizers: draws overwrite, only clear() masks.
    if (window_is_open)
        rasterizer_writemask(planes_config <= 12 ? mask : 0xffff, colormap);
}

int getwritemask() {
    return current_writemask;
}

void deflinestyle(int index, Linestyle pattern) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void defpattern(int index, int size, Pattern16 mask) {
    TRACEF("%d, %d, ...", index, size);
    if(size != 16) {
        printf("pattern size %d not supported\n", size);
        return;
    }
    if(index == 0) {
        printf("cannot define pattern 0\n");
        return;
    }
    if(index < 0 || index >= MAX_PATTERNS) {
        printf("pattern index %d out of range\n", index);
        return;
    }
    for(int i = 0; i < 16; i++)
        patterns[index][i] = mask[i];

    // Flush cache.
    if (index == current_pattern) {
        // Send it again next time setpattern() is called.
        current_pattern = 0;
    }
}

void doublebuffer() {
    frontbuffer_draw_enabled = 0;
    backbuffer_draw_enabled = 1;
    rasterizer_cbuffer_draw(frontbuffer_draw_enabled, backbuffer_draw_enabled);
}

// Historically, SGI's default at winopen() was single-buffer mode, and
// demos called doublebuffer() to opt in to double buffering. This shim
// starts double-buffered instead, so a demo relying on the SGI single-
// buffer default (cedit) must get singlebuffer() called explicitly — done
// on its behalf in apply_demo_quirks so the original source stays intact.
void singlebuffer() {
    frontbuffer_draw_enabled = 1;
    backbuffer_draw_enabled = 0;
    rasterizer_cbuffer_draw(frontbuffer_draw_enabled, backbuffer_draw_enabled);
}

void editobj(Object obj) {
    TRACEF("%d", obj);

    cur_ptr_to_nextptr = &(objects[obj]);
    while(*cur_ptr_to_nextptr != NULL)
        cur_ptr_to_nextptr = &(*cur_ptr_to_nextptr)->next;
    replace_mode = 0;
}

void frontbuffer(Boolean enable) {
    frontbuffer_draw_enabled = enable;
    rasterizer_cbuffer_draw(frontbuffer_draw_enabled, backbuffer_draw_enabled);
}

void backbuffer(Boolean enable) {
    backbuffer_draw_enabled = enable;
    rasterizer_cbuffer_draw(frontbuffer_draw_enabled, backbuffer_draw_enabled);
}

void gconfig() {
    // Nothing to do here really. It's to be called after configuring:
    // 1. overlay/underlay (not supported)
    // 2. RGB vs. color map (only RGB supported)
    // 3. single vs. double buffer (only double buffer supported)
}

Object genobj() {
    for(int i = 0; i < OBJ_MAX; i++)
        if(!object_allocation[i]) {
            object_allocation[i] = 1;
            objects[i] = NULL;
            if(trace_functions) printf("%*sgenobj -> %d\n", trace_indent, "", i);
            return i;
        }
    abort();
}

Tag gentag() {
    for(int i = 0; i < OBJ_MAX; i++)
        if(!tag_allocation[i]) {
            tag_allocation[i] = 1;
            ptrs_to_tagptrs[i] = NULL;
            if(trace_functions) printf("%*sgentag -> %d\n", trace_indent, "", i);
            return i;
        }
    abort();
}

void getmcolor(Colorindex index, short *red, short *green, short *blue) {
    TRACEF("%d", index);

    int layer = drawmode_layer(current_drawmode);
    if (layer >= 0) {
        *red = layer_colormap[layer][index & 0xff][0];
        *green = layer_colormap[layer][index & 0xff][1];
        *blue = layer_colormap[layer][index & 0xff][2];
        return;
    }

    *red = colormap[index][0];
    *green = colormap[index][1];
    *blue = colormap[index][2];
}

void getorigin(long *x, long *y) {
    TRACE();

    *x = 0;
    *y = 0;
}

void getsize(long *width, long *height) {
    TRACE();

    *width = DISPLAY_WIDTH;
    *height = DISPLAY_HEIGHT;
}

Boolean getbutton(int button) {
    TRACEF("%d", button);
    return sdl_events_get_button(button);
}

// valuator = device with continuous input, like a mouse or dial
int getvaluator(int device) {
    TRACEF("%d", device);
    return sdl_events_get_valuator(device);
}

void setvaluator(Device device, int init, int min, int max) {
    // IRIS GL used this to warp the cursor and clamp a valuator's range
    // (newave constrains MOUSEX/MOUSEY to the window while editing). Our
    // mouse valuators are already window-relative and framebuffer-clamped
    // (sdl_events_get_valuator), so there is nothing to do.
    TRACEF("%d, %d, %d, %d", device, init, min, max);
}

void setlinestyle(int index) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void gflush() {
    TRACE();
    // For single-buffered demos: present the current front buffer and
    // yield. Same yield primitive as swapbuffers(), but with no back/front
    // swap (single-buffered demos draw directly to the front buffer).
    gl_resolve_ci_if_needed();
    sdl_events_frame_complete();
}

void greset() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void glcompat(int mode, int value) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

#ifndef M_PI
#define M_PI 3.141596
#endif
void gl_sincos(Angle angle, float *s, float *c) {
    float a = angle / 1800.0 * M_PI;
    if (s != NULL) {
        *s = sin(a);
    }
    if (c != NULL) {
        *c = cos(a);
    }
}

void gexit() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void makeobj(Object obj) {
    TRACEF("%d", obj);

    if(objects[obj] != NULL) {
        element_free(objects[obj]);
    }
    objects[obj] = NULL;
    cur_ptr_to_nextptr = &(objects[obj]);
    replace_mode = 0;
}

void maketag(Tag tag) {
    TRACEF("%d", tag);

    if(cur_ptr_to_nextptr == NULL) {
        printf("maketag : not editing\n");
        return;
    }
    dl_element *e = element_new();
    e->type = TAG;
    e->tag.tag = tag;
    ptrs_to_tagptrs[tag] = cur_ptr_to_nextptr;
    element_insert(&cur_ptr_to_nextptr, e);
}

void mapcolor(Colorindex index, int red, int green, int blue) {
    // XXX insect only provides numbers ranging 0..255
    TRACEF("%d, %d, %d, %d", index, red, green, blue);

    int layer = drawmode_layer(current_drawmode);
    if (layer >= 0) {
        layer_colormap[layer][index & 0xff][0] = red;
        layer_colormap[layer][index & 0xff][1] = green;
        layer_colormap[layer][index & 0xff][2] = blue;
        return;
    }

    colormap[index][0] = red;
    colormap[index][1] = green;
    colormap[index][2] = blue;
    colormap_mapped[index] = 1;
    if (index > colormap_max_mapped)
        colormap_max_mapped = index;
    ci_rgb_cache_stale = 1;
    ci_rgb_cache_stale_back = 1;
}

// SGI hardware palette LUT emulation: in CI mode, re-derive the front RGB
// buffer from the front color-index buffer whenever the colormap changed
// (mapcolor) or the front CI buffer was replaced (swapbuffers), so palette
// edits show up on screen without the demo redrawing (cedit's live sliders).
//
// Called only from "demo finished a frame, present it" sites — swapbuffers,
// gflush, qread's blocking wait, and the yieldByEventQuery safety net in
// sdl_events.c. NOT from sdl_events_frame_complete itself: dopup composites its
// menu into the RGB front buffer (with no CI backing) and presents through
// there, and a resolve would repaint the scene over the open menu.
//
// No-op in RGB mode and on rasterizers with no CI buffer (gles2).
void gl_resolve_ci_if_needed(void)
{
    if (!rgb_mode && ci_rgb_cache_stale) {
        rasterizer_resolve_ci_to_rgb(colormap);
        ci_rgb_cache_stale = 0;
    }
}

void multmatrix(Matrix m) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(MULTMATRIX);
        memcpy(e->multmatrix.m, m, sizeof(Matrix));
        return;
    }

    if(trace_functions) {
        printf("%*smultmatrix\n", trace_indent, "");
        for(int i = 0 ; i < 4; i++)
            printf("%*s    %f %f %f %f\n", trace_indent, "",
                m[i][0], m[i][1], m[i][2], m[i][3]);
    }

    matrix4x4f_stack_mult(current_stack, (float *)m);
}

void objreplace(Tag tag) {
    TRACEF("%d", tag);

    cur_ptr_to_nextptr = &(*ptrs_to_tagptrs[tag])->next;
    replace_mode = 1;
}

//
// Adaptive aspect (implied reshape). GLUT programs re-derive their
// projection from the new aspect on every window reshape; the original
// demos can't be modified to do that (rule #1), so the shim does it for
// them: the last projection the demo set is recorded here, and when the
// framebuffer aspect changes on a window resize it is re-derived with the
// horizontal view widened/narrowed to the new aspect. Content keeps 1:1
// x/y at any window shape — no letterboxing, no stretching.
//
// MSINGLE-mode projections are recorded but not re-applied: single-matrix
// demos rebuild their matrix every frame from getsize(), so they adapt on
// their own (and re-applying would clobber their composed matrix).
//
typedef enum { PROJ_NONE = 0, PROJ_PERSPECTIVE, PROJ_WINDOW, PROJ_ORTHO2 } proj_type;
static struct {
    proj_type type;
    float fovy, aspect;                     // perspective
    float left, right, bottom, top;         // window / ortho2
    float near, far;                        // perspective / window
    float fb_aspect_at_set;                 // framebuffer aspect when set
    int msingle;                            // set while in MSINGLE mode
    float matrix[16];                       // the projection matrix as loaded
                                            // (updated on each re-derivation)
} the_projection = { PROJ_NONE };

static void record_projection(proj_type type, const float m[16],
    float fovy, float aspect, float left, float right, float bottom, float top,
    float near, float far)
{
    the_projection.type = type;
    matrix4x4f_copy(the_projection.matrix, (float *)m);
    the_projection.fovy = fovy;
    the_projection.aspect = aspect;
    the_projection.left = left;
    the_projection.right = right;
    the_projection.bottom = bottom;
    the_projection.top = top;
    the_projection.near = near;
    the_projection.far = far;
    the_projection.fb_aspect_at_set = (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT;
    the_projection.msingle = (matrix_mode == MSINGLE);
}

static void perspective_matrix(float m[16], Angle fovy_, float aspect, Coord near, Coord far)
{
    float fovy = fovy_ / 1800.0 * M_PI;
    float f = 1.0 / tan(fovy / 2.0);

    matrix4x4f_copy(m, identity_4x4f);
    m[0] = f / aspect;
    m[5] = f;
    m[10] = (far + near) / (near - far);
    m[11] = -1.0;
    m[14] = 2 * far * near / (near - far);
    m[15] = 0.0;
}

static void ortho2_matrix(float m[16], Coord left, Coord right, Coord bottom, Coord top)
{
    matrix4x4f_copy(m, identity_4x4f);
    m[0] =  2.0f / (right-left);
    m[5] =  2.0f / (top-bottom);
    m[10] = -1.0f;
    m[12] = -(right+left) / (right-left);
    m[13] = -(top+bottom) / (top-bottom);
    m[15] =  1.0f;
}

static void window_matrix(float m[16], Coord left, Coord right, Coord bottom, Coord top, Coord near, Coord far)
{
    matrix4x4f_copy(m, identity_4x4f);
    m[0] = 2 * near / (right - left);
    m[5] = 2 * near / (top - bottom);
    m[8] = (right + left) / (right - left);
    m[9] = (top + bottom) / (top - bottom);
    m[10] = - (far + near) / (far - near);
    m[14] = - 2 * far * near / (far - near);
}

void perspective(Angle fovy_, float aspect, Coord near, Coord far) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(PERSPECTIVE);
        e->perspective.fovy = fovy_;
        e->perspective.aspect = aspect;
        e->perspective.near = near;
        e->perspective.far = far;
        return;
    }

    TRACEF("%d, %f, %f, %f", fovy_, aspect, near, far);

    float m[16];
    perspective_matrix(m, fovy_, aspect, near, far);
    record_projection(PROJ_PERSPECTIVE, m, fovy_, aspect, 0, 0, 0, 0, near, far);
    if(matrix_mode == MSINGLE) {
        matrix4x4f_stack_load(&projection_stack, m);
        matrix4x4f_stack_load(&modelview_stack, identity_4x4f);
    } else
        // In MVIEWING/MPROJECTION, perspective always loads the PROJECTION
        // matrix (never the viewing matrix) — same as window() below. flight
        // 3.4 sets perspective while in MVIEWING; loading current_stack (the
        // modelview in MVIEWING) left projection at identity and squished the
        // world into a narrow strip. MPROJECTION is unaffected (current_stack
        // already is the projection stack).
        matrix4x4f_stack_load(&projection_stack, m);
}

void ortho2(Coord left, Coord right, Coord bottom, Coord top) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(ORTHO2);
        e->ortho2.left = left;
        e->ortho2.right = right;
        e->ortho2.bottom = bottom;
        e->ortho2.top = top;
        return;
    }

    TRACEF("%f, %f, %f, %f", left, right, bottom, top);

    float m[16];
    ortho2_matrix(m, left, right, bottom, top);
    record_projection(PROJ_ORTHO2, m, 0, 0, left, right, bottom, top, 0, 0);

    if(matrix_mode == MSINGLE) {
        matrix4x4f_stack_load(&projection_stack, m);
        matrix4x4f_stack_load(&modelview_stack, identity_4x4f);
    } else
        // Always the PROJECTION matrix in MVIEWING/MPROJECTION (see perspective).
        matrix4x4f_stack_load(&projection_stack, m);
}

void poly_(int n, Coord parray[ ][3]) {
    static world_vertex worldverts[POLY_MAX];
    vec4f color;
    vec4f_copy(color, current_color);

    for(int i = 0 ; i < n; i++) {
        vec4f_set(worldverts[i].coord,
            parray[i][0], parray[i][1], parray[i][2], 1.0);
        vec4f_copy(worldverts[i].color, color);
        worldverts[i].ci = current_color_index;
        vec3f_set(worldverts[i].normal, 1, 0, 0);
    }

    process_polygon(n, worldverts);
}

void polf(int n, Coord parray[ ][3]) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(POLF);
        e->polf.n = n;
        e->polf.parray = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
        memcpy(e->polf.parray, parray, sizeof(Coord) * 3 * n);
        return;
    }

    TRACEF("%d", n);

    poly_(n, parray);
}

void polfi(int n, Icoord p[][3]) {
    Coord (*np)[3] = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
    for (int i = 0; i < n; i++) {
        np[i][0] = p[i][0];
        np[i][1] = p[i][1];
        np[i][2] = p[i][2];
    }
    polf(n, np);
    free(np);
}

void polfs(int n, Scoord p[][3]) {
    Coord (*np)[3] = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
    for (int i = 0; i < n; i++) {
        np[i][0] = p[i][0];
        np[i][1] = p[i][1];
        np[i][2] = p[i][2];
    }
    polf(n, np);
    free(np);
}

void polf2(int n, Coord p[][2]) {
    Coord (*np)[3] = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
    for (int i = 0; i < n; i++) {
        np[i][0] = p[i][0];
        np[i][1] = p[i][1];
        np[i][2] = 0;
    }
    polf(n, np);
    free(np);
}

void polf2i(int n, Icoord p[][2]) {
    Coord (*np)[3] = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
    for (int i = 0; i < n; i++) {
        np[i][0] = p[i][0];
        np[i][1] = p[i][1];
        np[i][2] = 0;
    }
    polf(n, np);
    free(np);
}

void polf2s(int n, Scoord p[][2]) {
    Coord (*np)[3] = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
    for (int i = 0; i < n; i++) {
        np[i][0] = p[i][0];
        np[i][1] = p[i][1];
        np[i][2] = 0;
    }
    polf(n, np);
    free(np);
}

void popmatrix() {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(POPMATRIX);
        return;
    }

    TRACE();

    if(matrix_mode == MSINGLE) {
        matrix4x4f_stack_pop(&modelview_stack);
        matrix4x4f_stack_pop(&projection_stack);
    } else {
        matrix4x4f_stack_pop(current_stack);
    }
}

void pushmatrix() {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(PUSHMATRIX);
        return;
    }

    TRACE();

    if(matrix_mode == MSINGLE) {
        matrix4x4f_stack_push(&modelview_stack);
        matrix4x4f_stack_push(&projection_stack);
    } else {
        matrix4x4f_stack_push(current_stack);
    }
}

void pushviewport() {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(PUSHVIEWPORT);
        return;
    }

    TRACE();

    // viewport() writes only the_viewport, so the stack top is stale until
    // synced here; without this, popviewport restores whatever the stack
    // held at init (zeros) and every later draw clips to a degenerate
    // viewport (flight 3.4's gauge faces vanished this way)
    viewport_copy(viewport_stack_top(&viewport_stack), the_viewport);
    viewport_stack_push(&viewport_stack);
}

void popviewport() {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(POPVIEWPORT);
        return;
    }

    TRACE();

    viewport_copy(the_viewport, viewport_stack_top(&viewport_stack));
    viewport_stack_pop(&viewport_stack);
}


void viewport(Screencoord left, Screencoord right, Screencoord bottom, Screencoord top)
{
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(VIEWPORT);
        e->viewport.left = left;
        e->viewport.right = right;
        e->viewport.bottom = bottom;
        e->viewport.top = top;
        return;
    }

    TRACEF("%d, %d, %d, %d", left, right, bottom, top);

    the_viewport[0] = left;
    the_viewport[1] = right;
    the_viewport[2] = bottom;
    the_viewport[3] = top;
}

// XXX display-listable?
void reshapeviewport() {
    TRACE();

    long xsize, ysize;
    getsize(&xsize, &ysize);
    viewport(0, xsize-1, 0, ysize-1);
}

void rotate(Angle ang, char axis) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(ROTATE);
        e->rotate.angle = ang;
        e->rotate.axis = axis;
        return;
    }

    TRACEF("%d, %c", ang, axis);

    float m[16];

    matrix4x4f_copy(m, identity_4x4f);

    float s;
    float c;
    float t;
    float d;
    float x = 0.0, y = 0.0, z = 0.0;

    if(axis == 'x' || axis == 'X') {
        x = 1.0;
    } else if(axis == 'y' || axis == 'Y') {
        y = 1.0;
    } else {
        z = 1.0;
    }

    float angle = ang / 1800.0 * M_PI;
    d = sqrtf(x * x + y * y + z * z);
    x /= d;
    y /= d;
    z /= d;

    /*
     * Rotation around axis from Graphics Gems 1, p.466
     */
    s = sinf(angle);
    c = cosf(angle);
    t = 1 - cosf(angle);
    m[0] = t * x * x + c;
    m[5] = t * y * y + c;
    m[10] = t * z * z + c;
    m[1] = t * x * y + s * z;
    m[4] = t * x * y - s * z;
    m[2] = t * x * z - s * y;
    m[8] = t * x * z + s * y;
    m[6] = t * y * z + s * x;
    m[9] = t * y * z - s * x;

    matrix4x4f_stack_mult(current_stack, m);
}

// rot() is the float-degrees variant of rotate(); tenths of a degree
// is the finest granularity the fixed-point Angle path supports
void rot(float ang, char axis) {
    rotate((Angle)roundf(ang * 10.0f), axis);
}

void setpattern(int pattern) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(SETPATTERN);
        e->setpattern.pattern = pattern;
        return;
    }

    TRACEF("%d", pattern);

    if(pattern == 0) {
        rasterizer_pattern(0);
    } else {
        if(current_pattern != pattern) {
            rasterizer_setpattern(patterns[pattern]);
            current_pattern = pattern;
        }
        rasterizer_pattern(1);
    }
}

void shademodel(int mode) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void swapbuffers() {
    TRACE();
    rasterizer_swap();
    sdl_events_set_framebuffer(rasterizer_frontbuffer());
    if (!rgb_mode) {
        // the staleness flags travel with their buffers
        int t = ci_rgb_cache_stale;
        ci_rgb_cache_stale = ci_rgb_cache_stale_back;
        ci_rgb_cache_stale_back = t;
    }
    gl_resolve_ci_if_needed();
    sdl_events_frame_complete();
}

void translate(Coord x, Coord y, Coord z) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(TRANSLATE);
        e->translate.x = x;
        e->translate.y = y;
        e->translate.z = z;
        return;
    }

    TRACEF("%f, %f, %f", x, y, z);

    float m[16];

    matrix4x4f_translate(x, y, z, m);
    matrix4x4f_stack_mult(current_stack, m);
}

void window(Coord left, Coord right, Coord bottom, Coord top, Coord near, Coord far) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(WINDOW);
        e->window.left = left;
        e->window.right = right;
        e->window.bottom = bottom;
        e->window.top = top;
        e->window.near = near;
        e->window.left = left;
        return;
    }

    TRACEF("%f, %f, %f, %f, %f, %f", left, right, bottom, top, near, far);

    float m[16];
    window_matrix(m, left, right, bottom, top, near, far);
    record_projection(PROJ_WINDOW, m, 0, 0, left, right, bottom, top, near, far);
    if(matrix_mode == MSINGLE) {
        matrix4x4f_stack_load(&projection_stack, m);
        matrix4x4f_stack_load(&modelview_stack, identity_4x4f);
    } else {
        matrix4x4f_stack_load(&projection_stack, m);
    }
}

// Re-derive the recorded projection for the current framebuffer aspect
// (the implied reshape; see the_projection above). The horizontal view
// widens/narrows so x/y stays 1:1 — like gluPerspective with a new aspect.
static void reapply_projection_for_aspect(void) {
    if (the_projection.type == PROJ_NONE || the_projection.msingle)
        return;

    float k = ((float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT)
            / the_projection.fb_aspect_at_set;
    float m[16];

    switch (the_projection.type) {
        case PROJ_PERSPECTIVE:
            perspective_matrix(m, the_projection.fovy, the_projection.aspect * k,
                               the_projection.near, the_projection.far);
            break;
        case PROJ_WINDOW:
        case PROJ_ORTHO2: {
            // scale the horizontal extents about their center
            float cx = (the_projection.left + the_projection.right) * 0.5f;
            float hw = (the_projection.right - the_projection.left) * 0.5f * k;
            if (the_projection.type == PROJ_WINDOW)
                window_matrix(m, cx - hw, cx + hw,
                              the_projection.bottom, the_projection.top,
                              the_projection.near, the_projection.far);
            else
                ortho2_matrix(m, cx - hw, cx + hw,
                              the_projection.bottom, the_projection.top);
            break;
        }
        default:
            return;
    }

    // Demos may compose extra transforms onto the projection stack after
    // setting it (buttonfly: translate right after perspective, in
    // MPROJECTION mode). The stack top is E x P_set; replace only the
    // projection part: top = E x P_new = (top x P_set^-1) x P_new.
    float inv[16], extra[16], newtop[16];
    if (matrix4x4f_invert(the_projection.matrix, inv) == 0) {
        matrix4x4f_mult_matrix4x4f(matrix4x4f_stack_top(&projection_stack), inv, extra);
        matrix4x4f_mult_matrix4x4f(extra, m, newtop);
        matrix4x4f_stack_load(&projection_stack, newtop);
    } else {
        matrix4x4f_stack_load(&projection_stack, m); // singular: bare reload
    }
    matrix4x4f_copy(the_projection.matrix, m);
}

// Called by the events layer when the framebuffer size is established
// (window creation) or changes (window resize; the demo also gets a REDRAW
// event). Updates GL's display dimensions, resizes the rasterizer
// framebuffer (atomic buffer swap), and re-registers the possibly
// reallocated front buffer with the display. A full-screen viewport tracks
// the new size; a demo-set sub-viewport is left for the demo's own
// reshapeviewport() (IRIS GL semantics).
void gl_framebuffer_resized(int width, int height) {
    int was_full_viewport = is_full_viewport();

    DISPLAY_WIDTH = width;
    DISPLAY_HEIGHT = height;
    menu_corner_top = DISPLAY_HEIGHT - 1 - 1 - 10;

    rasterizer_resize((uint32_t)width, (uint32_t)height);
    sdl_events_set_framebuffer(rasterizer_frontbuffer());

    if (was_full_viewport) {
        the_viewport[1] = DISPLAY_WIDTH - 1.0;
        the_viewport[3] = DISPLAY_HEIGHT - 1.0;
    }

    // implied reshape: keep the demo's projection aspect-true
    reapply_projection_for_aspect();
}

// IRIX window-constraint semantics: keepaspect after winopen is deferred
// until the demo calls winconstraints (see keepaspect/winconstraints)
static int pending_aspect_x = 0, pending_aspect_y = 0;

// The demo name stamped into the binary by make_demo.mk (see
// makefiles/gl_appname.c). Weak NULL default for programs built outside
// make_demo.mk (e.g. tests/native-resize); those fall back to the title
// passed to winopen.
__attribute__((weak)) const char *gl_appname = NULL;

static int demo_is(const char *title, const char *name) {
    return strcmp(title, name) == 0;
}

// Shim-level per-demo compatibility quirks. Original demo sources are never
// modified (rule #1); demos whose code bakes in the classic fixed screen
// get shim policies that recreate it:
//  - arena: on a <=12-plane IRIS it composites its HUD in colormap
//    bitplanes, protecting the static yellow overlay with per-draw
//    writemask()s. Report the 24-plane config of the bigger 4Ds instead:
//    arena's own high-plane path redraws the HUD every frame, which renders
//    correctly in both rasterizers. (Its 1024x768 screen is a compile-time
//    matter — DEMO_CFLAGS in its Makefile — and prefposition() then gets
//    it the matching fixed framebuffer, so no display quirk is needed.)
//  - cedit: relies on SGI's single-buffer-at-winopen default (it never
//    calls doublebuffer), which this shim inverts.
//
// flight 1988 and cedit need no rasterizer quirk anymore: writemask
// compositing, the live palette LUT, and index readback all run on both
// rasterizers (the reference through its CPU CI buffer, gles2 through the
// GPU CI buffer on an ES3 context).
static void apply_demo_quirks(char *title) {
    if (demo_is(title, "arena"))
        planes_config = 24;
    else if (demo_is(title, "cedit"))
        singlebuffer();
}

static void init_gl_state()
{
    static int initialized = 0;
    if (initialized)
        return;
    initialized = 1;

#if !defined(NDEBUG)
    if(getenv("TRACE_GL") != NULL)
        trace_functions = 1;
#endif

    for(int i = 0; i < MAX_PATTERNS; i++)
        for(int j = 0; j < 16; j++)
            patterns[i][j] = 0xffff;

    matrix4x4f_stack_init(&modelview_stack);
    matrix4x4f_stack_init(&projection_stack);
    matrix4x4f_stack_init(&texture_stack);
    matrix4x4f_stack_load(&modelview_stack, identity_4x4f);
    matrix4x4f_stack_load(&projection_stack, identity_4x4f);
    current_stack = &modelview_stack;

    the_viewport[0] = 0.0;
    the_viewport[1] = DISPLAY_WIDTH - 1.0;
    the_viewport[2] = 0.0;
    the_viewport[3] = DISPLAY_HEIGHT - 1.0;
    the_viewport[4] = 0.0;
    the_viewport[5] = 1.0;

    for(int i = 0; i < MAX_MATERIALS; i++)
        material_init(&materials[i]);
    for(int i = 0; i < MAX_LIGHTS; i++)
        light_init(&lights[i]);
    for(int i = 0; i < MAX_LMODELS; i++)
        lmodel_init(&lmodels[i]);

    for(int i = 0; i < MAX_LIGHTS; i++)
        lights_bound[i] = NULL;

    for(int i = 0; i < CIRCLE_SEGMENTS; i++) {
        float a = i * M_PI * 2 / CIRCLE_SEGMENTS;
        circle_verts[i][0] = cos(a);
        circle_verts[i][1] = sin(a);
    }

    vec3ub_set(colormap[BLACK], 0, 0, 0);
    vec3ub_set(colormap[RED], 255, 0, 0);
    vec3ub_set(colormap[GREEN], 0, 255, 0);
    vec3ub_set(colormap[YELLOW], 255, 255, 0);
    vec3ub_set(colormap[BLUE], 0, 0, 255);
    vec3ub_set(colormap[MAGENTA], 255, 0, 255);
    vec3ub_set(colormap[CYAN], 0, 255, 255);
    vec3ub_set(colormap[WHITE], 255, 255, 255);

    // IRIS default colormap also carried a 16-step grey ramp at 16..31
    // (libdemo port.h: GREY(x) = 16+x); cedit and friends use it without
    // ever mapping it themselves
    for(int i = 0; i < 16; i++)
        vec3ub_set(colormap[16 + i], i * 17, i * 17, i * 17);

    for(int i = 0; i < MAX_PUPS; i++)
        pup_init(pups + i);

    // BDF font is baked into the binary (see bake_bdf.py). It's a const
    // global, so no loading/parsing is needed -- just point at it.
    extern const BdfFont helvBO14_bdf;
    pup_bdffont = &helvBO14_bdf;

    //signal(SIGWINCH, sigwinch); // window changed event callback, maybe for window resizing
    //signal(SIGINFO, siginfo);   // status info event callback, Ctrl+T request for program info
}

int winopen(char *title) {
    init_gl_state();

    // One demo per program: the build-stamped name beats the passed title
    // (web argv[0] is "this.program"; native titles pick up argv paths)
    if (gl_appname)
        title = (char *)gl_appname;

    TRACEF("%s", title);

    // Quirks must run before the first rasterizer_* call: they may select
    // which rasterizer implementation gets locked in (cedit -> reference)
    apply_demo_quirks(title);

    int rasterizer_window = rasterizer_winopen(title);

    move(0.0, 0.0, 0.0);
    rasterizer_linewidth(the_linewidth);
    rasterizer_zbuffer(zbuffer_enabled);
    rasterizer_pattern(0);
    rasterizer_setpattern(patterns[0]);
    rasterizer_cbuffer_draw(frontbuffer_draw_enabled, backbuffer_draw_enabled);
    // catch up on any writemask() issued before the window existed (same
    // <=12-plane forwarding rule as writemask())
    rasterizer_writemask(planes_config <= 12 ? current_writemask : 0xffff, colormap);
    // likewise a drawmode() issued before the window existed
    rasterizer_layer(drawmode_layer(current_drawmode) + 1);

    // Aspect policy: demos that declared keepaspect() get a conforming
    // window (native) / centered framebuffer (web). All other demos get a
    // free-form window-sized framebuffer, kept undistorted by the implied
    // reshape (see the_projection / reapply_projection_for_aspect).
    int sdl_events_window = sdl_events_winopen(title);
    window_is_open = 1;

    sdl_events_set_framebuffer(rasterizer_frontbuffer());
    // XXX if we made a multi-window system, we'd tie "rasterizer_window"
    // and "sdl_events_window" together so we could pass the right identifier
    // to window functions.  But we are fullscreen and no demo we care
    // about uses multiple windows.
    return 1;
}

void noborder() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void winpop() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void ringbell() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

static int polygon_vert_count = 0;
static world_vertex polygon_verts[POLY_MAX];

void reset_vertex_list()
{
    polygon_vert_count = 0;
}

void bgntmesh() {
    bgn_object_type = BGNTMESH;

    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(BGNTMESH);
        return;
    }

    TRACE();

    reset_vertex_list();
}

void bgnline() {
    bgn_object_type = BGNLINE;

    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(BGNLINE);
        return;
    }

    TRACE();

    reset_vertex_list();
}

void bgnpoint()
{
    bgn_object_type = BGNPOINT;

    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(BGNPOINT);
        return;
    }

    TRACE();

    reset_vertex_list();
}

void bgnclosedline() {
    bgn_object_type = BGNCLOSEDLINE;

    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(BGNCLOSEDLINE);
        return;
    }

    TRACE();

    reset_vertex_list();
}

void bgnpolygon() {
    bgn_object_type = BGNPOLYGON;

    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(BGNPOLYGON);
        return;
    }

    TRACE();

    reset_vertex_list();
}

void c3i(int c[3]) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(C3F);
        for(int i = 0; i < 3; i++)
            e->c3i.c[i] = c[i];
        return;
    }

    TRACEF("%d, %d, %d", c[0], c[1], c[2]);

    vec4f_set(current_color, c[0] / 255.0, c[1] / 255.0, c[2] / 255.0, 1.0f);
}

void cpack(unsigned int pack)
{
    // cpack(0xFF004080);
    // sets red to 0x80, green to 0x40, blue to 0x0, and alpha to 0xFF
    int c[3] = { (pack & 0x000000ff),
                 (pack & 0x0000ff00) >> 8,
                 (pack & 0x00ff0000) >> 16};
    c3i(c);
    // alpha matters when blendfunction(BF_SA, BF_MSA) is active (explosions)
    current_color[3] = ((pack >> 24) & 0xff) / 255.0f;
}

void c3f(float c[3]) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(C3F);
        vec3f_copy(e->c3f.c, c);
        return;
    }

    TRACEF("%f, %f, %f", c[0], c[1], c[2]);

    vec4f_set(current_color, c[0], c[1], c[2], 1.0f);
}

/*
newpup(), addtopup(), defpup(), dopup()

newpup, addtopup, defpup create "struct menu"s

pushing SELECT sends RIGHTMOUSE?

dopup() enters a loop:
    (optional) entire previous frame contents are saved
    while not leaf item selected:
        menu is displayed with selected item inverted
        swap
        joystick can move up or down, back exits menus, select selects or submenus
        (optional) play back entire previous frame contents
    return leaf item value
*/
int defpup(char *menu, ...)
{
    int which = 0;
    while(pups[which].defd) {
        which++;
        if(which == MAX_PUPS) {
            printf("warning: max pups exceeded\n");
            return -1;
        }
    }

    pup *thepup = pups + which;
    pup_init(thepup);
    thepup->defd = 1;

    if (menu) {
        va_list ap;
        va_start(ap, menu);
        pup_parse_string(thepup, menu, ap);
        va_end(ap);
    }

    return which;
}

int newpup() {
    return defpup(NULL);
}

void addtopup(long which, char *menu, ...) {
    if(which < 0 || which >= MAX_PUPS || !pups[which].defd) {
        printf("addtopup: invalid pup id %ld\n", which);
        return;
    }
    va_list ap;
    va_start(ap, menu);
    pup_parse_string(pups + which, menu, ap);
    va_end(ap);
}

int dopup(int pup_index) {
    pup_active = 1;

    // Save previous drawing state
    int old_zbuffer = zbuffer_enabled;
    zbuffer(0);
    rasterizer_copy_front_to_back();
    vec4f previous_color;
    vec4f_copy(previous_color, current_color);
    vec4f_set(current_color, .1, .1, .1, 1);

    pup *thepup = pups + pup_index;

    Boolean larrow_queued = sdl_events_device_queued(LEFTARROWKEY),
            rarrow_queued = sdl_events_device_queued(RIGHTARROWKEY),
            uarrow_queued = sdl_events_device_queued(UPARROWKEY),
            darrow_queued = sdl_events_device_queued(DOWNARROWKEY),
            esc_queued    = sdl_events_device_queued(ESCKEY),
            ret_queued    = sdl_events_device_queued(RETKEY),
            lmouse_queued = sdl_events_device_queued(LEFTMOUSE);

    qdevice(LEFTARROWKEY);
    qdevice(RIGHTARROWKEY);
    qdevice(UPARROWKEY);
    qdevice(DOWNARROWKEY);
    qdevice(ESCKEY);
    qdevice(RETKEY);
    qdevice(LEFTMOUSE);

    pup_menu_topleft_corner_from_mouse(thepup);

    // Compute menu geometry once for hit-testing
    pup_layout layout;
    pup_compute_layout(thepup, menu_corner_left, menu_corner_top, &layout);

    // Full menu box: top of title down to bottom of items. Title and items
    // panes share the same horizontal extent.
    IcoordRect menu_box = {
        layout.title_outline.left,
        layout.title_outline.top,
        layout.items_outline.right,
        layout.items_outline.bottom,
    };

    int selected = 0;
    int done = 0;

    while (!done) {
        rasterizer_copy_back_to_front();
        pup_draw(thepup, menu_corner_left, menu_corner_top, selected);

        sdl_events_frame_complete();

        // Hover: if the cursor is over an item slot, move the highlight to
        // it. If the cursor is over the title, the gap, or outside the menu,
        // leave the highlight alone.
        {
            int hovered = pup_item_at(thepup, &layout,
                (Icoord2){ getvaluator(MOUSEX), getvaluator(MOUSEY) });
            if (hovered >= 0)
                selected = hovered;
        }

        if (qtest() != 0) {
            short val;
            int device = qread(&val);

            if (device == ESCKEY) {
                selected = -1;
                // if (val) { // ESCKEY down
                //     printf("PUP esc key down\n");
                // }
                if (!val) {     // ESCKEY up
                    // printf("PUP esc key up\n");
                    done = 1;               // done
                }
            }

            if (val) {
                switch (device) {
                    case LEFTARROWKEY:
                        selected = -1;
                        break;
                    case RETKEY:
                    case RIGHTARROWKEY:
                        done = 1;
                        break;
                    case UPARROWKEY:
                        if (selected > 0)
                            selected--;
                        break;
                    case DOWNARROWKEY:
                        if (selected < thepup->item_count - 1)
                            selected++;
                        break;
                    case LEFTMOUSE: {
                        // Click over an item: select it. Click outside the
                        // full menu box: cancel. Click on the title or in
                        // the gap between title and items: ignore.
                        Icoord2 cm = { getvaluator(MOUSEX), getvaluator(MOUSEY) };
                        int idx = pup_item_at(thepup, &layout, cm);
                        if (idx >= 0) {
                            selected = idx;
                            done = 1;
                        } else if (cm.x < menu_box.left   || cm.x > menu_box.right ||
                                   cm.y < menu_box.bottom || cm.y > menu_box.top) {
                            selected = -1;
                            done = 1;
                        }
                        break;
                    }
                }
            }
        }
    }

    if (!larrow_queued) unqdevice(LEFTARROWKEY);
    if (!rarrow_queued) unqdevice(RIGHTARROWKEY);
    if (!uarrow_queued) unqdevice(UPARROWKEY);
    if (!darrow_queued) unqdevice(DOWNARROWKEY);
    if (!esc_queued)    unqdevice(ESCKEY);
    if (!ret_queued)    unqdevice(RETKEY);
    if (!lmouse_queued) unqdevice(LEFTMOUSE);

    // Restore previous drawing state
    rasterizer_copy_back_to_front();
    vec4f_copy(current_color, previous_color);
    zbuffer(old_zbuffer);

    pup_active = 0;

    if (selected >= 0) {
        pup_item *item = thepup->items + selected;
        int value = item->value;
        // %f / %F callbacks run after the menu is closed and drawing state
        // is restored (they may change GL state themselves — newave's
        // display-mode menu does). Item function first, then the menu-wide
        // function, per IRIS GL ordering (see pup_func for why no args).
        if (item->func)
            value = item->func();
        if (thepup->func)
            value = thepup->func();
        return value;
    }
    else
        return -1;
}

void freepup(int popup) {
    if(popup < 0 || popup >= MAX_PUPS) {
        printf("freepup: invalid pup id %d\n", popup);
        return;
    }
    pup_free(pups + popup);
}

void endpoint()
{
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(ENDPOINT);
        return;
    }

    if(trace_functions) printf("%*sendpoint(); /* %d verts */\n", trace_indent, "", polygon_vert_count);

    for(int i = 0; i < polygon_vert_count; i++) {
        process_point(&polygon_verts[i]);
    }
}

void endline() {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(ENDLINE);
        return;
    }

    if(trace_functions) printf("%*sendline(); /* %d verts */\n", trace_indent, "", polygon_vert_count);

    for(int i = 0; i < polygon_vert_count - 1; i++) {
        process_line(&polygon_verts[i], &polygon_verts[i + 1]);
    }
}

void endclosedline() {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(ENDCLOSEDLINE);
        return;
    }

    if(trace_functions) printf("%*sendclosedline(); /* %d verts */\n", trace_indent, "", polygon_vert_count);

    for(int i = 0; i < polygon_vert_count; i++) {
        process_line(&polygon_verts[i], &polygon_verts[(i + 1) % polygon_vert_count]);
    }
}

void endtmesh() {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(ENDTMESH);
        return;
    }

    if(trace_functions) printf("%*sendtmesh(); /* %d verts */\n", trace_indent, "", polygon_vert_count);

    process_tmesh(polygon_vert_count, polygon_verts);
}

void endpolygon() {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(ENDPOLYGON);
        return;
    }

    if(trace_functions) printf("%*sendpolygon(); /* %d verts */\n", trace_indent, "", polygon_vert_count);

    process_polygon(polygon_vert_count, polygon_verts);
}

void drawmode(int mode) {
    TRACEF("%d", mode);

    current_drawmode = mode;
    if (window_is_open)     // pre-winopen call must not lock in the rasterizer
        rasterizer_layer(drawmode_layer(mode) + 1);   // 0=normal, 1=under, 2=over

    // vertex alpha carries the layer "index != 0" bit while a layer is
    // selected; back on the normal planes drawing is opaque again
    if (drawmode_layer(mode) < 0)
        current_color[3] = 1.0f;
}

void draw_(Coord x, Coord y, Coord z) {
    world_vertex v0, v1;
    vec4f_copy(v0.coord, current_position);
    vec4f_copy(v0.color, current_color);
    v0.ci = current_color_index;
    vec3f_copy(v0.normal, current_normal);

    current_position[0] = x;
    current_position[1] = y;
    current_position[2] = z;

    vec4f_copy(v1.coord, current_position);
    vec4f_copy(v1.color, current_color);
    v1.ci = current_color_index;
    vec3f_copy(v1.normal, current_normal);

    // move/draw lines light like any other primitive when a material and
    // lmodel are bound (flight 3.4's ground grid is setmaterial(MAT_DIRT) +
    // n3f + draw2i — suppressing lighting here left the lines in whatever
    // color was last set, the sky blue). Demos drawing unlit lines have no
    // material bound, so lighting_enabled is already off for them.
    process_line(&v0, &v1);
}

void draw(Coord x, Coord y, Coord z) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(DRAW);
        e->draw.x = x;
        e->draw.y = y;
        e->draw.z = z;
        return;
    }

    TRACEF("%f, %f, %f", x, y, z);
    draw_(x, y, z);
}

void draw2(Coord x, Coord y) {
    draw(x, y, 0);
}

void drawi(Icoord x, Icoord y, Icoord z) {
    draw(x, y, z);
}

void draw2i(Icoord x, Icoord y) {
    draw(x, y, 0);
}

void draws(Scoord x, Scoord y, Scoord z) {
    draw(x, y, z);
}

void draw2s(Scoord x, Scoord y) {
    draw(x, y, 0);
}

void pdr_(Coord x, Coord y, Coord z) {
    vec3f p = {x, y, z};
    v3f(p);
}

void pdr(Coord x, Coord y, Coord z) {
    pdr_(x, y, z);
}

void pdr2(Coord x, Coord y) {
    pdr_(x, y, 0);
}

void pdr2i(Icoord x, Icoord y) {
    pdr_(x, y, 0);
}

void pdri(Icoord x, Icoord y, Icoord z) {
    pdr_(x, y, z);
}

void pclos() {
    endpolygon();
}

// Old-style (pre-4D) shaded polygons: setshade picks the colormap shade for
// the vertices that follow, spclos closes and fills. True Gouraud between
// shades isn't emulated; the polygon fills flat with the latest shade.
void setshade(Colorindex shade) {
    color(shade);
}

void spclos() {
    endpolygon();
}

void pmv_(Coord x, Coord y, Coord z) {
    bgnpolygon();
    pdr_(x, y, z);
}

void pmv(Coord x, Coord y, Coord z) {
    pmv_(x, y, z);
}

void pmv2 (Coord x, Coord y) {
    pmv_(x, y, 0);
}

void pmvi(Icoord x, Icoord y, Icoord z) {
    pmv_(x, y, z);
}

void pmv2i(Icoord x, Icoord y) {
    pmv_(x, y, 0);
}

void pmvs (Scoord x, Scoord y, Scoord z)
{
    pmv_(x, y, z);
}

void pmv2s (Scoord x, Scoord y)
{
    pmv_(x, y, 0);
}

void pnt(Coord x, Coord y, Coord z)
{
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(PNT);
        e->pnt.x = x;
        e->pnt.y = y;
        e->pnt.z = z;
        return;
    }

    static world_vertex wv;
    vec4f_set(wv.coord, x, y, z, 1.0);
    vec4f_copy(wv.color, current_color);
    wv.ci = current_color_index;

    process_point(&wv);
}

void pnt2(Coord x, Coord y) {
    pnt(x, y, 0);
}

void pnti(Icoord x, Icoord y, Icoord z) {
    pnt(x, y, z);
}

void pnt2i(Icoord x, Icoord y) {
    pnt(x, y, 0);
}

void pnts(Scoord x, Scoord y, Scoord z) {
    pnt(x, y, z);
}

void pnt2s(Scoord x, Scoord y) {
    pnt(x, y, 0);
}

void keepaspect(int x, int y) {
    TRACEF("%d, %d", x, y);
    // IRIX keepaspect took effect at the NEXT winopen or winconstraints,
    // never immediately. Before winopen we pass it straight down (recorded,
    // applied at window creation). After winopen it stays pending until the
    // demo calls winconstraints (e.g. buttonfly's SPACE toggle_window).
    if (!window_is_open) {
        sdl_events_keepaspect(x, y);
    } else {
        pending_aspect_x = x;
        pending_aspect_y = y;
    }
}

void linewidth(int w) {
    if(trace_functions) printf("%*slinewidth(%d);\n", trace_indent, "", w);
    the_linewidth = w;
    rasterizer_linewidth(w);
}

void lmbind(int target, int index) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(LMBIND);
        e->lmbind.target = target;
        e->lmbind.index = index;
        return;
    }

    TRACEF("%d, %d", target, index);

    if(target == MATERIAL) {
        if(index < 0 || index > MAX_MATERIALS) {
            static int warned = 0; if(!warned) { printf("lmbind: material index %d out of range\n", index); warned = 1; }
            index = 0;
        }
        material_bound = (index == 0) ? NULL : &materials[index - 1];
        lighting_enabled = (material_bound != NULL) && (lmodel_bound != NULL);
    } else if(target >= LIGHT0 && target <= LIGHT7) {
        lights_bound[target - LIGHT0] = (index == 0) ? NULL : &lights[index - 1];
    } else if(target == LMODEL) {
        lmodel_bound = (index == 0) ? NULL : &lmodels[index - 1];
        lighting_enabled = (material_bound != NULL) && (lmodel_bound != NULL);
    } else
        abort();
}

// IRIS GL clamps color-valued lmdef properties to [0, 1] at definition time.
// flight 3.4 depends on it: the daytime sun is set_lightcolor(SUN, ...,
// l*4.4, l, l) — the 4.4 red multiplier only shapes the sunrise ramp and is
// meant to saturate at 1.0 well before full day. Stored unclamped, the
// red-heavy sun tints every dark lit material brick-orange (the F-14's
// engine nozzles read as thrust-flame colored).
static void vec3f_set_clamped01(vec3f d, float x, float y, float z)
{
    vec3f_set(d, unitclamp(x), unitclamp(y), unitclamp(z));
}

void lmdef(int deftype, int index, int numpoints, float properties[]) {
    if(index == 0)
        abort();
    index -=1;
    float *p = properties;
    int next = 0;
    if(deftype == DEFMATERIAL) {
        static material dropped;    /* out-of-range defs land here */
        material *m;
        if(index < 0 || index >= MAX_MATERIALS) {
            static int warned = 0; if(!warned) { printf("lmdef: material index %d out of range\n", index + 1); warned = 1; }
            m = &dropped;
        } else
            m = &materials[index];
        if(trace_functions) printf("%*slmdef(DEFMATERIAL, %d, %d, {\n", trace_indent, "", index + 1, numpoints);
        while(*p != LMNULL) {
            switch((int)*p) {
                case DIFFUSE:
                    if(trace_functions) printf("%*sDIFFUSE, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set_clamped01(m->diffuse, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case EMISSION:
                    if(trace_functions) printf("%*sEMISSION, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set_clamped01(m->emission, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case AMBIENT:
                    if(trace_functions) printf("%*sAMBIENT, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set_clamped01(m->ambient, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case SPECULAR:
                    if(trace_functions) printf("%*sSPECULAR, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set_clamped01(m->specular, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case SHININESS:
                    if(trace_functions) printf("%*sSHININESS, %f,\n", trace_indent + 4, "", p[1]);
                    m->shininess = p[1];
                    p+= 2;
                    break;
                case ALPHA:
                    if(trace_functions) printf("%*sALPHA, %f,\n", trace_indent + 4, "", p[1]);
                    m->alpha = unitclamp(p[1]);
                    p+= 2;
                    break;
                default:
                    abort();
            }
        }
        if(trace_functions) printf("%*sLMNULL }\n", trace_indent + 4, "");
    } else if(deftype == DEFLIGHT) {
        light *l = &lights[index];
        if(trace_functions) printf("%*slmdef(DEFLIGHT, %d, %d, {\n", trace_indent, "", index + 1, numpoints);

        while(*p != LMNULL) {
            switch((int)*p) {
                case SPOTDIRECTION: {
                    vec3f direction;
                    vec3f transformed;
                    if(trace_functions) printf("%*sSPOTDIRECTION, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    // XXX probably not right
                    vec3f_set(direction, p[1], p[2], p[3]);
                    vec3f_mult_matrix4x4f(direction, matrix4x4f_stack_get_inverse(&modelview_stack), transformed);
                    vec4f_set(l->spotdirection, transformed[0], transformed[1], transformed[2], 0.0f);
                    p+= 4;
                    break;
                }
                case AMBIENT:
                    if(trace_functions) printf("%*sAMBIENT, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set_clamped01(l->ambient, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case LCOLOR:
                    if(trace_functions) printf("%*sLCOLOR, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set_clamped01(l->color, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case POSITION:
                    if(trace_functions) printf("%*sPOSITION, %f, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3], p[4]);
                    if(p[4] == 0.0) {
                        vec3f direction;
                        vec3f transformed;
                        // XXX may not be right
                        vec3f_set(direction, p[1], p[2], p[3]);
                        vec3f_mult_matrix4x4f(direction, matrix4x4f_stack_get_inverse(&modelview_stack), transformed);
                        vec4f_set(l->position, transformed[0], transformed[1], transformed[2], 0.0f);
                    } else {
                        vec4f position;
                        vec4f_set(position, p[1], p[2], p[3], p[4]);
                        matrix4x4f_mult_vec4f_(matrix4x4f_stack_top(&modelview_stack), position, l->position);
                    }
                    p+= 5;
                    break;
                case SPOTLIGHT:
                    if(trace_functions) printf("%*sSPOTLIGHT, %f, %f,\n", trace_indent + 4, "", p[1], p[2]);
                    l->spotlight[0] = p[1];
                    l->spotlight[1] = p[2];
                    p+= 3;
                    break;
                default:
                    abort();
            }
        }
        if(trace_functions) printf("%*sLMNULL }\n", trace_indent + 4, "");
    } else if(deftype == DEFLMODEL) {
        lmodel *lm = &lmodels[index];
        if(trace_functions) printf("%*slmdef(DEFLMODEL, %d, %d, {\n", trace_indent, "", index + 1, numpoints);
        while(*p != LMNULL) {
            switch((int)*p) {
                case LOCALVIEWER:
                    if(trace_functions) printf("%*sLOCALVIEWER, %f,\n", trace_indent + 4, "", p[1]);
                    lm->local = (int)p[1];
                    p+= 2;
                    break;
                case AMBIENT:
                    if(trace_functions) printf("%*sAMBIENT, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set(lm->ambient, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case ATTENUATION:
                    if(trace_functions) printf("%*sATTENUATION, %f, %f,\n", trace_indent + 4, "", p[1], p[2]);
                    lm->attenuation[0] = p[1];
                    lm->attenuation[1] = p[2];
                    p+= 3;
                    break;
                default:
                    abort();
            }
        }
        if(trace_functions) printf("%*sLMNULL }\n", trace_indent + 4, "");
    } else {
        abort();
    }
}

void loadmatrix(Matrix m) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(LOADMATRIX);
        memcpy(e->loadmatrix.m, m, sizeof(Matrix));
        return;
    }

    if(trace_functions)
    {
        printf("%*sloadmatrix\n", trace_indent, "");
        for(int i = 0 ; i < 4; i++)
            printf("%*s    %f %f %f %f\n", trace_indent, "",
                m[i][0], m[i][1], m[i][2], m[i][3]);
    }

    if(matrix_mode == MSINGLE) {
        matrix4x4f_stack_load(&projection_stack, identity_4x4f);
        matrix4x4f_stack_load(&modelview_stack, (float *)m);
    } else {
        matrix4x4f_stack_load(current_stack, (float *)m);
    }
}

void mmode(int mode) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(MMODE);
        e->mmode.mode = mode;
        return;
    }

    TRACEF("%d", mode);

    matrix_mode = mode;
    switch(mode) {
        case MSINGLE: current_stack = &modelview_stack; break;
        case MVIEWING: current_stack = &modelview_stack; break;
        case MTEXTURE: current_stack = &texture_stack; break;
        case MPROJECTION: current_stack = &projection_stack; break;
    }
}

void move(Coord x, Coord y, Coord z) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(MOVE);
        e->move.x = x;
        e->move.y = y;
        e->move.z = z;
        return;
    }

    TRACEF("%f, %f, %f", x, y, z);
    vec4f_set(current_position, x, y, z, 1.0);
}

void move2(Coord x, Coord y) {
    move(x, y, 0);
}

void moves(Scoord x, Scoord y, Scoord z) {
    move(x, y, z);
}

void move2s(Scoord x, Scoord y) {
    move(x, y, 0);
}

void movei(Icoord x, Icoord y, Icoord z) {
    move(x, y, z);
}

void move2i(Icoord x, Icoord y) {
    move(x, y, 0);
}

void n3f(float n[3]) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(N3F);
        vec3f_copy(e->n3f.n, n);
        return;
    }

    TRACEF("%f, %f, %f", n[0], n[1], n[2]);

    vec3f_copy(current_normal, n);
}

void prefsize(long width, long height) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void prefposition(int x1, int x2, int y1, int y2) {
    // IRIS GL: the next winopen creates a window of exactly this size and
    // position. The canvas/window is our "screen", so the demo instead gets a
    // FRAMEBUFFER of exactly the requested size, scaled to the window by the
    // display (both flight demos hard-code their layout to the classic
    // 1280x1024 screen and never look at the real window size). Position is
    // ignored.
    int w = (x2 > x1 ? x2 - x1 : x1 - x2) + 1;
    int h = (y2 > y1 ? y2 - y1 : y1 - y2) + 1;
    TRACEF("%d, %d, %d, %d", x1, x2, y1, y2);
    sdl_events_set_framebuffer_fixed_size(w, h);
}

void rdr2i(Icoord dx, Icoord dy) {
    TRACEF("%d, %d", dx, dy);

    world_vertex v0, v1;
    vec4f_copy(v0.coord, current_position);
    vec4f_copy(v0.color, current_color);
    v0.ci = current_color_index;

    current_position[0] += dx;
    current_position[1] += dy;

    vec4f_copy(v1.coord, current_position);
    vec4f_copy(v1.color, current_color);
    v1.ci = current_color_index;

    int save_lighting = lighting_enabled;
    lighting_enabled = 0;
    process_line(&v0, &v1);
    lighting_enabled = save_lighting;
}

void rmv2i(Icoord dx, Icoord dy) {
    TRACEF("%d, %d", dx, dy);
    current_position[0] += dx;
    current_position[1] += dy;
}

void scale(float x, float y, float z) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(SCALE);
        e->scale.x = x;
        e->scale.y = y;
        e->scale.z = z;
        return;
    }

    TRACEF("%f, %f, %f", x, y, z);

    float m[16];

    matrix4x4f_scale(x, y, z, m);
    matrix4x4f_stack_mult(current_stack, m);
}

// XXX sdl_events_tie
void tie(int button, int val1, int val2) {
    sdl_events_tie(button, val1, val2);
}

void v4f(float v[4]) {

    if(polygon_vert_count > POLY_MAX - 2) {
        if (bgn_object_type == BGNPOINT) {
            endpoint();
            bgnpoint();
        }
        else
            abort();
    }

    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(V4F);
        vec4f_copy(e->v4f.v, v);
        return;
    }

    TRACEF("%f, %f, %f, %f", v[0], v[1], v[2], v[3]);

    world_vertex *wv = polygon_verts + polygon_vert_count;
    vec4f_copy(wv->coord, v);
    wv->st[0] = current_texcoord[0];
    wv->st[1] = current_texcoord[1];
    vec4f_copy(wv->color, current_color);
    wv->ci = current_color_index;
    vec3f_copy(wv->normal, current_normal);
    polygon_vert_count++;
}

void v3f(float v[3]) {
    float v_[4] = {v[0], v[1], v[2], 1.0f};
    v4f(v_);
}

void v2f(float v[2]) {
    float v_[4] = {v[0], v[1], 0.0, 1.0f};
    v4f(v_);
}

void v3i(long v[3]) {
    float v_[4] = {v[0], v[1], v[2], 1.0f};
    v4f(v_);
}

void v2i(long v[2]) {
    float v_[4] = {v[0], v[1], 0.0, 1.0f};
    v4f(v_);
}

/* Swap the two retained triangle-strip vertices (IRIS GL tmesh "swap").
 * Our tmesh buffers the whole strip and triangulates in process_tmesh(),
 * so emulate by re-appending the next-to-last vertex: the extra degenerate
 * triangle is invisible and leaves the strip in the swapped order. */
void swaptmesh() {
    if(bgn_object_type != BGNTMESH || polygon_vert_count < 2)
        return;
    if(polygon_vert_count > POLY_MAX - 2)
        abort();
    polygon_verts[polygon_vert_count] = polygon_verts[polygon_vert_count - 2];
    polygon_vert_count++;
}

int winattach() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
    return 0;
}

void winconstraints() {
    // Applies constraints declared since the last winopen/winconstraints
    // (IRIX one-shot semantics). Only keepaspect is modeled; prefsize/
    // prefposition/winposition remain unimplemented.
    if (pending_aspect_x > 0) {
        sdl_events_keepaspect(pending_aspect_x, pending_aspect_y);
        pending_aspect_x = pending_aspect_y = 0;
    }
}

int winget() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
    return 1;
}

void winposition(int x1, int x2, int y1, int y2) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void getmatrix(Matrix m) {
    TRACE();

    if(matrix_mode == MSINGLE) {
        matrix4x4f_mult_matrix4x4f(matrix4x4f_stack_top(&modelview_stack), matrix4x4f_stack_top(&projection_stack), (float*)m);
    } else {
        matrix4x4f_copy((float*)m, matrix4x4f_stack_top(current_stack));
    }
}

void lookat(Coord viewx,Coord viewy, Coord viewz, Coord pointx, Coord pointy, Coord pointz, Angle twist) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(LOOKAT);
        e->lookat.viewx = viewx;
        e->lookat.viewy = viewy;
        e->lookat.viewz = viewz;
        e->lookat.pointx = pointx;
        e->lookat.pointy = pointy;
        e->lookat.pointz = pointz;
        e->lookat.twist = twist;
        return;
    }

    TRACEF("%f, %f, %f, %f, %f, %f, %u", viewx, viewy, viewz, pointx, pointy, pointz, twist);

    vec3f f;
    vec3f up;
    f[0] = pointx - viewx;
    f[1] = pointy - viewy;
    f[2] = pointz - viewz;

    if(f[0] != 0.0 || f[2] != 0.0) {
        up[0] = 0.0; up[1] = 1.0; up[2] = 0.0;
    } else {
        up[0] = 0.0; up[1] = 0.0; up[2] = -1.0;
    }

    vec3f_normalize(f, f);
    vec3f_normalize(up, up);
    vec3f s, u;
    vec3f_cross(f, up, s);
    vec3f_cross(s, f, u);

    float m[16];

    m[0] =    s[0]; m[1]  =   u[0]; m[2]  =  -f[0]; m[3]  = 0;
    m[4] =    s[1]; m[5]  =   u[1]; m[6]  =  -f[1]; m[7]  = 0;
    m[8] =    s[2]; m[9]  =   u[2]; m[10] =  -f[2]; m[11] = 0;
    m[12] =      0; m[13] =      0; m[14] =      0; m[15] = 1;

    matrix4x4f_stack_mult(current_stack, (float *)m);

    matrix4x4f_translate(-viewx, -viewy, -viewz, m);
    matrix4x4f_stack_mult(current_stack, (float *)m);

    matrix4x4f_rotate(twist * M_PI / 1800, f[0], f[1], f[2], m);
    matrix4x4f_stack_mult(current_stack, (float *)m);
}

// Viewer on a sphere around the origin: back the eye off by dist, then
// undo twist, incidence, and azimuth. Angles are in tenths of degrees.
// Implemented with the regular matrix calls so display lists and the
// current matrix mode are handled for free. (Used by electropaint.)
void polarview(Coord dist, Angle azim, Angle inc, Angle twist) {
    translate(0.0, 0.0, -dist);
    rotate(-twist, 'z');
    rotate(-inc, 'x');
    rotate(-azim, 'z');
}

// Define the screen z range: the units lshaderange's znear/zfar are
// expressed in, and (for forward ranges) the window z range projected
// vertices map into — flight 3.4 jams the horizon ball to the far plane
// with lsetdepth(zmax, zmax) so the bezel plate's z occludes it into a
// circle. Reversed ranges (gview's lsetdepth(0x7FFFFF, 0x2000), paired
// with a zfunction we also don't emulate) stay ignored — that departure
// is documented in gview.c.
void lsetdepth(int near, int far) {
    TRACEF("%d, %d", near, far);
    ls_znear = near;
    ls_zfar = far;
    if (near <= far) {
        the_viewport[4] = near / (float)0x7fffff;
        the_viewport[5] = far / (float)0x7fffff;
    }
}

// pre-4D name for lsetdepth, with a Screencoord (16-bit) z range
void setdepth(Screencoord near, Screencoord far) {
    TRACEF("%d, %d", near, far);
    ls_znear = near;
    ls_zfar = far;
}

// IRIX libc, not IRIS GL: nap for ticks/100 seconds. Demos call it to be
// polite with the CPU; our frame pacing happens in sdl_events_frame_complete()
// (swapbuffers/gflush/event queries), so there is nothing to do here.
long sginap(long ticks) {
    return 0;
}

void depthcue(Boolean enable)
{
    TRACEF("%d", enable);
    depthcue_enabled = enable;
}

int getgdesc (int inquiry)
{
    switch(inquiry)
    {
        case GD_BITS_NORM_SNG_RED:
        case GD_BITS_NORM_SNG_GREEN:
        case GD_BITS_NORM_SNG_BLUE:
        case GD_BITS_NORM_DBL_RED:
        case GD_BITS_NORM_DBL_GREEN:
        case GD_BITS_NORM_DBL_BLUE:
            return 8;
        case GD_BITS_NORM_SNG_CMODE:
        case GD_BITS_NORM_DBL_CMODE:
            return 12;
        case GD_BITS_NORM_ZBUFFER:
            return 24;
        case GD_XPMAX:
            return DISPLAY_WIDTH;
        case GD_YPMAX:
            return DISPLAY_HEIGHT;
        case GD_ZMIN:
            return 0;
        case GD_ZMAX:
            return 0x7fffff;    /* standard IRIS 24-bit z range */
        /* features we don\'t have (0 = absent, and vintage code takes the
           no-feature path cleanly): multisample, texturing, vertex fog,
           antialiased RGB lines, blending */
        case GD_FOGVERTEX:
        case GD_BLEND:
        case GD_TEXTURE:
            return 1;
        case GD_MULTISAMPLE:
        case GD_LINESMOOTH_CMODE:
        case GD_LINESMOOTH_RGB:
        case GD_CIFRACT:
            return 0;
        // 2-bit overlay/underlay planes, like mid-range IRIS hardware —
        // emulated as composited side layers (see rasterizer_layer)
        case GD_BITS_OVER_SNG_CMODE:
        case GD_BITS_UNDR_SNG_CMODE:
            return 2;
    }

    static int warned = 0; if(!warned) { printf("%s %d unimplemented\n", __FUNCTION__, inquiry); warned = 1; }
    return 0;
}

// Set the color-index ramp that depth-cued vertices shade through: a
// vertex at znear draws with highin (brightest), at zfar with lowin, and
// linearly in between (see project_vertex). znear/zfar are in lsetdepth
// units.
void lshaderange (Colorindex lowin, Colorindex highin, long znear, long zfar)
{
    TRACEF("%d, %d, %ld, %ld", lowin, highin, znear, zfar);
    shade_lowin = lowin;
    shade_highin = highin;
    shade_znear = znear;
    shade_zfar = zfar;
}


/* GL2-era name for line antialiasing (newave). We can't reproduce per-pixel
 * coverage, but in CI mode we approximate its visible effect: smooth lines
 * draw with the brightest entry of their 16-entry intensity ramp (see
 * process_line) instead of the ramp base, which is what the hardware
 * converged to for fully-covered pixels. */
void smoothline (long mode)
{
    TRACEF("%ld", mode);
    smoothline_enabled = (mode != 0);
}

/* the real IRIS GL name for line antialiasing */
void linesmooth (long mode)
{
    TRACEF("%ld", mode);
    smoothline_enabled = (mode != 0);
}

void blendfunction (long sfactor, long dfactor)
{
    TRACEF("%ld, %ld", sfactor, dfactor);

    if (sfactor == BF_SA && dfactor == BF_MSA)
        rasterizer_blend(1);
    else if (sfactor == BF_ONE && dfactor == BF_ZERO)
        rasterizer_blend(0);
    else {
        // the only modes the demos use; anything else falls back to off
        static int warned = 0; if(!warned) { printf("blendfunction(%ld, %ld) unsupported\n", sfactor, dfactor); warned = 1; }
        rasterizer_blend(0);
    }
}

void fogvertex (long mode, float *params)
{
    TRACEF("%ld", mode);

    switch(mode) {
        case FG_DEFINE:
            // flight 3.4 usage: params[0] = density, params[1..3] = fog RGB
            fog_density = params[0];
            vec3f_set(fog_color, params[1], params[2], params[3]);
            break;
        case FG_ON:
            fog_enabled = 1;
            break;
        case FG_OFF:
            fog_enabled = 0;
            break;
    }
}

void texdef2d (long index, long nc, long width, long height, unsigned long *image, long np, float *props)
{
    TRACEF("%ld, %ld, %ld, %ld", index, nc, width, height);

    if (index <= 0 || index >= MAX_TEXTURES) {
        printf("texdef2d: index %ld out of range\n", index);
        return;
    }

    gl_texture *tx = &textures[index];
    free(tx->rgb);
    tx->rgb = (uint8_t *)malloc((size_t)width * height * 3);
    tx->width = width;
    tx->height = height;
    tx->defined = 1;

    // filters: use the mag filter; mipmap min-filter variants collapse to
    // their base (no mipmapping)
    tx->bilinear = 0;
    for (long i = 0; i + 1 < np; i += 2)
        if ((int)props[i] == TX_MAGFILTER && (int)props[i + 1] == TX_BILINEAR)
            tx->bilinear = 1;

    if (nc == 1) {
        // 8-bit intensity texels (flight 3.4's hills.t)
        const uint8_t *src = (const uint8_t *)image;
        for (long i = 0; i < width * height; i++) {
            tx->rgb[i * 3 + 0] = src[i];
            tx->rgb[i * 3 + 1] = src[i];
            tx->rgb[i * 3 + 2] = src[i];
        }
    } else {
        // packed RGBA words (untested: no current demo uses nc > 1)
        const uint32_t *src = (const uint32_t *)image;
        for (long i = 0; i < width * height; i++) {
            tx->rgb[i * 3 + 0] = src[i] & 0xff;
            tx->rgb[i * 3 + 1] = (src[i] >> 8) & 0xff;
            tx->rgb[i * 3 + 2] = (src[i] >> 16) & 0xff;
        }
    }
}

void texbind (long target, long index)
{
    TRACEF("%ld, %ld", target, index);

    if (index > 0 && index < MAX_TEXTURES && textures[index].defined) {
        gl_texture *tx = &textures[index];
        rasterizer_teximage(tx->width, tx->height, tx->rgb, tx->bilinear);
        rasterizer_texture(1);
        texture_bound = index;
    } else {
        rasterizer_texture(0);
        texture_bound = 0;
    }
}

void tevdef (long index, long np, float *props)
{
    // the texture environment is always TV_MODULATE (flight's tevps is {0})
    TRACEF("%ld", index);
}

void tevbind (long target, long index)
{
    TRACEF("%ld, %ld", target, index);
}

/* per-vertex texture coordinate for the next vertex */
void t2f (float t[2])
{
    current_texcoord[0] = t[0];
    current_texcoord[1] = t[1];
}

void subpixel (Boolean b)
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

/* font metrics for the built-in IRIS GL font 0 (irisfont0) */
int strwidth (char *str)
{
    return strlen(str) * 9;     /* irisfont0 is charcell: 9px per glyph */
}

int getheight ()
{
    return irisfont0.ascent + irisfont0.descent;
}

int getdescender ()
{
    return irisfont0.descent;
}

void getviewport (Screencoord *left, Screencoord *right, Screencoord *bottom, Screencoord *top)
{
    *left = the_viewport[0];
    *right = the_viewport[1];
    *bottom = the_viewport[2];
    *top = the_viewport[3];
}

/* IRIX libfastm float math, used by flight 3.4 */
float fasin (float a) { return asinf(a); }
float fcos (float a) { return cosf(a); }
float fexp (float a) { return expf(a); }
float fsqrt (float a) { return sqrtf(a); }

void foreground ()
{
    /* "don't fork into the background" — we never do */
}

void setbell (int durations)
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void swapinterval (int interval)
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void overlay (long planes)
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void underlay (long planes)
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

/* GL selection/picking names — flight only uses these in pick mode */
void loadname (int name)
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void pushname (int name)
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void popname ()
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void wmpack (unsigned long pack)
{
    TRACEF("%lu", pack);

    // all-or-nothing color writes: flight 3.4's tail-decal z backfill uses
    // wmpack(0) / wmpack(0xffffffff). Partial channel masks are not needed
    // by the demo corpus.
    if (pack != 0 && pack != 0xffffffff) {
        static int warned = 0;
        if (!warned) { printf("wmpack: partial masks unimplemented\n"); warned = 1; }
    }
    rasterizer_colormask(pack != 0);
}

void scrmask (int left, int right, int bottom, int top)
{
    TRACEF("%d, %d, %d, %d", left, right, bottom, top);

    // full-window mask = no clipping (how demos reset it)
    if (left <= 0 && bottom <= 0 &&
        right >= DISPLAY_WIDTH - 1 && top >= DISPLAY_HEIGHT - 1) {
        rasterizer_scissor(0, 0, 0, 0, 0);
        return;
    }
    rasterizer_scissor(1, left, bottom, right, top);
}

void zwritemask (unsigned long mask)
{
    TRACEF("%lu", mask);

    // all-or-nothing depth writes (flight 3.4 uses 0 / 0xffffff around the
    // blended explosion sprites); the z test itself stays on
    rasterizer_zwrite(mask != 0);
}

// zsource(ZSRC_COLOR) makes z comparisons use color instead of depth
// (newave's antialiased mode uses it as a brightest-pixel-wins trick for
// smooth lines). We can't source z from color, so z-testing is suspended
// while it's selected — the demo's zfunction tricks against a czclear'd
// buffer degenerate to plain draw-in-order, which is the right look for
// the wireframes that use this.
void zsource (long src)
{
    TRACEF("%ld", src);
    zsource_color = (src == ZSRC_COLOR);
    rasterizer_zbuffer(zbuffer_enabled && !zsource_color);
}

void charstr(char *str) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(CHARSTR);
        e->charstr.str = strdup(str);
        return;
    }

    TRACEF("\"%s\"", str);

    static lit_vertex vert;
    static screen_vertex screenvert;

    vec4f_copy(vert.coord, current_character_position);
    vec4f_copy(vert.color, current_color);
    vert.ci = current_color_index;

    int code = classify_vertex(vert.coord);
    if(code != CLIP_ALL_IN)
        return;

    project_vertex(&vert, &screenvert);

    string_draw(&screenvert, str);
}

void circi(Icoord x, Icoord y, Icoord r) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(CIRCI);
        e->circi.x = x;
        e->circi.y = y;
        e->circi.r = r;
        return;
    }

    TRACEF("%d, %d, %d", x, y, r);

    world_vertex v0, v1;

    vec4f_copy(v0.color, current_color);
    v0.ci = current_color_index;
    vec4f_copy(v1.color, current_color);
    v1.ci = current_color_index;

    int save_lighting = lighting_enabled;
    lighting_enabled = 0;

    v0.coord[2] = 0.0;
    v0.coord[3] = 1.0;
    v1.coord[2] = 0.0;
    v1.coord[3] = 1.0;

    for(int i = 0; i < CIRCLE_SEGMENTS; i++) {
        v0.coord[0] = x + r * circle_verts[i][0];
        v0.coord[1] = y + r * circle_verts[i][1];
        v1.coord[0] = x + r * circle_verts[(i + 1) % CIRCLE_SEGMENTS][0];
        v1.coord[1] = y + r * circle_verts[(i + 1) % CIRCLE_SEGMENTS][1];

        process_line(&v0, &v1);
    }

    lighting_enabled = save_lighting;
}

void circfs(Scoord x, Scoord y, Scoord r) {
    circf(x, y, r);
}

void circ(Coord x, Coord y, Coord r) {
    TRACEF("%f, %f, %f", x, y, r);

    world_vertex v0, v1;

    vec4f_copy(v0.color, current_color);
    v0.ci = current_color_index;
    vec4f_copy(v1.color, current_color);
    v1.ci = current_color_index;

    int save_lighting = lighting_enabled;
    lighting_enabled = 0;

    v0.coord[2] = 0.0;
    v0.coord[3] = 1.0;
    v1.coord[2] = 0.0;
    v1.coord[3] = 1.0;

    for(int i = 0; i < CIRCLE_SEGMENTS; i++) {
        v0.coord[0] = x + r * circle_verts[i][0];
        v0.coord[1] = y + r * circle_verts[i][1];
        v1.coord[0] = x + r * circle_verts[(i + 1) % CIRCLE_SEGMENTS][0];
        v1.coord[1] = y + r * circle_verts[(i + 1) % CIRCLE_SEGMENTS][1];

        process_line(&v0, &v1);
    }

    lighting_enabled = save_lighting;
}

void circf(Coord x, Coord y, Coord r) {
    TRACEF("%f, %f, %f", x, y, r);

    static world_vertex verts[CIRCLE_SEGMENTS];

    int save_lighting = lighting_enabled;
    lighting_enabled = 0;

    for(int i = 0; i < CIRCLE_SEGMENTS; i++) {
        verts[i].coord[0] = x + r * circle_verts[i][0];
        verts[i].coord[1] = y + r * circle_verts[i][1];
        verts[i].coord[2] = 0.0;
        verts[i].coord[3] = 1.0;
        vec4f_copy(verts[i].color, current_color);
        verts[i].color[3] = 1.0;
        verts[i].ci = current_color_index;
    }
    process_polygon(CIRCLE_SEGMENTS, verts);

    lighting_enabled = save_lighting;
}

void cmov2i(Icoord x, Icoord y) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(CMOV2I);
        e->cmov2i.x = x;
        e->cmov2i.y = y;
        return;
    }

    TRACEF("%d, %d", x, y);

    vec4f c, p;
    vec4f_set(c, x, y, 0.0, 1.0);
    matrix4x4f_mult_vec4f(matrix4x4f_stack_top(&modelview_stack), c, p);
    matrix4x4f_mult_vec4f(matrix4x4f_stack_top(&projection_stack), p, current_character_position);
}

void cmov2s(Scoord x, Scoord y) {
    cmov2i(x, y);
}

void cmov(Coord x, Coord y, Coord z) {
    TRACEF("%f, %f, %f", x, y, z);

    vec4f c, p;
    vec4f_set(c, x, y, z, 1.0);
    matrix4x4f_mult_vec4f(matrix4x4f_stack_top(&modelview_stack), c, p);
    matrix4x4f_mult_vec4f(matrix4x4f_stack_top(&projection_stack), p, current_character_position);
}

void cmov2(Coord x, Coord y) {
    cmov(x, y, 0.0);
}

/* current character position, in window coordinates (same transform as
 * project_vertex) */
void getcpos(Screencoord *ix, Screencoord *iy) {
    int viewport_width = the_viewport[1] - the_viewport[0] + 1;
    int viewport_height = the_viewport[3] - the_viewport[2] + 1;
    float xndc = current_character_position[0] / current_character_position[3];
    float yndc = current_character_position[1] / current_character_position[3];
    *ix = (Screencoord)(viewport_width / 2.0 * xndc + (the_viewport[0] + viewport_width / 2.0));
    *iy = (Screencoord)(viewport_height / 2.0 * yndc + (the_viewport[2] + viewport_height / 2.0));
}

void cursoff() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void curson() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void feedback(float buffer[], long size) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

int endfeedback(float buffer[]) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
    return 0;
}

void setcursor(short index, Colorindex color, Colorindex writemask) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void defcursor(int index, short *cursor) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void curorigin(short index, short xorigin, short yorigin) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void rectf_(Coord x1, Coord y1, Coord x2, Coord y2) {
    bgnpolygon();
    pdr_(x1, y1, 0);
    pdr_(x1, y2, 0);
    pdr_(x2, y2, 0);
    pdr_(x2, y1, 0);
    endpolygon();
}

void rect_(Coord x1, Coord y1, Coord x2, Coord y2) {
    bgnline();
    pdr_(x1, y1, 0);
    pdr_(x1, y2, 0);
    pdr_(x2, y2, 0);
    pdr_(x2, y1, 0);
    endclosedline();
}

void rectf(Coord x1, Coord y1, Coord x2, Coord y2) {
    rectf_(x1, y1, x2, y2);
}

void rectfi(Icoord x1, Icoord y1, Icoord x2, Icoord y2) {
    rectf_(x1, y1, x2, y2);
}

void rectfs(Scoord x1, Scoord y1, Scoord x2, Scoord y2) {
    rectf_(x1, y1, x2, y2);
}

void rect(Coord x1, Coord y1, Coord x2, Coord y2) {
    rect_(x1, y1, x2, y2);
}

void recti(Icoord x1, Icoord y1, Icoord x2, Icoord y2) {
    rect_(x1, y1, x2, y2);
}

void rects(Scoord x1, Scoord y1, Scoord x2, Scoord y2) {
    rect_(x1, y1, x2, y2);
}

static int bgn_screen_aligned()
{
    pushviewport();
    viewport (0, DISPLAY_WIDTH - 1, 0, DISPLAY_HEIGHT - 1);

    int prev_matrix_mode = matrix_mode;
    mmode(MPROJECTION);
    pushmatrix();
    // load the screen-aligned ortho WITHOUT recording it as the demo's
    // projection (the demo's own is restored by popmatrix below)
    {
        float m[16];
        ortho2_matrix(m, -0.5, DISPLAY_WIDTH - 1 + 0.5, -0.5, DISPLAY_HEIGHT - 1 + 0.5);
        matrix4x4f_stack_load(&projection_stack, m);
    }
    return prev_matrix_mode;
}

static void end_screen_aligned(int prev_matrix_mode)
{
    popmatrix();
    mmode(prev_matrix_mode);
    popviewport();
}

void sbox(Coord x1, Coord y1, Coord x2, Coord y2)
{
    int prev_matrix_mode = bgn_screen_aligned();
    rect_(x1, y1, x2, y2);
    end_screen_aligned(prev_matrix_mode);
}

void sboxi(Icoord x1, Icoord y1, Icoord x2, Icoord y2)
{
    sbox(x1, y1, x2, y2);
}

void sboxs(Scoord x1, Scoord y1, Scoord x2, Scoord y2)
{
    sbox(x1, y1, x2, y2);
}

void sboxf(Coord x1, Coord y1, Coord x2, Coord y2)
{
    int prev_matrix_mode = bgn_screen_aligned();
    rectf_(x1, y1, x2, y2);
    end_screen_aligned(prev_matrix_mode);
}

void sboxfi(Icoord x1, Icoord y1, Icoord x2, Icoord y2)
{
    sboxf(x1, y1, x2, y2);
}

void sboxfs(Scoord x1, Scoord y1, Scoord x2, Scoord y2)
{
    sboxf(x1, y1, x2, y2);
}

void poly(int n, Coord p[][3]) {
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(POLY);
        e->poly.n = n;
        e->poly.p = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
        memcpy(e->poly.p, p, sizeof(Coord) * 3 * n);
        return;
    }

    TRACEF("%d", n);

    static world_vertex worldverts[POLY_MAX];
    vec4f color;
    vec4f_copy(color, current_color);

    for(int i = 0 ; i < n; i++) {
        vec4f_set(worldverts[i].coord,
            p[i][0], p[i][1], p[i][2], 1.0);
        vec4f_copy(worldverts[i].color, color);
        worldverts[i].ci = current_color_index;
        vec3f_set(worldverts[i].normal, 1, 0, 0);
    }

    for(int i = 0; i < polygon_vert_count; i++) {
        process_line(&worldverts[i], &worldverts[(i + 1) % polygon_vert_count]);
    }
}

void polyi(int n, Icoord p[][3]) {
    Coord (*np)[3] = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
    for (int i = 0; i < n; i++) {
        np[i][0] = p[i][0];
        np[i][1] = p[i][1];
        np[i][2] = p[i][2];
    }
    poly(n, np);
    free(np);
}

void polys(int n, Scoord p[][3]) {
    Coord (*np)[3] = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
    for (int i = 0; i < n; i++) {
        np[i][0] = p[i][0];
        np[i][1] = p[i][1];
        np[i][2] = p[i][2];
    }
    poly(n, np);
    free(np);
}

void poly2(int n, Coord p[][2]) {
    Coord (*np)[3] = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
    for (int i = 0; i < n; i++) {
        np[i][0] = p[i][0];
        np[i][1] = p[i][1];
        np[i][2] = 0;
    }
    poly(n, np);
    free(np);
}

void poly2i(int n, Icoord p[][2]) {
    Coord (*np)[3] = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
    for (int i = 0; i < n; i++) {
        np[i][0] = p[i][0];
        np[i][1] = p[i][1];
        np[i][2] = 0;
    }
    poly(n, np);
    free(np);
}

void poly2s(int n, Scoord p[][2]) {
    Coord (*np)[3] = (Coord(*)[]) malloc(sizeof(Coord) * 3 * n);
    for (int i = 0; i < n; i++) {
        np[i][0] = p[i][0];
        np[i][1] = p[i][1];
        np[i][2] = 0;
    }
    poly(n, np);
    free(np);
}

// XXX display list

void zbuffer(int enable) {
    TRACEF("%d", enable);
    zbuffer_enabled = enable;
    rasterizer_zbuffer(enable && !zsource_color);
}

// XXX display list
void zclear() {
    TRACE();

    // the layer planes carry no z; don't let a layer-mode zclear wipe the
    // normal planes' shared depth buffer
    if (drawmode_layer(current_drawmode) >= 0)
        return;

    // IRIS zclear only clears the viewport — flight 3.4's per-frame scene
    // zclear must leave the instrument panel's plate z intact (it occludes
    // the horizon ball inside its bezel)
    if (!is_full_viewport()) {
        rasterizer_zclear_rect(0xffffffff,
                               (int32_t)the_viewport[0], (int32_t)the_viewport[2],
                               (int32_t)the_viewport[1], (int32_t)the_viewport[3]);
        return;
    }

    rasterizer_zclear(0xffffffff);
}

void zfunction(int func) {
    TRACEF("%d", func);
    // The rasterizers compare LEQUAL, the IRIS GL default and the only
    // function the demo corpus asks for. (newave also sets ZF_GEQUAL, but
    // only together with zsource(ZSRC_COLOR), where z-testing is suspended
    // anyway — see zsource.)
    if (func != ZF_LEQUAL) {
        static int warned = 0;
        if (!warned) { printf("zfunction: only ZF_LEQUAL emulated\n"); warned = 1; }
    }
}

// XXX display list
void czclear(int color, int depth) {
    TRACE();

    if (!is_full_viewport()) {
        // viewport-scoped like clear()/zclear(): depth via the rect clear,
        // color via a viewport rect fill through the draw path
        rasterizer_zclear_rect((uint32_t)depth,
                               (int32_t)the_viewport[0], (int32_t)the_viewport[2],
                               (int32_t)the_viewport[1], (int32_t)the_viewport[3]);
        vec4f saved_color;
        unsigned short saved_index = current_color_index;
        vec4f_copy(saved_color, current_color);
        current_color[0] = ((color >> 16) & 0xff) / 255.0f;
        current_color[1] = ((color >>  8) & 0xff) / 255.0f;
        current_color[2] = ((color >>  0) & 0xff) / 255.0f;
        current_color[3] = 1.0f;
        current_color_index = color;
        clear();
        vec4f_copy(current_color, saved_color);
        current_color_index = saved_index;
        return;
    }

    rasterizer_czclear((color >> 16) & 0xff, (color >>  8) & 0xff, (color >>  0) & 0xff, color, depth);
}

int gversion(char *version)
{
    /* IRIX callers pass a 12-byte buffer (flight 3.4 passes 16) — keep it short */
    strcpy(version, "SGI-DEMOS");
    return 0;
}

// #ifndef SIGINFO
// #define SIGINFO 29
// #endif
// void sigwinch(int s)
// {
//     enqueue_device(RIGHTMOUSE, 1);
// }
// void siginfo(int s)
// {
//     enqueue_device(RIGHTMOUSE, 0);
// }

// Read back color indices from the front buffer, starting at the current
// character position and moving right (CI mode; cedit's getapixel uses this
// for its pick-a-color-off-the-screen clicks). Both rasterizers provide the
// CI buffer (gles2 reads its CI FBO back on demand); NULL only when the
// gles2 CI path is unavailable (ES2 context) — those reads see index 0.
int readpixels(short number, Colorindex colors[ ])
{
    TRACEF("%d", number);

    unsigned short *cibuf = rasterizer_ci_frontbuffer();
    if (cibuf == NULL) {
        static int warned = 0;
        if (!warned) {
            printf("readpixels: no color-index buffer on this rasterizer (use the reference rasterizer)\n");
            warned = 1;
        }
        for (int i = 0; i < number; i++)
            colors[i] = 0;
        return number;
    }

    Screencoord cx, cy;
    getcpos(&cx, &cy);

    int count = 0;
    for (int i = 0; i < number; i++) {
        int x = cx + i;
        if (x < 0 || x >= DISPLAY_WIDTH || cy < 0 || cy >= DISPLAY_HEIGHT)
            break;
        // window y is up; buffer row 0 is the top row
        colors[count++] = cibuf[(size_t)(DISPLAY_HEIGHT - 1 - cy) * DISPLAY_WIDTH + x];
    }
    // (IRIS GL also advances the character position past the pixels read;
    // nothing in this corpus depends on that.)
    return count;
}
int readRGB(short number, RGBvalue red[ ], RGBvalue green[ ], RGBvalue blue[ ])
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
    return 0;
}

void pushattributes()
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void popattributes()
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

// Make world coordinates coincide with screen pixels: full-framebuffer
// viewport and an ortho projection mapping x,y 1:1 onto pixel centers.
// Loads the matrix stacks directly (no record_projection) so the demo's
// own recorded projection isn't disturbed; callers bracket this with
// pushviewport/pushmatrix ... popmatrix/popviewport (libdemo's getapixel),
// which in MSINGLE mode saves and restores both stacks.
void screenspace()
{
    TRACE();
    viewport(0, DISPLAY_WIDTH - 1, 0, DISPLAY_HEIGHT - 1);
    float m[16];
    ortho2_matrix(m, -0.5, DISPLAY_WIDTH - 0.5, -0.5, DISPLAY_HEIGHT - 0.5);
    matrix4x4f_stack_load(&projection_stack, m);
    matrix4x4f_stack_load(&modelview_stack, identity_4x4f);
}

//
// IRIS GL event handling (gl_events.c)
//
// The GL-side event system: the device-event queue and the IRIS GL API that
// drives it (qdevice/unqdevice/qread/qtest/qenter/qreset), plus the quit
// policy. It sits above the SDL translation layer (sdl_events.c, the sdl_events_*
// interface in events.h) and below the demos. gl.c is rendering; this is
// input.
//


// The GL device-event queue (filled from the SDL layer by fetch_event_queue).
static unsigned int input_queue_device[INPUT_QUEUE_SIZE];
static unsigned short input_queue_val[INPUT_QUEUE_SIZE];
static int input_queue_head = 0;    // next entry to read
static int input_queue_length = 0;  // entries queued (tail = (head+length)%len)

static void enqueue_device(int device, unsigned short val) {
    TRACEF("%d, %d", device, val);

    if (input_queue_length == INPUT_QUEUE_SIZE) {
        printf("Input queue overflow.");
    } else {
        int tail = (input_queue_head + input_queue_length) % INPUT_QUEUE_SIZE;
        input_queue_device[tail] = device;
        input_queue_val[tail] = val;
        input_queue_length++;
    }
}

/* XXX event_get_qdevice() */
// We're interested in events from this device.
void qdevice(Device device) {
    TRACEF("%d", device);

    switch (device) {
        case REDRAW:
            // Initial redraw, so the demo's first frame draws even before
            // any SDL window event arrives.
            enqueue_device(REDRAW, 0);
            // Also register REDRAW with the SDL side so it will enqueue
            // REDRAW events on window expose/resize and via periodic pulse.
            sdl_events_qdevice(device);
            break;

        case INPUTCHANGE:
            // Tell app that this window has received input focus
            enqueue_device(INPUTCHANGE, 1);
            break;

        default:
            // Send the device to the server.
            sdl_events_qdevice(device);
            break;
    }
}

void unqdevice(Device device) {
    sdl_events_unqdevice(device);
}

// XXX sdl_events_qread_start
// XXX sdl_events_qread_continue
static void fetch_event_queue() {
    int count = sdl_events_qread_start();

    // First is number of events.
    for (int i = 0; i < count; i++) {
        short value;
        int device = sdl_events_qread_continue(&value);
        enqueue_device(device, value);
    }
}

// Pops the next event (device number and value) off the head of the queue
// and returns it. Like real IRIS GL, BLOCKS until an event is available
// (flight 3.4's wait_for_input spins forever otherwise); while waiting, the
// events layer pumps input, keeps the frame presented, and idles. The one
// exception: inside the SDL event pump blocking would deadlock, so there it
// returns 0 on an empty queue (the old Alice4 behavior).
int qread(short *val) {
    TRACE();

    while (!qtest())
    {
        // The blocking wait presents frames while idle; make sure any
        // pending palette change is baked in before it does (cedit finishes
        // a slider drag and then blocks here).
        gl_resolve_ci_if_needed();
        if (!sdl_events_qread_block())
            return 0;
    }

    *val = input_queue_val[input_queue_head];
    int device = input_queue_device[input_queue_head];
    input_queue_head = (input_queue_head + 1) % INPUT_QUEUE_SIZE;
    input_queue_length--;

    // Universal quit via ESC: Exit the demo here whether or not the
    // demo registered to handle ESC with qdevice(ESCKEY). Don't exit
    // though if popup menu is active (it uses ESC to quit poup)
    if (device == ESCKEY || device == WINQUIT)
    {
        //printf("qread ESC val = %d\n", *val);
        // if (*val == 0)
        //     printf("here!\n");
        if (!pup_active)
            gl_exit(0);
    }

    return device;
}

// Returns the device number of the first entry.
// Returns 0 if the event queue is empty.
// Doesn't change the queue.
int qtest() {
    TRACE();

    if (input_queue_length == 0)
        fetch_event_queue();

    if (input_queue_length == 0) {
        // Empty queue.
        return 0;
    } else {
        // Peek at the head.
        return input_queue_device[input_queue_head];
    }
}

void qenter(short qtype, short value) {
    enqueue_device(qtype, value);
}

void qreset ()
{
    TRACE();
    // Discard all pending events: pull anything queued in the events layer
    // into the GL queue first, then drop the lot.
    fetch_event_queue();
    input_queue_head = 0;
    input_queue_length = 0;
}

// Browser-friendly exit(): in the web build a raw exit() tears down the C
// runtime but leaves the page sitting there (looks frozen), so instead we
// navigate away -- back to the previous page, or to the demos home if there
// is none. Native builds exit normally.
void gl_exit(int status)
{
#ifdef __EMSCRIPTEN__
    // Go to previous page, or if none, to the demos home page.
    const char *exit_js =
        "if (document.referrer) {                                   "
        "     window.history.back();                                "
        "}                                                          "
        "else {                                                     "
        "    window.location.href = 'https://sgi-demos.github.io';  "
        "}                                                          ";
    extern void emscripten_run_script(const char *);
    emscripten_run_script(exit_js);
#endif
    exit(status);
}

// #define exit gl_exit
