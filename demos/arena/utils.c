
#include <gl.h>
#include <device.h>
#include <math.h>

#include "arena.h"

#define PI 3.14159265


abs(i)
    int i;
{
    if (i >= 0)
	return(i);
    else
	return(-i);
}


float get_range(obj)
    struct thing *obj;
{
    float x, z;
    float fa;		/* floating point angle */
    Angle ia;		/* intager angle */

    x = obj->xpos - xpos;
    z = obj->zpos - zpos;
    if (x > 0)
	fa = atan(z/x);
    else if (x < 0)
	fa = atan(z/x) + PI;
    else /* (x == 0) */
	if (z > 0)
	    fa = 0.5 * PI;
	else
	    fa = -0.5 * PI;
    ia= (3600 / (PI * 2.0)) * fa;
    if (ia < 0)
	ia += 3600;
    obj->rel_rot = (ia + obj->yrot) % 3600;
    obj->range = sqrt(pow(fabs(x), 2.0) + pow(fabs(z), 2.0));
    return(obj->range);
}



wait()
{
    while(!getbutton(LEFTMOUSE));
    while(getbutton(LEFTMOUSE));
}
