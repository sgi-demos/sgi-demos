
#include <gl.h>
#include <stdio.h>
#include "arena.h"

#define MAXOBJ 100

struct thing player[MAXPLAYERS];
struct thing *sector[NUMSECTORS];


struct thing *sort_obj(list)
    struct thing *list;
{
    struct thing *sorted, *tmp, *tmp2;
    float r;			/* range */

    sorted = list;
    list = list->next;
    sorted->next = NULL;
    get_range(sorted);

    while (list != NULL)
    {
	tmp2 = list;
	list = list->next;

	r = get_range(tmp2);
	if (r > sorted->range)
	{
	    tmp2->next = sorted;
	    sorted = tmp2;
	}
	else
	{
	    for(tmp = sorted; tmp->next != NULL && r < tmp->next->range;
		tmp = tmp->next);
	    tmp2->next = tmp->next;
	    tmp->next = tmp2;
	}
    }
    return(sorted);
}



place_obj(obj)
    struct thing *obj;
{
    float xp = obj->xpos;
    float zp = obj->zpos;

    if (xp <= 0)
    {
	if (zp <= 0)			/* south west */
	{
	    obj->next = sector[SOUTHWEST];
	    sector[SOUTHWEST] = obj;
	}
	else if (zp <= MAZE)		/* west */
	{
	    obj->next = sector[WEST];
	    sector[WEST] = obj;
	}
	else				/* north west */
	{
	    obj->next = sector[NORTHWEST];
	    sector[NORTHWEST] = obj;
	}
    }
    else if (xp <= MAZE)
    {
	if (zp <= 0)			/* south */
	{
	    obj->next = sector[SOUTH];
	    sector[SOUTH] = obj;
	}
	else if (zp <= MAZE)		/* maze */
	{
	    if (obj->ypos < 2.0)
	    {
	        int pos = (((int)zp>>2)<<MSHIFT) + ((int)xp>>2);
	        obj->next = maze_obj[pos];
	        maze_obj[pos] = obj;
	        push_pos(pos);
	    }
	    else
	    {
	        obj->next = sector[INMAZE];
	        sector[INMAZE] = obj;
	    }
	}
	else				/* north */
	{
	    obj->next = sector[NORTH];
	    sector[NORTH] = obj;
	}
    }
    else
    {
	if (zp <= 0)			/* south east */
	{
	    obj->next = sector[SOUTHEAST];
	    sector[SOUTHEAST] = obj;
	}
	else if (zp <= MAZE)		/* east */
	{
	    obj->next = sector[EAST];
	    sector[EAST] = obj;
	}
	else				/* north east */
	{
	    obj->next = sector[NORTHEAST];
	    sector[NORTHEAST] = obj;
	}
    }
}


push_pos(pos)
    int pos;
{
    static int top = -1;
    static int stack[MAXOBJ];

    if (pos == -1)
    {
	for(;top >= 0; top--)		/* clear the stack */
	    maze_obj[stack[top]] = NULL;
    }
    else
	stack[++top] = pos;
}

visible(x1, x2, x3, x4, z1, z2, z3, z4)
    float x1, x2, x3, x4, z1, z2, z3, z4;
{
    short fbbuf[20];

    feedback(fbbuf, 10);
    {
	pnt(x1, ypos, z1);
	pnt(x2, ypos, z2);
	pnt(x3, ypos, z3);
	pnt(x4, ypos, z4);
    }
    if (1 || endfeedback(fbbuf))
	return TRUE;
    else
	return FALSE;
}


draw_obj(list)
    struct thing *list;
{
    struct thing *tmp;

    if (list)
    {
	for (tmp = sort_obj(list); tmp != NULL; tmp = tmp->next)
	{
	    if (tmp->type & PLAYER)
		draw_mech(tmp);
	    else
		draw_missile(tmp);
	}
    }
}


visible_sect(sect)
    int sect;
{
    short fbbuf[20];

    feedback(fbbuf, 10);
    switch(sect)
    {
	case INMAZE:
	    move(        0.0, ypos, 0.0);
	    draw((float)MAZE, ypos, 0.0);
	    draw((float)MAZE, ypos, (float)-MAZE);
	    draw(        0.0, ypos, (float)-MAZE);
	    draw(        0.0, ypos, 0.0);
	    break;
	case NORTH:
	    move(        0.0, ypos, (float)-MAZE);
	    draw((float)MAZE, ypos, (float)-MAZE);
	    draw((float)MAZE, ypos, (float)-(MAZE+BORDER));
	    draw(        0.0, ypos, (float)-(MAZE+BORDER));
	    draw(        0.0, ypos, (float)-MAZE);
	    break;
	case SOUTH:
	    move(        0.0, ypos, 0.0);
	    draw((float)MAZE, ypos, 0.0);
	    draw((float)MAZE, ypos, (float)BORDER);
	    draw(        0.0, ypos, (float)BORDER);
	    draw(        0.0, ypos, 0.0);
	    break;
	case EAST:
	    move(       (float)MAZE, ypos, 0.0);
	    draw(       (float)MAZE, ypos, (float)-MAZE);
	    draw((float)MAZE+BORDER, ypos, (float)-MAZE);
	    draw((float)MAZE+BORDER, ypos, 0.0);
	    draw(       (float)MAZE, ypos, 0.0);
	    break;
	case WEST:
	    move(           0.0, ypos, 0.0);
	    draw((float)-BORDER, ypos, 0.0);
	    draw((float)-BORDER, ypos, (float)-MAZE);
	    draw(           0.0, ypos, (float)-MAZE);
	    draw(           0.0, ypos, 0.0);
	    break;
	case NORTHWEST:
	    move(           0.0, ypos, (float)-MAZE);
	    draw((float)-BORDER, ypos, (float)-MAZE);
	    draw((float)-BORDER, ypos, (float)-(MAZE+BORDER));
	    draw(           0.0, ypos, (float)-(MAZE+BORDER));
	    draw(           0.0, ypos, (float)-MAZE);
	    break;
	case NORTHEAST:
	    move(       (float)MAZE, ypos, (float)-MAZE);
	    draw(       (float)MAZE, ypos, (float)-(MAZE+BORDER));
	    draw((float)MAZE+BORDER, ypos, (float)-(MAZE+BORDER));
	    draw((float)MAZE+BORDER, ypos, (float)-MAZE);
	    draw(       (float)MAZE, ypos, (float)-MAZE);
	    break;
	case SOUTHWEST:
	    move(           0.0, ypos, (float)BORDER);
	    draw((float)-BORDER, ypos, (float)BORDER);
	    draw((float)-BORDER, ypos, 0.0);
	    draw(           0.0, ypos, 0.0);
	    draw(           0.0, ypos, (float)BORDER);
	    break;
	case SOUTHEAST:
	    move(       (float)MAZE, ypos, (float)BORDER);
	    draw(       (float)MAZE, ypos, 0.0);
	    draw((float)MAZE+BORDER, ypos, 0.0);
	    draw((float)MAZE+BORDER, ypos, (float)BORDER);
	    draw(       (float)MAZE, ypos, (float)BORDER);
	    break;
	default:
	    break;
    }
    if (1 || endfeedback(fbbuf))
	return TRUE;
    else
	return FALSE;
}


get_obj_sect(obj)
    struct thing *obj;
{
    obj->last_sect = obj->sect;
    if (obj->xpos <= 0)
    {
	if (obj->zpos <= 0)		/* south west */
	    obj->sect = SOUTHWEST;
	else if (obj->zpos <= MAZE)	/* west */
	    obj->sect = WEST;
	else			/* north west */
	    obj->sect = NORTHWEST;
    }
    else if (obj->xpos <= MAZE)
    {
	if (obj->zpos <= 0)		/* south */
	    obj->sect = SOUTH;
	else if (obj->zpos <= MAZE)	/* maze */
	    obj->sect = INMAZE;
	else			/* north */
	    obj->sect = NORTH;
    }
    else
    {
	if (obj->zpos <= 0)		/* south east */
	    obj->sect = SOUTHEAST;
	else if (obj->zpos <= MAZE)	/* east */
	    obj->sect = EAST;
	else			/* north east */
	    obj->sect = NORTHEAST;
    }
}

