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

const int SCREEN_FPS = 60;
//#define SDL_GL_FRAMEBUFFER

typedef struct
{
    // Window
    char windowTitle[128];
    SDL_Window* pWindow;
    Uint32 windowID;
    Size2D windowSize;

    // Framebuffer
    Size2D framebufferSize;         // Framebuffer size may differ from window size
    unsigned char* pFramebuffer;    // IRIS GL's framebuffer
    SDL_Texture * pFramebufferTex;  // SDL's texture for displaying the framebuffer

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

void build_framebuffer_tex()
{
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
        printf("init OGL texture\n");
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
        printf("free OGL texture\n");
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
        printf("redraw OGL texture\n");
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        update_framebuffer_tex();

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

    #ifdef MAIN_LOOP_DEBUG
        static int main_loop_count = 0;
        if (main_loop_count % SCREEN_FPS == 0)
            printf("main_loop BEGIN %d\n",main_loop_count);
    #endif

    #ifdef MAIN_LOOP_DEBUG
    if (main_loop_count % SCREEN_FPS == 0)
        printf("main_loop END %d\n",main_loop_count);
    ++main_loop_count;
    #endif
}

int main(int argc, char* argv[])
{
    // Initialize SDL window
    sdlInit(NULL);
    build_framebuffer_tex();

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