//
// GLES2 (GPU) rasterizer
//
// Implements the rasterizer interface with OpenGL ES2 draw calls instead of
// the CPU reference rasterizer. Selected via rasterizer.c dispatch
// (GLES2_RASTERIZER=gles2 native, ?rast=gles2 web).
//
// Design:
//  - Primitives are batched into a vertex array (points and lines are
//    expanded into quads exactly the way the reference rasterizer does)
//    and flushed with one glDrawArrays(GL_TRIANGLES) per color buffer.
//  - IRIS GL's double-buffered model is mirrored with two offscreen FBOs
//    (front and back), each with an RGBA color texture and a 16-bit depth
//    renderbuffer (the reference rasterizer's z-buffer is also 16-bit).
//  - After each swap (or any operation that touches the front buffer) the
//    front FBO is read back into a CPU BGRA buffer, so the existing SDL
//    display and events code paths work unchanged in both modes.
//  - GL resources are created lazily on the first call after the SDL window
//    and GL context exist (rasterizer_winopen is called before the window
//    is created, so nothing GL can happen there).
//  - The screen-door pattern is implemented in the fragment shader by
//    sampling a 16x16 alpha texture at gl_FragCoord and discarding.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include <SDL.h>
#include <SDL_opengles2.h>

#include <gl.h> // XMAXSCREEN / YMAXSCREEN
#include "rasterizer.h"
#include "sdl_framebuffer.h"

#define FB_WIDTH  (XMAXSCREEN + 1)
#define FB_HEIGHT (YMAXSCREEN + 1)

// CPU front buffer byte order must match the reference rasterizer (BGRA for SDL)
#define BLUE_BYTE 0
#define GREEN_BYTE 1
#define RED_BYTE 2
#define ALPHA_BYTE 3

//
// pipeline state (mirrors reference rasterizer semantics)
//
static float the_linewidth = 1.0f;
static uint16_t the_pattern[16];
static int pattern_enabled = 0;
static int pattern_dirty = 1;
static int rgb_mode = 0;
static int zbuffer_enabled = 0;
static int backbuffer_draw_enabled = 1;
static int frontbuffer_draw_enabled = 0;
static int gen_ppm_frame_files = 0;

// clear values recorded before the GL context exists (applied at lazy init)
static uint8_t pend_clear_rgb[3] = {0, 0, 0};
static uint32_t pend_clear_z = 0xffffffffu;

//
// GL objects
//
typedef struct gl_buffer
{
    GLuint fbo;
    GLuint tex;
} gl_buffer;

static gl_buffer buffers[2];
static gl_buffer *back_buf = &buffers[0];
static gl_buffer *front_buf = &buffers[1];

// One depth renderbuffer shared by both FBOs, matching the reference
// rasterizer's single z-buffer (front and back share z state there too)
static GLuint shared_depth_rb = 0;

static GLuint draw_prog = 0;        // batched geometry program
static GLint  u_draw_scale = -1;    // 2/W, 2/H pixel->NDC scale
static GLint  u_draw_pattern_on = -1;
static GLint  u_draw_pattern_tex = -1;

static GLuint blit_prog = 0;        // alpha_blit program (textured, blended)
static GLint  u_blit_scale = -1;
static GLint  u_blit_color = -1;
static GLint  u_blit_tex = -1;

static GLuint pattern_tex = 0;      // 16x16 alpha texture of the_pattern
static GLuint blit_tex = 0;         // scratch texture for alpha_blit
static GLuint batch_vbo = 0;
static GLuint blit_vbo = 0;

static int gl_ready = 0;

//
// CPU front buffer (what the SDL display and events layers consume)
//
static unsigned char cpu_front[FB_HEIGHT][FB_WIDTH][4];    // BGRA, row 0 = top
static unsigned char readback_rgba[FB_HEIGHT][FB_WIDTH][4]; // RGBA, row 0 = bottom (GL order)
static int front_dirty = 0; // front FBO has content not yet in cpu_front

//
// vertex batch — everything becomes GL_TRIANGLES
//
typedef struct gpu_vertex
{
    float x, y, z;      // x,y in pixels, z in [0,1]
    uint8_t rgba[4];
} gpu_vertex;

#define BATCH_MAX_VERTS (64 * 1024)
static gpu_vertex batch[BATCH_MAX_VERTS];
static int batch_count = 0;

// Pattern state captured for the current batch contents. The reference
// applies the screen-door pattern in triPixel, which triangles, wide lines
// and bitmap glyphs go through — but points are written directly and are
// never stippled. Emitters declare which they need; a mismatch flushes.
static int batch_pattern_on = 0;

//
// shaders
//
static const GLchar *draw_vs_src =
    "attribute vec3 pos;                                                \n" // x,y pixels, z [0,1]
    "attribute vec4 color;                                              \n"
    "varying vec4 v_color;                                              \n"
    "uniform vec2 scale;                                                \n" // 2/W, 2/H
    "void main()                                                        \n"
    "{                                                                  \n"
    "    gl_Position = vec4(pos.x * scale.x - 1.0,                      \n"
    "                       pos.y * scale.y - 1.0,                      \n"
    "                       pos.z * 2.0 - 1.0, 1.0);                    \n"
    "    v_color = color;                                               \n"
    "}                                                                  \n";

static const GLchar *draw_fs_src =
    "precision mediump float;                                           \n"
    "varying vec4 v_color;                                              \n"
    "uniform sampler2D pattern_tex;                                     \n"
    "uniform float pattern_on;                                          \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    if (pattern_on > 0.5)                                          \n"
    "    {                                                              \n"
    "        vec2 pc = mod(gl_FragCoord.xy, 16.0) / 16.0;               \n"
    "        if (texture2D(pattern_tex, pc).a < 0.5)                    \n"
    "            discard;                                               \n"
    "    }                                                              \n"
    "    gl_FragColor = v_color;                                        \n"
    "}                                                                  \n";

static const GLchar *blit_vs_src =
    "attribute vec3 pos;                                                \n"
    "attribute vec2 uv;                                                 \n"
    "varying vec2 v_uv;                                                 \n"
    "uniform vec2 scale;                                                \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    gl_Position = vec4(pos.x * scale.x - 1.0,                      \n"
    "                       pos.y * scale.y - 1.0,                      \n"
    "                       0.0, 1.0);                                  \n"
    "    v_uv = uv;                                                     \n"
    "}                                                                  \n";

static const GLchar *blit_fs_src =
    "precision mediump float;                                           \n"
    "varying vec2 v_uv;                                                 \n"
    "uniform sampler2D blit_tex;                                        \n"
    "uniform vec4 color;                                                \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    gl_FragColor = vec4(color.rgb, texture2D(blit_tex, v_uv).a);   \n"
    "}                                                                  \n";

static float clampf(float v, float low, float high)
{
    return v > high ? high : (v < low ? low : v);
}

//
// GL setup
//

static GLuint build_shader(GLenum type, const GLchar *src, const char *name)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), NULL, log);
        printf("ERROR: gles2 rasterizer %s shader build FAILED:\n%s\n", name, log);
    }
    return shader;
}

static GLuint build_program(const GLchar *vs_src, const GLchar *fs_src,
                            const char *attr0, const char *attr1, const char *name)
{
    GLuint vs = build_shader(GL_VERTEX_SHADER, vs_src, name);
    GLuint fs = build_shader(GL_FRAGMENT_SHADER, fs_src, name);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glBindAttribLocation(prog, 0, attr0);
    glBindAttribLocation(prog, 1, attr1);
    glLinkProgram(prog);

    GLint success = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success)
    {
        char log[1024];
        glGetProgramInfoLog(prog, sizeof(log), NULL, log);
        printf("ERROR: gles2 rasterizer %s program link FAILED:\n%s\n", name, log);
    }
    else
        printf("INFO: gles2 rasterizer %s program id %d build OK\n", name, prog);

    return prog;
}

static void create_buffer(gl_buffer *b)
{
    glGenTextures(1, &b->tex);
    glBindTexture(GL_TEXTURE_2D, b->tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FB_WIDTH, FB_HEIGHT, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glGenFramebuffers(1, &b->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, b->fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, b->tex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, shared_depth_rb);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR: gles2 rasterizer FBO incomplete: 0x%x\n", status);
}

static void clear_gl_buffers(uint8_t r, uint8_t g, uint8_t b,
                             int clear_front, int clear_back, GLbitfield mask);

// Create all GL resources on the first call after the SDL window/GL context
// exists. Returns 0 (and does nothing) if the context isn't up yet.
static int ensure_gl(void)
{
    if (gl_ready)
        return 1;
    if (!sdlGLContextReady())
        return 0;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 4);

    draw_prog = build_program(draw_vs_src, draw_fs_src, "pos", "color", "draw");
    u_draw_scale = glGetUniformLocation(draw_prog, "scale");
    u_draw_pattern_on = glGetUniformLocation(draw_prog, "pattern_on");
    u_draw_pattern_tex = glGetUniformLocation(draw_prog, "pattern_tex");

    blit_prog = build_program(blit_vs_src, blit_fs_src, "pos", "uv", "blit");
    u_blit_scale = glGetUniformLocation(blit_prog, "scale");
    u_blit_color = glGetUniformLocation(blit_prog, "color");
    u_blit_tex = glGetUniformLocation(blit_prog, "blit_tex");

    glGenTextures(1, &pattern_tex);
    glBindTexture(GL_TEXTURE_2D, pattern_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 16, 16, 0,
                 GL_ALPHA, GL_UNSIGNED_BYTE, NULL);
    pattern_dirty = 1;

    glGenTextures(1, &blit_tex);
    glBindTexture(GL_TEXTURE_2D, blit_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenBuffers(1, &batch_vbo);
    glGenBuffers(1, &blit_vbo);

    glGenRenderbuffers(1, &shared_depth_rb);
    glBindRenderbuffer(GL_RENDERBUFFER, shared_depth_rb);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, FB_WIDTH, FB_HEIGHT);

    create_buffer(&buffers[0]);
    create_buffer(&buffers[1]);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    gl_ready = 1;

    // apply clears recorded before the context existed (winopen clears to
    // black / max z); clear both buffers regardless of draw enables
    glClearDepthf((GLfloat)(pend_clear_z / 4294967295.0));
    clear_gl_buffers(pend_clear_rgb[0], pend_clear_rgb[1], pend_clear_rgb[2],
                     1, 1, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    printf("INFO: gles2 rasterizer initialized (%dx%d front/back FBOs)\n", FB_WIDTH, FB_HEIGHT);
    return 1;
}

//
// batch flush
//

static void upload_pattern_if_dirty(void)
{
    if (!pattern_dirty)
        return;

    // expand the 16x16 bit pattern into an alpha texture; row j corresponds
    // to screen y % 16 == j (gl_FragCoord is y-up, same as the pattern's
    // indexing in the reference rasterizer)
    uint8_t texels[16][16];
    for (int j = 0; j < 16; j++)
        for (int i = 0; i < 16; i++)
            texels[j][i] = (the_pattern[j] & (1 << i)) ? 255 : 0;

    glBindTexture(GL_TEXTURE_2D, pattern_tex);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 16, 16, GL_ALPHA, GL_UNSIGNED_BYTE, texels);
    pattern_dirty = 0;
}

static void flush_batch(void)
{
    if (batch_count == 0 || !gl_ready)
    {
        batch_count = 0;
        return;
    }

    upload_pattern_if_dirty();

    glBindBuffer(GL_ARRAY_BUFFER, batch_vbo);
    glBufferData(GL_ARRAY_BUFFER, batch_count * sizeof(gpu_vertex), batch, GL_STREAM_DRAW);

    glUseProgram(draw_prog);
    glUniform2f(u_draw_scale, 2.0f / FB_WIDTH, 2.0f / FB_HEIGHT);
    glUniform1f(u_draw_pattern_on, batch_pattern_on ? 1.0f : 0.0f);
    glUniform1i(u_draw_pattern_tex, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pattern_tex);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(gpu_vertex), (void *)0);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(gpu_vertex),
                          (void *)offsetof(gpu_vertex, rgba));

    // The reference rasterizer writes z whenever a pixel passes, even with
    // the z-buffer disabled; GL_ALWAYS with depth writes on matches that.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(zbuffer_enabled ? GL_LESS : GL_ALWAYS);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glViewport(0, 0, FB_WIDTH, FB_HEIGHT);

    if (backbuffer_draw_enabled)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, back_buf->fbo);
        glDrawArrays(GL_TRIANGLES, 0, batch_count);
    }
    if (frontbuffer_draw_enabled)
    {
        // With the shared depth buffer, a preceding back-buffer pass already
        // wrote these fragments' z values; GL_LESS would reject them all.
        // GL_LEQUAL lets the front pass land the same pixels the reference's
        // single test-once-write-both z logic would.
        if (backbuffer_draw_enabled && zbuffer_enabled)
            glDepthFunc(GL_LEQUAL);
        glBindFramebuffer(GL_FRAMEBUFFER, front_buf->fbo);
        glDrawArrays(GL_TRIANGLES, 0, batch_count);
        front_dirty = 1;
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    batch_count = 0;
}

//
// front buffer readback: front FBO -> cpu_front (BGRA, row 0 = top)
//
static void sync_front_to_cpu(void)
{
    if (!gl_ready)
        return;

    glBindFramebuffer(GL_FRAMEBUFFER, front_buf->fbo);
    glReadPixels(0, 0, FB_WIDTH, FB_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, readback_rgba);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // swizzle RGBA -> BGRA and flip vertically (GL row 0 is the bottom row)
    for (int j = 0; j < FB_HEIGHT; j++)
    {
        unsigned char (*src)[4] = readback_rgba[FB_HEIGHT - 1 - j];
        unsigned char (*dst)[4] = cpu_front[j];
        for (int i = 0; i < FB_WIDTH; i++)
        {
            dst[i][BLUE_BYTE] = src[i][2];
            dst[i][GREEN_BYTE] = src[i][1];
            dst[i][RED_BYTE] = src[i][0];
            dst[i][ALPHA_BYTE] = 255;
        }
    }

    front_dirty = 0;
}

//
// clears
//
static void clear_gl_buffers(uint8_t r, uint8_t g, uint8_t b,
                             int clear_front, int clear_back, GLbitfield mask)
{
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    glDepthMask(GL_TRUE);

    if (clear_back)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, back_buf->fbo);
        glClear(mask);
    }
    if (clear_front)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, front_buf->fbo);
        glClear(mask);
        if (mask & GL_COLOR_BUFFER_BIT)
            front_dirty = 1;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void gles2_rasterizer_clear(uint8_t r, uint8_t g, uint8_t b, short color_index)
{
    if (!ensure_gl())
    {
        pend_clear_rgb[0] = r; pend_clear_rgb[1] = g; pend_clear_rgb[2] = b;
        return;
    }
    flush_batch();
    clear_gl_buffers(r, g, b, frontbuffer_draw_enabled, backbuffer_draw_enabled,
                     GL_COLOR_BUFFER_BIT);
}

void gles2_rasterizer_zclear(uint32_t z)
{
    if (!ensure_gl())
    {
        pend_clear_z = z;
        return;
    }
    flush_batch();
    glClearDepthf((GLfloat)(z / 4294967295.0));
    // both FBOs share one depth renderbuffer (like the reference's single
    // z-buffer), so one clear through either FBO clears it for both
    clear_gl_buffers(0, 0, 0, 0, 1, GL_DEPTH_BUFFER_BIT);
}

void gles2_rasterizer_czclear(uint8_t r, uint8_t g, uint8_t b, short color_index, uint32_t z)
{
    gles2_rasterizer_zclear(z);
    gles2_rasterizer_clear(r, g, b, color_index);
}

//
// buffer management
//

void gles2_rasterizer_swap(void)
{
    flush_batch();

    // optionally dump frames to ppm files; like the reference rasterizer,
    // the frame dumped at swap N is the frame presented at swap N-1
    static int frame = 0;
    if (gen_ppm_frame_files && gl_ready)
    {
        char name[128];
        sprintf(name, "frame%04d.ppm", frame);
        FILE *fp = fopen(name, "wb");
        if (fp)
        {
            fprintf(fp, "P6 %d %d 255\n", FB_WIDTH, FB_HEIGHT);
            for (int j = 0; j < FB_HEIGHT; j++)
            {
                for (int i = 0; i < FB_WIDTH; i++)
                {
                    unsigned char rgb_pixel[3];
                    rgb_pixel[0] = cpu_front[j][i][RED_BYTE];
                    rgb_pixel[1] = cpu_front[j][i][GREEN_BYTE];
                    rgb_pixel[2] = cpu_front[j][i][BLUE_BYTE];
                    fwrite(rgb_pixel, 1, 3, fp);
                }
            }
            fclose(fp);
        }
    }
    frame++;

    // exchange front and back, then refresh the CPU copy of the new front
    gl_buffer *tmp = back_buf;
    back_buf = front_buf;
    front_buf = tmp;

    sync_front_to_cpu();
}

void gles2_rasterizer_copy_front_to_back(void)
{
    if (!ensure_gl())
        return;
    flush_batch();

    glBindFramebuffer(GL_FRAMEBUFFER, front_buf->fbo);
    glBindTexture(GL_TEXTURE_2D, back_buf->tex);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, FB_WIDTH, FB_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void gles2_rasterizer_copy_back_to_front(void)
{
    if (!ensure_gl())
        return;
    flush_batch();

    glBindFramebuffer(GL_FRAMEBUFFER, back_buf->fbo);
    glBindTexture(GL_TEXTURE_2D, front_buf->tex);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, FB_WIDTH, FB_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    front_dirty = 1;
    sync_front_to_cpu();
}

unsigned char* gles2_rasterizer_frontbuffer(void)
{
    return (unsigned char *)cpu_front;
}

// Called once per presented frame (events_frame_complete), to allow the
// GPU rasterizer to flush pending batched geometry and read back the
// front buffer; no-op for the CPU reference rasterizer.
void gles2_rasterizer_frame_sync(void)
{
    if (!gl_ready)
        return;
    if (batch_count > 0)
        flush_batch();
    if (front_dirty)
        sync_front_to_cpu();
}

//
// primitive batching — points and lines expand to quads exactly like the
// reference rasterizer, so geometry matches pixel-for-pixel where possible
//

static void batch_reserve(int verts_needed)
{
    if (batch_count + verts_needed > BATCH_MAX_VERTS)
        flush_batch();
}

static void batch_select_pattern(int want_pattern)
{
    if (batch_count > 0 && want_pattern != batch_pattern_on)
        flush_batch();
    batch_pattern_on = want_pattern;
}

static void emit_vertex(float x, float y, float z01, uint8_t r, uint8_t g, uint8_t b)
{
    gpu_vertex *v = &batch[batch_count++];
    v->x = x;
    v->y = y;
    v->z = z01;
    v->rgba[0] = r;
    v->rgba[1] = g;
    v->rgba[2] = b;
    v->rgba[3] = 255;
}

static float sv_z01(screen_vertex *s)
{
    return (float)((double)s->z / 4294967295.0);
}

static void emit_screen_triangle(screen_vertex *s0, screen_vertex *s1, screen_vertex *s2)
{
    batch_select_pattern(pattern_enabled);
    batch_reserve(3);
    screen_vertex *s[3] = { s0, s1, s2 };
    for (int i = 0; i < 3; i++)
        emit_vertex(s[i]->x / (float)SCREEN_VERTEX_V2_SCALE,
                    s[i]->y / (float)SCREEN_VERTEX_V2_SCALE,
                    sv_z01(s[i]),
                    s[i]->r, s[i]->g, s[i]->b);
}

static void screen_vertex_offset_with_clamp(screen_vertex *v, float dx, float dy)
{
    v->x = clampf(v->x + dx * SCREEN_VERTEX_V2_SCALE, 0, (FB_WIDTH - 1) * SCREEN_VERTEX_V2_SCALE);
    v->y = clampf(v->y + dy * SCREEN_VERTEX_V2_SCALE, 0, (FB_HEIGHT - 1) * SCREEN_VERTEX_V2_SCALE);
}

static void emit_point(screen_vertex *sv)
{
    // the reference rasterizer writes exactly one pixel, bypassing the
    // pattern test; emit a never-stippled 1x1 quad covering that pixel
    batch_select_pattern(0);
    float px = floorf(clampf(sv->x / (float)SCREEN_VERTEX_V2_SCALE, 0, FB_WIDTH - 1));
    float py = floorf(clampf(sv->y / (float)SCREEN_VERTEX_V2_SCALE, 0, FB_HEIGHT - 1));
    float z = sv_z01(sv);

    batch_reserve(6);
    emit_vertex(px,     py,     z, sv->r, sv->g, sv->b);
    emit_vertex(px + 1, py,     z, sv->r, sv->g, sv->b);
    emit_vertex(px + 1, py + 1, z, sv->r, sv->g, sv->b);
    emit_vertex(px + 1, py + 1, z, sv->r, sv->g, sv->b);
    emit_vertex(px,     py + 1, z, sv->r, sv->g, sv->b);
    emit_vertex(px,     py,     z, sv->r, sv->g, sv->b);
}

static void emit_line(screen_vertex *v0, screen_vertex *v1)
{
    // same quad expansion as the reference rasterizer's draw_line
    float dx = (float)(v1->x - v0->x);
    float dy = (float)(v1->y - v0->y);

    if (dx == 0.0f && dy == 0.0f)
    {
        emit_point(v0);
        return;
    }

    screen_vertex q[4] = { *v0, *v0, *v1, *v1 };

    if (fabsf(dx) > fabsf(dy))
    {
        screen_vertex_offset_with_clamp(&q[0], 0, -the_linewidth * .5);
        screen_vertex_offset_with_clamp(&q[1], 0,  the_linewidth * .5);
        screen_vertex_offset_with_clamp(&q[2], 0,  the_linewidth * .5);
        screen_vertex_offset_with_clamp(&q[3], 0, -the_linewidth * .5);
    }
    else
    {
        screen_vertex_offset_with_clamp(&q[0], -the_linewidth * .5, 0);
        screen_vertex_offset_with_clamp(&q[1],  the_linewidth * .5, 0);
        screen_vertex_offset_with_clamp(&q[2],  the_linewidth * .5, 0);
        screen_vertex_offset_with_clamp(&q[3], -the_linewidth * .5, 0);
    }

    emit_screen_triangle(&q[0], &q[1], &q[2]);
    emit_screen_triangle(&q[2], &q[3], &q[0]);
}

void gles2_rasterizer_draw(uint32_t type, uint32_t count, screen_vertex *screenverts)
{
    if (!ensure_gl())
        return;

    switch (type)
    {
        case DRAW_POINTS:
            for (uint32_t i = 0; i < count; ++i)
                emit_point(&screenverts[i]);
            break;
        case DRAW_LINES:
            for (uint32_t i = 0; i < count / 2; i++)
                emit_line(&screenverts[i * 2 + 0], &screenverts[i * 2 + 1]);
            break;
        case DRAW_TRIANGLES:
            for (uint32_t i = 0; i < count / 3; i++)
                emit_screen_triangle(&screenverts[i * 3], &screenverts[i * 3 + 1], &screenverts[i * 3 + 2]);
            break;
    }
}

void gles2_rasterizer_bitmap(uint32_t width, uint32_t rowbytes, uint32_t height,
                             screen_vertex *sv, uint8_t *bits)
{
    if (!ensure_gl())
        return;

    // same run-length quad expansion as the reference rasterizer
    screen_vertex s[4];

    for (uint32_t j = 0; j < height; j++)
    {
        int prevbit = 0;
        int count = 0;
        for (uint32_t i = 0; i < width; i++)
        {
            int bit = (bits[j * rowbytes + i / 8] >> (7 - i % 8)) & 1;

            if (bit)
            {
                if (!prevbit)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        s[k] = *sv; // copy color
                        s[k].x = sv->x + SCREEN_VERTEX_V2_SCALE * i;
                        s[k].y = sv->y + (height - j - 1) * SCREEN_VERTEX_V2_SCALE;
                        s[k].z = sv->z;
                    }
                    screen_vertex_offset_with_clamp(&s[0], 0, 0);
                    screen_vertex_offset_with_clamp(&s[1], 0, 1);
                    count = 0;
                }
                count++;
            }
            else if (prevbit)
            {
                screen_vertex_offset_with_clamp(&s[2], count, 1);
                screen_vertex_offset_with_clamp(&s[3], count, 0);
                emit_screen_triangle(&s[0], &s[1], &s[2]);
                emit_screen_triangle(&s[2], &s[3], &s[0]);
            }

            prevbit = bit;
        }

        if (prevbit)
        {
            screen_vertex_offset_with_clamp(&s[2], count, 1);
            screen_vertex_offset_with_clamp(&s[3], count, 0);
            emit_screen_triangle(&s[0], &s[1], &s[2]);
            emit_screen_triangle(&s[2], &s[3], &s[0]);
        }
    }
}

void gles2_rasterizer_alpha_blit(uint32_t width, uint32_t rowbytes, uint32_t height,
                                 screen_vertex *sv, uint8_t *alpha,
                                 uint8_t r, uint8_t g, uint8_t b)
{
    if (!ensure_gl())
        return;
    flush_batch();

    // upload coverage as an alpha texture (repack if rows aren't tight)
    glBindTexture(GL_TEXTURE_2D, blit_tex);
    if (rowbytes == width)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0,
                     GL_ALPHA, GL_UNSIGNED_BYTE, alpha);
    else
    {
        uint8_t *tight = malloc((size_t)width * height);
        for (uint32_t j = 0; j < height; j++)
            memcpy(tight + j * width, alpha + j * rowbytes, width);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0,
                     GL_ALPHA, GL_UNSIGNED_BYTE, tight);
        free(tight);
    }

    // quad in pixel coords; source row 0 lands at the top (y-flipped),
    // matching the reference rasterizer's coordinate convention
    float x0 = sv->x / (float)SCREEN_VERTEX_V2_SCALE;
    float y0 = sv->y / (float)SCREEN_VERTEX_V2_SCALE;
    float x1 = x0 + width;
    float y1 = y0 + height;

    // x, y, z, u, v
    const GLfloat quad[6][5] =
    {
        { x0, y0, 0, 0, 1 },
        { x1, y0, 0, 1, 1 },
        { x1, y1, 0, 1, 0 },
        { x1, y1, 0, 1, 0 },
        { x0, y1, 0, 0, 0 },
        { x0, y0, 0, 0, 1 },
    };

    glBindBuffer(GL_ARRAY_BUFFER, blit_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STREAM_DRAW);

    glUseProgram(blit_prog);
    glUniform2f(u_blit_scale, 2.0f / FB_WIDTH, 2.0f / FB_HEIGHT);
    glUniform4f(u_blit_color, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    glUniform1i(u_blit_tex, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, blit_tex);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                          (void *)(3 * sizeof(GLfloat)));

    // the reference rasterizer's alpha blit ignores the z-buffer entirely
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, FB_WIDTH, FB_HEIGHT);

    if (backbuffer_draw_enabled)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, back_buf->fbo);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    if (frontbuffer_draw_enabled)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, front_buf->fbo);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        front_dirty = 1;
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//
// state
//

void gles2_rasterizer_setpattern(uint16_t pattern[16])
{
    // batched stippled geometry must draw with the mask active when emitted
    if (batch_count > 0 && batch_pattern_on)
        flush_batch();
    for (int i = 0; i < 16; i++)
        the_pattern[i] = pattern[i];
    pattern_dirty = 1;
}

void gles2_rasterizer_pattern(int enable)
{
    // no flush needed: emitters capture the state per batch (batch_select_pattern)
    pattern_enabled = enable;
}

void gles2_rasterizer_cbuffer_draw(int enable_front, int enable_back)
{
    if (enable_front != frontbuffer_draw_enabled || enable_back != backbuffer_draw_enabled)
        flush_batch();
    frontbuffer_draw_enabled = enable_front;
    backbuffer_draw_enabled = enable_back;
}

void gles2_rasterizer_zbuffer(int enable)
{
    if (enable != zbuffer_enabled)
        flush_batch();
    zbuffer_enabled = enable;
}

void gles2_rasterizer_linewidth(float w)
{
    // affects geometry generation at batch time only; no flush needed
    the_linewidth = w;
}

void gles2_rasterizer_rgbmode(int enable)
{
    rgb_mode = enable;
}

int32_t gles2_rasterizer_winopen(char *title)
{
    // no GL context yet — just record env options and init the CPU front
    // buffer; GL resources are created lazily on the first draw/clear
    if (getenv("GEN_FRAME_PPM_FILES") != NULL)
    {
        gen_ppm_frame_files = 1;
        printf("Generating .PPM file for each frame\n");
    }

    memset(cpu_front, 0, sizeof(cpu_front));
    for (int j = 0; j < FB_HEIGHT; j++)
        for (int i = 0; i < FB_WIDTH; i++)
            cpu_front[j][i][ALPHA_BYTE] = 255;

    return 1;
}

const rasterizer_funcs* gles2_rasterizer_get_funcs(void)
{
    static const rasterizer_funcs funcs =
    {
        .winopen            = gles2_rasterizer_winopen,
        .rgbmode            = gles2_rasterizer_rgbmode,
        .clear              = gles2_rasterizer_clear,
        .zclear             = gles2_rasterizer_zclear,
        .czclear            = gles2_rasterizer_czclear,
        .swap               = gles2_rasterizer_swap,
        .copy_front_to_back = gles2_rasterizer_copy_front_to_back,
        .copy_back_to_front = gles2_rasterizer_copy_back_to_front,
        .frontbuffer        = gles2_rasterizer_frontbuffer,
        .draw               = gles2_rasterizer_draw,
        .bitmap             = gles2_rasterizer_bitmap,
        .alpha_blit         = gles2_rasterizer_alpha_blit,
        .setpattern         = gles2_rasterizer_setpattern,
        .pattern            = gles2_rasterizer_pattern,
        .cbuffer_draw       = gles2_rasterizer_cbuffer_draw,
        .zbuffer            = gles2_rasterizer_zbuffer,
        .linewidth          = gles2_rasterizer_linewidth,
        .frame_sync         = gles2_rasterizer_frame_sync,
    };
    return &funcs;
}
