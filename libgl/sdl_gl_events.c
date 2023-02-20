#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#else
#include <SDL2/SDL.h>
#endif

#include <gl.h>
#include <device.h>
#include "camera2D.h"
#include "sdl_events.h"
#include "events.h"

int sdlMousePosX();
int sdlMousePosY();
unsigned char sdlMouseButtonState();
unsigned char* sdlGetKeyboardState();
int sdlPeepEvents();

typedef struct gl_event {
    int32_t device;
    int16_t val;
} gl_event;

static uint32_t devices_queued[2048];
static uint32_t tied_valuators[2048][2];
static gl_event input_queue[INPUT_QUEUE_SIZE];
static uint32_t input_queue_head = 0;    // The next item that needs to be read
static uint32_t input_queue_length = 0;  // The number of items in the queue (tail = (head + length) % len):

typedef struct
{
    // Window
    SDL_Window* pWindow;
    Uint32 windowID;
    Size2D frameSize; // Framebuffer size may not be the same as window size

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

} SDLState;

static SDLState sdlState = (SDLState)
{
    // Window
    .pWindow = NULL,
    .windowID = 0,
    .frameSize = {640, 480},

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

// TBD - for desktop, have an escape key; for mobile, probably will have a window title bar with X to close window
//       which user can tap, and this can enqueue an ESCKEY event here
static void emulateEscapeWithTapClose()
{
    // // Only Home button for now, which is mapped to ESC.
    // int home_button;
    // gl_event ev;
    
    // // libawesome will queue up two transitions per frame, so read the button
    // // twice to get those.
    // for (int i = 0; i < 2; i++) {
    //     home_button = awesome_get_home_button();
    //     if(home_button != home_button_previous) {
    //         if(devices_queued[ESCKEY]) {
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
    // gl_event ev;
    // int drained = 0;
    // while((e = touchscreen_read(&x, &y, &z)) != TOUCHSCREEN_IDLE) {
	// drained ++;
	// switch(e) {
	//     case TOUCHSCREEN_START:
	// 	// N.B. The devices is rotated 180 degrees from it's
	// 	// "natural," originally-developed orientation
	// 	mousex = 800 - 1 - x;
	// 	mousey = y; // GL valuator MOUSEY is 0 at bottom
	// 	if(devices_queued[LEFTMOUSE]) {
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
	// 	if(devices_queued[LEFTMOUSE]) {
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

static int clamp(int v, int low, int high)
{
    return v > high ? high : (v < low ? low : v);
}

static Boolean would_clamp(int v, int low, int high)
{
    return v < low || v > high;
}

int32_t sdl_to_gl_mouse_x()
{
    // For now, SDL window and GL framebuffer dimensions may differ, so convert
    // SDL window mouse coords to GL framebuffer coords
    int32_t offsetX = sdlWindowSize().width / 2 - sdlState.frameSize.width / 2;
    return sdlMousePosX() - offsetX;
}

int32_t sdl_to_gl_mouse_y()
{
    // For now, SDL window and GL framebuffer dimensions may differ, so convert
    // SDL window mouse coords to GL framebuffer coords, including inverting y
    int32_t offsetY = sdlWindowSize().height / 2 - sdlState.frameSize.height / 2;
    return sdlWindowSize().height - sdlMousePosY() - offsetY;
}

bool mouse_inside_framebuffer()
{
    return !would_clamp(sdl_to_gl_mouse_x(), 1, sdlState.frameSize.width - 1) 
        && !would_clamp(sdl_to_gl_mouse_y(), 1, sdlState.frameSize.height - 1);
}

int32_t events_get_valuator(int32_t device)
{
    // emulateMouseWithTouch(); // TBD

    switch (device)
    {
        case MOUSEX: return clamp(sdl_to_gl_mouse_x(), 1, sdlState.frameSize.width - 1);
        case MOUSEY: return clamp(sdl_to_gl_mouse_y(), 1, sdlState.frameSize.height - 1);
        default: {
            //if (isDial(device))
            //    return emulateDialsWithTilt(device); // TBD
        }
    }  

    printf("warning: unimplemented evaluator %d\n", device);
    return 0;
}

#define GL_KEY_COUNT 78
static int32_t sdl_to_gl_key_map[GL_KEY_COUNT][3] = {
    {SDLK_0,            ZEROKEY},
    {SDLK_1,            ONEKEY},
    {SDLK_2,            TWOKEY},
    {SDLK_3,            THREEKEY},
    {SDLK_4,            FOURKEY},
    {SDLK_5,            FIVEKEY},
    {SDLK_6,            SIXKEY},
    {SDLK_7,            SEVENKEY},
    {SDLK_8,            EIGHTKEY},
    {SDLK_9,            NINEKEY},
    {SDLK_a,            AKEY},
    {SDLK_b,            BKEY},
    {SDLK_BACKQUOTE,    ACCENTGRAVEKEY},
    {SDLK_BACKSLASH,    BACKSLASHKEY},
    {SDLK_BACKSPACE,    BACKSPACEKEY},
    {SDLK_c,            CKEY},
    {SDLK_CAPSLOCK,     CAPSLOCKKEY},
    {SDLK_COMMA,        COMMAKEY},
    {SDLK_d,            DKEY},
    {SDLK_DELETE,       DELKEY},
    {SDLK_DOWN,         DOWNARROWKEY},
    {SDLK_e,            EKEY},
    {SDLK_EQUALS,       EQUALKEY},
    {SDLK_ESCAPE,       ESCKEY},
    {SDLK_f,            FKEY},
    {SDLK_g,            GKEY},
    {SDLK_h,            HKEY},
    {SDLK_i,            IKEY},
    {SDLK_j,            JKEY},
    {SDLK_k,            KKEY},
    {SDLK_KP_0,         PAD0},
    {SDLK_KP_1,         PAD1},
    {SDLK_KP_2,         PAD2},
    {SDLK_KP_3,         PAD3},
    {SDLK_KP_4,         PAD4},
    {SDLK_KP_5,         PAD5},
    {SDLK_KP_6,         PAD6},
    {SDLK_KP_7,         PAD7},
    {SDLK_KP_8,         PAD8},
    {SDLK_KP_9,         PAD9},
    {SDLK_KP_COMMA,     PADCOMMA},
    {SDLK_KP_ENTER,     PADENTER},
    {SDLK_KP_MINUS,     PADMINUS},
    {SDLK_KP_PERIOD,    PADPERIOD},
    {SDLK_l,            LKEY},
    {SDLK_LCTRL,        CTRLKEY},
    {SDLK_LEFT,         LEFTARROWKEY},
    {SDLK_LEFTBRACKET,  LEFTBRACKETKEY},
    {SDLK_LSHIFT,       LEFTSHIFTKEY},
    {SDLK_m,            MKEY},
    {SDLK_MINUS,        MINUSKEY},
    {SDLK_n,            NKEY},
    {SDLK_o,            OKEY},
    {SDLK_p,            PKEY},
    {SDLK_PERIOD,       PERIODKEY},
    {SDLK_q,            QKEY},
    {SDLK_QUOTE,        QUOTEKEY},
    {SDLK_r,            RKEY},
    {SDLK_RETURN,       RETKEY},
    {SDLK_RETURN2,      LINEFEEDKEY},
    {SDLK_RIGHT,        RIGHTARROWKEY},
    {SDLK_RIGHTBRACKET, RIGHTBRACKETKEY},
    {SDLK_RSHIFT,       RIGHTSHIFTKEY},
    {SDLK_s,            SKEY},
    {SDLK_SCROLLLOCK,   NOSCRLKEY},
    {SDLK_SEMICOLON,    SEMICOLONKEY},
    {SDLK_SLASH,        VIRGULEKEY},
    {SDLK_SPACE,        SPACEKEY},
    {SDLK_STOP,         BREAKKEY},
    {SDLK_t,            TKEY},
    {SDLK_TAB,          TABKEY},
    {SDLK_u,            UKEY},
    {SDLK_UP,           UPARROWKEY},
    {SDLK_v,            VKEY},
    {SDLK_w,            WKEY},
    {SDLK_x,            XKEY},
    {SDLK_y,            YKEY},
    {SDLK_z,            ZKEY}
    // {SDLK_UNDEFINED,    SETUPKEY},
    // {SDLK_UNDEFINED,    PADPF2},
    // {SDLK_UNDEFINED,    PADPF1},
    // {SDLK_UNDEFINED,    PADPF4},
    // {SDLK_UNDEFINED,    PADPF3},
};

// linear search key map, if this turns out to be a performance issue, we
// can sort the SDLK_ keys by numeric value to directly index the GL key

// get SDL scancode from GL key
static SDL_Scancode gl_to_sdl_scancode(int32_t gl_key)
{
    for (int i = 0; i < GL_KEY_COUNT; ++i)
    {
        if (sdl_to_gl_key_map[i][1] == gl_key)
            return SDL_GetScancodeFromKey(sdl_to_gl_key_map[i][0]);
    }
    return 0;
}

// get GL key from SDL keycode
static int32_t sdl_keycode_to_gl(int32_t sdl_keycode)
{
    for (int i = 0; i < GL_KEY_COUNT; ++i)
    {
        if (sdl_to_gl_key_map[i][0] == sdl_keycode)
            return sdl_to_gl_key_map[i][1];
    }
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
        case CTRLKEY: 
            return keyArray[SDL_SCANCODE_LCTRL] || keyArray[SDL_SCANCODE_RCTRL];

        default:  
        {
            // Map SDL_SCANCODE to GL device
            SDL_Scancode sdl_scancode = gl_to_sdl_scancode(button);
            if (sdl_scancode != 0)
                return keyArray[sdl_scancode];
            else
                return 0;
        }
    }  
}

void events_qdevice(int32_t device)
{
    devices_queued[device] = device;
}

void events_unqdevice(int32_t device)
{
    devices_queued[device] = 0;
}

static void enqueue_event(gl_event *e)
{
    if (input_queue_length == INPUT_QUEUE_SIZE) {
        printf("Input queue overflow.");
    } else {
        uint32_t tail = (input_queue_head + input_queue_length) % INPUT_QUEUE_SIZE;
        input_queue[tail] = *e;
        input_queue_length++;
    }
}

uint32_t events_qread_start(int blocking)
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
    Size2D frameSize = { frame_width, frame_height };
    sdlState.frameSize = frameSize;

    // tell app mouse is in middle of framebuffer, even if it isn't?

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

void windowResizeEvent(Size2D winSize)
{
    glViewport(0, 0, winSize.width, winSize.height);
    cam2DSetWindowSize(winSize);
}

void sdlInit(const char *windowTitle)
{
    // Create SDL window
    sdlState.pWindow =
        SDL_CreateWindow(windowTitle,
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         sdlWindowSize().width, sdlWindowSize().height,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    sdlState.windowID = SDL_GetWindowID(sdlState.pWindow);

    // Create OpenGLES 2 context on SDL window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GLContext glc = SDL_GL_CreateContext(sdlState.pWindow);

    // Set clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Initialize viewport
    windowResizeEvent(sdlWindowSize());
}

void sdlPresent()
{
    SDL_GL_SwapWindow(sdlState.pWindow);
}

void sdlProcessEvents()
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
            if (event.window.windowID == sdlState.windowID && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
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
                    // Go to previous page, or if none, to demo home page
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
                
                default:
                {
                    // convert SDL key event to GL and add it to GL event queue
                    gl_event ev;
                    ev.device = sdl_keycode_to_gl(event.key.keysym.sym);
                    if (ev.device != 0 && devices_queued[ev.device])
                    {
                        ev.val = 1; 
                        enqueue_event(&ev);
                    }
                }
            }
            break;
        }

        case SDL_MOUSEWHEEL:
        {
            // SDL_MOUSEWHEEL regression?
            // m->y no longer reliable (often y is 0 when sdlState.mouse wheel is spun up or down), use m->preciseY instead
            SDL_MouseWheelEvent *m = (SDL_MouseWheelEvent *)&event;
            bool mouseWheelDown = (m->preciseY < 0.0);
            cam2DZoomEventMouse(mouseWheelDown, sdlState.mousePosition);
            break;
        }

        case SDL_MOUSEMOTION:
        {
            // detect when mouse transits into or out of framebuffer for INPUTCHANGE events
            // TODO: also perhaps when window loses/gains focus? 
            bool mouseInsideFB = mouse_inside_framebuffer();
            if (mouseInsideFB != sdlState.mouseInsideFramebuffer) 
            {
                sdlState.mouseInsideFramebuffer = mouseInsideFB;
                if (devices_queued[INPUTCHANGE])
                {
                    gl_event ev;
                    ev.device = INPUTCHANGE;
                    ev.val = mouseInsideFB;
                    enqueue_event(&ev);
                }
            }

            SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent *)&event;
            sdlState.mousePosition = (Pixel2D){(int)m->x, (int)m->y};
            if (sdlState.leftMouseButtonDown && !sdlState.fingerDown && !sdlState.pinch)
                cam2DPanEventMouse(sdlState.mousePosition, sdlState.leftMouseButtonDownCoord);
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            if (!sdlState.fingerDown && !sdlState.pinch)
            {
                SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent *)&event;               
                gl_event ev;

                switch (m->button)
                {
                case SDL_BUTTON_LEFT:
                    sdlState.leftMouseButtonDown = true;
                    sdlState.leftMouseButtonDownCoord = (Pixel2D){(int)m->x, (int)m->y};
                    cam2DSetBasePan();
                    ev.device = LEFTMOUSE;
                    break;
                case SDL_BUTTON_MIDDLE:
                    sdlState.middleMouseButtonDown = true;
                    ev.device = MIDDLEMOUSE;
                    break;
                case SDL_BUTTON_RIGHT:
                    sdlState.rightMouseButtonDown = true;
                    ev.device = RIGHTMOUSE;
                    break;
                }

                // convert SDL mouse button event to GL and add it to GL event queue
                if (devices_queued[ev.device]) 
                {
                    ev.val = 1;
                    enqueue_event(&ev);

                    // tied valuators is typically used for capturing mouse x and/or
                    // y position at the time when a mouse button is pressed, and 
                    // emitting those as mouse position x and y events right after
                    // the mouse button event in the GL event queue
                    gl_event tied_ev;
                    for (int j = 0; j < 2; ++j) 
                    {
                        if (tied_valuators[ev.device][j])
                        {
                            tied_ev.device = tied_valuators[ev.device][j];
                            tied_ev.val = events_get_valuator(tied_valuators[ev.device][j]);
                            enqueue_event(&tied_ev);
                        }
                    }
                }

            }
            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent *)&event;
            gl_event ev;

            switch (m->button)
            {
            case SDL_BUTTON_LEFT:
                sdlState.leftMouseButtonDown = false;
                ev.device = LEFTMOUSE;
                break;
            case SDL_BUTTON_MIDDLE:
                sdlState.middleMouseButtonDown = false;
                ev.device = MIDDLEMOUSE;
                break;
            case SDL_BUTTON_RIGHT:
                sdlState.rightMouseButtonDown = false;
                ev.device = RIGHTMOUSE;
                break;
            }
            // convert SDL mouse button event to GL and add it to GL event queue
            if (devices_queued[ev.device]) 
            {
                ev.val = 0;
                enqueue_event(&ev);

                gl_event tied_ev;
                for (int j = 0; j < 2; ++j) 
                {
                    if (tied_valuators[ev.device][j])
                    {
                        tied_ev.device = tied_valuators[ev.device][j];
                        tied_ev.val = events_get_valuator(tied_valuators[ev.device][j]);
                        enqueue_event(&tied_ev);
                    }
                }
            }

            break;
        }

        case SDL_FINGERMOTION:
            if (sdlState.fingerDown)
            {
                SDL_TouchFingerEvent *m = (SDL_TouchFingerEvent *)&event;

                // Finger down and finger moving must match
                if (m->fingerId == sdlState.fingerDownId)
                {
                    Vec2D fingerCoord = (Vec2D){m->x, m->y};
                    cam2DPanEventFinger(fingerCoord, sdlState.fingerDownCoord);
                }
            }
            break;

        case SDL_FINGERDOWN:
            if (!sdlState.pinch)
            {
                // Finger already down means multiple fingers, which is handled by multigesture event
                if (sdlState.fingerDown)
                    sdlState.fingerDown = false;
                else
                {
                    SDL_TouchFingerEvent *m = (SDL_TouchFingerEvent *)&event;
                    sdlState.fingerDown = true;
                    sdlState.fingerDownCoord = (Vec2D){m->x, m->y};
                    sdlState.fingerDownId = m->fingerId;
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
                sdlState.pinch = true;
                sdlState.fingerDown = false;
                sdlState.leftMouseButtonDown = false;
                Vec2D pinchCoord = (Vec2D){m->x, m->y};
                cam2DZoomEventPinch(m->dDist, pinchCoord);
            }
            break;
        }

        case SDL_FINGERUP:
            sdlState.fingerDown = false;
            sdlState.pinch = false;
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

Size2D sdlFramebufferSize()
{
    return sdlState.frameSize;
}

Size2D sdlWindowSize()
{
    return cam2DWindowSize();
}

Vec2D sdlViewport()   
{ 
    return cam2DViewport();
}

bool sdlViewChanged()
{
    return cam2DUpdated();
}