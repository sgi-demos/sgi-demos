//
//  Provide an SDL framebuffer for IRIS GL to render into
//
//  Two types of framebuffers are provided:
//  1. An SDL_texture is updated with ref rasterizer frontbuffer or GLES2 front FBO, and displayed using SDL_RenderCopy & SDL_RenderPresent
//  2. An OpenGL texture is updated with ref rasterizer frontbuffer or GLES2 front FBO,, and displayed using glDrawArrays & SDL_GL_SwapWindow
//
//  The OpenGL texture framebuffer is a stepping stone towards having an OpenGL rasterizer, which opens up
//  faster rendering -- especially important for arbitrary window sizes and texture mapping.
//
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "sdl_framebuffer.h"

static const int fbBitsPerPixel = 32;
static bool useGLFramebuffer = true;

// Enable to debug initial test texture
static bool debugTexBuild = false;
// Enable to debug texture updates
static bool debugTexUpdate = false;

typedef struct { int width; int height; } Size2D;
typedef struct
{
    // SDL Window
    char title[256];
    SDL_Window* pWindow;
    Uint32 windowID;
    Size2D windowSize;          // Drawable size in device pixels (GL viewport space)
    Size2D logicalSize;         // SDL window size in points (the space mouse coords arrive in)

    // Rendered framebuffer
    Size2D size;                // Framebuffer size (<= window size)
    unsigned char* pSrcPixels;  // Framebuffer source pixels
    GLfloat pixelScale;         // Device pixels per point: windowSize / logicalSize (SDL_WINDOW_ALLOW_HIGHDPI)

    // OGL framebuffer
    GLuint  glShaderProg;       // Framebuffer shader
    GLint   glShaderVpSize;     // Viewport size is same as window size
    GLint   glShaderFbSize;
    GLint   glShaderPixelScale;
    GLint   glShaderYFlip;      // location of bool yFlip: true = source rows are top-down (CPU upload path)
    GLint   glShaderRBSwap;     // location of float rbSwap: 1.0 = source bytes are BGRA (CPU upload path)
    GLuint  glTex;              // Texture object for displaying the framebuffer
    GLuint  extTex;             // Framebuffer-sized external texture (gles2 rasterizer front FBO, 0 for CPU upload path)
    GLuint  glQuadVBO;          // Quad geometry for displaying the texture
    SDL_GLContext glContext;    // OGL renderer context

    // SDL framebuffer
    SDL_Texture*  pSDLTex;      // Texture for displaying the framebuffer
    SDL_Renderer* pSDLRenderer; // SDL renderer
} SDLFramebuffer;

static SDLFramebuffer fb = (SDLFramebuffer)
{
    .title = {"sgi-demos"},
    .pWindow = NULL,
    .windowID = 0,
    .windowSize = {880, 560},
    .logicalSize = {880, 560},

    .size = {800, 480},
    .pSrcPixels = NULL,

    // OGL framebuffer
    .glShaderProg = 0,
    .glShaderVpSize = 0,
    .glShaderFbSize = 0,
    .glShaderPixelScale = 0,
    .glShaderYFlip = 0,
    .glShaderRBSwap = 0,
    .glTex = 0,
    .extTex = 0,
    .glQuadVBO = 0,
    .glContext = NULL,
    .pixelScale = 1.0f,

    // SDL framebuffer
    .pSDLTex = NULL,
    .pSDLRenderer = NULL,
};

static int min(int x, int y)            { return x < y ? x : y; }

// Max framebuffer dimension: screen_vertex coordinates are int32 fixed
// point (no practical limit), so the bound is the GL max texture size (all
// framebuffer textures — the CPU-upload display texture and the gles2
// rasterizer's FBO color textures — are exact framebuffer-sized). Queried
// from GL once the context exists; conservative default before that.
// Typical framebuffer memory (RGBA): 5120x2880 57MB, 3840x2160 32MB,
// 1920x1080 8MB — heap allocated per color buffer by the rasterizers.
static int maxFramebufferDim = 2048;
static void showFrameCounter()          { static int frameCt = 0; printf("frame = %d\n", frameCt++); }

// Mouse coordinates arrive in SDL's logical window space; the framebuffer is
// displayed at 1:1 in that same space, centered (the GL quad spans
// fb.size * pixelScale device pixels = fb.size points). Both transforms
// derive from logicalSize so display and hit testing always agree.
static void displayedFbSizeFwd(int *w, int *h);
static int windowToFramebufferOffsetX() { int w, h; displayedFbSizeFwd(&w, &h); return fb.logicalSize.width / 2 - w / 2; }
static int windowToFramebufferOffsetY() { int w, h; displayedFbSizeFwd(&w, &h); return fb.logicalSize.height / 2 - h / 2; }

// Refresh the window geometry: logical size (points), drawable size (device
// pixels), and their ratio. Called at window creation and on every resize.
static void updateWindowGeometry()
{
    SDL_GetWindowSize(fb.pWindow, &fb.logicalSize.width, &fb.logicalSize.height);

    if (useGLFramebuffer)
        SDL_GL_GetDrawableSize(fb.pWindow, &fb.windowSize.width, &fb.windowSize.height);
    else
        fb.windowSize = fb.logicalSize;

    fb.pixelScale = (fb.logicalSize.width > 0)
        ? (GLfloat)fb.windowSize.width / (GLfloat)fb.logicalSize.width
        : 1.0f;
}

// keepaspect(): x:y aspect the framebuffer must keep, 0:0 = unconstrained.
// On IRIX the window manager enforced keepaspect on the window; here the
// framebuffer keeps the aspect at the largest size that fits the window,
// centered (letterboxed) by the existing display/mouse offset math.
static Size2D fbAspect = {0, 0};

//
// SGI display simulation (issue #9). SGI framebuffers were 5:4 (1280x1024)
// shown on 4:3 CRT glass, making each pixel 16:15 wide (non-square). We
// reproduce that in the present pass by STRETCHING horizontally: the
// framebuffer gets 15/16 the columns of the window and the displayed image
// is widened 16/15, exactly filling the window (no letterbox) with the
// authentic CRT proportions. Stretching (magnification) rather than
// squashing (minification) so no framebuffer row/column is ever dropped by
// the NEAREST sampling, at any display density. Display-only: rasterizer
// output and PPM dumps are untouched.
//
// Config (native env / web URL param):
//   SGI_PAR=0|1      / ?par=0|1        pixel aspect correction (default 1)
//
#define SGI_PAR_NUM 15  // displayed width = fb columns * 16/15
#define SGI_PAR_DEN 16

static bool parEnabled = true;

// Fixed framebuffer size (demo compatibility quirk): some demos are
// hard-authored for the classic screen (compile-time viewport constants);
// they get exactly that framebuffer and the display scales it to the
// window. 0,0 = normal window-tracking framebuffer.
static Size2D fbFixedSize = {0, 0};

void sdlSetFramebufferFixedSize(int32_t width, int32_t height)
{
    fbFixedSize.width = width;
    fbFixedSize.height = height;
}

// Displayed size of the framebuffer in window points: PAR widens columns
// by 16/15; a fixed-size framebuffer additionally scales to the largest
// fit in the window (the window conforms via keepaspect, so it fills)
static void displayedFbSize(int *w, int *h)
{
    int64_t ax = (int64_t)fb.size.width  * (parEnabled ? SGI_PAR_DEN : 1);
    int64_t ay = (int64_t)fb.size.height * (parEnabled ? SGI_PAR_NUM : 1);

    if (fbFixedSize.width > 0 && ax > 0 && ay > 0)
    {
        int64_t W = fb.logicalSize.width, H = fb.logicalSize.height;
        if (W * ay > H * ax) { *h = (int)H; *w = (int)((H * ax + ay / 2) / ay); }
        else                 { *w = (int)W; *h = (int)((W * ay + ax / 2) / ax); }
    }
    else
    {
        *w = parEnabled ? (fb.size.width * SGI_PAR_DEN + SGI_PAR_NUM / 2) / SGI_PAR_NUM
                        : fb.size.width;
        *h = fb.size.height;
    }
}
static void displayedFbSizeFwd(int *w, int *h) { displayedFbSize(w, h); }

// Parse the SGI display simulation config: native env vars, web URL params
static void parseDisplayConfig(void)
{
    const char *v;
    if ((v = getenv("SGI_PAR")) != NULL)    parEnabled = atoi(v) != 0;

#ifdef __EMSCRIPTEN__
    int q;
    q = EM_ASM_INT({
        var m = window.location.search.match(/[?&]par=([0-9]+)/);
        return m ? (m[1] | 0) : -1;
    });
    if (q >= 0) parEnabled = q != 0;
#endif

    printf("INFO: SGI display sim: par=%d\n", parEnabled);
}

void sdlSetFramebufferAspect(int32_t x, int32_t y)
{
    fbAspect.width = x;
    fbAspect.height = y;
}

// Shrink one axis of w x h (a WINDOW/displayed size, in points) to the
// largest size matching the aspect constraint (no-op when unconstrained).
// The declared aspect is the FRAMEBUFFER shape; with PAR correction on,
// the displayed shape is wider by 16:15 (5:4 fb displays as 4:3 — the
// SGI CRT geometry), so fit against aspect scaled by the pixel aspect.
static void aspectFitSize(int *w, int *h)
{
    if (fbAspect.width <= 0 || fbAspect.height <= 0)
        return;

    int64_t ax = (int64_t)fbAspect.width  * (parEnabled ? SGI_PAR_DEN : 1);
    int64_t ay = (int64_t)fbAspect.height * (parEnabled ? SGI_PAR_NUM : 1);

    // round to nearest so fitting an already-fitted size is a no-op
    if ((int64_t)*w * ay > (int64_t)*h * ax)
        *w = (int)(((int64_t)*h * ax + ay / 2) / ay);
    else
        *h = (int)(((int64_t)*w * ay + ax / 2) / ax);
}

// The framebuffer tracks the window's logical size (capped at the GL max
// texture size; aspect-constrained if keepaspect was called; stays centered
// when smaller than the window). With PAR correction the framebuffer gets
// 15/16 the columns of its displayed width, so the 16/15 display stretch
// fills the window exactly. Returns true when the size changed.
static bool updateFramebufferSize()
{
    int w, h;

    if (fbFixedSize.width > 0 && fbFixedSize.height > 0)
    {
        // demo compatibility quirk: classic fixed-size framebuffer; the
        // display scales it to the window (see displayedFbSize)
        w = min(fbFixedSize.width, maxFramebufferDim);
        h = min(fbFixedSize.height, maxFramebufferDim);
    }
    else
    {
    // displayed (window-point) size first...
    w = min(fb.logicalSize.width, maxFramebufferDim);
    h = min(fb.logicalSize.height, maxFramebufferDim);
    aspectFitSize(&w, &h);

    // ...then the framebuffer column count behind it (rounded so the
    // 16/15 display stretch lands back on the displayed width)
    if (parEnabled)
        w = (w * SGI_PAR_NUM + SGI_PAR_DEN / 2) / SGI_PAR_DEN;
    }

    if (w < 1) w = 1;
    if (h < 1) h = 1;

    if (w == fb.size.width && h == fb.size.height)
        return false;

    fb.size.width = w;
    fb.size.height = h;
    return true;
}

static void updateShaderVars(); // defined below (needs the shader in scope)

// Re-fit the framebuffer to the current window and aspect constraint,
// rebuilding the display texture on a size change. Shared by the resize
// path and keepaspect(). Returns true when the framebuffer size changed
// (the caller then resizes the rasterizer and sends the demo a REDRAW).
// Native: snap the window to the (displayed) aspect constraint now — used
// when a constraint arrives after window creation (e.g. flight calls
// keepaspect after winopen)
static void conformWindowToAspect(void)
{
#ifndef __EMSCRIPTEN__
    if (!fb.pWindow)
        return;
    int fitW = fb.logicalSize.width, fitH = fb.logicalSize.height;
    aspectFitSize(&fitW, &fitH);
    if (fitW != fb.logicalSize.width || fitH != fb.logicalSize.height)
        SDL_SetWindowSize(fb.pWindow, fitW, fitH);
#endif
}

bool sdlApplyFramebufferSize(void)
{
    if (!fb.pWindow)
        return false; // pre-window keepaspect: applied at window creation

    conformWindowToAspect();

    bool changed = updateFramebufferSize();
    if (changed)
    {
        sdlFreeFramebufferTexture();
        sdlInitFramebufferTexture();
        if (useGLFramebuffer)
            updateShaderVars();
    }
    return changed;
}

void sdlGetFramebufferSize(int32_t *width, int32_t *height)
{
    *width = fb.size.width;
    *height = fb.size.height;
}

// Shader for displaying the framebuffer texture on a quad which fills the viewport
const GLchar* fbVertexSource =
    "attribute vec4 position;                                           \n"
    "varying vec2 texCoord;                                             \n"
    "uniform float pixelScale;                                          \n"
    "uniform vec2 vpSize;                                               \n"
    "uniform vec2 fbSize;                                               \n"
    "uniform bool yFlip;                                                \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    // Geometry                                                    \n"
    "                                                                   \n"
    "    // Scale to framebuffer size                                   \n"
    "    gl_Position = vec4(position.xy, 0.0, 1.0);                     \n"
    "    gl_Position.x *= fbSize.x;                                     \n"
    "    gl_Position.y *= fbSize.y;                                     \n"
    "                                                                   \n"
    "    // Translate to framebuffer's lower left                       \n"
    "    gl_Position.x -= fbSize.x / 2.0 + 1.0;                         \n"
    "    gl_Position.y -= fbSize.y / 2.0 + 1.0;                         \n"
    "                                                                   \n"
    "    // Ortho project                                               \n"
    "    gl_Position.x *= 2.0 / vpSize.x * pixelScale;                  \n"
    "    gl_Position.y *= 2.0 / vpSize.y * pixelScale;                  \n"
    "                                                                   \n"
    "    // Texture coords: both sources are exact framebuffer-sized    \n"
    "    // textures. CPU-uploaded textures store rows top-down: flip y \n"
    "    // to put the fb origin at upper left. FBO textures (gles2     \n"
    "    // rasterizer) are bottom-up like GL wants: no flip.           \n"
    "    texCoord = position.xy;                                        \n"
    "    if (yFlip)                                                     \n"
    "        texCoord.y = 1.0 - texCoord.y;                             \n"
    "}                                                                  \n";

const GLchar* fbFragmentSource =
    "precision mediump float;                                           \n"
    "varying vec2 texCoord;                                             \n"
    "uniform sampler2D texSampler;                                      \n"
    "uniform float rbSwap;                                              \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    // CPU-uploaded textures hold BGRA bytes: swap B and R.        \n"
    "    // FBO textures (gles2 rasterizer) are true RGBA: no swap.     \n"
    "    vec3 texel = texture2D(texSampler, texCoord).rgb;              \n"
    "    gl_FragColor = vec4(mix(texel, texel.bgr, rbSwap), 1.0);       \n"
    "}                                                                  \n";

static void checkShaderBuilt(const char* shader_name, GLenum status, GLuint shader)
{
    GLint success;
    glGetShaderiv(shader, status, &success);
    if (success)
        printf("INFO: GL %s shader id %d build OK\n", shader_name, shader);
    else
        printf("ERROR: GL %s shader id %d build FAILED!\n", shader_name, shader);
}

// The texture the present quad samples: the external FBO texture when set
// (gles2 rasterizer), else the CPU-upload texture
static GLuint presentTexSource()
{
    return fb.extTex ? fb.extTex : fb.glTex;
}

static void updateShaderVars()
{
    glUseProgram(fb.glShaderProg);

    GLfloat windowSize[2] = {fb.windowSize.width, fb.windowSize.height};
    glUniform2fv(fb.glShaderVpSize, 1, windowSize);

    // the quad geometry uses the DISPLAYED size: PAR stretches the
    // framebuffer columns 16/15, and a fixed-size framebuffer scales to
    // the window (see SGI display sim / demo quirks)
    int dispW, dispH;
    displayedFbSize(&dispW, &dispH);
    GLfloat fbSize[2] = {dispW, dispH};
    glUniform2fv(fb.glShaderFbSize, 1, fbSize);

    glUniform1f(fb.glShaderPixelScale, fb.pixelScale);


    // Source-dependent vars. Both sources are exact framebuffer-sized
    // NPOT textures — legal to sample with CLAMP_TO_EDGE and no mipmaps,
    // which is how both are built (the old POT requirement came from the
    // y-flip's GL_REPEAT wrap; the flip is now done in positive texcoord
    // space). CPU-upload texture: BGRA bytes, top-down. External FBO
    // texture (gles2 rasterizer): true RGBA, bottom-up.
    bool useExtTex = fb.extTex != 0;
    glUniform1i(fb.glShaderYFlip, useExtTex ? 0 : 1);        // bool uniform
    glUniform1f(fb.glShaderRBSwap, useExtTex ? 0.0f : 1.0f); // float: used in mix()
}

static void initShader()
{
    // Create and compile vertex shader
    GLuint fbVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fbVertexShader, 1, &fbVertexSource, NULL);
    glCompileShader(fbVertexShader);
    checkShaderBuilt("vertex", GL_COMPILE_STATUS, fbVertexShader);

    // Create and compile fragment shader
    GLuint fbFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fbFragmentShader, 1, &fbFragmentSource, NULL);
    glCompileShader(fbFragmentShader);
    checkShaderBuilt("fragment", GL_COMPILE_STATUS, fbFragmentShader);

    // Link vertex and fragment shader into shader program
    fb.glShaderProg = glCreateProgram();
    glAttachShader(fb.glShaderProg, fbVertexShader);
    glAttachShader(fb.glShaderProg, fbFragmentShader);
    glLinkProgram(fb.glShaderProg);
    glUseProgram(fb.glShaderProg);

    // Get shader variables and initalize them
    fb.glShaderVpSize     = glGetUniformLocation(fb.glShaderProg, "vpSize");
    fb.glShaderFbSize     = glGetUniformLocation(fb.glShaderProg, "fbSize");
    fb.glShaderPixelScale = glGetUniformLocation(fb.glShaderProg, "pixelScale");
    fb.glShaderYFlip      = glGetUniformLocation(fb.glShaderProg, "yFlip");
    fb.glShaderRBSwap     = glGetUniformLocation(fb.glShaderProg, "rbSwap");

    updateShaderVars();
}

static void initGeometry()
{
    // Create vertex buffer object (VBO) and copy vertex data into it
    glGenBuffers(1, &fb.glQuadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, fb.glQuadVBO);
    GLfloat quadVertices[] =
    {
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
}

uint32_t sdlInitWindow()
{
    // SGI display simulation options (affect window/framebuffer geometry)
    parseDisplayConfig();

    // The window itself keeps the aspect (IRIX keepaspect semantics): born
    // conforming, so the framebuffer fills it exactly — no letterboxing.
    // (On web SDL adopts the canvas CSS size instead; the framebuffer then
    // centers in the canvas and the page background plays the desktop.)
    aspectFitSize(&fb.windowSize.width, &fb.windowSize.height);
    fb.logicalSize = fb.windowSize;

    // Create SDL window
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_version version;
    SDL_GetVersion(&version);
    printf("INFO: SDL version: %d.%d.%d\n", version.major, version.minor, version.patch);

    // OpenGLES framebuffer
    if (useGLFramebuffer)
    {
        // Init OpenGLES driver and context
        SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetSwapInterval(1); // 1 = sync framerate to refresh rate (no screen tearing)

        // Explicitly set channel depths, otherwise we might get some < 8
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        // ES 3.0 (WebGL2 on web): the gles2 rasterizer's color-index buffer
        // path needs ES3 shaders. All other GL use stays at the ES2 API
        // level, so if 3.0 isn't available fall back to a 2.0 context and
        // the CI path degrades gracefully.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        fb.pWindow = SDL_CreateWindow(
            fb.title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            fb.windowSize.width, fb.windowSize.height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
        );

        fb.glContext = SDL_GL_CreateContext(fb.pWindow);
        if (fb.glContext == NULL)
        {
            printf("INFO: ES 3.0 context unavailable (%s), falling back to ES 2.0\n", SDL_GetError());
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
            fb.glContext = SDL_GL_CreateContext(fb.pWindow);
        }
        printf("INFO: GL vendor: %s\n", glGetString(GL_VENDOR));
        printf("INFO: GL renderer: %s\n", glGetString(GL_RENDERER));
        printf("INFO: GL version: %s\n", glGetString(GL_VERSION));

        //const float r = 0.2f, g = 0.1f, b = 0.15f, a = 1.0f;
        //glClearColor(r, g, b, a);
        glClearColor(0,0,0,1.0f);

        // All framebuffer textures are exact framebuffer-sized, so the GL
        // max texture size is the framebuffer dimension cap
        GLint maxTextureSize = 0;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
        if (maxTextureSize > 0)
            maxFramebufferDim = maxTextureSize;
        printf("INFO: GL max texture size: %d\n", maxFramebufferDim);

        // Window geometry: logical (mouse) size, drawable (GL) size, and
        // their HIGHDPI ratio. NOTE: must be float division — on web the
        // canvas can be any size (e.g. fullwindow shells), so the ratio is
        // not necessarily a whole number
        updateWindowGeometry();
        updateFramebufferSize();
        printf("INFO: GL window: %dx%d points, viewport %dx%d px, pixel scale %f, fb %dx%d\n",
               fb.logicalSize.width, fb.logicalSize.height,
               fb.windowSize.width, fb.windowSize.height, fb.pixelScale,
               fb.size.width, fb.size.height);

        glViewport(0, 0, fb.windowSize.width, fb.windowSize.height);

        initShader();
        initGeometry();
    }

    // SDL framebuffer
    else
    {
        fb.pWindow = SDL_CreateWindow(
            fb.title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            fb.windowSize.width, fb.windowSize.height,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

        fb.pSDLRenderer = SDL_CreateRenderer(fb.pWindow, -1, 0);

        updateWindowGeometry();
        updateFramebufferSize();

        // const Uint8 r = 0.2f * 255, g = 0.1f * 255, b = 0.15f * 255, a = 255;
        // SDL_SetRenderDrawColor(fb.pSDLRenderer, r, g, b, a);
        SDL_SetRenderDrawColor(fb.pSDLRenderer, 0, 0, 0, 255);
    }

    fb.windowID = SDL_GetWindowID(fb.pWindow);
    SDL_StartTextInput();

    return (uint32_t)fb.windowID;
}

// True once the GL context exists (i.e. after sdlInitWindow on the GL
// display path). The gles2 rasterizer polls this to lazily create its GL
// resources, since rasterizer_winopen runs before the window is created.
bool sdlGLContextReady()
{
    return useGLFramebuffer && fb.glContext != NULL;
}

//
// framebuffer texture
//

static void fillTestPixels(unsigned int* pixels,
                           int width, int height,
                           int inner_width, int inner_height,
                           unsigned int inner_border_line,
                           unsigned int outer_border_fill,
                           unsigned int light_checker,
                           unsigned int dark_checker)
{
    const int checkerSize = 100, halfChecker = checkerSize / 2;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const int i = x + y * width;
            if (y == 0 || x == 0 || y == inner_height - 1 || x == inner_width - 1)
                pixels[i] = inner_border_line;

            else if (y > inner_height  - 1 || x > inner_width - 1)
                pixels[i] = outer_border_fill;

            else
            {
                const int yMod = y % checkerSize,
                          xMod = x % checkerSize;
                if ((yMod < halfChecker && xMod < halfChecker)
                    || (yMod >= halfChecker && xMod >= halfChecker))
                    pixels[i] = light_checker;
                else
                    pixels[i] = dark_checker;
            }
        }
    }
}

// Create initial texture surface
// NOTE: Caller must free returned surface when they are done with it!
static SDL_Surface* createTexSurface(int width, int height, int inner_width, int inner_height)
{
    SDL_Surface* pSurface = SDL_CreateRGBSurface(0, width, height, fbBitsPerPixel, 0, 0, 0, 0);

    if (debugTexBuild)
    {
        // Create grey checkerboard surface with yellow border for testing
        unsigned int* pixels = (unsigned int*)pSurface->pixels;
        unsigned int inner_border_line = 0xff00ffff, // yellow
                    outer_border_fill = 0xff00a5ff, // orange
                    light_checker     = 0xffc4c4c4, // light gray
                    dark_checker      = 0xff808080; // dark gray
        fillTestPixels(pixels, width, height, inner_width, inner_height,
                    inner_border_line, outer_border_fill, light_checker, dark_checker);
    }
    return pSurface;
}

static void checkValidTex()
{
    static int calls = 0;
    if (++calls <= 3)
    {
        char texture_info[256];
        snprintf(texture_info, sizeof(texture_info), "%s texture id %d for fb (%dx%d)",
            calls == 1 ? "built" : "updated",
            fb.glTex, fb.size.width, fb.size.height
        );
        GLenum glError = glGetError();
        if (glError == GL_NO_ERROR)
            printf("INFO:  GL %s OK\n", texture_info);
        else
            printf("ERROR: GL %s code: 0x%x\n", texture_info, glError);
    }
}

void sdlInitFramebufferTexture()
{
    if (useGLFramebuffer)
    {
        // Exact framebuffer-sized texture. NPOT is fine to sample with
        // CLAMP_TO_EDGE wrapping and no mipmaps (the y-flip happens in
        // positive texcoord space, so no GL_REPEAT — the old POT reqmt)
        SDL_Surface* fbTexture =
            createTexSurface(fb.size.width, fb.size.height, fb.size.width, fb.size.height);

        // Generate GL texture object and bind as current
        glGenTextures(1, &fb.glTex);
        glBindTexture(GL_TEXTURE_2D, fb.glTex);

        // Set the GL texture's wrapping and stretching properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // nearest filter = looks vintage
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // nearest filter = looks vintage

        // Upload SDL image to GL texture
        GLint level_0 = 0, no_border = 0;
        glTexImage2D(GL_TEXTURE_2D, level_0, GL_RGBA,
                     fb.size.width, fb.size.height,
                     no_border, GL_RGBA, GL_UNSIGNED_BYTE,
                     fbTexture->pixels);

        // Check for errors and free SDL surface
        checkValidTex();
        SDL_FreeSurface(fbTexture);

        updateShaderVars();
    }
    else
    {
        // Create SDL texture from checkerboard surface
        SDL_Surface* pSurface = createTexSurface(fb.size.width, fb.size.height, fb.size.width, fb.size.height);
        fb.pSDLTex = SDL_CreateTextureFromSurface(fb.pSDLRenderer, pSurface);
        SDL_FreeSurface(pSurface);
    }
}

static void fillTestFramebuffer(unsigned int* pixels, int texWidth, int texHeight)
{
    unsigned int inner_border_line = 0x00ffffff, // cyan
                    outer_border_fill = 0x0025afff, // orange
                    light_checker     = 0xafaf00ff, // yellow
                    dark_checker      = 0x600060ff; // dark magenta
    fillTestPixels(pixels, texWidth, texHeight, texWidth, texHeight,
                    inner_border_line, outer_border_fill, light_checker, dark_checker);
}

void sdlUpdateFramebufferTexture()
{
    if (debugTexBuild)
        return;

    // Use external framebuffer texture directly
    if (fb.extTex)
        return;

    if (fb.pSrcPixels)
    {
        if (useGLFramebuffer)
        {
            // Generate SDL surface for debugging texture updates
            int texWidth = fb.size.width, texHeight = fb.size.height;
            unsigned int* pixels = (unsigned int*)fb.pSrcPixels;

            if (debugTexUpdate)
                fillTestFramebuffer(pixels, texWidth, texHeight);

            glBindTexture(GL_TEXTURE_2D, fb.glTex);

            const GLint level_0 = 0, offset_0 = 0;
            glTexSubImage2D(GL_TEXTURE_2D, level_0,
                            offset_0, offset_0,
                            texWidth, texHeight,
                            GL_RGBA, GL_UNSIGNED_BYTE,
                            pixels);
            checkValidTex();
        }
        else
        {
            int pitch = fb.size.width * 4;
            SDL_UpdateTexture(fb.pSDLTex, NULL, fb.pSrcPixels, pitch);
        }
    }
}

void sdlRenderFramebufferTexture()
{
    // Draw the quad VBO with texture bound and use framebuffer shader
    if (useGLFramebuffer)
    {
        // showFrameCounter();
        // Reset state the gles2 rasterizer may have changed (it renders
        // into its own FBOs with depth testing between our frames, and its
        // clears leave the demo's clear color behind)
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, fb.windowSize.width, fb.windowSize.height);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        glClearColor(0, 0, 0, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(fb.glShaderProg);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, presentTexSource());
        glBindBuffer(GL_ARRAY_BUFFER, fb.glQuadVBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        SDL_GL_SwapWindow(fb.pWindow);
    }
    else
    {
        SDL_RenderClear(fb.pSDLRenderer);
        SDL_Rect destRect = (SDL_Rect)
        {
            .x = windowToFramebufferOffsetX(),
            .y = windowToFramebufferOffsetY(),
            fb.size.width,
            fb.size.height
        };
        SDL_RenderCopy(fb.pSDLRenderer, fb.pSDLTex, NULL, &destRect);

        SDL_RenderPresent(fb.pSDLRenderer);
    }
}

void sdlFreeFramebufferTexture()
{
    if (fb.glTex > 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &fb.glTex);
        fb.glTex = 0;
    }

    if (fb.pSDLTex)
    {
        SDL_DestroyTexture(fb.pSDLTex);
        fb.pSDLTex = NULL;
    }
}

//
// framebuffer events
//

// Returns true when the framebuffer size changed (the caller then resizes
// the rasterizer via gl_framebuffer_resized and sends the demo a REDRAW)
bool sdlResizeWindow(Uint32 windowID)
{
    bool fbSizeChanged = false;

    if (windowID == fb.windowID)
    {
        updateWindowGeometry();

#ifndef __EMSCRIPTEN__
        // Native windows keep the aspect like the IRIX window manager did:
        // snap a non-conforming size back to the largest conforming fit.
        // The SDL_SetWindowSize triggers another SIZE_CHANGED that settles
        // (fit of a conforming size is itself). Browser windows can't be
        // constrained; there the framebuffer centers in the canvas instead.
        {
            int fitW = fb.logicalSize.width, fitH = fb.logicalSize.height;
            aspectFitSize(&fitW, &fitH);
            if (fitW != fb.logicalSize.width || fitH != fb.logicalSize.height)
                SDL_SetWindowSize(fb.pWindow, fitW, fitH);
        }
#endif

        // the framebuffer tracks the window (aspect-constrained if the demo
        // called keepaspect); a size change rebuilds the display texture
        fbSizeChanged = sdlApplyFramebufferSize();
        printf("INFO: resize window: %dx%d points, viewport %dx%d px, pixel scale %f, fb %dx%d\n",
               fb.logicalSize.width, fb.logicalSize.height,
               fb.windowSize.width, fb.windowSize.height, fb.pixelScale,
               fb.size.width, fb.size.height);

        if (useGLFramebuffer)
        {
            glViewport(0, 0, fb.windowSize.width, fb.windowSize.height);
            updateShaderVars();
        }
    }

    return fbSizeChanged;
}

void sdlOpenWindow(char *title)
{
    printf("INFO: open window: %s (fb %dx%d)\n", title, fb.size.width, fb.size.height);
    strncpy(fb.title, title, sizeof(fb.title));

#ifndef __EMSCRIPTEN__
    // Emscripten sets window title to 'this.program' on calling SDL_SetWindowTitle
    if (fb.pWindow)
        SDL_SetWindowTitle(fb.pWindow, fb.title);
#endif

    // fb.size is owned by updateFramebufferSize (framebuffer tracks the
    // window); nothing size-related to do here anymore

    if (useGLFramebuffer)
        updateShaderVars();
}

void sdlSetFramebufferSourceMem(unsigned char* pSrcPixels)
{
    static int calls = 0;
    if (++calls <= 1)
        printf("SDL fb source = %p\n", pSrcPixels);
    fb.pSrcPixels = pSrcPixels;
}

// Zero-readback present: display directly from a GL texture (the gles2
// rasterizer's front FBO color texture) instead of uploading CPU pixels.
// The texture must be exactly framebuffer-sized.
void sdlSetFramebufferSourceTex(uint32_t tex)
{
    static int calls = 0;
    if (++calls <= 1)
        printf("SDL fb texture source = %u\n", tex);

    bool changed = fb.extTex != (GLuint)tex;
    fb.extTex = (GLuint)tex;

    // source-dependent shader vars (texSize, yFlip, rbSwap) follow the source
    if (changed && fb.glShaderProg)
        updateShaderVars();
}

// For now, window and framebuffer dimensions may differ, so convert
// incoming window coords to framebuffer coords, including inverting y
static int clamp(int v, int low, int high)          { return v > high ? high : (v < low ? low : v); }
static bool would_clamp(int v, int low, int high)   { return v < low || v > high; }
static int framebufferX(int windowX)
{
    // displayed point within the fb region, then unscale to fb columns
    int dispW, dispH;
    displayedFbSize(&dispW, &dispH);
    int dispX = windowX - windowToFramebufferOffsetX();
    return dispW > 0 ? (int)((int64_t)dispX * fb.size.width / dispW) : dispX;
}
static int framebufferY(int windowY)
{
    // displayed point within the fb region (y-up), then unscale to fb rows
    int dispW, dispH;
    displayedFbSize(&dispW, &dispH);
    int dispY = fb.logicalSize.height - windowY - windowToFramebufferOffsetY();
    return dispH > 0 ? (int)((int64_t)dispY * fb.size.height / dispH) : dispY;
}

int sdlClampToFramebufferX(int windowX)             { return clamp(framebufferX(windowX), 1, fb.size.width - 1); }
int sdlClampToFramebufferY(int windowY)             { return clamp(framebufferY(windowY), 1, fb.size.height - 1); }

bool sdlInsideFramebuffer(int windowX, int windowY)
{
    return !would_clamp(framebufferX(windowX), 1, fb.size.width - 1)
        && !would_clamp(framebufferY(windowY), 1, fb.size.height - 1);
}
