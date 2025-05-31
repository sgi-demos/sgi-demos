//
//  Provide a framebuffer for IRIS GL to draw into
//
//  Two types of framebuffers are provided:
//  1. An SDL_texture is updated with IRIS GL's ref rasterizer buffer, and displayed using SDL_RenderCopy & SDL_RenderPresent
//  2. An OpenGL texture is updated with IRIS GL's ref rasterizer buffer, and displayed using glDrawArrays & SDL_GL_SwapWindow
//
//  The OpenGL texture framebuffer is a stepping stone towards having an OpenGL rasterizer, which opens up
//  faster rendering -- especially important for arbitrary window sizes and texture mapping.
//
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include <SDL_opengles2.h>

#include "sdl_events.h"
#include "EM_CHILD_APP_DECL.h"

//#define SDL_GL_FRAMEBUFFER

// Framerate control:
// - Simulate a decent SGI machine for the time, 60 fps is too fast for some demos (like ideas)
// - Also, in the 80s and 90s, we had way less than 60 fps and we liked it!
// - TODO: Make this a per-demo option
const int SCREEN_FPS = 30; 

#ifdef SDL_GL_FRAMEBUFFER
    // Shader for displaying the framebuffer texture on a quad VBO which fills the viewport
    GLuint framebufferShaderProg = 0;
    GLuint framebufferQuadVBO       = 0;
    GLuint framebufferQuadPosAttrib = 0;
    GLuint framebufferTex           = 0;

    // Size of the displayed framebuffer
    GLfloat framebufferSize[2]      = {0.0f, 0.0f}; 

    // Size of the framebuffer texture, likely larger than displayed framebuffer due to power of 2 dimensions
    GLfloat framebufferTexSize[2]   = {0.0f, 0.0f};   

    const GLchar* framebufferVertexSource =
        "attribute vec4 position;                                       \n"
        "varying vec2 texCoord;                                         \n"
        "uniform vec2 viewport;                                         \n"
        "uniform vec2 framebufferSize;                                  \n"
        "uniform vec2 texSize;                                          \n"
        "void main()                                                    \n"
        "{                                                              \n"
        "    // Scale to framebuffer size                               \n"
        "    gl_Position = vec4(position.xyz, 1.0);                     \n"
        "    gl_Position.x *= framebufferSize.x;                        \n"
        "    gl_Position.y *= framebufferSize.y;                        \n"
        "                                                               \n"
        "    // Translate to framebuffer's lower left                   \n"
        "    gl_Position.x -= framebufferSize.x / 2.0 + 1.0;            \n"
        "    gl_Position.y -= framebufferSize.y / 2.0 + 1.0;            \n"
        "                                                               \n"
        "    // Ortho projection                                        \n"
        "    gl_Position.x += 1.0;                                      \n"
        "    gl_Position.x *= 2.0 / viewport.x;                         \n"
        "    gl_Position.y += 1.0;                                      \n"
        "    gl_Position.y *= 2.0 / viewport.y;                         \n"
        "                                                               \n"
        "    // Framebuffer subrectangle from overall texture           \n"
        "    texCoord.x = position.x * framebufferSize.x / texSize.x;   \n"
        "    texCoord.y = -position.y * framebufferSize.y / texSize.y;  \n"
        "}                                                              \n";

    const GLchar* framebufferFragmentSource =
        "precision mediump float;                                       \n"
        "varying vec2 texCoord;                                         \n"
        "uniform sampler2D texSampler;                                  \n"
        "void main()                                                    \n"
        "{                                                              \n"
        "    gl_FragColor = texture2D(texSampler, texCoord);            \n"
        "}                                                              \n";

    void updateShader(EventHandler& eventHandler)
    {
        glUseProgram(framebufferShaderProg);
        glUniform2fv(shaderViewport, 1, camera.viewport());
        glUniform2fv(shaderImageSize, 1, imageSize);
        glUniform2fv(shaderTexSize, 1, texSize);
    }

    void initShader()
    {
        // Create and compile vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &framebufferVertexSource, NULL);
        glCompileShader(vertexShader);

        // Create and compile fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &framebufferFragmentSource, NULL);
        glCompileShader(fragmentShader);

        // Link vertex and fragment shader into shader program
        GLuint framebufferShaderProg = glCreateProgram();
        glAttachShader(framebufferShaderProg, vertexShader);
        glAttachShader(framebufferShaderProg, fragmentShader);
        glBindAttribLocation(framebufferShaderProg, framebufferQuadPosAttrib, "position");
        glEnableVertexAttribArray(framebufferQuadPosAttrib);
        glLinkProgram(framebufferShaderProg);

        // Get shader variables and initalize them
        shaderViewport = glGetUniformLocation(framebufferShaderProg, "viewport");
        shaderImageSize = glGetUniformLocation(framebufferShaderProg, "imageSize");
        shaderTexSize = glGetUniformLocation(framebufferShaderProg, "texSize");

        updateShader();
    }

    void initGeometry()
    {
        // Create vertex buffer objects and copy vertex data into them
        glGenBuffers(1, &quadVbo);
        glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
        GLfloat quadVertices[] = 
        {
            0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    }

#endif

typedef struct
{
    // Window
    char windowTitle[128];
    SDL_Window* pWindow;
    Uint32 windowID;
    Size2D windowSize;

    // Framebuffer
    Size2D framebufferSize;             // Framebuffer size may differ from window size
    unsigned char* pFramebuffer;        // IRIS GL's framebuffer
    #ifdef SDL_GL_FRAMEBUFFER
        GLuint framebufferQuadShader;   // OGL's quad shader and VBO for displaying the texture
        GLuint framebufferQuadVBO;      
        GLuint framebufferTex;          // OGL's texture for displaying the framebuffer
    #else
        SDL_Texture * pFramebufferTex;  // SDL's texture for displaying the framebuffer
    #endif

    // Renderers
    SDL_Renderer* pRenderer;
    SDL_GLContext glContext;

} SDLState;

static SDLState sdlState = (SDLState)
{
    // Window
    .windowTitle = {"sgi-demos"},
    .pWindow = NULL,
    .windowID = 0,
    .windowSize = {880, 560},

    // Framebuffer
    .framebufferSize = {800, 480},
    .pFramebuffer = NULL, 
    .pFramebufferTex = NULL, 

    // Renderers
    .pRenderer = NULL,
    .glContext = NULL,   
};

void sdlInit(const char *windowTitle)
{  
    if (windowTitle)
        strncpy(sdlState.windowTitle, windowTitle, sizeof(sdlState.windowTitle));

    // Create SDL window
    #ifdef SDL_GL_FRAMEBUFFER
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        SDL_version version;
        SDL_GetVersion(&version);
        printf("INFO: SDL version: %d.%d.%d\n", version.major, version.minor, version.patch);

        // Init OpenGLES driver and context
        SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); 
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetSwapInterval(1); // 1 = sync framerate to refresh rate (no screen tearing)

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        // Explicitly set channel depths, otherwise we might get some < 8
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        sdlState.pWindow = SDL_CreateWindow(
            sdlState.windowTitle,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            sdlState.windowSize.width, sdlState.windowSize.height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
        );

        sdlState.glContext = SDL_GL_CreateContext(sdlState.pWindow);
    #else
        sdlState.pWindow = SDL_CreateWindow(
            sdlState.windowTitle,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            sdlState.windowSize.width, sdlState.windowSize.height,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

        sdlState.pRenderer = SDL_CreateRenderer(sdlState.pWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC
    #endif

    sdlState.windowID = SDL_GetWindowID(sdlState.pWindow);

    // Initialize viewport
    sdlWindowResizeEvent(sdlState.windowID, sdlState.windowSize);

    SDL_StartTextInput();
}


void sdlWindowResizeEvent(Uint32 windowID, Size2D windowSize)
{
    if (windowID == sdlState.windowID)
    {
        sdlState.windowSize = windowSize;

        #ifdef SDL_GL_FRAMEBUFFER
            glViewport(0, 0, windowSize.width, windowSize.height);
        #endif

        // TODO: Make framebuffer and window size the same, and rebuild framebuffer texture here on resizes
    }
}
void sdlWindowOpen(char *title, int32_t frame_width, int32_t frame_height)
{
    strncpy(sdlState.windowTitle, title, sizeof(sdlState.windowTitle));

#ifndef __EMSCRIPTEN__
    // Emscripten sets window title to 'this.program' if SDL_SetWindowTitle is called
    if (sdlState.pWindow)
        SDL_SetWindowTitle(sdlState.pWindow, sdlState.windowTitle);
#endif

    sdlState.framebufferSize = (Size2D) { frame_width, frame_height };
}

void sdlSetFramebuffer(unsigned char* framebuffer)
{
    sdlState.pFramebuffer = framebuffer;
}

static int clamp(int v, int low, int high)          { return v > high ? high : (v < low ? low : v); }
static bool would_clamp(int v, int low, int high)   { return v < low || v > high; }
static int windowToFramebufferOffsetX()             { return sdlState.windowSize.width / 2 - sdlState.framebufferSize.width / 2; }
static int windowToFramebufferOffsetY()             { return sdlState.windowSize.height / 2 - sdlState.framebufferSize.height / 2; }
static int framebufferX(int windowX)                { return windowX - windowToFramebufferOffsetX(); }
static int framebufferY(int windowY)                { return sdlState.windowSize.height - windowY - windowToFramebufferOffsetY(); }

int sdlClampToFramebufferX(int windowX)             { return clamp(framebufferX(windowX), 1, sdlState.framebufferSize.width - 1); }
int sdlClampToFramebufferY(int windowY)             { return clamp(framebufferY(windowY), 1, sdlState.framebufferSize.height - 1); }

bool sdlInsideFramebuffer(int windowX, int windowY)
{
    // For now, window and framebuffer dimensions may differ, so convert
    // incoming window coords to framebuffer coords, including inverting y    
    return !would_clamp(framebufferX(windowX), 1, sdlState.framebufferSize.width - 1) 
        && !would_clamp(framebufferY(windowY), 1, sdlState.framebufferSize.height - 1);
}

#ifdef SDL_GL_FRAMEBUFFER
    int min(int x, int y) { return x < y ? x : y; }
    int nextPowerOfTwo(int val) { int power = 1; while (power < val) power *= 2; return power; }
#endif

void init_framebuffer_tex()
{
    #ifdef SDL_GL_FRAMEBUFFER
        // Create background image at size of window
        int winWidth = eventHandler.camera().windowSize().width,
            winHeight = eventHandler.camera().windowSize().height,
            bitsPerPixel = 32;

        // Don't exceed max GL texture size
        //
        // Also may need to set WASM heap via -s TOTAL_MEMORY
        //
        // Framebuffer sizes:
        // 5120x2880 57MB
        // 3840x2160 32MB
        // 2738x2048 22MB
        // 1920x1080 8MB
        // 1280x1024 5MB
        //
        GLint maxTextureSize = 256;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
        int imageWidth = min(winWidth, maxTextureSize),
            imageHeight = min(winHeight, maxTextureSize);
        printf("INFO: window size=%dx%d  image size=%dx%d\n", winWidth, winHeight, imageWidth, imageHeight);
    #endif

    // Create grey checkerboard surface with yellow border
    const int bitsPerPixel = 32;

    SDL_Surface* pSurface = SDL_CreateRGBSurface(0, sdlState.framebufferSize.width, sdlState.framebufferSize.height, bitsPerPixel, 0, 0, 0, 0);
    unsigned int* surfacePixels = (unsigned int*)pSurface->pixels;
    
    for (int y = 0; y < pSurface->h; ++y)
        for (int x = 0; x < pSurface->w; ++x)
        {
            const int i = x + y * pSurface->w;
            if (y == 0 || x == 0 || y == pSurface->h-1 || x == pSurface->w - 1)
                surfacePixels[i] = 0xff00ffff; // yellow
            else 
            {
                const int checkerSize = 100, halfChecker = checkerSize / 2,
                        yMod = y % checkerSize, xMod = x % checkerSize;
                if ((yMod < halfChecker && xMod < halfChecker) 
                    || (yMod >= halfChecker && xMod >= halfChecker))
                    surfacePixels[i] = 0xffc4c4c4; // light grey
                else
                    surfacePixels[i] = 0xff808080; // dark grey
            }
        }
    
    #ifdef SDL_GL_FRAMEBUFFER
        // OpenGLES requires power of 2 dimension textures, so create the smallest
        // power of 2 image that fits the background image, along with 1 texel border
        int texWidth = nextPowerOfTwo(bgImage->w + 2),
            texHeight = nextPowerOfTwo(bgImage->h + 2);
        bgImageTexture = SDL_CreateRGBSurface(0, texWidth, texHeight, bitsPerPixel, 0, 0, 0, 0);

        // Clear the image and copy the background image into it, centered
        unsigned int* texPixels = (unsigned int*)bgImageTexture->pixels;
        memset(texPixels, 0x0, bgImageTexture->w * bgImageTexture->h * bgImageTexture->format->BytesPerPixel);
        SDL_Rect destRect = {1, bgImageTexture->h - bgImage->h - 1, bgImage->w + 1, bgImageTexture->h - 1};
        SDL_BlitSurface(bgImage, NULL, bgImageTexture, &destRect);
        
        // Build GL texture
        //

        // Generate a GL texture object and bind it as current
        glGenTextures(1, &textureObj);
        glBindTexture(GL_TEXTURE_2D, textureObj);

        // Set the GL texture's wrapping and stretching properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Upload SDL image to GL texture
        GLint level = 0, border = 0;
        glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, 
                    bgImageTexture->w, bgImageTexture->h, 
                    border, GL_RGBA, GL_UNSIGNED_BYTE, bgImageTexture->pixels);

        // Check for errors
        GLenum glError = glGetError();
        if (glError != GL_NO_ERROR)
            printf("ERROR: Texture %d (%dx%d) not built, error code %d\n", textureObj, bgImageTexture->w, bgImageTexture->h, glError);
        else
            printf("OK: Texture %d (%dx%d) built.\n", textureObj, bgImageTexture->w, bgImageTexture->h);

        // Unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Update quad shader
        imageSize[0] = (GLfloat)bgImage->w + 2;
        imageSize[1] = (GLfloat)bgImage->h + 2;
        texSize[0] = (GLfloat)bgImageTexture->w;
        texSize[1] = (GLfloat)bgImageTexture->h;
        updateShader(eventHandler);
    #else
        // Create texture from surface
        sdlState.pFramebufferTex = SDL_CreateTextureFromSurface(sdlState.pRenderer, pSurface);
    #endif

    SDL_FreeSurface(pSurface);
}

void update_framebuffer_tex()
{
    if (sdlState.pFramebuffer)
    {
        #ifdef SDL_GL_FRAMEBUFFER
            printf("update OGL texture\n");
        #else        
            int pitch = sdlState.framebufferSize.width * 4;
            SDL_UpdateTexture(sdlState.pFramebufferTex, NULL, sdlState.pFramebuffer, pitch);
        #endif
    }
}

void free_framebuffer_tex()
{
    #ifdef SDL_GL_FRAMEBUFFER
        if (textureObj > 0)
        {
            glDeleteTextures(1, &textureObj);
            textureObj = 0;
        }
    #else
        if (sdlState.pFramebufferTex)
        {
            SDL_DestroyTexture(sdlState.pFramebufferTex);
            sdlState.pFramebufferTex = NULL;
        }
    #endif
}

Uint32 beginMaintainFPS()
{
    return SDL_GetTicks();
}

void endMaintainFPS(int fps, Uint32 startTicks)
{
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    Uint32 frameTicks = SDL_GetTicks() - startTicks;
    if( frameTicks < SCREEN_TICKS_PER_FRAME )
    {
        SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
    }    
}

void redraw()
{
    #ifdef SDL_GL_FRAMEBUFFER
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the background quad VBO with texture bound and image texture shader
        glBindTexture(GL_TEXTURE_2D, textureObj);
        glUseProgram(quadShaderProgram);
        glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
        glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindTexture(GL_TEXTURE_2D, 0);

        SDL_GL_SwapWindow(sdlState.pWindow);
    #else    
        SDL_SetRenderDrawColor(sdlState.pRenderer, 0, 0, 0, 0);
        SDL_RenderClear(sdlState.pRenderer);

        SDL_Rect destRect = (SDL_Rect) {
            .x = windowToFramebufferOffsetX(), 
            .y = windowToFramebufferOffsetY(), 
            sdlState.framebufferSize.width, 
            sdlState.framebufferSize.height };
        SDL_RenderCopy(sdlState.pRenderer, sdlState.pFramebufferTex, NULL, &destRect);
        SDL_RenderPresent(sdlState.pRenderer);
    #endif
}

void main_loop(void* main_loop_arg) 
{   
    Uint32 startTicks = beginMaintainFPS();

    sdlProcessEvents();

    // Run child main loop - let child process events and redraw its stuff
    child_main_loop();

    update_framebuffer_tex();
    redraw();

    endMaintainFPS(SCREEN_FPS, startTicks);
}

int main(int argc, char* argv[])
{
    // Initialize SDL window
    sdlInit(NULL);
    init_framebuffer_tex();

    // Run child main
    child_main(argc, argv);

    // Start the main loop
    void* main_loop_arg = NULL;
    #ifdef __EMSCRIPTEN__
        int fps = 0; // Set to 0 to use browser's requestAnimationFrame (recommended)
        int simulate_infinite_loop = 1;
        emscripten_set_main_loop_arg(main_loop, main_loop_arg, fps, simulate_infinite_loop);
    #else
        while(true) 
            main_loop(main_loop_arg);
    #endif

    free_framebuffer_tex();
    return 0;
}