//
//  Provide an SDL framebuffer for IRIS GL to render into
//
//  Two types of framebuffers are provided:
//  1. An SDL_texture is updated with IRIS GL's ref rasterizer buffer, and displayed using SDL_RenderCopy & SDL_RenderPresent
//  2. An OpenGL texture is updated with IRIS GL's ref rasterizer buffer, and displayed using glDrawArrays & SDL_GL_SwapWindow
//
//  The OpenGL texture framebuffer is a stepping stone towards having an OpenGL rasterizer, which opens up
//  faster rendering -- especially important for arbitrary window sizes and texture mapping.
//
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#include "sdl_framebuffer.h"
#include "sdl_events.h"

static const int fbBitsPerPixel = 32;
static bool useGLFramebuffer = false;

// Enable to debug initial test texture
static bool debugTexBuild = false;
// Enable to debug texture updates
static bool debugTexUpdate = false;

typedef struct
{
    // SDL Window
    char title[256];
    SDL_Window* pWindow;
    Uint32 windowID;
    Size2D windowSize;

    // Rendered framebuffer
    Size2D size;                // Framebuffer size (<= window size)
    unsigned char* pSrcPixels;  // Framebuffer source pixels
    GLfloat pixelScale;         // Handle SDL_WINDOW_ALLOW_HIGHDPI 

    // OGL framebuffer
    GLuint  glShaderProg;       // Framebuffer shader
    GLint   glShaderVpSize;     // Viewport size is same as window size
    GLint   glShaderFbSize;      
    GLint   glShaderTexSize;    
    GLint   glShaderPixelScale;  
    GLuint  glTex;              // Texture object for displaying the framebuffer
    GLsizei glTexSize[2];       // Texture size >= framebuffer size (GLES n^2 texture reqmt)
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

    .size = {800, 480},
    .pSrcPixels = NULL, 

    // OGL framebuffer
    .glShaderProg = 0,
    .glShaderVpSize = 0,
    .glShaderFbSize = 0,
    .glShaderTexSize = 0,
    .glShaderPixelScale = 0,
    .glTex = 0,
    .glTexSize = {0, 0},
    .glQuadVBO = 0,
    .glContext = NULL,
    .pixelScale = 1.0f,

    // SDL framebuffer
    .pSDLTex = NULL,
    .pSDLRenderer = NULL,
};

static int min(int x, int y)            { return x < y ? x : y; }
static int nextPowerOfTwo(int val)      { int power = 1; while (power < val) power *= 2; return power; }
static void showFrameCounter()          { static int frameCt = 0; printf("frame = %d\n", frameCt++); }
static int normWindowWidth()            { return fb.windowSize.width / fb.pixelScale; }
static int normWindowHeight()           { return fb.windowSize.height / fb.pixelScale; }
static int windowToFramebufferOffsetX() { return normWindowWidth() / 2 - fb.size.width / 2; }
static int windowToFramebufferOffsetY() { return normWindowHeight() / 2 - fb.size.height / 2; }

// Shader for displaying the framebuffer texture on a quad which fills the viewport
const GLchar* fbVertexSource =
    "attribute vec4 position;                                           \n"
    "varying vec2 texCoord;                                             \n"
    "uniform float pixelScale;                                          \n"
    "uniform vec2 vpSize;                                               \n"
    "uniform vec2 fbSize;                                               \n"
    "uniform vec2 texSize;                                              \n"
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
    "    // Texture coords                                              \n"
    "                                                                   \n"
    "    // Zoom in texture to only show framebuffer                    \n"
    "    texCoord.x = position.x * fbSize.x / texSize.x;                \n"
    "    texCoord.y = position.y * fbSize.y / texSize.y;                \n"
    "                                                                   \n"
    "    // Invert and offset y to put fb origin at upper left          \n"
    "    texCoord.y = -texCoord.y;                                      \n"
    "    texCoord.y -= (texSize.y - fbSize.y) / texSize.y;              \n"
    "}                                                                  \n";

const GLchar* fbFragmentSource =
    "precision mediump float;                                           \n"
    "varying vec2 texCoord;                                             \n"
    "uniform sampler2D texSampler;                                      \n"
    "void main()                                                        \n"
    "{                                                                  \n"
    "    // Sample ABGR fb texture, then swap B and R, and make A opaque\n"
    "    vec3 texel = texture2D(texSampler, texCoord).rgb;              \n"
    "    gl_FragColor = vec4(texel.b, texel.g, texel.r, 1.0);           \n"
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

static void updateShaderVars()
{
    glUseProgram(fb.glShaderProg);

    GLfloat windowSize[2] = {fb.windowSize.width, fb.windowSize.height};
    glUniform2fv(fb.glShaderVpSize, 1, windowSize);
    
    GLfloat fbSize[2] = {fb.size.width, fb.size.height};
    glUniform2fv(fb.glShaderFbSize, 1, fbSize);
    
    GLfloat texSize[2] = {fb.glTexSize[0], fb.glTexSize[1]};
    glUniform2fv(fb.glShaderTexSize, 1, texSize);

    glUniform1f(fb.glShaderPixelScale, fb.pixelScale);
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
    fb.glShaderTexSize    = glGetUniformLocation(fb.glShaderProg, "texSize");
    fb.glShaderPixelScale = glGetUniformLocation(fb.glShaderProg, "pixelScale");
    
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

void sdlInitWindow()
{  
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

        fb.pWindow = SDL_CreateWindow(
            fb.title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            fb.windowSize.width, fb.windowSize.height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
        );

        fb.glContext = SDL_GL_CreateContext(fb.pWindow);
        printf("INFO: GL vendor: %s\n", glGetString(GL_VENDOR));
        printf("INFO: GL renderer: %s\n", glGetString(GL_RENDERER));
        printf("INFO: GL version: %s\n", glGetString(GL_VERSION));

        //const float r = 0.2f, g = 0.1f, b = 0.15f, a = 1.0f;
        //glClearColor(r, g, b, a);
        glClearColor(0,0,0,1.0f);
 
        // handle high DPI scaling by getting ratio of requested to actual window size
        int requestedWidth = fb.windowSize.width;
        SDL_GL_GetDrawableSize(fb.pWindow, &fb.windowSize.width, &fb.windowSize.height);
        fb.pixelScale = fb.windowSize.width / requestedWidth; 
        printf("INFO: GL pixel scale: %f\n", fb.pixelScale);
        
        glViewport(0, 0, fb.windowSize.width, fb.windowSize.height);
        printf("INFO: GL viewport: %dx%d\n", fb.windowSize.width, fb.windowSize.height);

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

        // const Uint8 r = 0.2f * 255, g = 0.1f * 255, b = 0.15f * 255, a = 255;
        // SDL_SetRenderDrawColor(fb.pSDLRenderer, r, g, b, a);
        SDL_SetRenderDrawColor(fb.pSDLRenderer, 0, 0, 0, 255);
    }

    fb.windowID = SDL_GetWindowID(fb.pWindow);
    SDL_StartTextInput();
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

static bool validTexSize(int texWidth, int texHeight)
{
    // Don't exceed max GL texture size
    // - Also may need to increase WASM heap via -s TOTAL_MEMORY
    // - Typical framebuffer sizes and memory usage:
    //   5120x2880 57MB
    //   3840x2160 32MB
    //   2738x2048 22MB
    //   1920x1080 8MB
    //   1280x1024 5MB
    GLint maxTextureSize = 256;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    int clampedWidth  = min(texWidth,  maxTextureSize),
        clampedHeight = min(texHeight, maxTextureSize);
    if (clampedWidth < texWidth || clampedHeight < texHeight)
    {
        printf("ERROR: texture size=%dx%d exceeds GL max texture size=%dx%d\n", 
            texWidth, texHeight, clampedWidth, clampedHeight);
        return false;
    }
    return true;
}

static void checkValidTex()
{
    static int calls = 0;
    if (++calls <= 3)
    {
        char texture_info[256];
        snprintf(texture_info, sizeof(texture_info), "%s texture id %d (%dx%d) for fb (%dx%d)", 
            calls == 1 ? "built" : "updated",
            fb.glTex, fb.glTexSize[0], fb.glTexSize[1],
            fb.size.width, fb.size.height
        );
        GLenum glError = glGetError();
        if (glError == GL_NO_ERROR)
            printf("INFO: GL %s OK\n", texture_info);
        else
            printf("ERROR: GL %s code: 0x%x\n", texture_info, glError);
    }
}

void sdlInitFramebufferTexture()
{
    if (useGLFramebuffer) 
    {
        // OpenGLES requires power of 2 dimension textures, so create the smallest
        // power of 2 image that fits the framebuffer
        int texWidth = nextPowerOfTwo(fb.size.width),
            texHeight = nextPowerOfTwo(fb.size.height);
        if (!validTexSize(texWidth, texHeight))
            exit(1);

        // Generate SDL surface for initial texture
        SDL_Surface* fbTexture = 
            createTexSurface(texWidth, texHeight, fb.size.width, fb.size.height);
    
        // Generate GL texture object and bind as current
        glGenTextures(1, &fb.glTex);
        glBindTexture(GL_TEXTURE_2D, fb.glTex);

        // Set the GL texture's wrapping and stretching properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       // repeat needed for flipping y in shader
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // nearest filter = looks vintage
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // nearest filter = looks vintage

        // Upload SDL image to GL texture
        GLint level_0 = 0, no_border = 0;
        fb.glTexSize[0] = (GLsizei)fbTexture->w;
        fb.glTexSize[1] = (GLsizei)fbTexture->h;
        glTexImage2D(GL_TEXTURE_2D, level_0, GL_RGBA, 
                     fb.glTexSize[0], fb.glTexSize[1], 
                     no_border, GL_RGBA, GL_UNSIGNED_BYTE,
                     fbTexture->pixels);

        // Check for errors and free SDL surface
        checkValidTex();
        SDL_FreeSurface(fbTexture);

        // Update shader with texture size
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
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(fb.glShaderProg);
        glBindTexture(GL_TEXTURE_2D, fb.glTex);
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
void sdlResizeWindow(Uint32 windowID)
{
    if (windowID == fb.windowID)
    {
        SDL_GL_GetDrawableSize(fb.pWindow, &fb.windowSize.width, &fb.windowSize.height);
        printf("INFO: resize window: %dx%d\n", fb.windowSize.width, fb.windowSize.height);

        if (useGLFramebuffer)
        {
            glViewport(0, 0, fb.windowSize.width, fb.windowSize.height);
            updateShaderVars();
        }

        // TODO: For now, framebuffer size is static.  Future: make framebuffer and
        // window size the same, and rebuild framebuffer texture here on resizes (and
        // communicate size change back to IRIS GL)        
    }
}

void sdlOpenWindow(char *title, int32_t frameWidth, int32_t frameHeight)
{
    printf("INFO: open window: %s %dx%d\n", title, frameWidth, frameHeight);
    strncpy(fb.title, title, sizeof(fb.title));

#ifndef __EMSCRIPTEN__
    // Emscripten sets window title to 'this.program' on calling SDL_SetWindowTitle
    if (fb.pWindow)
        SDL_SetWindowTitle(fb.pWindow, fb.title);
#endif

    fb.size = (Size2D) { frameWidth, frameHeight };

    if (useGLFramebuffer)
        updateShaderVars();

    // TODO: come back to this when we get framebuffer resizing working
    // Q: how does the timing on this work, it needs to be called
    // before sdlInitWindow so SDL framebuffer can be initialized at
    // the correct size? 
    // A: sdlOpenWindow just happens to specify the same size as the
    // initial size
}

void sdlSetFramebufferSource(unsigned char* pSrcPixels)
{
    static int calls = 0;
    if (++calls <= 1)
        printf("SDL fb source = %p\n", pSrcPixels);
    fb.pSrcPixels = pSrcPixels;
}

// For now, window and framebuffer dimensions may differ, so convert
// incoming window coords to framebuffer coords, including inverting y    
static int clamp(int v, int low, int high)          { return v > high ? high : (v < low ? low : v); }
static bool would_clamp(int v, int low, int high)   { return v < low || v > high; }
static int framebufferX(int windowX)                { return windowX - windowToFramebufferOffsetX(); }
static int framebufferY(int windowY)                { return normWindowHeight() - windowY - windowToFramebufferOffsetY(); }

int sdlClampToFramebufferX(int windowX)             { return clamp(framebufferX(windowX), 1, fb.size.width - 1); }
int sdlClampToFramebufferY(int windowY)             { return clamp(framebufferY(windowY), 1, fb.size.height - 1); }

bool sdlInsideFramebuffer(int windowX, int windowY)
{
    return !would_clamp(framebufferX(windowX), 1, fb.size.width - 1) 
        && !would_clamp(framebufferY(windowY), 1, fb.size.height - 1);
}