#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#include <gl.h>
#include "rasterizer.h"

static const int32_t DISPLAY_WIDTH = XMAXSCREEN + 1;
static const int32_t DISPLAY_HEIGHT = YMAXSCREEN + 1;

// SDL wants BGRA
#define BLUE_BYTE 0
#define GREEN_BYTE 1
#define RED_BYTE 2

static int gen_ppm_frame_files = 0;
static int snap_vertices = 0;

static float the_linewidth;
static uint16_t the_pattern[16];
static int pattern_enabled = 0;
static int rgb_mode = 0; // color map mode by default

// double color buffers
static int backbuffer_draw_enabled = 1;
static int frontbuffer_draw_enabled = 0;
typedef unsigned char color_buffer_t[YMAXSCREEN + 1][XMAXSCREEN + 1][4]; // uchar = 8 bits = 1 byte * 800 * 480 * 4 = 1.53M * 2 = 3.06M
static color_buffer_t c_buffer_1;
static color_buffer_t c_buffer_2;
static color_buffer_t *gl_backbuffer = &c_buffer_1;  // render to back buffer
static color_buffer_t *gl_frontbuffer = &c_buffer_2; // display from front buffer

typedef unsigned short color_index_buffer_t[YMAXSCREEN + 1][XMAXSCREEN + 1]; // short = 16 bits = 2 bytes * 800 * 480 = 640K * 2 = 1.28M
static color_index_buffer_t ci_buffer_1;
static color_index_buffer_t ci_buffer_2;

// z buffer
static int zbuffer_enabled = 0;
typedef uint16_t z_t;
static const int Z_SHIFT = 16; // Shift computed 32-bit Z into 16-bit Z buffer 
static const unsigned int Z_MAX = 0xffffffff;
// Should we just 'upgrade' GL to 32-bit Z since we computed it?
//typedef uint32_t z_t;
//static const int Z_SHIFT = 0; 
static z_t z_buffer[YMAXSCREEN + 1][XMAXSCREEN + 1];

static float min(float a, float b)
{
    return (a < b) ? a : b;
}

static float clamp(float v, float low, float high)
{
    return v > high ? high : (v < low ? low : v);
}

static void clear_cbuffer(int draw_enabled, color_buffer_t* buffer, uint8_t r, uint8_t g, uint8_t b)
{
    if (draw_enabled) {    
        for (int j = 0; j < DISPLAY_HEIGHT; j++)
            for (int i = 0; i < DISPLAY_WIDTH; i++) {
                (*buffer)[j][i][RED_BYTE] = r;
                (*buffer)[j][i][GREEN_BYTE] = g;
                (*buffer)[j][i][BLUE_BYTE] = b;
            }
    }
}

void rasterizer_clear(uint8_t r, uint8_t g, uint8_t b, short color_index)
{
    clear_cbuffer(backbuffer_draw_enabled, gl_backbuffer, r, g, b);
    clear_cbuffer(frontbuffer_draw_enabled, gl_frontbuffer, r, g, b);
}

void rasterizer_linewidth(float w)
{
    the_linewidth = w;
}

void rasterizer_setpattern(uint16_t pattern[16])
{
    for (int i = 0; i < 16; i++) {
        the_pattern[i] = pattern[i];
    }
}

void rasterizer_pattern(int enable)
{
    pattern_enabled = enable;
}

unsigned char* rasterizer_frontbuffer()
{
    return (unsigned char*)gl_frontbuffer;
}

void rasterizer_swap()
{
    // swap back buffer (buffer being rasterized) and front buffer (buffer being displayed)
    color_buffer_t *_gl_backbuffer = gl_backbuffer; gl_backbuffer = gl_frontbuffer; gl_frontbuffer = _gl_backbuffer;

    // optionally dump frames to ppm files
    static int frame = 0;
    if (gen_ppm_frame_files) 
    {
        unsigned char rgb_pixel[3];
        char name[128];
        sprintf(name, "frame%04d.ppm", frame);
        FILE *fp = fopen(name, "wb");
        fprintf(fp, "P6 %d %d 255\n", DISPLAY_WIDTH, DISPLAY_HEIGHT);
            for (int j = 0; j < DISPLAY_HEIGHT; j++) {
                for (int i = 0; i < DISPLAY_WIDTH; i++) {
                    // PPM expects RGB format
                    rgb_pixel[0] = (*gl_backbuffer)[j][i][RED_BYTE];
                    rgb_pixel[1] = (*gl_backbuffer)[j][i][GREEN_BYTE];
                    rgb_pixel[2] = (*gl_backbuffer)[j][i][BLUE_BYTE];                   
                    fwrite(rgb_pixel, 1, 3, fp);
                }
            }
        fclose(fp);
    }

    frame++;
}

int32_t rasterizer_winopen(char *title)
{
    rasterizer_clear(0, 0, 0, 0);
    rasterizer_zclear(Z_MAX);

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

void rasterizer_rgbmode(int enable)
{
    rgb_mode = enable;
}

void rasterizer_cbuffer_draw(int enable_front, int enable_back)
{
    frontbuffer_draw_enabled = enable_front;
    backbuffer_draw_enabled = enable_back;
}

void rasterizer_zbuffer(int enable)
{
    zbuffer_enabled = enable;
}

void rasterizer_zclear(uint32_t z)
{
    for (int j = 0; j < DISPLAY_HEIGHT; j++)
        for (int i = 0; i < DISPLAY_WIDTH; i++)
            z_buffer[j][i] = z;
}

void rasterizer_czclear(uint8_t r, uint8_t g, uint8_t b, short color_index, uint32_t z)
{
    rasterizer_zclear(z);
    rasterizer_clear(r, g, b, color_index);
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

static void set_buffer_pixel(int draw_enabled, color_buffer_t* buffer, int y, int x, uint8_t r, uint8_t g, uint8_t b)
{                  
    if (draw_enabled) 
    {
        (*buffer)[y][x][RED_BYTE] = r;
        (*buffer)[y][x][GREEN_BYTE] = g;
        (*buffer)[y][x][BLUE_BYTE] = b;
    }
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

    uint8_t r = (uint8_t)clamp(bary[0] * s[0].r + bary[1] * s[1].r + bary[2] * s[2].r, 0.0, UCHAR_MAX);
    uint8_t g = (uint8_t)clamp(bary[0] * s[0].g + bary[1] * s[1].g + bary[2] * s[2].g, 0.0, UCHAR_MAX);
    uint8_t b = (uint8_t)clamp(bary[0] * s[0].b + bary[1] * s[1].b + bary[2] * s[2].b, 0.0, UCHAR_MAX);

    z_t z = sz_to_zbuffer(bary[0] * s[0].z + bary[1] * s[1].z + bary[2] * s[2].z);

    int buffer_y = DISPLAY_HEIGHT - 1 - y;

    if (!zbuffer_enabled || (z < z_buffer[buffer_y][x])) {
        set_buffer_pixel(backbuffer_draw_enabled, gl_backbuffer, buffer_y, x, r, g, b);
        set_buffer_pixel(frontbuffer_draw_enabled, gl_frontbuffer, buffer_y, x, r, g, b);
        z_buffer[buffer_y][x] = z;
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
    static int viewport[4] = {0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT};
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

void rasterizer_bitmap(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *bits)
{
    screen_vertex s[4];

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
    
    int x = clamp(v[0], 0, DISPLAY_WIDTH);
    int y = clamp(v[1], 0, DISPLAY_HEIGHT);
    z_t z = sz_to_zbuffer(s.z);

    int buffer_y = DISPLAY_HEIGHT - 1 - y;
    if (!zbuffer_enabled || (z < z_buffer[buffer_y][x])) {
        set_buffer_pixel(backbuffer_draw_enabled, gl_backbuffer, buffer_y, x, s.r, s.g, s.b);
        set_buffer_pixel(frontbuffer_draw_enabled, gl_frontbuffer, buffer_y, x, s.r, s.g, s.b);
        z_buffer[buffer_y][x] = z;
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

void rasterizer_draw(uint32_t type, uint32_t count, screen_vertex *screenverts)
{
    int i;
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