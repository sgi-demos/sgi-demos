#include <SDL.h>
#include <SDL_opengles2.h>
#include <gl.h>
#include <device.h>
#include "camera2D.h"
#include "sdl_events.h"
#include "events.h"

typedef struct event {
    int32_t device;
    int16_t val;
    // union here for other events like keys
} event;

static uint32_t tied_valuators[2048][2];
static uint32_t device_queued[2048];

#define INPUT_QUEUE_SIZE 128
static event input_queue[INPUT_QUEUE_SIZE];
// The next item that needs to be read:
static int input_queue_head = 0;
// The number of items in the queue (tail = (head + length) % len):
static int input_queue_length = 0;

// Framebuffer size may not be the same as window size
Size2D frame_size;

static void enqueue_event(event *e)
{
    if (input_queue_length == INPUT_QUEUE_SIZE) {
        printf("Input queue overflow.");
    } else {
        int tail = (input_queue_head + input_queue_length) % INPUT_QUEUE_SIZE;
        input_queue[tail] = *e;
        input_queue_length++;
    }
}

// TBD - for desktop, have an escape key; for mobile, probably will have a window title bar with X to close window
//       which user can tap, and this can enqueue an ESCKEY event here
static void emulateEscapeWithTapClose()
{
    // // Only Home button for now, which is mapped to ESC.
    // int home_button;
    // event ev;
    
    // // libawesome will queue up two transitions per frame, so read the button
    // // twice to get those.
    // for (int i = 0; i < 2; i++) {
    //     home_button = awesome_get_home_button();
    //     if(home_button != home_button_previous) {
    //         if(device_queued[ESCKEY]) {
    //         ev.device = ESCKEY;
    //         ev.val = home_button;
    //         enqueue_event(&ev);
    //         }
    //         home_button_previous = home_button;
    //     }
    // }
}

// TBD - For mobile, translate touch events into mouse events, and push those mouse events onto the queue
//       NOTE: may not need this, as touch events are already translated into mouse events by SDL
static void emulateMouseWithTouch()
{
    // int x, y;
    // float z;

    // TouchscreenEvent e;
    // event ev;
    // int drained = 0;
    // while((e = touchscreen_read(&x, &y, &z)) != TOUCHSCREEN_IDLE) {
	// drained ++;
	// switch(e) {
	//     case TOUCHSCREEN_START:
	// 	// N.B. The devices is rotated 180 degrees from it's
	// 	// "natural," originally-developed orientation
	// 	mousex = 800 - 1 - x;
	// 	mousey = y; // GL valuator MOUSEY is 0 at bottom
	// 	if(device_queued[LEFTMOUSE]) {
	// 	    ev.device = LEFTMOUSE;
	// 	    ev.val = 1;
	// 	    enqueue_event(&ev);
	// 	    for(int j = 0; j < 2; j++) {
	// 		if(tied_valuators[LEFTMOUSE][j]) {
	// 		    ev.device = tied_valuators[LEFTMOUSE][j];
	// 		    ev.val = events_get_valuator(tied_valuators[LEFTMOUSE][j]);
	// 		    enqueue_event(&ev);
	// 		}
	// 	    }
	// 	}
	// 	break;
	//     case TOUCHSCREEN_DRAG:
	//     	// XXX device is rotated 180 degrees
	// 	mousex = 800 - 1 - x;
	// 	mousey = y; // GL valuator MOUSEY is 0 at bottom
	// 	break;
	//     case TOUCHSCREEN_STOP:
	// 	if(device_queued[LEFTMOUSE]) {
	// 	    ev.device = LEFTMOUSE;
	// 	    ev.val = 0;
	// 	    enqueue_event(&ev);
	// 	    for(int j = 0; j < 2; j++) {
	// 		if(tied_valuators[LEFTMOUSE][j]) {
	// 		    ev.device = tied_valuators[LEFTMOUSE][j];
	// 		    ev.val = events_get_valuator(tied_valuators[LEFTMOUSE][j]);
	// 		    enqueue_event(&ev);
	// 		}
	// 	    }
	// 	}
	// 	break;
	//     case TOUCHSCREEN_IDLE:
	//     default:
	// 	break;
	// }
    // }
}

// static float theta_x_smoothed, theta_y_smoothed;
// static const float decay = .95;

static bool isDial(int32_t device)
{
    // Safe! IrisGL API is never changing again
    return device >= DIAL0 && device <= DIAL8; 
}

// TBD - For mobile, map dials to tilt; for desktop, probably have a floating emulator window to simulate the dials
int32_t emulateDialsWithTilt(int32_t device)
{
    // if(device == DIAL0 || device == DIAL1) 
    // {
    //     float theta_x, theta_y, value;
    
    //     accelerometer_read(&theta_y, &theta_x);
    //     // N.B. The devices is rotated 180 degrees from its "natural,"
    //     // originally-developed orientation
    //     theta_y = -theta_y;
    //     theta_x = -theta_x;

    //     theta_x_smoothed = theta_x_smoothed * decay + theta_x * (1 - decay);
    //     theta_y_smoothed = theta_y_smoothed * decay + theta_y * (1 - decay);

    //     if(device == DIAL0)
    //         value = theta_x_smoothed / (2 * M_PI) * 3600;
    //     else /* device == DIAL1 */
    //         value = theta_y_smoothed / (2 * M_PI) * 3600;

    //     return value;
    // } 
    // else if(device == DIAL2 || device == DIAL3 || device == DIAL4) 
    // {
    //     if (gyro_reads == 0) {
    //         // Get the data from the real device.
    //         while (!gyro_ready()) {
    //         // Wait.
    //         }

    //         gyro_read(&gyro_dx, &gyro_dy, &gyro_dz);
    //     }

    //     gyro_reads = (gyro_reads + 1) % 3;

    //     switch (device) {
    //         case DIAL2: return gyro_dx;
    //         case DIAL3: return gyro_dy;
    //         case DIAL4: return gyro_dz;
    //     }
    // } 
    // else if(device == DIAL5) return accelerometer_read_x();
    // else if(device == DIAL6) return accelerometer_read_y();
    // else if(device == DIAL7) return accelerometer_read_z();
    //  
    printf("warning: unimplemented dial/tilt %d\n", device);
    return 0;
}

static int iclamp(int v, int low, int high)
{
    return v > high ? high : (v < low ? low : v);
}

int32_t events_get_valuator(int32_t device)
{
    // emulateMouseWithTouch(); // TBD

    switch (device)
    {
        case MOUSEX: {
            // For now, window and framebuffer dimensions may differ, so convert
            // window mouse coords to framebuffer coords
            int offsetX = cam2DWindowSize().width / 2 - frame_size.width / 2;
            int32_t fbPos = sdlMousePosX() - offsetX;
            int32_t posClamped = iclamp(fbPos, 1, frame_size.width - 1);
            return posClamped;
        }
        case MOUSEY: {
            // For now, window and framebuffer dimensions may differ, so convert
            // window mouse coords to framebuffer coords.  Also, invert mouse y.
            int offsetY = cam2DWindowSize().height / 2 - frame_size.height / 2;
            int32_t fbPos = cam2DWindowSize().height - sdlMousePosY() - offsetY;
            int32_t posClamped = iclamp(fbPos, 1, frame_size.height - 1);
            return posClamped;
        }
        default: {
            if (isDial(device))
                return emulateDialsWithTilt(device); // TBD
        }
    }  

    printf("warning: unimplemented evaluator %d\n", device);
    return 0;
}

Boolean events_get_button(int32_t button) {

    if (button >= RIGHTMOUSE && button <= LEFTMOUSE)
    {
        unsigned char buttonState = sdlMouseButtonState();
        switch (button)
        {
            case LEFTMOUSE:   return buttonState & SDL_BUTTON_LMASK;
            case MIDDLEMOUSE: return buttonState & SDL_BUTTON_MMASK;
            case RIGHTMOUSE:  return buttonState & SDL_BUTTON_RMASK;
            default:          return 0;
        }
    }
    
    unsigned char* keyArray = sdlGetKeyboardState();
    switch (button)
    {
        case LEFTSHIFTKEY:  return keyArray[SDL_SCANCODE_LSHIFT];
        case RIGHTSHIFTKEY: return keyArray[SDL_SCANCODE_RSHIFT];
        case CTRLKEY:       return keyArray[SDL_SCANCODE_LCTRL] || keyArray[SDL_SCANCODE_RCTRL];
        default:            return 0;
    }  
}

void events_qdevice(int32_t device)
{
    device_queued[device] = device;
}

uint32_t event_qread_start(int blocking)
{
    // emulateMouseWithTouch();
    // emulateEscapeWithTapClose();
    return input_queue_length;
}

int32_t events_qread_continue(int16_t *value)
{
    *value = input_queue[input_queue_head].val;
    int32_t device = input_queue[input_queue_head].device;
    input_queue_head = (input_queue_head + 1) % INPUT_QUEUE_SIZE;
    input_queue_length--;
    return device;
}

int32_t events_winopen(char *title, int32_t frame_width, int32_t frame_height)
{
    // emulateDialsWithTilt();
    // accelerometer_read(&theta_y_smoothed, &theta_x_smoothed);   
    // emulateMouseWithTouch();
    // emulateEscapeWithTapClose();

    frame_size.width = frame_width;
    frame_size.height = frame_height;

    return 0;
}

void events_tie(int32_t button, int32_t val1, int32_t val2)
{
    // XXX this maybe should be allowed to happen in libgl
    // XXX except that network_events is probably more efficient handling
    // XXX tie() itself...
    tied_valuators[button][0] = val1;
    tied_valuators[button][1] = val2;
}


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
    bool leftShift;
    bool rightShift;
    bool leftCtrl;
    bool rightCtrl;

} SDLEventState;

static SDLEventState sdlEvents = (SDLEventState){
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
    .keyDown = 0,
    .leftShift = false,
    .rightShift = false,
    .leftCtrl = false,
    .rightCtrl = false
};

bool *sdlLeftMouse = &sdlEvents.leftMouseButtonDown;
bool *sdlMiddleMouse = &sdlEvents.middleMouseButtonDown;
bool *sdlRightMouse = &sdlEvents.rightMouseButtonDown;
Pixel2D *sdlMousePos = &sdlEvents.mousePosition;
char *sdlKeyDown = &sdlEvents.keyDown;
bool *sdlLeftShift = &sdlEvents.leftShift;
bool *sdlRightShift = &sdlEvents.rightShift;
bool *sdlLeftCtrl = &sdlEvents.leftCtrl;
bool *sdlRightCtrl = &sdlEvents.rightCtrl;

void
windowResizeEvent(Size2D winSize)
{
    glViewport(0, 0, winSize.width, winSize.height);
    cam2DSetWindowSize(winSize);
}

void sdlEventsInit(const char *windowTitle)
{
    // Create SDL window
    sdlEvents.pWindow =
        SDL_CreateWindow(windowTitle,
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         cam2DWindowSize().width, cam2DWindowSize().height,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
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
    Vec2D deltaWorld = {postZoomWorld.x - preZoomWorld.x, postZoomWorld.y - preZoomWorld.y};
    cam2DSetPanDelta(deltaWorld);
}

void zoomEventPinch(float pinchDist, Vec2D pinchCoord)
{
    Vec2D preZoomWorld;
    cam2DNormWindowToWorld(pinchCoord, &preZoomWorld);

    // Zoom in/out by positive/negative pinch distance
    float zoomDelta = pinchDist * cPinchScale;
    cam2DSetZoomDelta(zoomDelta);

    // Zoom to point: Keep the world coords under sdlEvents.pinch position the same before and after the zoom
    Vec2D postZoomWorld;
    cam2DNormWindowToWorld(pinchCoord, &postZoomWorld);
    Vec2D deltaWorld = {postZoomWorld.x - preZoomWorld.x, postZoomWorld.y - preZoomWorld.y};
    cam2DSetPanDelta(deltaWorld);
}

void panEventMouse(Pixel2D mousePos)
{
    Pixel2D delta = {cam2DWindowSize().width / 2 + (mousePos.x - sdlEvents.leftMouseButtonDownCoord.x),
                     cam2DWindowSize().height / 2 + (mousePos.y - sdlEvents.leftMouseButtonDownCoord.y)};

    Vec2D device;
    cam2DWindowToDevice(delta, &device);

    Vec2D pan = {cam2DBasePan().x + device.x / cam2DZoom(),
                 cam2DBasePan().y + device.y / cam2DZoom() / cam2DAspect()};
    cam2DSetPan(pan);
}

void panEventFinger(Vec2D fingerCoord)
{
    Vec2D delta = {0.5f + (fingerCoord.x - sdlEvents.fingerDownCoord.x),
                   0.5f + (fingerCoord.y - sdlEvents.fingerDownCoord.y)};

    Vec2D device;
    cam2DNormWindowToDevice(delta, &device);

    Vec2D pan = {cam2DBasePan().x + device.x / cam2DZoom(),
                 cam2DBasePan().y + device.y / cam2DZoom() / cam2DAspect()};
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
            if (event.window.windowID == sdlEvents.windowID && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                Size2D winSize = {event.window.data1, event.window.data2};
                windowResizeEvent(winSize);
            }
            break;
        }

        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    const char *exit_js =
                        "if (document.referrer) {                                   "
                        "     window.history.back();                                "
                        "}                                                          "
                        "else {                                                     "
                        "    window.location.href = 'https://sgi-demos.github.io';  "
                        "}                                                          ";
                    emscripten_run_script(exit_js);
                    break; // as if
                }
                case SDLK_LSHIFT : sdlEvents.leftShift = true; break;
                case SDLK_RSHIFT : sdlEvents.rightShift = true; break;
                case SDLK_LCTRL : sdlEvents.leftCtrl = true; break; 
                case SDLK_RCTRL : sdlEvents.rightCtrl = true; break; 
                default: 
                {
                    // alphanumeric input
                    const char *keyName = SDL_GetKeyName(event.key.keysym.sym);
                    if (strlen(keyName) == 1)
                        sdlEvents.keyDown = keyName[0];
                }
            }
            break;
        }

        case SDL_KEYUP:
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_LSHIFT : sdlEvents.leftShift = false; break;
                case SDLK_RSHIFT : sdlEvents.rightShift = false; break;
                case SDLK_LCTRL  : sdlEvents.leftCtrl = false; break; 
                case SDLK_RCTRL  : sdlEvents.rightCtrl = false; break; 
                default: 
                {
                    // alphanumeric input
                    const char *keyName = SDL_GetKeyName(event.key.keysym.sym);
                    if (strlen(keyName) == 1)
                        if (sdlEvents.keyDown == keyName[0])
                            sdlEvents.keyDown = 0;
                }
            }
            break;
        }

        case SDL_MOUSEWHEEL:
        {
            // SDL_MOUSEWHEEL regression?
            // m->y no longer reliable (often y is 0 when sdlEvents.mouse wheel is spun up or down), use m->preciseY instead
            SDL_MouseWheelEvent *m = (SDL_MouseWheelEvent *)&event;
            bool mouseWheelDown = (m->preciseY < 0.0);
            zoomEventMouse(mouseWheelDown);
            break;
        }

        case SDL_MOUSEMOTION:
        {
            SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent *)&event;
            sdlEvents.mousePosition = (Pixel2D){(int)m->x, (int)m->y};
            if (sdlEvents.leftMouseButtonDown && !sdlEvents.fingerDown && !sdlEvents.pinch)
                panEventMouse(sdlEvents.mousePosition);
            break;
        }

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
            break;
        }

        case SDL_FINGERMOTION:
            if (sdlEvents.fingerDown)
            {
                SDL_TouchFingerEvent *m = (SDL_TouchFingerEvent *)&event;

                // Finger down and finger moving must match
                if (m->fingerId == sdlEvents.fingerDownId)
                {
                    Vec2D fingerCoord = (Vec2D){m->x, m->y};
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
            SDL_MultiGestureEvent *m = (SDL_MultiGestureEvent *)&event;
            if (m->numFingers == 2 && fabs(m->dDist) >= cPinchZoomThreshold)
            {
                sdlEvents.pinch = true;
                sdlEvents.fingerDown = false;
                sdlEvents.leftMouseButtonDown = false;
                Vec2D pinchCoord = (Vec2D){m->x, m->y};
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
