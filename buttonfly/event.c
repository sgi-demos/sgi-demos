/*
 *	event.c
 *	A more rational way to handle reading the event queue
 * Written by Wade Olsen
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <device.h>
#include "event.h"


typedef struct event_s
{
    int		window, device, state;
	void (*func)(void *, int);
	char *arg;
    struct event_s	*next;
} event_t, *event_p;

typedef struct update_s
{
    int *flag;
	void (*ufunc)(void *);
	char *arg;
    struct update_s *next;
} update_t, *update_p;


static event_p	    event_list;
static update_p    update_list;

/*
 * This routine adds an event to be checked for to the event queue.
 * window should be the wid of the window to respond in, or ANY if
 * this event applies to all windows.  device is the device, and state
 * is the device's value (e.g.  ANY, UP, DOWN, the window id (for
 * REDRAW), etc).  Func is the function that will be called, with
 * arguments 'arg' and the device's value.
 * 
 * NOTE:  the device must be queued for it to be found by the event()
 * routine-- add_event DOES NOT qdevice(device).
 */
void
add_event(window, device, state, func, arg)
int	window, device, state;
void (*func)(void *, int);
char *arg;
{
    event_p new_guy;

	new_guy = (event_p)malloc(sizeof(event_t));
    new_guy->window = window;
    new_guy->device = device;
    new_guy->state  = state;
    new_guy->func   = func;
    new_guy->arg    = arg;
    new_guy->next   = event_list;
    event_list = new_guy;
}

/*
 *	Specify a function to be called if there is nothing in the queue
 * and (*flag) is non-zero.  If no update function is active, or
 * (*flag) is 0, then event() will block on a qread.  If there is an
 * active update function, event() will continuously call the update
 * function, hogging the cpu.
 */
void
add_update(flag, ufunc, arg)
int	*flag;
void (*ufunc)(void *);
char *arg;
{
    update_p	new_guy;

    new_guy = (update_p)malloc(sizeof(update_t));
    new_guy->flag = flag;
    new_guy->ufunc = ufunc;
	new_guy->arg  = arg;
    new_guy->next = update_list;
    update_list = new_guy;
}

/*
 * The main Event.  Call this repeatedly to automagically handle
 * reading the queue, and calling your functions to handle what
 * appears there.
 */
void
event()
{
	void find_event(void), event_inputchange(void *, int);
	int find_update(void);
	static int initialized = 0;
	
	if (initialized == 0)
	{
		add_event(ANY, INPUTCHANGE, ANY, event_inputchange, NULL);
		qdevice(INPUTCHANGE);
		initialized = 1;
	}

	/* Something in the queue?  Handle it */
    if (qtest())
		find_event();
	/*
	 * Or, if there's no update function, wait for something to appear
	 */
    else if (find_update() == 0)
		find_event();
}

int
find_update()
{
    update_p	scan;
    int		updated = 0;

    for (scan = update_list; scan && updated == 0; scan = scan->next)
	{
		if (*scan->flag)
		{
		    (*scan->ufunc)(scan->arg);
		    updated = 1;
		}
	}

    return(updated);
}

int context, state, device;

void
event_inputchange(void *unused1, int unused2)
{
	context = winget();
}

void
find_event()
{
    event_p scan;
	short	s;

    device = qread(&s);
	state = s;
    for (scan = event_list; scan; scan = scan->next)
	{
		if ( ((scan->window == ANY) || (context == scan->window))
			&& ((scan->device == ANY) ||(device == scan->device))
			&& ((scan->state == ANY) || (state == scan->state)))
		{
		    (*scan->func)(scan->arg, state);
		}
	}
}
