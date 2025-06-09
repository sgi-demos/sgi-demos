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
static uint32_t sdl_input_queue_length = 0;  // The number of items in the queue (tail = (head + length) % len):
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

static void keyDownEvent(int sdl_keycode, char *text)
{
    if (sdl_keycode == SDLK_ESCAPE)
        exitEvent();
    else 
    {
        // convert SDL key event to GL and add it to GL event queue
        //printf("sdl_keycode = %d, text = [%s]\n", sdl_keycode, text);
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
}

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

        // tied valuators is typically used for capturing mouse x and/or
        // y position at the time when a mouse button is pressed, and 
        // emitting those as mouse position x and y events right after
        // the mouse button event in the GL event queue
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

void sdlProcessEvents()
{
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
                    sdlResizeWindow(event.window.windowID,(Size2D){event.window.data1, event.window.data2});
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
}


//
// IRIS GL event queue
//

int32_t events_get_valuator(int32_t device)
{
    switch (device)
    {
        case MOUSEX: return sdlClampToFramebufferX(mousePosX());
        case MOUSEY: return sdlClampToFramebufferY(mousePosY());
    }  

    printf("warning: unimplemented evaluator %d\n", device);
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

Boolean events_get_button(int32_t button) {

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
    sdlOpenWindow(title, frame_width, frame_height);
    return 0;
}

void events_set_framebuffer(unsigned char* framebuffer)
{
    sdlSetFramebufferSource(framebuffer);
}

void events_tie(int32_t button, int32_t val1, int32_t val2)
{
    sdl_tied_valuators[button][0] = val1;
    sdl_tied_valuators[button][1] = val2;
}