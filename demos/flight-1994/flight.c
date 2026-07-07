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
 *  flight/flight.c $Revision: 1.1 $
 */


#include "flight.h"
#include "light.h"
#include "udpbrdcst.h"
#include <sys/param.h>
#include <sys/types.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


/*
 *  general status
 */

/*
 *  timing info
 */
int int_tps = 20;	/* integer ticks per second */
float tps = 20;		/* ticks per second */
short tick_counter;	/* counts the loop ticks	*/
struct tms tms_start_buf, tms_end_buf;	/* timer buffer */
int time_start, time_end;			/* start/end times */

/*
 *  effects of timing
 */
float gravity = 1;		/* the effect of gravity relative to tps */
float fps_knots;	/* fps to knots conversion factor based on tps */

int number_planes;	/* number of planes in game	*/


/*
 *  screen and window info
 */
int xmaxscreen = 0;
int ymaxscreen = 0;
int xorigin, yorigin;
int xmaxwindow, ymaxwindow;
int xmiddle, ymiddle;
int zminscreen, zmaxscreen;
int inst_x1, inst_x2, inst_y1, inst_y2;
int report_x1, report_x2, report_y1, report_y2;

/*
 *  display state info
 */
int in_cmode = FALSE;
int force_cmode = FALSE;
int force_rgb = FALSE;
int bits_cmode = 6;			/* maximum of 6 bits used */
int bits_over = 2;
int bits_under = 2;
long over_drawmode = PUPDRAW;		/* OVERDRAW or PUPDRAW */
int ms_samples = 0;

/*
 *  mouse and spaceball positions
 */
long mousex, mousey, sbtx, sbtz;


/*
 *  misc
 */
int i;
int errno;
static char charbuf[80];	/* char buffer */
Matrix identmat;		/* identity matrix */
char status_text[60];

char *WEAPON_NAME[] = {"rocket", "sidewinder", "20mm cannon",
		       "Surface to Air Missile"};
extern float ro[], fuel_consump();	/* air density table	*/

int oldthrust;   /* thing for constant thrust sound */
int bell=1;      /* keyboard beep on */

int restart = 1;
#define START1 1
#define START2 2
#define START3 3
#define START4 4


/*
 *  flags
 */
short debug;			/* TRUE if in debug mode */
short dogfight;			/* TRUE if dogfight */
short shadow;			/* TRUE if shadow */
short radar;			/* TRUE if radar */
short hud;			/* TRUE if hud, else meters */
short threat_mode;		/* TRUE if threats envelopes */
short timeit;			/* TRUE if displaying timing info */
short test_mode;		/* test mode uses no fuel */
short dials = FALSE;		/* TRUE if using dials */
short new_inst = TRUE;		/* TRUE if using new instroments */
short show_help = FALSE;	/* TRUE if displaying help */


/*
 *  geomety objects
 */
object_t *runwayobj;
object_t *lightsobj;
object_t *hillsobj;
object_t *mtnsobj;
object_t *buildingsobj;
object_t *planeobj[9];
object_t *swobj;
object_t *threatobj;
object_t *planeboxobj;
char datadir[108];
char sounddir[108];
char objdir[108];
char objfname[128];
grid_t *hillsgrid;

obj_list_t sort_obj[MAX_OBJS];
obj_list_t sort_plane[MAX_PLANES];
obj_list_t sort_missile[MAX_PLANES];
int obj_count;


/*
 *  The following are used to adjust for frame rate speed changes
 */
float vx_add,		/* plane velocity add per frame */
      vy_add,
      vz_add;
float missile_vx_add,	/* missile velocity add per frame */
      missile_vy_add,
      missile_vz_add;
float tps_add;		/* tps (ticks per second) add per frame */




/*
 *  plane design parameters
 */
char *plane_type;		/* plane type (i.e. "F-15") */
float s;			/* wing area in sq. feet */
float W;			/* weight of plane in lbs. */
float fuel_weight;		/* weight of fuel */
float Mthrust;			/* maximum thrust */
float b;			/* wing span in feet */
float ef;			/* efficiency factor */
float Fmax;			/* maximum flap deflection */
float Smax;			/* maximum spoiler deflection */
float ELEVF;			/* elevator rate in degrees/sec */
float ROLLF;			/* roll rate (both at 300 mph) */
float pilot_eye[4] = {0.0, 0.0, 0.0, 1.0};	/* pilots eye position */
float Lmax;			/* maximum lift before wing breaks */
float Lmin;			/* minimum lift before wing breaks */
float plane_height;		/* height of plane midpoint */
int MAX_RK, MAX_SW;		/* max rockets and sidewinders */
int MIN_LIFT_SPEED;		/* minimum lift-up speed fps */
float swpos[4][4] = {{0.0, 0.0, 0.0, 1.0},	/* position of sidewinders on */
		     {0.0, 0.0, 0.0, 1.0},	/* plane */
		     {0.0, 0.0, 0.0, 1.0},
		     {0.0, 0.0, 0.0, 1.0}};
float rkpos[4][4] = {{0.0, 0.0, 0.0, 1.0},	/* position of rockets on */
		     {0.0, 0.0, 0.0, 1.0},	/* plane */
		     {0.0, 0.0, 0.0, 1.0},
		     {0.0, 0.0, 0.0, 1.0}};

/*
 *  computed plane design parameters
 */
float gefy;			/* maximum height for ground effect */
float fuel_rate;		/* fuel consumption rate */
float ipi_AR;			/* 1.0 / pi * wing Aspect Ratio */
float ie_pi_AR;			/* 1.0 / pi * AR * efficiency */

/*
 *  variable plane design parameters
 */
float inverse_mass;		/* 1.0 / mass of plane */
float Lmax_g;			/* Lmax * gravity */
float Lmin_g;			/* Lmin * gravity */

/*
 *  plane state
 */
Matrix ptw;				/* my ptw matrix */
float (*my_ptw)[4];			/* pointer to my matrix	*/
int sidewinders, rockets;		/* number of armaments		*/
float rudder, elevator, rollers;	/* control settings		*/
float vx, vy, vz;			/* plane velocity */
int twist, elevation, azimuth;		/* plane orientation		*/
int roll_speed;				/* roll, elevation, azimuth speeds */
int elevation_speed;			/* in 10'ths degrees per tick	*/
int azimuth_speed;
int flaps, spoilers;			/* flap and spoiler settings	*/
float lift;				/* lift acceleration		*/
int airspeed, last_airspeed;
int climbspeed, last_climbspeed;
short g_limit;				/* TRUE if wing g-limit is hit	*/
short wing_stall;			/* TRUE if wing is stalling	*/
short on_ground;			/* TRUE if plane is on ground	*/
short on_hill;				/* TRUE if plane is on hill	*/
short wheels;				/* TRUE if the wheels are down	*/
short wheels_retracting;		/* used only			*/
short landing_gear_stuck;		/* >= 0 if the gear is stuck	*/
int fuel;				/* fuel (0 - 12800)		*/
int thrust;				/* thrust (0 - 100)		*/
int throttle;				/* throttle (0 - 100)		*/
int max_throttle;			/* upper limit on engines	*/
int min_throttle;			/* lower limit on engines	*/
float last_px, last_py, last_pz;	/* last plane position		*/
float max_cl, min_cl;			/* max and min coefficient of lift */
float tilt_factor;			/* wing angle tilt due to flaps	*/
float Splf, Spdf;			/* spoiler factors on lift and drag */
float mach;				/* mach #, crest critical #, ratio */
float Cdp;				/* coefficient of parasitic drag */

/*
 *  autopilot state
 */
short autopilot_on;			/* TRUE in autopilot mode */
int target_twist;			/* target twist for autopilot */
int target_speed;			/* target speed for autopilot */
int target_climb;			/* target climb for autopilot */

/*
 *  crash state
 */
int stick_xadd, stick_yadd;
int sb_xadd, sb_yadd;

/*
 *  missile status
 */
long missile_target;		/* plane my missile is after	*/
long missile_target_timeout;	/* timeout for missile tracking */
float missile_vx,		/* missile velocity */
      missile_vy,
      missile_vz;
float missile_eye[4] = {0.0, 5.0, 0.0, 1.0};	/* missiles eye position */
int mvpos = 0;
int mvspos = 0;
int mvfollow = 1;

/*
 *  wingman history
 */
int wm_twist[10];
int wm_elevation[10];
int wm_azimuth[10];
float wm_x[10], wm_y[10], wm_z[10];
int wmpos = 0;
int wmspos = 0;
int wmfollow = 5;

/*
 *  view state
 */
short view_switch;
int wingman_view = 0;
int missile_view = 0;
int cam_az = 0, cam_el = 900;
float cam_x, cam_y, cam_z;
float cam_dist = 100.0;			/* stuff for plane camera */
int fov = 600;				/* field of view */
int plane_fov, tower_fov;		/* plane, tower field of view */
float ar = 2.0;				/* aspect rationo */
long dist_for_lines;			/* distance to draw building lines */
int view_angle;				/* rotation of pilot's head */
int fogit = FALSE;
int texit = FALSE;
float eye_x, eye_y, eye_z;		/* eye position	 */
float current_eye[4];			/* current eye position */
float frustum[4][4];
float clip_planes[4][4];


flight(argc, argv)
    int argc;
    char *argv[];
{
    register int itemp;		/* temp integer variable	*/

    float temp;				/* temp float variable	*/

    register Plane ptemp, pp;		/* my plane data structure	*/


static char usage[] = "Usage: flight  [-bdhnsO] [-i filename] [-o filename] [-D datadirectory] [-T ttl] [-I addr]\n";

    test_mode = FALSE;

    strncpy(datadir, DATADIR, 80);

    /*
     *  the web build preloads defs/ at DATADIR; a native run has no such
     *  mount, so fall back to the defs/ directory beside the demo source
     *  (still overridable with -D below)
     */
    if (access(datadir, F_OK) < 0)
	strncpy(datadir, "defs/", 80);

    if (strcmp(argv[0] + strlen(argv[0]) - strlen("shadow"), "shadow") == 0)
    {
	shadow = TRUE;
	dogfight = TRUE;
    }
    else if (strcmp(argv[0] + strlen(argv[0]) - strlen("radar"), "radar") == 0)
    {
	radar = TRUE;
	dogfight = TRUE;
    }
    else if (strcmp(argv[0] + strlen(argv[0]) - strlen("dog"), "dog") == 0)
	dogfight = TRUE;

    /*
     *  parse command line arguments
     */
    while (--argc > 0 && **++argv == '-')
    {
	register char *token;

	for (token = argv[0] + 1; *token; token++)
	switch (*token)
	{
	    case 'i':
		if (--argc > 0)
		{
		    infile = *++argv;
		    dogfight = TRUE;
		}
		break;
	    case 'o':
		if (--argc > 0)
		{
		    outfile = *++argv;
		    dogfight = TRUE;
		}
		break;
	    case 'b':	/* broadcast */
		multicast = FALSE;
		break;
	    case 'I':
		if (--argc > 0)
		    mcast_ifaddr = *++argv;
		break;
	    case 'T':
		if (--argc > 0)
		    mcast_ttl = atoi(*++argv);
		break;
	    case 'd':
		dials = TRUE;
		break;
	    case 'n':
		dogfight = TRUE;
		break;
	    case 'r':
		radar = TRUE;
		dogfight = TRUE;
		break;
	    case 's':
		shadow = TRUE;
		dogfight = TRUE;
		break;
	    case 'D':
		if (--argc > 0)
		{
		    strncpy(datadir, *++argv, 58);
		    strcat(datadir, "/");
		}
		break;
	    case 'h':
		hud = TRUE;
		break;
	    case 'O':
		new_inst = FALSE;
		break;
	    case 'C':
		force_cmode = TRUE;
		break;
	    case '4':
		bits_cmode = 4;
		break;
	    case 'R':
		force_rgb = TRUE;
		break;
#ifdef EXPER
	    case 'X':
		if (--argc > 0)
		    xmaxscreen = atoi(*++argv);
		if (--argc > 0)
		    ymaxscreen = atoi(*++argv);
		break;
#endif
	    default:
		fprintf(stderr, "unknown option %c\n", *token);
		break;
	}
    }
    if (argc > 0)
    {
	fprintf(stderr, usage);
	exit(0);
    }

    eye_x = TOWER_X;
    eye_y = TOWER_Y;
    eye_z = TOWER_Z;

    /*
     *  initialize toggle settings
     */
    fogit = FALSE;
    {
	char buf[32];
	gversion(buf);
	texit = (strncmp(buf, "GL4DXG-", 7) != 0) &&
		(strncmp(buf, "GL4DLG-", 7) != 0) &&
		(strncmp(buf, "GL4DNP-", 7) != 0) &&
		(getgdesc(GD_TEXTURE) > 0);
    }

    if (shadow)
    {
	init_graphics("shadow");
	InitComm("shadow");
    }
    else if (radar)
    {
	init_graphics("radar");
	InitComm("radar");
    }
    else if (dogfight)
    {
	init_graphics("dog");
	InitComm("plane");
    }
    else
    {
	init_graphics("flight");
	for (itemp=0; itemp < 2; itemp++)
	{
	    pp = (Plane)malloc(sizeof(struct plane));
	    pp->alive = -1;
	    pp->won = 0;
	    pp->lost = 0;
	    PLANE_ID(pp) = 23;
	    strcpy(pp->myname, "myself");
	    planes[itemp] = pp;
	}
	plane_hists[0] = (Plane_hist)malloc(sizeof(struct plane_hist));
    }

    pp = planes[0];

    qreset();

    my_ptw = ptw;

    if (dials)
	init_dials();

    redraw_screen();
    reset_meters();

    if (shadow)
    {
	number_planes = 0;
	display_shadow_help();		/* I do a swapbuffers */
    }
    else if (radar)
    {
	number_planes = 0;
	display_radar_help();		/* I do a swapbuffers */
    }
    else
    {
	number_planes = 2;
	display_help();			/* I do a swapbuffers */
    }

    argc = 0;

    time_start = times(&tms_start_buf);

    if (!radar)
	read_objects(TRUE);
    wait_for_input();

do_restart:
    if (shadow)
    {
	shadow_start();
	shadow_loop();
    }
    else if (radar)
    {
	radar_start();
	radar_loop();
    }
    else
    {
	flight_start();
	flight_loop();
    }

    if (restart)
	goto do_restart;
}



/*
 *  start up code specific to flight
 */
flight_start()
{
    Plane pp = planes[0];
    int itemp;

    switch(restart)
    {
	case START1:			/* come here for default start */
	default:
	    pp->x = START_X;
	    pp->y = START_Y;
	    pp->z = START_Z;
	    azimuth = START_AZIMUTH;
	    vz = 0.0;
	    wheels = TRUE; pp->wheels = 0;
	    break;
	case START2:			/* end of runway start */
	    pp->x = 0.0;
	    pp->y = START_Y;
	    pp->z = -500.0;
	    azimuth = 0;
	    vz = 0.0;
	    wheels = TRUE; pp->wheels = 0;
	    break;
	case START3:			/* airborn start */
	    pp->x = flight_random(20000);
	    pp->y = 8000 + flight_random(6000);
	    pp->z = flight_random(20000);
	    azimuth = flight_random(3600);
	    vz = (flight_random(60)-80)/fps_knots;
	    wheels = FALSE; pp->wheels = 10;
	    break;
	case START4:			/* used for threat runs */
	    pp->x = flight_random(20000);
	    pp->y = 10000 + flight_random(5000);
	    pp->z = 100000.0;
	    azimuth = 0;
	    vz = (flight_random(60)-160)/fps_knots;
	    wheels = FALSE; pp->wheels = 10;
	    break;
    }
    restart = 0;

    for (itemp = number_planes-1; itemp >= 0; itemp--)
	planes[itemp]->alive = -1;
    number_planes = 1;
    reset_meters();
    landing_gear_stuck = -1;		/* can toggle landing gear	*/
    test_mode = FALSE;


    setvaluator(MOUSEX, mousex = xmiddle, 0, xmaxscreen);
    setvaluator(MOUSEY, mousey = ymiddle, 0, ymaxscreen);

    select_plane();

    read_objects(FALSE);

    pp->y += plane_height;	/* add plane_height to plane elevation */

    Cdp = .015;				/* coefficient of parasitic drag*/
    ipi_AR = 1.0/(3.1415927 * b*b/s);	/* 1.0 / pi * wing Aspect Ratio	*/
    ie_pi_AR = ipi_AR/ef;		/* 1.0 / pi * AR * efficiency	*/
    ROLLF *= 10.0/(30.0 * 400.0);
    ELEVF *= 10.0/(20.0 * 400.0);

    debug = timeit = FALSE;
    autopilot_on = wheels = wing_stall = FALSE;
    tick_counter = 2;			/* force text display	*/
    throttle = thrust = pp->thrust = 0;
    roll_speed = elevation_speed = azimuth_speed = 0;
    rudder = elevator = rollers = 0.0;
    airspeed = last_airspeed = climbspeed = last_climbspeed = 0;
    on_ground = (pp->y - plane_height) <= 4.0;
    on_hill = FALSE;
    gefy = .7 * b;
    max_throttle = 100;
    min_throttle = on_ground?-max_throttle:0;
    vx = vy = vx_add = vy_add = vz_add = 0.0;
    lift = 0.0;	mach = 0.0;
    sidewinders = MAX_SW;
    rockets = MAX_RK;
    pp->mstatus = 0;
    pp->weapon_state = PS_WEAPONS >> PS_W_SHIFT;
    missile_target = NULL_PLANE_ID;
#define compute_mass() (G_ACC / \
	(W + fuel/12800.0*fuel_weight + ((sidewinders+rockets)<<9)))
    fuel = 100 << 7;
    inverse_mass = compute_mass();

    view_switch = PLANE_VIEW;			/* view from plane	*/
    if (hud)
	plane_fov = tower_fov = 400;
    else
	plane_fov = tower_fov = 360;
    reset_fov(plane_fov);

    last_py = pp->y;
    pp->elevation = elevation = 0;
    pp->twist = twist = 0;
    pp->azimuth = azimuth;
    pp->status = MSTART;
    pp->alive = int_tps << 2;
    flaps = spoilers = 0;
    view_angle = 0;
    fuel_rate = fuel_consump(Mthrust, W);
    rebuild_status();

    /*
     *  init wingman info
     */
    for (wmpos = 0; wmpos < 10; wmpos++)
    {
	wm_x[wmpos] = pp->x;
	wm_y[wmpos] = pp->y;
	wm_z[wmpos] = pp->z;
	wm_twist[wmpos] = twist;
	wm_elevation[wmpos] = elevation;
	wm_azimuth[wmpos] = azimuth;
    }
    wmspos = wmfollow;
    wmpos = 0;

    if (dogfight || shadow)
    {
	for (itemp=0; itemp < MAX_PLANES; itemp++)
	    get_indata(0);		/* read all input data	*/
	reset_meters();
	display_score();
    }

    if (on_ground)
    {
	qenter(KEYBD, 'f');		/* flaps up 1 notch	*/
	qenter(KEYBD, 'f');		/* flaps up 1 notch	*/
	qenter(KEYBD, 'f');		/* flaps up 1 notch	*/
	Cdp *= 3.0;
    }
    else
    {
	throttle = thrust = pp->thrust = max_throttle;
	qenter(KEYBD, 'F');
    }
    if (on_ground || landing_gear_stuck > 0)
	qenter(KEYBD, 'l');	/* put wheels down	*/
#ifdef AUDIO
    pitch_thrust((float)(oldthrust = pp->thrust)/100.0);
#endif
}




/*
 *  main loop for flight
 */
flight_loop()
{
    unsigned char frame_count = 0;	/* count of frames */
    int itemp;
    Plane pp = planes[0], ptemp;

    while (!restart)
    {
	clearz();	/* do this while all the calculations are happening */
	if (pp->y <= 10.0 && pp->status <= MEXPLODE)
	{
	    cpack(0x0);
	    clear();
	}


	if (dials)
	    check_dials();

#ifdef AUDIO
	if (pp->status > MEXPLODE) play_thrust();
#endif

	read_queue();

	/*
	 *  update time
	 */
	if (!frame_count)
	    update_ftime();		/* every 256 frames */
	frame_count++;

	/****************************************************************
	/*	handle retractable landing gear
	/****************************************************************/
	if (wheels_retracting > 0)		/* going up	*/
	{
	    pp->wheels++;
	    if (pp->wheels >= 10)
	    {
		pp->wheels = 10;
		wheels_retracting = 0;
	    }
	}
	else if (wheels_retracting < 0)		/* going down	*/
	{
	    pp->wheels--;
	    if (pp->wheels <= 0)
	    {
		pp->wheels = 0;
		wheels_retracting = 0;
	    }
	}

	/****************************************************************/
	/*	process incoming data packets
	/****************************************************************/
	pp->alive = int_tps << 2;	/* always make me alive		*/
	if (pp->status > MEXPLODE)
	    if (pp->status > 65000)	/* increment my timestamp	*/
		pp->status = MSTART;
	    else
		pp->status++;
	else if (pp->status > 0)
	    pp->status--;

	if (dogfight)
	{
	    ptemp = get_indata(1);	/* read all input data		*/
	    if (ptemp != NULL)
	    {
		sprintf(charbuf, "You were blown up by an enemy %s fired by %s",
			WEAPON_NAME[ptemp->mtype], ptemp->myname);
		make_crash(charbuf);
	    }
	}

	/*
	 *  If the plane is not crashed to the ground
	 */
	if ((pp->status || !on_ground) && !on_hill)
	{
	    if (autopilot_on)
		autopilot();

	    compute_speeds();

	    update_position();

	    test_position();
	}

	update_missiles();

	draw_scene();

	if (dogfight)
	    draw_messages();		/* display any network messages	*/

	/****************************************************************
	/*	compute new velocities, accelerations
	/****************************************************************/
	if (!hud && !new_inst)
	    draw_clear_meters();	/* sets up viewport, ortho, wm	*/

	/*
	 *  check my missile against my plane
	 */
	if (pp->mstatus && pp->mstatus < MEXPLODE && test_blow_up(pp, pp))
	{
	    sprintf(charbuf, "You were blown up by your own %s",
		    WEAPON_NAME[pp->mtype]);
	    make_crash(charbuf);
	    sprintf(charbuf, "blown up by my own %s", WEAPON_NAME[pp->mtype]);
	    broadcast(charbuf);
	}

	if (pp->mstatus)
	    check_missile(pp);	/* first test for missile hit */

	if (dogfight)
	    send_outdata(pp);	/* send my data out over net */

	if (fuel <= 0)		/* out of gas */
	{
	    throttle = thrust = pp->thrust = 0;
	    max_throttle = 0;
	    min_throttle = 0;
	}

	do_flight();

	/****************************************************************
	/*	display METERS
	/****************************************************************/
	tick_counter--;				/* 7,6,5,4,3,2,1,0 */

	if (!pp->mstatus && missile_target)	/* zero target if one */
	    if (--missile_target_timeout <= 0)
		missile_target = NULL_PLANE_ID;

	if (tick_counter <= 1 && wing_stall && pp->status >= MEXPLODE)
	    ringbell();

	if (tick_counter & 1)
	{					/* only do this on odd ticks */
	    last_airspeed = airspeed;		/* needed for autopilot */
	    last_climbspeed = climbspeed;
	    pp->airspeed = airspeed = -(int)(fps_knots * vz);
	}

	draw_meters();

	if (tick_counter == 0)	/* only update them every second */
	{
	    if (flaps && airspeed > 400-flaps)		/* rip off flaps */
	    {
		for (itemp=flaps; itemp>0; itemp-=10) qenter(KEYBD, 'F');
		Fmax = 0;
	    }
	    if (wheels && airspeed > 400)	/* if airspeed > 400 knots */
	    {
		qenter(KEYBD, 'l');		/* rip off the gear */
		landing_gear_stuck = 0;
	    }

	    /*
	     *  calculate the current tps (ticks per second)
	     *  and reset the tick counter
	     */
	    time_end = times(&tms_end_buf);
	    check_time();
	    time_start = times(&tms_start_buf);
	    tick_counter = int_tps;		/* reset tick counter */
	}

	/*
	 *  addjust flight characteristics for frame rate change
	 */
	vx += vx_add;
	vy += vy_add;
	vz += vz_add;
	missile_vx += missile_vx_add;
	missile_vy += missile_vy_add;
	missile_vz += missile_vz_add;

	tps += tps_add;
	pp->tps = tps;

	fps_knots = tps * (3600.0/6082.0);
	gravity = G_ACC / tps / tps;
	Lmax_g = Lmax * gravity;
	Lmin_g = Lmin * gravity;

	swapbuffers();

    }
}



addplane(Plane p)
{
    int i;
    radar_hist_t *rh;

    number_planes++;

    if (radar)
    {
	for (i=0; i <= number_planes; i++)
	    if (radar_history[i].id == NULL_PLANE_ID)
	    {
		rh = &radar_history[i];
		rh->id = PLANE_ID(p);
		rh->n = 0;
		reset_radar_hist(rh);
		return;
	    }
    }
    else if (!shadow)
    {
	rebuild_status();
	if (dogfight && new_inst)
	{
	    sprintf(charbuf, "Players: %d", number_planes);
	    set_text_meter(1, charbuf, -1);
	}
    }
}


delplane(Plane p)
{
    long i, id;

    number_planes--;

    if (radar)
    {
	id = PLANE_ID(p);
	for (i=0; i < MAX_PLANES; i++)
	    if (id == radar_history[i].id)
	    {
		radar_history[i].id = NULL_PLANE_ID;
		return(number_planes);
	    }
    }
    else if (!shadow)
    {
	rebuild_status();
	if (dogfight && new_inst)
	{
	    sprintf(charbuf, "Players: %d", number_planes);
	    set_text_meter(1, charbuf, -1);
	}
    }
    return(number_planes);
}


rebuild_status()
{
    sprintf(status_text, "%s   Rockets:%d  Sidewinders:%d  Players:%d",
	    plane_type, rockets, sidewinders, number_planes);
}


float fuel_consump(thrust, half_mass)
    float thrust, half_mass;
{
    return(test_mode ? 0.0 : 0.3 * thrust/half_mass);
}


#define CLOCKRATE HZ
#define DY 14

check_time()
{
    register int y, s60;
    register char charbuf[80];
    register float veldiff;
    int current_tps, tps_dif;

    s60 = time_end - time_start;
    if (s60 <= 0)
	s60 = (tms_end_buf.tms_utime-tms_start_buf.tms_utime) +
	      (tms_end_buf.tms_stime-tms_start_buf.tms_stime);
    if (s60 == 0)
	s60 = 1;

    current_tps = int_tps * CLOCKRATE / s60;

    if (timeit)				/* display the timeing info */
    {
	clear_report();

	y = (DY * 3) + 5;

	add_report_line(150, 0.80, "Times for main loop:");

	sprintf(charbuf, "    %d in %d.%02d seconds",
		int_tps, s60/CLOCKRATE, (s60%CLOCKRATE)*1000/CLOCKRATE/10);
	add_report_line(150, 0.55, charbuf);

	sprintf(charbuf, "    %d msecs per call", s60*1000/CLOCKRATE/int_tps);
	add_report_line(150, 0.30, charbuf);

	sprintf(charbuf, "    %d per second", current_tps);
	add_report_line(150, 0.05, charbuf);

	if (!hud && !shadow)
	{
	    frontbuffer(TRUE);
	    clear_report_area();
	    draw_report();
	    frontbuffer(FALSE);
	}
    }

    tps = int_tps;

    if (current_tps == int_tps)
    {
	vx_add = vy_add = vz_add =
	missile_vx_add = missile_vy_add = missile_vz_add =
	tps_add = 0.0;
	return;
    }
    else if (current_tps > int_tps)
    {
	tps_dif = (current_tps - int_tps) / 3 + 1;
    }
    else /* (current_tps < int_tps) */
    {
	tps_dif = (current_tps - int_tps) / 3 - 1;
	if (int_tps+tps_dif < 3)
	    tps_dif = 3 - int_tps;
    }
    veldiff = int_tps / (float)(int_tps + tps_dif);
    int_tps += tps_dif;
    tps_add = tps_dif / (float)int_tps;

    vx_add = ((vx * veldiff) - vx) / int_tps;
    vy_add = ((vy * veldiff) - vy) / int_tps;
    vz_add = ((vz * veldiff) - vz) / int_tps;
    missile_vx_add = ((missile_vx * veldiff) - missile_vx) / int_tps;
    missile_vy_add = ((missile_vy * veldiff) - missile_vy) / int_tps;
    missile_vz_add = ((missile_vz * veldiff) - missile_vz) / int_tps;
}


check_dials()
/* Check the dial and button box, and load the apropriate value onto
 * the cue.  The dials are as follows:
 *
 *	DIAL0 = Thrust up/down.
 *	DIAL1 = Flaps up/down.
 *	DIAL2 = Spoilers up/down.
 *	DIAL4 = Tower veiw in/out.	*/
{

    long value;
    int i;

    /* Check for thrust */
    value = getvaluator(DIAL0) - 200;
    if (value <= -10)
    {
	setvaluator(DIAL0, 200, 0, 400);
	for (i = 0 ; i >= (value/10) ; i--)
	    qenter(KEYBD, 'a');
    }
    if (value >= 10)
    {
	setvaluator(DIAL0, 200, 0, 400);
	for (i = 0 ; i <= (value/10) ; i++)
	    qenter(KEYBD, 's');
    }

    /* Check for flaps */
    value = getvaluator(DIAL1) - 50;
    if (value <= -10)
    {
	setvaluator(DIAL1, 50, 0, 100);
	for (i = 0 ; i >= (value/10) ; i--)
	    qenter(KEYBD, 'F');
    }
    if (value >= 10)
    {
	setvaluator(DIAL1, 50, 0, 100);
	for (i = 0 ; i <= (value/10) ; i++)
	    qenter(KEYBD, 'f');
    }

    /* Check the spoilers */
    value = getvaluator(DIAL2) - 30;
    if (value <= -10)
    {
	setvaluator(DIAL2, 30, 0, 60);
	for (i = 0 ; i >= (value/10) ; i--)
	    qenter(KEYBD, 'C');
    }
    if (value >= 10)
    {
	setvaluator(DIAL2, 30, 0, 60);
	for (i = 0 ; i <= (value/10) ; i++)
	    qenter(KEYBD, 'c');
    }

    /* Check the tower view */
    value = getvaluator(DIAL4) - 240;
    if (value <= -10)
    {
	setvaluator(DIAL4, 240, 0, 480);
	for (i = 0 ; i >= (value/10) ; i--)
	    qenter(KEYBD, 'z');
    }
    if (value >= 10)
    {
	setvaluator(DIAL4, 240, 0, 480);
	for (i = 0 ; i <= (value/10) ; i++)
	    qenter(KEYBD, 'x');
    }
}


/*
 *  Initialize the dials to the correct values
 */
init_dials()
{
	setvaluator(DIAL0, 200, 0, 400);
	setvaluator(DIAL1, 50, 0, 100);
	setvaluator(DIAL2, 30, 0, 60);
	setvaluator(DIAL4, 240, 0, 480);
}


#define TEST_EVENT		\
    if (event_break && qtest())	\
	return			\


/*
 *  read_objects() reads the data files needed by flight.  It is designed
 *  to be run several times.  If event break is set it will check after
 *  each data file read for events pending in the queue.  If it find
 *  events it will abort.
 */
read_objects(event_break)
    int event_break;
{
    static int objects_to_read = TRUE;
    int i;

    if (!objects_to_read)
	return;

    if (!event_break)
	display_wait();

    /*
     *  read object files
     */

    if (!runwayobj)
    {
	strcpy(objfname, objdir);
	strcat(objfname, "runway.d");
	runwayobj = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(runwayobj);
    }

    TEST_EVENT;

    if (!lightsobj)
    {
	strcpy(objfname, objdir);
	strcat(objfname, "lights.d");
	lightsobj = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(lightsobj);
    }

    TEST_EVENT;

    if (!planeobj[C150])
    {
	strcpy(objfname, objdir);
	strcat(objfname, "c150.d");
	planeobj[C150] = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(planeobj[C150]);
    }

    TEST_EVENT;

    if (!planeobj[F16])
    {
	strcpy(objfname, objdir);
	strcat(objfname, "f16.d");
	planeobj[F16] = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(planeobj[F16]);
    }

    TEST_EVENT;

    if (!planeobj[F18])
    {
	strcpy(objfname, objdir);
	strcat(objfname, "f18.d");
	planeobj[F18] = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(planeobj[F18]);
    }

    TEST_EVENT;

    if (!planeobj[B747])
    {
	strcpy(objfname, objdir);
	strcat(objfname, "b747.d");
	planeobj[B747] = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(planeobj[B747]);
    }

    TEST_EVENT;

    if (!planeobj[B727])
    {
	if (!in_cmode)
	{
	    strcpy(objfname, objdir);
	    strcat(objfname, "b727.d");		/* in_cmode uses 747 instead */
	}
	planeobj[B727] = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(planeobj[B727]);
    }

    TEST_EVENT;

    if (!planeobj[P38])
    {
	strcpy(objfname, objdir);
	strcat(objfname, "p38.d");
	planeobj[P38] = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(planeobj[P38]);
    }

    TEST_EVENT;

    if (!planeobj[F14])
    {
	strcpy(objfname, objdir);
	strcat(objfname, "f14.d");
	planeobj[F14] = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(planeobj[F14]);
    }

    TEST_EVENT;

    if (!planeobj[F15])
    {
	if (in_cmode)
	{
	    strcpy(objfname, objdir);
	    strcat(objfname, "f15.d");		/* RGBmode uses F14 instead */
	}
	planeobj[F15] = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(planeobj[F15]);
	if (!in_cmode)
	{
	    setrotation(planeobj[F15], 2, -480, 'y');
	    setrotation(planeobj[F15], 3, 480, 'y');
	}
    }

#if 0
    TEST_EVENT;

    if (!planeobj[STEALTH])
    {
	strcpy(objfname, objdir);
	strcat(objfname, "stealth.d");
	planeobj[STEALTH] = readobj(objfname);
    }
#endif

    TEST_EVENT;

    if (!buildingsobj)
    {
	if (in_cmode)
	{
	    for (i = 0; i < NUM_BUILDINGS; i++)
	    {
		float x, y, z;

		sprintf(objfname, "%sbci%d.d", objdir, i);
		buildingsobj = readobj(objfname);
		avg_verts(buildingsobj, &x, &y, &z);
		if (bits_cmode < 6)
		    remap_obj(buildingsobj);

		add_obj(BUILDING_OBJ, x, y, z, buildingsobj);
	    }
	}
	else
	{
	    strcpy(objfname, objdir);
	    strcat(objfname, "buildings.d");
	    buildingsobj = readobj(objfname);
	}
    }

    TEST_EVENT;

    if (!mtnsobj)
    {
	strcpy(objfname, objdir);
	strcat(objfname, "mtns.d");
	mtnsobj = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(mtnsobj);
    }

    TEST_EVENT;

    if (!swobj)
    {
	strcpy(objfname, objdir);
	strcat(objfname, "sw.d");
	swobj = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	    remap_obj(swobj);
    }

    TEST_EVENT;

    if (!threatobj)
    {
	strcpy(objfname, objdir);
	strcat(objfname, "threat.d");
	if (in_cmode)
	{
	    threatobj = readobj(objfname);
	    settranslation(threatobj, 0, 6000.0, 0.0, 14000.0);
	    setscale(threatobj, 1, 17000.0, 17000.0, 17000.0);
	    if (bits_cmode < 6)
		remap_obj(threatobj);
	    add_obj(THREAT_OBJ, 6000.0, 0.0, 14000.0, threatobj);

	    threatobj = readobj(objfname);
	    settranslation(threatobj, 0, -20000.0, 0.0, 15000.0);
	    setscale(threatobj, 1, 10700.0, 10700.0, 10700.0);
	    if (bits_cmode < 6)
		remap_obj(threatobj);
	    add_obj(THREAT_OBJ, -20000.0, 0.0, 15000.0, threatobj);

	    threatobj = readobj(objfname);
	    settranslation(threatobj, 0, 3000.0, 0.0, 34000.0);
	    setscale(threatobj, 1, 2700.0, 2700.0, 2700.0);
	    if (bits_cmode < 6)
		remap_obj(threatobj);
	    add_obj(THREAT_OBJ, 3000.0, 0.0, 34000.0, threatobj);
	}
	else
	{
	    threatobj = readobj(objfname);
	}
    }

    TEST_EVENT;

    if (!hillsobj && !in_cmode)
    {
	strcpy(objfname, objdir);
	strcat(objfname, "hills.d");
	hillsobj = readobj(objfname);
	strcpy(objfname, datadir);
	strcat(objfname, "hills.grid");
	hillsgrid = read_grid(objfname);
    }

    if (in_cmode)
    {
	for (i = 0; i < MAX_PLANES; i++)
	{
	    sort_plane[i].type = PLANE_OBJ;
	    sort_plane[i].id = i;
	    sort_missile[i].type = MISSILE_OBJ;
	    sort_missile[i].id = i;
	}
    }

    objects_to_read = FALSE;
}


/*
 *  stopit() will iconify flight and get it up and running again when the user
 *  restarts it.
 */
stopit()
{
#ifdef FIX_XXX
    extern PSFILE *PostScript;
    short dummy;

    /*
     *  do most of same stuff as when we exit in ExitComm()
     */
    restore_map();

    /*
     *  clear the pup underlay and color planes
     */
    viewport(0, xmaxwindow, 0, ymaxwindow);
    drawmode(PUPDRAW);
    color(0);
    clear();
    drawmode(UNDERDRAW);
    color(0);
    clear();
    drawmode(NORMALDRAW);
    frontbuffer(TRUE);
    cpack(0);
    clear();
    frontbuffer(FALSE);

    /*
     *	flight will iconify and suspend apon flipiconic().  The code following
     *  flipiconic will get flight up and running again.
     */
    flipiconic(winget());
    winpop();	/* This is a kludge to keep flight from continuing before */
		/* iconifying */

    while (qread(&dummy) != REDRAW);	/* will hang here until uniconified */

    winpop();	/* This is a kludge to keep flight from continuing before */
		/* its window id bits have been painted */

    if (dogfight)
	init_graphics("dog");
    else
	init_graphics("flight");

    if (dials) init_dials();

    /*
     *  restore mouse position
     */
    setvaluator(MOUSEX, mousex, 0, xmaxscreen);
    setvaluator(MOUSEY, mousey, 0, ymaxscreen);

    winpop();	/* make sure at top! */
    redraw_screen();
#endif
}


/*
 *  read all queue entries
 */
read_queue()
{
    short type, val;
    float temp;
    Plane pp = planes[0], ptemp;

    while (qtest())
    {
	switch (type = qread(&val))
	{
	    case KEYBD:
		switch (val)
		{
		    case 27:
			end_of_program();
		    case 'b':
			bell = !bell;
			setbell(bell);
			break;
		    case 'a':
			throttle -= 5;
			if (throttle < min_throttle)
			    throttle = min_throttle;
			break;
		    case 's':
			throttle += 5;
			if (throttle > max_throttle)
			    throttle = max_throttle;
			break;
#ifdef AUDIO
		    case 'S':
			if (--sound_mode < 0) sound_mode = 2;
			break;
#endif
		    case 'z':
		    case 'x':
			if (view_switch == TOWER_VIEW)
			{
			    if (val == 'x')
			    {
				if (tower_fov > 30) tower_fov -= 25;
			    }
			    else
			    {
				if (tower_fov < 600) tower_fov += 25;
			    }
			    reset_fov(tower_fov);
			}
			else if (missile_view)
			{
			    if (val == 'x')
			    {
				if (mvfollow > 0) mvfollow--;
			    }
			    else
				if (mvfollow < 9) mvfollow++;
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
			if (view_switch != TOWER_VIEW)
			{
			    view_switch = TOWER_VIEW;
			    eye_x = TOWER_X;
			    eye_y = TOWER_Y;
			    eye_z = TOWER_Z;
			    reset_fov(tower_fov);
			}
			else
			{
			    view_switch = PLANE_VIEW;
			    reset_fov(plane_fov);
			}
			break;
		    case 'Q':
			missile_view = !missile_view;
			break;
		    case 'W':
			wingman_view = !wingman_view;
			break;
		    case '-':
			cam_dist -= 15.0;
			break;
		    case '=':
			cam_dist += 15.0;
			break;
		    case 'v':
			autopilot_on = !autopilot_on;
			if (autopilot_on)
			{
			    target_speed = airspeed;
			    target_climb = climbspeed;
			    target_twist = twist;
			}
			break;
		    case 'f':
		    case 'F':
			if (val == 'f')
			{
			    if (flaps < Fmax) flaps += 10;
			}
			else
			{
			    if (flaps > 0) flaps -= 10;
			}
			max_cl = 1.5 + flaps/62.5;
			min_cl = flaps/62.5 - 1.5;
			tilt_factor = .005 * flaps + .017;
			break;
		    case 'c':
		    case 'C':
			if (val == 'c')
			{
			    if (spoilers < Smax) spoilers += 20;
			}
			else
			{
			    if (spoilers > 0) spoilers -= 20;
			}
			Spdf = .0025 * spoilers;    /* adjust drag and lift */
			Splf = 1.0 - .005 * spoilers;
			break;
		    case 'l':
			if (landing_gear_stuck != wheels)
			{
			    if (wheels)
			    {
				wheels = FALSE;
				Cdp /= 2.0;
				wheels_retracting = 1;
				if (on_ground && pp->status > MEXPLODE)
				{
make_crash("You retracted the landing gear while on the ground");
broadcast("retracted my landing gear while on the ground");
				}
			    }
			    else
			    {
				wheels = TRUE;
				wheels_retracting = -1;
				Cdp *= 2.0;
			    }
			}
			break;
		    case 't':
			/* if I'm alive and no weapon already fired */
			if (pp->status > MEXPLODE && !pp->mstatus)
			{
			    if (ptemp = find_closest_plane(pp))
			    {
				/* lock on the plane for 1 second */
#ifdef AUDIO
				play_samps( locksample, locklength);
#endif
				missile_target = PLANE_ID(ptemp);
				missile_target_timeout = int_tps;
				if (ptemp)
				{
				    sprintf(charbuf, "Locked on->%s",
					    ptemp->myname);
				    set_text_meter(0, charbuf, int_tps);
				}
			    }
			}
			break;
		    case 'q':
			launch_missile(TYPE_ROCKET);
			break;
		    case 'w':
			launch_missile(TYPE_SIDEWINDER);
			break;
		    case 'e':
			launch_missile(TYPE_CANNON);
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
		    case 'H':
			/*
			 *  switch from hud to instrument panel
			 */
			hud = !hud;
			redraw_screen();
			if (!hud)
			{
			    clear_report_card();
			    plane_fov = 360;
			    dist_for_lines >>= 1;
			}
			else
			{
			    plane_fov = 400;
			    dist_for_lines <<= 1;
			}
			if (view_switch == TOWER_VIEW)
			    reset_fov(tower_fov);
			else
			    reset_fov(plane_fov);
			break;
		    case 'r':
		    case 'R':
		    case 'u':
		    case 'U':
			if (pp->status == 0)
			    if      (val == 'r')    restart = START1;
			    else if (val == 'R')    restart = START2;
			    else if (val == 'u')    restart = START3;
			    else /* (val == 'U') */ restart = START4;
			else
			    /*
			     *  if missile launched, then blow it up
			     */
			    if (pp->mstatus > MEXPLODE &&
				(pp->mtype == TYPE_ROCKET ||
				 pp->mtype == TYPE_SIDEWINDER))
				pp->mstatus = MEXPLODE;
			break;
		    case 'T':
			threat_mode = !threat_mode;
			break;
		    case 'I':    /* iconize and suspend */
			stopit();
			break;
		    case '~':
			test_mode = !test_mode;
			fuel_rate = fuel_consump(Mthrust, W);
			sidewinders = rockets = 0;
			rebuild_status();
			break;
		    case '?':
			timeit = !timeit;
			break;
		    case '':
			wait_for_input();
			break;
#ifdef DEBUG
		    case '-':
		    case '_':
			if (dogfight)
			    rewind_if(-10);
			break;
		    case '+':
		    case '=':
			if (dogfight)
			    rewind_if(10);
			break;
		    case '':
			view_switch = -view_switch;
			break;
		    case 'P':
			wait_for_input();
			break;
		    default:
			if (val >= '0' && val <= '9')
			debug ^= 1 << (val-'0');
#endif
		}
		break;
	    case MOUSEX:
		mousex = val;
		break;
	    case MOUSEY:
		mousey = val;
		break;
	    case SBTX:
		sbtx = val;
		break;
	    case SBTZ:
		sbtz = val;
		break;
	    case F1KEY:		/* toggle fog */
		if (val)
		    fogit = !fogit && !in_cmode && (getgdesc(GD_FOGVERTEX) > 0);
		break;
	    case F2KEY:		/* toggle texturing */
		if (val)
		    texit = !texit && !in_cmode && (getgdesc(GD_TEXTURE) > 0);
		break;
	    case REDRAW:
		redraw_screen();
		break;
	    case WINQUIT:
		end_of_program();
		break;
	    case MOUSE3:
	    case SBBUT6:
		if (val)
		    if (rudder > -.75)
			rudder -= .1;
		break;
	    case MOUSE2:
	    case SBBUT7:
		if (val)
		    rudder = 0;
		break;
	    case MOUSE1:
	    case SBBUT8:
		if (val)
		    if (rudder < .75)
			rudder += .1;
		break;
	    case SBPICK:
		launch_missile(TYPE_CANNON);
		break;
	    case SBBUT2:
		launch_missile(TYPE_ROCKET);
		break;
	    case SBBUT3:
		launch_missile(TYPE_SIDEWINDER);
		break;
	    case LEFTARROWKEY:
		if (val &&(view_switch==PLANE_VIEW))
		{
		    view_angle -= 50;
		    if (view_angle <= -1800)
			view_angle += 3600;
		}
		break;
	    case RIGHTARROWKEY:
		if (val && (view_switch == PLANE_VIEW))
		{
		    view_angle += 50;
		    if (view_angle > 1800)
			view_angle -= 3600;
		}
		break;
	    case UPARROWKEY:
		if (val && (view_switch == PLANE_VIEW))
		    view_angle = 0;
		break;
	    case DOWNARROWKEY:
		if (val && (view_switch == PLANE_VIEW))
		    view_angle = 1800;
		break;
	    default:
		break;
	}	/* of switch qread */
    }		/* of while qtest */
}


/*
 *  auto pilot routine
 */
autopilot()
{
    int itemp, diff;
    Plane pp = planes[0];

    itemp = mousey;
    /* first adjust the roll ??? XXX	*/

    /*
     *  adjust speed next
     */
    diff = target_speed - airspeed - ((airspeed-last_airspeed)<<3);
    diff = (diff+4) >> 3;
    if (diff > 0)		/* need more acceleration	*/
    {
	if (throttle < max_throttle)
	    throttle += diff;		/* try engines first */
	else if (!on_ground)
	{				/* next wheels and yaw	*/
	    if (flaps && vz < -400.0/TPS)
		qenter(KEYBD, 'F');
	    else if (rudder > 0.05)
		rudder -= .1;
	    else if (rudder < -0.05)
		rudder += .1;
	    else
		setvaluator(MOUSEY,	/* lastly pitch		*/
			   mousey = (itemp+=(int)(diff/-ELEVF/vz)),
			   0, ymaxscreen);
	}
    }
    else if (diff < 0)		/* need less acceleration	*/
    {
	throttle += diff;		/* reduce thrust		*/
	if (throttle < min_throttle)
	    throttle = min_throttle;
    }

    /*
     *  adjust climb last - this has highest priority
     */
    diff = target_climb - climbspeed -
	   ((climbspeed-last_climbspeed) << 7);
    diff = (diff+4) >> 4;

    if (wing_stall)
    {
	if (throttle < max_throttle)
	    throttle += 10;
	if (spoilers)
	    qenter(KEYBD, 'C');
    }
    else if (diff != 0)
    {
	if (twist > 900 && twist < 2700)
	    diff = -diff;
	setvaluator(MOUSEY, mousey = (itemp+=(int)(diff/ELEVF/vz)),
		    0, ymaxscreen);
    }
    if (throttle > max_throttle)
	throttle = max_throttle;
}


#define TDELAY (TPS/4) /*XXX*/

/*
 *  compute roll_speed, elevation_speed, azimuth_speed and
 *  wing stall
 */
compute_speeds()
{
    int itemp;
    float temp;
    Plane pp = planes[0];
    short tmpx, tmpy;
    int centered;		/* is the spaceball centered */
    static int still = TRUE;	/* is the spaceball in use */

    /*
     *  check if spaceball is in use
     */
    tmpx = sbtx;
    tmpy = sbtz;

    centered = !(tmpx || tmpy);

    if (!centered || !still)
    {
	still = centered;

	tmpx = ((tmpx * xmiddle) >> 13) + xmiddle;
	tmpy = ((tmpy * ymiddle) >> 13) + ymiddle;
	if (tmpx > xmaxscreen) tmpx = xmaxscreen;
	else if (tmpx < 0) tmpx = 0;
	if (tmpy > ymaxscreen) tmpy = ymaxscreen;
	else if (tmpy < 0) tmpy = 0;

	if (pp->status <= MEXPLODE)
	{
	    sb_xadd += flight_random(20);
	    tmpx += sb_xadd;
	    sb_yadd += flight_random(20);
	    tmpy += sb_yadd;
	}

	setvaluator(MOUSEX, mousex = tmpx, 0, xmaxscreen);
	setvaluator(MOUSEY, mousey = tmpy, 0, ymaxscreen);
    }

    /*
     *  start calculations
     */
    /* tenths of degrees per tick	*/
    pp->rollers = mousex;
    if (pp->status <= MEXPLODE)
    {
	pp->rollers += stick_xadd + flight_random(20);
	setvaluator(MOUSEX, mousex = pp->rollers, 0, xmaxscreen);
    }
    pp->rollers -= xmiddle - 8;
    rollers = ROLLF * (pp->rollers >> 4);
    itemp = rollers * vz - roll_speed;	/* delta	*/
    if (itemp!=0)
	if (itemp >= TDELAY || itemp <= -TDELAY)
	    itemp /= TDELAY;
	else
	    itemp = itemp>0 ? 1 : -1;
    if (wing_stall > 0)
    {
	itemp >>= wing_stall;
	itemp += flight_random(wing_stall << 3);
    }
    roll_speed += itemp;

    pp->elevator = mousey;
    if (pp->status <= MEXPLODE)
    {
	pp->elevator += stick_yadd + flight_random(20);
	setvaluator(MOUSEY, mousey = pp->elevator, 0, ymaxscreen);
    }
    pp->elevator -= ymiddle - 8;
    elevator = ELEVF * (pp->elevator >> 4);
    itemp = elevator * vz + vy - elevation_speed;
    if (itemp!=0)
	if (itemp >= TDELAY || itemp <= -TDELAY)
	    itemp /= TDELAY;
	else
	    itemp = itemp>0 ? 1 : -1;
    if (wing_stall > 0)
    {
	itemp >>= wing_stall;
	itemp += flight_random(wing_stall << 1);
    }
    elevation_speed += itemp;

    temp = rudder * vz - 2.0 * vx;
    if (on_ground)
    {
#define MAX_TURNRATE (600/TPS) /*XXX*/
	itemp = 16.0 * temp;
	if (itemp < -MAX_TURNRATE || itemp > MAX_TURNRATE)
	{
	    if (itemp < 0)		/* clip turn rate	*/
		itemp = -MAX_TURNRATE;
	    else
		itemp = MAX_TURNRATE;
	    if (fabs(vz) > 10.0/TPS)	/* decrease with velocity */
	    {
		temp = 0.4 * TPS * (rudder*vz - .75); /* skid effect */
		if (temp < -MAX_TURNRATE || temp > MAX_TURNRATE)
		    temp = itemp;
		itemp -= temp;
	    }
	}
    }
    else
	itemp = temp;	/* itemp is desired azimuth speed	*/
    itemp -= azimuth_speed;	/* itemp is now desired-actual		*/

    if (itemp!=0)
	if (itemp >= TDELAY || itemp <= -TDELAY)
	    itemp /= TDELAY;
	else
	    itemp = itemp>0 ? 1 : -1;
    azimuth_speed += itemp;

    if (on_ground)
    {
	/*
	 * dont allow negative pitch unless positive elevation
	 */
	if (elevation_speed < 0)
	{
	    if (elevation <= 0)
		elevation_speed = 0;
	}
	else		/* mimic gravitational torque	*/
	{
	    itemp = -((int)vz * int_tps + MIN_LIFT_SPEED) >> 2;
	    if (itemp < 0 && elevation <= 0)
		itemp = 0;
	    if (elevation_speed > itemp)
		elevation_speed = itemp;
	}
	roll_speed = 0;
    }
}


/*
 *  update_position() updates the vehicles position, azimuth, elevation,
 *  twist, and velocity.  Based on it's velocity and rotational speeds
 */
update_position()
{
    float elev_rad;	/* elevation in radians */
    float cos_elev;	/* cosine of elevation */
    float temp;
    register Matrix incremental;	/* temp matrix	*/
    Plane pp = planes[0];
    float vscale;

    /*
     *	concat incremental rotations and get new angles back
     */
    identify_matrix(ptw);
    matrix_translate(ptw, pp->x, pp->y, pp->z);
    matrix_rotate(ptw, azimuth, 'y');
    matrix_rotate(ptw, elevation, 'x');
    matrix_rotate(ptw, twist, 'z');

    if (pp->status > MEXPLODE || !on_ground)
    {
	matrix_translate(ptw, vx, vy, vz);
	if (azimuth_speed) matrix_rotate(ptw, azimuth_speed, 'y');
	if (elevation_speed) matrix_rotate(ptw, elevation_speed, 'x');
	if (roll_speed) matrix_rotate(ptw, roll_speed, 'z');
    }
    else
    {
	vscale = pp->status / 20.0;
	matrix_translate(ptw, vx*vscale, vy*vscale, vz*vscale);
	if (azimuth_speed) matrix_rotate(ptw, azimuth_speed*vscale, 'y');
	if (elevation_speed) matrix_rotate(ptw, elevation_speed*vscale, 'x');
	if (roll_speed) matrix_rotate(ptw, roll_speed*vscale, 'z');
    }

    /*
     *  analyze new ptw
     */
    elev_rad = -fasin(ptw[2][1]);
    temp = elev_rad * (1800.0/M_PI);
    /*
    temp = -xasin(ptw[2][1]);
    */
    elevation = (temp < 0)? temp-0.5: temp + 0.5;
    cos_elev = fcos(elev_rad);
    /*
    gl_sincos(elevation, NULL, &cos_elev);
    */
    if (cos_elev != 0.0)
    {

	temp = ptw[2][0]/cos_elev;
	if (temp >= 1)
	    azimuth = 900;
	else if (temp <= -1)
	    azimuth = -900;
	else
	{
	    temp = fasin(ptw[2][0]/cos_elev) * (1800.0/M_PI);
	    /*
	    temp = xasin(ptw[2][0]/cos_elev);
	    */
	    azimuth = (temp < 0)? temp-0.5: temp + 0.5;
	}
	if (ptw[2][2] < 0.0)		/* if heading into z	*/
	    azimuth = 1800 - azimuth;	/* then adjust		*/
	if (azimuth < 0)
	    azimuth += 3600;

	temp = xasin(ptw[0][1]/cos_elev);
	/*
	temp = fasin(ptw[0][1]/cos_elev) * (1800.0/M_PI);
	*/
	twist = (temp < 0)? temp-0.5: temp + 0.5;
	if (ptw[1][1] < 0.0)		/* if upside down	*/
	    twist = 1800 - twist;
	if (twist < 0)
	    twist += 3600;
    }
    last_px = pp->x;			/* save last position	*/
    last_py = pp->y;
    last_pz = pp->z;
    pp->x = ptw[3][0];
    pp->y = ptw[3][1];
    pp->z = ptw[3][2];
    climbspeed = TPS * (pp->y - last_py);

    wm_x[wmspos] = pp->x;
    wm_y[wmspos] = pp->y;
    wm_z[wmspos] = pp->z;
    wm_twist[wmspos] = twist;
    wm_elevation[wmspos] = elevation;
    wm_azimuth[wmspos] = azimuth;
    wmpos = wmspos - wmfollow;
    if (wmpos < 0)
	wmpos += 10;
    wmspos = (wmspos+1) % 10;

    /*
     *	perform incremental rotations on velocities
     */
    identify_matrix(incremental);
    if (roll_speed) matrix_rotate(incremental, -roll_speed, 'z');
    if (elevation_speed) matrix_rotate(incremental, -elevation_speed, 'x');
    if (azimuth_speed) matrix_rotate(incremental, -azimuth_speed, 'y');
    matrix_translate(incremental, vx, vy, vz);
    vx = incremental[3][0];
    vy = incremental[3][1];
    vz = incremental[3][2];
}


/*
 *  test_position() tests for colisions, landing and flame out.
 */
test_position()
{
    Plane pp = planes[0];

    /*
     *  check altitude for too high, and landing/takeoff
     */
    if (pp->y > 50000.0)
	throttle = thrust = pp->thrust = 0;	/* flame out		*/
    else if ((pp->y - plane_height) > 4.0)	/* not on ground	*/
    {
	if (on_ground)			/* if was on ground	*/
	{
	    clear_report_card();		/* clear report card	*/
	    Cdp /= 3.0;			/* decrease drag	*/
	    min_throttle = 0;		/* no reverse engines	*/
	    on_ground = FALSE;
	}
    }
    else if ((pp->y - plane_height) < .5)	/* check for on the ground */
    {
	if (IN_BOX(pp,  -800.0,  100.0, -9500.0,  1000.0) ||
	    IN_BOX(pp,   100.0, 1300.0, -2500.0, -1500.0) ||
	    IN_BOX(pp, -2300.0, -800.0, -4900.0, -2000.0))
	{
	    /*
	     *  landing on a runway
	     */
	    if (!on_ground)
	    {
		int rating, nm;

		Cdp *= 3.0;			/* increase drag	*/

		rating = report_card(-climbspeed, twist, (int)(vx * TPS),
				     (int)(-vz * fps_knots), wheels, pp);

		if (rating == -1)		/* oops - you crashed	*/
		{
		    pp->status = MEXPLODE;	/* set to exploding	*/
		    pp->lost++;		/* increment count	*/
		}
		else
		{
		    fuel += rating << 7;
		    if (fuel > (100 << 7))
			fuel = 100 << 7;
		    max_throttle = 100;
		}
		min_throttle = -max_throttle; /* allow reverse engines*/

		rating = rating/10;	/* number of added missiles	*/

		/*
		 *  add sidewinders
		 */
		nm = MAX_SW - sidewinders;		/* need this many */
		if (nm > 0)
		{
		    if (nm > rating)
			nm = rating;		/* get this many */
		    sidewinders += nm;
		    rating -= nm;
		}

		/*
		 *  add rockets
		 */
		nm = MAX_RK - rockets;		/* need this many */
		if (nm > 0)
		{
		    if (nm > rating)
			nm = rating;	/* get this many */
		    rockets += nm;
		}

		test_mode = FALSE;
		fuel_rate = fuel_consump(Mthrust, W);
		rebuild_status();
	    }
	}
	else
	{
	    if (pp->status > MEXPLODE)
	    {
		make_crash("You crashed into the swamps");
		broadcast("crashed into the swamps");
	    }
	    else if (!on_ground)
	    {
		pp->status = MEXPLODE;	/* set to exploding	*/
#ifdef AUDIO
		play_samps(diesample, dielength);
#endif
	    }
	}

	ptw[3][1] = 0.0;
	pp->y = plane_height;
	on_ground = TRUE;
	if (pp->status > MEXPLODE)
	{
	    if (elevation < 0) elevation = 0;/* kill negative elevation */
	    if (twist != 0) twist = 0;	/* kill any twist	*/
	}
    }
#ifdef AUDIO
    if (pp->thrust != oldthrust)
	pitch_thrust((float)(oldthrust = pp->thrust)/100.0);
#endif

    /*
     *  check for collision with hills
     */
    if (!in_cmode)
	if (collide_grid(pp->x, pp->y, pp->z, hillsgrid))
	{
	    if (pp->status > MEXPLODE)
	    {
		make_crash("You crashed into a hill");
		broadcast("crashed into a hill");
	    }
	    else if (!on_hill)
	    {
		pp->status = MEXPLODE;	/* set to exploding	*/
#ifdef AUDIO
		play_samps(diesample, dielength);
#endif

	    }
	    on_hill = TRUE;
	}
}


/*
 *  update_missiles() updates the position and status of missiles.
 *  It also launches a SAM if appropriate.
 */
update_missiles()
{
    Plane pp = planes[0], ptemp;
    float temp;

    /*
     *  SAM threats
     */
    if (threat_mode &&
	(tick_counter & 1) &&
	(pp->mtype != TYPE_SAM || !pp->mstatus) &&
	pp->y > 200.0)
    {
	register float dx, dy, dz;
	int launch_sam;

	/*
	 *  test for proximity to SAM threats
	 */
	dy = pp->y * pp->y;
	dx = 3000 - pp->x;
	dz = 34000 - pp->z;
	if (dx*dx + dz*dz + dy < 2700.0*2700.0)
	{
	    pp->mx = 3000;
	    pp->mz = 34000;
	    launch_sam = TRUE;
	}
	else
	{
	    dx = 6000 - pp->x;
	    dz = 14000 - pp->z;
	    if (dx*dx + dz*dz + dy < 17000.0*17000.0)
	    {
		pp->mx = 6000;
		pp->mz = 14000;
		launch_sam = TRUE;
	    }
	    else
	    {
		dx = -20000 - pp->x;
		dz = 15000 - pp->z;
		if (dx*dx + dz*dz + dy < 10700.0*10700.0)
		{
		    pp->mx = -20000;
		    pp->mz = 15000;
		    launch_sam = TRUE;
		}
		else launch_sam = FALSE;
	    }
	}

	/*
	 *  if close enuf, take over a missile
	 */
	if (launch_sam)
	{
	    pp->my = 50;
	    pp->mkill = NULL_PLANE_ID;
	    pp->mtype = TYPE_SAM;
	    pp->mstatus = MSTART;

	    missile_target = PLANE_ID(pp);
	    missile_vx = 0;
	    missile_vy = 500.0/TPS;
	    missile_vz = 0;

	    sprintf(charbuf, "SAMissile->%s", pp->myname);
	    set_text_meter(0, charbuf, -1);

	    tick_counter = 2;
	    rebuild_status();
	}
    }

    /*
     *  update MISSILES
     */
    if (pp->mstatus)			/* if missile launched	*/
    {
	if (pp->mstatus > MEXPLODE)	/* if not exploding	*/
	{
	    pp->last_mx = pp->mx;		/* save last position	*/
	    pp->last_my = pp->my;
	    pp->last_mz = pp->mz;
	    pp->mx += missile_vx;		/* update position	*/
	    pp->my += missile_vy;
	    pp->mz += missile_vz;
	    if (pp->mtype == TYPE_CANNON)
	    {
		pp->last_mx = .2 * pp->last_mx + .8 * pp->mx;
		pp->last_my = .2 * pp->last_my + .8 * pp->my;
		pp->last_mz = .2 * pp->last_mz + .8 * pp->mz;
	    }
	    if (pp->my < 10.0)		/* if too low, explode	*/
	    {
		pp->my = 20.0;
		if (pp->mtype == TYPE_CANNON)
		    pp->mstatus = 1;	/* kill a cannon shot	*/
		else
		    pp->mstatus = MEXPLODE;
	    }
	    if (!in_cmode)
		if (collide_grid(pp->mx, pp->my - 10.0, pp->mz, hillsgrid))
		{
		    if (pp->mtype == TYPE_CANNON)
			pp->mstatus = 1;	/* kill a cannon shot	*/
		    else
			pp->mstatus = MEXPLODE;
		}
	    if (pp->mstatus == MFINISH)		/* coasting */
	    {
		missile_vx *= .995;		/* air resistance hack */
		missile_vy *= .9975;
		missile_vz *= .995;
		missile_vy -= GRAVITY;		/* gravity */
		missile_target = NULL_PLANE_ID;
		if (pp->mtype == TYPE_CANNON)
		    pp->mstatus = 1;		/* kill a cannon shot */
		else if (pp -> mtype == TYPE_SAM)
		    pp -> mstatus = MEXPLODE;   /* or a SAM */
		else
		    pp->mstatus++;		/* else continue to coast */
	    }
	    else	/* not finished - still has gas	*/
	    {
		float dx, dy, dz, acc, ticks, dvx, dvy, dvz;

		ticks = pp->mstatus - MFINISH;
		if (missile_target == NULL_PLANE_ID)
		    ptemp = NULL;
		else
		    ptemp = lookup_plane(missile_target);

		if (ptemp == NULL)
		{
		    dx = missile_vx;
		    dy = missile_vy;
		    dz = missile_vz;
		    acc = GRAVITY * .25 * ticks;
		}
		else	/* lock on the target	*/
		{
		    static float last_tpx, last_tpy, last_tpz;
		    int txi, tyi, tzi;	/* time to intercept	*/

		    if (pp->mstatus == MSTART)
		    {
			last_tpx = ptemp->x;
			last_tpy = ptemp->y;
			last_tpz = ptemp->z;
		    }
		    dx = ptemp->x - pp->mx;
		    dy = ptemp->y - pp->my;
		    dz = ptemp->z - pp->mz;
		    dvx = (ptemp->x - last_tpx) - missile_vx;
		    dvy = (ptemp->y - last_tpy) - missile_vy;
		    dvz = (ptemp->z - last_tpz) - missile_vz;
		    if (fabs(dvx) < .00001)
			txi = MLIFE;
		    else
		    {
			txi = dx/-dvx;
			if (txi < 0)
			    txi = -txi;
		    }
		    if (fabs(dvy) < .00001)
			tyi = MLIFE;
		    else
		    {
			tyi = dy/-dvy;
			if (tyi < 0)
			    tyi = -tyi;
		    }
		    if (fabs(dvz) < .00001)
			tzi = MLIFE;
		    else
		    {
			tzi = dz/-dvz;
			if (tzi < 0)
			    tzi = -tzi;
		    }
#ifdef DEBUG
if (debug & (1<<4))
{
    printf("Status:%3d  Time x,y,z: %3d %3d %3d", pp->mstatus, txi, tyi, tzi);
    printf("	Dist: %d", itemp = sqrt(dx*dx + dy*dy + dz*dz));
    if (itemp < 250)
	printf(" <== killed *****\n");
    else
	printf("\n");
}
#endif
		    /*
		     *  find maximum intercept time
		     */
		    if (tyi > txi)
			txi = tyi;
		    if (tzi > txi)
			txi = tzi;
		    if (txi > MLIFE)
			txi = MLIFE;

		    if (txi == 0)
			temp = 1.7/.2;
		    else
			temp = 1.7/txi;			/* cut it by 1.7 */
		    dx = temp * dx + dvx;		/* and aim for it */
		    dy = temp * dy + dvy;
		    dz = temp * dz + dvz;
		    if (pp->mtype == TYPE_SIDEWINDER)
			acc = 16.0 * GRAVITY;		/* with 16 G's  */
		    else
			acc = 20.0 * GRAVITY;		/* with 20 G's  */

		    /*
		     *  save target's last pos
		     */
		    last_tpx = ptemp->x;
		    last_tpy = ptemp->y;
		    last_tpz = ptemp->z;
		}
		if (pp->mtype != TYPE_CANNON)
		{
		    temp = acc / (fabs(dx) + fabs(dy) + fabs(dz));
		    missile_vx += dx * temp;
		    missile_vy += dy * temp;
		    missile_vz += dz * temp;
		}
	    }

	}	/* end of if (pp->mstatus > MEXPLODE)	*/
	else
	    missile_target = NULL_PLANE_ID;

#ifdef AUDIO
	if (pp->mstatus == MEXPLODE)
	    if (view_switch == PLANE_VIEW && missile_view)
		play_explosion(1.0);	/* use max volume -> small dist */
	    else
		play_explosion((pp->x - pp->mx)*(pp->x - pp->mx) +
			       (pp->y - pp->my)*(pp->y - pp->my) +
			       (pp->z - pp->mz)*(pp->z - pp->mz));
#endif

	pp->mstatus--;		/* decrement status	*/

	if (pp->mstatus == 0)
	    set_text_meter(0, "", -1);
    }
}


/*
 *  do_flight() is the actual flight equasion code
 */
do_flight()
{
    float temp;
    int itemp;
    short vz_positive;			/* true if vz >= 0 */
    Plane pp = planes[0];

    static float ax, ay, az;		/* plane acceleration		*/
    static float ydrag, zdrag;		/* drag force in y and z	*/
    static float ae;			/* angle of attack for wing	*/
    static float ro2, sos;		/* air density / 2.0, speed of sound */
    static float mcc, mratio;		/* mach crest critical #, mach/mcc */
    static float uCl, Cl, Cd, Cdc;	/* coefficients of lift and drag */
    static float kl, qs;		/* ground effect, ro/2*Vz*s	*/

    /* XXX
    if (pp->status > MEXPLODE)
    if (1)
    */
    if ((pp->status || !on_ground) && !on_hill)
    {
	/* ground effect factor	*/
	if ((pp->y - plane_height) > gefy)
	    kl = 1.0;
	else
	{
	    kl = (pp->y - plane_height) / b;
	    if (kl > .225)
		kl = .484 * kl + .661;
	    else
		kl = 2.533 * kl + .20;
	}

	/* compute new accelerations, lift: only if vz is negative	*/
	vz_positive = (vz >= 0.0);
	if (!vz_positive)
	{
	    ae = vy/vz + tilt_factor;
	    Cl = uCl = ae/(.17 + kl*ipi_AR);
	    if (Cl > max_cl)		/* check for positive stall	*/
	    {
		Cl = 3.0 * max_cl - 2.0 * Cl;
		wing_stall = 1;
		if (Cl < 0.0)
		{
		    wing_stall += 1 - (int)(Cl/max_cl);
		    Cl = 0.0;
		}
		if (uCl > 5.0)
		    uCl = 5.0;
	    }
	    else if (Cl < min_cl)	/* check for negative stall	*/
	    {
		Cl = 3.0 * min_cl - 2.0 * Cl;
		wing_stall = 1;
		if (Cl > 0.0)
		{
		    wing_stall += 1 - (int)(Cl/min_cl);
		    Cl = 0.0;
		}
		if (uCl < -5.0)
		    uCl = -5.0;
	    }
	    else
		wing_stall = FALSE;
	}
	else
	{
	    Cl = uCl = 0.0;
	    wing_stall = on_ground ? 0 : vz;
	    ae = 0;
	}
	if (wing_stall > 64)
	    wing_stall = 64;

	if ((tick_counter & 1) == 0)	/* only do on even ticks	*/
	{
	    if (pp->y <= 36000.0)	/* compute speed of sound	*/
		sos = -1116.0/TPS + (1116.0-968.0)/TPS/36000.0 * pp->y;
	    else
		sos = -968.0/TPS;
	    itemp = ((int)pp->y) >> 10;
	    if (itemp > 74)
		itemp = 74;
	    ro2 = .5 * ro[itemp];
	    if (Cl < .2)
		mcc = .7166666 + .1666667 * Cl;
	    else
		mcc = .7833333 - .1666667 * Cl;
	    mach = vz/sos;		/* and current mach number	*/
	    mratio = mach/mcc;
	    if (mratio < 1.034)
		Cdc = 0.0;
	    else
	    {
		Cdc = .082 * mratio - 0.084788;
		if (Cdc > .03)
		    Cdc = .03;
	    }
	    if (spoilers > 0)
		Cdc += Spdf;
	}

	qs = ro2 * vz * s;		/* assume V approx = vz	*/

	lift = Cl * qs;
	g_limit = FALSE;
	if (spoilers > 0)
	    lift *= Splf;
    relift:
	ay = vz * lift;
	az = -vy * lift;
	lift = ay * inverse_mass;	/* save for wing loading meter	*/
	if (lift > Lmax_g)
	{
	    lift = .99 * Lmax_g/inverse_mass/vz;
	    g_limit = TRUE;
	    goto relift;
	}
	else if (lift < Lmin_g)
	{
	    lift = .99 * Lmin_g/inverse_mass/vz;
	    g_limit = TRUE;
	    goto relift;
	}

	/* engine thrust		*/
	if (thrust < throttle)
	{
	    thrust += (50.0/tps);	/* 2 seconds to rev to full 100% */
	    if (thrust > throttle)
		thrust = throttle;
	}
	else if (thrust > throttle)
	{
	    thrust -= (50.0/tps);	/* 2 seconds to rev to full 100% */
	    if (thrust < throttle)
		thrust = throttle;
	}
	pp->thrust = thrust;
	az -= .01/TPS/TPS*thrust * Mthrust;

	/* drag - needs to be broken into y/z components		*/
	Cd = Cdp + kl*uCl*uCl*ie_pi_AR + Cdc;
	zdrag = Cd * qs;
	ydrag = vy * zdrag;
	zdrag = vz * zdrag;
	if (vz_positive)		/* if vz is positive	*/
	{
	    ay -= ydrag;
	    az -= zdrag;
	}
	else
	{
	    ay += ydrag;
	    az += zdrag;
	}

	/* now convert forces to accelerations (A=F/M)	*/
	ax = 0.0;
	ay *= inverse_mass;
	az *= inverse_mass;

	/* add in gravity which is an acceleration	*/
	ax -= ptw[0][1] * GRAVITY;
	ay -= ptw[1][1] * GRAVITY;
	az -= ptw[2][1] * GRAVITY;

	vx += ax;	vz += az;
	if (on_ground && pp->status > MEXPLODE)
	{
	    float cos;

	    vx = 0.0;
	    gl_sincos(elevation, &temp, &cos);
	    temp = vz * temp/cos;
	    if (vy+ay < temp)
		ay = temp - vy;
	}
	vy += ay;

	/*
	 *  use fuel
	 */
	if (tick_counter == 2 && fuel > 0)
	{
	    fuel -= (int)(_ABS(thrust) * fuel_rate);
	    inverse_mass = compute_mass();
	}
    }
    else /* plane has exploded */
    {
	wing_stall = FALSE;	/* so the bell will stop ringing */
    }


#ifdef DEBUG
if (debug & (1<<1))
{
    temp = inverse_mass * TPS *TPS;
    printf("----------------------%d----------------------\n", tick_counter);
    printf("Position (xyz): %12.2f%12.2f%12.2f    %s\n",
		pp->x, pp->y, pp->z, on_ground?"*** ON THE GROUND":"");
    printf("Elevation, azimuth, roll: %6d%6d%6d\n",
			elevation, azimuth, twist);
    printf("Elev, azim, roll speeds:  %6d%6d%6d\n",
			elevation_speed, azimuth_speed, roll_speed);
    printf("Rotated velocities per tick: %9.2f%9.2f%9.2f\n",
	incremental[3][0]*TPS, incremental[3][1]*TPS, incremental[3][2]*TPS);
    printf("Speed-of-sound:%8.1f  Mach:%5.2f  Mcc:%5.2f  Mach/Mcc:%5.2f\n",
		-sos*TPS, mach, mcc, mratio);
    printf("Cd:%8.4f=%7.4f +%7.4f +%7.4f  (p+i+c)\n",
		Cd, Cdp, kl*uCl*uCl*ie_pi_AR, Cdc);
    printf("Cl:%5.2f  kl:%5.2f  ro2:%7.4f  qs:%6.2f\n",
		Cl, kl, ro2, TPS*TPS*vz*qs);
    printf("Thrust:   %21.2f\n", -.01*thrust * Mthrust * inverse_mass);
    if (spoilers > 0)
	qs *= Splf;
    printf("Lift:     %14.2f%7.2f        angle:%6.2f\n",
		vz*Cl*qs*temp, -vy*Cl*qs*temp, 57.3 * (ae-tilt_factor));
    printf("Drag:     %14.2f%7.2f\n", ydrag*temp, zdrag*temp);
    printf("Gravity:  %7.2f%7.2f%7.2f\n",
		ptw[0][1]*-G_ACC, ptw[1][1]*-G_ACC, ptw[2][1]*-G_ACC);
    printf("-------------------------------   Mass: %g\n", G_ACC/inverse_mass);
    printf("Totals:   %7.2f%7.2f%7.2f\n", ax*TPS*TPS, ay*TPS*TPS, az*TPS*TPS);
    printf("New velocities per tick: %9.2f%9.2f%9.2f\n",
			    vx*TPS, vy*TPS, vz*TPS);
}
if (debug & (1<<5)) printf("Wing_stall = %d\n", wing_stall);
if (debug & (1<<3))
{
    if (pp->mstatus)
    {
	printf("----------------------------------------\n");
	printf("Missile status: %d\n", pp->mstatus);
	printf("Missile velocities (xyz): %12.2f%12.2f%12.2f\n",
			missile_vx*TPS, missile_vy*TPS, missile_vz*TPS);
	printf("Missile position (xyz):   %12.2f%12.2f%12.2f\n",
			pp->mx, pp->my, pp->mz);
    }
}
#endif
}


draw_scene()
{
    float fcp;		/* front clipping plane */
    Plane pp = planes[0];
    float mk_x,mk_y,mk_z,mk_len;  /* mk = missile kludge */
    Matrix tmpmat;

    /*
     *  set up windshield, and load perspective
     */
    if (shadow)
    {
	azimuth = pp->azimuth;
	elevation = pp->elevation;
	twist = pp->twist;
    }
    else
    {
	pp->azimuth = azimuth;
	pp->elevation = elevation;
	pp->twist = twist;
    }

    if (hud || shadow)
	viewport(0, xmaxwindow, 0, ymaxwindow);
    else
	viewport(1, xmaxwindow-1, ymiddle, ymaxwindow-1);

    if (view_switch == TOWER_VIEW)
    {
	if ((fcp = range(eye_x, eye_y, eye_z,
			 pp->x, pp->y, pp->z) / 2.0) > 200.0)
	    fcp = 200.0;
	else
	    fcp = (fcp > 4.0)? fcp : 4.0;
	perspective(fov, ar, fcp, 1.0e6);
    }
    else
    {
	fcp = (pp->y < 20.0 || (wingman_view && wmfollow <= 1))? 4.0 : 10.0;
	perspective(fov, ar, fcp, 1.0e6);
    }

    loadmatrix(identmat);
    pushmatrix();

    if (fogit)
	fog(TRUE);

    if (view_switch == TOWER_VIEW)
    {
	identify_matrix(tmpmat);
	if (missile_view && pp->mstatus)
	    my_lookat(eye_x, eye_y, eye_z, pp->mx, pp->my, pp->mz, tmpmat);
	else
	    my_lookat(eye_x, eye_y, eye_z, pp->x, pp->y, pp->z, tmpmat);
	if (!in_cmode)
	    lmbind(LIGHT0, SUN);
	draw_infinite_world();

	current_eye[X] = eye_x;
	current_eye[Y] = eye_y;
	current_eye[Z] = eye_z;
	calc_clip_planes(tmpmat, current_eye);
    }
    else if (view_switch == PLANE_VIEW)
    {
	if (missile_view && pp->mstatus)
	{
	    Plane_hist ph = plane_hists[0];

	    identify_matrix(tmpmat);
	    translate(0.0, -missile_eye[Y], 0.0);

	    vec_len(&pp->mx, &pp->last_mx, 30.0, current_eye);

	    my_lookat(current_eye[X], current_eye[Y], current_eye[Z],
		      pp->mx, pp->my, pp->mz, tmpmat);

	    if (!in_cmode)
		lmbind(LIGHT0, SUN);
	    draw_infinite_world();

	    current_eye[Y] += missile_eye[Y];
	    calc_clip_planes(tmpmat, current_eye);
	}
	else if (wingman_view)
	{
	    if (view_angle != 0)
		rotate(view_angle, 'y');

	    /* pilot's eye position */
	    translate(0.0, -pilot_eye[Y], -pilot_eye[Z]);

	    rotate(-wm_twist[wmpos], 'z');
	    rotate(-wm_elevation[wmpos], 'x');
	    rotate(-wm_azimuth[wmpos], 'y');
	    if (!in_cmode)
		lmbind(LIGHT0, SUN);
	    translate(0.0, -wm_y[wmpos], 0.0);
	    draw_infinite_world();
	    translate(-wm_x[wmpos], 0.0, -wm_z[wmpos]);

	    identify_matrix(tmpmat);
	    matrix_rotate(tmpmat, wm_azimuth[wmpos], 'y');
	    matrix_rotate(tmpmat, wm_elevation[wmpos], 'x');
	    matrix_rotate(tmpmat, wm_twist[wmpos], 'z');
	    mult_vec(tmpmat, pilot_eye, current_eye);
	    if (view_angle != 0)
		matrix_rotate(tmpmat, -view_angle, 'y');
	    current_eye[X] += wm_x[wmpos];
	    current_eye[Y] += wm_y[wmpos];
	    current_eye[Z] += wm_z[wmpos];
	    calc_clip_planes(tmpmat, current_eye);
	}
	else	/* just draw the view from the plane */
	{
	    if (view_angle != 0)
		rotate(view_angle, 'y');

	    /* pilot's eye position */
	    translate(0.0, -pilot_eye[Y], -pilot_eye[Z]);

	    rotate(-twist, 'z');
	    rotate(-elevation, 'x');
	    rotate(-azimuth, 'y');
	    if (!in_cmode)
		lmbind(LIGHT0, SUN);
	    translate(0.0, -pp->y, 0.0);
	    draw_infinite_world();
	    translate(-pp->x, 0.0, -pp->z);

	    identify_matrix(tmpmat);
	    matrix_rotate(tmpmat, azimuth, 'y');
	    matrix_rotate(tmpmat, elevation, 'x');
	    matrix_rotate(tmpmat, twist, 'z');
	    mult_vec(tmpmat, pilot_eye, current_eye);
	    if (view_angle != 0)
		matrix_rotate(tmpmat, -view_angle, 'y');
	    current_eye[X] += pp->x;
	    current_eye[Y] += pp->y;
	    current_eye[Z] += pp->z;
	    calc_clip_planes(tmpmat, current_eye);
	}
    }

    if (in_cmode)
	draw_world_ci();
    else
	draw_world();

    popmatrix();	/* Back to identity */

    if (hud)
    {
	ortho2(-0.5, xmaxwindow+0.5, -0.5, ymaxwindow+0.5);
	cmov2s(50, ymaxwindow-20);	/* position character origin    */
    }
    else if (shadow)
    {
	ortho2(-200.0,200.0,-200.0,200.0);
	draw_cross_hairs();
	cmov2s(-195,192);		/* position character origin    */
    }
    else
    {
	ortho2(-200.0,200.0,-100.0,100.0);
	draw_cross_hairs();
	cmov2s(-195,92);		/* position character origin    */
    }

    if (view_switch == PLANE_VIEW)
    {
	COLOR(C_ORANGE);
	if (view_angle == 0)
	{
	    charstr("Front view");
	    if (!hud)
	    {
		setlinestyle(1);
		rects(-40, -40, 40, 40);
		setlinestyle(0);
	    }
	}
	else if (view_angle == -900) charstr("Left view");
	else if (view_angle == 900) charstr("Right view");
	else if (view_angle == 1800) charstr("Back view");
	else
	{
	    sprintf(charbuf, "%d degree view", view_angle / 10);
	    charstr(charbuf);
	}
	if (shadow)
	{
	    charstr(" of ");
	    charstr(pp->myname);
	}
    }

    if (show_help)
	if (shadow)
	    overlay_shadow_help();
	else
	    overlay_help();
}


draw_world()
{
    Plane pp = planes[0];

    /*
     *  draw local objects
     */
    lighting(TRUE);
    zbuffer(TRUE);
    drawobj(mtnsobj, 0x1);
    zbuffer(FALSE);
    draw_grid();
    drawobj(runwayobj, 0x1);
    lighting(FALSE);
    if (lightson)
	drawobj(lightsobj, 0x1);
    draw_vasi(pp);			/* show VASI lights	*/

    zbuffer(TRUE);

    if (threat_mode)
	draw_threats();

    lighting(TRUE);

    if (texit)
	texturing(TRUE);
    drawobj(hillsobj, 0x1);
    if (texit)
	texturing(FALSE);

    if (view_switch == TOWER_VIEW)
    {
	draw_buildings(eye_x, eye_y, eye_z);
	draw_planes(eye_x, eye_y, eye_z, 0, number_planes);
    }
    else if (missile_view && pp->mstatus)
    {
	draw_buildings(pp->last_mx, pp->last_my, pp->last_mz);
	draw_planes(pp->last_mx, pp->last_my, pp->last_mz, 0, number_planes);
    }
    else if (wingman_view)
    {
	draw_buildings(wm_x[wmpos], wm_y[wmpos], wm_z[wmpos]);
	draw_planes(wm_x[wmpos], wm_y[wmpos], wm_z[wmpos], 0, number_planes);
    }
    else
    {
	draw_buildings(pp->x, pp->y, pp->z);
	draw_planes(pp->x, pp->y, pp->z, 1, number_planes);
    }

    draw_missiles();

    lighting(FALSE);

    zbuffer(FALSE);

    if (fogit)
	    fog(FALSE);
}


draw_world_ci()
{
    Plane pp = planes[0];

    /*
     *  draw local objects
     */
    drawobj(mtnsobj, 0x1);

    draw_grid();

    drawobj(runwayobj, 0x1);

    if (lightson)
	drawobj(lightsobj, 0x1);

    draw_vasi(pp);			/* show VASI lights	*/


    if (view_switch == TOWER_VIEW)
    {
	draw_everything(eye_x, eye_y, eye_z, number_planes, 1);
    }
    else if (missile_view && pp->mstatus)
    {
	draw_everything(pp->last_mx, pp->last_my, pp->last_mz,
			number_planes, 1);
    }
    else if (wingman_view)
    {
	draw_everything(wm_x[wmpos], wm_y[wmpos], wm_z[wmpos],
			number_planes, 1);
    }
    else
    {
	draw_everything(pp->x, pp->y, pp->z, number_planes, 0);
    }
}


/*
 *  clean up and exit routine for flight
 */
end_of_program()
{
#ifdef AUDIO
    close_audio();
#endif
    ExitComm();
    greset();
    COLOR(C_BLACK);
    clear();
    restore_map();
    drawmode(over_drawmode);
    color(0);
    clear();
    if (bits_under)
    {
	drawmode(UNDERDRAW);
	color(0);
	clear();
    }
    exit(0);
}


draw_meters()
{
    if (hud)
	draw_hud(planes[0], tick_counter, vx, vy, vz, climbspeed, mach,
		 lift/GRAVITY, wheels, flaps, spoilers, autopilot_on,
		 fuel >> 7, thrust, throttle);
    else if (new_inst)
	update_instruments(0);
    else
	old_meters();
}


/*
 *  select a plane and set it's design parameters
 */
select_plane()
{
    Plane pp = planes[0];

    pp->type = -1;

    while (pp->type == -1)
	switch (pick_plane())
	{
	    case 1:
		plane_type = C150_NAME;
		pp->type = C150;
		s = 157.0;
		W = 1000.0;
		fuel_weight = 400.0;
		set_fuelgauge(400.0, 100.0, 10, 100);
		Mthrust = 300.0;
		b = 28.0;
		ef = .80;
		Lmax = 5.0;	Lmin = -3.0;
		Fmax = 20;	Smax = 0;
		set_flapspoiler(20, 20, 4, 0, 0, 0);
		MAX_RK = 0;	MAX_SW = 0;
		MIN_LIFT_SPEED = 70;
		ELEVF = 75.0;
		ROLLF = 130.0;
		landing_gear_stuck = 1;	/* stuck down	*/
		pilot_eye[Y] = 5.0;
		pilot_eye[Z] = 0.0;
		plane_height = 1.5;
#ifdef AUDIO
		thrust_type(0);
#endif
		break;
	    case 2:
		plane_type = B747_NAME;
		pp->type = B747;
		s = 5500.0;		/* wing area in sq. feet	*/
		W = 500000.0;		/* weight of plane in lbs.	*/
		fuel_weight = 100000.0;
		set_fuelgauge(100000.0, 10000.0, 2, 10000);
		Mthrust = 200000.0;	/* maximum thrust		*/
		b = 220.0;		/* wing span in feet		*/
		ef = .83;		/* efficiency factor		*/
		Lmax = 4.0;		/* maximum lift before wing breaks */
		Lmin = -2.0;		/* minimum lift before wing breaks */
		Fmax = 50;		/* maximum flap deflection	*/
		Smax = 80;		/* maximum spoiler deflection	*/
		set_flapspoiler(50, 50, 10, 80, 80, 8);
		MAX_RK = 0;
		MAX_SW = 0;
		MIN_LIFT_SPEED = 200;
		ELEVF = 25.0;		/* elevator rate in degrees/sec	*/
		ROLLF = 50.0;		/* roll rate (both at 300 mph)	*/
		pilot_eye[Y] = 30.0;
		pilot_eye[Z] = -92.0;
		plane_height = 0.0;
#ifdef AUDIO
		thrust_type(0);
#endif
		break;
	    case 3:
		plane_type = F15_NAME;
		pp->type = F15;
		s = 608.0;
		W = 28000.0;
		fuel_weight = 14000.0;
		set_fuelgauge(14000.0, 2000.0, 5, 1000);
		Mthrust = 46000.0;
		b = 43.0;
		ef = .87;
		Lmax = 8.0;	Lmin = -5.0;
		Fmax = 30;	Smax = 60;
		set_flapspoiler(30, 30, 6, 60, 60, 6);
		MAX_RK = 4;	MAX_SW = 4;
		swpos[3][X] =   9.0; swpos[3][Y] =  0.0; swpos[3][Z] = 3.0;
		swpos[2][X] =  -9.0; swpos[2][Y] =  0.0; swpos[2][Z] = 3.0;
		swpos[1][X] =   9.0; swpos[1][Y] =  0.0; swpos[1][Z] = 3.0;
		swpos[0][X] =  -9.0; swpos[0][Y] =  0.0; swpos[0][Z] = 3.0;
		rkpos[3][X] =  -2.0; rkpos[3][Y] = -1.0; rkpos[3][Z] = 3.0;
		rkpos[2][X] =   2.0; rkpos[2][Y] = -1.0; rkpos[2][Z] = 3.0;
		rkpos[1][X] =  -2.0; rkpos[1][Y] = -1.0; rkpos[1][Z] = 3.0;
		rkpos[0][X] =   2.0; rkpos[0][Y] = -1.0; rkpos[0][Z] = 3.0;
		MIN_LIFT_SPEED = 100;
		ELEVF = 32.0;
		ROLLF = 140.0;
		pilot_eye[Y] = 4.8;
		pilot_eye[Z] = -26.0;
		plane_height = 4.89;
		/*
		pilot_eye[Y] = 10.0;
		pilot_eye[Z] = -25.0;
		plane_height = 4.0;
		*/
#ifdef AUDIO
		thrust_type(1);
#endif
		break;
	    case 4:
		plane_type = F16_NAME;
		pp->type = F16;
		s = 390.0;
		W = 18000.0;
		fuel_weight = 8000.0;
		set_fuelgauge(8000.0, 1000.0, 5, 1000);
		Mthrust = 23000.0;
		b = 32.0;
		ef = .93;
		Lmax = 10.0; Lmin = -7.0;
		Fmax = 40;	Smax = 40;
		set_flapspoiler(40, 40, 4, 40, 40, 4);
		MAX_RK = 2;	MAX_SW = 2;
		swpos[1][X] =  14.8; swpos[1][Y] = -2.0; swpos[1][Z] = 4.6334;
		swpos[0][X] = -14.8; swpos[0][Y] = -2.0; swpos[0][Z] = 4.6334;
		rkpos[1][X] =  -6.0; rkpos[1][Y] = -2.0; rkpos[1][Z] = 4.6334;
		rkpos[0][X] =   6.0; rkpos[0][Y] = -2.0; rkpos[0][Z] = 4.6334;
		MIN_LIFT_SPEED = 120;
		ELEVF = 34.0;
		ROLLF = 180.0;
		pilot_eye[Y] = 3.5;
		pilot_eye[Z] = -13.0;
		plane_height = 4.0;
#ifdef AUDIO
		thrust_type(1);
#endif
		break;
	    case 5:
		plane_type = F18_NAME;
		pp->type = F18;
		s = 510.0;
		W = 24000.0;
		fuel_weight = 12000.0;
		set_fuelgauge(12000.0, 2000.0, 5, 1000);
		Mthrust = 32000.0;
		b = 38.0;
		ef = .90;
		Lmax = 9.0;	Lmin = -6.0;
		Fmax = 50;	Smax = 60;
		set_flapspoiler(50, 50, 5, 60, 60, 6);
		MAX_RK = 3;	MAX_SW = 3;
		swpos[2][X] = -18.2; swpos[2][Y] =  0.0; swpos[2][Z] = 7.2;
		swpos[1][X] =  18.2; swpos[1][Y] =  0.0; swpos[1][Z] = 7.2;
		swpos[0][X] =   0.0; swpos[0][Y] = -2.0; swpos[0][Z] = 7.2;
		rkpos[2][X] =   8.2; rkpos[2][Y] =  0.0; rkpos[2][Z] = 7.2;
		rkpos[1][X] =  -8.2; rkpos[1][Y] =  0.0; rkpos[1][Z] = 7.2;
		rkpos[0][X] =   0.0; rkpos[0][Y] = -2.0; rkpos[0][Z] = 7.2;
		MIN_LIFT_SPEED = 110;
		ELEVF = 30.0;
		ROLLF = 170.0;
		pilot_eye[Y] = 4.3;
		pilot_eye[Z] = -13.5;
		plane_height = 4.565;
#ifdef AUDIO
		thrust_type(1);
#endif
		break;
	    case 6:
		plane_type = P38_NAME;
		pp->type = P38;
		s = 327.5;
		W = 13500.0;
		fuel_weight = 1600.0;
		set_fuelgauge(1600.0, 200.0, 5, 100);
		Mthrust = 4000.0;
		b = 52.0;
		ef = .90;
		Lmax = 6.0;	Lmin = -3.5;
		Fmax = 50;	Smax = 60;
		set_flapspoiler(50, 50, 5, 60, 60, 6);
		MAX_RK = 2;	MAX_SW = 0;
		rkpos[1][X] = -16.0; rkpos[1][Y] =  0.0; rkpos[1][Z] = 0.0;
		rkpos[0][X] =  16.0; rkpos[0][Y] =  0.0; rkpos[0][Z] = 0.0;
		MIN_LIFT_SPEED = 75;
		ELEVF = 30.0;
		ROLLF = 100.0;
		pilot_eye[Y] = 2.3;
		pilot_eye[Z] = -3.0;
		plane_height = 6.0;
#ifdef AUDIO
		thrust_type(0);
#endif
		break;
	    case 7:
		plane_type = F14_NAME;
		pp->type = F14;
		s = 565.0;
		W = 42000.0;
		fuel_weight = 16200.0;
		set_fuelgauge(16000.0, 2000.0, 5, 1000);
		Mthrust = 55000.0;
		b = 64.0;
		ef = .87;
		Lmax = 8.0;	Lmin = -4.0;
		Fmax = 40;	Smax = 60;
		set_flapspoiler(40, 40, 4, 60, 60, 6);
		MAX_RK = 4;	MAX_SW = 4;
		swpos[3][X] =   9.0; swpos[3][Y] =  0.0; swpos[3][Z] = 3.0;
		swpos[2][X] =  -9.0; swpos[2][Y] =  0.0; swpos[2][Z] = 3.0;
		swpos[1][X] =   9.0; swpos[1][Y] =  0.0; swpos[1][Z] = 3.0;
		swpos[0][X] =  -9.0; swpos[0][Y] =  0.0; swpos[0][Z] = 3.0;
		rkpos[3][X] =  -2.0; rkpos[3][Y] = -1.0; rkpos[3][Z] = 3.0;
		rkpos[2][X] =   2.0; rkpos[2][Y] = -1.0; rkpos[2][Z] = 3.0;
		rkpos[1][X] =  -2.0; rkpos[1][Y] = -1.0; rkpos[1][Z] = 3.0;
		rkpos[0][X] =   2.0; rkpos[0][Y] = -1.0; rkpos[0][Z] = 3.0;
		MIN_LIFT_SPEED = 90;
		ELEVF = 32.0;
		ROLLF = 130.0;
		pilot_eye[Y] = 4.8;
		pilot_eye[Z] = -26.0;
		plane_height = 4.89;
#ifdef AUDIO
		thrust_type(1);
#endif
		break;
	    case 8:
		plane_type = B727_NAME;
		pp->type = B727;
		s = 1700.0;		/* wing area in sq. feet	*/
		W = 101773.0;		/* weight of plane in lbs.	*/
		fuel_weight = 59750.0;
		Mthrust = 48000.0;	/* maximum thrust		*/
		set_fuelgauge(48000.0, 8000.0, 5, 1000);
		b = 108.0;		/* wing span in feet		*/
		ef = .83;		/* efficiency factor		*/
		Lmax = 4.0;		/* maximum lift before wing breaks */
		Lmin = -2.0;		/* minimum lift before wing breaks */
		Fmax = 50;		/* maximum flap deflection	*/
		Smax = 80;		/* maximum spoiler deflection	*/
		set_flapspoiler(50, 50, 5, 80, 80, 8);
		MAX_RK = 0;	MAX_SW = 0;
		MIN_LIFT_SPEED = 180;
		ELEVF = 25.0;		/* elevator rate in degrees/sec	*/
		ROLLF = 50.0;		/* roll rate (both at 300 mph)	*/
		pilot_eye[Y] = 2.0;
		pilot_eye[Z] = -66.0;
		plane_height = 10.0;
#ifdef AUDIO
		thrust_type(1);
#endif
		break;
#if 0
	    case 9:
		plane_type = STEALTH_NAME;
		pp->type = STEALTH;
		s = 1000.0;		/* wing area in sq. feet	*/
		W = 30000.0;		/* weight of plane in lbs.	*/
		fuel_weight = 14000.0;
		Mthrust = 25000.0;	/* maximum thrust		*/
		set_fuelgauge(10000.0, 120.0, 5, 1000);
		b = 38.0;		/* wing span in feet		*/
		ef = .85;		/* efficiency factor		*/
		Lmax = 4.0;		/* maximum lift before wing breaks */
		Lmin = -2.0;		/* minimum lift before wing breaks */
		Fmax = 30;		/* maximum flap deflection	*/
		Smax = 60;		/* maximum spoiler deflection	*/
		set_flapspoiler(50, 50, 5, 80, 80, 8);
		MAX_RK = 0;
		MAX_SW = 4;
		swpos[3][X] =  14.8; swpos[3][Y] = -2.0; swpos[3][Z] = 4.6334;
		swpos[2][X] = -14.8; swpos[2][Y] = -2.0; swpos[2][Z] = 4.6334;
		swpos[1][X] =  12.8; swpos[1][Y] = -2.0; swpos[1][Z] = 4.6334;
		swpos[0][X] = -12.8; swpos[0][Y] = -2.0; swpos[0][Z] = 4.6334;
		MIN_LIFT_SPEED = 120;
		ELEVF = 35.0;		/* elevator rate in degrees/sec	*/
		ROLLF = 170.0;		/* roll rate (both at 300 mph)	*/
		pilot_eye[Y] = 0.0;
		pilot_eye[Z] = 0.0;
		plane_height = 10.0;
#ifdef AUDIO
		thrust_type(1);
#endif
		break;
#endif
	    case 27-'0':
		end_of_program();
	}

    if (!hud && new_inst)
	draw_instruments();
}


/*
 *  trash_plane() is called when a plane is blowb up to screw up it's dynamics.
 */
trash_plane()
{
    s /= 3.0;		/* lower wing area */
    b /= 2.0;		/* shorten wings */
    ef = 1.0;		/* lower efficiency factor */
    Lmax = 1.0;		/* poor maximum lift before wing breaks */
    Lmin = -1.0;	/* poor minimum lift before wing breaks */
    max_throttle = 0;
    throttle = 0;

    Cdp = .015;				/* coefficient of parasitic drag*/
    ipi_AR = 1.0/(3.1415927 * b*b/s);	/* 1.0 / pi * wing Aspect Ratio	*/
    ie_pi_AR = ipi_AR/ef;		/* 1.0 / pi * AR * efficiency	*/
    gefy = .7 * b;

    stick_xadd = flight_random(30);
    stick_yadd = flight_random(30);
    sb_xadd = stick_xadd * 10;
    sb_yadd = stick_yadd * 10;
}


launch_missile(mtype)
    int mtype;
{
    float temp;
    Plane pp = planes[0], ptemp;
    float *mpos;

    /*
     *  if I'm alive and no weapon already fired
     *  and I am not on the ground
     */
    if (pp->status > MEXPLODE && !pp->mstatus && !on_ground)
    {
	if (mtype == TYPE_SIDEWINDER && sidewinders > 0)
	{
	    sidewinders--;
	    pp->mtype = TYPE_SIDEWINDER;
	    pp->mstatus = MSTART;
#ifdef AUDIO
	    play_samps(misslesample, misslelength);
#endif
	    if (missile_target == NULL_PLANE_ID)
	    {
		if (ptemp = find_closest_plane(pp))
		{
		    missile_target = PLANE_ID(ptemp);
		    sprintf(charbuf, "Sidewinder->%s", ptemp->myname);
		    set_text_meter(0, charbuf, -1);
		}
		else
		    set_text_meter(0, "Sidewinder Launched", -1);
	    }
	    else if (ptemp = lookup_plane(missile_target))
	    {
		sprintf(charbuf, "Sidewinder->%s", ptemp->myname);
		set_text_meter(0, charbuf, -1);
	    }
	    else
		set_text_meter(0, "Sidewinder Launched", -1);
	    mpos = swpos[sidewinders];
	    pp->weapon_state &= ~((PS_SW1 >> PS_W_SHIFT) << sidewinders);
	}
	else if (mtype == TYPE_ROCKET && rockets > 0)
	{
	    rockets--;
	    pp->mtype = TYPE_ROCKET;
	    pp->mstatus = MSTART;
#ifdef AUDIO
	    play_samps(misslesample, misslelength);
#endif
	    missile_target = NULL_PLANE_ID;
	    set_text_meter(0, "Rocket Launched", -1);
	    mpos = rkpos[rockets];
	    pp->weapon_state &= ~((PS_RK1 >> PS_W_SHIFT) << rockets);
	}
	temp = fabs(vy) + fabs(vz);
	if (mtype == TYPE_CANNON)
	{
	    pp->mtype = TYPE_CANNON;
	    pp->mstatus = MFINISH + int_tps;
#ifdef AUDIO
	    play_samps(cannonsample, cannonlength);
#endif
	    temp = -2000.0/TPS - temp;
	    missile_target = NULL_PLANE_ID;
	    set_text_meter(0, "20mm Cannon Fired", -1);
	}
	else
	    temp = -500.0/TPS - temp;

	if (pp->mstatus)
	{
	    missile_vx = ptw[2][0] * temp;
	    missile_vy = ptw[2][1] * temp;
	    missile_vz = ptw[2][2] * temp;
	    if (mtype == TYPE_CANNON)
	    {
		pp->mx = pp->x + missile_vx;
		pp->my = pp->y + missile_vy;
		pp->mz = pp->z + missile_vz;
	    }
	    else
	    {
		mult_vec(ptw, mpos, &pp->mx);
	    }
	    pp->mkill = NULL_PLANE_ID;
	    rebuild_status();
	}
    }
}


void calc_clip_planes(Matrix mat, float *eye_point)
{
    int i;

    for (i=0; i < 4; i++)
    {
	mult_vec(mat, frustum[i], clip_planes[i]);
	clip_planes[i][3] = -DOT(clip_planes[i], eye_point);
    }
}


