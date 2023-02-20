#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "camera2D.h"
#include "sdl_events.h"

typedef struct
{
    // Window
    SDL_Window* pWindow;
    Uint32 windowID;
    SDL_Renderer* pRenderer;

    // Mouse input
    bool leftMouseButtonDown;
    bool middleMouseButtonDown;
    bool rightMouseButtonDown;
    Pixel2D leftMouseButtonDownCoord;
    Pixel2D mousePosition;
    bool mouseInsideFramebuffer;

    // Finger input
    bool fingerDown;
    Vec2D fingerDownCoord;
    long long fingerDownId;

    // Pinch input
    bool pinch;

} SDLEventState;

static SDLEventState sdlEvents = (SDLEventState)
{
    // Window
    .pWindow = NULL,
    .windowID = 0,
    .pRenderer = NULL,

    // Mouse input
    .leftMouseButtonDown = false,
    .middleMouseButtonDown = false,
    .rightMouseButtonDown = false,
    .leftMouseButtonDownCoord = {0, 0},
    .mousePosition = {0, 0},
    .mouseInsideFramebuffer = false,

    // Finger input
    .fingerDown = false,
    .fingerDownCoord = {0.0, 0.0},
    .fingerDownId = 0,

    // Pinch input
    .pinch = false,
};

void sdlEventsInit(const char *windowTitle)
{
    // Create SDL window
    sdlEvents.pWindow =
        SDL_CreateWindow(windowTitle,
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         cam2DWindowSize().width, cam2DWindowSize().height,
                         SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    sdlEvents.windowID = SDL_GetWindowID(sdlEvents.pWindow);
    sdlEvents.pRenderer = SDL_CreateRenderer(sdlEvents.pWindow, -1, 0);

    // Initialize viewport
    cam2DSetWindowSize(cam2DWindowSize());
}

void sdlEventsPresent()
{
    SDL_RenderPresent(sdlRenderer());
}

void sdlEventsProcess()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_WINDOWEVENT:
        {
            if (event.window.windowID == sdlEvents.windowID && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                Size2D winSize = {event.window.data1, event.window.data2};
                cam2DSetWindowSize(winSize);
            }
            break;
        }

        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    exit(0);
                }
                break;
                
                default:
                {
                }
                break;
            }
            break;
        }

        case SDL_MOUSEWHEEL:
        {
            SDL_MouseWheelEvent *m = (SDL_MouseWheelEvent *)&event;
            bool mouseWheelDown = (m->preciseY < 0.0);
            cam2DZoomEventMouse(mouseWheelDown, sdlEvents.mousePosition);
        }
        break;

        case SDL_MOUSEMOTION:
        {
            SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent *)&event;
            sdlEvents.mousePosition = (Pixel2D){(int)m->x, (int)m->y};
            if (sdlEvents.leftMouseButtonDown && !sdlEvents.fingerDown && !sdlEvents.pinch)
                cam2DPanEventMouse(sdlEvents.mousePosition, sdlEvents.leftMouseButtonDownCoord);
        }
        break;

        case SDL_MOUSEBUTTONDOWN:
        {
            if (!sdlEvents.fingerDown && !sdlEvents.pinch)
            {
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent *)&event;               

                switch (m->button)
                {
                case SDL_BUTTON_LEFT:
                    sdlEvents.leftMouseButtonDown = true;
                    sdlEvents.leftMouseButtonDownCoord = (Pixel2D){(int)m->x, (int)m->y};
                    cam2DSetBasePan();
                    break;
                case SDL_BUTTON_MIDDLE:
                    sdlEvents.middleMouseButtonDown = true;
                    break;
                case SDL_BUTTON_RIGHT:
                    sdlEvents.rightMouseButtonDown = true;
                    break;
                }
            }
            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent *)&event;

            switch (m->button)
            {
            case SDL_BUTTON_LEFT:
                sdlEvents.leftMouseButtonDown = false;
                break;
            case SDL_BUTTON_MIDDLE:
                sdlEvents.middleMouseButtonDown = false;
                break;
            case SDL_BUTTON_RIGHT:
                sdlEvents.rightMouseButtonDown = false;
                break;
            }
        }
        break;

        case SDL_FINGERMOTION:
            if (sdlEvents.fingerDown)
            {
                SDL_TouchFingerEvent *m = (SDL_TouchFingerEvent *)&event;

                // Finger down and finger moving must match
                if (m->fingerId == sdlEvents.fingerDownId)
                {
                    Vec2D fingerCoord = (Vec2D){m->x, m->y};
                    cam2DPanEventFinger(fingerCoord, sdlEvents.fingerDownCoord);
                }
            }
            break;

        case SDL_FINGERDOWN:
            if (!sdlEvents.pinch)
            {
                // Finger already down means multiple fingers, which is handled by multigesture event
                if (sdlEvents.fingerDown)
                    sdlEvents.fingerDown = false;
                else
                {
                    SDL_TouchFingerEvent *m = (SDL_TouchFingerEvent *)&event;
                    sdlEvents.fingerDown = true;
                    sdlEvents.fingerDownCoord = (Vec2D){m->x, m->y};
                    sdlEvents.fingerDownId = m->fingerId;
                    cam2DSetBasePan();
                }
            }
            break;

        case SDL_MULTIGESTURE:
        {
            static const float cPinchZoomThreshold = 0.001;
            SDL_MultiGestureEvent *m = (SDL_MultiGestureEvent *)&event;
            if (m->numFingers == 2 && fabs(m->dDist) >= cPinchZoomThreshold)
            {
                sdlEvents.pinch = true;
                sdlEvents.fingerDown = false;
                sdlEvents.leftMouseButtonDown = false;
                Vec2D pinchCoord = (Vec2D){m->x, m->y};
                cam2DZoomEventPinch(m->dDist, pinchCoord);
            }
            break;
        }

        case SDL_FINGERUP:
            sdlEvents.fingerDown = false;
            sdlEvents.pinch = false;
            break;
        }
    }
}

int sdlMousePosX()
{
    //SDL_PumpEvents();
    int x, y;
    SDL_GetMouseState(&x, &y);
    return x;
}
int sdlMousePosY()
{
    //SDL_PumpEvents();
    int x, y;
    SDL_GetMouseState(&x, &y);
    return y;
}

unsigned char sdlMouseButtonState()
{
    //SDL_PumpEvents();
    int x, y;
    return SDL_GetMouseState(&x, &y);    
}

int sdlPeepEvents()
{
    //SDL_PumpEvents();
    SDL_Event event;
    int count = SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
    return count;
}

Uint8* sdlGetKeyboardState()
{
    //SDL_PumpEvents();
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    return (unsigned char*)keys;
}

SDL_Renderer* sdlRenderer()
{
    return sdlEvents.pRenderer;
}

Size2D sdlGetFramebufferSize()
{
    Size2D nullSize;
    return nullSize;
}