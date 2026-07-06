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

/*
 *  flight/light.c $Revision: 1.1 $
 */

#include "light.h"
#include "flight.h"

static int curmaterial = 0;
static int curlighting = 0;

/*
 *  materials
 */
float mat_swamp[] = {AMBIENT,	0.3, 0.6, 0.3,
		     DIFFUSE,	0.3, 0.6, 0.3,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_plane[] = {AMBIENT,	0.7, 0.7, 0.7,
		     DIFFUSE,	0.7, 0.7, 0.7,
		     SPECULAR,	1.0, 1.0, 1.0,
		     SHININESS, 30.0,
		     LMNULL};

float mat_thruster[] = {AMBIENT,   0.2, 0.2, 0.2,
			DIFFUSE,   0.2, 0.2, 0.2,
			SPECULAR,  0.3, 0.3, 0.3,
			SHININESS, 5.0,
			LMNULL};

float mat_dirt[] = {AMBIENT,	0.44, 0.37, 0.19,
		     DIFFUSE,	0.44, 0.37, 0.19,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray0[] = {AMBIENT,	0.88, 0.88, 0.88,
		     DIFFUSE,	0.88, 0.88, 0.88,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray1[] = {AMBIENT,	0.82, 0.82, 0.82,
		     DIFFUSE,	0.82, 0.82, 0.82,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray2[] = {AMBIENT,	0.75, 0.75, 0.75,
		     DIFFUSE,	0.75, 0.75, 0.75,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray3[] = {AMBIENT,	0.69, 0.69, 0.69,
		     DIFFUSE,	0.69, 0.69, 0.69,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray4[] = {AMBIENT,	0.63, 0.63, 0.63,
		     DIFFUSE,	0.63, 0.63, 0.63,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray5[] = {AMBIENT,	0.55, 0.55, 0.55,
		     DIFFUSE,	0.55, 0.55, 0.55,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray6[] = {AMBIENT,	0.13, 0.13, 0.13,
		     DIFFUSE,	0.50, 0.50, 0.50,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray7[] = {AMBIENT,	0.44, 0.44, 0.44,
		     DIFFUSE,	0.44, 0.44, 0.44,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray8[] = {AMBIENT,	0.38, 0.38, 0.38,
		     DIFFUSE,	0.38, 0.38, 0.38,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray9[] = {AMBIENT,	0.31, 0.31, 0.31,
		     DIFFUSE,	0.31, 0.31, 0.31,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray10[] = {AMBIENT,	0.25, 0.25, 0.25,
		     DIFFUSE,	0.25, 0.25, 0.25,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray11[] = {AMBIENT,	0.19, 0.19, 0.19,
		     DIFFUSE,	0.19, 0.19, 0.19,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_gray12[] = {AMBIENT,	0.13, 0.13, 0.13,
		     DIFFUSE,	0.13, 0.13, 0.13,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_glass[] = {AMBIENT,	0.4, 0.4, 0.5,
		     DIFFUSE,	0.5, 0.5, 0.6,
		     SPECULAR,	0.9, 0.9, 1.0,
		     SHININESS, 30.0,
		     ALPHA,	0.3,
		     LMNULL};

float mat_prop[] = {AMBIENT,	0.3, 0.3, 0.3,
		    DIFFUSE,	0.3, 0.3, 0.3,
		    SPECULAR,	0.0, 0.0, 0.0,
		    SHININESS,  0.0,
		    ALPHA,	0.5,
		    LMNULL};

float mat_borange[] = {AMBIENT,	  0.5, 0.25, 0.0,
		       DIFFUSE,	  0.5, 0.25, 0.0,
		       SPECULAR,  0.0, 0.0, 0.0,
		       SHININESS, 0.0,
		       LMNULL};

float mat_blime[] = {AMBIENT,	0.40, 0.5, 0.35,
		     DIFFUSE,	0.40, 0.5, 0.35,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_btan[] = {AMBIENT,	0.42, 0.30, 0.25,
		    DIFFUSE,	0.42, 0.30, 0.25,
		    SPECULAR,	0.0, 0.0, 0.0,
		    SHININESS,  0.0,
		    LMNULL};

float mat_bgray[] = {AMBIENT,	0.6, 0.6, 0.6,
		     DIFFUSE,	0.6, 0.6, 0.6,
		     SPECULAR,	0.0, 0.0, 0.0,
		     SHININESS, 0.0,
		     LMNULL};

float mat_purple[] = {AMBIENT,	 0.6, 0.0, 0.6,
		      DIFFUSE,	 0.6, 0.0, 0.6,
		      SPECULAR,	 0.0, 0.0, 0.0,
		      SHININESS, 0.0,
		      LMNULL};

float mat_lpurple[] = {AMBIENT,	  0.7, 0.0, 0.7,
		       DIFFUSE,	  0.7, 0.0, 0.7,
		       SPECULAR,  0.0, 0.0, 0.0,
		       SHININESS, 0.0,
		       LMNULL};

float mat_mtrail[] = {AMBIENT,	 0.7, 0.7, 0.7,
		      DIFFUSE,	 0.7, 0.7, 0.7,
		      SPECULAR,  0.0, 0.0, 0.0,
		      SHININESS, 0.0,
		      ALPHA,     0.8,
		      LMNULL};

float mat_f14black[] = {AMBIENT,   0.1, 0.1, 0.1,
			DIFFUSE,   0.1, 0.1, 0.1,
			SPECULAR,  0.3, 0.3, 0.3,
			SHININESS, 30.0,
			LMNULL};

float mat_f14yellow[] = {AMBIENT,   0.9, 0.7, 0.0,
			 DIFFUSE,   0.9, 0.7, 0.0,
			 SPECULAR,  0.8, 0.8, 0.8,
			 SHININESS, 30.0,
			 LMNULL};

float mat_white[] = {AMBIENT,   1.0, 1.0, 1.0,
		     DIFFUSE,   1.0, 1.0, 1.0,
		     SPECULAR,  1.0, 1.0, 1.0,
		     SHININESS, 30.0,
		     LMNULL};



/*
 *  lights
 */
float sun[] = {AMBIENT, 0.3, 0.3, 0.3,
	       LCOLOR,   1.0, 1.0, 1.0,
	       POSITION, 0.0, 1.0, 0.0, 0.0,
	       LMNULL};

float moon[] = {AMBIENT, 0.0, 0.0, 0.0,
		LCOLOR,   0.2, 0.2, 0.2,
		POSITION, 1.0, 1.0, 1.0, 0.0,
		LMNULL};

float inst_light[] = {AMBIENT, 0.3, 0.3, 0.3,
		      LCOLOR,   1.0, 1.0, 1.0,
		      POSITION, 0.0, 1.0, 0.5, 0.0,
		      LMNULL};

/*
 *  lighting models
 */
float infinite[] = {AMBIENT, 0.1,  0.1, 0.1,
		    LOCALVIEWER, 0.0,
		    LMNULL};


init_lighting()
{
    lmdef (DEFMATERIAL, MAT_SWAMP, 0, mat_swamp);
    lmdef (DEFMATERIAL, MAT_PLANE, 0, mat_plane);
    lmdef (DEFMATERIAL, MAT_THRUSTER, 0, mat_thruster);
    lmdef (DEFMATERIAL, MAT_DIRT, 0, mat_dirt);
    lmdef (DEFMATERIAL, MAT_GRAY0, 0, mat_gray0);
    lmdef (DEFMATERIAL, MAT_GRAY1, 0, mat_gray1);
    lmdef (DEFMATERIAL, MAT_GRAY2, 0, mat_gray2);
    lmdef (DEFMATERIAL, MAT_GRAY3, 0, mat_gray3);
    lmdef (DEFMATERIAL, MAT_GRAY4, 0, mat_gray4);
    lmdef (DEFMATERIAL, MAT_GRAY5, 0, mat_gray5);
    lmdef (DEFMATERIAL, MAT_GRAY6, 0, mat_gray6);
    lmdef (DEFMATERIAL, MAT_GRAY7, 0, mat_gray7);
    lmdef (DEFMATERIAL, MAT_GRAY8, 0, mat_gray8);
    lmdef (DEFMATERIAL, MAT_GRAY9, 0, mat_gray9);
    lmdef (DEFMATERIAL, MAT_GRAY10, 0, mat_gray10);
    lmdef (DEFMATERIAL, MAT_GRAY11, 0, mat_gray11);
    lmdef (DEFMATERIAL, MAT_GRAY12, 0, mat_gray12);
    lmdef (DEFMATERIAL, MAT_GLASS, 0, mat_glass);
    lmdef (DEFMATERIAL, MAT_PROP, 0, mat_prop);
    lmdef (DEFMATERIAL, MAT_BORANGE, 0, mat_borange);
    lmdef (DEFMATERIAL, MAT_BLIME, 0, mat_blime);
    lmdef (DEFMATERIAL, MAT_BTAN, 0, mat_btan);
    lmdef (DEFMATERIAL, MAT_BGRAY, 0, mat_bgray);
    lmdef (DEFMATERIAL, MAT_PURPLE, 0, mat_purple);
    lmdef (DEFMATERIAL, MAT_LPURPLE, 0, mat_lpurple);
    lmdef (DEFMATERIAL, MAT_MTRAIL, 0, mat_mtrail);
    lmdef (DEFMATERIAL, MAT_F14BLACK, 0, mat_f14black);
    lmdef (DEFMATERIAL, MAT_F14YELLOW, 0, mat_f14yellow);
    lmdef (DEFMATERIAL, MAT_WHITE, 0, mat_white);

    lmdef (DEFLIGHT, SUN, 0, sun);
    lmdef (DEFLIGHT, MOON, 0, moon);
    lmdef (DEFLIGHT, INST_LIGHT, 0, inst_light);

    lmdef (DEFLMODEL, INFINITE, 0, infinite);
}


lighting(b)
    int b;
{
    if (in_cmode)
	return;

    if (b)
	lmbind(LMODEL, INFINITE);
    else
	lmbind(LMODEL, 0);
}


set_lightpos(name, x, y, z)
    int name;
    float x, y, z;
{
    static float lpos[6] = {POSITION, 0.0, 1.0, 0.0, 0.0, LMNULL};

    lpos[1] = x;
    lpos[2] = y;
    lpos[3] = z;
    lmdef(DEFLIGHT, name, 0, lpos);
}


set_lightcolor(name, ar, ag, ab, r, g, b)
    int name;
    float ar, ag, ab, r, g, b;
{
    static float lcol[9] = {AMBIENT, 0.3, 0.3, 0.3, LCOLOR, 1.0, 1.0, 1.0,
			    LMNULL};

    lcol[1] = ar;
    lcol[2] = ag;
    lcol[3] = ab;
    lcol[5] = r;
    lcol[6] = g;
    lcol[7] = b;
    lmdef(DEFLIGHT, name, 0, lcol);
}


set_matalpha(name, a)
    int name;
    float a;
{
    static float ma[3] = {ALPHA, 0.0, LMNULL};

    ma[1] = a;
    lmdef(DEFMATERIAL, name, 0, ma);
}


set_matemission(name, r, g, b)
    int name;
    float r, g, b;
{
    static float me[6] = {EMISSION, 0.0, 0.0, 0.0, LMNULL};

    me[1] = r;
    me[2] = g;
    me[3] = b;
    lmdef(DEFMATERIAL, name, 0, me);
}

/*
setmaterial(name)
{
    static curmaterial = 0;

    if (name != curmaterial)
    {
	curmaterial = name;
	lmbind(MATERIAL, name);
    }
}
*/
