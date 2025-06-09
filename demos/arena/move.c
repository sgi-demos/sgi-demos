
#include <stdlib.h>
#include <gl.h>
#include <math.h>

#include "arena.h"

#define GRAVITY -0.1
#define THRUST 	 0.1

float velocity = 0.0;
int speed = 0, throttle = 0;
int turn = 0;
int thrust = FALSE;

Coord xpos = 64.0, ypos = 0.0, zpos = -20.0;
float dy = 0.0;
Coord lastx = 64.0, lastz = -20.0;
Angle wrot = 0;

move_mech()
{
    Angle turn_add = turn >> 1;
    Angle max_turn = 200 / (abs(speed) / 20.0 + 2.0);

    lastx = xpos;
    lastz = zpos;

    if ((ypos != 0.0 && !(ypos == 2.0 && sect == INMAZE)) || thrust)
    {
	if (thrust)
	    dy += THRUST;
	else
	    dy += GRAVITY;
	
	if (dy > 1.0)
	    dy = 1.0;

	if (sect == INMAZE)
	{
	    if (ypos < 2.0)
	    {
		ypos += dy;
		if (ypos > 0.95)
		{
		    ypos = 0.95;
		    dy = -dy;
		    did_colide = TRUE;
		    player[id].type |= HIT_WALL;
		}
	        else if (ypos < 0.0)
		    ypos = dy = 0.0;
	    }
	    else
	    {
		ypos += dy;
		if (ypos < 2.0)
		{
		    ypos = 2.0;
		    dy = 0.0;
		}
	    }
	}
	else
	{
	    ypos += dy;
	    if (ypos < 0.0)
		ypos = dy = 0.0;
	}
    }
    else
    {
        if (turn >= 0)
	    wrot += (turn_add < max_turn)? turn_add : max_turn;
        else
	    wrot += (turn_add > -max_turn)? turn_add : -max_turn;
        if (wrot > 3600)
	    wrot -= 3600;
        else if (wrot < 0)
	    wrot += 3600;
    
        if (speed != throttle)
        {
	    if (speed < throttle - 20)
	        speed += 20;
	    else if (speed > throttle + 20)
	        speed -= 20;
	    else 
	        speed = throttle;
        }
    }


    player[id].torso_x_rot = ((abs(turn) < abs(speed))? abs(turn) : abs(speed))
			     * ((turn >= 0)? 1 : -1);
    player[id].torso_z_rot = -abs(speed);
    player[id].anckle_rot = -abs(speed);
    player[id].knee_rot = abs(speed) << 1;
    player[6].torso_z_rot = player[id].torso_z_rot;
    player[6].torso_x_rot = player[id].torso_x_rot;
    player[6].anckle_rot = player[id].anckle_rot;
    player[6].knee_rot = player[id].knee_rot;

    velocity = speed / 200.0;

    xpos += sin(wrot/1800.0 * PI) * velocity;
    zpos += cos(wrot/1800.0 * PI) * velocity;
    /*
    xpos += cos(wrot/1800.0 * PI) * velocity;
    zpos += sin(wrot/1800.0 * PI) * velocity;
    */
}
