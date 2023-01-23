#include <SDL.h>
#include <SDL_opengles2.h>
#include "camera2D.h"
#include "sdl_events.h"

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
    bool leftMouseButtonDown;
    bool middleMouseButtonDown;
    bool rightMouseButtonDown;
    Pixel2D leftMouseButtonDownCoord;
    Pixel2D mousePosition;

    // Finger input
    bool fingerDown;
    Vec2D fingerDownCoord;
    long long fingerDownId;

    // Pinch input
    bool pinch;

    // Keyboard input
    char keyDown;

} SDLEventState;

static SDLEventState sdlEvents = (SDLEventState)
{
    // Window
    .pWindow = NULL,
    .windowID = 0,
 
    // Mouse input
    .leftMouseButtonDown = false,
    .middleMouseButtonDown = false,
    .rightMouseButtonDown = false,
    .leftMouseButtonDownCoord = {0, 0},
    .mousePosition = {0, 0},

    // Finger input
    .fingerDown = false,
    .fingerDownCoord = {0.0, 0.0},
    .fingerDownId = 0,

    // Pinch input
    .pinch = false,

    // Keyboard input
    .keyDown = 0
};

bool* sdlLeftMouse = &sdlEvents.leftMouseButtonDown;
bool* sdlMiddleMouse = &sdlEvents.middleMouseButtonDown;
bool* sdlRightMouse = &sdlEvents.rightMouseButtonDown;
Pixel2D* sdlMousePos = &sdlEvents.mousePosition;
char* sdlKeyDown = &sdlEvents.keyDown;

void windowResizeEvent(Size2D winSize)
{
    glViewport(0, 0, winSize.width, winSize.height);
    cam2DSetWindowSize(winSize);
}

void sdlEventsInit(const char* windowTitle)
{
    // Create SDL window
    sdlEvents.pWindow = 
        SDL_CreateWindow(windowTitle, 
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         cam2DWindowSize().width, cam2DWindowSize().height, 
                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE| SDL_WINDOW_SHOWN);
    sdlEvents.windowID = SDL_GetWindowID(sdlEvents.pWindow);

    // Create OpenGLES 2 context on SDL window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GLContext glc = SDL_GL_CreateContext(sdlEvents.pWindow);

    // Set clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Initialize viewport
    windowResizeEvent(cam2DWindowSize());
}

void sdlEventsSwapWindow()
{
    SDL_GL_SwapWindow(sdlEvents.pWindow);
}

void zoomEventMouse(bool mouseWheelDown)
{                
    Vec2D preZoomWorld;
    cam2DWindowToWorld(sdlEvents.mousePosition, &preZoomWorld);

    // Zoom by scaling up/down in 0.05 increments 
    float zoomDelta = mouseWheelDown ? -cMouseWheelZoomDelta : cMouseWheelZoomDelta;
    cam2DSetZoomDelta(zoomDelta);

    // Zoom to point: Keep the world coords under sdlEvents.mouse position the same before and after the zoom
    Vec2D postZoomWorld;
    cam2DWindowToWorld(sdlEvents.mousePosition, &postZoomWorld);
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

    // Zoom to point: Keep the world coords under sdlEvents.pinch position the same before and after the zoom
    Vec2D postZoomWorld;
    cam2DNormWindowToWorld(pinchCoord, &postZoomWorld);
    Vec2D deltaWorld = { postZoomWorld.x - preZoomWorld.x, postZoomWorld.y - preZoomWorld.y };
    cam2DSetPanDelta (deltaWorld);
}

void panEventMouse(Pixel2D mousePos)
{ 
    Pixel2D delta = { cam2DWindowSize().width / 2 + (mousePos.x - sdlEvents.leftMouseButtonDownCoord.x),
                      cam2DWindowSize().height / 2 + (mousePos.y - sdlEvents.leftMouseButtonDownCoord.y) };

    Vec2D device;
    cam2DWindowToDevice(delta, &device);

    Vec2D pan = { cam2DBasePan().x + device.x / cam2DZoom(), 
                  cam2DBasePan().y + device.y / cam2DZoom() / cam2DAspect() };
    cam2DSetPan(pan);
}

void panEventFinger(Vec2D fingerCoord)
{ 
    Vec2D delta = { 0.5f + (fingerCoord.x - sdlEvents.fingerDownCoord.x),
                    0.5f + (fingerCoord.y - sdlEvents.fingerDownCoord.y) };

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
                if (event.window.windowID == sdlEvents.windowID
                    && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    Size2D winSize = { event.window.data1, event.window.data2 };
                    windowResizeEvent(winSize);
                }
                break;
            }

            case SDL_KEYDOWN:
            {
                const char* keyName = SDL_GetKeyName(event.key.keysym.sym);
                if (strlen(keyName) == 1) {
                    sdlEvents.keyDown = keyName[0];
                    printf("key down %c\n",sdlEvents.keyDown);
                }
                break;
            }

            case SDL_KEYUP:
            {
                const char* keyName = SDL_GetKeyName(event.key.keysym.sym);
                if (strlen(keyName) == 1)
                    if (sdlEvents.keyDown == keyName[0]) {
                        sdlEvents.keyDown = 0;
                        printf("key up %c\n",keyName[0]);
                    }
                break;
            }

            case SDL_MOUSEWHEEL: 
            {
                // SDL_MOUSEWHEEL regression? 
                // m->y no longer reliable (often y is 0 when sdlEvents.mouse wheel is spun up or down), use m->preciseY instead
                SDL_MouseWheelEvent *m = (SDL_MouseWheelEvent*)&event;
            	bool mouseWheelDown = (m->preciseY < 0.0);
            	zoomEventMouse(mouseWheelDown);
            	break;
            }
            
            case SDL_MOUSEMOTION: 
            {
                SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent*)&event;
                sdlEvents.mousePosition = (Pixel2D) { (int)m->x, (int)m->y };
                if (sdlEvents.leftMouseButtonDown && !sdlEvents.fingerDown && !sdlEvents.pinch)
                    panEventMouse(sdlEvents.mousePosition);
                break;
            }

            case SDL_MOUSEBUTTONDOWN: 
            {
                if (!sdlEvents.fingerDown && !sdlEvents.pinch)
                {
                    SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&event;
                    switch (m->button)                   
                    {
                        case SDL_BUTTON_LEFT:
                            sdlEvents.leftMouseButtonDown = true;
                            sdlEvents.leftMouseButtonDownCoord = (Pixel2D) { (int)m->x, (int)m->y };
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
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&event;
                switch (m->button)                   
                {
                    case SDL_BUTTON_LEFT:   sdlEvents.leftMouseButtonDown = false;   break;
                    case SDL_BUTTON_MIDDLE: sdlEvents.middleMouseButtonDown = false; break;
                    case SDL_BUTTON_RIGHT:  sdlEvents.rightMouseButtonDown = false;  break;
                }
                break;
            }

            case SDL_FINGERMOTION:
                if (sdlEvents.fingerDown)
                {
                    SDL_TouchFingerEvent *m = (SDL_TouchFingerEvent*)&event;

                    // Finger down and finger moving must match
                    if (m->fingerId == sdlEvents.fingerDownId)
                    {
                        Vec2D fingerCoord = (Vec2D) {m->x, m->y};
                        panEventFinger(fingerCoord);
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
                        SDL_TouchFingerEvent *m = (SDL_TouchFingerEvent*)&event;
                        sdlEvents.fingerDown = true;
                        sdlEvents.fingerDownCoord = (Vec2D) { m->x, m->y };
                        sdlEvents.fingerDownId = m->fingerId;
                        cam2DSetBasePan();
                    }
                }
                break;

            case SDL_MULTIGESTURE:
            {
                SDL_MultiGestureEvent *m = (SDL_MultiGestureEvent*)&event;
                if (m->numFingers == 2 && fabs(m->dDist) >= cPinchZoomThreshold)
                {
                    sdlEvents.pinch = true;
                    sdlEvents.fingerDown = false;
                    sdlEvents.leftMouseButtonDown = false;
                    Vec2D pinchCoord = (Vec2D) { m->x, m->y };
                    zoomEventPinch(m->dDist, pinchCoord);
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