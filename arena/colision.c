
#include <gl.h>
#include <stdio.h>
#include <math.h>
#include <device.h>

#include "arena.h"


#define N_EDGE (lastz < (MAZE-WL))
#define S_EDGE (lastz > WL)
#define E_EDGE (lastx < (MAZE-WL))
#define W_EDGE (lastx > WL)


check_colision()
{
    int col = FALSE;

    switch(last_sect)
    {
        case INMAZE:
	if (ypos < 2.0)
        {
	    float x = lastx - (int)(lastx / 4.0) * 4.0;
	    float z = lastz - (int)(lastz / 4.0) * 4.0;
	    float x1 = ((int)lastx >> SHIFT) * 4.0;
	    float z1 = ((int)lastz >> SHIFT) * 4.0;
	    float x2 = x1 + 4.0;
	    float z2 = z1 + 4.0;
	    int pos = (((int)lastz >> SHIFT) << MSHIFT) + ((int)lastx >> SHIFT);
    
	    if (x > 2.0)
	        if (z > 2.0)
	        {
		    if (maze_w[pos][N] &&
		        intersect_NS(x1, x2, z2))
		        col = TRUE;
		    if (maze_w[pos][E] &&
		        intersect_EW(x2, z1, z2))
		        col = TRUE;
		    if (!maze_w[pos][E] && E_EDGE && maze_w[pos+1][N] &&
		        intersect_NS(x2, x2+4.0, z2))
		        col = TRUE;
		    if (!maze_w[pos][N] && N_EDGE && maze_w[pos+MSIZ][E] &&
		        intersect_EW(x2, z2, z2+4.0))
		        col = TRUE;
	        }
	        else
	        {
		    if (maze_w[pos][S] &&
		        intersect_NS(x1, x2, z1))
		        col = TRUE;
		    if (maze_w[pos][E] &&
		        intersect_EW(x2, z1, z2))
		        col = TRUE;
		    if (!maze_w[pos][E] && E_EDGE && maze_w[pos+1][S] &&
		        intersect_NS(x2, x2+4.0, z1))
		        col = TRUE;
		    if (!maze_w[pos][S] && S_EDGE && maze_w[pos-MSIZ][E] &&
		        intersect_EW(x2, z1-4.0, z1))
		        col = TRUE;
	        }
	    else
	        if (z > 2.0)
	        {
		    if (maze_w[pos][N] &&
		        intersect_NS(x1, x2, z2))
		        col = TRUE;
		    if (maze_w[pos][W] &&
		        intersect_EW(x1, z1, z2))
		        col = TRUE;
		    if (!maze_w[pos][W] && W_EDGE && maze_w[pos-1][N] &&
		        intersect_NS(x1-4.0, x1, z2))
		        col = TRUE;
		    if (!maze_w[pos][N] && N_EDGE && maze_w[pos+32][W] &&
		        intersect_EW(x1, z2, z2+4.0))
		        col = TRUE;
	        }
	        else
	        {
		    if (maze_w[pos][S] &&
		        intersect_NS(x1, x2, z1))
		        col = TRUE;
		    if (maze_w[pos][W] &&
		        intersect_EW(x1, z1, z2))
		        col = TRUE;
		    if (!maze_w[pos][W] && W_EDGE && maze_w[pos-1][S] &&
		        intersect_NS(x1-4.0, x1, z1))
		        col = TRUE;
		    if (!maze_w[pos][S] && S_EDGE && maze_w[pos-32][W] &&
		        intersect_EW(x1, z1-4.0, z1))
		        col = TRUE;
	        }
        }
	    break;
        case NORTH:
	    if (ypos < 2.0)
	    {
	        if (intersect_NS(0.0, (float)((MAZE>>1)-WL), (float)MAZE))
		    col = TRUE;
	        if (intersect_NS((float)((MAZE>>1)+WL), (float)MAZE,
				 (float)MAZE))
		    col = TRUE;
	    }
	    if (intersect_NS((float)-BORDER, (float)MAZE+BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case EAST:
	    if (ypos < 2.0)
	    {
	        if (intersect_EW((float)MAZE, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (intersect_EW((float)MAZE+BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case SOUTH:
	    if (ypos < 2.0)
	    {
	        if (intersect_NS(0.0, (float)((MAZE>>1)-WL), 0.0))
		    col = TRUE;
	        if (intersect_NS((float)((MAZE>>1)+WL), (float)MAZE, 0.0))
		    col = TRUE;
	    }
	    if (intersect_NS((float)-BORDER, (float)MAZE+BORDER,
			     (float)-BORDER))
		col = TRUE;
	    break;
        case WEST:
	    if (ypos < 2.0)
	    {
	        if (intersect_EW(0.0, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (intersect_EW((float)-BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case NORTHEAST:
	    if (ypos < 2.0)
	    {
	        if (intersect_NS((float)((MAZE>>1)+WL), (float)MAZE,
				 (float)MAZE))
		    col = TRUE;
	        if (intersect_EW((float)MAZE, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (intersect_NS((float)-BORDER, (float)MAZE+BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    if (intersect_EW((float)MAZE+BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case SOUTHEAST:
	    if (ypos < 2.0)
	    {
	        if (intersect_NS((float)((MAZE>>1)+WL), (float)MAZE, 0.0))
		    col = TRUE;
	        if (intersect_EW((float)MAZE, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (intersect_NS((float)-BORDER, (float)MAZE+BORDER,
			     (float)-BORDER))
		col = TRUE;
	    if (intersect_EW((float)MAZE+BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case NORTHWEST:
	    if (ypos < 2.0)
	    {
	        if (intersect_NS(0.0, (float)((MAZE>>1)-WL), (float)MAZE))
		    col = TRUE;
	        if (intersect_EW(0.0, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (intersect_NS((float)-BORDER, (float)MAZE+BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    if (intersect_EW((float)-BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
        case SOUTHWEST:
	    if (ypos < 2.0)
	    {
	        if (intersect_NS(0.0, (float)((MAZE>>1)-WL), 0.0))
		    col = TRUE;
	        if (intersect_EW(0.0, 0.0, (float)MAZE))
		    col = TRUE;
	    }
	    if (intersect_NS((float)-BORDER, (float)MAZE+BORDER,
			     (float)-BORDER))
		col = TRUE;
	    if (intersect_EW((float)-BORDER, (float)-BORDER,
			     (float)MAZE+BORDER))
		col = TRUE;
	    break;
	default:
	    break;
    }
    return col;
}


colide()
{
    speed = speed >> 1;
}


intersect_NS(x1, x2, z)
    float x1, x2, z;
{
    float i;

    if (lastz < z)
    {
	if (zpos < (z - 0.25))
	    return FALSE;
	else
	{
	    i = ((z - lastz) / (zpos - lastz)) * (xpos - lastx) + lastx;
	    if (i >= x1 - 0.25 && i <= x2 + 0.25)
	    {
		if (fabs(zpos - lastz) > 0.25)
		    xpos = lastx +
			   (xpos - lastx) *
			   (((z - 0.25) - lastz) / (zpos - lastz));
		zpos = z - 0.25;
		return TRUE;
	    }
	    else
		return FALSE;
	}
    }
    else
	if (zpos > (z + 0.25))
	    return FALSE;
	else
	{
	    i = ((z - lastz) / (zpos - lastz)) * (xpos - lastx) + lastx;
	    if (i >= x1 - 0.25 && i <= x2 + 0.25)
	    {
		if (fabs(zpos - lastz) > 0.25)
		    xpos = lastx +
			   (xpos - lastx) *
			   (((z + 0.25) - lastz) / (zpos - lastz));
		zpos = z + 0.25;
		return TRUE;
	    }
	    else
		return FALSE;
	}
}


intersect_EW(x, z1, z2)
    float x, z1, z2;
{
    float i;

    if (lastx < x)
    {
	if (xpos < (x - 0.25))
	    return FALSE;
	else
	{
	    i = ((x - lastx) / (xpos - lastx)) * (zpos - lastz) + lastz;
	    if (i >= z1 - 0.25 && i <= z2 + 0.25)
	    {
		if (fabs(xpos - lastx) > 0.25)
		    zpos = lastz +
			   (zpos - lastz) *
			   (((x - 0.25) - lastx) / (xpos - lastx));
		xpos = x - 0.25;
		return TRUE;
	    }
	    else
		return FALSE;
	}
    }
    else
	if (xpos > (x + 0.25))
	    return FALSE;
	else
	{
	    i = ((x - lastx) / (xpos - lastx)) * (zpos - lastz) + lastz;
	    if (i >= z1 - 0.25 && i <= z2 + 0.25)
	    {
		if (fabs(xpos - lastx) > 0.25)
		    zpos = lastz +
			   (zpos - lastz) *
			   (((x + 0.25) - lastx) / (xpos - lastx));
		xpos = x + 0.25;
		return TRUE;
	    }
	    else
		return FALSE;
	}
}


colide_obj(list)
    struct thing *list;
{
    float r;
    float i;
    float x, z, xdif, zdif, xrat, zrat;
    int col = FALSE;

    for(; list != NULL; list = list->next)
    {
	if (fabs(list->ypos - ypos) > 1.0)
	    continue;

	z = list->zpos;
	x = list->xpos;

	 
	if ((r = RANGE(list)) < 0.5)
	    col = TRUE;
	else if ((lastz <= z && zpos >= z - 0.50) ||
		 (lastz >= z && zpos <= z + 0.50))
	{
	    if (fabs(lastz - zpos) < 0.05)
	    {
		if ((lastx <= x + 0.50 && xpos >= x - 0.50) ||
		    (lastx >= x - 0.50 && xpos <= x + 0.50))
		    col = TRUE;
	    }
	    else
	    {
	    	i = ((z - lastz) / (zpos - lastz)) * (xpos - lastx) + lastx;
	        if (i >= x - 0.25 && i <= x + 0.25)
		    col = TRUE;
	    }
	}
	if (col)
	{
	    player[id].type |= (list->id << WHAT_SHIFT);

	    lastx = xpos;
	    lastz = zpos;

	    xpos += (xpos - list->xpos) * (0.5/r);
	    zpos += (zpos - list->zpos) * (0.5/r);
	    /*
	    xdif = lastx - xpos;
	    zdif = lastz - zpos;
	    xrat = fabs(xdif / zdif);
	    zrat = fabs(zdif / xdif);
	    lastx = xpos;
	    lastz = zpos;
	    xpos = x + (sqrt(fabs(xrat / (xrat+zrat))) * 0.60) *
			((xdif < 0)? -1.0 : 1.0);
	    zpos = z + (sqrt(fabs(zrat / (xrat+zrat))) * 0.60) *
			((zdif < 0)? -1.0 : 1.0);
	    */
	    speed = speed >> 1;

	    get_sect();

	    if (check_colision())
		colide();
	    return TRUE;
	}
    }
    return FALSE;
}


check_obj_colision()
{
    int col = FALSE;

    switch(sect)
    {
        case INMAZE:
	if (ypos >= 2.0)
	{
	    if (colide_obj(sector[INMAZE]))
	        return TRUE;
	}
	else
        {
	    float x = xpos - (int)(xpos / 4.0) * 4.0;
	    float z = zpos - (int)(zpos / 4.0) * 4.0;
	    int pos = (((int)zpos >> SHIFT) << MSHIFT) + ((int)xpos >> SHIFT);
    
	    if (colide_obj(maze_obj[pos]))
	        return TRUE;
	    if (x > 3.5 && !maze_w[pos][E] && (xpos < (MAZE-WL)) &&
		colide_obj(maze_obj[pos+1]))
		return TRUE;
	    if (z > 3.5 && !maze_w[pos][N] && (zpos < (MAZE-WL)) &&
		colide_obj(maze_obj[pos+MSIZ]))
		return TRUE;
	    if (x < 0.5 && !maze_w[pos][W] && (xpos > WL) &&
		colide_obj(maze_obj[pos-1]))
		return TRUE;
	    if (z < 0.5 && !maze_w[pos][S] && (zpos > WL) &&
		colide_obj(maze_obj[pos-MSIZ]))
		return TRUE;
	}
	    break;
        case NORTH:
	    if (colide_obj(sector[NORTH]))
	        return TRUE;
	    if (xpos > MAZE-0.5 && colide_obj(sector[NORTHWEST]))
		return TRUE;
	    if (xpos < 0.5 && colide_obj(sector[NORTHEAST]))
		return TRUE;
	    break;
        case EAST:
	    if (colide_obj(sector[EAST]))
	        return TRUE;
	    if (zpos < 0.5 && colide_obj(sector[SOUTHEAST]))
		return TRUE;
	    if (zpos > MAZE-0.5 && colide_obj(sector[NORTHEAST]))
		return TRUE;
	    break;
        case SOUTH:
	    if (colide_obj(sector[SOUTH]))
	        return TRUE;
	    if (xpos > MAZE-0.5 && colide_obj(sector[SOUTHWEST]))
		return TRUE;
	    if (xpos < 0.5 && colide_obj(sector[SOUTHEAST]))
		return TRUE;
	    break;
        case WEST:
	    if (colide_obj(sector[WEST]))
	        return TRUE;
	    if (zpos < 0.5 && colide_obj(sector[SOUTHWEST]))
		return TRUE;
	    if (zpos > MAZE-0.5 && colide_obj(sector[NORTHWEST]))
		return TRUE;
	    break;
        case NORTHEAST:
	    if (colide_obj(sector[NORTHEAST]))
	        return TRUE;
	    if (xpos < MAZE+0.5 && colide_obj(sector[NORTH]))
		return TRUE;
	    if (zpos < MAZE+0.5 && colide_obj(sector[EAST]))
		return TRUE;
	    break;
        case SOUTHEAST:
	    if (colide_obj(sector[SOUTHEAST]))
	        return TRUE;
	    if (xpos < MAZE+0.5 && colide_obj(sector[SOUTH]))
		return TRUE;
	    if (zpos > -0.5 && colide_obj(sector[EAST]))
		return TRUE;
	    break;
        case NORTHWEST:
	    if (colide_obj(sector[NORTHWEST]))
	        return TRUE;
	    if (xpos > -0.5 && colide_obj(sector[NORTH]))
		return TRUE;
	    if (zpos < MAZE+0.5 && colide_obj(sector[WEST]))
		return TRUE;
	    break;
        case SOUTHWEST:
	    if (colide_obj(sector[SOUTHWEST]))
	        return TRUE;
	    if (xpos > -0.5 && colide_obj(sector[SOUTH]))
		return TRUE;
	    if (zpos > -0.5 && colide_obj(sector[WEST]))
		return TRUE;
	    break;
	default:
	    break;
    }
    return FALSE;
}


/*
intersect(sx1, ex1, sz1, ez1, sx2, ex2, sz2, ez2)
    float sx1, ex1, sz1, ez1, sx2, ex2, sz2, ez2;
{
    float a1, a2, b1, b2;

    a1 = (sz1 - ez1) / (sx1 - ex1);
    b1 = sz1 - (a1 * sx1)
    a2 = (sz2 - ez2) / (sx2 - ex2);
    b2 = sz2 - (a2 * sx2)

    if (a1 != a2)
    {
	x = (b2 - b1) / (a1 - a2);
	if (((x > sx1-0.5 && x < ex1+0.5) || (x < sx1+0.5 && x > ex1-0.5))
	    ((x > sx2-0.5 && x < ex2+0.5) || (x < sx2+0.5 && x > ex2-0.5)))
	{
	    t1 = (x / (sx1 - ex1));
	    if (fabs((t1 * (sx2 - ex2)) - x) < = 0.5)
	        col = TRUE;
	    t2 = (x / (sx2 - ex2));
	    z = t1 * (sz1 - ez1);
	}
    }
}
*/
