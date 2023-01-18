
#include <gl.h>
#include <stdio.h>
#include <math.h>
#include <device.h>

#include "arena.h"


#define N_EDGE (mis->lastz < (MAZE-WL))
#define S_EDGE (mis->lastz > WL)
#define E_EDGE (mis->lastx < (MAZE-WL))
#define W_EDGE (mis->lastx > WL)

#define CANNON_SPEED 800


struct thing shots[MAXPLAYERS][3];
struct thing *shot;
Object cannon, cannon_hit[3];


fire_missile(type)
    int type;
{
    int i;

    for(i = 0; i < 3 && shot[i].type != NOTHING; i++);
    if (i < 3)
    {
	shot[i].type = type | i;
	shot[i].id = id;
	shot[i].xpos = xpos;
	shot[i].ypos = ypos + 0.7;
	shot[i].zpos = zpos;
	shot[i].yrot = wrot;
	shot[i].sect = sect;
	shot[i].last_sect = sect;
    }
}


make_missiles()
{
    makeobj(cannon = genobj());
    {
	color(RED);
	move(0.0, 0.0, 0.0);
	draw(0.0, 0.0, 0.3);
    }
    closeobj();

    /*
    makeobj(cannon_hit[0] = genobj());
    {
	color(RED);
	move( 0.00,  0.00, 0.00);
	draw(-0.06,  0.06, 0.10);
	move( 0.00,  0.00, 0.00);
	draw( 0.06,  0.06, 0.10);
	move( 0.00,  0.00, 0.00);
	draw(-0.06, -0.06, 0.10);
	move( 0.00,  0.00, 0.00);
	draw( 0.06, -0.06, 0.10);
    }
    closeobj();
    */

    makeobj(cannon_hit[0] = genobj());
    {
	color(RED);
	move( 0.00,  0.00, 0.00);
	draw(-0.02,  0.08, 0.09);
	move( 0.00,  0.00, 0.00);
	draw(-0.06,  0.01, 0.10);
	move( 0.00,  0.00, 0.00);
	draw( 0.07,  0.01, 0.10);
	move( 0.00,  0.00, 0.00);
	draw( 0.03,  0.08, 0.10);
	move( 0.00,  0.00, 0.00);
	draw(-0.07, -0.08, 0.11);
	move( 0.00,  0.00, 0.00);
	draw( 0.05, -0.07, 0.04);
	move( 0.00,  0.00, 0.00);
	draw(-0.01, -0.10, 0.04);
    }
    closeobj();

    makeobj(cannon_hit[1] = genobj());
    {
	color(RED);
	move( 0.00,  0.00, 0.00);
	draw(-0.01,  0.10, 0.10);
	move( 0.00,  0.00, 0.00);
	draw(-0.07,  0.03, 0.11);
	move( 0.00,  0.00, 0.00);
	draw( 0.05,  0.02, 0.05);
	move( 0.00,  0.00, 0.00);
	draw( 0.04,  0.06, 0.11);
	move( 0.00,  0.00, 0.00);
	draw(-0.08, -0.09, 0.11);
	move( 0.00,  0.00, 0.00);
	draw( 0.06, -0.06, 0.06);
	move( 0.00,  0.00, 0.00);
	draw(-0.02, -0.09, 0.07);
    }
    closeobj();

    makeobj(cannon_hit[2] = genobj());
    {
	color(RED);
	move( 0.00,  0.00, 0.00);
	draw(-0.04,  0.07, 0.05);
	move( 0.00,  0.00, 0.00);
	draw(-0.08,  0.06, 0.11);
	move( 0.00,  0.00, 0.00);
	draw( 0.04,  0.10, 0.11);
	move( 0.00,  0.00, 0.00);
	draw( 0.07,  0.03, 0.08);
	move( 0.00,  0.00, 0.00);
	draw(-0.09, -0.07, 0.09);
	move( 0.00,  0.00, 0.00);
	draw( 0.09, -0.06, 0.11);
	move( 0.00,  0.00, 0.00);
	draw(-0.03, -0.07, 0.10);
    }
    closeobj();
}


draw_missile(mis)
    struct thing *mis;
{
    if (mis->type & DEATH)
	return;
    pushmatrix();
    translate(mis->xpos, mis->ypos, -(mis->zpos));
    rotate(-(mis->yrot), 'y');
    switch(mis->type & MISSILE)
    {
	case CANNON:
	    if (mis->type & DID_HIT)
	    {
		rotate(ROLL(3600), 'z');
		callobj(cannon_hit[ROLL(3)]);
		rotate(ROLL(3600), 'z');
		callobj(cannon_hit[ROLL(3)]);
	    }
	    else
		callobj(cannon);
	    break;
	default:
	    break;
    }
    popmatrix();
}


move_missile(mis)
    struct thing *mis;
{
    float velocity = 0.0;

    mis->lastx = mis->xpos;
    mis->lastz = mis->zpos;

    velocity = CANNON_SPEED / 200.0;

    mis->xpos += sin(mis->yrot/1800.0 * PI) * velocity;
    mis->zpos += cos(mis->yrot/1800.0 * PI) * velocity;
}



m_check_colision(mis)
   struct thing *mis;
{
    int col = FALSE;

    switch(mis->last_sect)
    {
        case INMAZE:
	if (mis->ypos < 2.0)
        {
	    float x = mis->lastx - (int)(mis->lastx / 4.0) * 4.0;
	    float z = mis->lastz - (int)(mis->lastz / 4.0) * 4.0;
	    float x1 = ((int)mis->lastx >> SHIFT) * 4.0;
	    float z1 = ((int)mis->lastz >> SHIFT) * 4.0;
	    float x2 = x1 + 4.0;
	    float z2 = z1 + 4.0;
	    int pos = (((int)mis->lastz >> SHIFT) << MSHIFT) +
		      ((int)mis->lastx >> SHIFT);
    
	    if (mis->yrot >= 0  && mis->yrot < 900)
	        {
		    if (maze_w[pos][N] &&
		        m_intersect_NS(mis, x1, x2, z2))
		        col = TRUE;
		    if (maze_w[pos][E] &&
		        m_intersect_EW(mis, x2, z1, z2))
		        col = TRUE;
		    if (!maze_w[pos][E] && E_EDGE && maze_w[pos+1][N] &&
		        m_intersect_NS(mis, x2, x2+4.0, z2))
		        col = TRUE;
		    if (!maze_w[pos][N] && N_EDGE && maze_w[pos+MSIZ][E] &&
		        m_intersect_EW(mis, x2, z2, z2+4.0))
		        col = TRUE;
	        }
	    else if (mis->yrot >= 900  && mis->yrot < 1800)
	        {
		    if (maze_w[pos][S] &&
		        m_intersect_NS(mis, x1, x2, z1))
		        col = TRUE;
		    if (maze_w[pos][E] &&
		        m_intersect_EW(mis, x2, z1, z2))
		        col = TRUE;
		    if (!maze_w[pos][E] && E_EDGE && maze_w[pos+1][S] &&
		        m_intersect_NS(mis, x2, x2+4.0, z1))
		        col = TRUE;
		    if (!maze_w[pos][S] && S_EDGE && maze_w[pos-MSIZ][E] &&
		        m_intersect_EW(mis, x2, z1-4.0, z1))
		        col = TRUE;
	        }
	    else if (mis->yrot >= 1800  && mis->yrot < 2700)
	        {
		    if (maze_w[pos][S] &&
		        m_intersect_NS(mis, x1, x2, z1))
		        col = TRUE;
		    if (maze_w[pos][W] &&
		        m_intersect_EW(mis, x1, z1, z2))
		        col = TRUE;
		    if (!maze_w[pos][W] && W_EDGE && maze_w[pos-1][S] &&
		        m_intersect_NS(mis, x1-4.0, x1, z1))
		        col = TRUE;
		    if (!maze_w[pos][S] && S_EDGE && maze_w[pos-32][W] &&
		        m_intersect_EW(mis, x1, z1-4.0, z1))
		        col = TRUE;
	        }
	    else
	        {
		    if (maze_w[pos][N] &&
		        m_intersect_NS(mis, x1, x2, z2))
		        col = TRUE;
		    if (maze_w[pos][W] &&
		        m_intersect_EW(mis, x1, z1, z2))
		        col = TRUE;
		    if (!maze_w[pos][W] && W_EDGE && maze_w[pos-1][N] &&
		        m_intersect_NS(mis, x1-4.0, x1, z2))
		        col = TRUE;
		    if (!maze_w[pos][N] && N_EDGE && maze_w[pos+32][W] &&
		        m_intersect_EW(mis, x1, z2, z2+4.0))
		        col = TRUE;
	        }
        }
	    break;
        case NORTH:
	    if (mis->ypos < 2.0)
	    {
	        if (m_intersect_NS(mis, 0.0, (float)((MAZE>>1)-WL),
				   (float)MAZE))
		    col = TRUE;
	        if (m_intersect_NS(mis, (float)((MAZE>>1)+WL), (float)MAZE,
				   (float)MAZE))
		    col = TRUE;
	    }
	    if (m_intersect_NS(mis, (float)-BORDER, (float)MAZE+BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case EAST:
	    if (mis->ypos < 2.0)
	    {
	        if (m_intersect_EW(mis, (float)MAZE, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (m_intersect_EW(mis, (float)MAZE+BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case SOUTH:
	    if (mis->ypos < 2.0)
	    {
	        if (m_intersect_NS(mis, 0.0, (float)((MAZE>>1)-WL), 0.0))
		    col = TRUE;
	        if (m_intersect_NS(mis, (float)((MAZE>>1)+WL), (float)MAZE,
				   0.0))
		    col = TRUE;
	    }
	    if (m_intersect_NS(mis, (float)-BORDER, (float)MAZE+BORDER,
			     (float)-BORDER))
		col = TRUE;
	    break;
        case WEST:
	    if (mis->ypos < 2.0)
	    {
	        if (m_intersect_EW(mis, 0.0, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (m_intersect_EW(mis, (float)-BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case NORTHEAST:
	    if (mis->ypos < 2.0)
	    {
	        if (m_intersect_NS(mis, (float)((MAZE>>1)+WL), (float)MAZE,
				   (float)MAZE))
		    col = TRUE;
	        if (m_intersect_EW(mis, (float)MAZE, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (m_intersect_NS(mis, (float)-BORDER, (float)MAZE+BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    if (m_intersect_EW(mis, (float)MAZE+BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case SOUTHEAST:
	    if (mis->ypos < 2.0)
	    {
	        if (m_intersect_NS(mis, (float)((MAZE>>1)+WL), (float)MAZE,
				   0.0))
		    col = TRUE;
	        if (m_intersect_EW(mis, (float)MAZE, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (m_intersect_NS(mis, (float)-BORDER, (float)MAZE+BORDER,
			     (float)-BORDER))
		col = TRUE;
	    if (m_intersect_EW(mis, (float)MAZE+BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case NORTHWEST:
	    if (mis->ypos < 2.0)
	    {
	        if (m_intersect_NS(mis, 0.0, (float)((MAZE>>1)-WL),
				   (float)MAZE))
		    col = TRUE;
	        if (m_intersect_EW(mis, 0.0, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (m_intersect_NS(mis, (float)-BORDER, (float)MAZE+BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    if (m_intersect_EW(mis, (float)-BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case SOUTHWEST:
	    if (mis->ypos < 2.0)
	    {
	        if (m_intersect_NS(mis, 0.0, (float)((MAZE>>1)-WL), 0.0))
		    col = TRUE;
	        if (m_intersect_EW(mis, 0.0, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (m_intersect_NS(mis, (float)-BORDER, (float)MAZE+BORDER,
			     (float)-BORDER))
		col = TRUE;
	    if (m_intersect_EW(mis, (float)-BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
	default:
	    break;
    }
    return col;
}


m_intersect_NS(mis, x1, x2, z)
    struct thing *mis;
    float x1, x2, z;
{
    float i;

    if ((mis->lastz >= z && mis->zpos <= z) ||
	(mis->lastz <= z && mis->zpos >= z))
	{
	    i = ((z - mis->lastz) / (mis->zpos - mis->lastz)) *
		(mis->xpos - mis->lastx) + mis->lastx;
	    if (i >= x1 && i <= x2)
	    {
		mis->xpos = i;
		if (lastz < z)
		    mis->zpos = z - 0.01;
		else
		    mis->zpos = z + 0.01;
		return TRUE;
	    }
	    else
		return FALSE;
	}
    else
	return FALSE;
}


m_intersect_EW(mis, x, z1, z2)
    struct thing *mis;
    float x, z1, z2;
{
    float i;

    if ((mis->lastx > x && mis->xpos < x) ||
	(mis->lastx < x && mis->xpos > x))
	{
	    i = ((x - mis->lastx) / (mis->xpos - mis->lastx)) *
		(mis->zpos - mis->lastz) + mis->lastz;
	    if (i >= z1 && i <= z2)
	    {
		mis->zpos = i;
		if (lastx < x)
		    mis->xpos = x - 0.01;
		else
		    mis->xpos = x + 0.01;
		return TRUE;
	    }
	    else
		return FALSE;
	}
    else
	return FALSE;
}


m_colide_obj(mis, list)
    struct thing *mis, *list;
{
    float r;
    float i;
    float x, z, xdif, zdif, xrat, zrat;
    int col = FALSE;

    for(; list != NULL; list = list->next)
    {
	if ((list->type & PLAYER) && !(list->type & DEAD))
	{
	    if (fabs((list->ypos+0.5) - mis->ypos) > 0.5)
		continue;

	    z = list->zpos;
	    x = list->xpos;
    
	    if (((mis->lastz <= z + 0.25 && mis->zpos >= z - 0.25) ||
		 (mis->lastz >= z - 0.25 && mis->zpos <= z + 0.25)) &&
		((mis->lastx <= x + 0.25 && mis->xpos >= x - 0.25) ||
		 (mis->lastx >= x - 0.25 && mis->xpos <= x + 0.25)))
	    {
		if (mis->yrot >= 0 && mis->yrot < 900)
		{
		    if (m_intersect_EW(mis, x-.2, z-.2, z+.2) ||
			m_intersect_NS(mis, x-.2, x+.2, z-.2))
		    {
			mis->type = (mis->type & CLEAR_WHAT) |
				    (list->id << WHAT_SHIFT);
			return TRUE;
		    }
		}
		else if (mis->yrot >= 900 && mis->yrot < 1800)
		{
		    if (m_intersect_EW(mis, x-.2, z-.2, z+.2) ||
			m_intersect_NS(mis, x-.2, x+.2, z+.2))
		    {
			mis->type = (mis->type & CLEAR_WHAT) |
				    (list->id << WHAT_SHIFT);
			return TRUE;
		    }
		}
		else if (mis->yrot >= 1800 && mis->yrot < 2700)
		{
		    if (m_intersect_EW(mis, x+.2, z-.2, z+.2) ||
			m_intersect_NS(mis, x-.2, x+.2, z+.2))
		    {
			mis->type = (mis->type & CLEAR_WHAT) |
				    (list->id << WHAT_SHIFT);
			return TRUE;
		    }
		}
		else 
		{
		    if (m_intersect_EW(mis, x+.2, z-.2, z+.2) ||
			m_intersect_NS(mis, x-.2, x+.2, z-.2))
		    {
			mis->type = (mis->type & CLEAR_WHAT) |
				    (list->id << WHAT_SHIFT);
			return TRUE;
		    }
		}
	    }
	}
    }
    return FALSE;
}


m_check_obj_colision(mis)
    struct thing *mis;
{
    int col = FALSE;

    switch(mis->last_sect)
    {
        case INMAZE:
	if (mis->ypos > 2.0)
	{
	    if (m_colide_obj(mis, sector[INMAZE]))
		return TRUE;
	}
	else
        {
	    float x = mis->lastx - (int)(mis->lastx / 4.0) * 4.0;
	    float z = mis->lastz - (int)(mis->lastz / 4.0) * 4.0;
	    int pos = (((int)mis->lastz >> SHIFT) << MSHIFT) +
		      ((int)mis->lastx >> SHIFT);
    
	    if (m_colide_obj(mis, maze_obj[pos]))
	        return TRUE;
	    if (mis->yrot >= 0 && mis->yrot < 900)
	    {
		if (!maze_w[pos][E] && (mis->xpos < (MAZE-WL)) &&
		    m_colide_obj(mis, maze_obj[pos+1]))
		    return TRUE;
		if (!maze_w[pos][N] && (mis->zpos < (MAZE-WL)) &&
		    m_colide_obj(mis, maze_obj[pos+MSIZ]))
		    return TRUE;
	    }
	    else if (mis->yrot >= 900 && mis->yrot < 1800)
	    {
		if (!maze_w[pos][E] && (mis->xpos < (MAZE-WL)) &&
		    m_colide_obj(mis, maze_obj[pos+1]))
		    return TRUE;
		if (!maze_w[pos][S] && (mis->zpos > WL) &&
		    m_colide_obj(mis, maze_obj[pos-MSIZ]))
		    return TRUE;
	    }
	    else if (mis->yrot >= 1800 && mis->yrot < 2700)
	    {
		if (!maze_w[pos][W] && (mis->xpos > WL) &&
		    m_colide_obj(mis, maze_obj[pos-1]))
		    return TRUE;
		if (!maze_w[pos][S] && (mis->zpos > WL) &&
		    m_colide_obj(mis, maze_obj[pos-MSIZ]))
		    return TRUE;
	    }
	    else 
	    {
		if (!maze_w[pos][N] && (mis->zpos < (MAZE-WL)) &&
		    m_colide_obj(mis, maze_obj[pos+MSIZ]))
		    return TRUE;
		if (!maze_w[pos][W] && (mis->xpos > WL) &&
		    m_colide_obj(mis, maze_obj[pos-1]))
		    return TRUE;
	    }
	}
	    break;
        case NORTH:
	    if (m_colide_obj(mis, sector[NORTH]))
	        return TRUE;
	    if (mis->xpos > MAZE-4.0 && m_colide_obj(mis, sector[NORTHWEST]))
		return TRUE;
	    if (mis->xpos < 4.0 && m_colide_obj(mis, sector[NORTHEAST]))
		return TRUE;
	    break;
        case EAST:
	    if (m_colide_obj(mis, sector[EAST]))
	        return TRUE;
	    if (mis->zpos < 4.0 && m_colide_obj(mis, sector[SOUTHEAST]))
		return TRUE;
	    if (mis->zpos > MAZE-4.0 && m_colide_obj(mis, sector[NORTHEAST]))
		return TRUE;
	    break;
        case SOUTH:
	    if (m_colide_obj(mis, sector[SOUTH]))
	        return TRUE;
	    if (mis->xpos > MAZE-4.0 && m_colide_obj(mis, sector[SOUTHWEST]))
		return TRUE;
	    if (mis->xpos < 4.0 && m_colide_obj(mis, sector[SOUTHEAST]))
		return TRUE;
	    break;
        case WEST:
	    if (m_colide_obj(mis, sector[WEST]))
	        return TRUE;
	    if (mis->zpos < 4.0 && m_colide_obj(mis, sector[SOUTHWEST]))
		return TRUE;
	    if (mis->zpos > MAZE-4.0 && m_colide_obj(mis, sector[NORTHWEST]))
		return TRUE;
	    break;
        case NORTHEAST:
	    if (m_colide_obj(mis, sector[NORTHEAST]))
	        return TRUE;
	    if (mis->xpos < MAZE+4.0 && m_colide_obj(mis, sector[NORTH]))
		return TRUE;
	    if (mis->zpos < MAZE+4.0 && m_colide_obj(mis, sector[EAST]))
		return TRUE;
	    break;
        case SOUTHEAST:
	    if (m_colide_obj(mis, sector[SOUTHEAST]))
	        return TRUE;
	    if (mis->xpos < MAZE+4.0 && m_colide_obj(mis, sector[SOUTH]))
		return TRUE;
	    if (mis->zpos > -4.0 && m_colide_obj(mis, sector[EAST]))
		return TRUE;
	    break;
        case NORTHWEST:
	    if (m_colide_obj(mis, sector[NORTHWEST]))
	        return TRUE;
	    if (mis->xpos > -4.0 && m_colide_obj(mis, sector[NORTH]))
		return TRUE;
	    if (mis->zpos < MAZE+4.0 && m_colide_obj(mis, sector[WEST]))
		return TRUE;
	    break;
        case SOUTHWEST:
	    if (m_colide_obj(mis, sector[SOUTHWEST]))
	        return TRUE;
	    if (mis->xpos > -4.0 && m_colide_obj(mis, sector[SOUTH]))
		return TRUE;
	    if (mis->zpos > -4.0 && m_colide_obj(mis, sector[WEST]))
		return TRUE;
	    break;
	default:
	    break;
    }
    return FALSE;
}


do_shots()
{
    int i;

    for (i = 0; i < 3; i++)
	if (shot[i].type)
	{
	    if (shot[i].type & DEATH)
		shot[i].type = NOTHING;
	    else if (shot[i].type & DID_HIT)
		shot[i].type |= DEATH;
	    else
	    {
		move_missile(&shot[i]);
		get_obj_sect(&shot[i]);
		if (m_check_colision(&shot[i]))
		{
		    shot[i].type |= DID_HIT | HIT_WALL;
		}
		if (m_check_obj_colision(&shot[i]))
		{
		    shot[i].type |= DID_HIT;
		}
	    }
	}
}


