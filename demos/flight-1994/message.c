/*
 * Copyright 1993, 1994, Silicon Graphics, Inc.
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
 *  flight/message.c $Revision: 1.1 $
 */

#include "flight.h"


/*
 *  Messages
 */
#define XXXHEADER(vnum)\
"                      SGI Flight Simulator Version vnum"
#define HEADER(vnum)\
"                      SGI Flight Simulator Version 3.4"


static char *helpmsg[] = {
HEADER(VERSION_NUMBER),
"The mouse  controls the white square on the screen which represents the control",
"stick of the plane.  Moving  the  mouse  to  the right causes the plane to roll",
"to the right.  Note that the plane continues to roll until you return the stick",
"to the  center (the bottom center of the windshield).  To takeoff,  use maximum",
"thrust and  pull  back on the stick once you are going fast enough.  The  mouse",
"buttons control the rudder.  Each press of the left mouse button increases left",
"rudder, likewise for the right button.  The  middle  button  returns the rudder",
"to the middle position.  The  rudder  position is indicated by the red triangle",
"at the bottom of the horizon meter.  Try to land with less than 600 fpm descent",
"and 10 degrees roll.  The better the landing, the more  fuel  and  weapons  you",
"receive.  Press any character to continue.  Good luck!",
" ",
"                 ------  Keyboard commands  ------",
"    t   - track/lock on a target      x/z - zoom in/out (tower view)",
"    n/N - time of day +5/-5 minutes   a/s - decrease/increase thrust",
"    Q   - Missile view toggle         H   - Toggle heads-up display",
"    d   - Tower/plane view toggle     f/F - increase/decrease flaps",
"    W   - Wingman view toggle         c/C - increase/decrease spoilers",
"    l   - toggle landing gear         r/R - detonate/restart game (also 'u')",
"    v   - autopilot                   q/w - fire a rocket/sidewinder",
"    e   - fire a cannon burst         h   - display help",
"    F1  - toggle fog                  F2  - toggle texture",
"    m/M - increase/decrease fog       ESC - quit",
""
};


#define XXXSHADOW_HEADER(vnum)\
"          SGI Flight Simulator Shadower Version vnum"
#define SHADOW_HEADER(vnum)\
"          SGI Flight Simulator Shadower Version 3.4"


static char *shadow_helpmsg[] = {
SHADOW_HEADER(VERSION_NUMBER),
" ",
"This program shadows another plane that is playing  dogfight.  You  cannot",
"control  the  plane,  you  can only control your view from the plane.  The",
"left and right  arrow  keys  rotate  your  head  90 degrees left and right",
"when viewing from the plane, check the upper left of the screen for status",
"Press any character to continue",
" ",
"                     Keyboard commands",
"                     -------- --------",
"  t  - track next plane           n/N - time of day +5/-5 minutes",
"  d  - toggle tower/plane view    x   - zoom in (tower view)",
"  W  - toggle wingmans view       z   - zoom out (tower view)",
"  r  - restart the game           h   - display help",
"  F1 - toggle fog                 F2  - toggle texture",
"  m  - increase/decrease fog      ESC - quit",
""
};


#define XXXHEADER(vnum)\
"                          SGI Radar Version vnum"
#define RADAR_HEADER(vnum)\
"                          SGI Radar Version 3.4"

static char *radar_helpmsg[] = {
RADAR_HEADER(VERSION_NUMBER),
" ",
"The radar screen displays the world and planes looking down from the above.",
"Each plane is displayed in a different color with a 16 second history shown",
"with dots and an 8 second projected trajectory shown with a line. The first",
"line of text is the person's name, the second line contains the plane type,",
"its air speed in knots, the sign of its rate of climb,  and its altitude in",
"hundreds of feet.  Sidewinders are red, rockets are orange, and cannons are",
"yellow.  Press ESC to close this window.",
" ",
"                     Keyboard commands",
"                     -------- --------",
"  h   - display help              x/z - zoom in/out",
"  ESC - quit",
"  left   mouse button - send message to closest plane",
"  middle mouse button - broadcast message to everyone",
"  right  mouse button - drag radar screen around",
"  arrow keys - move one grid square in the direction of arrow",
""
};


static char *waitmsg[] = {
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
"Initializing Data",
""
};


static char *plane_menu[] = {
"                      Choose a plane from the following list",
"                        by typing the number of the plane",
" ",
"                        Weight(lbs)     Max        Wing     Loading   Takeoff",
"    #     Type        body      fuel   Thrust   area  span  max  min   speed",
"    -   ----------   -------  -------  -------  ----  ----  ---  ---  -------",
"    1   Cessna 150     1,000      400      250   157    28  +5g  -3g     55",
"    2   Boeing 747   500,000  100,000  200,000  5500   220  +4g  -2g    148",
"    3   F-15          28,000   14,000   46,000   608    42  +8g  -5g    112",
"    4   F-16          18,000    8,000   23,000   390    32 +10g  -7g    122",
"    5   F-18          24,000   12,000   32,000   510    38  +9g  -6g    116",
"    6   P-38          13,500    1,600    4,000   327    52  +6g  -3.5g   75",
"    7   F-14D         42,000   16,200   55,000   565    64  +8g  -4g    115",
"    8   Boeing 727   101,773   59,750   48,000  1700   108  +4g  -2g    140",
#if 0
"    9   F-117A        30,000   14,000   25,000   900    38  +8g  -6g    120",
#endif
" ",
"                                 Additional Help",
"The left and right arrow keys rotate  your head left and right when viewing",
"from the plane, check the upper left of the screen for how much.  Only one weapon can be",
"in play at a time.  To prematurely detonate a rocket or sidewinder, use restart ('r').",
"Cannon shots last one second.  Sidewinders  track planes (except the C-150) within the",
"target window that are higher than 150 feet.  The track command identifies the closest",
"target and locks on to it for one second.  Sidewinders are guaranteed to track  locked",
"targets.  Flaps increase lift and angle of attack but decrease the  stall  angle.  The",
"spoilers  substantially  increase drag and decrease lift.  To land, first slow down to",
"just over the stall speed.  Then use full flaps and don't forget your landing gear!",
""
};


void display_help()
{
    display_message_no_wait(helpmsg, 0);
}


void overlay_help()
{
    display_message_no_wait(helpmsg, 1);
}


void display_shadow_help()
{
    display_message_no_wait(shadow_helpmsg, 0);
}


void overlay_shadow_help()
{
    display_message_no_wait(shadow_helpmsg, 1);
}


void display_radar_help()
{
    display_message_no_wait(radar_helpmsg, 0);
}


void overlay_radar_help()
{
    display_message_no_wait(radar_helpmsg, 1);
}


void display_wait()
{
    display_message_no_wait(waitmsg, 0);
}


int pick_plane()
{
    register int i;

    display_message_no_wait(plane_menu, 0);
    read_objects(TRUE);

    i = wait_for_input();
    if (i > 0) return(i - '0');
    i = -i;
    if (i == PAD1) return(1);
    else if (i == PAD2) return(2);
    else if (i == PAD3) return(3);
    else if (i == PAD4) return(4);
    else if (i == PAD5) return(5);
}


void display_score()
{
    register char *plane_name, **msg;
    register int i;
    register Plane p, *pp;
    static char *score_msg[MAX_PLANES+6];

    /*
     *  init the array first
     */
    if (score_msg[0] == NULL)
    {
	msg = score_msg;
	*msg++ = "               Score Board";
	*msg++ = " ";
	*msg++ = "            Name Plane  Won Lost  Score";
	*msg++ = "---------------- -----  --- ----  -----";
	for (i=0; i < MAX_PLANES+2; i++)
	    *msg++ = (char *) malloc(strlen(score_msg[2])+1);
    };

    msg = &score_msg[4];
    FOR_EACH_PLANE (p, pp)
    {
	switch(p->type)
	{
	    case C150:
		plane_name = C150_NAME;
		break;
	    case B747:
		plane_name = B747_NAME;
		break;
	    case F15:
		plane_name = F15_NAME;
		break;
	    case F16:
		plane_name = F16_NAME;
		break;
	    case F18:
		plane_name = F18_NAME;
		break;
	    case P38:
		plane_name = P38_NAME;
		break;
	    case F14:
		plane_name = F14_NAME;
		break;
	    case B727:
		plane_name = B727_NAME;
		break;
	    default:
		plane_name = "UNKNOWN";
		break;
	}
	sprintf(*msg++, "%16s %5s  %3d %4d  %5d",
		p->myname, plane_name,
		p->won, p->lost, p->won - p->lost);
    }
    sprintf(*msg++, " ");
    sprintf(*msg++, "Press any character to continue.");
    **msg = '\0';
    display_message(score_msg);
}


/*
 *  wait for a key to be hit and return it
 */
int wait_for_input()
{
    short type, val;

    while ((type = qread(&val)) != KEYBD)	/* wait for character	*/
	if (type == REDRAW)
	    redraw_screen();

    return(val);
}


/*
 *  display a message and wait for input before returning
 */
int display_message(char **msg)
{
    display_message_no_wait(msg, 0);
    return(wait_for_input());
}


/*
 *  display a message but dont wait for input'
 */
void display_message_no_wait(char **msg, int transparent)
{
    float y;
    int lines;
    float delta;
    int w, mw;
    char **tmp;

    if (hud || shadow || radar)
    {
	viewport(0, xmaxwindow, 0, ymaxwindow);
	ortho2(-200.0, 200.0, -150.0, 150.0);
	ortho2(-0.5, xmaxwindow+0.5, -150.0, 150.0);
    }
    else
    {
	viewport(1, xmaxwindow-1, ymiddle, ymaxwindow-1);
	ortho2(-200.0, 200.0, -100.0, 100.0);
	ortho2(-0.5, xmaxwindow+0.5, -100.0, 100.0);
    }

    tmp = msg;
    mw = 0;
    lines = 0;
    while (**tmp)
    {
	w = strwidth(*tmp++);
	if (w > mw)
	    mw = w;
	lines++;
    }
    w = mw >> 1;

    delta = MIN((190.0/lines), 8.0);

    if (!transparent)
    {
	COLOR(C_BLUE);
	clear();
    }

    y = 90;
    COLOR(C_WHITE);
    while (**msg)			/* display help in white	*/
    {
	cmov2((float)(xmiddle-w), y);
	charstr(*msg++);
	y -= delta;
    }

    if (!transparent)
	swapbuffers();
}
