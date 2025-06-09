/*
 *	rectlib -
 *		A set of functions to operate on rectanges.
 *
 *				Paul Haeberli - 1985
 *
 */
#include "rect.h"

/*
 *	xy - return an xy pair
 *
 */
XY xy(x,y)
float x, y;
{
    XY p;

    p.x = x;
    p.y = y;
    return p;
}

/*
 *	makerect - return a rect with the given origin and corner
 *
 */
Rect makerect( origin, corner )
XY origin, corner;
{
    Rect a;

    a.origin = origin;
    a.corner = corner;
    return a;
}

/*
 *	rectarea - return a rect given x1, x2, y1, y2
 *
 */
Rect rectarea( x1, x2, y1, y2 )
float x1, x2, y1, y2;
{
    Rect a;

    a.origin.x = MIN(x1,x2);
    a.origin.y = MIN(y1,y2);
    a.corner.x = MAX(x1,x2);
    a.corner.y = MAX(y1,y2);
    return a;
}

/*
** 	intersect - return the intersection of two rects. a zero size rect
**		    is returned if the rects don't overlap.
**
*/
Rect intersect( a, b )
Rect a, b;
{
    Rect i;
    float axmin, axmax, aymin, aymax;
    float bxmin, bxmax, bymin, bymax;
    float ixmin, ixmax, iymin, iymax;

    axmin = a.origin.x;
    axmax = a.corner.x;
    aymin = a.origin.y;
    aymax = a.corner.y;
    bxmin = b.origin.x;
    bxmax = b.corner.x;
    bymin = b.origin.y;
    bymax = b.corner.y;
    ixmin = MAX(axmin,bxmin);
    ixmax = MIN(axmax,bxmax);
    iymin = MAX(aymin,bymin);
    iymax = MIN(aymax,bymax);
    if (ixmin >= ixmax || iymin >= iymax) {
	i.origin.x = 0.0;
	i.origin.y = 0.0;
	i.corner.x = 0.0;
	i.corner.y = 0.0;
    } else
	i = rectarea(ixmin,ixmax,iymin,iymax);
    return i;
}

/*
 *	printrect - print the center and size of a rect
 *
 */
printrect( a )
Rect a;
{
    printf("origin.x: %f\n",a.origin.x);
    printf("origin.y: %f\n",a.origin.y);
    printf("corner.x: %f\n",a.corner.x);
    printf("corner.y: %f\n",a.corner.y);
}

/*
 *	trans - translate a rect
 *
 */
Rect trans( a, pnt )
Rect a;
XY pnt;
{
    a.origin.x += pnt.x;
    a.corner.x += pnt.x;
    a.origin.y += pnt.y;
    a.corner.y += pnt.y;
    return a;
}

/*
 *	grow - make a rect bigger
 *
 */
Rect grow( a, amount )
Rect a; 
float amount;
{
    amount /= 2.0;
    a.origin.x -= amount;
    a.origin.y -= amount;
    a.corner.x += amount;
    a.corner.y += amount;
    return a;
}

/*
 *	shrink - make a rect smaller
 *
 */
Rect shrink( a, amount )
Rect a; 
float amount;
{
    return grow(a,-amount);
}

/*
**	movebottomedge
**	movetopedge
**	moveleftedge
**	moverightedge - Move the edges out or in.
**
*/
Rect movebottomedge( a, amount )
Rect a; 
float amount;
{
    a.origin.y += amount;
    return a;
}

Rect movetopedge( a, amount )
Rect a; 
float amount;
{
    a.corner.y += amount;
    return a;
}

Rect moveleftedge( a, amount )
Rect a; 
float amount;
{
    a.origin.x += amount;
    return a;
}

Rect moverightedge( a, amount )
Rect a; 
float amount;
{
    a.corner.x += amount;
    return a;
}
