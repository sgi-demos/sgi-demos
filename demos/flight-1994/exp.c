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
 *  flight/exp.c $Revision: 1.1 $
 *
 *  code for drawing explosions and missiles
 */

#include <math.h>
#include "flight.h"
#include "light.h"

int expv_cols[55];
float expv[55][3] = {{0.967742, 0.000000, -1.612903},
		     {1.129032, 0.838710, 0.967742},
		     {0.612903, 1.629032, 0.577419},
		     {0.161290, -1.048387, -1.367742},
		     {1.267742, -0.174194, 1.212903},
		     {-1.129032, 0.835484, -0.967742},
		     {1.277419, -1.296774, -0.270968},
		     {1.038710, -0.664516, -1.141935},
		     {0.806452, 0.538710, 1.729032},
		     {-0.706452, 0.151613, 1.729032},
		     {-1.374194, -0.793548, 0.309677},
		     {0.961290, 1.483871, -0.348387},
		     {-1.451613, 0.280645, 0.967742},
		     {0.000000, 0.000000, -1.935484},
		     {0.000000, 1.767742, -0.309677},
		     {-1.525806, -0.300000, -0.880645},
		     {-1.129032, 1.396774, -0.967742},
		     {0.806452, 1.396774, -0.967742},
		     {0.483871, 0.838710, -1.612903},
		     {0.806452, -1.396774, 0.967742},
		     {1.129032, 0.838710, -0.967742},
		     {0.161290, 1.048387, 1.367742},
		     {-0.180645, 1.641935, 0.683871},
		     {0.551613, -0.667742, -1.674194},
		     {-0.812903, -1.587097, 0.619355},
		     {-1.380645, -0.693548, -0.464516},
		     {-0.483871, 0.629032, -1.858065},
		     {-1.606452, 0.367742, -0.348387},
		     {-0.967742, 1.677419, 0.000000},
		     {-0.806452, -1.261290, -1.125806},
		     {0.000000, -1.587097, 0.309677},
		     {-0.812903, -1.767742, 0.000000},
		     {1.670968, 0.283871, 0.306452},
		     {-0.161290, 1.261290, -1.125806},
		     {0.161290, -1.487097, -0.658064},
		     {0.967742, -1.677419, 0.000000},
		     {0.645161, -0.558065, 1.612903},
		     {1.522581, -0.693548, 0.038710},
		     {-1.380645, 0.693548, 0.464516},
		     {0.806452, -1.396774, -0.967742},
		     {0.483871, -0.974194, 1.454839},
		     {0.161290, -0.235484, 1.845161},
		     {-0.161290, -0.538710, 1.729032},
		     {-0.693548, 1.200000, 1.196774},
		     {-0.409677, -1.309677, 1.070968},
		     {1.545161, -0.258065, -0.825806},
		     {-1.935484, 0.000000, 0.000000},
		     {-0.829032, -0.664516, 1.367742},
		     {-0.161290, -0.838710, -1.612903},
		     {-0.161290, 0.538710, 1.729032},
		     {-1.070968, -0.300000, -1.338710},
		     {-0.680645, 0.316129, -1.770968},
		     {1.606452, 0.367742, -0.348387},
		     {-1.303226, 1.125806, 0.048387},
		     {1.438710, 1.016129, 0.270968}};


#define EXP_TRI 106
int expref[EXP_TRI][3] = {{40, 41, 42},
			  {40, 42, 44},
			  {44, 42, 47},
			  {47, 42,  9},
			  { 9, 42, 49},
			  {49, 42, 41},
			  { 8, 49, 41},
			  { 8, 41, 36},
			  {36, 41, 40},
			  {40, 44, 19},
			  { 4, 40, 19},
			  {40,  4, 36},
			  {36,  4,  8},
			  { 8,  4,  1},
			  { 1,  4, 32},
			  {32,  4, 37},
			  {37,  4, 19},
			  { 6, 37, 19},
			  {45, 37,  6},
			  {37, 45, 52},
			  {52, 32, 37},
			  {52, 11, 54},
			  {32, 52, 54},
			  {54,  1, 32},
			  {54,  2,  1},
			  {54, 11,  2},
			  {21,  1,  2},
			  { 8,  1, 21},
			  {21, 49,  8},
			  {43, 49, 21},
			  {43, 21, 22},
			  {22, 21,  2},
			  {49, 43, 12},
			  { 9, 49, 12},
			  {12, 47,  9},
			  {10, 47, 12},
			  {24, 47, 10},
			  {44, 47, 24},
			  {44, 24, 30},
			  {30, 19, 44},
			  {30, 24, 31},
			  {31, 24, 10},
			  {34, 30, 31},
			  {35, 30, 34},
			  {19, 30, 35},
			  {19, 35,  6},
			  {35, 34, 39},
			  { 6, 35, 39},
			  { 6, 39, 45},
			  {45, 39,  7},
			  { 0, 45,  7},
			  { 0,  7, 23},
			  { 3, 23,  7},
			  { 3,  7, 39},
			  {39, 34,  3},
			  {13,  0, 23},
			  {48, 13, 23},
			  {23,  3, 48},
			  { 3, 29, 48},
			  {34, 29,  3},
			  {31, 29, 34},
			  {25, 29, 31},
			  {31, 10, 25},
			  {10, 46, 25},
			  {12, 46, 10},
			  {20, 52, 45},
			  {11, 52, 20},
			  {20, 45,  0},
			  {29, 15, 50},
			  {29, 50, 48},
			  {29, 25, 15},
			  {27, 15, 25},
			  {25, 46, 27},
			  {27,  5, 15},
			  { 5, 50, 15},
			  {48, 50, 51},
			  {48, 51, 13},
			  {51, 50,  5},
			  {53,  5, 27},
			  {38, 53, 27},
			  {27, 46, 38},
			  {38, 46, 12},
			  {43, 38, 12},
			  {28, 53, 38},
			  {22, 38, 43},
			  {28, 38, 22},
			  {22,  2, 14},
			  {22, 14, 28},
			  {14,  2, 11},
			  {16,  5, 53},
			  {53, 28, 16},
			  {16, 28, 14},
			  {14, 11, 17},
			  {11, 20, 17},
			  { 0, 13, 18},
			  {13, 26, 18},
			  {13, 51, 26},
			  {18, 26, 33},
			  {18, 20,  0},
			  {18, 17, 20},
			  {33, 17, 18},
			  {14, 17, 33},
			  {14, 33, 16},
			  {16, 33,  5},
			  {26, 51,  5},
			  { 5, 33, 26}};


unsigned long exp_cp[160];

float **exp_p;

float exp_pnt[100][4];

float n_up[4] = {0.0, 1.0, 0.0, 0.0};


static unsigned short exp_pats[] =
/* 15 / 16 */
   { 0x8888, 0xffff, 0xffff, 0xffff, 0x8888, 0xffff, 0xffff, 0xffff,
     0x8888, 0xffff, 0xffff, 0xffff, 0x8888, 0xffff, 0xffff, 0xffff,
/* 12 / 16 */
     0xafaf, 0xfafa, 0x5f5f, 0xf5f5, 0xafaf, 0xfafa, 0x5f5f, 0xf5f5,
     0xafaf, 0xfafa, 0x5f5f, 0xf5f5, 0xafaf, 0xfafa, 0x5f5f, 0xf5f5,
/* 8 / 16 */
     0x5555, 0xaaaa, 0x5555, 0xaaaa, 0x5555, 0xaaaa, 0x5555, 0xaaaa,
     0x5555, 0xaaaa, 0x5555, 0xaaaa, 0x5555, 0xaaaa, 0x5555, 0xaaaa,
/* 4 / 16 */
     0x5050, 0x0505, 0xa0a0, 0x0a0a, 0x5050, 0x0505, 0xa0a0, 0x0a0a,
     0x5050, 0x0505, 0xa0a0, 0x0a0a, 0x5050, 0x0505, 0xa0a0, 0x0a0a,
/* 1 / 16 */
     0x1111, 0x0000, 0x0000, 0x0000, 0x2222, 0x0000, 0x0000, 0x0000,
     0x4444, 0x0000, 0x0000, 0x0000, 0x8888, 0x0000, 0x0000, 0x0000,
/* 0 / 16 */
     0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
     0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };


init_exp()
{
    int red_1 = 0xff;
    int red_2 = 0xcc;
    int red_3 = 0x00;
    int red_4 = 0x00;
    int green_1 = 0x88;
    int green_2 = 0x11;
    int green_3 = 0x00;
    int green_4 = 0x00;
    int alpha_1 = 0xff;
    int alpha_2 = 0xff;
    int alpha_3 = 0x99;
    int alpha_4 = 0x11;
    unsigned long cur_red, cur_green, cur_alpha;
    int i;
    float delta, idelta;

    /*
     *  color index setup
     */
    for (i=0; i<55; i++)
    {
	expv_cols[i] = (i%2 == 0)? ci_table[C_RED] : ci_table[C_DRED];
    }
    for (i=0; i<5; i++)
    {
	defpattern(EXPL_PAT0+i, 16, &(exp_pats[(i<<4)&0xf0]));
    }
    defpattern(3, 16, &(exp_pats[32]));

    /*
     *  rgb setup
     */
    for (i = 0; i < 50; i++)
    {
	delta = i / 49.0;
	idelta = 1.0-delta;

	cur_red = red_1 * idelta + red_2 * delta;
	cur_green = green_1 * idelta + green_2 * delta;
	cur_alpha = alpha_1 * idelta + alpha_2 * delta;

	exp_cp[i] = (cur_alpha << 24) + (cur_green << 8) + cur_red;
    }

    for (i = 50; i < 100; i++)
    {
	delta = (i-50) / 49.0;
	idelta = 1.0-delta;

	cur_red = red_2 * idelta + red_3 * delta;
	cur_green = green_2 * idelta + green_3 * delta;
	cur_alpha = alpha_2 * idelta + alpha_3 * delta;

	exp_cp[i] = (cur_alpha << 24) + (cur_green << 8) + cur_red;
    }

    for (i = 100; i < 150; i++)
    {
	delta = (i-100) / 49.0;
	idelta = 1.0-delta;

	cur_red = red_3 * idelta + red_4 * delta;
	cur_green = green_3 * idelta + green_4 * delta;
	cur_alpha = alpha_3 * idelta + alpha_4 * delta;

	exp_cp[i] = (cur_alpha << 24) + (cur_green << 8) + cur_red;
    }

    exp_p = (float **)malloc(sizeof(float *) * EXP_TRI * 3);
    for (i = 0; i < EXP_TRI*3; i += 3)
    {
	exp_p[i] = expv[expref[i/3][0]];
	exp_p[i+1] = expv[expref[i/3][1]];
	exp_p[i+2] = expv[expref[i/3][2]];
    }

    for (i = 0; i < 100; i++)
    {
	exp_pnt[i][0] = flight_random(1000) / 250.0;
	exp_pnt[i][1] = flight_random(1000) / 250.0;
	exp_pnt[i][2] = flight_random(1000) / 250.0;
    }
}


draw_exp(int frame)
{
    int i, c;
    float s;
    float **p, *v;

    pushmatrix();

    s = (frame + 1.0) * 3.0;
    scale(s, s, s);

    cpack(0xff0055ff);
    bgnpoint();
    for (i = 0, v = exp_pnt[0]; i < 100; i+=10, v += 10)
    {
	v3f(v);
	v3f(v+1);
	v3f(v+2);
	v3f(v+3);
	v3f(v+4);
	v3f(v+5);
	v3f(v+6);
	v3f(v+7);
	v3f(v+8);
	v3f(v+9);
    }
    endpoint();

    zwritemask(0x0);
    blendfunction(BF_SA, BF_MSA);

    for (i=0, p = exp_p; i < EXP_TRI; i++, p += 3)
    {
	c = frame * 5;

	bgnpolygon();
	cpack(exp_cp[expref[i][0] + c]);
	v3f(*p);
	cpack(exp_cp[expref[i][1] + c]);
	v3f(*(p+1));
	cpack(exp_cp[expref[i][2] + c]);
	v3f(*(p+2));
	endpolygon();
    }

    blendfunction(BF_ONE, BF_ZERO);
    zwritemask(0xffffff);

    popmatrix();
}


draw_exp_ci(int frame)
{
    int i, c, j;
    float s;
    float **p;
    static float t0[3] = { .2, .2, -.1},
		 t1[3] = {-.2, 0.0, 0.0},
		 t2[3] = {.2, -.2, .1};

    backface(1);
    pushmatrix();

    s = (frame + 1.0) * 3.0;
    scale(s, s, s);

    setpattern(EXPL_PAT0 + (frame>>2));

    for (i = 0; i < 100; i++)
    {
	pushmatrix();
	translate(exp_pnt[i][0], exp_pnt[i][1], exp_pnt[i][2]);
	switch (i % 3)
	{
	    case 0:
		color(ci_table[C_RED]);
		break;
	    case 1:
		color(ci_table[C_ORANGE]);
		break;
	    case 2:
		color(ci_table[C_DRED]);
		break;
	}
	rotate((i%20)<<8, 'x');
	rotate((i%20)<<7, 'y');
	bgnpolygon();
	v3f(t0);
	v3f(t1);
	v3f(t2);
	endpolygon();
	popmatrix();
    }

    rotate(frame<<10, 'x');
    rotate(frame<<6, 'y');

    /*
     *  fire ball
     */
    for (i=0, p = exp_p; i < EXP_TRI; i++, p += 3)
    {
	bgnpolygon();
	color(expv_cols[expref[i][0]]);
	v3f(*p);
	color(expv_cols[expref[i][1]]);
	v3f(*(p+1));
	color(expv_cols[expref[i][2]]);
	v3f(*(p+2));
	endpolygon();
    }

    popmatrix();
    backface(0);
    setpattern(0);
}


/*
 *  draw_missile() draws a missile it's contrail and it's explosion.
 *  RGB version
 */
draw_missile(p, ph)
    Plane p;
    Plane_hist ph;
{
    float tmpv1[4];
    float tmpv2[4];
    int i, j, k;
    float vx, vy, vz, d1, d2;
    int myrot, mxrot;
    float px, py, pz, qx, qy, qz, nx, ny, nz, nm;
    Plane pp = planes[0];

    if (p->mstatus)			/* if launched */
    {
	if (p->mstatus <= MEXPLODE)	/* if exploding */
	{
	    pushmatrix();
	    translate(p->mx, p->my, p->mz);
	    draw_exp(19 - (p->mstatus - 1));
	    popmatrix();
	}
	else if (p->mtype != TYPE_CANNON)
	{
	    if (!ph->malive)	/* just launched */
	    {
		ph->mtpos = ph->mtspos = ph->mtlen = 0;
		ph->mt[0][0] = p->last_mx;
		ph->mt[0][1] = p->last_my;
		ph->mt[0][2] = p->last_mz;
	    }

	    /*
	     *  compute missile direction
	     */
	    vx = p->mx - p->last_mx;
	    vy = p->my - p->last_my;
	    vz = p->mz - p->last_mz;

	    d1 = sqrt(vx*vx + vz*vz);
	    d2 = sqrt(vx*vx + vy*vy + vz*vz);

	    if (d1 != 0.0)
		vx /= d1;
	    else
		vx = 1.0;

	    vy /= d2;

	    myrot = xasin(vx);
	    if (vz > 0)
		myrot = ((vx > 0)? 1800 : -1800) - myrot;

	    mxrot = xasin(vy);

	    pushmatrix();
	    translate(p->mx, p->my, p->mz);
	    rotate(-myrot, 'y');
	    rotate(mxrot, 'x');

	    drawobj(swobj, 0x1);

	    popmatrix();

	    if (ph->mt[ph->mtpos][0] != p->mx ||
		ph->mt[ph->mtpos][1] != p->my ||
		ph->mt[ph->mtpos][2] != p->mz)
	    {
		ph->mtpos++;
		ph->mtpos %= MT_MAX;
		if (ph->mtlen == MT_MAX-1)
		    ph->mtspos = (ph->mtpos + 1) % MT_MAX;
		else
		    ph->mtlen++;

		ph->mt[ph->mtpos][0] = p->mx;
		ph->mt[ph->mtpos][1] = p->my;
		ph->mt[ph->mtpos][2] = p->mz;
	    }

	    blendfunction(BF_SA, BF_MSA);

	    set_matalpha(MAT_MTRAIL, 0.8);
	    set_matemission(MAT_MTRAIL, 1.0, 0.2, 0.0);
	    setmaterial(MAT_MTRAIL);
	    bgntmesh();

	    for (i = ph->mtpos, k=0; i != ph->mtspos; i = j, k++)
	    {
		j = i - 1;
		if (j < 0)
		    j = MT_MAX-1;

		if (k == 2)
		    set_matemission(MAT_MTRAIL, 0.0, 0.0, 0.0);
		else if (k >= 22)
		    set_matalpha(MAT_MTRAIL, (29 - k) * 0.1);

		n3f(n_up);
		/*
		 *  compute the normal
		 */
		px = ph->mt[j][X] - ph->mt[i][X];
		py = ph->mt[j][Y] - ph->mt[i][Y];
		pz = ph->mt[j][Z] - ph->mt[i][Z];

		qx = ph->mt[i][X] - current_eye[X];
		qy = ph->mt[i][Y] - current_eye[Y];
		qz = ph->mt[i][Z] - current_eye[Z];

		nx = py*qz - pz*qy;
		ny = pz*qx - px*qz;
		nz = px*qy - py*qx;

		/*
		 * normalize the normal to length 1
		 */
		if (i == ph->mtpos)
		    nm = sqrt(nx*nx + ny*ny + nz*nz) * 2.0;
		else
		    nm = sqrt(nx*nx + ny*ny + nz*nz) * 0.4;

		nx /= nm;
		ny /= nm;
		nz /= nm;

		tmpv1[0] = ph->mt[i][0] + nx;
		tmpv1[1] = ph->mt[i][1] + ny;
		tmpv1[2] = ph->mt[i][2] + nz;
		v3f(tmpv1);
		tmpv2[0] = ph->mt[i][0] - nx;
		tmpv2[1] = ph->mt[i][1] - ny;
		tmpv2[2] = ph->mt[i][2] - nz;
		v3f(tmpv2);
	    }

	    if (k >= 22)
		set_matalpha(MAT_MTRAIL, (29 - k) * 0.1);
	    n3f(n_up);
	    tmpv1[0] = ph->mt[i][0] + nx;
	    tmpv1[1] = ph->mt[i][1] + ny;
	    tmpv1[2] = ph->mt[i][2] + nz;
	    v3f(tmpv1);
	    tmpv2[0] = ph->mt[i][0] - nx;
	    tmpv2[1] = ph->mt[i][1] - ny;
	    tmpv2[2] = ph->mt[i][2] - nz;
	    v3f(tmpv2);

	    endtmesh();

	    blendfunction(BF_ONE, BF_ZERO);
	}
	else
	{
	    cpack(cpack_table[C_RED]);
	    lsuspend(TRUE);
	    move(p->last_mx, p->last_my, p->last_mz);
	    draw(p->mx, p->my, p->mz);
	    lsuspend(FALSE);
	}
    }

    ph->malive = p->mstatus;
}


/*
 *  draw_missile_ci() draws a missile it's contrail and it's explosion.
 *  color_index version
 */
draw_missile_ci(p, ph)
    Plane p;
    Plane_hist ph;
{
    float tmpv1[4];
    float tmpv2[4];
    int i, j, k;
    float vx, vy, vz, d1, d2;
    int myrot, mxrot;
    float px, py, pz, qx, qy, qz, nx, ny, nz, nm;
    Plane pp = planes[0];

    if (p->mstatus)			/* if launched */
    {
	if (p->mstatus <= MEXPLODE)	/* if exploding */
	{
	    pushmatrix();
	    translate(p->mx, p->my, p->mz);
	    draw_exp_ci(19 - (p->mstatus - 1));
	    popmatrix();
	}
	else if (p->mtype != TYPE_CANNON)
	{
	    if (!ph->malive)	/* just launched */
	    {
		ph->mtpos = ph->mtspos = ph->mtlen = 0;
		ph->mt[0][0] = p->last_mx;
		ph->mt[0][1] = p->last_my;
		ph->mt[0][2] = p->last_mz;
	    }

	    /*
	     *  compute missile direction
	     */
	    vx = p->mx - p->last_mx;
	    vy = p->my - p->last_my;
	    vz = p->mz - p->last_mz;

	    d1 = sqrt(vx*vx + vz*vz);
	    d2 = sqrt(vx*vx + vy*vy + vz*vz);

	    if (d1 != 0.0)
		vx /= d1;
	    else
		vx = 1.0;

	    vy /= d2;

	    myrot = xasin(vx);
	    if (vz > 0)
		myrot = ((vx > 0)? 1800 : -1800) - myrot;

	    mxrot = xasin(vy);

	    pushmatrix();
	    translate(p->mx, p->my, p->mz);
	    rotate(-myrot, 'y');
	    rotate(mxrot, 'x');

	    drawobj(swobj, 0x1);

	    popmatrix();

	    /* do that contrail thing */

	    if (ph->mt[ph->mtpos][0] != p->mx ||
		ph->mt[ph->mtpos][1] != p->my ||
		ph->mt[ph->mtpos][2] != p->mz)
	    {
		ph->mtpos++;
		ph->mtpos %= MT_MAX;
		if (ph->mtlen == MT_MAX-1)
		    ph->mtspos = (ph->mtpos + 1) % MT_MAX;
		else
		    ph->mtlen++;

		ph->mt[ph->mtpos][0] = p->mx;
		ph->mt[ph->mtpos][1] = p->my;
		ph->mt[ph->mtpos][2] = p->mz;
	    }

	    setpattern(EXPL_PAT0 + 2);

	    shademodel(GOURAUD);
	    bgntmesh();
	    color(ci_table[C_MC_FLAME]);

	    for (i = ph->mtpos, k=0; i != ph->mtspos; i = j, k++)
	    {
		j = i - 1;
		if (j < 0)
		    j = MT_MAX-1;

		/*
		 *  compute the normal
		 */
		px = ph->mt[j][X] - ph->mt[i][X];
		py = ph->mt[j][Y] - ph->mt[i][Y];
		pz = ph->mt[j][Z] - ph->mt[i][Z];

		qx = ph->mt[i][X] - current_eye[X];
		qy = ph->mt[i][Y] - current_eye[Y];
		qz = ph->mt[i][Z] - current_eye[Z];

		nx = py*qz - pz*qy;
		ny = pz*qx - px*qz;
		nz = px*qy - py*qx;

		/*
		 * normalize the normal to length 1
		 */
		if (i == ph->mtpos)
		    nm = sqrt(nx*nx + ny*ny + nz*nz) * 2.0;
		else
		    nm = sqrt(nx*nx + ny*ny + nz*nz) * 0.4;

		nx /= nm;
		ny /= nm;
		nz /= nm;

		tmpv1[0] = ph->mt[i][0] + nx;
		tmpv1[1] = ph->mt[i][1] + ny;
		tmpv1[2] = ph->mt[i][2] + nz;
		tmpv2[0] = ph->mt[i][0] - nx;
		tmpv2[1] = ph->mt[i][1] - ny;
		tmpv2[2] = ph->mt[i][2] - nz;

		if (k != 1)
		{
		    v3f(tmpv1);
		    v3f(tmpv2);

		}
		else
		{
		    color(ci_table[C_MC_TRAIL]);
		    v3f(tmpv1);
		    v3f(tmpv2);
		    endtmesh();
		    shademodel(FLAT);
		    bgntmesh();
		    v3f(tmpv1);
		    v3f(tmpv2);
		}
	    }

	    endtmesh();
	}
	else
	{
	    linewidth(2);
	    color(ci_table[C_RED]);
	    move(p->last_mx, p->last_my, p->last_mz);
	    draw(p->mx, p->my, p->mz);
	    linewidth(1);
	}
    }
    setpattern(0);

    ph->malive = p->mstatus;
}


