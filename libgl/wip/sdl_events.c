#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "sdl_events.h"

typedef struct
{
    // Window
    SDL_Window* pWindow;
    Uint32 windowID;
    Size2D winSize;
    SDL_Renderer* pRenderer;

    // Mouse input
    bool leftMouseButtonDown;
    bool middleMouseButtonDown;
    bool rightMouseButtonDown;
    Pixel2D mousePosition;
} SDLState;

static SDLState sdlState = (SDLState)
{
    // Window
    .pWindow = NULL,
    .windowID = 0,
    .winSize = {800, 480},
    .pRenderer = NULL,

    // Mouse input
    .leftMouseButtonDown = false,
    .middleMouseButtonDown = false,
    .rightMouseButtonDown = false,
    .mousePosition = {0, 0},
};

void sdlInit(const char *windowTitle)
{
    // Create SDL window
    sdlState.pWindow =
        SDL_CreateWindow(windowTitle,
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         sdlState.winSize.width, sdlState.winSize.height,
                         SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    sdlState.windowID = SDL_GetWindowID(sdlState.pWindow);
    sdlState.pRenderer = SDL_CreateRenderer(sdlState.pWindow, -1, 0);
}

static void exitApp()
{
    #ifdef __EMSCRIPTEN__
        // Go to previous page, or if none, to demo home page
        const char *exit_js =
            "if (document.referrer) {                                   "
            "     window.history.back();                                "
            "}                                                          "
            "else {                                                     "
            "    window.location.href = 'https://sgi-demos.github.io';  "
            "}                                                          ";
        emscripten_run_script(exit_js);
    #else
        exit(0);
    #endif
}

void sdlProcessEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_WINDOWEVENT:
            {
                if (event.window.windowID == sdlState.windowID && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    sdlState.winSize = (Size2D){event.window.data1, event.window.data2};
                }
            }
            break;

            case SDL_QUIT:
                exitApp();
            break;

            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: 
                        exitApp(); 
                    break;
                    
                    default:
                    break;
                }
            }
            break;

            case SDL_MOUSEMOTION:
            {
                SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent *)&event;
                sdlState.mousePosition = (Pixel2D){(int)m->x, (int)m->y};
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent *)&event;               
                switch (m->button)
                {
                    case SDL_BUTTON_LEFT:   sdlState.leftMouseButtonDown = true;    break;
                    case SDL_BUTTON_MIDDLE: sdlState.middleMouseButtonDown = true;  break;
                    case SDL_BUTTON_RIGHT:  sdlState.rightMouseButtonDown = true;   break;
                }
            }
            break;

            case SDL_MOUSEBUTTONUP:
            {
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent *)&event;
                switch (m->button)
                {
                    case SDL_BUTTON_LEFT:   sdlState.leftMouseButtonDown = false;   break;
                    case SDL_BUTTON_MIDDLE: sdlState.middleMouseButtonDown = false; break;
                    case SDL_BUTTON_RIGHT:  sdlState.rightMouseButtonDown = false;  break;
                }
            }
            break;
        }
    }
}

void sdlPresent()
{
    SDL_RenderPresent(sdlState.pRenderer);
}

SDL_Renderer* sdlRenderer()
{
    return sdlState.pRenderer;
}

Size2D sdlWindowSize()
{
    return sdlState.winSize;
}

Vec2D sdlViewport()   
{ 
    return (Vec2D) { .x = (float)sdlState.winSize.width, .y = (float)sdlState.winSize.height };
}

Size2D sdlFramebufferSize()
{
    return sdlState.winSize;
}

unsigned char* sdlFramebuffer()
{
    return NULL;
}

int sdlWindowToFramebufferOffsetX()
{
    return 0;
}

int sdlWindowToFramebufferOffsetY()
{
    return 0;
}