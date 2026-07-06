/*
 * Copyright 1983-1991, 1992, 1993, 1994, Silicon Graphics, Inc.
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
 *  flight/main.c $Revision: 1.1 $
 */

#include "flight.h"


int main(argc, argv)	/* was K&R untyped main(); clang requires char** */
    int argc;
    char **argv;
{
    flight(argc, argv);
    return 0;
}


reset_fov(nfov)
    register int nfov;
{
    float sin, cos;

    fov = nfov;
    if (hud || shadow)
	ar = (xmaxwindow+1.0)/(ymaxwindow+1.0);
    else
	ar = (xmaxwindow-1.0)/(ymaxwindow-ymiddle);

    /*
     *  calculate dist_for_lines
     */
    nfov >>= 1;		/* half field of view	*/
    gl_sincos(nfov, &sin, &cos);
    dist_for_lines = 25 * 200/3 * cos/sin;
    if (hud || shadow)
	dist_for_lines *= 2;
    dist_for_lines >>= 5;
    dist_for_lines *= dist_for_lines;

    /*
     *  calculate non rotated viewing frustum normals
     */
    frustum[0][0] = frustum[2][0] = 0.0;
    frustum[0][1] = cos;
    frustum[2][1] = -cos;
    frustum[0][2] = frustum[2][2] = sin;
    gl_sincos((int)(nfov * ar + 0.5), &sin, &cos);
    frustum[1][0] = cos;
    frustum[3][0] = -cos;
    frustum[1][1] = frustum[3][1] = 0.0;
    frustum[1][2] = frustum[3][2] = sin;
}



#define DY 0.25

make_crash(msg)
    char *msg;
{
    register Plane p;

    p = planes[0];		/* a bold assumption */

    if (p->status <= MEXPLODE)
	return;

#ifdef AUDIO
    play_samps(diesample, dielength);
#endif

    p->lost++;			/* increment my lost count */
    p->status = MEXPLODE;
    trash_plane();

    clear_report();
    add_report_line(50.0, 0.8, msg);	/* crash message */

    if (!hud)
    {
	frontbuffer(TRUE);
	pushmatrix();
	pushviewport();
	clear_report_area();
	draw_report();
	popmatrix();
	popviewport();
	frontbuffer(FALSE);
    }
}


clear_report_card()
{
    clear_report();
    if (!hud && !shadow)
    {
	frontbuffer(TRUE);	/* clear report card from both buffers */
	clear_report_area();
	frontbuffer(FALSE);
    }
}


int report_card(descent, roll, vx, vz, wheels, p)
    int descent, vx, vz;
    int roll, wheels;
    register Plane p;
{
    short on_runway;
    register int azimuth, rating;
    register float y;
    float xdist, zdist;
    register char charbuf[80];

    azimuth = p->azimuth;
    on_runway = IN_BOX(p, -100.0, 100.0, -8500.0, 0.0);

    roll /= 10;
    if (roll > 180) roll -= 360;
    rating = 1;

    clear_report();

    y = 0.8;

    add_report_line(50.0, y, "Landing Report Card:");

    sprintf(charbuf,"Rate of descent: %d fpm", descent * 60);
    add_report_line(50.0, y-DY, charbuf);

    sprintf(charbuf, "Roll angle: %d", roll);
    add_report_line(50.0, y-2*DY, charbuf);

    sprintf(charbuf, "Air speed: %d knots", vz);
    add_report_line(50.0, y-3*DY, charbuf);

    if (!wheels)
    {
	add_report_line(450.0, y, "*** Landed with the landing gear up!");
	rating = 0;
    }
    if (descent > 10)
    {
	add_report_line(350.0, y-DY, "*** Descending too fast!");
	rating = 0;
    }
    if (roll < 0)
	roll = -roll;
    if (roll > 10)
    {
	add_report_line(350.0, y-2*DY, "*** Too much roll!");
	rating = 0;
    }
    if (!on_runway)
    {
	sprintf(charbuf, "*** Landed off the runway!");
	add_report_line(350.0, y-3*DY, charbuf);
	rating = 0;
    }
    else if (vx > 10 || vx < -10)
    {
	sprintf(charbuf, "*** Too much drifting: %d fps", vx);
	add_report_line(350.0, y-3*DY, charbuf);
	rating = 0;
    }
    if (roll > 20 || descent > 20 || vx > 20 || vx < -20)
	rating = -1;

    if (rating == 1)		/* good landing => rate it */
    {
	sprintf(charbuf, "Sideways speed: %d fps", vx);
	add_report_line(650.0, y, charbuf);

	if (azimuth < 900 || azimuth > 2700)
	    zdist = -1075.0 - p->z;
	else
	    zdist = -7425.0 - p->z;
	xdist = fabs(p->x);

	sprintf(charbuf, "Distance from centerline: %d", (int)xdist);
	add_report_line(650.0, y-DY, charbuf);

	zdist = fabs(zdist);
	sprintf(charbuf, "Distance from touchdown: %d", (int)zdist);
	add_report_line(650.0, y-2*DY, charbuf);

	if (azimuth > 2700)
	    azimuth = 3600-azimuth;
	else if (azimuth > 900)
	    azimuth = 1800 - azimuth;
	if (azimuth < 0)
	    azimuth = -azimuth;
	azimuth /=10;
	sprintf(charbuf, "Heading error: %d degrees", azimuth);
	add_report_line(650.0, y-3*DY, charbuf);

	if (vx < 0)
	    vx = -vx;
	rating = 100 - descent - roll - azimuth - (vx>>1)
		    -(int)(.01 * zdist) - (int)(.1 * xdist);
	if (rating < 0)
	    rating = 0;
	sprintf(charbuf, "Nice landing! (%d/100)", rating);
	add_report_line(250.0, y, charbuf);
    }
    else if (rating == 0)
    {
	add_report_line(250.0, y, "CRASH LANDING! (0/100)");
    }
    else
    {
	add_report_line(250.0, y, "EXPLODED ON IMPACT!");
	broadcast("exploded on impact");
    }

    if (!hud)
    {
	frontbuffer(TRUE);
	clear_report_area();
	draw_report();
	frontbuffer(FALSE);
    }
    return(rating);
}

/* check my missile against other planes	*/
check_missile(p)
    register Plane p;
{
    char buf[NAME_LENGTH+32];
    register Plane ptest, *pp;
    long last_kill;

    last_kill = p->mkill;
    FOR_EACH_PLANE (ptest, pp)
	if ((p != ptest || p->mtype == TYPE_SAM) && test_blow_up(p, ptest))
	{
	    p->mkill = PLANE_ID(ptest);
	    if (last_kill == NULL_PLANE_ID)
	    {
		p->mx = .2 * p->mx + .8 * ptest->x;
		p->my = .2 * p->my + .8 * ptest->y;
		p->mz = .2 * p->mz + .8 * ptest->z;
	    }
	    if (p->mkill != last_kill)	/* debounce */
	    {
		extern char *WEAPON_NAME[];

		p->won++;
		sprintf(buf, "destroyed %s with a %s",
			    ptest->myname, WEAPON_NAME[p->mtype]);
		broadcast(buf);
	    }
	    return;
	}
}


int test_blow_up(m, p)
    register Plane m, p;
{
    register int dx, dy, dz;
    static int MDIST[] = {250, 350, 150, 300};

    /*
     *  if the plane is not exploding
     */
    if (p->status > MEXPLODE)
    {
	dx = m->mx - p->x;
	dy = m->my - p->y;
	dz = m->mz - p->z;
	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	if (dz < 0) dz = -dz;
	if (dx + dy + dz < MDIST[m->mtype])
	{
	    if (m->mstatus > MEXPLODE)
		m->mstatus = MEXPLODE;
	    return (TRUE);
	}
    }
    return(FALSE);
}

/* find and return the closest plane to me	*/
Plane find_closest_plane(myp)
    register Plane myp;
{
    float myx, myy, myz;
    float dx, dy, dz, d, dbest;
    register Plane p, *pp, pbest;

    pbest = NULL;
    dbest = 1e30;
    myx = my_ptw[2][0];
    myy = my_ptw[2][1];
    myz = my_ptw[2][2];

    FOR_EACH_PLANE(p, pp)		/* for each plane	*/
    /* if its not me, not exploding, above 150 feet, not C150	*/
    if ((p != myp || myp->mtype == TYPE_SAM) && p->status > MEXPLODE &&
	p->y > 150.0 && p->type != C150)
    {
	dx = myp->x - p->x;		/* compute distance	*/
	dy = myp->y - p->y;
	dz = myp->z - p->z;
	d = sqrt(dx*dx + dy*dy + dz*dz);

	if ((myx*dx + myy*dy + myz*dz)/d > .988)
	{
	    if (d < dbest)		/* and compare with best */
	    {
		dbest = d;
		pbest = p;
	    }
	}
    }
    return(pbest);
}
