#include <SDL.h>
#include <SDL_opengles2.h>
#include "sdl_events.h"
#include "camera2D.h"

#define false 0
#define true 1

static const float cMouseWheelZoomDelta = 0.05;
static const float cPinchZoomThreshold = 0.001, 
                   cPinchScale = 8.0;

typedef struct
{
    // Window
    SDL_Window* pWindow;
    Uint32 windowID;

    // Mouse input
    bool mouseButtonDown;
    Pixel2D mouseButtonDownCoord;
    Pixel2D mousePosition;

    // Finger input
    bool fingerDown;
    Vec2D fingerDownCoord;
    long long fingerDownId;

    // Pinch input
    bool pinch;

} SDLEventState;

static SDLEventState events = (SDLEventState)
{
    // Window
    .pWindow = NULL,
    .windowID = 0,
 
    // Mouse input
    .mouseButtonDown = false,
    .mouseButtonDownCoord = {0, 0},
    .mousePosition = {0, 0},

    // Finger input
    .fingerDown = false,
    .fingerDownCoord = {0.0, 0.0},
    .fingerDownId = 0,

    // Pinch input
    .pinch = false
};

void windowResizeEvent(Size2D winSize)
{
    glViewport(0, 0, winSize.width, winSize.height);
    cam2DSetWindowSize(winSize);
}

void sdlEventsInit(const char* windowTitle)
{
    // Create SDL window
    events.pWindow = 
        SDL_CreateWindow(windowTitle, 
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         cam2DWindowSize().width, cam2DWindowSize().height, 
                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE| SDL_WINDOW_SHOWN);
    events.windowID = SDL_GetWindowID(events.pWindow);

    // Create OpenGLES 2 context on SDL window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GLContext glc = SDL_GL_CreateContext(events.pWindow);

    // Set clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Initialize viewport
    windowResizeEvent(cam2DWindowSize());
}

void sdlEventsSwapWindow()
{
    SDL_GL_SwapWindow(events.pWindow);
}

void zoomEventMouse(bool mouseWheelDown)
{                
    Vec2D preZoomWorld;
    cam2DWindowToWorld(events.mousePosition, &preZoomWorld);

    // Zoom by scaling up/down in 0.05 increments 
    float zoomDelta = mouseWheelDown ? -cMouseWheelZoomDelta : cMouseWheelZoomDelta;
    cam2DSetZoomDelta(zoomDelta);

    // Zoom to point: Keep the world coords under events.mouse position the same before and after the zoom
    Vec2D postZoomWorld;
    cam2DWindowToWorld(events.mousePosition, &postZoomWorld);
    Vec2D deltaWorld = { postZoomWorld.x - preZoomWorld.x, postZoomWorld.y - preZoomWorld.y };
    cam2DSetPanDelta (deltaWorld);
}

void zoomEventPinch (float pinchDist, Vec2D pinchCoord)
{
    Vec2D preZoomWorld;
    cam2DNormWindowToWorld(pinchCoord, &preZoomWorld);

    // Zoom in/out by positive/negative pinch distance
    float zoomDelta = pinchDist * cPinchScale;
    cam2DSetZoomDelta(zoomDelta);

    // Zoom to point: Keep the world coords under events.pinch position the same before and after the zoom
    Vec2D postZoomWorld;
    cam2DNormWindowToWorld(pinchCoord, &postZoomWorld);
    Vec2D deltaWorld = { postZoomWorld.x - preZoomWorld.x, postZoomWorld.y - preZoomWorld.y };
    cam2DSetPanDelta (deltaWorld);
}

void panEventMouse(Pixel2D mousePos)
{ 
    Pixel2D delta = { cam2DWindowSize().width / 2 + (mousePos.x - events.mouseButtonDownCoord.x),
                      cam2DWindowSize().height / 2 + (mousePos.y - events.mouseButtonDownCoord.y) };

    Vec2D device;
    cam2DWindowToDevice(delta, &device);

    Vec2D pan = { cam2DBasePan().x + device.x / cam2DZoom(), 
                  cam2DBasePan().y + device.y / cam2DZoom() / cam2DAspect() };
    cam2DSetPan(pan);
}

void panEventFinger(Vec2D fingerCoord)
{ 
    Vec2D delta = { 0.5f + (fingerCoord.x - events.fingerDownCoord.x),
                    0.5f + (fingerCoord.y - events.fingerDownCoord.y) };

    Vec2D device;
    cam2DNormWindowToDevice(delta, &device);

    Vec2D pan = { cam2DBasePan().x + device.x / cam2DZoom(), 
                  cam2DBasePan().y + device.y / cam2DZoom() / cam2DAspect() };
    cam2DSetPan(pan);
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
                if (event.window.windowID == events.windowID
                    && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    Size2D winSize = { event.window.data1, event.window.data2 };
                    windowResizeEvent(winSize);
                }
                break;
            }

            case SDL_MOUSEWHEEL: 
            {
                // SDL_MOUSEWHEEL regression? 
                // m->y no longer reliable (often y is 0 when events.mouse wheel is spun up or down), use m->preciseY instead
                SDL_MouseWheelEvent *m = (SDL_MouseWheelEvent*)&event;
            	bool mouseWheelDown = (m->preciseY < 0.0);
            	zoomEventMouse(mouseWheelDown);
            	break;
            }
            
            case SDL_MOUSEMOTION: 
            {
                SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent*)&event;
                events.mousePosition = (Pixel2D) { (int)m->x, (int)m->y };
                if (events.mouseButtonDown && !events.fingerDown && !events.pinch)
                    panEventMouse(events.mousePosition);
                break;
            }

            case SDL_MOUSEBUTTONDOWN: 
            {
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&event;
                if (m->button == SDL_BUTTON_LEFT && !events.fingerDown && !events.pinch)
                {
                    events.mouseButtonDown = true;
                    events.mouseButtonDownCoord = 
                        (Pixel2D) { (int)m->x, (int)m->y };
                    cam2DSetBasePan();
                }
                break;
            }

            case SDL_MOUSEBUTTONUP: 
            {
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&event;
                if (m->button == SDL_BUTTON_LEFT)
                    events.mouseButtonDown = false;
                break;
            }

            case SDL_FINGERMOTION:
                if (events.fingerDown)
                {
                    SDL_TouchFingerEvent *m = (SDL_TouchFingerEvent*)&event;

                    // Finger down and finger moving must match
                    if (m->fingerId == events.fingerDownId)
                    {
                        Vec2D fingerCoord = (Vec2D) {m->x, m->y};
                        panEventFinger(fingerCoord);
                    }
                }
                break;

            case SDL_FINGERDOWN:
                if (!events.pinch)
                {
                    // Finger already down means multiple fingers, which is handled by multigesture event
                    if (events.fingerDown)
                        events.fingerDown = false;
                    else
                    {
                        SDL_TouchFingerEvent *m = (SDL_TouchFingerEvent*)&event;
                        events.fingerDown = true;
                        events.fingerDownCoord = (Vec2D) { m->x, m->y };
                        events.fingerDownId = m->fingerId;
                        cam2DSetBasePan();
                    }
                }
                break;

            case SDL_MULTIGESTURE:
            {
                SDL_MultiGestureEvent *m = (SDL_MultiGestureEvent*)&event;
                if (m->numFingers == 2 && fabs(m->dDist) >= cPinchZoomThreshold)
                {
                    events.pinch = true;
                    events.fingerDown = false;
                    events.mouseButtonDown = false;
                    Vec2D pinchCoord = (Vec2D) { m->x, m->y };
                    zoomEventPinch(m->dDist, pinchCoord);
                }
                break;
            }

            case SDL_FINGERUP:
                events.fingerDown = false;
                events.pinch = false;
                break;
        }
    }
}