#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "basic_types.h"
#define INPUT_QUEUE_SIZE 128

// The SDL side of IRIS GL's window and events (sdl_events.c): gl.c calls
// these to open the window, read device state, drain SDL input into its GL
// event queue, and end each frame. The last two go the other way, SDL to GL.

extern int32_t sdl_events_winopen(char *title);

extern int32_t sdl_events_get_valuator(int32_t device);
extern Boolean sdl_events_get_button(int32_t button);

extern void sdl_events_qdevice(int32_t device);
extern Boolean sdl_events_device_queued(int32_t device);
extern void sdl_events_unqdevice(int32_t device);

extern uint32_t sdl_events_qread_start();
extern int32_t sdl_events_qread_block(void);
extern int32_t sdl_events_qread_continue(int16_t *value);

extern void sdl_events_tie(int32_t button, int32_t val1, int32_t val2);

extern void sdl_events_set_framebuffer(unsigned char* framebuffer);
extern void sdl_events_set_framebuffer_fixed_size(int32_t width, int32_t height);
extern void sdl_events_keepaspect(int32_t x, int32_t y);
extern void sdl_events_frame_complete(void);

extern void gl_framebuffer_resized(int width, int height);
extern void gl_exit(int status);

#endif /* __EVENTS_H__ */
