/*
 * Copyright 1984, 1991, 1992, 1993, 1994, Silicon Graphics, Inc.
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


#include "gobj.h"

#include <gl.h>
#include <math.h>
#include <stdio.h>

float weight();


setrotation(obj, tnum, angle, axis)
    object_t *obj;
    int tnum;
    int angle;
    char axis;
{
    obj->tlist[tnum].angle = angle;
    switch(axis)
    {
	case 'x':
	    obj->tlist[tnum].type = ROTX;
	    break;
	case 'y':
	    obj->tlist[tnum].type = ROTY;
	    break;
	case 'z':
	    obj->tlist[tnum].type = ROTZ;
	    break;
	default:
	    break;
    }
}


setscale(obj, tnum, x, y, z)
    object_t *obj;
    int tnum;
    float x, y, z;
{
    obj->tlist[tnum].type = SCALE;
    obj->tlist[tnum].x = x;
    obj->tlist[tnum].y = y;
    obj->tlist[tnum].z = z;
}


settranslation(obj, tnum, x, y, z)
    object_t *obj;
    int tnum;
    float x, y, z;
{
    obj->tlist[tnum].type = TRANSLATE;
    obj->tlist[tnum].x = x;
    obj->tlist[tnum].y = y;
    obj->tlist[tnum].z = z;
}


/*
 *  routines to generate normals for an object
 */
normalize(obj)
    object_t *obj;
{
    int i;

    for (i=0; i < obj->gcount; i++)
    {
	switch(obj->glist[i].type)
	{
	    case SSECTION:
		ssect_norm(&obj->glist[i]);
		break;
	    case FSECTION:
		fsect_norm(&obj->glist[i]);
		break;
	    case PSECTION:
	    case CSECTION:
	    case CDV_GEOM:
	    case CLS_GEOM:
	    case CDS_GEOM:
		break;
	    default:
		fprintf(stderr, "Error in normalizing \n");
		break;
	}
    }
}


ssect_norm(sect)
    geometry_t *sect;
{
    int i;
    float nm;

    for (i=0; i < sect->vcount; i++)
    {
	sect->nlist[i][X] = 0.0;
	sect->nlist[i][Y] = 0.0;
	sect->nlist[i][Z] = 0.0;
    }

    for (i=0; i < sect->pcount; i++)
	spoly_norm(&sect->plist[i]);

    for (i=0; i < sect->vcount; i++)
    {
	if (sect->nlist[i][X] != 0.0 ||
	    sect->nlist[i][Y] != 0.0 ||
	    sect->nlist[i][Z] != 0.0)
	{
	    nm = sqrt(sect->nlist[i][X] * sect->nlist[i][X] +
		      sect->nlist[i][Y] * sect->nlist[i][Y] +
		      sect->nlist[i][Z] * sect->nlist[i][Z]);

	    sect->nlist[i][X] /= nm;
	    sect->nlist[i][Y] /= nm;
	    sect->nlist[i][Z] /= nm;
	}
    }
}


spoly_norm(p)
    polygon_t *p;
{
    float px, py, pz, qx, qy, qz, nx, ny, nz, nm;
    float w;
    int i;

    /*
     *  compute the normal
     */
    px = p->vlist[0][X] - p->vlist[1][X];
    py = p->vlist[0][Y] - p->vlist[1][Y];
    pz = p->vlist[0][Z] - p->vlist[1][Z];
    qx = p->vlist[1][X] - p->vlist[2][X];
    qy = p->vlist[1][Y] - p->vlist[2][Y];
    qz = p->vlist[1][Z] - p->vlist[2][Z];
    nx = py*qz - pz*qy;
    ny = pz*qx - px*qz;
    nz = px*qy - py*qx;

    /*
     * normalize the normal to length 1
     */
    nm = sqrt(nx*nx + ny*ny + nz*nz);

    nx /= nm;
    ny /= nm;
    nz /= nm;

    w =  weight(p);
    nx *= w;
    ny *= w;
    nz *= w;

    for (i=0; i < p->vcount; i++)
    {
	p->nlist[i][X] += nx;
	p->nlist[i][Y] += ny;
	p->nlist[i][Z] += nz;
    }
}


float weight(p)
    polygon_t *p;
{
    float xmax, ymax, zmax;
    float xmin, ymin, zmin;
    float dx, dy, dz;
    int i;

    xmin = xmax = p->vlist[0][X];
    ymin = ymax = p->vlist[0][Y];
    zmin = zmax = p->vlist[0][Z];

    for (i=1; i < p->vcount; i++)
    {
	if (xmin > p->vlist[i][X])
	    xmin = p->vlist[i][X];
	if (ymin > p->vlist[i][Y])
	    ymin = p->vlist[i][Y];
	if (zmin > p->vlist[i][Z])
	    zmin = p->vlist[i][Z];
	if (xmax < p->vlist[i][X])
	    xmax = p->vlist[i][X];
	if (ymax < p->vlist[i][Y])
	    ymax = p->vlist[i][Y];
	if (zmax < p->vlist[i][Z])
	    zmax = p->vlist[i][Z];
    }

    dx = xmax - xmin;
    dy = ymax - ymin;
    dz = zmax - zmin;

    return (dx*dx + dy*dy + dz*dz);
}


fsect_norm(sect)
    geometry_t *sect;
{
    int i;
    float nm;

    for (i=0; i < sect->pcount; i++)
	fpoly_norm(&sect->plist[i]);
}


fpoly_norm(p)
    polygon_t *p;
{
    float px, py, pz, qx, qy, qz, nx, ny, nz, nm;
    int i;

    /*
     *  compute the normal
     */
    px = p->vlist[0][X] - p->vlist[1][X];
    py = p->vlist[0][Y] - p->vlist[1][Y];
    pz = p->vlist[0][Z] - p->vlist[1][Z];
    qx = p->vlist[1][X] - p->vlist[2][X];
    qy = p->vlist[1][Y] - p->vlist[2][Y];
    qz = p->vlist[1][Z] - p->vlist[2][Z];
    nx = py*qz - pz*qy;
    ny = pz*qx - px*qz;
    nz = px*qy - py*qx;

    /*
     * normalize the normal to length 1
     */
    nm = sqrt(nx*nx + ny*ny + nz*nz);

    p->normal[X] = nx / nm;
    p->normal[Y] = ny / nm;
    p->normal[Z] = nz / nm;
}


compress(obj)
    object_t *obj;
{
    int i;

    for (i=0; i < obj->gcount; i++)
	g_compress(&obj->glist[i]);
}


g_compress(g)
    geometry_t *g;
{
    polygon_t *p;
    float **new_vlist;
    float **new_nlist;
    int new_vcount;
    int *used, *loss;
    int lost = 0;
    int i, j;

    used = (int *)malloc(sizeof(int) * g->vcount);
    loss = (int *)malloc(sizeof(int) * g->vcount);
    bzero(used, sizeof(int) * g->vcount);

    for (i=0; i < g->pcount; i++)
    {
	p = &g->plist[i];
        for (j=0; j < p->vcount; j++)
	    used[p->vnlist[j]] = TRUE;
    }

    for (i=0; i < g->vcount; i++)
    {
	if (!used[i])
	{
	    lost++;
	    free(g->vlist[i]);
	    if (g->nlist)
	        free(g->nlist[i]);
	}
	loss[i] = lost;
    }

    if (!lost)
    {
        free(used);
        free(loss);
	return;
    }

    new_vcount = g->vcount - lost;
    new_vlist = (float **)malloc(sizeof(float *) * new_vcount);
    if (g->nlist)
        new_nlist = (float **)malloc(sizeof(float *) * new_vcount);
    for (i=0, j=0; i < g->vcount; i++)
    {
	if (used[i])
	{
	    new_vlist[j] = g->vlist[i];
	    if (g->nlist)
	        new_nlist[j] = g->nlist[i];
	    j++;
	}
    }

    g->vcount = new_vcount;

    free(g->vlist);
    g->vlist = new_vlist;

    if (g->nlist)
    {
        free(g->nlist);
        g->nlist = new_nlist;
    }

    for (i=0; i < g->pcount; i++)
    {
	p = &g->plist[i];
        for (j=0; j < p->vcount; j++)
	    p->vnlist[j] -= loss[p->vnlist[j]];
    }

    free(used);
    free(loss);
}


combine(obj)
    object_t *obj;
{
    int i;

    for (i=0; i < obj->gcount; i++)
	g_combine(&obj->glist[i]);
}


g_combine(g)
    geometry_t *g;
{
    polygon_t *p;
    int *use;
    int i, j, k;

    use = (int *)malloc(sizeof(int) * g->vcount);
    for (i=0; i < g->vcount; i++)
        use[i] = -1;

    for (i=0; i < g->vcount; i++)
    {
	if (use[i] == -1)
            for (j=i+1; j < g->vcount; j++)
	        if (g->vlist[i][X] == g->vlist[j][X] &&
	            g->vlist[i][Y] == g->vlist[j][Y] &&
	            g->vlist[i][Z] == g->vlist[j][Z] )
		    use[j] = i;
    }

    for (i=0; i < g->pcount; i++)
    {
	p = &g->plist[i];
        for (j=0; j < p->vcount; j++)
	{
	    k = p->vnlist[j];
	    if (use[k] != -1)
	    {
	        p->vnlist[j] = use[k];
	        p->vlist[j] = g->vlist[use[k]];
		if (g->nlist)
	            p->nlist[j] = g->nlist[use[k]];
	    }
	}
    }

    free(use);
}


scale_obj(obj, x, y, z)
    object_t *obj;
    float x, y, z;
{
    geometry_t *g;
    int i;

    for (i=0; i < obj->gcount; i++)
        scale_g(&obj->glist[i], x, y, z);
}

scale_g(g, x, y, z)
    geometry_t *g;
    float x, y, z;
{
    int i;

    for (i=0; i < g->vcount; i++)
    {
	g->vlist[i][X] *= x;
	g->vlist[i][Y] *= y;
	g->vlist[i][Z] *= z;
    }
}


translate_obj(obj, x, y, z)
    object_t *obj;
    float x, y, z;
{
    geometry_t *g;
    int i;

    for (i=0; i < obj->gcount; i++)
        translate_g(&obj->glist[i], x, y, z);
}


translate_g(g, x, y, z)
    geometry_t *g;
    float x, y, z;
{
    int i;

    for (i=0; i < g->vcount; i++)
    {
	g->vlist[i][X] += x;
	g->vlist[i][Y] += y;
	g->vlist[i][Z] += z;
    }
}


reverse_g(g)
    geometry_t *g;
{
    polygon_t *p;
    int i, j, tmp[200];

    for (i=0; i < g->pcount; i++)
    {
	p = &g->plist[i];
	for (j=0; j < p->vcount; j++)
	    tmp[j] = p->vnlist[j];
	for (j=0; j < p->vcount; j++)
	    p->vnlist[j] = tmp[(p->vcount-1)-j];
    }
}
