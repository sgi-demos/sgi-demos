#ifndef __EVENT_SERVICE_H__
#define __EVENT_SERVICE_H__

#include "basic_types.h"
#define INPUT_QUEUE_SIZE 128

extern int32_t events_winopen(char *title, int32_t frame_width, int32_t frame_height);

extern int32_t events_get_valuator(int32_t device);
extern Boolean events_get_button(int32_t button);

extern void events_qdevice(int32_t device);
extern void events_unqdevice(int32_t device);

extern uint32_t events_qread_start();
extern int32_t events_qread_continue(int16_t *value);

extern void events_tie(int32_t button, int32_t val1, int32_t val2);

extern void events_set_framebuffer(unsigned char* framebuffer);

#endif /* __EVENT_SERVICE_H__ */
