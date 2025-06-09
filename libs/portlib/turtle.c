/*
 *	turtle -
 * 		A simple implementation of turtle graphics.
 *
 *				Paul Haeberli - 1984
 *
 */
#include <math.h>
#include "gl.h"

#define RADIANS(a) ((a)*0.017453)
#define INVISIBLE -1
#define NONE -1

typedef int (*FUNPTR)();

static float lastx = 10000,
	     lasty = 10000,
	     lastz = 10000;

double xposition = 0.0;
double yposition = 0.0;
double zposition = 0.0;
double uposition = 0.0;
double vposition = 0.0;
double heading = 0.0;
int  penc = INVISIBLE;
int  pent = 0;
int  fillc = INVISIBLE;
int  fillt = 0;
int  tgpolypoints = 0;
float tgpoly[1000][3];

int drawline();

FUNPTR tg_line3 = drawline;

/*
**	CLEARSCREEN - erase the entire screen area.
*/
CLEARSCREEN()
{
    clear();
}

/*
**	MOVE - move some distance.
*/
MOVE( distance )
float distance;
{
    float x, y;

    x = uposition + distance * cos( RADIANS( heading ) );
    y = vposition + distance * sin( RADIANS( heading ) );
    MOVETO( x, y );
}

/*
**	MOVETO - move to a cartesian coordinate.
*/
MOVETO(x,y)
register float x,y;
{
    if (penc != INVISIBLE)
	tg_line3(uposition,vposition,0.0,x,y,0.0);
    uposition = x;
    vposition = y;
    tg_addpolypoint(x,y,0.0); 
}

/*
**	SPACETO - move to a point in 3 space.
*/
SPACETO( x, y, z )
double   x, y, z;
{
    if (penc != INVISIBLE)
	tg_line3(xposition,yposition,zposition,x,y,z);
    xposition = x;
    yposition = y;
    zposition = z;
    tg_addpolypoint(x,y,z);
}

/*
**	TURN - turn the turtle.
*/
TURN(angle)
float	angle;
{
    heading =  heading + angle;
    heading -= 360 * (int)( heading / 360.0 );
}

/*
**	TURNTO - turn to a specific angle.
*/
TURNTO(angle)
float	angle;
{
    heading =  angle;
    heading -= 360 * (int)(heading / 360.0);
}

/*
**	FILLCOLOR 
**	FILLTEXTURE
**	PENCOLOR
**	PENTYPE - change the fillcolor, filltexture, pencolor, and pentype.
*/
FILLCOLOR( fillcolor )
int fillcolor;
{
    fillc = fillcolor;
}

FILLTEXTURE( filltype )
int filltype;
{
    fillt = filltype;
}

PENCOLOR( threadcolor )
int threadcolor;
{
    penc = threadcolor;
    if (penc != INVISIBLE)
	color(penc); 
}

PENTYPE( threadtype )
int threadtype;
{
    pent = threadtype;
}

/*
**	WHATCOLOR - return the current color.	
*/
WHATCOLOR()
{
    return penc;
}

/*
**	WHEREAMI - return our current heading and position.
*/
WHEREAMI(x,y,h)
float *x,*y;
float *h;
{
    *x = uposition;
    *y = vposition;
    *h = heading;
}

/*
**	BEGINPOLY - start a polygon.
*/
BEGINPOLY()
{
    tgpolypoints = 0; 
}

/*
**	ENDPOLY - close and fill a polygon.
*/
ENDPOLY()
{
    polf((short)tgpolypoints,tgpoly);
}

/*
**	TEXT - put some text.
*/
TEXT( x, y, string )
float x, y;
char *string;
{
    cmov( x, y );
    charstr( string );
}

/*
**	VIEWPORT - set the viewport.
*/
VIEWPORT(x1,y1,x2,y2)
float x1,x2,y1,y2;
{
    viewport(x1,y1,x2,y2);
}

/*
**	WINDOW - set the window.
*/
WINDOW(x1,y1,x2,y2)
float x1,x2,y1,y2;
{
    ortho2(x1,y1,x2,y2); 
}

/*
**	draw a straight line in 3 space.
*/
drawline(x1,y1,z1,x2,y2,z2)
register float x1,y1,z1,x2,y2,z2;
{
    if ((x1 != lastx) || (y1 != lasty) || (z1 != lastz))
        move(x1,y1,z1);
    draw(x2,y2,z2);
    lastx = x2;
    lasty = y2;
    lastz = z2;
}

tg_addpolypoint( x, y, z )
float x, y, z;
{
    tgpoly[tgpolypoints][0] = x;
    tgpoly[tgpolypoints][1] = y;
    tgpoly[tgpolypoints][2] = z;
    tgpolypoints = (tgpolypoints+1) % 1000;
}
