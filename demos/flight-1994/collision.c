/*
 * Copyright 1984-1991, 1992, 1993, 1994, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 */


#include <gl.h>
#include <stdio.h>
#include <fcntl.h>

#include "collision.h"


/*
 * collide_tri() returns true if the given point has a y value less than the
 * y value of the given triangle at the given x and z location.
 *
 *	A-------B
 *	| P    /
 *	|    /
 *	|  /
 *	|/
 *	C
 */
int collide_tri(px, py, pz, ax, bx, az, cz, aelv, belv, celv)
    float px, py, pz, ax, bx, az, cz, aelv, belv, celv;
{
    float delta1, elv1, delta2, elv2;

    delta1 = (ax - px) / (ax - bx);
    elv1 = aelv - ((aelv - belv) * delta1);
    delta2 = (az - pz) / (az - cz);
    elv2 = elv1 - ((aelv - celv) * delta2);

    if (py < elv2)
	return(TRUE);
    else
	return(FALSE);
}



/*
 * collide_grid() returns true if the given point is lower than the given grid
 * at the point's x and z location.
 */
int collide_grid(float px, float py, float pz, grid_t *g)
{
    int gx, gz;
    float rpx, rpz;

    if (px > g->xmin && px < g->xmax &&
	pz > g->zmin && pz < g->zmax)
    {
	gx = (px - g->xmin) / g->stepsize;
	gz = (pz - g->zmin) / g->stepsize;
	rpx = px - gx * g->stepsize - g->xmin;
	rpz = pz - gz * g->stepsize - g->zmin;
	if (rpx + rpz < g->stepsize)
	    return(collide_tri(rpx, py, rpz, 0.0, g->stepsize, 0.0, g->stepsize,
		       g->elv[gx][gz], g->elv[gx+1][gz], g->elv[gx][gz+1]));
	else
	    return(collide_tri(rpx, py, rpz, g->stepsize, 0.0, g->stepsize, 0.0,
		       g->elv[gx+1][gz+1], g->elv[gx][gz+1], g->elv[gx+1][gz]));
    }

    return(FALSE);
}



/*
 *  Read a grid file
 */
static int grid_swap32(int v)
{
    unsigned u = (unsigned)v;
    return (int)((u >> 24) | ((u >> 8) & 0xff00) | ((u << 8) & 0xff0000) | (u << 24));
}

static float grid_swapf(float v)
{
    union { float f; unsigned u; } c;
    c.f = v;
    c.u = (c.u >> 24) | ((c.u >> 8) & 0xff00) | ((c.u << 8) & 0xff0000) | (c.u << 24);
    return c.f;
}

grid_t *read_grid(char *fname)
{
    int x, z;
    int fd;
    grid_t *g;
    int swap_grid;

    if ((fd = open(fname, O_RDONLY)) == -1)
    {
	fprintf(stderr, "can't open \"%s\"\n", fname);
	perror("read");
    }

    g = (grid_t *)malloc(sizeof(grid_t));

    read(fd, &g->xsize, sizeof(int));
    read(fd, &g->zsize, sizeof(int));

    /* hills.grid was written on big-endian IRIX; byte-swap on little-endian
     * machines (detected by the header being implausibly large) */
    swap_grid = (unsigned)g->xsize > 0x10000;
    if (swap_grid)
    {
	g->xsize = grid_swap32(g->xsize);
	g->zsize = grid_swap32(g->zsize);
    }

    /* was: malloc(sizeof(float *) * g->xsize+1) — one extra BYTE, not one
     * extra element, while the loops below write elv[xsize] (IRIX survived
     * on malloc slack) */
    g->elv = (float **)malloc(sizeof(float *) * (g->xsize+1));
    for (x=0; x <= g->xsize; x++)
	g->elv[x] = (float *)malloc(sizeof(float) * (g->zsize+1));

    for (z=0; z <= g->zsize; z++)
	for (x=0; x <= g->xsize; x++)
	{
	    read(fd, &g->elv[x][z], sizeof(float));
	    if (swap_grid)
		g->elv[x][z] = grid_swapf(g->elv[x][z]);
	    g->elv[x][z] *= 2000.0;
	}

    close(fd);
    g->stepsize = 2000.0;
    g->xmin = g->zmin = 0.0;
    g->xmax = g->xsize * 2000.0;
    g->zmax = g->zsize * 2000.0;
    return(g);
}

