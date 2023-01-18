#include <gl.h>
#include <device.h>

#include "arena.h"


int damage = 0;		/* amount of damage taken */
int explode_counter = 0;
int was_shot = FALSE;	/* was shot this frame */

hit_by(type)
    int type;
{
    switch(type)
    {
	case CANNON:
	    if (++damage >= 10)
	    {
		if (!(player[id].type & EXPLODE))
		{
		    player[id].type |= EXPLODE;
		    explode_counter = 10;
		    throttle = 0;
		    turn = 0;
		    setvaluator(MOUSEX, MOUSE_CENT,
				-200+MOUSE_CENT, 200+MOUSE_CENT);
		    setvaluator(MOUSEY, MOUSE_CENT,
				-100+MOUSE_CENT, 200+MOUSE_CENT);
		}
	    }
	    break;
	default:
	    break;
    }

    was_shot = TRUE;
}


restart()
{
    player[id].type = PLAYER;
    xpos = 64.0;
    zpos = -20.0;
    wrot = 0;
    speed = 0;
    throttle = 0;
    turn = 0;
    damage = 0;
    setvaluator(MOUSEX, MOUSE_CENT, -200+MOUSE_CENT, 200+MOUSE_CENT);
    setvaluator(MOUSEY, MOUSE_CENT, -100+MOUSE_CENT, 200+MOUSE_CENT);
}
