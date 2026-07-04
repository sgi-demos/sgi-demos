#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "basic_types.h"
#define INPUT_QUEUE_SIZE 128

//
// function                 sdl   params                        frequency
// --------                 ---   ------                        ---------
// events_winopen           to:   title                         once, at startup
// events_get_valuator      from: mouse, x and y                continuous
// events_get_button        from: mouse & keyboard button state continuous
// events_qdevice           to:   event queue device filtering  continuous
// events_unqdevice         to:   event queue device filtering  continuous
// events_qread_start       from: sdl queue length (rewrite)    event queue
// events_qread_continue    from: sdl queue pop device, val     event queue
// events_tie               to:   event queue device & valuator continuous
// events_set_framebuffer   to:   framebuffer                   continuous
//
extern void events_frame_complete(void);

// Implemented in gl.c, called by the events layer when the framebuffer size
// is established (window creation) or changes (window resize). The
// framebuffer tracks the window size.
extern void gl_framebuffer_resized(int width, int height);

extern int32_t events_winopen(char *title);
extern void events_keepaspect(int32_t x, int32_t y);
extern void events_fix_framebuffer_size(int32_t width, int32_t height);

extern int32_t events_get_valuator(int32_t device);
extern Boolean events_get_button(int32_t button);

extern void events_qdevice(int32_t device);
extern void events_unqdevice(int32_t device);

extern uint32_t events_qread_start();
extern int32_t events_qread_continue(int16_t *value);

extern void events_tie(int32_t button, int32_t val1, int32_t val2);

extern void events_set_framebuffer(unsigned char* framebuffer);

#endif /* __EVENTS_H__ */
