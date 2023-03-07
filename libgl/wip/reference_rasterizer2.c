#include <stdio.h>
#include <time.h>
#include <gl.h>
#include <math.h>
#include "rasterizer.h"

////////// network_rasterizer.c

static const int32_t DISPLAY_WIDTH = XMAXSCREEN + 1;
static const int32_t DISPLAY_HEIGHT = YMAXSCREEN + 1;

static int save_file_frame_number = 0;
static int save_file_last_frame = 12; //1 << 30;
static char *save_filename = NULL; // "save.txt";
static FILE *save_file = NULL;

////////// DisplayImage.m

#define WIDTH 800
#define HEIGHT 480
#define BYTES_PER_PIXEL 4
#define STRIDE (WIDTH*4)
#define NUM_VERTICES 3

// Type of Z-buffer pixel.
typedef uint16_t z_t;
// Shift to go from 32 bits to Z bits (0, 16, or 24).
#define Z_SHIFT 16
static z_t z_buffer[WIDTH*HEIGHT];

////////// reference_rasterizer.c

// SDL fast path is BGRA
#define BLUE_BYTE 0
#define GREEN_BYTE 1
#define RED_BYTE 2
#define ALPHA_BYTE 3

static bool gen_ppm_frame_files = 0;
static int ppm_frame_num = 0;

static float the_linewidth = 0;
static uint16_t the_pattern[16];
static int pattern_enabled = 0;
static int zbuffer_enabled = 0;

static uint8_t c_buffer[WIDTH*HEIGHT*4];
uint8_t *gl_backbuffer = (uint8_t *)&c_buffer;

////////// network_rasterizer.c

static float min(float a, float b)
{
    return (a < b) ? a : b;
}

static float clamp(float v, float low, float high)
{
    return v > high ? high : (v < low ? low : v);
}

void rasterizer_clear(uint8_t r, uint8_t g, uint8_t b)
{
    for(int i = 0; i < WIDTH*HEIGHT*4; i += 4) {
        c_buffer[i+BLUE_BYTE] = b;
        c_buffer[i+GREEN_BYTE] = g;
        c_buffer[i+RED_BYTE] = r;
        c_buffer[i+ALPHA_BYTE] = 0xff;
    }

    if(save_file) {
        fprintf(save_file, "clear %u %u %u\n", r, g, b);
    }
}

void rasterizer_linewidth(float w)
{
    the_linewidth = w;
    
    if(save_file)
        fprintf(save_file, "linewidth %f\n", w);
}

void rasterizer_setpattern(uint16_t pattern[16])
{
    for (int i = 0; i < 16; i++) {
	    the_pattern[i] = pattern[i];
    }

    if(save_file) {
        fprintf(save_file, "setpattern");
        for (int i = 0; i < 16; i++)
            fprintf(save_file, " %04X", pattern[i]);
        fprintf(save_file, "\n");
    }
}

void rasterizer_pattern(int enable)
{
    pattern_enabled = enable;

    if(save_file) {
        fprintf(save_file, "pattern %d\n", enable);
    }
}

static void flush()
{
    ////////// nonetwork.c
    static int count = 0;
    static time_t previoustime = 0;
    static int previouscount = 0;
    static int fps = 0;

    count++;
    time_t now = time(0);
    if(now - previoustime > 0) {
        fps = count - previouscount;
        printf("%d frames per second\n", fps);
        previoustime = now;
        previouscount = count;
    }
}

void rasterizer_swap()
{
    // copy back to front color buffer
    // memcpy(c_front_buffer, c_back_buffer, sizeof(c_front_buffer));

    if (gen_ppm_frame_files) 
    {
        uint8_t rgb_pixel[3];
        char name[128];
        sprintf(name, "frame%04d.ppm", ppm_frame_num++);
        FILE *fp = fopen(name, "wb");
        fprintf(fp, "P6 %d %d 255\n", DISPLAY_WIDTH, DISPLAY_HEIGHT);
        for(int i = 0; i < WIDTH*HEIGHT*4; i += 4) {
             // PPM expects RGB format
            rgb_pixel[0] = c_buffer[i+RED_BYTE];
            rgb_pixel[1] = c_buffer[i+GREEN_BYTE];
            rgb_pixel[2] = c_buffer[i+BLUE_BYTE];
            fwrite(rgb_pixel, 1, 3, fp);
        }
        fclose(fp);
    }
   
    if(save_file) {
        fprintf(save_file, "swap\n");
        if(save_file_frame_number++ == save_file_last_frame) {
            fflush(save_file);
            exit(EXIT_SUCCESS);
        }
        fprintf(save_file, "# frame %d\n", save_file_frame_number);
    }

    flush();
}

int32_t rasterizer_winopen(char *title)
{
    // See the ../NOTES file:
    if (save_filename == NULL)
        save_filename = getenv("SAVE_DRAWING_FILENAME");
    if (save_filename != NULL) {
        save_file = fopen(save_filename, "w");
        if(save_file == NULL) {
            fprintf(stderr, "Couldn't open \"%s\" for writing.\n", save_filename);
            exit(EXIT_FAILURE);
        } else {
            printf("Saving drawing commands to \"%s\".\n", save_filename);
            fprintf(save_file, "winopen %s\n", title);
            fprintf(save_file, "# frame 0\n");
        }
    }

    char *s = getenv("SAVE_DRAWING_LAST_FRAME");
    if(s != NULL) {
        save_file_last_frame = atoi(s);
    }
    if (save_file_last_frame > 0)
    {
        printf("Saving only %d frames\n", save_file_last_frame);
    }

    ////////// reference_rasterizer.c
    if(getenv("GEN_FRAME_PPM_FILES") != NULL) {
        gen_ppm_frame_files = 1;
        printf("Generating .PPM file for each frame\n");
    }

    return 1;
}

void rasterizer_zbuffer(int enable)
{
    zbuffer_enabled = enable;

    if(save_file) {
        fprintf(save_file, "z_buffer %d\n", enable);
    }
}

void rasterizer_zclear(uint32_t z)
{
    ////////// DisplayImage.m
    z_t *p = z_buffer;
    int count = WIDTH*HEIGHT;

    while (count-- > 0) {
	    *p++ = (z_t) 0xFFFFFFFF;
    }

    if(save_file) {
        fprintf(save_file, "zclear %u\n", z);
    }
}

void rasterizer_czclear(uint8_t r, uint8_t g, uint8_t b, uint32_t z)
{
    if(save_file) {
        fprintf(save_file, "czclear\n");
    }    
    rasterizer_zclear(z);
    rasterizer_clear(r, g, b);
}

void screen_vertex_offset_with_clamp(screen_vertex* v, float dx, float dy)
{
    v->x = clamp(v->x + dx * SCREEN_VERTEX_V2_SCALE, 0, (DISPLAY_WIDTH - 1) * SCREEN_VERTEX_V2_SCALE);
    v->y = clamp(v->y + dy * SCREEN_VERTEX_V2_SCALE, 0, (DISPLAY_HEIGHT - 1) * SCREEN_VERTEX_V2_SCALE);
}

////////// DisplayImage.m triangle rasterization BEGIN

// Returns on which side of the line (a,b) is the vertex (x,y). Or, returns
// twice the area of the triangle defined by the three vertices.
int edgeFunction(screen_vertex *a, screen_vertex *b, int x, int y) {
    return (b->x - a->x)*(y - a->y) - (b->y - a->y)*(x - a->x);
}

// Returns whether this edge is the top (horizontal) edge or a left
// edge of the triangle, as defined by D3D11.
// https://msdn.microsoft.com/en-us/library/windows/desktop/cc627092(v=vs.85).aspx#Triangle
//
// Since our vertices are always in counter-clockwise order, we can
// make some assumptions here.
bool isTopLeft(screen_vertex *a, screen_vertex *b) {
    if (a->y == b->y) {
        // If it's horizontal, then it's the top one if it's going left.
        return a->x < b->x;
    }

    // Else it's left if it's going down.
    return a->y > b->y;
}

static void rasterize_screen_triangle(screen_vertex *s0, screen_vertex *s1, screen_vertex *s2)
{
    screen_vertex vs[3] = {*s0, *s1, *s2};
    bool enableZbuffer = zbuffer_enabled;
    uint16_t *pattern = (uint16_t *)&the_pattern;
    uint8_t *data = (uint8_t *)&c_buffer;
    
    // Find bounding box of triangle on screen.
    int minX = WIDTH - 1;
    int minY = HEIGHT - 1;
    int maxX = 0;
    int maxY = 0;
    for (int i = 0; i < NUM_VERTICES; i++) {
        screen_vertex *v = &vs[i];

        // Temporary: Invert screen because libgl is giving us 0,0 in lower-left, but it's upper-left for us.
        v->y = HEIGHT - 1 - v->y;

        if (v->x < minX) minX = v->x;
        if (v->x > maxX) maxX = v->x;
        if (v->y < minY) minY = v->y;
        if (v->y > maxY) maxY = v->y;
    }

    // Clip to screen.
    if (minX < 0) minX = 0;
    if (minY < 0) minY = 0;
    if (maxX > WIDTH - 1) maxX = WIDTH - 1;
    if (maxY > HEIGHT - 1) maxY = HEIGHT - 1;

    // Reverse triangle if necessary to make it counter-clockwise.
    if (edgeFunction(&vs[0], &vs[1], vs[2].x, vs[2].y) < 0) {
        screen_vertex tmp = vs[0];
        vs[0] = vs[1];
        vs[1] = tmp;
    }

    // Set up edge equations.
    int x01 = vs[0].y - vs[1].y;
    int y01 = vs[1].x - vs[0].x;
    int x12 = vs[1].y - vs[2].y;
    int y12 = vs[2].x - vs[1].x;
    int x20 = vs[2].y - vs[0].y;
    int y20 = vs[0].x - vs[2].x;
    int w0_row = edgeFunction(&vs[1], &vs[2], minX, minY);
    int w1_row = edgeFunction(&vs[2], &vs[0], minX, minY);
    int w2_row = edgeFunction(&vs[0], &vs[1], minX, minY);
    // area is in s31.0 format.
    int32_t area = edgeFunction(&vs[0], &vs[1], vs[2].x, vs[2].y);
    if (area == 0) {
        // Empty triangle.
        return;
    }
    // recip_area is in s0.31 format.
    int64_t recip_area = 0x7FFFFFFFL / area;
    // Color.
    int64_t red_row = (w0_row*vs[0].r + w1_row*vs[1].r + w2_row*vs[2].r)*recip_area;
    int64_t red_incr = (x12*vs[0].r + x20*vs[1].r + x01*vs[2].r)*recip_area;
    int64_t red_row_incr = (y12*vs[0].r + y20*vs[1].r + y01*vs[2].r)*recip_area;
    int64_t green_row = (w0_row*vs[0].g + w1_row*vs[1].g + w2_row*vs[2].g)*recip_area;
    int64_t green_incr = (x12*vs[0].g + x20*vs[1].g + x01*vs[2].g)*recip_area;
    int64_t green_row_incr = (y12*vs[0].g + y20*vs[1].g + y01*vs[2].g)*recip_area;
    int64_t blue_row = (w0_row*vs[0].b + w1_row*vs[1].b + w2_row*vs[2].b)*recip_area;
    int64_t blue_incr = (x12*vs[0].b + x20*vs[1].b + x01*vs[2].b)*recip_area;
    int64_t blue_row_incr = (y12*vs[0].b + y20*vs[1].b + y01*vs[2].b)*recip_area;

    // The comparison value.
    int bias0 = isTopLeft(&vs[1], &vs[2]) ? 0 : 1;
    int bias1 = isTopLeft(&vs[2], &vs[0]) ? 0 : 1;
    int bias2 = isTopLeft(&vs[0], &vs[1]) ? 0 : 1;

    uint8_t *row_pixel = &data[(minY*WIDTH + minX)*BYTES_PER_PIXEL];
    z_t *row_zptr = &z_buffer[minY*WIDTH + minX];
    for (int y = minY; y <= maxY; y++) {
        uint8_t *p = row_pixel;
        z_t *zptr = row_zptr;
        int w0 = w0_row;
        int w1 = w1_row;
        int w2 = w2_row;
        int64_t red = red_row;
        int64_t green = green_row;
        int64_t blue = blue_row;
        uint16_t rowPattern = pattern == NULL ? 0xFFFF : pattern[y % 16];

        for (int x = minX; x <= maxX; x++) {
            // Check pattern.
            bool drawPixel = (rowPattern == 0xFFFF) || (rowPattern & (1 << (x % 16))) != 0;

            if (drawPixel && w0 >= bias0 && w1 >= bias1 && w2 >= bias2) {
                z_t z;

                if (enableZbuffer) {
                    uint64_t z64 = ((uint64_t)w0*vs[0].z + (uint64_t)w1*vs[1].z + (uint64_t)w2*vs[2].z)/area;
                    z = (z_t) (z64 >> Z_SHIFT);
                    drawPixel = (z <= *zptr);

                } else {
                    // Not sure this is correct. The man page of z_buffer() says that it only affects writing.
                    z = 0;
                }

                if (drawPixel) {
                    p[0] = red >> 31;
                    p[1] = green >> 31;
                    p[2] = blue >> 31;
                    if (enableZbuffer) {
                        *zptr = z;
                    }
                }
            }

            w0 += x12;
            w1 += x20;
            w2 += x01;
            red += red_incr;
            green += green_incr;
            blue += blue_incr;
            p += BYTES_PER_PIXEL;
            zptr++;
        }

        w0_row += y12;
        w1_row += y20;
        w2_row += y01;
        red_row += red_row_incr;
        green_row += green_row_incr;
        blue_row += blue_row_incr;
        row_pixel += STRIDE;
        row_zptr += WIDTH;
    }
}

////////// DisplayImage.m triangle rasterization END

void rasterizer_bitmap(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *bits)
{
    screen_vertex s[4];

    for(int j = 0; j < height; j++) {
        int prevbit = 0;
        int count;
        for(int i = 0; i < width; i++) {
            int bit = (bits[j * rowbytes + i / 8] >> (7 - i % 8)) & 1;

            if(bit) {

                if(!prevbit && bit) {
                    // Previous bit was 0 and this bit is 1, so start a
                    // run
                    for(int k = 0; k < 4; k++) {
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

            } else if(prevbit) {

                // The previous bit was 1 and this bit is 0, so
                // finish the run
                screen_vertex_offset_with_clamp(&s[2], count, 1);
                screen_vertex_offset_with_clamp(&s[3], count, 0);

                rasterize_screen_triangle(&s[0], &s[1], &s[2]);
                rasterize_screen_triangle(&s[2], &s[3], &s[0]);
            }

            prevbit = bit;
        }

        if(prevbit) {
            // the end of the row was a 1 bit, so finish run
            screen_vertex_offset_with_clamp(&s[2], count, 1);
            screen_vertex_offset_with_clamp(&s[3], count, 0);

            rasterize_screen_triangle(&s[0], &s[1], &s[2]);
            rasterize_screen_triangle(&s[2], &s[3], &s[0]);
        }
    }
    if(save_file) {
        fprintf(save_file, "bitmap\n");
        fprintf(save_file, " %u %u %u\n", width, rowbytes, height);
        fprintf(save_file, " %u %u %u %u %u %u\n", sv->x, sv->y, sv->z, sv->r, sv->g, sv->b);
        for(int j = 0; j < height; j++)
            for(int i = 0; i < rowbytes; i++)
                fprintf(save_file, " %20X", bits[j * rowbytes + i]);
        fprintf(save_file, "\n");
    }
}

void draw_line_as_triangles(screen_vertex *v0, screen_vertex *v1)
{

// Fake this with screen quads until rasterizer implements lines
    float dx = (v1->x - v0->x);
    float dy = (v1->y - v0->y);
    float d = sqrt(dx * dx + dy * dy);

    if(d == 0.0) {
        // XXX should draw point if the line is too short
        return;
    }

    screen_vertex q[4];
    q[0] = *v0;
    q[1] = *v0;
    q[2] = *v1;
    q[3] = *v1;

    if(fabs(dx) > fabs(dy)) {
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

    rasterize_screen_triangle(&q[0], &q[1], &q[2]);
    rasterize_screen_triangle(&q[2], &q[3], &q[0]);
}


void rasterizer_draw(uint32_t type, uint32_t count, screen_vertex *screenverts)
{
    switch(type) {
        default:
            fprintf(stderr, "Unimplemented draw type %d.\n", type);
            return;
            break;

        case DRAW_POINTS:
            fprintf(stderr, "POINTS not implemented\n");
            return;
            break;

        case DRAW_LINES:
            for(int i = 0; i < count / 2; i++) { 
                draw_line_as_triangles(&screenverts[i * 2 + 0], &screenverts[i * 2 + 1]);
            }
            break;

        case DRAW_TRIANGLES:
            for(int i = 0; i < count / 3; i++)
                rasterize_screen_triangle(&screenverts[i * 3], &screenverts[i * 3 + 1], &screenverts[i * 3 + 2]);
            break;
    }

    if(save_file) {
        fprintf(save_file, "draw %d %d\n", type, count);
        for(int i = 0; i < count; i++)
            fprintf(save_file, " %u %u %u %u %u %u\n", screenverts[i].x, screenverts[i].y, screenverts[i].z, screenverts[i].r, screenverts[i].g, screenverts[i].b);
    }
}

