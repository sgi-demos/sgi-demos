/*
 *	subview -
 *		Some support for viewports inside the graph port.
 *
 *				Henry Moreton - 1984
 *
 */
#include "gl.h"

subviewport(left, right, bottom, top)
long left, right, bottom, top;
{
    subport((float)left/XMAXSCREEN, (float)right/XMAXSCREEN, 
	     (float)bottom/YMAXSCREEN, (float)top/YMAXSCREEN);
}

subport(left, right, bottom, top)
float left, right, bottom, top;
{
    int	curr_left, curr_right, curr_bottom, curr_top;
    int	new_left, new_right, new_bottom, new_top;
    int width, height;

    getviewport(&curr_left,&curr_right,&curr_bottom,&curr_top);

    /* calculate the new viewport size and position based on the
    current viewport and the requested subviewport */

    height = (curr_top - curr_bottom);
    width = (curr_right - curr_left);
    new_right = curr_left + (right * width);
    new_left = curr_left + (left * width);
    new_top = curr_bottom + (top * height);
    new_bottom = curr_bottom + (bottom * height);
    viewport(new_left, new_right, new_bottom, new_top);
}
