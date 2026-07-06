/*
 * Copyright 1992, 1993, 1994, Silicon Graphics, Inc.
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

/*
 *  flight/objext.c $Revision: 1.1 $
 *
 *  Extensions to gobj library routines for flight
 */

#include "flight.h"


/*
 *  avg_verts() averages vertices, to get the "center" of an object.
 */
void avg_verts(object_t *obj, float *cx, float *cy, float *cz)
{
    geometry_t *g;
    int i,j,k=0;
    float *v;
    float tx=0.0, ty=0.0, tz=0.0;

    for (i=0; i<obj->gcount; i++)
    {
	g = &obj->glist[i];
	for (j=0; j<g->vcount; j++,k++)
	{
	    v = g->vlist[j];
	    tx += v[0];
	    ty += v[1];
	    tz += v[2];
	}
    }
    *cx = tx / (float)k;
    *cy = ty / (float)k;
    *cz = tz / (float)k;
}


/*
 *  remap_obj() remaps the colors in a color indexed object.
 *  You shouldn't call this with an object that has non color indexed
 *  geometry in it.
 */
void remap_obj(object_t *obj)
{
    int i;

    for (i = 0; i < obj->gcount; i++)
	remap_geom(&obj->glist[i]);
}


/*
 *  remap_geom() remaps the colors in a color indexed geometry node.
 *  You shouldn't call this with a geometry node that is not colorindex.
 */
void remap_geom(geometry_t *g)
{
    int i;

    switch(g->type)
    {
	case IMV_GEOM:
	case IPV_GEOM:
	    for (i = 0; i < g->vcount; i++)
		g->clist[i] = ci_table[g->clist[i]];
	    break;
	case IMU_GEOM:
	case IPU_GEOM:
	    for (i = 0; i < g->pcount; i++)
		g->plist[i].color = ci_table[g->plist[i].color];
	    break;
	default:
	    fprintf(stderr,
		    "Warning: remap_geom() told to remap non ci geometry\n");
	    break;
    }
}
