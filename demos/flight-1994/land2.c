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
 *  flight/land2.c $Revision: 1.1 $
 *
 *  contains world definitions
 */

#include "flight.h"
#include "light.h"
#include <stdio.h>


draw_grid()
{
    int x;
    static float nup[] = {0.0, 0.0, 1.0};

    if (in_cmode)
	color(ci_table[C_DIRT]);
    else
	setmaterial(MAT_DIRT);

    pushmatrix();
    rotate(-900, 'x');					/* z = -y */
    n3f(nup);

    for (x = -55000; x <= 55000; x += 10000)		/* grid lines */
    {
	move2i(x, -50000);
	draw2i(x, 50000);
    }
    for (x = -50000; x <= 50000; x += 10000)
    {
	move2i(-55000, x);
	draw2i(55000, x);
    }

    rectfs(6000, -14000, 6020, -14030);			/* threats */
    rectfi(-20000, -15000, -20040, -15020);
    rectfi(3000, -34000, 3010, -34030);

    popmatrix();
}

/*
 *  setup_world setsup a
 */
setup_world()
{
    if (hud)
	viewport(0, xmaxwindow, 0, ymaxwindow);
    else
	viewport(1, xmaxwindow-1, ymiddle, ymaxwindow-1);

    perspective(fov, ar, 4.0, 1.0e6);
}

clearz()
{
    if (hud)
	viewport(0, xmaxwindow, 0, ymaxwindow);
    else
	viewport(1, xmaxwindow-1, ymiddle, ymaxwindow-1);

    zclear();
}

#define EDGE 512000

/*
 *  draw_infinite_world()
 *  draws those objects at an effectively infinite range
 *  i.e. sky, ground stars, sun, moon
 */
draw_infinite_world()	/* unused K&R float param removed: every caller
				   passes no args, which traps wasm */
{
    static long sky[3] = {0, EDGE, 0};
    static long horizon1[11][3] = {{-EDGE,     0, -EDGE},
				   {-EDGE>>2,  0, -EDGE>>2},
				   {-EDGE>>3,  0, -EDGE>>3},
				   {-EDGE>>4,  0, -EDGE>>4},
				   {-EDGE>>5,  0, -EDGE>>5},
				   {-EDGE>>6,  0, -EDGE>>6},
				   {-EDGE>>7,  0, -EDGE>>7},
				   {-EDGE>>8,  0, -EDGE>>8},
				   {-EDGE>>9,  0, -EDGE>>9},
				   {-EDGE>>10, 0, -EDGE>>10},
				   { 0,        0,  0}};
    static long horizon2[11][3] = {{-EDGE,     0,  EDGE},
				   {-EDGE>>2,  0,  EDGE>>2},
				   {-EDGE>>3,  0,  EDGE>>3},
				   {-EDGE>>4,  0,  EDGE>>4},
				   {-EDGE>>5,  0,  EDGE>>5},
				   {-EDGE>>6,  0,  EDGE>>6},
				   {-EDGE>>7,  0,  EDGE>>7},
				   {-EDGE>>8,  0,  EDGE>>8},
				   {-EDGE>>9,  0,  EDGE>>9},
				   {-EDGE>>10, 0,  EDGE>>10},
				   { 0,        0,  0}};
    static long horizon3[11][3] = {{ EDGE,     0,  EDGE},
				   { EDGE>>2,  0,  EDGE>>2},
				   { EDGE>>3,  0,  EDGE>>3},
				   { EDGE>>4,  0,  EDGE>>4},
				   { EDGE>>5,  0,  EDGE>>5},
				   { EDGE>>6,  0,  EDGE>>6},
				   { EDGE>>7,  0,  EDGE>>7},
				   { EDGE>>8,  0,  EDGE>>8},
				   { EDGE>>9,  0,  EDGE>>9},
				   { EDGE>>10, 0,  EDGE>>10},
				   { 0,        0,  0}};
    static long horizon4[11][3] = {{ EDGE,     0, -EDGE},
				   { EDGE>>2,  0, -EDGE>>2},
				   { EDGE>>3,  0, -EDGE>>3},
				   { EDGE>>4,  0, -EDGE>>4},
				   { EDGE>>5,  0, -EDGE>>5},
				   { EDGE>>6,  0, -EDGE>>6},
				   { EDGE>>7,  0, -EDGE>>7},
				   { EDGE>>8,  0, -EDGE>>8},
				   { EDGE>>9,  0, -EDGE>>9},
				   { EDGE>>10, 0, -EDGE>>10},
				   { 0,        0,  0}};
    static float hst1[11][3] = {{-EDGE,     -EDGE},
				{-EDGE>>2,  -EDGE>>2},
				{-EDGE>>3,  -EDGE>>3},
				{-EDGE>>4,  -EDGE>>4},
				{-EDGE>>5,  -EDGE>>5},
				{-EDGE>>6,  -EDGE>>6},
				{-EDGE>>7,  -EDGE>>7},
				{-EDGE>>8,  -EDGE>>8},
				{-EDGE>>9,  -EDGE>>9},
				{-EDGE>>10, -EDGE>>10},
				{ 0,        0}};
    static float hst2[11][3] = {{-EDGE,     EDGE},
				{-EDGE>>2,  EDGE>>2},
				{-EDGE>>3,  EDGE>>3},
				{-EDGE>>4,  EDGE>>4},
				{-EDGE>>5,  EDGE>>5},
				{-EDGE>>6,  EDGE>>6},
				{-EDGE>>7,  EDGE>>7},
				{-EDGE>>8,  EDGE>>8},
				{-EDGE>>9,  EDGE>>9},
				{-EDGE>>10, EDGE>>10},
				{ 0,        0}};
    static float hst3[11][3] = {{ EDGE,     EDGE},
				{ EDGE>>2,  EDGE>>2},
				{ EDGE>>3,  EDGE>>3},
				{ EDGE>>4,  EDGE>>4},
				{ EDGE>>5,  EDGE>>5},
				{ EDGE>>6,  EDGE>>6},
				{ EDGE>>7,  EDGE>>7},
				{ EDGE>>8,  EDGE>>8},
				{ EDGE>>9,  EDGE>>9},
				{ EDGE>>10, EDGE>>10},
				{ 0,        0}};
    static float hst4[11][3] = {{ EDGE,     0, -EDGE},
				{ EDGE>>2,  -EDGE>>2},
				{ EDGE>>3,  -EDGE>>3},
				{ EDGE>>4,  -EDGE>>4},
				{ EDGE>>5,  -EDGE>>5},
				{ EDGE>>6,  -EDGE>>6},
				{ EDGE>>7,  -EDGE>>7},
				{ EDGE>>8,  -EDGE>>8},
				{ EDGE>>9,  -EDGE>>9},
				{ EDGE>>10, -EDGE>>10},
				{ 0,        0}};
    static float gnormal[3] = {0.0, 1.0, 0.0};
    int groundz;
    int i;
    Plane p, *pp;

    if (in_cmode)
    {
	color(ci_table[C_SWAMP]);
	bgnpolygon();
	v3i(horizon1[0]);
	v3i(horizon2[0]);
	v3i(horizon3[0]);
	v3i(horizon4[0]);
	endpolygon();

	color(ci_table[C_SKY]);
	bgntmesh();
	v3i(horizon1[0]);
	v3i(horizon2[0]);
	v3i(sky);
	v3i(horizon3[0]);
	swaptmesh();
	v3i(horizon4[0]);
	v3i(horizon1[0]);
	endtmesh();

	return;
    }

    groundz = FALSE;
    FOR_EACH_PLANE (p, pp)
    {
	if ((p->y <= 10.0 && p->status <= MEXPLODE) ||
	    (p->mstatus && p->my <= 100.0 && p->mstatus <= MEXPLODE))
	    groundz = TRUE;
    }

    if (groundz)
	zbuffer(TRUE);

    lighting(ON);
    setmaterial(MAT_SWAMP);
    n3f(gnormal);
    for (i=0; i < 10; i++)
    {
	bgnpolygon();
	v3i(horizon1[i]);
	v3i(horizon2[i]);
	v3i(horizon2[i+1]);
	v3i(horizon1[i+1]);
	endpolygon();
	bgnpolygon();
	v3i(horizon2[i]);
	v3i(horizon3[i]);
	v3i(horizon3[i+1]);
	v3i(horizon2[i+1]);
	endpolygon();
	bgnpolygon();
	v3i(horizon3[i]);
	v3i(horizon4[i]);
	v3i(horizon4[i+1]);
	v3i(horizon3[i+1]);
	endpolygon();
	bgnpolygon();
	v3i(horizon4[i]);
	v3i(horizon1[i]);
	v3i(horizon1[i+1]);
	v3i(horizon4[i+1]);
	endpolygon();
    }
    lighting(OFF);

    if (groundz)
	zbuffer(FALSE);

    bgntmesh();
    cpack(cp_W_horizon);
    v3i(horizon1[0]);
    v3i(horizon2[0]);
    cpack(cp_sky);
    v3i(sky);
    cpack(cp_E_horizon);
    v3i(horizon3[0]);
    swaptmesh();
    v3i(horizon4[0]);
    cpack(cp_W_horizon);
    v3i(horizon1[0]);
    endtmesh();

    /*
     *  sun
     */

    /*
    draw_cloud_layer();
    */
}


#define CLOUD_ELEV 4000.0
#define CLOUD_TSCALE 0.00003
#define CLOUD_R 100
#define CLOUD_S 12
#define CLOUD_D 1.14
#define CLOUD_START 1.0

draw_cloud_layer()
{
    static float cv[CLOUD_S][CLOUD_R][4];
    static float cv0[4];
    static float ct[CLOUD_S][CLOUD_R][2];
    static float ct0[2];
    static first_time = TRUE;
    float s, c;
    int i, j;
    Plane pp = planes[0];

    if (first_time)
    {
	first_time = FALSE;

	for (i=0; i < CLOUD_S; i++)
	{
	    cv0[X] = 0.0;
	    cv0[Y] = CLOUD_ELEV;
	    cv0[Z] = 0.0;
	    ct0[X] = 0.0;
	    ct0[Y] = 0.0;
	    gl_sincos((1800/CLOUD_S) + (3600/CLOUD_S)*i, &s, &c);
	    cv[i][0][X] = c * CLOUD_START;
	    cv[i][0][Y] = CLOUD_ELEV;
	    cv[i][0][Z] = s * CLOUD_START;
	    ct[i][0][X] = c * CLOUD_TSCALE * CLOUD_START;
	    ct[i][0][Y] = s * CLOUD_TSCALE * CLOUD_START;
	    for (j=1; j < CLOUD_R; j++)
	    {
		cv[i][j][X] = cv[i][j-1][X] * CLOUD_D;
		cv[i][j][Y] = CLOUD_ELEV;
		cv[i][j][Z] = cv[i][j-1][Z] * CLOUD_D;
		ct[i][j][X] = ct[i][j-1][X] * CLOUD_D;
		ct[i][j][Y] = ct[i][j-1][Y] * CLOUD_D;
	    }
	}
    }

    zbuffer(TRUE);

    if (texit)
    {
	texturing(ON);
	mmode(MTEXTURE);
	translate(pp->x * CLOUD_TSCALE, pp->z * CLOUD_TSCALE, 0.0);
	mmode(MVIEWING);
    }

    if (pp->y < CLOUD_ELEV)
	cpack(0xffaaaaaa);
    else
	cpack(0xffeeeeee);

    for (i=0; i < CLOUD_S; i++)
    {
	bgnpolygon();
	t2f(ct[i][j]);
	v3f(cv[i][j]);
	t2f(ct0);
	v3f(cv0);
	t2f(ct[i+1][j]);
	v3f(cv[i+1][j]);
	endpolygon();
    }
    bgnpolygon();
    t2f(ct[7][j]);
    v3f(cv[7][j]);
    t2f(ct0);
    v3f(cv0);
    t2f(ct[0][j]);
    v3f(cv[0][j]);
    endpolygon();

    for (j=0; j < CLOUD_R-1; j++)
    {
	bgntmesh();
	for (i=0; i < CLOUD_S; i++)
	{
	    t2f(ct[i][j+1]);
	    v3f(cv[i][j+1]);
	    t2f(ct[i][j]);
	    v3f(cv[i][j]);
	}
	t2f(ct[0][j+1]);
	v3f(cv[0][j+1]);
	t2f(ct[0][j]);
	v3f(cv[0][j]);
	endtmesh();
    }

    if (texit)
    {
	texturing(OFF);
	mmode(MTEXTURE);
	loadmatrix(identmat);
	mmode(MVIEWING);
    }

    zbuffer(FALSE);
}


genstripe(x1, y1, x2, y2)
    Icoord x1, y1, x2, y2;
{
    rectfs(x1, y1, x2, y2);
    rectfs(-x1, y1, -x2, y2);
    rectfs(x1, 8500-y1, x2, 8500-y2);
    rectfs(-x1, 8500-y1, -x2, 8500-y2);
}


draw_vasi_lights()
{
    register int i;

    static float v1[5][2] = {{ 160.0, 0.0}, { 160.0, 3.0},
			     { 163.0, 3.0}, { 163.0, 0.0}, { 161.5, 1.5}};
    static float v2[5][2] = {{ 180.0, 0.0}, { 180.0, 3.0},
			     { 183.0, 3.0}, { 183.0, 0.0}, { 181.5, 1.5}};
    static float v3[5][2] = {{ 200.0, 0.0}, { 200.0, 3.0},
			     { 203.0, 3.0}, { 203.0, 0.0}, { 201.5, 1.5}};
    static float v4[5][2] = {{-160.0, 0.0}, {-160.0, 3.0},
			     {-163.0, 3.0}, {-163.0, 0.0}, {-161.5, 1.5}};
    static float v5[5][2] = {{-180.0, 0.0}, {-180.0, 3.0},
			     {-183.0, 3.0}, {-183.0, 0.0}, {-181.5, 1.5}};
    static float v6[5][2] = {{-200.0, 0.0}, {-200.0, 3.0},
			     {-203.0, 3.0}, {-203.0, 0.0}, {-201.5, 1.5}};

    bgnpolygon(); for (i=0; i < 4; i++) v2f(v1[i]); endpolygon();
    bgnpolygon(); for (i=0; i < 4; i++) v2f(v2[i]); endpolygon();
    bgnpolygon(); for (i=0; i < 4; i++) v2f(v3[i]); endpolygon();
    bgnpolygon(); for (i=0; i < 4; i++) v2f(v4[i]); endpolygon();
    bgnpolygon(); for (i=0; i < 4; i++) v2f(v5[i]); endpolygon();
    bgnpolygon(); for (i=0; i < 4; i++) v2f(v6[i]); endpolygon();

    bgnpoint();
    v2f(v1[4]);
    v2f(v2[4]);
    v2f(v3[4]);
    v2f(v4[4]);
    v2f(v5[4]);
    v2f(v6[4]);
    endpoint();
}


/*
 *  draw VASI lights , plane is at pz
 */
draw_vasi(pp)
    Plane pp;
{
    float temp1, temp2;
    float trans1, trans2;

    temp1 = temp2 = 0.0;
    if (pp->z > -4000.0)
    {
	trans1 = -800;
	trans2 = 700;
	if (pp->z != -1150.0)
	    temp1 = pp->y/(pp->z + 1150.0);
	if (pp->z != -500.0)
	    temp2 = pp->y/(pp->z + 500.0);
    }
    else
    {
	trans1 = -7700;
	trans2 = -700;
	if (pp->z != -6850.0)
	    temp1 = pp->y/(-6850.0 - pp->z);
	if (pp->z != -7500.0)
	    temp2 = pp->y/(-7500.0 - pp->z);
    }

    pushmatrix();
    if (temp1 < 12.0/200.0)
	COLOR(C_RED);
    else
	COLOR(C_WHITE);
    translate(0.0, 0.0, trans1);
    draw_vasi_lights();

    if (temp2 < 12.0/200.0)
	COLOR(C_RED);
    else
	COLOR(C_WHITE);
    translate(0.0, 0.0, trans2);
    draw_vasi_lights();
    popmatrix();
}
