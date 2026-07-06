/*
 * Copyright 1988, 1989, 1990, 1991, 1992, 1993, 1994, Silicon Graphics, Inc.
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
 *  flight/shadow.c $Revision: 1.1 $
 */

#include "flight.h"
#include "light.h"
#include <stdio.h>

int newtarget = TRUE;
int shadow_target;


/*
 *  start up code specific to flight
 */
shadow_start()
{
    int itemp;

    view_switch = PLANE_VIEW;			/* view from plane	*/
    plane_fov = tower_fov = 400;
    reset_fov(400);
    view_angle = 0;
    debug = timeit = FALSE;

    read_objects(FALSE);

    /*
     *  read network buffers
     */
    for (itemp=0; itemp<16; itemp++)
	get_indata(1);
    qenter(REDRAW, 0);
    qenter(KEYBD, 't');

    tick_counter = int_tps;

    restart = 0;
}


/*
 *  main loop for shadow
 */
shadow_loop()
{
    unsigned char frame_count = 0;	/* count of frames */

    while (!restart)
    {
	viewport(0, xmaxwindow, 0, ymaxwindow);
	zclear();

	tick_counter--;

	/*
	 *  read all queue entries
	 */
	shadow_read_queue();

	/*
	 *  update time
	 */
	if (!frame_count)
	    update_ftime();		/* every 256 frames */
	frame_count++;

	/*
	 *  read network packets
	 */
	shadow_read_network();

	/*
	 *  draw the out the window scene
	 */
	draw_scene();

	draw_messages();		/* display any network messages	*/

	ortho2(-0.5, xmaxscreen+0.5, -0.5, ymaxscreen+.5);
	draw_report();

	swapbuffers();

	if (tick_counter == 0)		/* only update them every second */
	{
	    time_end = times(&tms_end_buf);
	    check_time();
	    time_start = times(&tms_start_buf);
	    tick_counter = int_tps;		/* reset tick counter */
	}
    }
}



shadow_read_queue()
{
    short type, val;

    while (qtest())
    {
	switch(type = qread(&val))
	{
	    case REDRAW:
		break;
	    case WINQUIT:
		end_of_program();
		break;
	    case KEYBD:
		switch(val)
		{
		    case 27:
			end_of_program();
		    case 'z':
		    case 'x':
			if (view_switch == TOWER_VIEW)
			{
			    if (val == 'x')
			    {
				if (tower_fov > 30)
				    tower_fov -= 25;
			    }
			    else
			    {
				if (tower_fov < 600)
				    tower_fov += 25;
			    }
			    reset_fov(tower_fov);
			}
			else if (wingman_view)
			{
			    if (val == 'x')
			    {
				if (wmfollow > 0) wmfollow--;
			    }
			    else
				if (wmfollow < 9) wmfollow++;
			}
			break;
		    case 'd':
			if (view_switch == PLANE_VIEW)
			{
			    view_switch = TOWER_VIEW;
			    reset_fov(tower_fov);
			}
			else if (view_switch == TOWER_VIEW)
			{
			    view_switch = PLANE_VIEW;
			    reset_fov(plane_fov);
			}
			break;
		    case 'W':
			wingman_view = !wingman_view;
			break;
		    case 't':	/* get next plane in array */
			{
			    static int index = -1;
			    if (planes[++index]->alive <= 0)
				index = 1;
			    shadow_target = PLANE_ID(planes[index]);
			    newtarget = TRUE;
			}
			break;
		    case 'm':
			set_fog_density(-1);
			break;
		    case 'M':
			set_fog_density(1);
			break;
		    case 'n':
			set_ftime(ftime + 5);
			break;
		    case 'N':
			set_ftime(ftime - 5);
			break;
		    case 'h':
			show_help = !show_help;
			break;
		    case 'r':
			restart = 1;
		    case 'p':
			wait_for_input();
			break;
		    case 'T':
			threat_mode = !threat_mode;
			break;
		    case 'I':
			stopit();
			break;
		    case '?':
			timeit = !timeit;
			tick_counter = TPS;
			break;
#ifdef DEBUG
		    case '-':
		    case '_':
			rewind_if(-10);
			break;
		    case '+':
		    case '=':
			rewind_if(10);
			break;
		    case '0':
		    case '1':
		    case '2':
		    case '3':
		    case '4':
		    case '5':
		    case '6':
		    case '7':
		    case '8':
		    case '9':
			debug ^= 1 << (val-'0');
			break;
#endif
		    default:
			break;
		}
		break;
	    case F1KEY:     /* toggle fog */
		if (val)
		    fogit = !fogit && (getgdesc(GD_FOGVERTEX) > 0);
		break;
	    case F2KEY:     /* toggle texturing */
		if (val)
		    texit = !texit && (getgdesc(GD_TEXTURE) > 0);
		break;
	    case LEFTARROWKEY:
		if (val && view_switch == PLANE_VIEW)
		{
		    view_angle -= 50;
		    if (view_angle <= -1800)
			view_angle += 3600;
		}
		break;
	    case RIGHTARROWKEY:
		if (val && view_switch == PLANE_VIEW)
		{
		    view_angle += 50;
		    if (view_angle > 1800)
			view_angle -= 3600;
		}
		break;
	    case UPARROWKEY:
		if (val && view_switch == PLANE_VIEW)
		    view_angle = 0;
		break;
	    case DOWNARROWKEY:
		if (val && view_switch == PLANE_VIEW)
		    view_angle = 1800;
		break;
	    case PAUSEKEY:
		if (val)
		    read_pause = !read_pause;
		break;
	    case HOMEKEY:
		if (val)
		    read_reset = TRUE;
		break;
	    case F9KEY:
		if (val)
		    read_speed = 0.2;
		break;
	    case F10KEY:
		if (val)
		    read_speed = 1.0;
		break;
	    case F11KEY:
		if (val)
		    read_speed = 5.0;
		break;
	    case F12KEY:
		if (val)
		    read_backwards = !read_backwards;
		break;
	    default:
		break;
	}
    }
}


shadow_read_network()
{
    Plane pp = planes[0];

    /*
     *  read network packets
     */
    get_indata(1);

    /*
     *  set pointers to incoming data buffers
     */
    pp = lookup_plane(shadow_target);
    if (pp == NULL)			/* if its not there, use first	*/
    {
	shadow_target = PLANE_ID(planes[0]);
	pp = lookup_plane(shadow_target);
    }
    if (pp == NULL)			/* if its still not there	*/
    {
	pp = planes[0];
	strcpy(pp->myname, "no one");
	pp->x = START_X;
	pp->y = START_Y;
	pp->z = START_Z;
	pp->elevation = 0;
	pp->twist = 0;
	pp->azimuth = START_AZIMUTH;
	pp->type = F15;
    }
    else				/* swap pp and planes[0]	*/
    {
	int i;
	Plane p, *ppp, pf;
	Plane_hist ph;

	i = 0;
	FOR_EACH_PLANE (p, ppp)
	{
	    if (p == pp)
	       break;
	    i++;
	}
	planes[i] = planes[0];
	planes[0] = pp;
	ph = plane_hists[i];
	plane_hists[i] = plane_hists[0];
	plane_hists[0] = ph;
	if (inf)
	{
	    pf = plane_futures[i];
	    plane_futures[i] = plane_futures[0];
	    plane_futures[0] = pf;
	}
    }

    if (newtarget)
    {
	/*
	 *  init wingman info
	 */
	for(wmspos = 0; wmspos < 10; wmspos++)
	{
	    wm_x[wmspos] = pp->x;
	    wm_y[wmspos] = pp->y;
	    wm_z[wmspos] = pp->z;
	    wm_twist[wmspos] = pp->twist;
	    wm_elevation[wmspos] = pp->elevation;
	    wm_azimuth[wmspos] = pp->azimuth;
	}
	wmpos = wmspos - wmfollow;
	if (wmpos < 0)
	    wmpos += 10;
	wmspos = 0;
	newtarget = FALSE;

	/*
	 *  init view position
	 */
	switch(pp->type)
	{
	    case C150:
		pilot_eye[Y] = 5.0;
		pilot_eye[Z] = -0.0;
		break;
	    case B747:
		pilot_eye[Y] = 30.0;
		pilot_eye[Z] = -92.0;
		break;
	    case F15:
		pilot_eye[Y] = 4.8;
		pilot_eye[Z] = -26.0;
		break;
	    case F16:
		pilot_eye[Y] = 3.5;
		pilot_eye[Z] = -13.0;
		break;
	    case F18:
		pilot_eye[Y] = 4.3;
		pilot_eye[Z] = -13.5;
		break;
	    case P38:
		pilot_eye[Y] = 2.3;
		pilot_eye[Z] = -3.0;
		break;
	    case F14:
		pilot_eye[Y] = 4.8;
		pilot_eye[Z] = -26.0;
		break;
	    case B727:
		pilot_eye[Y] = 2.0;
		pilot_eye[Z] = -66.0;
		break;
	}
    }
    else
    {
	wm_x[wmspos] = pp->x;
	wm_y[wmspos] = pp->y;
	wm_z[wmspos] = pp->z;
	wm_twist[wmspos] = pp->twist;
	wm_elevation[wmspos] = pp->elevation;
	wm_azimuth[wmspos] = pp->azimuth;
	wmpos = wmspos - wmfollow;
	if (wmpos < 0)
	    wmpos += 10;
	wmspos = (wmspos+1) % 10;
    }
}
