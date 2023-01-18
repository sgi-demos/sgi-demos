
#include "events.h"

// Do-nothing event stub.

int32_t events_winopen(char *title)
{
    // Nothing.
}

int32_t events_get_valuator(int32_t device)
{
    return 0;
}

void events_qdevice(int32_t device)
{
    // Nothing.
}

int32_t event_qread_start(int blocking)
{
    return 0;
}

int32_t events_qread_continue(int16_t *value)
{
    return 0;
}

void events_tie(int32_t button, int32_t val1, int32_t val2)
{
    // Nothing.
}
