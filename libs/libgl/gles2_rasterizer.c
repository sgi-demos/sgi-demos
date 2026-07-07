//
// GLES2 (GPU) rasterizer
//
// Implements the rasterizer interface with OpenGL ES2 draw calls instead of
// the CPU reference rasterizer. The DEFAULT rasterizer (rasterizer.c
// dispatch; select the CPU reference instead via GLES2_RASTERIZER=ref
// native, ?rast=ref web).
//
// Design:
//  - Primitives are batched into a vertex array (points and lines are
//    expanded into quads exactly the way the reference rasterizer does)
//    and flushed with one glDrawArrays(GL_TRIANGLES) per color buffer.
//  - IRIS GL's double-buffered model is mirrored with two offscreen FBOs
//    (front and back), each with an RGBA color texture; one 16-bit depth
//    renderbuffer is shared by both (the reference rasterizer's z-buffer is
//    also 16-bit and shared).
//  - Zero-readback present: the front FBO's color texture is handed to the
//    display quad directly (sdlSetFramebufferSourceTex), so no glReadPixels
//    happens per frame. The CPU front buffer copy is refreshed from the
//    GPU FBO only when GEN_FRAME_PPM_FILES needs it for frame dumps.
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

#include "rasterizer.h"
#include "sdl_framebuffer.h"

// Framebuffer size tracks the window (gles2_rasterizer_resize); buffers and
// FBOs are (re)created at that size. Zero until the window exists.
static int fb_width = 0;
static int fb_height = 0;

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

// IRIS layer planes (rasterizer_layer): single-buffered RGBA side buffers
// with no depth attachment. layer_bufs[0] = underlay, [1] = overlay/pup;
// a pixel's alpha records "layer index != 0" (0 = transparent/erased).
// Once any layer is selected, presents go through display_buf, the
// per-frame composite of overlay-over-front-over-underlay (underlay shows
// where the front pixel is exactly black — the SGI display priority).
// Demos that never touch drawmode keep the zero-copy front-texture present.
static gl_buffer layer_bufs[2];
static gl_buffer display_buf;
static int layer_target = 0;        // 0 = normal planes, 1 = underlay, 2 = overlay
static int layers_in_use = 0;

// IRIS scrmask (rasterizer_scissor): clips batched draws; y up like the batch
static int scissor_enabled = 0;
static int32_t scissor_rect[4];     // x0, y0, x1, y1 inclusive

// GPU color-index buffer (CI/cmode emulation, needs an ES3 context).
//
// In cmode, draws render their INDEX — encoded in the color attachment's
// bytes (R = index & 0xff, G = index >> 8) — into dedicated CI FBOs, and the
// present resolves indexes to RGB through a palette LUT texture, exactly the
// hardware model: mapcolor() changes already-drawn pixels on the next
// present, and per-draw/clear writemask compositing is exact index math,
// immune to the palette collisions that break RGB-matching (flight 1988 maps
// white, white+brown and white+orange to the same RGB but their masked
// clears must restore three different things).
//
// Masked draws sample a snapshot of the CI target (copied before each masked
// flush — the snapshot's protected planes are always current, since masked
// draws never write them) and an ES3 shader computes
// (old & ~wm) | (drawn & wm) per pixel in integer math.
//
// Shim UI drawn RGB-only during cmode (popup menus: CI_NONE vertices) lands
// in the regular RGB buffers, whose alpha marks "UI here" — cmode clears
// wipe those to alpha 0 and the resolve overlays where alpha is set, which
// is how newave's menus stay visible over its CI scene.
static gl_buffer ci_buffers[2];     // encoded-index targets, share the depth rb
static gl_buffer *back_ci = &ci_buffers[0];
static gl_buffer *front_ci = &ci_buffers[1];
static gl_buffer resolved_buf;      // LUT-resolved RGB, the cmode present source
static GLuint ci_snap_tex = 0;      // masked-composite snapshot of the CI target
static GLuint lut_tex = 0;          // 64x64 palette LUT (4096 indexes)
static int lut_dirty = 1;
static uint8_t (*the_colormap)[3] = NULL;   // GL layer's live palette
static uint16_t the_writemask = 0xffff;
static int ci_gpu_ok = 0;           // ES3 context + CI programs built

static GLuint ci_masked_prog = 0;   // masked-composite draw program (ES3)
static GLint  u_cim_scale = -1;
static GLint  u_cim_pattern_on = -1;
static GLint  u_cim_pattern_tex = -1;
static GLint  u_cim_snap_tex = -1;
static GLint  u_cim_wm = -1;

static GLuint resolve_prog = 0;     // CI -> RGB present resolve (ES3)
static GLint  u_res_scale = -1;
static GLint  u_res_ci_tex = -1;
static GLint  u_res_lut_tex = -1;
static GLint  u_res_ui_tex = -1;

// One depth renderbuffer shared by both FBOs, matching the reference
// rasterizer's single z-buffer (front and back share z state there too).
// 24-bit depth when the context provides it (ES3, or the OES_depth24
// extension): IRIS hardware had 24-bit z, and 16 bits visibly z-fights on
// flight 3.4's near=4..far=1e6 scene (the F-14 cockpit interior poked
// through the canopy glass).
static GLuint shared_depth_rb = 0;
#ifndef GL_DEPTH_COMPONENT24
#define GL_DEPTH_COMPONENT24 0x81A6
#endif
static GLenum depth_rb_format(void)
{
    const char *ver = (const char *)glGetString(GL_VERSION);
    const char *ext = (const char *)glGetString(GL_EXTENSIONS);
    if ((ver && strstr(ver, "OpenGL ES 3")) || (ext && strstr(ext, "OES_depth24")))
        return GL_DEPTH_COMPONENT24;
    return GL_DEPTH_COMPONENT16;
}

static GLuint draw_prog = 0;        // batched geometry program
static GLint  u_draw_scale = -1;    // 2/W, 2/H pixel->NDC scale
static GLint  u_draw_pattern_on = -1;
static GLint  u_draw_pattern_tex = -1;
static GLint  u_draw_tex_on = -1;
static GLint  u_draw_demo_tex = -1;

static GLuint blit_prog = 0;        // alpha_blit program (textured, blended)
static GLint  u_blit_scale = -1;
static GLint  u_blit_color = -1;
static GLint  u_blit_tex = -1;

static GLuint comp_prog = 0;        // layer composite program (see display_buf)
static GLint  u_comp_scale = -1;
static GLint  u_comp_front = -1;
static GLint  u_comp_under = -1;
static GLint  u_comp_over = -1;

static GLuint pattern_tex = 0;      // 16x16 alpha texture of the_pattern
static GLuint blit_tex = 0;         // scratch texture for alpha_blit
static GLuint batch_vbo = 0;
static GLuint blit_vbo = 0;

static int gl_ready = 0;

//
// CPU front buffer. The display samples the front FBO texture directly
// (zero-readback present), so this copy is only refreshed from the GPU
// front FBO for the GEN_FRAME_PPM_FILES frame dumps; it is also what
// rasterizer_frontbuffer returns (the display ignores that pointer once a
// texture source is set).
//
static unsigned char *cpu_front = NULL;     // BGRA, row 0 = top, fb_width*fb_height*4
static unsigned char *readback_rgba = NULL; // RGBA, row 0 = bottom (GL order), same size

//
// vertex batch — everything becomes GL_TRIANGLES
//
typedef struct gpu_vertex
{
    float x, y, z;      // x,y in pixels, z in [0,1]
    uint8_t rgba[4];
    float u, v;
} gpu_vertex;

#define BATCH_MAX_VERTS (64 * 1024)
static gpu_vertex batch[BATCH_MAX_VERTS];
static int batch_count = 0;

// Pattern state captured for the current batch contents. The reference
// applies the screen-door pattern in triPixel, which triangles, wide lines
// and bitmap glyphs go through — but points are written directly and are
// never stippled. Emitters declare which they need; a mismatch flushes.
static int batch_pattern_on = 0;
static int batch_ci_on = 0;         // batch targets the CI buffers (encoded indexes)
static int batch_masked_on = 0;     // batch composites through the writemask (CI only)
static void restore_depth_mask(void);
static int blend_enabled = 0;   // BF_SA/BF_MSA blending (batch-affecting: mismatch flushes)
static int batch_blend_on = 0;
static int zwrite_enabled = 1;  // depth writes (zwritemask)
static int colormask_enabled = 1;  // color writes (wmpack); off = z-only draws
static int texture_enabled = 0; // demo texture bound and on (batch-affecting)
static int batch_texture_on = 0;
static GLuint demo_tex = 0;     // the one demo texture (unit 1); pattern_tex stays on unit 0
static int demo_tex_bilinear = 0;

//
// shaders
//
static const GLchar *draw_vs_src =
    "attribute vec3 pos;                                                \n" // x,y pixels, z [0,1]
    "attribute vec4 color;                                              \n"
    "attribute vec2 uv;                                                 \n" // texture coords (tex_on)
    "varying vec4 v_color;                                              \n"
    "varying vec2 v_uv;                                                 \n"
    "uniform vec2 scale;                                                \n" // 2/W, 2/H
    "void main()                                                        \n"
    "{                                                                  \n"
    "    gl_Position = vec4(pos.x * scale.x - 1.0,                      \n"
    "                       pos.y * scale.y - 1.0,                      \n"
    "                       pos.z * 2.0 - 1.0, 1.0);                    \n"
    "    v_color = color;                                               \n"
    "    v_uv = uv;                                                     \n"
    "}                                                                  \n";

static const GLchar *draw_fs_src =
    // highp: mediump varyings interpolate at fp16 on Apple GPUs, and across
    // a screen-filling flat triangle the interpolation error exceeds half a
    // byte step — flat cmode fills came out off by one (154,150,150 amid
    // 155,150,150), stranding pixels the masked-clear RGB remap can never
    // match. fp32 interpolation plus the byte-grid quantize below keeps
    // cmode fills exactly on palette bytes.
    "#ifdef GL_FRAGMENT_PRECISION_HIGH                                  \n"
    "precision highp float;                                             \n"
    "#else                                                              \n"
    "precision mediump float;                                           \n"
    "#endif                                                             \n"
    "varying vec4 v_color;                                              \n"
    "varying vec2 v_uv;                                                 \n"
    "uniform sampler2D pattern_tex;                                     \n"
    "uniform sampler2D demo_tex;                                        \n"
    "uniform bool pattern_on;                                           \n"
    "uniform bool tex_on;                                               \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    if (pattern_on)                                                \n"
    "    {                                                              \n"
    "        vec2 pc = mod(gl_FragCoord.xy, 16.0) / 16.0;               \n"
    "        if (texture2D(pattern_tex, pc).a < 0.5)                    \n"
    "            discard;                                               \n"
    "    }                                                              \n"
    // Quantize to the byte grid: perspective-correct varying interpolation
    // is not byte-exact even across a flat-colored triangle (float noise
    // lands 154.99 where the vertices said 155), and the masked-clear RGB
    // remap needs cmode fills to hold exact palette bytes. Equivalent to
    // what the RGBA8 framebuffer write quantizes anyway, minus the noise.
    "    vec4 c = floor(v_color * 255.0 + 0.5) / 255.0;                 \n"
    "    gl_FragColor = tex_on                                          \n"
    "        ? c * vec4(texture2D(demo_tex, v_uv).rgb, 1.0)             \n" // IRIS TV_MODULATE
    "        : c;                                                       \n"
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

// layer composite (shares blit_vs_src): SGI display priority — overlay
// where its index bit (alpha) is set, else the normal planes, else the
// underlay where the normal planes are exactly black (all channels 0;
// texels are 8-bit so the float compare against 0.0 is exact)
static const GLchar *comp_fs_src =
    "precision mediump float;                                           \n"
    "varying vec2 v_uv;                                                 \n"
    "uniform sampler2D front_tex;                                       \n"
    "uniform sampler2D under_tex;                                       \n"
    "uniform sampler2D over_tex;                                        \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    vec4 o = texture2D(over_tex, v_uv);                            \n"
    "    vec4 f = texture2D(front_tex, v_uv);                           \n"
    "    vec4 u = texture2D(under_tex, v_uv);                           \n"
    "    vec3 base = (f.r + f.g + f.b == 0.0 && u.a > 0.5)              \n"
    "        ? u.rgb : f.rgb;                                           \n"
    "    gl_FragColor = vec4(o.a > 0.5 ? o.rgb : base, 1.0);            \n"
    "}                                                                  \n";

//
// ES3 (GLSL 300 es) programs for the CI buffer path. Batched CI geometry
// carries its encoded index in the vertex color (exact bytes: flat per
// primitive + the byte-grid quantize), so the unmasked case reuses draw_prog
// unchanged; these two cover masked compositing and the present resolve.
// uint uniforms are passed as floats (glUniform1ui is ES3-API; values are
// <= 4095 so the float round-trip is exact).
//
static const GLchar *ci_vs300_src =
    "#version 300 es                                                    \n"
    "in vec3 pos;                                                       \n"
    "in vec4 color;                                                     \n"
    "in vec2 uv;                                                        \n"
    "out vec4 v_color;                                                  \n"
    "out vec2 v_uv;                                                     \n"
    "uniform vec2 scale;                                                \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    gl_Position = vec4(pos.x * scale.x - 1.0,                      \n"
    "                       pos.y * scale.y - 1.0,                      \n"
    "                       pos.z * 2.0 - 1.0, 1.0);                    \n"
    "    v_color = color;                                               \n"
    "    v_uv = uv;                                                     \n"
    "}                                                                  \n";

static const GLchar *ci_masked_fs300_src =
    "#version 300 es                                                    \n"
    "precision highp float;                                             \n"
    "precision highp int;                                               \n"
    "in vec4 v_color;                                                   \n"
    "in vec2 v_uv;                                                      \n"
    "uniform sampler2D pattern_tex;                                     \n"
    "uniform sampler2D snap_tex;                                        \n"
    "uniform bool pattern_on;                                           \n"
    "uniform float wm;                                                  \n" // partial writemask, <= 0xfff
    "out vec4 frag;                                                     \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    if (pattern_on)                                                \n"
    "    {                                                              \n"
    "        vec2 pc = mod(gl_FragCoord.xy, 16.0) / 16.0;               \n"
    "        if (texture(pattern_tex, pc).a < 0.5)                      \n"
    "            discard;                                               \n"
    "    }                                                              \n"
    "    vec4 s = texelFetch(snap_tex, ivec2(gl_FragCoord.xy), 0);      \n"
    "    uint o = uint(s.r * 255.0 + 0.5)                               \n"
    "           | (uint(s.g * 255.0 + 0.5) << 8);                       \n"
    "    uint c = uint(v_color.r * 255.0 + 0.5)                         \n"
    "           | (uint(v_color.g * 255.0 + 0.5) << 8);                 \n"
    "    uint m = uint(wm + 0.5);                                       \n"
    "    uint n = ((o & ~m) | (c & m)) & 4095u;                         \n"
    "    frag = vec4(float(n & 255u) / 255.0,                           \n"
    "                float(n >> 8) / 255.0, 0.0, 1.0);                  \n"
    "}                                                                  \n";

// present resolve: index -> LUT RGB, with RGB-only shim UI (alpha-marked in
// the regular front buffer) overlaid on top
static const GLchar *resolve_vs300_src =
    "#version 300 es                                                    \n"
    "in vec3 pos;                                                       \n"
    "in vec2 uv;                                                        \n"
    "out vec2 v_uv;                                                     \n"
    "uniform vec2 scale;                                                \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    gl_Position = vec4(pos.x * scale.x - 1.0,                      \n"
    "                       pos.y * scale.y - 1.0, 0.0, 1.0);           \n"
    "    v_uv = uv;                                                     \n"
    "}                                                                  \n";

static const GLchar *resolve_fs300_src =
    "#version 300 es                                                    \n"
    "precision highp float;                                             \n"
    "precision highp int;                                               \n"
    "in vec2 v_uv;                                                      \n"
    "uniform sampler2D ci_tex;                                          \n"
    "uniform sampler2D lut_tex;                                         \n" // 64x64 = 4096 palette entries
    "uniform sampler2D ui_tex;                                          \n"
    "out vec4 frag;                                                     \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    ivec2 p = ivec2(gl_FragCoord.xy);                              \n"
    "    vec4 s = texelFetch(ci_tex, p, 0);                             \n"
    "    uint idx = (uint(s.r * 255.0 + 0.5)                            \n"
    "             | (uint(s.g * 255.0 + 0.5) << 8)) & 4095u;            \n"
    "    vec3 rgb = texelFetch(lut_tex,                                 \n"
    "                  ivec2(int(idx & 63u), int(idx >> 6)), 0).rgb;    \n"
    "    vec4 ui = texelFetch(ui_tex, p, 0);                            \n"
    "    frag = vec4(ui.a > 0.0 ? ui.rgb : rgb, 1.0);                   \n"
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

static void create_buffer(gl_buffer *b, int with_depth)
{
    glGenTextures(1, &b->tex);
    glBindTexture(GL_TEXTURE_2D, b->tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fb_width, fb_height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glGenFramebuffers(1, &b->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, b->fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, b->tex, 0);
    if (with_depth)     // layer/display buffers carry no z (see rasterizer_layer)
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, shared_depth_rb);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR: gles2 rasterizer FBO incomplete: 0x%x\n", status);
}

static void destroy_buffer(gl_buffer *b)
{
    glDeleteFramebuffers(1, &b->fbo);
    glDeleteTextures(1, &b->tex);
}

// clear a layer/display buffer to transparent black
static void clear_buffer_transparent(gl_buffer *b)
{
    glBindFramebuffer(GL_FRAMEBUFFER, b->fbo);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

static void clear_gl_buffers(uint8_t r, uint8_t g, uint8_t b,
                             int clear_front, int clear_back, GLbitfield mask);
static void flush_batch(void);
static void emit_screen_triangle(screen_vertex *s0, screen_vertex *s1, screen_vertex *s2);

// Create all GL resources on the first call after the SDL window/GL context
// exists. Returns 0 (and does nothing) if the context isn't up yet.
static int ensure_gl(void)
{
    if (gl_ready)
        return 1;
    if (!sdlGLContextReady() || fb_width == 0)
        return 0;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 4);

    draw_prog = build_program(draw_vs_src, draw_fs_src, "pos", "color", "draw");
    glBindAttribLocation(draw_prog, 2, "uv");
    glLinkProgram(draw_prog);   // relink with the uv attribute bound
    u_draw_scale = glGetUniformLocation(draw_prog, "scale");
    u_draw_pattern_on = glGetUniformLocation(draw_prog, "pattern_on");
    u_draw_tex_on = glGetUniformLocation(draw_prog, "tex_on");
    u_draw_demo_tex = glGetUniformLocation(draw_prog, "demo_tex");
    u_draw_pattern_tex = glGetUniformLocation(draw_prog, "pattern_tex");

    blit_prog = build_program(blit_vs_src, blit_fs_src, "pos", "uv", "blit");
    u_blit_scale = glGetUniformLocation(blit_prog, "scale");
    u_blit_color = glGetUniformLocation(blit_prog, "color");
    u_blit_tex = glGetUniformLocation(blit_prog, "blit_tex");

    comp_prog = build_program(blit_vs_src, comp_fs_src, "pos", "uv", "composite");
    u_comp_scale = glGetUniformLocation(comp_prog, "scale");
    u_comp_front = glGetUniformLocation(comp_prog, "front_tex");
    u_comp_under = glGetUniformLocation(comp_prog, "under_tex");
    u_comp_over = glGetUniformLocation(comp_prog, "over_tex");

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

    // The draw shader statically references demo_tex on unit 1. Leaving the
    // unit unbound until the first teximage() is technically undefined and
    // trips driver validation (Apple's GL-on-Metal logs "texture unloadable,
    // using zero texture" for demos that never texture). Start it as 1x1
    // white — the identity for the TV_MODULATE multiply — and keep it bound;
    // teximage() replaces the contents.
    {
        static const uint8_t white[3] = {255, 255, 255};
        glGenTextures(1, &demo_tex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, demo_tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, white);
        glActiveTexture(GL_TEXTURE0);
    }

    glGenBuffers(1, &batch_vbo);
    glGenBuffers(1, &blit_vbo);

    glGenRenderbuffers(1, &shared_depth_rb);
    glBindRenderbuffer(GL_RENDERBUFFER, shared_depth_rb);
    glRenderbufferStorage(GL_RENDERBUFFER, depth_rb_format(), fb_width, fb_height);

    create_buffer(&buffers[0], 1);
    create_buffer(&buffers[1], 1);
    create_buffer(&layer_bufs[0], 0);
    create_buffer(&layer_bufs[1], 0);
    create_buffer(&display_buf, 0);
    clear_buffer_transparent(&layer_bufs[0]);
    clear_buffer_transparent(&layer_bufs[1]);
    clear_buffer_transparent(&display_buf);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // CI buffer path: needs an ES3 context for the GLSL 300 es programs
    // (integer texel math); everything else stays ES2-level API. On an ES2
    // context cmode falls back to draw-time RGB resolution as before.
    {
        const char *ver = (const char *)glGetString(GL_VERSION);
        if (ver && strstr(ver, "OpenGL ES 3"))
        {
            ci_masked_prog = build_program(ci_vs300_src, ci_masked_fs300_src,
                                           "pos", "color", "ci-masked");
            glBindAttribLocation(ci_masked_prog, 2, "uv");
            glLinkProgram(ci_masked_prog);
            u_cim_scale = glGetUniformLocation(ci_masked_prog, "scale");
            u_cim_pattern_on = glGetUniformLocation(ci_masked_prog, "pattern_on");
            u_cim_pattern_tex = glGetUniformLocation(ci_masked_prog, "pattern_tex");
            u_cim_snap_tex = glGetUniformLocation(ci_masked_prog, "snap_tex");
            u_cim_wm = glGetUniformLocation(ci_masked_prog, "wm");

            resolve_prog = build_program(resolve_vs300_src, resolve_fs300_src,
                                         "pos", "uv", "ci-resolve");
            u_res_scale = glGetUniformLocation(resolve_prog, "scale");
            u_res_ci_tex = glGetUniformLocation(resolve_prog, "ci_tex");
            u_res_lut_tex = glGetUniformLocation(resolve_prog, "lut_tex");
            u_res_ui_tex = glGetUniformLocation(resolve_prog, "ui_tex");

            GLint ok1 = 0, ok2 = 0;
            glGetProgramiv(ci_masked_prog, GL_LINK_STATUS, &ok1);
            glGetProgramiv(resolve_prog, GL_LINK_STATUS, &ok2);
            ci_gpu_ok = ok1 && ok2;
        }
        if (ci_gpu_ok)
        {
            create_buffer(&ci_buffers[0], 1);
            create_buffer(&ci_buffers[1], 1);
            create_buffer(&resolved_buf, 0);
            clear_buffer_transparent(&ci_buffers[0]);
            clear_buffer_transparent(&ci_buffers[1]);
            clear_buffer_transparent(&resolved_buf);

            glGenTextures(1, &ci_snap_tex);
            glBindTexture(GL_TEXTURE_2D, ci_snap_tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fb_width, fb_height, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, NULL);

            glGenTextures(1, &lut_tex);
            glBindTexture(GL_TEXTURE_2D, lut_tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            lut_dirty = 1;
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            printf("INFO: gles2 rasterizer CI buffer enabled (ES3)\n");
        }
        else
            printf("INFO: gles2 rasterizer CI buffer unavailable (%s) — cmode approximated\n",
                   ver ? ver : "no version");
    }

    gl_ready = 1;

    // apply clears recorded before the context existed (winopen clears to
    // black / max z); clear both buffers regardless of draw enables
    glClearDepthf((GLfloat)(pend_clear_z / 4294967295.0));
    clear_gl_buffers(pend_clear_rgb[0], pend_clear_rgb[1], pend_clear_rgb[2],
                     1, 1, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // present directly from the front FBO texture from the outset, so even
    // frames before the first swap (front-buffer drawing) display correctly
    sdlSetFramebufferSourceTex(front_buf->tex);

    printf("INFO: gles2 rasterizer initialized (%dx%d front/back FBOs)\n", fb_width, fb_height);
    return 1;
}

//
// layer composite + present source (see layer_bufs/display_buf above)
//

// draw a fullscreen quad (pixel coords) with the currently-bound program;
// the caller sets up program, uniforms and textures
static void fullscreen_quad(GLuint target_fbo)
{
    struct { float x, y, z, u, v; } quad[6] = {
        { 0,               0,                0, 0, 0 },
        { (float)fb_width, 0,                0, 1, 0 },
        { (float)fb_width, (float)fb_height, 0, 1, 1 },
        { 0,               0,                0, 0, 0 },
        { (float)fb_width, (float)fb_height, 0, 1, 1 },
        { 0,               (float)fb_height, 0, 0, 1 },
    };

    glBindFramebuffer(GL_FRAMEBUFFER, target_fbo);
    glViewport(0, 0, fb_width, fb_height);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glBindBuffer(GL_ARRAY_BUFFER, blit_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STREAM_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(quad[0]), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(quad[0]), (void *)(3 * sizeof(float)));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glEnable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

static void composite_layers(GLuint front_tex)
{
    glUseProgram(comp_prog);
    glUniform2f(u_comp_scale, 2.0f / fb_width, 2.0f / fb_height);
    glUniform1i(u_comp_front, 0);
    glUniform1i(u_comp_under, 2);
    glUniform1i(u_comp_over, 3);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, front_tex);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, layer_bufs[0].tex);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, layer_bufs[1].tex);
    glActiveTexture(GL_TEXTURE0);

    fullscreen_quad(display_buf.fbo);
}

// bake the live palette into the LUT texture (64x64 = 4096 entries)
static void upload_lut_if_dirty(void)
{
    if (!lut_dirty || lut_tex == 0)
        return;
    static uint8_t texels[64 * 64 * 4];
    for (int i = 0; i < 4096; i++)
    {
        texels[i * 4 + 0] = the_colormap ? the_colormap[i][0] : 0;
        texels[i * 4 + 1] = the_colormap ? the_colormap[i][1] : 0;
        texels[i * 4 + 2] = the_colormap ? the_colormap[i][2] : 0;
        texels[i * 4 + 3] = 255;
    }
    glBindTexture(GL_TEXTURE_2D, lut_tex);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 64, 64, GL_RGBA, GL_UNSIGNED_BYTE, texels);
    lut_dirty = 0;
}

// resolve the front CI buffer through the palette LUT into resolved_buf,
// overlaying alpha-marked RGB-only shim UI (popup menus) from the regular
// front buffer — the SGI hardware LUT at present time
static void resolve_ci(void)
{
    upload_lut_if_dirty();

    glUseProgram(resolve_prog);
    glUniform2f(u_res_scale, 2.0f / fb_width, 2.0f / fb_height);
    glUniform1i(u_res_ci_tex, 0);
    glUniform1i(u_res_lut_tex, 5);
    glUniform1i(u_res_ui_tex, 6);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, front_ci->tex);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, lut_tex);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, front_buf->tex);
    glActiveTexture(GL_TEXTURE0);

    fullscreen_quad(resolved_buf.fbo);
}

// point the display at the right texture: the raw front FBO (zero-copy)
// until a layer or the CI buffer is used, a composited/resolved buffer after
static void present_source(void)
{
    if (!gl_ready)
        return;

    int cmode_ci = (!rgb_mode && ci_gpu_ok);
    GLuint front_tex = front_buf->tex;
    if (cmode_ci)
    {
        resolve_ci();
        front_tex = resolved_buf.tex;
    }

    if (layers_in_use)
    {
        composite_layers(front_tex);
        sdlSetFramebufferSourceTex(display_buf.tex);
    }
    else
        sdlSetFramebufferSourceTex(front_tex);
}

void gles2_rasterizer_layer(int layer)
{
    if (layer == layer_target)
        return;
    flush_batch();
    layer_target = layer;
    if (layer > 0)
        layers_in_use = 1;
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

    // masked CI batches composite through ci_masked_prog; everything else —
    // including unmasked CI batches, whose vertices carry exact encoded
    // index bytes — uses the regular draw program
    int use_masked = batch_ci_on && batch_masked_on;
    if (use_masked)
    {
        glUseProgram(ci_masked_prog);
        glUniform2f(u_cim_scale, 2.0f / fb_width, 2.0f / fb_height);
        glUniform1i(u_cim_pattern_on, batch_pattern_on ? 1 : 0);
        glUniform1i(u_cim_pattern_tex, 0);
        glUniform1i(u_cim_snap_tex, 4);
        glUniform1f(u_cim_wm, (float)(the_writemask & 0xfff));
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, ci_snap_tex);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, pattern_tex);
    }
    else
    {
        glUseProgram(draw_prog);
        glUniform2f(u_draw_scale, 2.0f / fb_width, 2.0f / fb_height);
        glUniform1i(u_draw_pattern_on, batch_pattern_on ? 1 : 0);   // bool uniform
        glUniform1i(u_draw_pattern_tex, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, pattern_tex);
    }

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(gpu_vertex), (void *)0);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(gpu_vertex),
                          (void *)offsetof(gpu_vertex, rgba));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(gpu_vertex),
                          (void *)offsetof(gpu_vertex, u));

    if (!use_masked) {
        glUniform1i(u_draw_tex_on, batch_texture_on ? 1 : 0);
        glUniform1i(u_draw_demo_tex, 1);
        if (batch_texture_on) {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, demo_tex);
            glActiveTexture(GL_TEXTURE0);
        }
    }

    // IRIS zbuffer(FALSE) means z is neither tested nor updated — flight
    // 3.4's horizon depends on it: the gauge's z-off black backing square
    // must not overwrite the far z that the lsetdepth-jammed horizon ball
    // is later LEQUAL-tested against. zwritemask can additionally turn
    // writes off while the test stays on.
    // GL_LEQUAL is the IRIS GL default z-function: later geometry at equal
    // depth overwrites (newave's edit crosshair repaints mesh lines in
    // green at the same z). It also lets the front-buffer pass below land
    // the same pixels the back-buffer pass just wrote z for.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(zbuffer_enabled ? GL_LEQUAL : GL_ALWAYS);
    glDepthMask((zbuffer_enabled && zwrite_enabled) ? GL_TRUE : GL_FALSE);
    if (batch_blend_on) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else
        glDisable(GL_BLEND);
    glViewport(0, 0, fb_width, fb_height);
    if (scissor_enabled) {
        glEnable(GL_SCISSOR_TEST);
        glScissor(scissor_rect[0], scissor_rect[1],
                  scissor_rect[2] - scissor_rect[0] + 1,
                  scissor_rect[3] - scissor_rect[1] + 1);
    }
    if (!colormask_enabled)     // wmpack(0): z-only draws
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    if (layer_target > 0)
    {
        // layer planes: single-buffered, no depth attachment (the depth
        // test/writes set above are inert without one). Blending is forced
        // off so a drawn pixel's alpha (its "index != 0" bit) replaces —
        // drawing index 0 erases the layer to transparent.
        glDisable(GL_BLEND);
        glBindFramebuffer(GL_FRAMEBUFFER, layer_bufs[layer_target - 1].fbo);
        glDrawArrays(GL_TRIANGLES, 0, batch_count);
    }
    else if (batch_ci_on)
    {
        // CI batches render encoded indexes into the CI targets. A masked
        // batch first snapshots its target: masked draws never write the
        // protected planes, so the target's protected bits are always
        // current — compositing against the snapshot is exact.
        for (int t = 0; t < 2; t++)
        {
            gl_buffer *target = (t == 0) ? back_ci : front_ci;
            int enabled       = (t == 0) ? backbuffer_draw_enabled : frontbuffer_draw_enabled;
            if (!enabled)
                continue;
            if (use_masked)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, target->fbo);
                glActiveTexture(GL_TEXTURE4);
                glBindTexture(GL_TEXTURE_2D, ci_snap_tex);
                glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, fb_width, fb_height);
                glActiveTexture(GL_TEXTURE0);
            }
            else
                glBindFramebuffer(GL_FRAMEBUFFER, target->fbo);
            glDrawArrays(GL_TRIANGLES, 0, batch_count);
        }
    }
    else
    {
        if (backbuffer_draw_enabled)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, back_buf->fbo);
            glDrawArrays(GL_TRIANGLES, 0, batch_count);
        }
        if (frontbuffer_draw_enabled)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, front_buf->fbo);
            glDrawArrays(GL_TRIANGLES, 0, batch_count);
        }
    }

    if (scissor_enabled)
        glDisable(GL_SCISSOR_TEST);
    if (!colormask_enabled)
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    batch_count = 0;
}

void gles2_rasterizer_scissor(int enable, int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    if (enable == scissor_enabled &&
        (!enable || (x0 == scissor_rect[0] && y0 == scissor_rect[1] &&
                     x1 == scissor_rect[2] && y1 == scissor_rect[3])))
        return;
    flush_batch();     // the rect applies at draw time; pending batch keeps the old one
    scissor_enabled = enable;
    scissor_rect[0] = x0;
    scissor_rect[1] = y0;
    scissor_rect[2] = x1;
    scissor_rect[3] = y1;
}

//
// front buffer readback: front FBO -> cpu_front (BGRA, row 0 = top)
//
static void sync_front_to_cpu(void)
{
    if (!gl_ready)
        return;

    // frame dumps should show what the display shows: the layer composite /
    // CI resolve when those are in use, the raw front FBO otherwise
    int cmode_ci = (!rgb_mode && ci_gpu_ok);
    if (layers_in_use || cmode_ci)
        present_source();
    glBindFramebuffer(GL_FRAMEBUFFER, layers_in_use ? display_buf.fbo
                                    : cmode_ci      ? resolved_buf.fbo
                                                    : front_buf->fbo);
    glReadPixels(0, 0, fb_width, fb_height, GL_RGBA, GL_UNSIGNED_BYTE, readback_rgba);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // swizzle RGBA -> BGRA and flip vertically (GL row 0 is the bottom row)
    for (int j = 0; j < fb_height; j++)
    {
        unsigned char *src = readback_rgba + (size_t)(fb_height - 1 - j) * fb_width * 4;
        unsigned char *dst = cpu_front + (size_t)j * fb_width * 4;
        for (int i = 0; i < fb_width; i++)
        {
            dst[i * 4 + BLUE_BYTE] = src[i * 4 + 2];
            dst[i * 4 + GREEN_BYTE] = src[i * 4 + 1];
            dst[i * 4 + RED_BYTE] = src[i * 4 + 0];
            dst[i * 4 + ALPHA_BYTE] = 255;
        }
    }
}

//
// clears
//
static void clear_gl_buffers(uint8_t r, uint8_t g, uint8_t b,
                             int clear_front, int clear_back, GLbitfield mask)
{
    // alpha 0: nothing downstream reads destination alpha except the CI
    // resolve's shim-UI overlay, which must see these pixels as "no UI" —
    // a cmode demo whose only clears are masked (arena's HUD scheme) never
    // wipes the RGB pair again after init
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 0.0f);
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
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    restore_depth_mask();   // clears force depth writes on; restore zwritemask
}

// clear a front/back pair honoring the draw enables
static void clear_pair(gl_buffer *bck, gl_buffer *frt, int clear_front, int clear_back,
                       float cr, float cg, float cb, float ca, GLbitfield mask)
{
    glClearColor(cr, cg, cb, ca);
    glDepthMask(GL_TRUE);
    if (clear_back)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, bck->fbo);
        glClear(mask);
    }
    if (clear_front)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frt->fbo);
        glClear(mask);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    restore_depth_mask();
}

void gles2_rasterizer_clear(uint8_t r, uint8_t g, uint8_t b, short color_index)
{
    if (!ensure_gl())
    {
        pend_clear_rgb[0] = r; pend_clear_rgb[1] = g; pend_clear_rgb[2] = b;
        return;
    }
    flush_batch();
    if (!rgb_mode && ci_gpu_ok)
    {
        // CI planes take the encoded index; the RGB pair is wiped to
        // transparent black so stale alpha-marked shim UI (popup menus)
        // stops overlaying the resolve
        uint16_t ci = (uint16_t)color_index & 0xfff;
        clear_pair(back_ci, front_ci, frontbuffer_draw_enabled, backbuffer_draw_enabled,
                   (ci & 0xff) / 255.0f, (ci >> 8) / 255.0f, 0.0f, 1.0f,
                   GL_COLOR_BUFFER_BIT);
        clear_pair(back_buf, front_buf, frontbuffer_draw_enabled, backbuffer_draw_enabled,
                   0.0f, 0.0f, 0.0f, 0.0f, GL_COLOR_BUFFER_BIT);
        return;
    }
    clear_gl_buffers(r, g, b, frontbuffer_draw_enabled, backbuffer_draw_enabled,
                     GL_COLOR_BUFFER_BIT);
}

static void restore_depth_mask(void)
{
    glDepthMask((zbuffer_enabled && zwrite_enabled) ? GL_TRUE : GL_FALSE);
}

void gles2_rasterizer_masked_clear(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                                   uint16_t wm, uint16_t clear_index, uint8_t colormap[][3],
                                   uint32_t n, const uint32_t *rgb_from, const uint32_t *rgb_to)
{
    if (!ensure_gl())
        return;

    if (!rgb_mode && ci_gpu_ok)
    {
        // Exact index math through the CI buffer: emit the clear rect as a
        // masked-composite draw with the clear index — the same machinery
        // as masked draws, which also honors the current pattern (flight
        // 1988's crashed-meters effect is a patterned clear through
        // writemask(white)). The clear ignores the z-buffer, like the
        // reference rasterizer's.
        (void)colormap; (void)n; (void)rgb_from; (void)rgb_to;
        flush_batch();
        uint16_t save_wm = the_writemask;
        int save_zb = zbuffer_enabled;
        the_writemask = wm;
        zbuffer_enabled = 0;

        screen_vertex q[4];
        memset(q, 0, sizeof(q));
        int32_t xs[4] = { x0, x1 + 1, x1 + 1, x0 };
        int32_t ys[4] = { y0, y0, y1 + 1, y1 + 1 };
        for (int i = 0; i < 4; i++)
        {
            q[i].x = xs[i] * SCREEN_VERTEX_V2_SCALE;
            q[i].y = ys[i] * SCREEN_VERTEX_V2_SCALE;
            q[i].z = 0;
            q[i].ci = clear_index;
        }
        emit_screen_triangle(&q[0], &q[1], &q[2]);
        emit_screen_triangle(&q[2], &q[3], &q[0]);
        flush_batch();

        the_writemask = save_wm;
        zbuffer_enabled = save_zb;
        return;
    }

    // No usable CI buffer (ES2 context): the index math is approximated by
    // the precomputed RGB remap pairs. Exact for flat cmode fills, but
    // blind to palette collisions.
    (void)wm; (void)clear_index; (void)colormap;
    if (n == 0)
        return;
    flush_batch();

    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 >= (int32_t)fb_width)  x1 = fb_width - 1;
    if (y1 >= (int32_t)fb_height) y1 = fb_height - 1;
    if (x0 > x1 || y0 > y1)
        return;
    int w = x1 - x0 + 1, h = y1 - y0 + 1;

    unsigned char *px = (unsigned char *)malloc((size_t)w * h * 4);
    if (!px)
        return;

    for (int t = 0; t < 2; t++)
    {
        gl_buffer *buf = (t == 0) ? back_buf : front_buf;
        int enabled    = (t == 0) ? backbuffer_draw_enabled : frontbuffer_draw_enabled;
        if (!enabled)
            continue;

        glBindFramebuffer(GL_FRAMEBUFFER, buf->fbo);
        glReadPixels(x0, y0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, px);
        // unbind before TexSubImage: writing a texture that is attached to
        // the bound framebuffer is a feedback hazard (undefined on ANGLE)
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        for (size_t i = 0; i < (size_t)w * h; i++)
        {
            // same patterned-clear rule as the draw shader (see pattern_tex)
            if (pattern_enabled)
            {
                int sx = x0 + (int)(i % w), sy = y0 + (int)(i / w);
                if (!(the_pattern[sy % 16] & (1 << (sx % 16))))
                    continue;
            }
            unsigned char *p = px + i * 4;
            uint32_t rgb = ((uint32_t)p[0] << 16) | ((uint32_t)p[1] << 8) | p[2];
            for (uint32_t j = 0; j < n; j++)
                if (rgb == rgb_from[j])
                {
                    p[0] = (rgb_to[j] >> 16) & 0xff;
                    p[1] = (rgb_to[j] >> 8) & 0xff;
                    p[2] = rgb_to[j] & 0xff;
                    break;
                }
        }

        glBindTexture(GL_TEXTURE_2D, buf->tex);
        glTexSubImage2D(GL_TEXTURE_2D, 0, x0, y0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, px);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    free(px);
}

void gles2_rasterizer_teximage(int width, int height, const uint8_t *rgb, int bilinear)
{
    if (!ensure_gl())
        return;
    flush_batch();
    if (demo_tex == 0)
        glGenTextures(1, &demo_tex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, demo_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, bilinear ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, bilinear ? GL_LINEAR : GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb);
    glActiveTexture(GL_TEXTURE0);
    demo_tex_bilinear = bilinear;
}

void gles2_rasterizer_texture(int enable)
{
    // batch-affecting; mismatch flush happens in batch_select_texture
    texture_enabled = enable;
}

void gles2_rasterizer_blend(int enable)
{
    // batch-affecting state; the mismatch flush happens via batch_select_blend
    blend_enabled = enable;
}

void gles2_rasterizer_zwrite(int enable)
{
    zwrite_enabled = enable;
    if (gl_ready) {
        flush_batch();
        glDepthMask((zbuffer_enabled && zwrite_enabled) ? GL_TRUE : GL_FALSE);
    }
}

void gles2_rasterizer_colormask(int enable)
{
    if (enable == colormask_enabled)
        return;
    if (gl_ready)
        flush_batch();      // the mask applies at draw time
    colormask_enabled = enable;
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

void gles2_rasterizer_zclear_rect(uint32_t z, int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    if (!ensure_gl())
    {
        pend_clear_z = z;
        return;
    }
    flush_batch();
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 >= fb_width)  x1 = fb_width - 1;
    if (y1 >= fb_height) y1 = fb_height - 1;
    if (x0 > x1 || y0 > y1)
        return;
    glClearDepthf((GLfloat)(z / 4294967295.0));
    glEnable(GL_SCISSOR_TEST);
    glScissor(x0, y0, x1 - x0 + 1, y1 - y0 + 1);   // FBO rows are y-up, same as the rect
    // the depth renderbuffer is shared by both FBOs; clear it through either
    clear_gl_buffers(0, 0, 0, 0, 1, GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
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
    // the frame dumped at swap N is the outgoing front buffer — the frame
    // presented at swap N-1 plus any front-buffer drawing done since
    static int frame = 0;
    if (gen_ppm_frame_files && gl_ready && cpu_front)
    {
        sync_front_to_cpu();
        char name[128];
        sprintf(name, "frame%04d.ppm", frame);
        FILE *fp = fopen(name, "wb");
        if (fp)
        {
            fprintf(fp, "P6 %d %d 255\n", fb_width, fb_height);
            for (int j = 0; j < fb_height; j++)
            {
                for (int i = 0; i < fb_width; i++)
                {
                    unsigned char rgb_pixel[3];
                    unsigned char *px = cpu_front + ((size_t)j * fb_width + i) * 4;
                    rgb_pixel[0] = px[RED_BYTE];
                    rgb_pixel[1] = px[GREEN_BYTE];
                    rgb_pixel[2] = px[BLUE_BYTE];
                    fwrite(rgb_pixel, 1, 3, fp);
                }
            }
            fclose(fp);
        }
    }
    frame++;

    // exchange front and back (CI pair too), and hand the new front texture
    // (or the resolve/composite of it) to the display quad
    gl_buffer *tmp = back_buf;
    back_buf = front_buf;
    front_buf = tmp;
    tmp = back_ci;
    back_ci = front_ci;
    front_ci = tmp;

    present_source();
}

void gles2_rasterizer_copy_front_to_back(void)
{
    if (!ensure_gl())
        return;
    flush_batch();

    glBindFramebuffer(GL_FRAMEBUFFER, front_buf->fbo);
    glBindTexture(GL_TEXTURE_2D, back_buf->tex);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, fb_width, fb_height);
    if (ci_gpu_ok)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, front_ci->fbo);
        glBindTexture(GL_TEXTURE_2D, back_ci->tex);
        glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, fb_width, fb_height);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void gles2_rasterizer_copy_back_to_front(void)
{
    if (!ensure_gl())
        return;
    flush_batch();

    glBindFramebuffer(GL_FRAMEBUFFER, back_buf->fbo);
    glBindTexture(GL_TEXTURE_2D, front_buf->tex);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, fb_width, fb_height);
    if (ci_gpu_ok)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, back_ci->fbo);
        glBindTexture(GL_TEXTURE_2D, front_ci->tex);
        glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, fb_width, fb_height);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned char* gles2_rasterizer_frontbuffer(void)
{
    return cpu_front; // NULL until the first resize allocates it
}

// CPU-side index readback: decode the front CI FBO into a uint16 buffer
// (row 0 = top, same layout as the reference rasterizer's). A full-frame
// glReadPixels per call — fine for its consumers (cedit's pick-a-color
// clicks via readpixels/getapixel), not for per-pixel polling.
static unsigned short *cpu_ci = NULL;

unsigned short* gles2_rasterizer_ci_frontbuffer(void)
{
    if (!gl_ready || !ci_gpu_ok || rgb_mode || !readback_rgba)
        return NULL;
    flush_batch();  // pending geometry must reach the FBO before reading

    if (cpu_ci == NULL)
        cpu_ci = malloc((size_t)fb_width * fb_height * sizeof(unsigned short));

    glBindFramebuffer(GL_FRAMEBUFFER, front_ci->fbo);
    glReadPixels(0, 0, fb_width, fb_height, GL_RGBA, GL_UNSIGNED_BYTE, readback_rgba);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // decode R=low byte, G=high nibble; flip rows (GL row 0 is the bottom)
    for (int j = 0; j < fb_height; j++)
    {
        unsigned char *src = readback_rgba + (size_t)(fb_height - 1 - j) * fb_width * 4;
        unsigned short *dst = cpu_ci + (size_t)j * fb_width;
        for (int i = 0; i < fb_width; i++)
            dst[i] = (unsigned short)(src[i * 4] | (src[i * 4 + 1] << 8)) & 0xfff;
    }
    return cpu_ci;
}

// The GL layer signals "the palette changed since the last present" —
// re-bake the LUT; the next present's resolve recolors every drawn pixel,
// which is the hardware palette-LUT behavior.
void gles2_rasterizer_resolve_ci_to_rgb(uint8_t colormap[][3])
{
    if (colormap)
        the_colormap = colormap;
    lut_dirty = 1;
}

// The framebuffer tracks the window size: reallocate the CPU buffers and,
// when GL is up, recreate the FBO textures and shared depth renderbuffer at
// the new size — atomically re-registering the new front texture with the
// display before returning (a size mismatch would crop, never scale).
void gles2_rasterizer_resize(uint32_t width, uint32_t height)
{
    if ((int)width == fb_width && (int)height == fb_height)
        return;

    fb_width = (int)width;
    fb_height = (int)height;

    free(cpu_front);
    free(readback_rgba);
    cpu_front = calloc(1, (size_t)fb_width * fb_height * 4);
    readback_rgba = malloc((size_t)fb_width * fb_height * 4);
    free(cpu_ci);       // ci_frontbuffer's decode target; reallocated lazily
    cpu_ci = NULL;

    if (!gl_ready)
    {
        // context may already exist (window created before first draw):
        // create everything now at the new size; otherwise the first
        // draw/clear's ensure_gl() picks the size up from fb_width/fb_height
        ensure_gl();
        return;
    }

    // GL resources exist at the old size: rebuild color textures, FBOs and
    // the shared depth renderbuffer
    batch_count = 0; // any batched geometry is in old-framebuffer coords
    for (int i = 0; i < 2; i++)
        destroy_buffer(&buffers[i]);
    destroy_buffer(&layer_bufs[0]);
    destroy_buffer(&layer_bufs[1]);
    destroy_buffer(&display_buf);
    if (ci_gpu_ok)
    {
        destroy_buffer(&ci_buffers[0]);
        destroy_buffer(&ci_buffers[1]);
        destroy_buffer(&resolved_buf);
        glDeleteTextures(1, &ci_snap_tex);
    }
    glDeleteRenderbuffers(1, &shared_depth_rb);

    glGenRenderbuffers(1, &shared_depth_rb);
    glBindRenderbuffer(GL_RENDERBUFFER, shared_depth_rb);
    glRenderbufferStorage(GL_RENDERBUFFER, depth_rb_format(), fb_width, fb_height);

    create_buffer(&buffers[0], 1);
    create_buffer(&buffers[1], 1);
    create_buffer(&layer_bufs[0], 0);
    create_buffer(&layer_bufs[1], 0);
    create_buffer(&display_buf, 0);
    clear_buffer_transparent(&layer_bufs[0]);
    clear_buffer_transparent(&layer_bufs[1]);
    clear_buffer_transparent(&display_buf);
    if (ci_gpu_ok)
    {
        create_buffer(&ci_buffers[0], 1);
        create_buffer(&ci_buffers[1], 1);
        create_buffer(&resolved_buf, 0);
        clear_buffer_transparent(&ci_buffers[0]);
        clear_buffer_transparent(&ci_buffers[1]);
        clear_buffer_transparent(&resolved_buf);

        glGenTextures(1, &ci_snap_tex);
        glBindTexture(GL_TEXTURE_2D, ci_snap_tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fb_width, fb_height, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearDepthf(1.0f);
    clear_gl_buffers(0, 0, 0, 1, 1, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    present_source();

    printf("INFO: gles2 rasterizer framebuffer %dx%d\n", fb_width, fb_height);
}

// Called once per presented frame (events_frame_complete), before the
// display quad samples the front FBO texture: flush pending batched
// geometry so everything drawn this frame (menus, single-buffered demos)
// is in the FBO. No readback — the display reads the texture directly.
void gles2_rasterizer_frame_sync(void)
{
    if (!gl_ready)
        return;
    if (batch_count > 0)
        flush_batch();
    // refresh the layer composite / CI resolve so front-buffer drawing done
    // since the last swap (flight's gauges) and palette changes reach the
    // display
    if (layers_in_use || (!rgb_mode && ci_gpu_ok))
        present_source();
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

static void batch_select_blend(int want_blend)
{
    if (batch_count > 0 && want_blend != batch_blend_on)
        flush_batch();
    batch_blend_on = want_blend;
}

static void batch_select_texture(int want_texture)
{
    if (batch_count > 0 && want_texture != batch_texture_on)
        flush_batch();
    batch_texture_on = want_texture;
}

static void batch_select_ci(int want_ci, int want_masked)
{
    if (batch_count > 0 && (want_ci != batch_ci_on || want_masked != batch_masked_on))
        flush_batch();
    batch_ci_on = want_ci;
    batch_masked_on = want_masked;
}

// Should this primitive render into the CI buffers? Flat per primitive: the
// reference rasterizer keys each triangle's index off its first vertex too.
static int primitive_wants_ci(screen_vertex *s0)
{
    return !rgb_mode && ci_gpu_ok && layer_target == 0 &&
           s0->ci != SCREEN_VERTEX_CI_NONE;
}

static int writemask_is_partial(void)
{
    return (~the_writemask & 0xfff) != 0;
}

static void emit_vertex(float x, float y, float z01, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    gpu_vertex *v = &batch[batch_count++];
    v->x = x;
    v->y = y;
    v->z = z01;
    v->rgba[0] = r;
    v->rgba[1] = g;
    v->rgba[2] = b;
    v->rgba[3] = a;
    v->u = 0.0f;
    v->v = 0.0f;
}

static float sv_z01(screen_vertex *s)
{
    return (float)((double)s->z / 4294967295.0);
}

static void emit_screen_triangle(screen_vertex *s0, screen_vertex *s1, screen_vertex *s2)
{
    int want_ci = primitive_wants_ci(s0);
    batch_select_pattern(pattern_enabled);
    batch_select_blend(want_ci ? 0 : blend_enabled);        // CI mode never blends
    batch_select_texture(want_ci ? 0 : texture_enabled);    // or textures
    batch_select_ci(want_ci, want_ci && writemask_is_partial());
    batch_reserve(3);
    screen_vertex *s[3] = { s0, s1, s2 };
    uint16_t ci = s0->ci & 0xfff;
    for (int i = 0; i < 3; i++) {
        if (want_ci)
            // encoded index (R = low byte, G = high nibble), exact bytes
            emit_vertex(s[i]->x / (float)SCREEN_VERTEX_V2_SCALE,
                        s[i]->y / (float)SCREEN_VERTEX_V2_SCALE,
                        sv_z01(s[i]),
                        ci & 0xff, ci >> 8, 0, 255);
        else
            emit_vertex(s[i]->x / (float)SCREEN_VERTEX_V2_SCALE,
                        s[i]->y / (float)SCREEN_VERTEX_V2_SCALE,
                        sv_z01(s[i]),
                        s[i]->r, s[i]->g, s[i]->b, s[i]->a);
        batch[batch_count - 1].u = s[i]->s;
        batch[batch_count - 1].v = s[i]->t;
    }
}

static void screen_vertex_offset_with_clamp(screen_vertex *v, float dx, float dy)
{
    v->x = clampf(v->x + dx * SCREEN_VERTEX_V2_SCALE, 0, (fb_width - 1) * SCREEN_VERTEX_V2_SCALE);
    v->y = clampf(v->y + dy * SCREEN_VERTEX_V2_SCALE, 0, (fb_height - 1) * SCREEN_VERTEX_V2_SCALE);
}

static void emit_point(screen_vertex *sv)
{
    // the reference rasterizer writes exactly one pixel, bypassing the
    // pattern test; emit a never-stippled 1x1 quad covering that pixel
    int want_ci = primitive_wants_ci(sv);
    batch_select_pattern(0);
    batch_select_blend(want_ci ? 0 : blend_enabled);
    batch_select_texture(want_ci ? 0 : texture_enabled);
    batch_select_ci(want_ci, want_ci && writemask_is_partial());
    float px = floorf(clampf(sv->x / (float)SCREEN_VERTEX_V2_SCALE, 0, fb_width - 1));
    float py = floorf(clampf(sv->y / (float)SCREEN_VERTEX_V2_SCALE, 0, fb_height - 1));
    float z = sv_z01(sv);
    uint16_t ci = sv->ci & 0xfff;
    uint8_t r = want_ci ? (ci & 0xff) : sv->r;
    uint8_t g = want_ci ? (ci >> 8)   : sv->g;
    uint8_t b = want_ci ? 0           : sv->b;
    uint8_t a = want_ci ? 255         : sv->a;

    batch_reserve(6);
    emit_vertex(px,     py,     z, r, g, b, a);
    emit_vertex(px + 1, py,     z, r, g, b, a);
    emit_vertex(px + 1, py + 1, z, r, g, b, a);
    emit_vertex(px + 1, py + 1, z, r, g, b, a);
    emit_vertex(px,     py + 1, z, r, g, b, a);
    emit_vertex(px,     py,     z, r, g, b, a);
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
    glUniform2f(u_blit_scale, 2.0f / fb_width, 2.0f / fb_height);
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
    glViewport(0, 0, fb_width, fb_height);

    if (backbuffer_draw_enabled)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, back_buf->fbo);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    if (frontbuffer_draw_enabled)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, front_buf->fbo);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisable(GL_BLEND);
    restore_depth_mask();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//
// state
//

void gles2_rasterizer_writemask(uint16_t wm, uint8_t colormap[][3])
{
    // a pending masked batch composites with the mask that was up when its
    // primitives were emitted
    if (batch_count > 0 && batch_masked_on && wm != the_writemask)
        flush_batch();
    the_writemask = wm;
    if (colormap != the_colormap)
    {
        the_colormap = colormap;
        lut_dirty = 1;
    }
}

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

    return 1; // buffers are allocated by the first gles2_rasterizer_resize
}

const rasterizer_funcs* gles2_rasterizer_get_funcs(void)
{
    static const rasterizer_funcs funcs =
    {
        .winopen            = gles2_rasterizer_winopen,
        .rgbmode            = gles2_rasterizer_rgbmode,
        .clear              = gles2_rasterizer_clear,
        .zclear             = gles2_rasterizer_zclear,
        .zclear_rect        = gles2_rasterizer_zclear_rect,
        .czclear            = gles2_rasterizer_czclear,
        .swap               = gles2_rasterizer_swap,
        .copy_front_to_back = gles2_rasterizer_copy_front_to_back,
        .copy_back_to_front = gles2_rasterizer_copy_back_to_front,
        .frontbuffer        = gles2_rasterizer_frontbuffer,
        .draw               = gles2_rasterizer_draw,
        .bitmap             = gles2_rasterizer_bitmap,
        .alpha_blit         = gles2_rasterizer_alpha_blit,
        .masked_clear       = gles2_rasterizer_masked_clear,
        .writemask          = gles2_rasterizer_writemask,
        .setpattern         = gles2_rasterizer_setpattern,
        .pattern            = gles2_rasterizer_pattern,
        .scissor            = gles2_rasterizer_scissor,
        .layer              = gles2_rasterizer_layer,
        .cbuffer_draw       = gles2_rasterizer_cbuffer_draw,
        .zbuffer            = gles2_rasterizer_zbuffer,
        .blend              = gles2_rasterizer_blend,
        .teximage           = gles2_rasterizer_teximage,
        .texture            = gles2_rasterizer_texture,
        .zwrite             = gles2_rasterizer_zwrite,
        .colormask          = gles2_rasterizer_colormask,
        .linewidth          = gles2_rasterizer_linewidth,
        .frame_sync         = gles2_rasterizer_frame_sync,
        .resize             = gles2_rasterizer_resize,
        .ci_frontbuffer     = gles2_rasterizer_ci_frontbuffer,
        .resolve_ci_to_rgb  = gles2_rasterizer_resolve_ci_to_rgb,
    };
    return &funcs;
}
