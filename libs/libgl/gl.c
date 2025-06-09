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
static const int DISPLAY_WIDTH = XMAXSCREEN + 1;
static const int DISPLAY_HEIGHT = YMAXSCREEN + 1;

static vec3ub colormap[4096];
static vec4f current_color = {1.0f, 1.0f, 1.0f, 1.0f};
static unsigned short current_color_index = 0;
static unsigned short current_writemask = 0xffff;
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

static int matrix_mode = MSINGLE;
static matrix4x4f_stack modelview_stack;
static matrix4x4f_stack projection_stack;
static matrix4x4f_stack *current_stack;

static viewport_t the_viewport;
static viewport_stack_t viewport_stack;

static unsigned int input_queue_device[INPUT_QUEUE_SIZE];
static unsigned short input_queue_val[INPUT_QUEUE_SIZE];
// The next time that needs to be read:
static int input_queue_head = 0;
// The number of items in the queue (tail = (head + length) % len):
static int input_queue_length = 0;

#define MAX_PATTERNS 16
static Pattern16 patterns[MAX_PATTERNS];

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

#define MAX_MATERIALS 8
#define MAX_LIGHTS 8
#define MAX_LMODELS 2
static material materials[MAX_MATERIALS];
static light lights[MAX_LIGHTS];
static lmodel lmodels[MAX_LMODELS];

static int lighting_enabled = 0;
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

//------------------------------------------------------------------------
// Popup menus ("pup" in GL lingo)

#define MAX_PUPS 16
#define MAX_PUP_ITEMS 16

typedef struct pup_item {
    char *item;
    int value;
    int submenu;
    int (*func)(int i);
} pup_item;

typedef struct pup {
    int defd;
    char *title;
    int (*func)(int i);
    int item_count;
    struct pup_item items[MAX_PUP_ITEMS];
} pup;
static struct pup pups[MAX_PUPS];

void pup_init(pup *p)
{
    p->defd = 0;
    p->title = NULL;
    p->func = NULL;
    p->item_count = 0;
}

void pup_new(pup *p)
{
    p->defd = 1;
}

void pup_free(pup *p)
{
    if(p->title != NULL) {
        free(p->title);
    }
    for(int i = 0; i < p->item_count; i++) {
        pup_item *pi = p->items + i;
        if(pi->item != NULL) {
            free(pi->item);
        }
    }
    pup_init(p);
}

void pup_set_title(pup *p, char *title)
{
    if(p->title != NULL) {
        free(p->title);
    }
    p->title = NULL;
    if(title != NULL) {
        p->title = strdup(title);
    }
}

void pup_add(pup *p, char *item, int value, int submenu, int (*func)(int i))
{
    pup_item *pi = p->items + p->item_count++;
    
    if(item != NULL)
        pi->item = strdup(item);
    else
        pi->item = NULL;
    pi->value = value;
    pi->submenu = submenu;
    pi->func = func;
}

//----------------------------------------------------------------------------
// Transformation, lighting, clipping

typedef struct world_vertex
{
    vec4f coord;
    vec3f normal;
    vec4f color;
} world_vertex;

typedef struct lit_vertex
{
    vec4f coord;
    vec4f color;
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

    matrix4x4f_mult_vec4f_(matrix4x4f_stack_top(&projection_stack), tv, lv->coord);
}

void screen_vertex_set_color(screen_vertex *sv, unsigned short r, unsigned short g, unsigned short b, unsigned short a)
{
    sv->r = r;
    sv->g = g;
    sv->b = b;
    sv->a = a;
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
    sv->r = unitclamp(lv->color[0]) * 255;
    sv->g = unitclamp(lv->color[1]) * 255;
    sv->b = unitclamp(lv->color[2]) * 255;
    sv->a = unitclamp(lv->color[3]) * 255;
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
    return the_viewport[0] == 0 && the_viewport[1] == XMAXSCREEN &&
           the_viewport[2] == 0 && the_viewport[3] == YMAXSCREEN;
}

void clear() { 
    if(cur_ptr_to_nextptr != NULL) {
        dl_element *e = element_next_in_object(CLEAR);
        return;
    }

    TRACE();

    // The clear() command must only clear the viewport. Use a slow rectangle when it's
    // not full-screen.
    if (is_full_viewport()) {
        // Full screen, we can use the optimized version.
        rasterizer_clear(current_color[0] * 255.0,
                current_color[1] * 255.0,
                current_color[2] * 255.0,
                current_color_index);
    } else {
        // Partial viewport, draw polygon. This uses the current color.
        bgnpolygon();
        pdri(0, 0, 0);
        pdri(0, 1, 0);
        pdri(1, 1, 0);
        pdri(1, 0, 0);
        endpolygon();
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
int getplanes() { 
    TRACE();
    return 24;
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
    for(int i = 0; i < 16; i++)
        patterns[index][i] = mask[i];

    // Flush cache.
    if (index == current_pattern) {
        // Send it again next time setpattern() is called.
        current_pattern = 0;
    }
}

void doublebuffer() { 
    // doublebuffer always enabled for now, more work here when/if singlebuffer is implemented
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
    return events_get_button(button);
}

// valuator = device with continuous input, like a mouse or dial
int getvaluator(int device) { 
    TRACEF("%d", device);
    return events_get_valuator(device);
}

void setvaluator(Device device, int init, int min, int max) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void setlinestyle(int index) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void gflush() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
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

    colormap[index][0] = red;
    colormap[index][1] = green;
    colormap[index][2] = blue;
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
    float fovy = fovy_ / 1800.0 * M_PI;

    float f = 1.0 / tan(fovy / 2.0);

    matrix4x4f_copy(m, identity_4x4f);
    m[0] = f / aspect;
    m[5] = f;
    m[10] = (far + near) / (near - far);
    m[11] = -1.0;
    m[14] = 2 * far * near / (near - far);
    m[15] = 0.0;
    if(matrix_mode == MSINGLE) {
        matrix4x4f_stack_load(&projection_stack, m);
        matrix4x4f_stack_load(&modelview_stack, identity_4x4f);
    } else 
        matrix4x4f_stack_load(current_stack, m);
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

    matrix4x4f_copy(m, identity_4x4f);
    m[0] =  2.0f / (right-left);
    m[5] =  2.0f / (top-bottom);
    m[10] = -1.0f;
    m[12] = -(right+left) / (right-left);
    m[13] = -(top+bottom) / (top-bottom);
    m[15] =  1.0f;

    if(matrix_mode == MSINGLE) {
        matrix4x4f_stack_load(&projection_stack, m);
        matrix4x4f_stack_load(&modelview_stack, identity_4x4f);
    } else 
        matrix4x4f_stack_load(current_stack, m);
}

void poly_(int n, Coord parray[ ][3]) {
    static world_vertex worldverts[POLY_MAX];
    vec4f color;
    vec4f_copy(color, current_color);

    for(int i = 0 ; i < n; i++) {
        vec4f_set(worldverts[i].coord,
            parray[i][0], parray[i][1], parray[i][2], 1.0);
        vec4f_copy(worldverts[i].color, color);
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

static int devices_queued[2048];

/* XXX event_get_qdevice() */
// We're interested in events from this device.
void qdevice(Device device) { 
    TRACEF("%d", device);

    devices_queued[device] = 1;

    switch (device) {
        case REDRAW:
            // Initial redraw.
            enqueue_device(REDRAW, 0);
            break;

        case INPUTCHANGE:
            // Tell app that this window has received input focus
            enqueue_device(INPUTCHANGE, 1);
            break;

        default:
            // Send the device to the server.
            events_qdevice(device);
            break;
    }
}

void unqdevice(Device device) {
    devices_queued[device] = 0;
    events_unqdevice(device);
}

// XXX events_qread_start
// XXX events_qread_continue
void fetch_event_queue() {
    int count = events_qread_start();

    // First is number of events.
    for (int i = 0; i < count; i++) {
        short value;
        int device = events_qread_continue(&value);
        enqueue_device(device, value);
    }
}

// If the queue is empty, qread() blocks.
int qread(short *val) { 
    TRACE();

    if (qtest())
    {
        *val = input_queue_val[input_queue_head];
        int device = input_queue_device[input_queue_head];
        input_queue_head = (input_queue_head + 1) % INPUT_QUEUE_SIZE;
        input_queue_length--;
        return device;
    }
    else
        return 0;
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
    events_set_framebuffer(rasterizer_frontbuffer());
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

    matrix4x4f_copy(m, identity_4x4f);

    m[0] = 2 * near / (right - left);
    m[5] = 2 * near / (top - bottom);
    m[8] = (right + left) / (right - left);
    m[9] = (top + bottom) / (top - bottom);
    m[10] = - (far + near) / (far - near);
    m[14] = - 2 * far * near / (far - near);
    if(matrix_mode == MSINGLE) {
        matrix4x4f_stack_load(&projection_stack, m);
        matrix4x4f_stack_load(&modelview_stack, identity_4x4f);
    } else {
        matrix4x4f_stack_load(&projection_stack, m);
    }
}

int winopen(char *title) {
    TRACEF("%s", title);
    int rasterizer_window = rasterizer_winopen(title);

    move(0.0, 0.0, 0.0);
    rasterizer_linewidth(the_linewidth);
    rasterizer_zbuffer(zbuffer_enabled);
    rasterizer_pattern(0);
    rasterizer_setpattern(patterns[0]);
    rasterizer_cbuffer_draw(frontbuffer_draw_enabled, backbuffer_draw_enabled);

    int events_window = events_winopen(title, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    events_set_framebuffer(rasterizer_frontbuffer());
    // XXX if we made a multi-window system, we'd tie "rasterizer_window"
    // and "events_window" together so we could pass the right identifier
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

void addtopup(long menu, char *add) {
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
    return 1; // TBD, temporarily disabled

    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }

    int which = 0;
    while(pups[which].defd) {
        which++;
        if(which == MAX_PUPS) {
            printf("warning: max pups exceeded\n");
            return -1;
        }
    }

    pup *thepup = pups + which;
    pup_new(thepup);

    char *menu2 = strdup(menu);
    char *menu3 = menu2;
    int nextvalue = 1;

    while(menu3) {
        char *item = strsep(&menu3, "|");
        int is_title = 0;
        
        int (*func)(int) = NULL;
        int value = -1;
        int submenu = -1;

        char *p = item;
        while(*p) {
            while(*p && *p != '%')
                p++;

            char *w = p;
            while(w >= item && *w == ' ')
                *w-- = '\0';

            *p++ = '\0';

            if(*p == 't') {
                is_title = 1;
                pup_set_title(thepup, item);
            } else if(*p == 'F') {
                /* thepup->func = XXX */
                printf("defpup argument %%F ignored\n");
            } else if(*p == 'f') {
                printf("defpup argument %%f ignored\n");
                /* func = XXX */
            } else if(*p == 'n') {
                printf("defpup argument %%n ignored\n");
                /* ??? XXX */
            } else if(*p == 'm') {
                printf("defpup argument %%m ignored\n");
                /* thepup->func = XXX */
            } else if(*p == 'x') {
                value = 0;
                while(*p && *p >= '0' && *p <= 9) {
                    value = value * 10 + *p - '0';
                    p++;
                }
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

    return which;
}

void sigwinch(int s)
{
    enqueue_device(RIGHTMOUSE, 1);
}

void siginfo(int s)
{
    enqueue_device(RIGHTMOUSE, 0);
}

const int menu_corner_top = YMAXSCREEN - 1 - 10;
const int menu_corner_left = 10;
const int menu_padding = 3; 
const int menu_item_separation = 2;
const int menu_items_gap = 8;

static int str_width_in_pixels(char *str) {
    int width = 0;
    for(int i = 0; i < strlen(str); i++) {
        if (str[i] == '\t') {
            width += font_width * 8;
        } else {
            width += font_width;
        }
    }
    return width;
}

void string_draw(screen_vertex* screenvert_, const char *str) {
    static screen_vertex screenvert;

    screenvert = *screenvert_;

    for(int i = 0; i < strlen(str); i++) {
        if (str[i] == '\t') {
            // I don't know whether the original charstr() supported tabs (I can't find
            // a man page), but arena/startup.c uses them. --LK
            screenvert.x += font_width * SCREEN_VERTEX_V2_SCALE * 8;
        } else {
            rasterizer_bitmap(font_width, font_rowbytes, font_height, &screenvert, font_bits + str[i] * font_height * font_rowbytes);
            screenvert.x += font_width * SCREEN_VERTEX_V2_SCALE;
        }
    }
}

// XXX rasterizer_draw() enqueue triangles
void draw_screen_aarect_filled(int r, int g, int b, float left, float top, float right, float bottom)
{
    screen_vertex q[4];

    for(int i = 0; i < 4; i++)
        screen_vertex_set_color(&q[i], r, g, b, 255);

    screen_vertex_set_position(&q[0], left, bottom);
    screen_vertex_set_position(&q[1], right, bottom);
    screen_vertex_set_position(&q[2], right, top);
    screen_vertex_set_position(&q[3], left, top);

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
void draw_screen_aarect_outline(int r, int g, int b, float left, float top, float right, float bottom)
{
    draw_screen_aarect_filled(r, g, b, left, top, left + 1, bottom);
    draw_screen_aarect_filled(r, g, b, right - 1, top, right, bottom);
    draw_screen_aarect_filled(r, g, b, left, top, right, top - 1);
    draw_screen_aarect_filled(r, g, b, left, bottom + 1, right, bottom);
}

void draw_screen_string(int r, int g, int b, float x, float y, const char *str) {
    screen_vertex sv;
    screen_vertex_set_color(&sv, r, g, b, 255);
    screen_vertex_set_position(&sv, x, y);
    string_draw(&sv, str);
}

void pup_draw(pup *p, int menu_left, int menu_top, int selected)
{
    int menu_text_pane_width = 0;

    int title_text_pane_height;

    // Size of title area
    if(p->title) {
        menu_text_pane_width = str_width_in_pixels(p->title);
        title_text_pane_height = font_height;
    } else {
        title_text_pane_height = menu_item_separation;
    }

    // Size of items area
    int items_text_pane_height = 0;
    for(int i = 0; i < p->item_count; i++) {
        int w = str_width_in_pixels(p->items[i].item);
        if(w > menu_text_pane_width)
            menu_text_pane_width = w;
        items_text_pane_height += font_height;
        if(i != p->item_count - 1)
            items_text_pane_height += menu_item_separation;
    }

    int title_fill_width = menu_padding * 2 + menu_text_pane_width;
    int title_fill_height = menu_padding * 2 + title_text_pane_height;

    int title_outline_left = menu_left;
    int title_outline_top = menu_top;
    int title_outline_right = title_outline_left + 2 + title_fill_width;
    int title_outline_bottom = title_outline_top - 2 - title_fill_height;

    int title_fill_left = title_outline_left + 1;
    int title_fill_top = title_outline_top - 1;
    int title_fill_right = title_outline_right - 1;
    int title_fill_bottom = title_outline_bottom + 1;

    int title_pane_left = title_fill_left + menu_padding;
    int title_pane_top = title_fill_top - menu_padding;

    // draw title:
    //  draw title border lines
    //  draw title box
    //  draw title string
    draw_screen_aarect_outline(0, 0, 0, title_outline_left, title_outline_top, title_outline_right, title_outline_bottom);
    draw_screen_aarect_filled(200, 200, 200, title_fill_left, title_fill_top, title_fill_right, title_fill_bottom);
    if(p->title) {
        draw_screen_string(0, 0, 0, title_pane_left, title_pane_top - font_height, p->title);
    }

    int items_fill_width = menu_padding * 2 + menu_text_pane_width;
    int items_fill_height = menu_padding * 2 + items_text_pane_height;

    int items_outline_left = menu_left;
    int items_outline_top = title_outline_bottom - menu_items_gap;
    int items_outline_right = items_outline_left + 2 + items_fill_width;
    int items_outline_bottom = items_outline_top - 2 - items_fill_height;

    int items_fill_left = items_outline_left + 1;
    int items_fill_top = items_outline_top - 1;
    int items_fill_right = items_outline_right - 1;
    int items_fill_bottom = items_outline_bottom + 1;

    int items_pane_left = items_fill_left + menu_padding;
    int items_pane_top = items_fill_top - menu_padding;

    // draw items:
    //  draw items border lines
    //  draw items box
    //  draw item strings
    draw_screen_aarect_outline(0, 0, 0, items_outline_left, items_outline_top, items_outline_right, items_outline_bottom);
    draw_screen_aarect_filled(255, 255, 255, items_fill_left, items_fill_top, items_fill_right, items_fill_bottom);
    int item_top = items_pane_top;
    for(int i = 0; i < p->item_count; i++) {
        if(i == selected) {
            draw_screen_aarect_filled(0, 0, 0, items_fill_left + 1, item_top + 2, items_fill_right - 1, item_top - font_height - 2);
            draw_screen_string(255, 255, 255, items_pane_left, item_top - font_height, p->items[i].item);
        }
        else
            draw_screen_string(0, 0, 0, items_pane_left, item_top - font_height, p->items[i].item);
            item_top -= font_height + menu_item_separation;
    }
}

int dopup(int pup_index) {

    return 0; // TODO: Locks up in browser currently.  Fix it, and with original SGI font.

    // Save previous drawing state
    int old_zbuffer = zbuffer_enabled;
    zbuffer(0);
    vec4f previous_color;
    vec4f_copy(previous_color, current_color);
    vec4f_set(current_color, .1, .1, .1, 1);

    pup *thepup = pups + pup_index;

    int larrow_queued = devices_queued[LEFTARROWKEY];
    int rarrow_queued = devices_queued[RIGHTARROWKEY];
    int uarrow_queued = devices_queued[UPARROWKEY];
    int darrow_queued = devices_queued[DOWNARROWKEY];

    qdevice(LEFTARROWKEY);
    qdevice(RIGHTARROWKEY);
    qdevice(UPARROWKEY);
    qdevice(DOWNARROWKEY);

    int selected = 0;
    int done = 0;
    while(!done) {
        clear();
        pup_draw(thepup, menu_corner_left, menu_corner_top, selected);
        swapbuffers();

        if(qtest() != 0) {
            short val;
            int device = qread(&val);
            switch(device) {
                case LEFTARROWKEY:
                    if(val)
                        return -1;
                    break;
                case RIGHTARROWKEY:
                    if(val)
                        done = 1;
                    break;
                case UPARROWKEY:
                    if(val)
                        if(selected > 0)
                            selected--;
                    break;
                case DOWNARROWKEY:
                    if(val)
                        if(selected < thepup->item_count)
                            selected++;
                    break;
            }
        }
    }

    if(!larrow_queued) unqdevice(LEFTARROWKEY);
    if(!rarrow_queued) unqdevice(RIGHTARROWKEY);
    if(!uarrow_queued) unqdevice(UPARROWKEY);
    if(!darrow_queued) unqdevice(DOWNARROWKEY);

    // Restore previous drawing state
    vec4f_copy(current_color, previous_color);
    zbuffer(old_zbuffer);

    return thepup->items[selected].value;
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

void freepup(int popup) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void drawmode(int drawmode) {
    static int warned = 0; if(!warned) { printf("%s not unimplemented\n", __FUNCTION__); warned = 1; }
}

void draw_(Coord x, Coord y, Coord z) {
    world_vertex v0, v1;
    vec4f_copy(v0.coord, current_position);
    vec3f_copy(v0.color, current_color);

    current_position[0] = x;
    current_position[1] = y;
    current_position[2] = z;

    vec4f_copy(v1.coord, current_position);
    vec3f_copy(v1.color, current_color);

    int save_lighting = lighting_enabled;
    lighting_enabled = 0;
    process_line(&v0, &v1);
    lighting_enabled = save_lighting;
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

void pdr2i(Icoord x, Icoord y) {
    pdr_(x, y, 0);
}

void pdri(Icoord x, Icoord y, Icoord z) {
    pdr_(x, y, z);
}

void pclos() {
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
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
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

void lmdef(int deftype, int index, int numpoints, float properties[]) {
    if(index == 0)
        abort();
    index -=1;
    float *p = properties;
    int next = 0;
    if(deftype == DEFMATERIAL) {
        material *m = &materials[index];
        if(trace_functions) printf("%*slmdef(DEFMATERIAL, %d, %d, {\n", trace_indent, "", index + 1, numpoints);
        while(*p != LMNULL) {
            switch((int)*p) {
                case DIFFUSE:
                    if(trace_functions) printf("%*sDIFFUSE, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set(m->diffuse, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case EMISSION:
                    if(trace_functions) printf("%*sEMISSION, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set(m->emission, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case AMBIENT:
                    if(trace_functions) printf("%*sAMBIENT, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set(m->ambient, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case SPECULAR:
                    if(trace_functions) printf("%*sSPECULAR, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set(m->specular, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case SHININESS:
                    if(trace_functions) printf("%*sSHININESS, %f,\n", trace_indent + 4, "", p[1]);
                    m->shininess = p[1];
                    p+= 2;
                    break;
                case ALPHA:
                    if(trace_functions) printf("%*sALPHA, %f,\n", trace_indent + 4, "", p[1]);
                    m->alpha = p[1];
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
                    vec3f_set(l->ambient, p[1], p[2], p[3]);
                    p+= 4;
                    break;
                case LCOLOR:
                    if(trace_functions) printf("%*sLCOLOR, %f, %f, %f,\n", trace_indent + 4, "", p[1], p[2], p[3]);
                    vec3f_set(l->color, p[1], p[2], p[3]);
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

int newpup() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
    return 0;
}

void prefposition(int x1, int x2, int y1, int y2) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void rdr2i(Icoord dx, Icoord dy) {
    TRACEF("%d, %d", dx, dy);

    world_vertex v0, v1;
    vec4f_copy(v0.coord, current_position);
    vec3f_copy(v0.color, current_color);

    current_position[0] += dx;
    current_position[1] += dy;

    vec4f_copy(v1.coord, current_position);
    vec3f_copy(v1.color, current_color);

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

// XXX events_tie
void tie(int button, int val1, int val2) {
    events_tie(button, val1, val2);
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
    vec4f_copy(wv->color, current_color);
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

int winattach() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
    return 0;
}

void winconstraints() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
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

void lsetdepth(int near, int far) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void depthcue(Boolean enable)
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

int getgdesc (int inquiry)
{
    switch(inquiry)
    {
        case GD_BITS_NORM_SNG_RED:
        case GD_BITS_NORM_SNG_GREEN:
        case GD_BITS_NORM_SNG_BLUE:
            return 8;       
    }

    static int warned = 0; if(!warned) { printf("%s %d unimplemented\n", __FUNCTION__, inquiry); warned = 1; }
    return 0;
}

void lshaderange (Colorindex lowin, Colorindex highin, long znear, long zfar)
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void qreset ()
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void smoothline (long mode)
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void zsource (long src)
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
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

    int code = classify_vertex(vert.coord);
    if(code != CLIP_ALL_IN)
        return;

    project_vertex(&vert, &screenvert);

    string_draw(&screenvert, str);
}

#define CIRCLE_SEGMENTS 80
static float circle_verts[CIRCLE_SEGMENTS][2];

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

    vec3f_copy(v0.color, current_color);
    vec3f_copy(v1.color, current_color);

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
    circi(x, y, r);
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

void cursoff() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void curson() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

void feedback() {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

int endfeedback() {
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
    viewport (0,XMAXSCREEN,0,YMAXSCREEN);

    int prev_matrix_mode = matrix_mode;
    mmode(MPROJECTION);
    pushmatrix();
    ortho2 (-0.5, XMAXSCREEN+0.5, -0.5, YMAXSCREEN+0.5);
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
    rasterizer_zbuffer(enable);
}

// XXX rasterizer_zclear()
// XXX display list
void zclear() {
    TRACE();

    if (!is_full_viewport()) {
        static int warned = 0; if(!warned) { printf("Partial zclear() unimplemented\n"); warned = 1; }
    }

    rasterizer_zclear(0xffffffff);
}

void zfunction(int func) {
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}

// XXX display list
void czclear(int color, int depth) {
    TRACE();
    rasterizer_czclear((color >> 16) & 0xff, (color >>  8) & 0xff, (color >>  0) & 0xff, color, depth);

    if (!is_full_viewport()) {
        static int warned = 0; if(!warned) { printf("Partial czclear() unimplemented\n"); warned = 1; }
    }
}

int gversion(char *version)
{
    strcpy(version, "GITHUB.COM/SGI-DEMOS");
    return 0;
}

#ifndef SIGINFO
#define SIGINFO 29
#endif

static void init_gl_state() __attribute__((constructor));
static void init_gl_state()
{
#if !defined(NDEBUG)
    if(getenv("TRACE_GL") != NULL)
        trace_functions = 1;
#endif

    for(int i = 0; i < MAX_PATTERNS; i++)
        for(int j = 0; j < 16; j++)
            patterns[i][j] = 0xffff;

    matrix4x4f_stack_init(&modelview_stack);
    matrix4x4f_stack_init(&projection_stack);
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

    for(int i = 0; i < MAX_PUPS; i++)
        pup_init(pups + i);

    //signal(SIGWINCH, sigwinch); // window changed event callback, maybe for window resizing
    //signal(SIGINFO, siginfo);   // status info event callback, Ctrl+T request for program info

    memset(devices_queued, 0, sizeof(devices_queued));
}

int readpixels(short number, Colorindex colors[ ])
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
    return 0;
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

void screenspace()
{
    static int warned = 0; if(!warned) { printf("%s unimplemented\n", __FUNCTION__); warned = 1; }
}