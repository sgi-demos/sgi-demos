#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "basic_types.h"
#define INPUT_QUEUE_SIZE 128

//
// function                 sdl   params                        frequency
// --------                 ---   ------                        ---------
// events_winopen           to:   title, fb size                once, at startup
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

extern int32_t events_winopen(char *title, int32_t frame_width, int32_t frame_height);

extern int32_t events_get_valuator(int32_t device);
extern Boolean events_get_button(int32_t button);

extern void events_qdevice(int32_t device);
extern void events_unqdevice(int32_t device);

extern uint32_t events_qread_start();
extern int32_t events_qread_continue(int16_t *value);

extern void events_tie(int32_t button, int32_t val1, int32_t val2);

extern void events_set_framebuffer(unsigned char* framebuffer);

#endif /* __EVENTS_H__ */
