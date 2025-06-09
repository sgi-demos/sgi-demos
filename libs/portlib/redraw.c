/*
 *	redraw -
 *		Test for a redraw token in the queue, and if present, 
 *		swallow it and call the optionally supplied user function 
 *		as well as the code to reshape the viewport based on the 
 *		new size.
 *
 *				Kipp Hickman - 1985
 *
 */
#include "gl.h"
#include "device.h"

redraw(f)
    int (*f)();
{
    int retval;
    short v;

    retval = 0;
    while (qtest()) {
	switch (qread(&v)) {
	    case REDRAW:
		reshapeviewport();
		if (f)
		    (*f)();
		retval = 1;
		break;
	}
    }
    return retval;
}
