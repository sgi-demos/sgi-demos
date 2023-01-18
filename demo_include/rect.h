/*
**	defines for area and xy utilities
**
*/ 
#ifndef PORT_RECT
#define PORT_RECT

#define MIN( a, b )	(((a) < (b)) ? (a) : (b))
#define MAX( a, b )	(((a) > (b)) ? (a) : (b))
#define ABS( a )	(((a) > 0) ? (a) : -(a))

typedef struct
{
    float x;
    float y;
} XY;

typedef struct 
{
    XY origin;
    XY corner;
} Rect;

XY xy();
Rect area();
Rect rectarea();
Rect makerect();
Rect intersect();
Rect legalport();
Rect trans();
Rect grow();
Rect shrink();
Rect movebottomedge();
Rect movetopedge();
Rect moveleftedge();
Rect moverightedge();
Rect screenarea();

#endif // PORT_RECT
