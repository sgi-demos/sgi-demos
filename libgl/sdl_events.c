//#include <algorithm>
#include <SDL.h>
#include <SDL_opengles2.h>
#include "sdl_events.h"
#include "camera2D.h"

// #define SDL_EVENTS_DEBUG
#define false 0
#define true 1

static const float cMouseWheelZoomDelta = 0.05;
static const float cPinchZoomThreshold = 0.001, cPinchScale = 8.0;

typedef struct
{
    // Window
    SDL_Window* pWindow;
    Uint32 windowID;

    // Mouse input
    bool mouseButtonDown;
    int mouseButtonDownX, mouseButtonDownY;
    int mousePositionX, mousePositionY;

    // Finger input
    bool fingerDown;
    float fingerDownX, fingerDownY;
    long long fingerDownId;

    // Pinch input
    bool pinch;

} SDLEventHandler;

static SDLEventHandler events = (SDLEventHandler)
{
    // Window
    .pWindow = NULL,
    .windowID = 0,
 
    // Mouse input
    .mouseButtonDown = false,
    .mouseButtonDownX = 0, .mouseButtonDownY = 0,
    .mousePositionX = 0, .mousePositionY = 0,

    // Finger input
    .fingerDown = false,
    .fingerDownX = 0.0, .fingerDownY = 0.0,
    .fingerDownId = 0,

    // Pinch input
    .pinch = false
};

void windowResizeEvent(int width, int height)
{
    glViewport(0, 0, width, height);
    cam2DSetWindowSize(width, height);
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
    windowResizeEvent(cam2DWindowSize().width, cam2DWindowSize().height);
}

void sdlEventsSwapWindow()
{
    SDL_GL_SwapWindow(events.pWindow);
}

void zoomEventMouse(bool mouseWheelDown)
{                
    float preZoomWorldX, preZoomWorldY;
    cam2DWindowToWorld(events.mousePositionX, events.mousePositionY, &preZoomWorldX, &preZoomWorldY);

    // Zoom by scaling up/down in 0.05 increments 
    float zoomDelta = mouseWheelDown ? -cMouseWheelZoomDelta : cMouseWheelZoomDelta;
    cam2DSetZoomDelta(zoomDelta);

    // Zoom to point: Keep the world coords under events.mouse position the same before and after the zoom
    float postZoomWorldX, postZoomWorldY;
    cam2DWindowToWorld(events.mousePositionX, events.mousePositionY, &postZoomWorldX, &postZoomWorldY);
    Vec2D deltaWorld = { postZoomWorldX - preZoomWorldX, postZoomWorldY - preZoomWorldY };
    cam2DSetPanDelta (deltaWorld);
}

void zoomEventPinch (float pinchDist, float pinchX, float pinchY)
{
    float preZoomWorldX, preZoomWorldY;
    cam2DWindowToWorld(pinchX, pinchY, &preZoomWorldX, &preZoomWorldY);

    // Zoom in/out by positive/negative events.pinch distance
    float zoomDelta = pinchDist * cPinchScale;
    cam2DSetZoomDelta(zoomDelta);

    // Zoom to point: Keep the world coords under events.pinch position the same before and after the zoom
    float postZoomWorldX, postZoomWorldY;
    cam2DWindowToWorld(pinchX, pinchY, &postZoomWorldX, &postZoomWorldY);
    Vec2D deltaWorld = { postZoomWorldX - preZoomWorldX, postZoomWorldY - preZoomWorldY };
    cam2DSetPanDelta (deltaWorld);
}

void panEventMouse(int x, int y)
{ 
     int deltaX = cam2DWindowSize().width / 2 + (x - events.mouseButtonDownX),
         deltaY = cam2DWindowSize().height / 2 + (y - events.mouseButtonDownY);

    float deviceX, deviceY;
    cam2DWindowToDevice(deltaX,  deltaY, &deviceX, &deviceY);

    Vec2D pan = { cam2DBasePan().x + deviceX / cam2DZoom(), 
                  cam2DBasePan().y + deviceY / cam2DZoom() / cam2DAspect() };
    cam2DSetPan(pan);
}

void panEventFinger(float x, float y)
{ 
    float deltaX = 0.5f + (x - events.fingerDownX),
          deltaY = 0.5f + (y - events.fingerDownY);

    float deviceX, deviceY;
    cam2DWindowToDevice(deltaX,  deltaY, &deviceX, &deviceY);

    Vec2D pan = { cam2DBasePan().x + deviceX / cam2DZoom(), 
                  cam2DBasePan().y + deviceY / cam2DZoom() / cam2DAspect() };
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
                    int width = event.window.data1, height = event.window.data2;
                    windowResizeEvent(width, height);
                }
                break;
            }

            case SDL_MOUSEWHEEL: 
            {
                // SDL_MOUSEWHEEL regression? 
                // m->y no longer reliable (often y is 0 when events.mouse wheel is spun up or down), use m->preciseY instead
                SDL_MouseWheelEvent *m = (SDL_MouseWheelEvent*)&event;
            	#ifdef EVENTS_DEBUG
                	printf ("SDL_MOUSEWHEEL= x,y=%d,%d preciseX,preciseY=%f,%f\n", m->x, m->y, m->preciseX, m->preciseY);
            	#endif
            	bool mouseWheelDown = (m->preciseY < 0.0);
            	zoomEventMouse(mouseWheelDown);
            	break;
            }
            
            case SDL_MOUSEMOTION: 
            {
                SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent*)&event;
                events.mousePositionX = m->x;
                events.mousePositionY = m->y;
                if (events.mouseButtonDown && !events.fingerDown && !events.pinch)
                    panEventMouse(events.mousePositionX, events.mousePositionY);
                break;
            }

            case SDL_MOUSEBUTTONDOWN: 
            {
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&event;
                if (m->button == SDL_BUTTON_LEFT && !events.fingerDown && !events.pinch)
                {
                    events.mouseButtonDown = true;
                    events.mouseButtonDownX = m->x;
                    events.mouseButtonDownY = m->y;
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
                        panEventFinger(m->x, m->y);
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
                        events.fingerDownX = m->x;
                        events.fingerDownY = m->y;
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
                    zoomEventPinch(m->dDist, m->x, m->y);
                }
                break;
            }

            case SDL_FINGERUP:
                events.fingerDown = false;
                events.pinch = false;
                break;
        }

        #ifdef SDL_EVENTS_DEBUG
            printf ("event=%d events.mousePos=%d,%d events.mouseButtonDown=%d events.fingerDown=%d events.pinch=%d aspect=%f window=%dx%d\n", 
                    event.type, events.mousePositionX, events.mousePositionY, events.mouseButtonDown, events.fingerDown, events.pinch, 
                    cam2DAspect(), cam2DWindowSize().width, cam2DWindowSize().height);      
            printf ("    zoom=%f pan=%f,%f\n", cam2DZoom(), cam2Dpan().x, cam2Dpan().x);
        #endif
    }
}