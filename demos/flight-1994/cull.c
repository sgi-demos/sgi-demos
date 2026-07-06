/*
 * Copyright 1991, 1992, 1993, 1994, Silicon Graphics, Inc.
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
 *  flight/cull.c $Revision: 1.1 $
 *
 *  culling routines
 */

#include "flight.h"
#include <math.h>


/*
 *  cull_sphere() returns TRUE if the sphere is outside the viewing frustom,
 *  FALSE other wise.
 */
cull_sphere(float *center, float radius)
{
    int i;

    if (clip_planes[0][3] + DOT(clip_planes[0], center) > radius)
	return(TRUE);
    if (clip_planes[1][3] + DOT(clip_planes[1], center) > radius)
	return(TRUE);
    if (clip_planes[2][3] + DOT(clip_planes[2], center) > radius)
	return(TRUE);
    if (clip_planes[3][3] + DOT(clip_planes[3], center) > radius)
	return(TRUE);

    return(FALSE);
}


/*
 *  cull_shadow() returns TRUE if the shadow of plane pp is outside the
 *  viewing frustom, FALSE other wise.
 */
cull_shadow(Plane pp, float xf, float zf)
{
    float v1[3], v2[3];
    float radius;

    radius = planeobj[pp->type]->radius;
    v1[X] = pp->x + (pp->y + radius) * xf;
    v1[Y] = 0;
    v1[Z] = pp->z + (pp->y + radius) * zf;
    v2[X] = pp->x + (pp->y - radius) * xf;
    v2[Y] = 0;
    v2[Z] = pp->z + (pp->y - radius) * zf;

    if (clip_planes[0][3] + DOT(clip_planes[0], v1) > radius &&
	clip_planes[0][3] + DOT(clip_planes[0], v2) > radius)
	return(TRUE);
    if (clip_planes[1][3] + DOT(clip_planes[1], v1) > radius &&
	clip_planes[1][3] + DOT(clip_planes[1], v2) > radius)
	return(TRUE);
    if (clip_planes[2][3] + DOT(clip_planes[2], v1) > radius &&
	clip_planes[2][3] + DOT(clip_planes[2], v2) > radius)
	return(TRUE);
    if (clip_planes[3][3] + DOT(clip_planes[3], v1) > radius &&
	clip_planes[3][3] + DOT(clip_planes[3], v2) > radius)
	return(TRUE);

    return(FALSE);
}

