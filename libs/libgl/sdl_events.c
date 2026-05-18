//
// Convert SDL events to IRIS GL events
//
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include "sdl_framebuffer.h"

// IRIS GL
#include <gl.h>
#include <device.h>
#include "events.h"

typedef struct gl_event {
    int32_t device;
    int16_t val;
} gl_event;

static uint32_t sdl_devices_queued[2048];
static uint32_t sdl_tied_valuators[2048][2];
static gl_event sdl_input_queue[INPUT_QUEUE_SIZE];
static uint32_t sdl_input_queue_head = 0;    // The next item that needs to be read
static uint32_t sdl_input_queue_length = 0;  // The number of items in the queue (tail = (head + length) % len)
static uint32_t sdl_window_id = 0;           // Set in events_winopen; used as REDRAW event value
static int32_t sdl_keycode_to_gl(int32_t sdl_keycode);
static void enqueue_event(gl_event *e);

static int mousePosX()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return x;
}

static int mousePosY()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return y;
}

static unsigned char mouseButtonState()
{
    int x, y;
    return SDL_GetMouseState(&x, &y);
}

static Uint8* getKeyboardState()
{
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    return (unsigned char*)keys;
}

static bool mouseInsideFramebuffer()
{
    return sdlInsideFramebuffer(mousePosX(), mousePosY());
}

static void exitEvent()
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

// EVENT: mouse transited framebuffer boundary, in or out
static void mouseMotionEvent()
{
    // detect when mouse transits into or out of framebuffer for INPUTCHANGE events
    // TODO: also perhaps when window loses/gains focus?
    static bool prevMouseInsideFramebuffer = false;
    bool mouseInsideFB = mouseInsideFramebuffer();
    if (mouseInsideFB != prevMouseInsideFramebuffer)
    {
        prevMouseInsideFramebuffer = mouseInsideFB;
        if (sdl_devices_queued[INPUTCHANGE])
        {
            gl_event ev;
            ev.device = INPUTCHANGE;
            ev.val = mouseInsideFB;
            enqueue_event(&ev);
        }
    }
}

// EVENT: SDL keycode, string
static void keyDownEvent(int sdl_keycode, char *text)
{
    // convert SDL key event to GL and add it to GL event queue
    // printf("sdl_keycode = %d, text = [%s]\n", sdl_keycode, text);
    gl_event ev;
    ev.device = sdl_keycode_to_gl(sdl_keycode);
    if (ev.device != 0 && (sdl_devices_queued[ev.device] || sdl_devices_queued[KEYBD]))
    {
        ev.val = 1;
        enqueue_event(&ev);
        if (sdl_devices_queued[KEYBD])
        {
            if (strlen(text) == 1)
            {
                ev.device = KEYBD;
                ev.val = text[0];
                enqueue_event(&ev);
            }
        }
    }
}

// EVENT: SDL mouse button, button up/down, mouse position
static void mouseButtonEvent(int sdlButton, bool buttonDown)
{
    gl_event ev;

    switch (sdlButton)
    {
        case SDL_BUTTON_LEFT:   ev.device = LEFTMOUSE;      break;
        case SDL_BUTTON_MIDDLE: ev.device = MIDDLEMOUSE;    break;
        case SDL_BUTTON_RIGHT:  ev.device = RIGHTMOUSE;     break;
        default: ev.device = NULLDEV;
    }

    // convert SDL mouse button event to GL and add it to GL event queue
    if (ev.device != NULLDEV && sdl_devices_queued[ev.device])
    {
        ev.val = buttonDown;
        enqueue_event(&ev);

        // tied valuators are used for capturing mouse x and/or y position at
        // the time when a mouse button (or other device) is pressed, and
        // emitting those as mouse position x and y events right after the
        // mouse button (or other device) event in the GL event queue
        gl_event tied_ev;
        for (int j = 0; j < 2; ++j)
        {
            if (sdl_tied_valuators[ev.device][j])
            {
                tied_ev.device = sdl_tied_valuators[ev.device][j];
                tied_ev.val = events_get_valuator(sdl_tied_valuators[ev.device][j]);
                enqueue_event(&tied_ev);
            }
        }
    }
}

// inSdlProcessEvents - This is the reentrancy guard for sdlProcessEvents.
//
// Always true for the duration of sdlProcessEvents(), false otherwise.
//
// Any set of events enqueued during one sdlProcessEvents call MUST stay contiguous
// (atomic) in sdl_input_queue. Some demos (e.g. buttonfly) depend on atomic event
// groups such as "LEFTMOUSE + tied MOUSEX + tied MOUSEY".
//
// Silently guarded in all yield paths:
//   yieldByEventQuery     - prevents reentrant REDRAW pulse + frame_complete
//   yieldByFrame          - prevents mid-pump Asyncify suspend
//   events_frame_complete - prevents any other re-entrant callers
//
// Loudly guarded in sdlProcessEvents() itself, with an actual abort (the three
// yield-path guards prevent normal expected reentrancy, so reaching this
// abort means someone has bypassed these guards with new code).
//
// See ARCHITECTURE.md ('Event pump integrity') for further details.
//
static bool inSdlProcessEvents = false;

//
// sdlProcessEvents - The event pump, drains events off the SDL event queue and
// enqueues them onto the IRIS GL event queue
//
void sdlProcessEvents()
{
    if (inSdlProcessEvents)
    {
        // This abort catches any future code that bypasses the existing reentrancy guards
        fprintf(stderr,
            "FATAL: sdlProcessEvents called reentrantly!\n"
            "See ARCHITECTURE.md ('Event pump integrity') for why this is prohibited.\n");
        abort();
    }

    inSdlProcessEvents = true;
    SDL_Event event;
    char text[32] = "";
    int keysym = 0;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                exitEvent();
                break;

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    sdlResizeWindow(event.window.windowID);
                break;

            case SDL_TEXTINPUT:
                memset(text, 0, sizeof(text));
                strncpy(text, event.text.text, sizeof(text)-1);
                //printf("SDL_TEXTINPUT text = [%s] keysym = [%d]\n", text, keysym);
                if (strlen(SDL_GetKeyName(keysym)) == 1)
                    keyDownEvent(keysym, text);
                break;

            case SDL_KEYDOWN:
                keysym = event.key.keysym.sym;
                //printf("SDL_KEYDOWN keysym = %d\n", keysym);
                if (strlen(SDL_GetKeyName(keysym)) > 1)
                    keyDownEvent(keysym, "");
                break;

            case SDL_MOUSEMOTION:
                mouseMotionEvent();
                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseButtonEvent(((SDL_MouseButtonEvent *)&event)->button, true);
                break;

            case SDL_MOUSEBUTTONUP:
                mouseButtonEvent(((SDL_MouseButtonEvent *)&event)->button, false);
                break;
        }
    }
    inSdlProcessEvents = false;
}

// Framerate control:
// - Simulate a decent SGI machine for the time at 30fps, 60 fps is too fast for some demos (like ideas)
// - Also, in the 80s and 90s, we had less than 60 fps and we liked it!
// - TODO: Make this a per-demo option
const int DEMO_FPS = 30;
const int DEMO_TICKS_PER_FRAME_BUDGET = 1000 / DEMO_FPS;
static Uint32 frameStartTicks = 0;

// yieldByFrame - Don't run faster than DEMO_FPS:
// Browser: Asyncify yield to the browser for the remainder of the frame budget time.
// Native:  SDL sleep for the remainder of the frame budget time.
void yieldByFrame(Uint32 frameTotalTicks)
{
    // This guard catches mid-pump Asyncify suspend on web builds. While not currently
    // necessary on native builds, we guard native too so that all yield paths obey the
    // same uniform "check the guard" rule.
    if (inSdlProcessEvents)
        return;

    if (frameTotalTicks < DEMO_TICKS_PER_FRAME_BUDGET)
    {
#ifdef __EMSCRIPTEN__
        // Asyncify: yield to the browser for the remainder of the frame
        // budget. The browser saves our C stack, runs other work, and
        // resumes here approximately DEMO_TICKS_PER_FRAME_BUDGET - frameTicks
        // milliseconds later.
        emscripten_sleep(DEMO_TICKS_PER_FRAME_BUDGET - frameTotalTicks);
#else
        // Native: just sleep the remainder of the frame budget
        SDL_Delay(DEMO_TICKS_PER_FRAME_BUDGET - frameTotalTicks);
#endif
    }
#ifdef __EMSCRIPTEN__
    else
    {
        // Frame ran over budget, but we still must yield to the browser
        // at least once per frame or the page will hang.
        emscripten_sleep(0);
    }
#endif
}

//
//  events_frame_complete - The single platform yield point
//
//  Called from:
//    - swapbuffers()       (double-buffered demos)
//    - gflush()            (single-buffered demos)
//    - dopup()             (dopup's modal inner loop)
//    - yieldByEventQuery() (qtest/qread/getbutton/getvaluator catch all for demos
//                           such as twilight, which don't call swapbuffers or gflush,
//                           but do at least poll the GL event queue)
//
//  This function:
//    1. Runs SDL event pump (iff pump is not already running).
//    2. Presents the framebuffer that was last set via events_set_framebuffer().
//       In practice, the framebuffer pointer is initialized by winopen and then only
//       updated by double-buffered demos via swapbuffers().
//    3. Native:     Delays if necessary to not exceed DEMO_FPS via SDL sleep.
//       Emscripten: Yields to the browser via emscripten_sleep(), also not exceeding DEMO_FPS.
//
void events_frame_complete(void)
{
    // This guards against any reentrant callers that don't go through yieldByEventQuery or yieldByFrame
    if (inSdlProcessEvents)
        return;

    // Translate input events into IRIS GL events
    sdlProcessEvents();

    // Update framebuffer texture with rendered pixels & render it
    sdlUpdateFramebufferTexture();
    sdlRenderFramebufferTexture();

    // Yield to browser every frame, and don't exceed DEMO_FPS in both browser & native
    Uint32 frameTotalTicks = SDL_GetTicks() - frameStartTicks;
    yieldByFrame(frameTotalTicks);

    // Start the clock for the next frame, which will be whatever the
    // demo does between now and the next call to this function
    frameStartTicks = SDL_GetTicks();
}

//
// yieldByEventQuery - Guarded and throttled catch-all yield, called from event query
// functions (events_qread_start, events_get_button, events_get_valuator). This is for
// demos that don't call swapbuffers or gflush, like twilight, but that do still query
// for events.
//
static void yieldByEventQuery()
{
    // This reentrancy guard prevents inserting REDRAW events and re-entering
    // sdlProcessEvents while querying event state. Specific example from the
    // buttonfly demo:
    //
    // sdlProcessEvents()
    // └─mouseButtonEvent(SDL_BUTTON_LEFT) // user pressed left mouse
    //   └─enqueue_event(LEFTMOUSE)
    //   └─events_get_valuator(MOUSEX)     // demo wants mouse x position with left mouse event
    //     └─yieldByEventQuery()
    //       └─ GUARD NOW PREVENTS -> enqueue REDRAW *AND* sdlProcessEvents()
    //
    if (inSdlProcessEvents)
        return;

    // This throttle keeps us from yielding more often than DEMO_FPS
    if (SDL_GetTicks() - frameStartTicks >= DEMO_TICKS_PER_FRAME_BUDGET)
    {
        // If a REDRAW-interested demo is waiting on events, pulse a REDRAW
        // so it can repaint - there's no external window system pushing
        // REDRAWs the way SGI did. Window id is set in the value field to
        // follow the IRIS GL API, although no demos in the current demo set
        // make use of it.
        if (sdl_devices_queued[REDRAW])
        {
            gl_event ev;
            ev.device = REDRAW;
            ev.val = (int16_t)sdl_window_id;
            enqueue_event(&ev);
        }

        // Pump events, redraw, and yield
        events_frame_complete();
    }
}


//
// IRIS GL event queue
//

// QUERY: SDL mouse position at any time
int32_t events_get_valuator(int32_t device)
{
    yieldByEventQuery();
    switch (device)
    {
        case MOUSEX: return sdlClampToFramebufferX(mousePosX());
        case MOUSEY: return sdlClampToFramebufferY(mousePosY());
    }

    printf("warning: unimplemented valuator %d\n", device);
    return 0;
}

#define GL_KEY_COUNT 78
static int32_t sdl_to_gl_key_map[GL_KEY_COUNT][2] = {
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
SDL_Scancode gl_to_sdl_scancode(int32_t gl_key)
{
    for (int i = 0; i < GL_KEY_COUNT; ++i)
    {
        if (sdl_to_gl_key_map[i][1] == gl_key)
            return SDL_GetScancodeFromKey(sdl_to_gl_key_map[i][0]);
    }
    return 0;
}

// get GL key from SDL keycode
int32_t sdl_keycode_to_gl(int32_t sdl_keycode)
{
    for (int i = 0; i < GL_KEY_COUNT; ++i)
    {
        if (sdl_to_gl_key_map[i][0] == sdl_keycode)
            return sdl_to_gl_key_map[i][1];
    }
    return 0;
}

Boolean events_get_button(int32_t button)
{
    yieldByEventQuery();

    if (button >= RIGHTMOUSE && button <= LEFTMOUSE)
    {
        unsigned char buttonState = mouseButtonState();
        switch (button)
        {
            case LEFTMOUSE:   return buttonState & SDL_BUTTON_LMASK;
            case MIDDLEMOUSE: return buttonState & SDL_BUTTON_MMASK;
            case RIGHTMOUSE:  return buttonState & SDL_BUTTON_RMASK;
            default:          return 0;
        }
    }

    unsigned char* keyArray = getKeyboardState();
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
    sdl_devices_queued[device] = device;
}

void events_unqdevice(int32_t device)
{
    sdl_devices_queued[device] = 0;
}

void enqueue_event(gl_event *e)
{
    if (sdl_input_queue_length == INPUT_QUEUE_SIZE) {
        printf("Input queue overflow.");
    }
    else {
        uint32_t tail = (sdl_input_queue_head + sdl_input_queue_length) % INPUT_QUEUE_SIZE;
        sdl_input_queue[tail] = *e;
        sdl_input_queue_length++;
    }
}

uint32_t events_qread_start()
{
    // This is called by qtest() and qread(), even when the GL-side queue is empty.
    // This is the hot spot where demos like twilight discover "no events"; a throttled
    // yield here lets SDL pump events and fill the GL queue before returning.
    yieldByEventQuery();
    return sdl_input_queue_length;
}

int32_t events_qread_continue(int16_t *value)
{
    *value = sdl_input_queue[sdl_input_queue_head].val;
    int32_t device = sdl_input_queue[sdl_input_queue_head].device;
    sdl_input_queue_head = (sdl_input_queue_head + 1) % INPUT_QUEUE_SIZE;
    sdl_input_queue_length--;
    return device;
}

int32_t events_winopen(char *title, int32_t frame_width, int32_t frame_height)
{
    static int sdl_initialized = 0;
    if (!sdl_initialized) {
        // On winopen() do full SDL initialization
        sdl_window_id = sdlInitWindow();
        sdlInitFramebufferTexture();
        atexit(sdlFreeFramebufferTexture);

        // Seed the frame timer so the first frame paces correctly
        frameStartTicks = SDL_GetTicks();
        sdl_initialized = 1;
    }

    sdlOpenWindow(title, frame_width, frame_height);
    return 0;
}

void events_set_framebuffer(unsigned char* framebuffer)
{
    sdlSetFramebufferSource(framebuffer);
}

// usually:
// button = LEFTMOUSE, MIDDLEMOUSE, RIGHTMOUSE
// val1 = MOUSEX
// val2 = MOUSEY
void events_tie(int32_t button, int32_t val1, int32_t val2)
{
    sdl_tied_valuators[button][0] = val1;
    sdl_tied_valuators[button][1] = val2;
}
