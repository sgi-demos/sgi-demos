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
 *  flight/uflight.c $Revision: 1.1 $
 */

#include "flight.h"
#include "light.h"
#include "colors.h"
#include <math.h>


void my_lookat(float vx, float vy, float vz, float px, float py, float pz,
	       Matrix resmat)
{
    float sine, cosine, hyp, hyp1, dx, dy, dz;
    static Matrix mat = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

    dx = px - vx;
    dy = py - vy;
    dz = pz - vz;

    hyp = dx * dx + dz * dz;	/* hyp squared	*/
    hyp1 = sqrt(dy*dy + hyp);
    hyp = sqrt(hyp);		/* the real hyp	*/

    if (hyp1 != 0.0)		/* rotate X	*/
    {
	sine = -dy / hyp1;
	cosine = hyp / hyp1;
    }
    else
    {
	sine = 0.0;
	cosine = 1.0;
    }
    mat[1][1] = resmat[1][1] = cosine;		/* rotate X	*/
    mat[1][2] = resmat[2][1] = sine;
    mat[2][1] = resmat[1][2] = -sine;
    mat[2][2] = resmat[2][2] = cosine;
    multmatrix(mat);
    mat[1][1] = 1.0;
    mat[1][2] = 0.0;
    mat[2][1] = 0.0;

    if (hyp != 0.0)		/* rotate Y	*/
    {
	sine = dx / hyp;
	cosine = -dz / hyp;
    }
    else
    {
	sine = 0.0;
	cosine = 1.0;
    }
    mat[0][0] = cosine;		/* rotate Y	*/
    mat[0][2] = -sine;
    mat[2][0] = sine;
    mat[2][2] = cosine;
    multmatrix(mat);
    mat[0][2] = sine;
    mat[2][0] = -sine;
    matrix_post_multiply(mat, resmat);
    mat[0][0] = 1.0;
    mat[0][2] = 0.0;
    mat[2][0] = 0.0;
    translate(-vx, -vy, -vz);			/* translate viewpoint */
}


void set_f14_form(Plane pp)
{
    int pos;

    /*
     * set wing position
     */
    if (pp->airspeed < 240)
    {
	setrotation(planeobj[F14], 2, -pp->airspeed/12, 'y');
	setrotation(planeobj[F14], 3, pp->airspeed/12, 'y');
    }
    else if (pp->airspeed <= 450)
    {
	setrotation(planeobj[F14], 2, -20, 'y');
	setrotation(planeobj[F14], 3, 20, 'y');
    }
    else if (pp->airspeed >= 720)
    {
	setrotation(planeobj[F14], 2, -480, 'y');
	setrotation(planeobj[F14], 3, 480, 'y');
    }
    else
    {
	setrotation(planeobj[F14], 2,
		    (int)((pp->airspeed-450)*-1.704)-20, 'y');
	setrotation(planeobj[F14], 3,
		    (int)((pp->airspeed-450)*1.704)+20, 'y');
    }

    /*
     * set tailplane position
     */
    pos = (int)(pp->elevator/2.5 + (pp->rollers>>2));
    if (pos > 200)
	pos = 200;
    else if (pos < -200)
	pos = -200;
    setrotation(planeobj[F14], 16, pos, 'x');	/* left tailplane */
    pos = (int)(pp->elevator/2.5 - (pp->rollers>>2));
    if (pos > 200)
	pos = 200;
    else if (pos < -200)
	pos = -200;
    setrotation(planeobj[F14], 15, pos, 'x');	/* right tailplane */

    /*
     * set thrust
     */
    if (pp->thrust <= 0)
	setscale(planeobj[F14], 5, 1.0, 1.0, 0.01);
    else
	setscale(planeobj[F14], 5, 1.0, 1.0, pp->thrust/100.0);

    /*
     * set wheel position
     */
    setrotation(planeobj[F14], 7, pp->wheels*90, 'x');
    setrotation(planeobj[F14], 10, pp->wheels*90, 'y');
    setrotation(planeobj[F14], 11, -pp->wheels*90, 'y');
}


void set_f15_form(Plane pp)
{
    int pos;

    /*
     * set tailplane position
     */
    pos = (int)(pp->elevator/2.5 + (pp->rollers>>2));
    if (pos > 200)
	pos = 200;
    else if (pos < -200)
	pos = -200;
    setrotation(planeobj[F15], 16, pos, 'x');	/* left tailplane */
    pos = (int)(pp->elevator/2.5 - (pp->rollers>>2));
    if (pos > 200)
	pos = 200;
    else if (pos < -200)
	pos = -200;
    setrotation(planeobj[F15], 15, pos, 'x');	/* right tailplane */

    /*
     * set thrust
     */
    if (pp->thrust <= 0)
	setscale(planeobj[F15], 5, 1.0, 1.0, 0.01);
    else
	setscale(planeobj[F15], 5, 1.0, 1.0, pp->thrust/100.0);

    /*
     * set wheel position
     */
    setrotation(planeobj[F15], 7, pp->wheels*90, 'x');
    setrotation(planeobj[F15], 10, pp->wheels*90, 'y');
    setrotation(planeobj[F15], 11, -pp->wheels*90, 'y');
}


void set_f18_form(Plane pp)
{
    float percent, ipercent, spercent;
    float a, b;
    int pos;

    /*
     * set landing gear position
     */
    percent = pp->wheels/10.0;
    ipercent = 1.0 - percent;

    setrotation(planeobj[F18],  7, (int)( 100 * ipercent),       'z');
    setrotation(planeobj[F18],  8, (int)(-900 *  percent - 100), 'x');
    setrotation(planeobj[F18],  9, (int)( 650 *  percent + 250), 'y');

    if (pp->y - 4.565 >= 2.3)
	spercent = 0.0;
    else if (pp->y - 4.565 == 0)
	spercent = ipercent;
    else
    {
	spercent = 1.0 - ((pp->y - 4.565) / 2.3);
	spercent = (spercent < ipercent)? spercent : ipercent;
    }

    setrotation(planeobj[F18], 10, (int)(-800 * spercent),       'x');
    setrotation(planeobj[F18], 11, (int)( 800 * spercent),       'x');
    setrotation(planeobj[F18], 12, (int)(-650 *  percent - 250), 'y');
    setrotation(planeobj[F18], 13, (int)( 100 * ipercent),       'x');
    setrotation(planeobj[F18], 14, (int)(-100 * ipercent),       'z');
    setrotation(planeobj[F18], 15, (int)( 250 * ipercent),       'y');
    setrotation(planeobj[F18], 16, (int)(-250 * ipercent),       'y');
    setrotation(planeobj[F18], 17, (int)(-100 *  percent),       'z');
    setrotation(planeobj[F18], 18, (int)( 100 *  percent),       'z');
    setrotation(planeobj[F18], 21, (int)(1000 *  percent),       'x');

    a = pp->y - 4.565;
    if (pp->elevation > 0)
	b = pp->elevation / 60.0;
    else
	b = 0;
    a = (a > b)? a : b;
    a = (a > 1.0)? 1.0 : b;

    settranslation(planeobj[F18], 20, 0.0 ,-1.4 - a ,0.0);


    /*
     * set tailplane position
     */
    pos = (int)(pp->elevator/2.5 + (pp->rollers>>2));
    if (pos > 200)
	pos = 200;
    else if (pos < -200)
	pos = -200;
    setrotation(planeobj[F18], 23, pos, 'x');	/* left tailplane */
    pos = (int)(pp->elevator/2.5 - (pp->rollers>>2));
    if (pos > 200)
	pos = 200;
    else if (pos < -200)
	pos = -200;
    setrotation(planeobj[F18], 24, pos, 'x');	/* left tailplane */

    /*
     * set thrust
     */
    if (pp->thrust <= 0)
	setscale(planeobj[pp->type], 27, 1.0, 1.0, 0.01);
    else
	setscale(planeobj[pp->type], 27, 1.0, 1.0, pp->thrust/100.0);
}


void set_p38_form(Plane pp)
{
    setrotation(planeobj[P38], 0, -pp->wheels*100, 'x');
}


void set_ci_f16_form(Plane pp)
{
    int pos;

    /*
     * set wheel position
     */
    setrotation(planeobj[F16], 0, pp->wheels*100, 'x');
    if (pp->wheels < 5)
    {
	setrotation(planeobj[F16], 4, -pp->wheels*100, 'y');
	setrotation(planeobj[F16], 6,  pp->wheels*100, 'y');
    }
    else
    {
	setrotation(planeobj[F16], 4, -500, 'y');
	setrotation(planeobj[F16], 6,  500, 'y');
    }
}




/*
 *  draw the planes and their shadows that are visible
 */
void draw_planes(float ex, float ey, float ez,
		 int start_plane, int num_planes)
{
    int i, close, x, z;
    register Plane pp;

    /*
     *  always draw my shadow
     */
    if (start_plane > 0)
    {
	draw_shadow(planes[0], TRUE);
	if (planes[0]->status <= MEXPLODE && planes[0]->status)
	{
	    lsuspend(TRUE);
	    pushmatrix();
	    translate(planes[0]->x, planes[0]->y, planes[0]->z);
	    draw_exp(19 - (planes[0]->status - 1));
	    popmatrix();
	    lsuspend(FALSE);
	}
    }

    for (i = start_plane; i < num_planes; i++)
    {
	pp = planes[i];

	z = ez - (int)pp->z;
	x = ex - (int)pp->x;
	if (z < 0) z = -z;
	if (x < 0) x = -x;
	if (x < 1024000 && z < 1024000)
	{
	    x >>= 5;
	    z >>= 5;
	    close = ((x * x + z * z) < (dist_for_lines<<1));

	    if (pp->y < 5000.0)
		draw_shadow(pp, close);

	    /*
	     *  If the plane is not visible don't draw it.
	     */
	    if (cull_sphere(&pp->x, planeobj[pp->type]->radius))
		continue;

	    pushmatrix();
	    translate(pp->x, pp->y, pp->z);
	    rotate(pp->azimuth, 'y');
	    rotate(pp->elevation, 'x');
	    rotate(pp->twist, 'z');

	    if (close)	/* if close enough */
	    {
		switch(pp->type)
		{
		    case F15:
			set_f15_form(pp);
			break;
		    case F18:
			set_f18_form(pp);
			break;
		    case F14:
			set_f14_form(pp);
			break;
		    case P38:
			set_p38_form(pp);
			break;
		}
		drawobj(planeobj[pp->type],
			PS_MAINBODY | ((pp->wheels != 10)? PS_LANDINGGEAR : 0) |
			(pp->weapon_state << PS_W_SHIFT));
	    }
	    else
		drawobj(planeobj[pp->type],
			PS_FAR | (pp->weapon_state << PS_W_SHIFT));

	    if (pp->status <= MEXPLODE && pp->status)  /* explosion if needed */
	    {
		lsuspend(TRUE);
		draw_exp(19 - (pp->status - 1));
#ifdef AUDIO
		if (pp->status == MEXPLODE - 1)   /* first frame of expl. */
		    play_explosion((ex - pp->x)*(ex - pp->x) +
			(ey - pp->y)*(ey - pp->y) +
			(ez - pp->z)*(ez - pp->z));
#endif
		lsuspend(FALSE);
	    }

	    popmatrix();
	}
    }
}



void draw_missiles()
{
    register Plane p, *pp;
    register Plane_hist ph, *pph;
    int i, j;

    linewidth(2);
    FOR_EACH_PLANE_AND_HIST (p, pp, ph, pph)
	draw_missile(p, ph);
    linewidth(1);
}


#define BUILDINGS_X -325
#define BUILDINGS_Z -2750

void draw_buildings(float ex, float ey, float ez)
{
    int x, y, z;

    x = ex + BUILDINGS_X;
    if (x < 0)
	x = -x;
    y = ey;
    z = ez + BUILDINGS_Z;
    if (z < 0)
	z = -z;

    x >>= 5;
    y >>= 5;
    z >>= 5;

    drawobj(buildingsobj,
	    ((x*x + y*y + z*z) < (dist_for_lines<<3)) ? BUILDING_NEAR :
							BUILDING_FAR );
}


void draw_threats()
{
    pushmatrix();
    settranslation(threatobj, 0, 6000.0, 0.0, 14000.0);
    setscale(threatobj, 1, 17000.0, 17000.0, 17000.0);
    drawobj(threatobj, 0x1);
    popmatrix();

    pushmatrix();
    settranslation(threatobj, 0, -20000.0, 0.0, 15000.0);
    setscale(threatobj, 1, 10700.0, 10700.0, 10700.0);
    drawobj(threatobj, 0x1);
    popmatrix();

    pushmatrix();
    settranslation(threatobj, 0, 3000.0, 0.0, 34000.0);
    setscale(threatobj, 1, 2700.0, 2700.0, 2700.0);
    drawobj(threatobj, 0x1);
    popmatrix();
}


void draw_everything(float ex, float ey, float ez,
		     int numplanes, int draw_self)
{
    int i, count;
    float tx, ty, tz;
    Matrix tempmat;
    Plane pp;
    int close;

    obj_list_t *draw_list[MAX_OBJS+2*MAX_PLANES];
    float dist[MAX_OBJS+2*MAX_PLANES];

    /*
     *  add buildings, threats, etc.
     */
    for (i=0, count=0; i < obj_count; i++, count++)
    {
	tx = ex - sort_obj[i].cx;
	tz = ez - sort_obj[i].cz;
	dist[count] = (tx * tx) + (tz * tz);
	draw_list[count] = &sort_obj[i];
    }

    /*
     *  add planes
     */
    for (i = 0; i < numplanes; i++)
    {
	pp = planes[i];

	if (i != 0 || draw_self)
	{
	    /*
	     *  calculate distance from eye to plane
	     */
	    tx = ex - pp->x;
	    ty = ey - pp->y;
	    tz = ez - pp->z;
	    dist[count] = (tx*tx) + (tz*tz);
	    sort_plane[i].obj = planeobj[pp->type];
	    draw_list[count] = &sort_plane[i];

	    /*
	     *  figure out what mode to draw in
	     */
	    if (dist[count] > (float)dist_for_lines * (1<<12))
	    {
		sort_plane[i].mode = PS_FAR;
	    }
	    else
	    {
		/*
		 *  calculate eightview
		 */
		sort_plane[i].mode = PS_MAINBODY;
		identify_matrix(tempmat);
		matrix_rotate(tempmat, -pp->twist, 'z');
		matrix_rotate(tempmat, -pp->elevation, 'x');
		matrix_rotate(tempmat, -pp->azimuth, 'y');
		matrix_translate(tempmat, tx, ty, tz);
		if (tempmat[3][0] >= 0.0) sort_plane[i].mode |= EV_RIGHT;
		if (tempmat[3][1] >= 0.0) sort_plane[i].mode |= EV_ABOVE;
		if (tempmat[3][2] >= 0.0) sort_plane[i].mode |= EV_BEHIND;
	    }
	    count++;
	}

	/*
	 *  add missile to list
	 */
	if (pp->mstatus)
	{
	    tz = ez - pp->mz;
	    tx = ex - pp->mx;
	    dist[count] = (tx*tx) + (tz*tz);
	    draw_list[count] = &sort_missile[i];
	    count++;
	}
	else
	{
	    plane_hists[i]->malive = pp->mstatus;
	}
    }

    /*
     *  Now sort the draw list
     */
    sink_sort(count, dist, (void **)draw_list);


    /*
     *  Now draw things
     */

    /*
     *  always draw your own shadow
     */
    if (!draw_self)
	draw_shadow(planes[0], TRUE);

    /*
     *  draw the sorted list
     */
    for (i=0; i < count; i++)
    {
	if (draw_list[i]->type == PLANE_OBJ)
	{
	    pp = planes[draw_list[i]->id];
	    close = (dist[i] <= dist_for_lines);

	    if (pp->y < 5000.0)
		draw_shadow(pp, close);

	    if (!cull_sphere(&pp->x, planeobj[pp->type]->radius))
	    {
		pushmatrix();
		translate(pp->x, pp->y, pp->z);
		rotate(pp->azimuth, 'y');
		rotate(pp->elevation, 'x');
		rotate(pp->twist, 'z');

		if (!(draw_list[i]->mode & PS_FAR))
		{
		    switch(pp->type)
		    {
			case P38:
			    set_p38_form(pp);
			    break;
			case F16:
			    set_ci_f16_form(pp);
			    break;
		    }

		    drawobj(draw_list[i]->obj,
			    draw_list[i]->mode |
			    ((pp->wheels != 10)? PS_LANDINGGEAR : 0) |
			    (pp->weapon_state << PS_W_SHIFT));
		}
		else
		    drawobj(draw_list[i]->obj, draw_list[i]->mode);

		if (pp->status <= MEXPLODE && pp->status)
		    draw_exp_ci(19 - (pp->status - 1));

		popmatrix();
	    }
	}
	else if (draw_list[i]->type == MISSILE_OBJ)
	{
	    pp = planes[draw_list[i]->id];
	    draw_missile_ci(pp, plane_hists[draw_list[i]->id & 0x00ff]);
	    plane_hists[draw_list[i]->id]->malive = pp->mstatus;
	}
	else if (draw_list[i]->type == BUILDING_OBJ)
	{
	    drawobj(draw_list[i]->obj,
		    (dist[i] < (float)dist_for_lines*(1<<13)) ? BUILDING_NEAR :
								BUILDING_FAR);
	}
	else if (draw_list[i]->type == THREAT_OBJ)
	{
	    if (threat_mode)
		drawobj(draw_list[i]->obj, 1);
	}
	else
	    fprintf(stderr, "draw_everything: Error unknown obj type\n");
    }
}


/*
 *  add an object to the sort obj list
 */
void add_obj(int type, float x, float y, float z, object_t *obj)
{
    sort_obj[obj_count].type = type;
    sort_obj[obj_count].cx = x;
    sort_obj[obj_count].cy = y;
    sort_obj[obj_count].cz = z;
    sort_obj[obj_count].obj = obj;
    obj_count++;
}


/*
 *   sort an array (and an associated tag array) in decreasing order
 */
void sink_sort(int n, float *array, void **array_tag)
{
    register float tmp, *end, *top, *bot;
    register void *tag, **top_tag, **bot_tag;

    end = &array[n];

    for (bot = array+1, bot_tag = array_tag+1; bot < end; bot++, bot_tag++)
    {
	top = bot - 1;		top_tag = bot_tag - 1;
	tmp = *bot;
	if (*top < tmp)
	{
	    tag = *bot_tag;
	sinktest:
	    top[1] = *top;	top_tag[1] = *top_tag;
	    top--;		top_tag--;
	    if (top >= array)
	    {
		if (*top < tmp)
		    goto sinktest;
	    }

	    top[1] = tmp; top_tag[1] = tag;
	}
    }
}


/*
 *  generate a random number x, where -maxr <= x <= maxr
 */
int flight_random(int maxr)
{
    static unsigned long randx = 1;
    register int n, retval;

    for (n=1; n<32; n++)
	if ((1 << n) > maxr)
	    break;

    retval = maxr << 1;
    while (retval > maxr)
    {
	randx = randx * 1103515245 + 12345;
	retval = (randx & 0x7fffffff) >> (31-n);
    }
    randx = randx * 1103515245 + 12345;
    if (randx & 0x40000000)
	return(retval);
    else
	return(-retval);
}


float range(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float x, y, z;

    x = fabs(x1 - x2);
    y = fabs(y1 - y2);
    z = fabs(z1 - z2);
    return(sqrt(x*x + y*y + z*z));
}
