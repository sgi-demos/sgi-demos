#ifndef __EVENT_SERVICE_H__
#define __EVENT_SERVICE_H__

#include "basic_types.h"

int32_t events_winopen(char *title);

int32_t events_get_valuator(int32_t device);
void events_qdevice(int32_t device);
int32_t events_qread_start(int blocking);
int32_t events_qread_continue(int16_t *value);
void events_tie(int32_t button, int32_t val1, int32_t val2);

#endif /* __EVENT_SERVICE_H__ */
