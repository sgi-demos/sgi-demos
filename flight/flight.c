/*
 *									  *
 *  Copyright (C)  1988 Silicon Graphics, Inc.	  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#define LK_DISABLE 0
#define LK_HACK 1
#define LK_DISABLE_SWAMPS 1
#define LK_PICK_PLANE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"
// #include "iconize.h" 	/* flipiconic() */
#include <sys/types.h>
#include <sys/times.h>
#include <sys/param.h>
#include <signal.h>
// #include <psio.h>

#ifdef _4D
int int_tps = 20;
float tps = 20.0;
#else
int tps = 20;
#endif

int errno;

static short tilt_left = -200;
static short tilt_right = 200;
static short tilt_forward = 650;
static short tilt_back = 150;

static char *plane_type;		/* plane type ("F-15")		*/
static char charbuf[80], status_text[60];	/* char buffers		*/
static struct tms tms_start_buf, tms_end_buf;	/* timer buffer		*/
static int time_start, time_end;		/* start/end times	*/

char *WEAPON_NAME[] = {"rocket","sidewinder","20mm cannon"};
short debug,				/* TRUE if in debug mode	*/
	dogfight,			/* TRUE if dogfight		*/
	hud,				/* TRUE if hud, else meters	*/
	threat_mode,			/* TRUE if threats envelopes	*/
	test_mode;			/* test mode uses no fuel	*/
int dist_for_lines;			/* distance to draw building lines */
int sidewinders, rockets;		/* number of armaments		*/
int number_planes;			/* number of planes in game	*/
float eye_x, eye_y, eye_z;		/* eye position		*/
float (*my_ptw)[4];			/* pointer to my matrix	*/
extern float ro[], fuel_consump ();	/* air density table	*/


int timeit;		/* TRUE if displaying timing info */
float vx,vy,vz;		/* plane velocity */
float missile_vx,	/* missile velocity */
      missile_vy,
      missile_vz;
float fps_knots;	/* fps to knots conversion factor */
float gravity;		/* the effect of gravity realtive to tps */

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

short dials = FALSE,		/* TRUE if using dials		*/
	daytime;		/* TRUE if daytime colormap	*/

#define MINTPS 12	/* See calculate_time().  Olson */

void calculate_time(char *name);

flight (argc,argv)
    int argc;
    char *argv[];
{
    short type,val,		/* queue reading variables	*/
	view_switch,		/* <0 (none), 1 (plane), 2 (tower) */
	tick_counter,		/* counts the loop ticks	*/
	on_ground,		/* TRUE if plane is on ground	*/
	wheels,			/* TRUE if the wheels are down	*/
	wheels_retracting,	/* used only by F16W		*/
	landing_gear_stuck,	/* >= 0 if the gear is stuck	*/
	autopilot, 		/* TRUE in autopilot mode	*/
	g_limit,		/* TRUE if wing g-limit is hit	*/
	wing_stall;		/* TRUE if wing is stalling	*/

    int flaps, spoilers,	/* flap and spoiler settings	*/
	roll_speed,		/* roll, elevation, azimuth speeds	*/
	elevation_speed,	/* in 10'ths degrees per tick	*/
	azimuth_speed, 
	plane_fov, tower_fov,	/* plane, tower field of view	*/
	fuel,			/* fuel (0 - 12800)		*/
	thrust,			/* thrust (0 - 100)		*/
	max_throttle,		/* upper limit on engines	*/
	min_throttle,		/* lower limit on engines	*/
	MAX_RK, MAX_SW,		/* max rockets and sidewinders	*/
	MIN_LIFT_SPEED,		/* minimum lift-up speed fps	*/
	airspeed, last_airspeed, target_speed,
	climbspeed, last_climbspeed, target_climb,
	target_twist,
#ifdef WINGMAN
	wm_twist[6],
	wm_elevation[6],
	wm_azimuth[6],
	wmpos = 0,
#endif
	view_angle;		/* rotation of pilot's head	*/
    int itemp,		/* temp integer variable	*/
	twist, elevation, azimuth;	/* plane orientation	*/

    float temp,				/* temp float variable	*/
	rudder, elevator, rollers,	/* control settings	*/
	last_px, last_py, last_pz,	/* last plane position	*/
	ax,ay,az,			/* plane acceleration	*/
	ydrag, zdrag, 		/* drag force in y and z	*/
	fuel_rate,		/* fuel consumption rate	*/
	lift,			/* lift acceleration		*/
	gefy,			/* maximum height for ground effect	*/
	ae,			/* angle of attack for wing		*/
	max_cl,min_cl,		/* max and min coefficient of lift	*/
	tilt_factor,		/* wing angle tilt due to flaps		*/
	Splf,Spdf,		/* spoiler factors on lift and drag	*/
	ro2, sos,		/* air density / 2.0, speed of sound	*/
	mach, mcc, mratio,	/* mach #, crest critical #, ratio	*/
	uCl, Cl, Cd, Cdc,	/* coefficients of lift and drag	*/
	kl, qs,			/* ground effect, ro/2*Vz*s		*/
	fuel_weight,		/* weight of fuel			*/
	inverse_mass;		/* 1.0 / mass of plane			*/
#ifdef WINGMAN
    float wm_x[6], wm_y[6], wm_z[6];
    int wingmanview = FALSE;
#endif
    float s,W,Mthrust,b,Cdp;		/* plane design parameters	*/
    float ipi_AR,ie_pi_AR,Lmax,Lmin,Fmax,Smax,ELEVF,ROLLF,pilot_y,pilot_z;

    long missile_target;		/* plane my missile is after	*/
    Matrix ptw, incremental;	/* my ptw matrix, temp matrix	*/
    Plane ptemp,pp;		/* my plane data structure	*/
	int moreplanes;

#ifdef DOGFIGHT
static char usage[] = "Usage: dog  [-dh] [-i filename] [-o filename]\n";
#else
static char usage[] = "Usage: flight [-dhz]\n";
#endif
    test_mode = FALSE;			/* swapinterval governor	*/
    while (--argc > 0 && **++argv == '-') {
	char *token;

	for (token = argv[0] + 1; *token; token++) 
	switch (*token) {
#ifdef DOGFIGHT
	    extern char *infile,*outfile;
	    case 'i':
		if (--argc > 0) infile = *++argv;
		break;
	    case 'o':
		if (--argc > 0) outfile = *++argv;
		break;
#else
	    case 'z':			/* only available in flight	*/
		test_mode = TRUE;
		break;
#endif
	    case 'd':
		dials = TRUE;
		break;
	    case 'h':
		hud = TRUE;
		break;
	    default:
		fprintf (stderr,"illegal option %c\n", *token);
		break;
	}
    }
    if (argc > 0) {
	fprintf (stderr,"%s", usage);
	exit (0);
    }
    eye_x = -1950.0;
    eye_y = 400.0;
    eye_z = -3150.0;

    fps_knots = tps * (3600.0/6082.0);
    gravity = G_ACC / tps / tps;

    prefposition (0,XMAXSCREEN,0,YMAXSCREEN);
#ifdef DOGFIGHT
    init_graphics ("dog");
    dogfight = TRUE;
    InitComm ("plane");
    pp = planes[0];
#else
    init_graphics ("flight");
    dogfight = FALSE;
    for (itemp=0; itemp < 2; itemp++) {
	pp = (Plane) malloc (sizeof (struct plane));
	pp -> alive = -1;
	pp -> won = 0;
	pp -> lost = 0;
	PLANE_ID(pp) = 23;
	pp -> myname[0] = '\0';
	planes [itemp] = pp;
    }
    pp = planes[0];
#endif

    number_planes = 2;
    my_ptw = ptw;

    if (dials) init_dials(); 

    make_meters ();
    redraw_screen ();
    reset_meters ();
    display_help ();			/* I do a swapbuffers		*/


    argc = 0;

	if((moreplanes = make_planes(1)) == 0)
		wait_for_input();	/* made all planes with no input yet */

    gl_IdentifyMatrix (ptw);		/* load and push an identity	*/
    loadmatrix (ptw);
    pushmatrix ();

    time_start = times (&tms_start_buf);

    if (LK_HACK) {
	// Easy runway start.
	goto start1;
    }

start:					/* come here for default start	*/
    pp -> x = START_X;
    pp -> y = START_Y;
    pp -> z = START_Z;
    azimuth = START_AZIMUTH;
    vz = 0.0;
    goto mstart;
start1:					/* end of runway start		*/
    pp -> x = 0.0;
    pp -> y = START_Y + 1000; // LK
    pp -> z = -500.0;
    azimuth = 0;
    vz = 0.0;
    goto mstart;
start2:					/* airborn start		*/
    pp -> x = flight_random (20000);
    pp -> y = 8000 + flight_random(6000);
    pp -> z = flight_random (20000);
    azimuth = flight_random(3600);
    vz = (flight_random(60)-80)/fps_knots;
    goto mstart;
start3:					/* used for threat runs		*/
    pp -> x = flight_random (20000);
    pp -> y = 10000 + flight_random(5000);
    pp -> z = 100000.0;
    azimuth = 0;
    vz = (flight_random(60)-160)/fps_knots;
mstart:
    for (itemp = number_planes-1; itemp >= 0; itemp--)
	planes[itemp] -> alive = -1;
    number_planes = 1;
    reset_meters ();
    landing_gear_stuck = -1;		/* can toggle landing gear	*/
    test_mode = FALSE;
    map_daynight (daytime = TRUE);

pickit:
    switch (LK_PICK_PLANE ? pick_plane() : 2) {	/* plane design parameters	*/
case 1:
    plane_type = C150_NAME;
    pp -> type = C150;
    s = 157.0;
    W = 1000.0;
    fuel_weight = 400.0;;
    Mthrust = 300.0;
    b = 28.0;
    ie_pi_AR = .80;
    Lmax = 5.0;	Lmin = -3.0;
    Fmax = 20;	Smax = 0;
    MAX_RK = 0;	MAX_SW = 0;
    MIN_LIFT_SPEED = 70;
    ELEVF = 75.0;
    ROLLF = 130.0;
    landing_gear_stuck = 1;		/* stuck down	*/
    pilot_y = -8.0;
    pilot_z = 18.0;
    break;
case 2:
    plane_type = B747_NAME;
    pp -> type = B747;
    s = 5500.0;				/* wing area in sq. feet	*/
    W = 500000.0;			/* weight of plane in lbs.	*/
    fuel_weight = 100000.0;
    Mthrust = 200000.0;			/* maximum thrust		*/
    b = 220.0;				/* wing span in feet		*/
    ie_pi_AR = .83;			/* efficiency factor		*/
    Lmax = 4.0;				/* maximum lift before wing breaks */
    Lmin = -2.0;			/* minimum lift before wing breaks */
    Fmax = 50;				/* maximum flap deflection	*/
    Smax = 80;				/* maximum spoiler deflection	*/
    MAX_RK = 0;	MAX_SW = 0;
    MIN_LIFT_SPEED = 200;
    ELEVF = 25.0;			/* elevator rate in degrees/sec	*/
    ROLLF = 50.0;			/* roll rate (both at 300 mph)	*/
    pilot_y = -30.0;
    pilot_z = 92.0;
    break;
case 3:
    plane_type = F15_NAME;
    pp -> type = F15;
    s = 608.0;
    W = 28000.0;
    fuel_weight = 14000.0;
    Mthrust = 46000.0;
    b = 43.0;
    ie_pi_AR = .87;
    Lmax = 8.0;	Lmin = -5.0;
    Fmax = 30;	Smax = 60;
    MAX_RK = 4;	MAX_SW = 4;
    MIN_LIFT_SPEED = 100;
    ELEVF = 32.0;
    ROLLF = 140.0;
    pilot_y = -10.0;
    pilot_z = 25.0;
    break;
case 4:
    plane_type = F16_NAME;
    pp -> type = F16;
    s = 390.0;
    W = 18000.0;
    fuel_weight = 8000.0;
    Mthrust = 23000.0;
    b = 32.0;
    ie_pi_AR = .93;
    Lmax = 10.0; Lmin = -7.0;
    Fmax = 40;	Smax = 40;
    MAX_RK = 2;	MAX_SW = 2;
    MIN_LIFT_SPEED = 120;
    ELEVF = 34.0;
    ROLLF = 180.0;
    pilot_y = -9.0;
    pilot_z = 18.0;
    break;
case 5:
    plane_type = F18_NAME;
    pp -> type = F18;
    s = 510.0;
    W = 24000.0;
    fuel_weight = 12000.0;
    Mthrust = 32000.0;
    b = 38.0;
    ie_pi_AR = .90;
    Lmax = 9.0;	Lmin = -6.0;
    Fmax = 50;	Smax = 60;
    MAX_RK = 3;	MAX_SW = 3;
    MIN_LIFT_SPEED = 110;
    ELEVF = 30.0;
    ROLLF = 100.0;
    pilot_y = -10.0;
    pilot_z = 22.0;
    break;
case 6:
    plane_type = P38_NAME;
    pp -> type = P38;
    s = 327.5;
    W = 13500.0;
    fuel_weight = 1600.0;
    Mthrust = 4000.0;
    b = 52.0;
    ie_pi_AR = .90;
    Lmax = 6.0;	Lmin = -3.5;
    Fmax = 50;	Smax = 60;
    MAX_RK = 2;	MAX_SW = 0;
    MIN_LIFT_SPEED = 75;
    ELEVF = 30.0;
    ROLLF = 100.0;
    pilot_y = -10.0;
    pilot_z = 22.0;
    break;
case 27-'0':
    goto end_of_program;
default:
    goto pickit;
    }

	if(moreplanes)	/* haven't made all the planes yet */
		(void)make_planes(0);

    Cdp = .015;				/* coefficient of parasitic drag*/
    ipi_AR = 1.0/(3.1415927 * b*b/s);	/* 1.0 / pi * wing Aspect Ratio	*/
    ie_pi_AR = ipi_AR/ie_pi_AR;		/* 1.0 / pi * AR * efficiency	*/
    ROLLF *= 10.0/(30.0 * 400.0);
    ELEVF *= 10.0/(20.0 * 400.0);

    if (hud) {	/* add plane dependent data to hud object	*/
	makeobj (METER_OVERLAY);	/* type of plane	*/
	cmov2s (HUD_MARGIN-30,30); charstr(plane_type);
	sprintf (charbuf,"%.1f",Lmax);	/* max G force		*/
	cmov2s (HUD_MARGIN-30,50); charstr(charbuf);
	closeobj ();
    }
    Lmax *= GRAVITY;
    Lmin *= GRAVITY;

    debug = timeit = FALSE;
    autopilot = wheels = wing_stall = FALSE;
    tick_counter = 2;			/* force text display	*/
    thrust = roll_speed = elevation_speed = azimuth_speed = 0;
    rudder = elevator = rollers = 0.0;
    airspeed = last_airspeed = climbspeed = last_climbspeed = 0;
    on_ground = pp -> y <= 4.0;
    gefy = .7 * b;
    max_throttle = 100;
    thrust = max_throttle; // LK_DISABLE
    min_throttle = on_ground?-max_throttle:0;
    vx = 0.0;
    vy = 0.0;
    lift = 0.0;	mach = 0.0;
    sidewinders = MAX_SW;
    rockets = MAX_RK;
    pp -> mstatus = 0;
    missile_target = NULL_PLANE_ID;
#define compute_mass() (G_ACC / \
	(W + fuel/12800.0*fuel_weight + ((sidewinders+rockets)<<9)))
    fuel = 100 << 7;
    inverse_mass = compute_mass();

#define PLANE_VIEW 1
#define TOWER_VIEW 2
    view_switch = PLANE_VIEW;			/* view from plane	*/
    if (LK_HACK && 1) {
        view_switch = TOWER_VIEW;
    }
    plane_fov = tower_fov = 360;
    reset_fov (plane_fov);

    if (LK_HACK) {
        tower_fov = 30;
        reset_fov (tower_fov);
    }

    last_py = pp -> y;
    pp -> elevation = elevation = 0;
    pp -> twist = twist = 0;
    pp -> azimuth = azimuth;
    pp -> status = MSTART;
    pp -> alive = int_tps << 2;
    flaps = spoilers = 0;
    view_angle = 0;
    fuel_rate = fuel_consump (Mthrust,W);
    rebuild_status ();

#ifdef WINGMAN
    /*
     *  init wingman info
     */
    for(wmpos = 0; wmpos < 6; wmpos++)
    {
	wm_x[wmpos] = pp->x;
	wm_y[wmpos] = pp->y;
	wm_z[wmpos] = pp->z;
	wm_twist[wmpos] = twist;
	wm_elevation[wmpos] = elevation;
	wm_azimuth[wmpos] = azimuth;
    }
    wmpos = 0;
#endif

#ifdef DOGFIGHT
    for (itemp=0; itemp < MAX_PLANES; itemp++)
	get_indata (0);		/* read all input data	*/
    reset_meters ();
    display_score ();
#endif
    if (on_ground) {
	qenter (KEYBD,'f');		/* flaps up 1 notch	*/
	qenter (KEYBD,'f');		/* flaps up 1 notch	*/
	qenter (KEYBD,'f');		/* flaps up 1 notch	*/
	Cdp *= 3.0;
    }
    else thrust = max_throttle;
    if (on_ground || landing_gear_stuck>0)
    then qenter (KEYBD,'l');	/* put wheels down	*/

    /****************************************************************
     *	Main loop
     ****************************************************************/
    while (1) {
	/* read all queue entries	*/
	if (dials) check_dials(); 
        while (qtest ()) {
	    type = qread (&val);
	     if (type == ESCKEY) {
		 if (!val) {
		    goto end_of_program;
		 }
	     } else if (type == KEYBD) {
		switch (val) {
		case 18:  /* ^R */
			redraw_screen();	/* because wsh scrolling sometimes
				causes bleed through */
			continue;
		case 26:  /* ^Z (iconize and suspend) */
		    stopit();
			continue;
		case 27:  /* ESC */
		    goto end_of_program;
		case 'a':
		    thrust -= 5;
		    if (thrust < min_throttle) thrust = min_throttle;
		    break;
		case 's':
		    thrust += 5;
		    if (thrust > max_throttle) thrust = max_throttle;
		    break;
		case 'z':
		case 'x':
		    if (view_switch == TOWER_VIEW) {
			if (val == 'x')
			then {if (tower_fov > 30) then tower_fov -= 25;}
			else if (tower_fov < 600) then tower_fov += 25;
			reset_fov (tower_fov);
		    }
		    break;
		case 'd':
		    if (view_switch == PLANE_VIEW) {
			view_switch = TOWER_VIEW;
			reset_fov (tower_fov);
		    }
		    else if (view_switch == TOWER_VIEW) {
			view_switch = PLANE_VIEW;
			reset_fov (plane_fov);
		    }
		    break;
#ifdef WINGMAN
		case 'W':
		    wingmanview = !wingmanview;
		    break;
#endif
		case 'v':
		    autopilot = !autopilot;
		    if (autopilot) {
			target_speed = airspeed;
			target_climb = climbspeed;
			target_twist = twist;
		    }
		    break;
		case 'f':
		case 'F':
		    if (val == 'f') {if (flaps < Fmax) then flaps += 10;}
		    else if (flaps > 0) then flaps -= 10;
		    max_cl = 1.5 + flaps/62.5;
		    min_cl = flaps/62.5 - 1.5;
		    tilt_factor = .005 * flaps + .017;
		    break;
		case 'c':
		case 'C':
		    if (val == 'c'){if (spoilers < Smax) then spoilers += 20;}
		    else if (spoilers > 0) then spoilers -= 20;
		    Spdf = .0025 * spoilers;	/* adjust drag and lift	*/
		    Splf = 1.0 - .005 * spoilers;
		    break;
		case 'l':
		    if (landing_gear_stuck != wheels) {
			if (wheels)		/* bring wheels up	*/
			{
			    if (pp->type == F16W)
				wheels_retracting = 1;
			    else if (pp->type == P38W)
			    {
				pp->type = P38;
				pp->wheels = 0;
			    }
			    wheels = FALSE;
			    Cdp /= 2.0;

			    if (on_ground && pp->status > MEXPLODE) {
make_crash ("You retracted the landing gear while on the ground");
broadcast ("retracted my landing gear while on the ground");
			    }
			}
			else {			/* put wheels down	*/
			    wheels = TRUE;
			    if (pp->type == F16) {
				pp->type = F16W;
				wheels_retracting = -1;
				pp->wheels = 10;
			    }
			    else if(pp->type == P38)
			    {
				pp->type = P38W;
				pp->wheels = 10;
			    }
			    Cdp *= 2.0;
			}
		    }
		    break;
		case 't':
		    /* if I'm alive and no weapon already fired	*/
		    if (pp -> status > MEXPLODE && !pp -> mstatus) {
			ptemp = find_closest_plane (pp);
			if (ptemp) {
			    /* lock on the plane for 1 second	*/
			    missile_target = PLANE_ID (ptemp);
			    tick_counter = 2;
			}
		    }
		    break;
		case 'q':
		case 'w':
		case 'e':
		    /* if I'm alive and no weapon already fired	*/
		    if (pp -> status > MEXPLODE && !pp -> mstatus)
		    if (!on_ground) {
			if (val == 'w' && sidewinders > 0) {
			    sidewinders--;
			    pp -> mtype = TYPE_SIDEWINDER;
			    pp -> mstatus = MSTART;
			    if (missile_target == NULL_PLANE_ID) {
				ptemp = find_closest_plane (pp);
				if (ptemp)
				then missile_target = PLANE_ID (ptemp);
			    }
			}
			else if (val == 'q' && rockets > 0) {
			    rockets--;
			    pp -> mtype = TYPE_ROCKET;
			    pp -> mstatus = MSTART;
			    missile_target = NULL_PLANE_ID;
			}
			temp = fabs(vy) + fabs(vz);
			if (val == 'e') {
			    pp -> mtype = TYPE_CANNON;
			    pp -> mstatus = MFINISH + int_tps;
			    temp = -2000.0/TPS - temp;
			    missile_target = NULL_PLANE_ID;
			}
			else temp = -500.0/TPS - temp;

			missile_vx = ptw[2][0] * temp;
			missile_vy = ptw[2][1] * temp;
			missile_vz = ptw[2][2] * temp;
			pp -> mx = pp -> x + missile_vx;
			pp -> my = pp -> y + missile_vy;
			pp -> mz = pp -> z + missile_vz;
			pp -> mkill = NULL_PLANE_ID;
			tick_counter = 2;
			rebuild_status ();
		    }
		    break;
		case 'n':
		    map_daynight (daytime = !daytime);
		    break;
		case 'h':
		    display_help ();
		    wait_for_input();
		    break;
		case 'r':
		case 'R':
		case 'u':
		case 'U':
		    if (pp -> status == 0)
			if (val == 'r') then goto start;
			else if (val == 'R') goto start1;
			else if (val == 'U') goto start3;
			else goto start2;
		    /* if missile launched, then blow up */
		    else if (pp->mstatus > MEXPLODE && 
			     pp->mtype != TYPE_CANNON)
			 then pp->mstatus = MEXPLODE;
		    break;
		case 'T':
		    threat_mode = !threat_mode;
		    break;
		case '~':
		    test_mode = !test_mode;
		    fuel_rate = fuel_consump (Mthrust,W);
		    sidewinders = rockets = 0;
		    rebuild_status ();
		    break;
		case '?':
		    timeit = !timeit;
		    /*
		    if (timeit) {
			time_start = times (&tms_start_buf);
			tick_counter = TPS;
		    }
		    */
		    break;
#ifdef DEBUG
		case '':
		    view_switch = -view_switch;
		    break;
		case 'p':
		    wait_for_input ();
		    break;
		default:
		    if (val >= '0' && val <= '9')
		    then debug ^= 1 << (val-'0');
#endif
		}
	    }

	    
	    else if (type == REDRAW) {

		redraw_screen();
		tick_counter = 2;
	    }
		else if(type == WINQUIT)	/* should only happen if iconisized */
		    goto end_of_program;
	    else if (val) {	/* only read button down presses	*/
		if (type == LEFTMOUSE) {
		    // rudder = (getvaluator (MOUSEX) - XMIDDLE)/10.0/XMAXSCREEN;
		    // change_rudder(rudder);
		}
		else if (type == LEFTARROWKEY && view_switch == PLANE_VIEW) {
		    view_angle += 900;
		    if (view_angle > 1800) then view_angle -= 3600;
		}
		else if (type == RIGHTARROWKEY && view_switch == PLANE_VIEW) {
		    view_angle -= 900;
		    if (view_angle < -1800) then view_angle += 3600;
		}	/* and ignore any other types	*/
	    }
	}		/* of while qtest	*/

	/****************************************************************
	 *	handle visible retractable landing gear
	 ****************************************************************/
	if (pp->type == F16W) {
	    if (wheels_retracting > 0) { 	/* going up	*/
		pp->wheels++;
		if (pp->wheels > 10) {
		    pp->type = F16; /* change to f16 with no wheels */
		    pp->wheels = 10;
		    wheels_retracting = 0;
		}
	    }
	    else if (wheels_retracting < 0) { 	/* going down	*/
		pp->wheels--;
		if (pp->wheels < 0) {
		    pp->wheels = 0;
		    wheels_retracting = 0;
		}
	    }
         }
	/****************************************************************
	 *	process incoming data packets
	 ****************************************************************/
	pp->alive = int_tps << 2;	/* always make me alive		*/
	if (pp -> status > MEXPLODE)
	then if (pp -> status > 65000)	/* increment my timestamp	*/
	     then pp -> status = MSTART;
	     else pp -> status++;
	else if (pp -> status > 0) then pp -> status--;
#ifdef DOGFIGHT
	ptemp = get_indata (1);	/* read all input data		*/
	if (ptemp != NULL) {	
	    sprintf (charbuf,"You were blown up by an enemy %s fired by %s",
			WEAPON_NAME[ptemp -> mtype], ptemp -> myname);
	    make_crash (charbuf);
	}
#endif

    /****************************************************************
     *	AUTOPILOT code
     ****************************************************************/
    if (pp -> status > MEXPLODE) {
	if (autopilot) {
	    int diff;

	    itemp = getvaluator (MOUSEY);
	    /* first adjust the roll ???	*/

	    /* adjust speed next	*/
	    diff = target_speed - airspeed - ((airspeed-last_airspeed)<<3);
	    diff = (diff+4) >> 3;
	    if (diff > 0) {		/* need more acceleration	*/
		if (thrust < max_throttle)
		then thrust += diff; 		/* try engines first	*/
		else if (!on_ground) {		/* next wheels and yaw	*/
		    if (flaps && vz < -400.0/TPS) qenter (KEYBD,'F');
		    else if (rudder > 0.05) then change_rudder (rudder -= .1);
		    else if (rudder < -0.05) then change_rudder(rudder += .1);
		    else setvaluator (MOUSEY,	/* lastly pitch		*/
				itemp+=(int)(diff/-ELEVF/vz), 
				0,YMAXSCREEN);
		}
	    }
	    else if (diff < 0) {	/* need less acceleration	*/
		thrust += diff; 	/* reduce thrust		*/
		if (thrust < min_throttle) thrust = min_throttle;
	    }

	    /* adjust climb last - this has highest priority	*/
	    diff = target_climb -climbspeed-((climbspeed-last_climbspeed)<<7);
	    diff = (diff+4) >> 4;
	    if (wing_stall) {
		if (thrust < max_throttle) thrust += 10;
		if (spoilers) then qenter (KEYBD,'C');
	    }
	    else if (diff != 0) {
		if (twist > 900 && twist < 2700) then diff = -diff;
		setvaluator(MOUSEY,itemp+=(int)(diff/ELEVF/vz),
				0,YMAXSCREEN);
	    }
	    if (thrust > max_throttle) thrust = max_throttle;
	}
#define DELAY (TPS/4)
	/* tenths of degrees per tick	*/
	int tilt_x = XMAXSCREEN * (getvaluator(DIAL0) - tilt_left) / (tilt_right - tilt_left);
	tilt_x = XMIDDLE;
	rollers = ROLLF * ((tilt_x - XMIDDLE+8) >> 4);
	itemp = rollers * vz - roll_speed;	/* delta	*/
	if (itemp!=0)
	    if (itemp >= DELAY || itemp <= -DELAY)
	    then itemp /= DELAY;
	    else itemp = itemp>0 ? 1 : -1;
	if (wing_stall > 0) {
	    itemp >>= wing_stall;
	    itemp += flight_random(wing_stall << 3);
	}
	roll_speed += itemp;

	int tilt_y = YMAXSCREEN * (getvaluator(DIAL1) - tilt_forward) / (tilt_back - tilt_forward) ;
	tilt_y = YMIDDLE;
	elevator = ELEVF * ((tilt_y - YMIDDLE+8) >> 4);
	itemp = elevator * vz + vy - elevation_speed;
	// printf("tilt x: %10d, rollers: %10g, tilt y: %10d, elevation: %10g, tps: %3d, itemp: %d\n", tilt_x, rollers, tilt_y, elevator, tps, itemp);
	printf("tilt y: %5d, elevation: %5g, tps: %3d, itemp: %d\n", tilt_y, elevator, tps, itemp);
	printf("%g * %g + %g - %d = %d\n", elevator, vz, vy, elevation_speed, itemp);
	if (itemp!=0)
	    if (itemp >= DELAY || itemp <= -DELAY)
	    then itemp /= DELAY;
	    else itemp = itemp>0 ? 1 : -1;
	if (wing_stall > 0) {
	    itemp >>= wing_stall;
	    itemp += flight_random(wing_stall << 1);
	}
	elevation_speed += itemp;

	temp = rudder * vz - 2.0 * vx;
	if (on_ground) {
#define MAX_TURNRATE (600/TPS)
	    itemp = 16.0 * temp;
	    if(itemp < -MAX_TURNRATE || itemp > MAX_TURNRATE){
		if (itemp < 0)		/* clip turn rate	*/
		then itemp = -MAX_TURNRATE;
		else itemp = MAX_TURNRATE;
		if (fabs(vz) > 10.0/TPS) {	/* decrease with velocity */
		    temp = 0.4 * TPS * (rudder*vz - .75); /* skid effect */
		    if (temp < -MAX_TURNRATE || temp > MAX_TURNRATE)
		    then temp = itemp;
		    itemp -= temp;
		}
	    }
	}
	else itemp = temp;	/* itemp is desired azimuth speed	*/
	itemp -= azimuth_speed;	/* itemp is now desired-actual		*/

	if (itemp!=0)
	    if (itemp >= DELAY || itemp <= -DELAY)
	    then itemp /= DELAY;
	    else itemp = itemp>0 ? 1 : -1;
	azimuth_speed += itemp;

	if (on_ground) {
	    /* dont allow negative pitch unless positive elevation	*/
	    if (elevation_speed < 0) {
		 if (elevation <= 0) then elevation_speed = 0;
	    }
	    else {		/* mimic gravitational torque	*/
		itemp = -((int)vz * int_tps + MIN_LIFT_SPEED) >> 2;
		if (itemp < 0 && elevation <= 0) then itemp = 0;
		if (elevation_speed > itemp)
		then elevation_speed = itemp;
	    }
	    roll_speed = 0;
	}

	/****************************************************************
	 *	concat incremental rotations and get new angles back
	 ****************************************************************/
	popmatrix ();			/* pop back to identity		*/
	pushmatrix ();			/* push it			*/
//	if ((tick_counter&1) == 0) {	/* every once in a while	*/
	if (TRUE) {
	    translate (pp->x,pp->y,pp->z);/* rebuild old ptw		*/
	    rotate (azimuth,'y');	/* to keep it normalized	*/
	    rotate (elevation,'x');
	    rotate (twist,'z');
	}
	else loadmatrix(ptw);		/* otherwise reload old one	*/
	translate (vx,vy,vz);		/* build up new one		*/
	if (azimuth_speed) rotate (azimuth_speed,'y');
	if (elevation_speed) rotate (elevation_speed,'x');
	if (roll_speed) rotate (roll_speed,'z');
	getmatrix (ptw);		/* fetch new one		*/

	/* analyze new ptw	*/
	elevation = -xasin(ptw[2][1]);
	gl_sincos (elevation,NULL,&temp);
	if (temp != 0.0) {
	    azimuth = xasin (ptw[2][0]/temp);
	    if (ptw[2][2] < 0.0)		/* if heading into z	*/
	    then azimuth = 1800 - azimuth;	/* then adjust		*/
	    if (azimuth < 0) then azimuth += 3600;

	    twist = xasin (ptw[0][1]/temp);
	    if (ptw[1][1] < 0.0)		/* if upside down	*/
	    then twist = 1800 - twist;
	    if (twist < 0) then twist += 3600;
	}
	last_px = pp -> x;			/* save last position	*/
	last_py = pp -> y;
	last_pz = pp -> z;
	pp -> x = ptw [3][0];
	pp -> y = ptw [3][1];
	pp -> z = ptw [3][2];
	climbspeed = TPS * (pp -> y - last_py);

#ifdef WINGMAN
	wm_x[wmpos] = pp->x;
	wm_y[wmpos] = pp->y;
	wm_z[wmpos] = pp->z;
	wm_twist[wmpos] = twist;
	wm_elevation[wmpos] = elevation;
	wm_azimuth[wmpos] = azimuth;
	wmpos = (wmpos+1) % 6;
#endif

	/****************************************************************
	 *	perform incremental rotations on velocities
	 ****************************************************************/
	popmatrix ();				/* pop and push I	*/
	pushmatrix ();
	if (roll_speed) rotate (-roll_speed,'z');
	if (elevation_speed) rotate (-elevation_speed,'x');
	if (azimuth_speed) rotate (-azimuth_speed,'y');
	translate (vx,vy,vz);
	printf("r=%d,e=%d,a=%d,vx=%g,vy=%g,vz=%g\n",
		roll_speed, elevation_speed, azimuth_speed,
		vx, vy, vz);
	getmatrix (incremental);	/* to get new rotated velocities */
	float before_vy = vy;
	vx = incremental[3][0];
	vy = incremental[3][1];
	vz = incremental[3][2];
	printf("vy = %10g, elevation_speed = %10d, vy = %10g\n",
		before_vy, elevation_speed, vy);
		

	/****************************************************************
	 *	check altitude for too high, and landing/takeoff
	 ****************************************************************/
	if (pp -> y > 50000.0) then thrust = 0;	/* flame out		*/
	else if (pp -> y > 4.0) {		/* not on ground	*/
	    if (on_ground) {			/* if was on ground	*/
		clear_report_card ();		/* clear report card	*/
		Cdp /= 3.0;			/* decrease drag	*/
		min_throttle = 0;		/* no reverse engines	*/
	    }
	    on_ground = FALSE;
	}
	else if (pp -> y < .5) {		/* check for on the ground */
	    if (IN_BOX (pp,-800.0,100.0, -9500.0,1000.0) || 
		IN_BOX (pp,100.0,1300.0, -2500.0,-1500.0) || 
		IN_BOX (pp,-2300.0,-800.0, -4900.0,-2000.0) || LK_DISABLE_SWAMPS)
	    if (!on_ground) {			/* and not on ground before */
		int rating,nm;

		Cdp *= 3.0;			/* increase drag	*/
		min_throttle = -max_throttle;	/* allow reverse engines*/
		rating = report_card (-climbspeed,twist,
				    (int)(vx * TPS), (int)(-vz * fps_knots),
				    wheels, pp);
		if (rating == -1) {		/* oops - you crashed	*/
		    pp -> status = MEXPLODE;	/* set to exploding	*/
		    pp -> lost++;		/* increment count	*/
		}
		else {
		    fuel += rating << 7;
		    if (fuel > (100 << 7)) then fuel = 100 << 7;
		    max_throttle = 100;
		}
		rating = rating/10;	/* number of added missiles	*/
		nm = MAX_SW - sidewinders;	/* need this many	*/
		if (nm > 0) {
		    if (nm > rating) nm = rating;/* get this many	*/
		    sidewinders += nm;
		    rating -= nm;
		}
		nm = MAX_RK - rockets;		/* need this many	*/
		if (nm > 0) {
		    if (nm > rating) nm = rating;/* get this many	*/
		    rockets += nm;
		}
		test_mode = FALSE;
		fuel_rate = fuel_consump (Mthrust,W);
		rebuild_status ();
	    } else;
	    else {
		make_crash ("You crashed into the swamps");
		broadcast ("crashed into the swamps");
	    }
	    ptw[3][1] = pp -> y = 0.0;
	    on_ground = TRUE;
	    if (pp -> status > MEXPLODE) {
		if (elevation < 0) elevation = 0;/* kill negative elevation */
		if (twist != 0) twist = 0;	/* kill any twist	*/
	    }
	}
    }	/* end not crashing	*/

	/****************************************************************
	 *	update MISSILES
	 ****************************************************************/
	if (pp -> mstatus) {		/* if missile launched	*/
	    if (pp -> mstatus > MEXPLODE) {	/* if not exploding 	*/
		pp -> last_mx = pp -> mx;	/* save last position	*/
		pp -> last_my = pp -> my;
		pp -> last_mz = pp -> mz;
		pp -> mx += missile_vx;		/* update position	*/
		pp -> my += missile_vy;
		pp -> mz += missile_vz;
		if (pp -> mtype == TYPE_CANNON) {
		    pp -> last_mx = .2 * pp -> last_mx + .8 * pp -> mx;
		    pp -> last_my = .2 * pp -> last_my + .8 * pp -> my;
		    pp -> last_mz = .2 * pp -> last_mz + .8 * pp -> mz;
		}
		if (pp -> my < 10.0) {		/* if too low, explode	*/
		    pp -> my = 20.0;
		    if (pp -> mtype == TYPE_CANNON)
		    then pp -> mstatus = 1;	/* kill a cannon shot	*/
		    else pp -> mstatus = MEXPLODE;
		}
		if (pp -> mstatus == MFINISH) { /* coasting		*/
		    missile_vx *= .995;		/* air resistance hack	*/
		    missile_vy *= .9975;
		    missile_vz *= .995;
		    missile_vy -= GRAVITY;	/* gravity		*/
		    missile_target = NULL_PLANE_ID;
		    if (pp -> mtype == TYPE_CANNON)
		    then pp -> mstatus = 1;	/* kill a cannon shot	*/
		    else pp -> mstatus++;	/* else continue to coast */
		}
		else {	/* not finished - still has gas	*/
		    float dx,dy,dz, acc,ticks, dvx,dvy,dvz;

		    ticks = pp -> mstatus - MFINISH;
		    if (missile_target == NULL_PLANE_ID)
		    then ptemp = NULL;
		    else ptemp = lookup_plane (missile_target);

		    if (ptemp == NULL) {
			dx = missile_vx;
			dy = missile_vy;
			dz = missile_vz;
			acc = GRAVITY * .25 * ticks;
		    }
		    else {	/* lock on the target	*/
			static float last_tpx,last_tpy,last_tpz;
			int txi,tyi,tzi;	/* time to intercept	*/

			if (pp -> mstatus == MSTART) {
			    last_tpx = ptemp->x;
			    last_tpy = ptemp->y;
			    last_tpz = ptemp->z;
			}
			dx = ptemp->x - pp -> mx;
			dy = ptemp->y - pp -> my;
			dz = ptemp->z - pp -> mz;
			dvx = (ptemp -> x - last_tpx) - missile_vx;
			dvy = (ptemp -> y - last_tpy) - missile_vy;
			dvz = (ptemp -> z - last_tpz) - missile_vz;
			if (fabs(dvx) < .00001) then txi = MLIFE;
			else {
			    txi = dx/-dvx;
			    if (txi < 0) then txi = -txi;
			}
			if (fabs(dvy) < .00001) then tyi = MLIFE;
			else {
			    tyi = dy/-dvy;
			    if (tyi < 0) then tyi = -tyi;
			}
			if (fabs(dvz) < .00001) then tzi = MLIFE;
			else {
			    tzi = dz/-dvz;
			    if (tzi < 0) then tzi = -tzi;
			}
#ifdef DEBUG
if (debug & (1<<4)) {
	printf ("Status:%3d  Time x,y,z: %3d %3d %3d",
			pp -> mstatus,txi,tyi,tzi);
	printf ("	Dist: %d",itemp = sqrt(dx*dx + dy*dy + dz*dz));
	if (itemp < 250)
	then printf (" <== killed *****\n");
	else printf ("\n");
}
#endif
			/* find maximum intercept time	*/
			if (tyi > txi) then txi = tyi;
			if (tzi > txi) then txi = tzi;
			if (txi > MLIFE) then txi = MLIFE;

			if (txi == 0)
			then temp = 1.7/.2;
			else temp = 1.7/txi;	/* cut it by 1.7	*/
			dx = temp * dx + dvx;	/* and aim for it	*/
			dy = temp * dy + dvy;
			dz = temp * dz + dvz;
			acc = 16.0 * GRAVITY;	/* with 16 G's		*/

			last_tpx = ptemp->x; 	/* save target's last pos */
			last_tpy = ptemp->y;
			last_tpz = ptemp->z;
		    }
		    if (pp -> mtype != TYPE_CANNON) {
			temp = acc / (fabs(dx) + fabs(dy) + fabs(dz));
			missile_vx += dx * temp;
			missile_vy += dy * temp;
			missile_vz += dz * temp;
		    }
		}
	    }	/* end of if (pp -> mstatus > MEXPLODE)	*/
	    else missile_target = NULL_PLANE_ID;
	    pp -> mstatus--;		/* decrement status	*/
	}

	/****************************************************************
	 * set up windshield, push the ortho, and load perspective
	 ****************************************************************/
	pp -> azimuth = azimuth;
	pp -> elevation = elevation;
	pp -> twist = twist;
	callobj (SETUP_WORLD);

	if (view_switch == TOWER_VIEW) {	/* view from the tower	*/
	    my_lookat (eye_x,eye_y,eye_z, pp->x,pp->y,pp->z);
	    callobj (WORLD_OBJECT);		/* draw the world	*/
	    callobj (RUNWAY_STRIPES);
	    if (!daytime) then callobj (LIGHTS);
	    popmatrix();
	    draw_vasi (pp);			/* show VASI lights	*/
	    draw_buildings(eye_x, eye_y, eye_z, 0,number_planes);
	    draw_missiles ();
	    draw_hud (pp,tick_counter,vx,vy,vz,climbspeed,mach,lift/GRAVITY,
			wheels,flaps,spoilers,autopilot,fuel >> 7,thrust);
	}
	else if (view_switch == PLANE_VIEW) 	/* view from the plane	*/
	{
	    if (view_angle != 0) 
		rotate(-view_angle, 'y');
	    translate(0.0, pilot_y, pilot_z);	/* pilot's seat loc.	*/

#ifdef WINGMAN
	    if (!wingmanview)
	    {
#endif
		rotate(-twist, 'z');
		rotate(-elevation, 'x');
		rotate(-azimuth, 'y');
		translate(-pp->x, -pp->y, -pp->z);
#ifdef WINGMAN
	    }
	    else
	    {
		rotate(-wm_twist[wmpos], 'z');
		rotate(-wm_elevation[wmpos], 'x');
		rotate(-wm_azimuth[wmpos], 'y');
		translate(-wm_x[wmpos], -wm_y[wmpos], -wm_z[wmpos]);
	    }
#endif

	    callobj (WORLD_OBJECT);		/* draw the world	*/
	    if (pp->x*pp->x + pp->y*pp->y + pp->z*pp->z < 15000.0*15000.0)
	    then callobj (RUNWAY_STRIPES);
	    else callobj (FAKE_STRIPES);
	    if (!daytime) then callobj (LIGHTS);
	    popmatrix();
	    draw_vasi (pp);			/* show VASI lights	*/

#ifdef WINGMAN
	    if (!wingmanview)
#endif
		draw_buildings(pp->x, pp->y, pp->z, 1, number_planes);
#ifdef WINGMAN
	    else
		draw_buildings(wm_x[wmpos], wm_y[wmpos], wm_z[wmpos],
			       0, number_planes);
#endif

	    draw_missiles ();
            if (LK_DISABLE) {
	    draw_hud (pp,tick_counter,vx,vy,vz,climbspeed,mach,lift/GRAVITY,
			wheels,flaps,spoilers,autopilot,fuel>>7,thrust);
            }
	    if (view_angle == 0) {
		charstr ("Front view");
		if (!hud) {
		    setlinestyle (1);
		    rects (-40,-40,40,40);
		    setlinestyle (0);
		}
	    }
	    else if (view_angle == 900) then charstr ("Left view");
	    else if (view_angle == -900) then charstr ("Right view");
	    else charstr ("Back view");
	}
	draw_messages ();		/* display any network messages	*/

	/****************************************************************
	 *	compute new velocities, accelerations
	 ****************************************************************/
        if (LK_DISABLE) {
            callobj (CLEAR_METERS);		/* sets up viewport, ortho, wm	*/
        }

	/* check my missile against my plane		*/
	if (pp -> mstatus && pp->mstatus < MEXPLODE && test_blow_up(pp,pp)) {
	    sprintf (charbuf,"You were blown up by your own %s",
				WEAPON_NAME[pp -> mtype]);
	    make_crash (charbuf);
	    sprintf (charbuf,"blown up by my own %s",
				WEAPON_NAME[pp -> mtype]);
	    broadcast (charbuf);
	}
#ifdef DOGFIGHT
	if (pp->mstatus) check_missile (pp);/* first test for missile hit*/
	send_outdata (pp);		/* send my data out over net	*/
#endif
	if (fuel <= 0) {		/* out of gas	*/
	    thrust = 0;
	    max_throttle = 0;
	    min_throttle = 0;
	}

    if (pp -> status > MEXPLODE) {
	if (pp -> y > gefy) then kl = 1.0;	/* ground effect factor	*/
	else {
	    kl = pp -> y/b;		
	    if (kl > .225)
	    then kl = .484 * kl + .661;
	    else kl = 2.533 * kl + .20;
	}

	/* compute new accelerations, lift: only if vz is negative	*/
	val = (vz >= 0.0);
	if (!val) {
	    ae = vy/vz + tilt_factor;
	    Cl = uCl = ae/(.17 + kl*ipi_AR);
	    if (Cl > max_cl) {		/* check for positive stall	*/
		Cl = 3.0 * max_cl - 2.0 * Cl;
		wing_stall = 1;
		if (Cl < 0.0) {
		    wing_stall += 1 - (int)(Cl/max_cl);
		    Cl = 0.0;
		}
		if (uCl > 5.0) then uCl = 5.0;
	    }
	    else if (Cl < min_cl) {	/* check for negative stall	*/
		Cl = 3.0 * min_cl - 2.0 * Cl;
		wing_stall = 1;
		if (Cl > 0.0) {
		    wing_stall += 1 - (int)(Cl/min_cl);
		    Cl = 0.0;
		}
		if (uCl < -5.0) then uCl = -5.0;
	    }
	    else wing_stall = FALSE;
	}
	else {
	    Cl = uCl = 0.0;
	    wing_stall = on_ground ? 0 : vz;
	    ae = 0;
	}
	if (wing_stall > 64) then wing_stall = 64;
	if ((tick_counter & 1) == 0) {	/* only do on even ticks	*/
	    if (pp -> y <= 36000.0)	/* compute speed of sound	*/
	    then sos = -1116.0/TPS + (1116.0-968.0)/TPS/36000.0 * pp -> y;
	    else sos = -968.0/TPS;
	    itemp = ((int)pp -> y) >> 10;
	    if (itemp > 74) then itemp = 74;
	    ro2 = .5 * ro[itemp];
	    if (Cl < .2)
	    then mcc = .7166666 + .1666667 * Cl;
	    else mcc = .7833333 - .1666667 * Cl;
	    mach = vz/sos;		/* and current mach number	*/
	    mratio = mach/mcc;
	    if (mratio < 1.034) then Cdc = 0.0;
	    else {
		Cdc = .082 * mratio - 0.084788;
		if (Cdc > .03) then Cdc = .03;
	    }
	    if (spoilers > 0) then Cdc += Spdf;
	}

	qs = ro2 * vz * s;		/* assume V approx = vz	*/

	lift = Cl * qs;
	g_limit = FALSE;
	if (spoilers > 0) then lift *= Splf;
    relift:
	ay = vz * lift;
	az = -vy * lift;
	lift = ay * inverse_mass;	/* save for wing loading meter	*/
	if (lift > Lmax) {
	    lift = .99 * Lmax/inverse_mass/vz;
	    g_limit = TRUE;
	    goto relift;
	}
	else if (lift < Lmin) {
	    lift = .99 * Lmin/inverse_mass/vz;
	    g_limit = TRUE;
	    goto relift;
	}

	/* engine thrust		*/
	az -= .01/TPS/TPS*thrust * Mthrust;

	/* drag - needs to be broken into y/z components		*/
	Cd = Cdp + kl*uCl*uCl*ie_pi_AR + Cdc;
	zdrag = Cd * qs;
	ydrag = vy * zdrag;
	zdrag = vz * zdrag;
	if (val) {			/* if vz is positive	*/
	    ay -= ydrag;
	    az -= zdrag; 
	}
	else {
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
	if (on_ground && pp -> status > MEXPLODE) {
	    float cos;

	    vx = 0.0;
	    gl_sincos (elevation,&temp,&cos);
	    temp = vz * temp/cos;
	    if (vy+ay < temp) then ay = temp - vy;
	}
	vy += ay;
    }

#ifdef DEBUG
if (debug & (1<<1)) {
    temp = inverse_mass * TPS *TPS;
    printf ("----------------------%d----------------------\n",tick_counter);
    printf ("Position (xyz): %12.2f%12.2f%12.2f    %s\n",
		pp -> x,pp -> y,pp -> z,on_ground?"*** ON THE GROUND":"");
    printf ("Elevation, azimuth, roll: %6d%6d%6d\n",
			elevation,azimuth,twist);
    printf ("Elev, azim, roll speeds:  %6d%6d%6d\n",
			elevation_speed,azimuth_speed,roll_speed);
    printf ("Rotated velocities per tick: %9.2f%9.2f%9.2f\n",
	incremental[3][0]*TPS,incremental[3][1]*TPS,incremental[3][2]*TPS);
    printf ("Speed-of-sound:%8.1f  Mach:%5.2f  Mcc:%5.2f  Mach/Mcc:%5.2f\n",
		-sos*TPS,mach,mcc,mratio);
    printf ("Cd:%8.4f=%7.4f +%7.4f +%7.4f  (p+i+c)\n",
		Cd,Cdp,kl*uCl*uCl*ie_pi_AR,Cdc);
    printf ("Cl:%5.2f  kl:%5.2f  ro2:%7.4f  qs:%6.2f\n",
		Cl,kl,ro2,TPS*TPS*vz*qs);
    printf ("Thrust:   %21.2f\n",-.01*thrust * Mthrust * inverse_mass);
    if (spoilers > 0) then qs *= Splf;
    printf ("Lift:     %14.2f%7.2f        angle:%6.2f\n",
		vz*Cl*qs*temp,-vy*Cl*qs*temp, 57.3 * (ae-tilt_factor));
    printf ("Drag:     %14.2f%7.2f\n",ydrag*temp,zdrag*temp);
    printf ("Gravity:  %7.2f%7.2f%7.2f\n",
		ptw[0][1]*-G_ACC, ptw[1][1]*-G_ACC, ptw[2][1]*-G_ACC);
    printf("-------------------------------   Mass: %g\n",G_ACC/inverse_mass);
    printf ("Totals:   %7.2f%7.2f%7.2f\n",ax*TPS*TPS,ay*TPS*TPS,az*TPS*TPS);
    printf ("New velocities per tick: %9.2f%9.2f%9.2f\n",
			    vx*TPS,vy*TPS,vz*TPS);
}
if (debug & (1<<5)) printf ("Wing_stall = %d\n",wing_stall);
if (debug & (1<<3)) {
    if (pp -> mstatus) {
	printf ("----------------------------------------\n");
	printf ("Missile status: %d\n",pp -> mstatus);
	printf ("Missile velocities (xyz): %12.2f%12.2f%12.2f\n",
			missile_vx*TPS,missile_vy*TPS,missile_vz*TPS);
	printf ("Missile position (xyz):   %12.2f%12.2f%12.2f\n",
			pp -> mx, pp -> my, pp -> mz);
    }
}
#endif

	/****************************************************************
	 *	display METERS
	 ****************************************************************/
	tick_counter--;			/* 7,6,5,4,3,2,1,0	*/	
	if (tick_counter == 2 && !pp -> mstatus) /* zero target if one	*/
	then missile_target = NULL_PLANE_ID;

	if (tick_counter <= 1 && wing_stall) then ringbell();
	if ((tick_counter & 1) && LK_DISABLE) {		/* only do this on odd ticks	*/
	    last_airspeed = airspeed;	/* needed for autopilot		*/
	    last_climbspeed = climbspeed;
	    airspeed = -(int)(fps_knots * vz);

	    makeobj (RADAR);		/* make the radar object	*/
	    {
		Plane *ptemp2;
		translate (-pp -> x,-pp -> z,0.0);
#ifdef DOGFIGHT
		FOR_EACH_PLANE (ptemp,ptemp2)
		if (ptemp != pp) {
		    color (ptemp -> y <= pp -> y ? green0:red);
		    if (hud) {
			cmov2(ptemp->x,ptemp->z); charstr("^");
		    }
		    else rectf (ptemp -> x - 200.0, ptemp -> z - 200.0,
			    ptemp -> x + 200.0, ptemp -> z + 200.0);
		}
#endif
		color (red);		/* draw all missiles in red	*/
		FOR_EACH_PLANE (ptemp,ptemp2)
		    if (ptemp -> mstatus && ptemp -> mtype != TYPE_CANNON)
		    then pnt2 (ptemp -> mx, ptemp -> mz);
	    }
	    closeobj ();
	}

	    if (tick_counter == 1 && fuel > 0) {
		if (thrust > 0) then itemp = thrust; else itemp = -thrust;
		fuel -= (int) (itemp * fuel_rate);
		inverse_mass = compute_mass();
	    }

if (!hud && LK_DISABLE) {
	editobj (SLOW_METERS);
	if (tick_counter & 1) {		/* only do this on odd ticks	*/
	    objreplace (TEXT_EDIT);
	    sprintf (charbuf,"%d",airspeed);
	    cmov2s (SPEED_LLX+8,METER_LLY+5);
	    charstr (charbuf);

	    sprintf (charbuf,"%d",(climbspeed << 6) - (climbspeed << 2));
	    cmov2s (CLIMB_LLX+3,METER_LLY+5);	/* (x*64) - (x*4) */
	    charstr (charbuf);
	    objreplace (GY_EDIT);		/* +- 8 G's		*/
	    translate(366.0,-100.0/8.0/GRAVITY * lift,0.0);
	}
	objreplace (HEADING_ROTATE_EDIT);
	rotate (-azimuth,'z');
	closeobj ();

	draw_meter (THRUST_LLX,thrust);		/* thrust meter		*/
	draw_meter (SPEED_LLX,airspeed/10);	/* speed meter		*/
	draw_meter (CLIMB_LLX,(climbspeed>>1)+(climbspeed>>3));/* 1/2 + 1/8 */
	callobj (SLOW_METERS);			/* display the text	*/

	if (tick_counter <= 1) {	/* draw fuel on frames 1,0	*/
	    callobj (CLEAR_FUEL_METER);
	    draw_meter (FUEL_LLX,fuel >> 7);	/* fuel meter		*/
	}

	editobj (HORIZON_METER);		/* horizon meter - last	*/
	objreplace (HORIZON_EDIT);
	    rotate (-twist,'z');
	    translate (0.0,-.1 * elevation,0.0);
	closeobj ();
	callobj (HORIZON_METER);		/* resets writemask	*/
	if (g_limit) then callobj (G_LIMIT);
	else if (wing_stall) callobj (WING_STALL);
	if (autopilot) then callobj (AUTO_PILOT);
	if (pp -> status <= MEXPLODE) then callobj (CRASH_METERS);
}	/* end of !hud	*/

	/****************************************************************
	 *	display TEXT readouts
	 ****************************************************************/
	if (tick_counter == 0 && LK_DISABLE) {	/* only update them every second */
	    tick_counter = TPS;		/* reset tick counter		*/
if (!hud) {
	    cursoff ();
	    frontbuffer (TRUE);
	    callobj (CLEAR_TEXT_DISPLAY);
	    if (flaps) {
		if (airspeed > 400-flaps)
		then strcpy (charbuf,"Flaps torn off");
		else sprintf (charbuf,"Flaps: %2d degrees",flaps);
		cmov2s (100,310);
		charstr (charbuf);
	    }
	    if (spoilers > 0) {
		cmov2s (280,310);
		sprintf (charbuf,"Spoilers: %d degrees",spoilers);
		charstr (charbuf);
	    }

	    cmov2s (100,330);
	    if (wheels) {
		if (airspeed > 400)	/* if airspeed > 400 knots	*/
		then charstr ("LANDING GEAR TORN OFF");
		else charstr ("LANDING GEAR DOWN");
	    }
	    if (pp -> mstatus) {
		cmov2s (310,330);
		if (pp -> mkill != NULL_PLANE_ID) {
		    ptemp = lookup_plane (pp -> mkill);
		    if (ptemp) {
			sprintf (charbuf,"DESTROYED -> %s",ptemp->myname);
			charstr (charbuf);
		    }
		}
		else if (pp -> mtype == TYPE_CANNON)
		then charstr ("20mm Cannon Fired");
		else if (pp -> mtype == TYPE_ROCKET)
		then charstr ("Rocket Launched");
		else {
		    ptemp = lookup_plane (missile_target);
		    if (ptemp == NULL)
		    then charstr ("Sidewinder Launched");
		    else {
			sprintf (charbuf,"Sidewinder -> %s",ptemp->myname);
			charstr (charbuf);
		    }
		}
	    }
	    /* check for a locked on target	*/
	    else if (missile_target != NULL_PLANE_ID) {
		cmov2s (310,330);
		ptemp = lookup_plane (missile_target);
		if (ptemp != NULL) {
		    sprintf (charbuf,"Locked on -> %s",ptemp->myname);
		    charstr (charbuf);
		}
	    }
	    cmov2s (492,310);
	    charstr (status_text);

	    sprintf (charbuf,"Altitude: %d  Won:%d  Lost:%d",
			(int)pp -> y, pp -> won, pp -> lost);
	    cmov2s (612,330);
	    charstr (charbuf);
	    frontbuffer (FALSE);
	    curson ();
}	/* end of not hud	*/
	    if (flaps && airspeed > 400-flaps) {	/* rip off flaps */
		for (itemp=flaps; itemp>0; itemp-=10) qenter (KEYBD,'F');
		Fmax = 0;
	    }
	    if (wheels && airspeed > 400) { /* if airspeed > 400 knots	*/
		qenter (KEYBD,'l');		/* rip off the gear	*/
		landing_gear_stuck = 0;
	    }

	    /*
	     *  calculate the current tps (ticks per second)
	     */
	    time_end = times (&tms_end_buf);
	    calculate_time ("main loop");
	    time_start = times (&tms_start_buf);

	    tick_counter = int_tps;
#ifndef _4D
	    fps_knots = tps * (3600.0/6082.0);
	    gravity = G_ACC / tps / tps;
#endif
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

#ifdef _4D
	tps += tps_add;
	fps_knots = tps * (3600.0/6082.0);
	gravity = G_ACC / tps / tps;
#endif

	swapbuffers ();
    }

end_of_program:
    ExitComm ();

    exit (0);
}

addplane ()
{
    number_planes++;
    rebuild_status ();
}

delplane ()
{
    number_planes--;
    rebuild_status ();
    return (number_planes);
}

rebuild_status ()
{
    sprintf (status_text,"%s   Rockets:%d  Sidewinders:%d  Players:%d",
		plane_type, rockets, sidewinders, number_planes);
}

float fuel_consump (thrust,half_mass)
    float thrust,half_mass;
{
    return (test_mode ? 0.0 : 0.3 * thrust/half_mass);
}


#define dy 14
#ifdef _4D
#define CLOCKRATE HZ
#else
#define CLOCKRATE 60
#endif

void
calculate_time (name)
    char *name;
{
    int y,s60;
    char charbuf[80];
    float veldiff;
    int current_tps;

    s60 = time_end - time_start;
    if (s60 <= 0) then s60 = (tms_end_buf.tms_utime-tms_start_buf.tms_utime) +
			(tms_end_buf.tms_stime-tms_start_buf.tms_stime);
    if (s60 == 0) then s60 = 1;

    current_tps = int_tps * CLOCKRATE / s60;
	if(current_tps < MINTPS)
		current_tps = MINTPS;	/* probably on an Eclipse w/o floating point.
			It seems unbearably slow below 10.  Typically 15-30 on a lightly
			loaded 12Mhz IP4 and 12-20 on an Eclipse with floating point.
			Olson, 9/88 */

    if (timeit)				/* display the timeing info */
    {
	if (hud)
	    makeobj (CLEAR_TEXT_DISPLAY);
	else
	{
	    cursoff ();
	    frontbuffer (TRUE);
	    callobj (CLEAR_REPORT_CARD);	/* just in case, also set up */
	}
	color(white);
	y = METER_LLY - 40 - dy;

	sprintf (charbuf,"Times for %s:",name);
	cmov2s (150, y);
	charstr (charbuf);

	sprintf (charbuf, "    %d in %d.%02d seconds",
		 int_tps, s60/CLOCKRATE, (s60%CLOCKRATE)*1000/CLOCKRATE/10);
	cmov2s (150, y-dy);
	charstr (charbuf);

	sprintf (charbuf, "    %d msecs per call", s60*1000/CLOCKRATE/int_tps);
	cmov2s (150, y-2*dy);
	charstr (charbuf);

	sprintf (charbuf, "    %d per second", current_tps);
	cmov2s (150, y-3*dy);
	charstr (charbuf);

	if (hud) 
	    closeobj();
	else
	{
	    frontbuffer (FALSE);
	    curson ();
	}
    }

    tps = int_tps;

    if (current_tps == int_tps)
    {
#ifdef _4D
        tps_add = 
#endif
	vx_add = vy_add = vz_add = 
	missile_vx_add = missile_vy_add = missile_vz_add = 0.0;
	return;
    }
    else if (current_tps > int_tps)
    {
	veldiff = int_tps / (float)(int_tps+1);
	int_tps++;
#ifdef _4D
        tps_add = 1.0 / int_tps;
#endif
    }
    else /* (current_tps < int_tps) */
    {
	veldiff = int_tps / (float)(int_tps-1);
	int_tps--;
#ifdef _4D
        tps_add = -1.0 / int_tps;
#endif
    }

    vx_add = ((vx * veldiff) - vx) / int_tps;
    vy_add = ((vy * veldiff) - vy) / int_tps;
    vz_add = ((vz * veldiff) - vz) / int_tps;
    missile_vx_add = ((missile_vx * veldiff) - missile_vx) / int_tps;
    missile_vy_add = ((missile_vy * veldiff) - missile_vy) / int_tps;
    missile_vz_add = ((missile_vz * veldiff) - missile_vz) / int_tps;
}


#ifndef DOGFIGHT
broadcast () {}

draw_messages () {}

Plane lookup_plane() {return(NULL);}

ExitComm () {
    replacecolors();
    greset ();
    color (BLACK);
    clear ();
}
#endif

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
	if (value <= -10){
		setvaluator(DIAL0,200,0,400);
		for (i = 0 ; i >= (value/10) ; i--)
			qenter(KEYBD,'a');
	}
	if (value >= 10){
		setvaluator(DIAL0,200,0,400);
		for (i = 0 ; i <= (value/10) ; i++)
			qenter(KEYBD,'s');
	}

	/* Check for flaps */
	value = getvaluator(DIAL1) - 50;
	if (value <= -10){
		setvaluator(DIAL1,50,0,100);
		for (i = 0 ; i >= (value/10) ; i--)
			qenter(KEYBD,'F');
	}
	if (value >= 10){
		setvaluator(DIAL1,50,0,100);
		for (i = 0 ; i <= (value/10) ; i++)
			qenter(KEYBD,'f');
	}

	/* Check the spoilers */
	value = getvaluator(DIAL2) - 30;
	if (value <= -10){
		setvaluator(DIAL2,30,0,60);
		for (i = 0 ; i >= (value/10) ; i--)
			qenter(KEYBD,'C');
	}
	if (value >= 10){
		setvaluator(DIAL2,30,0,60);
		for (i = 0 ; i <= (value/10) ; i++)
			qenter(KEYBD,'c');
	}

	/* Check the tower view */
	value = getvaluator(DIAL4) - 240;
	if (value <= -10){
		setvaluator(DIAL4,240,0,480);
		for (i = 0 ; i >= (value/10) ; i--)
			qenter(KEYBD,'z');
	}
	if (value >= 10){
		setvaluator(DIAL4,240,0,480);
		for (i = 0 ; i <= (value/10) ; i++)
			qenter(KEYBD,'x');
	}
}

init_dials()
/* Initialize the dials to the correct values */
{
	setvaluator(DIAL0,200,0,400);
	setvaluator(DIAL1,50,0,100);
	setvaluator(DIAL2,30,0,60);
	setvaluator(DIAL4,240,0,480);
}


extern int make_c150(), make_b747(), make_f15(), make_f16(), make_f18(),
	make_p38(), make_f16w(), make_p38w();

struct mkplns {
	int (*func)();
	Object arg;
} mk_plns[] = {
	{ make_c150, C150 },
	{ make_b747, B747 },
	{ make_f15, F15 },
	{ make_f16, F16 },
	{ make_f18, F18 },
	{ make_p38, P38 },
	{ make_f16w, F16W },
	{ make_p38w, P38W },
	{ NULL, 0 }
};


/*	Making the planes typically takes ~15 seconds on a lightly loaded
	Eclipse w/o floating point!  only a second or two with floating
	point.  So make them while waiting for a key stroke if chkkey set,
	otherwise make them all.  Might want to optimize later to make
	only the needed plane(s).
	Olson, 9/88
*/
make_planes(chkkey)
{
	static int which = 0, type;

	while((!chkkey || (type=qtest()) != KEYBD) &&
		mk_plns[which].func != NULL) {
		(*mk_plns[which].func)(mk_plns[which].arg);
		which++;
	}
	return (type == KEYBD);
}

stopit()
{
	int mousex, mousey;

	/* do most of same stuff as when we exit in ExitComm() */
    replacecolors();
	mousex = getvaluator(MOUSEX);	/* save mouse position */
	mousey = getvaluator(MOUSEY);

	/* greset(); */

	/* flipiconic(winget()); */

	/* clear the overlay, underlay, and cursor planes */
	drawmode(OVERDRAW);
	color(BLACK);
	clear();
	drawmode(UNDERDRAW);
	color(BLACK);
	clear();
	drawmode(CURSORDRAW);
	color(BLACK);
	clear();
	drawmode(NORMALDRAW);

#ifdef DOGFIGHT
    init_graphics ("dog");
#else
    init_graphics ("flight");
#endif
    if (dials) init_dials(); 
    make_meters ();
	map_daynight (daytime);

	/* restore mouse position */
	setvaluator(MOUSEX, mousex, 0,XMAXSCREEN);
	setvaluator(MOUSEY, mousey, 0,YMAXSCREEN);

	/* re-calculate the current tps (ticks per second) */
	time_end = times (&tms_end_buf);
	calculate_time ("main loop");
	time_start = times (&tms_start_buf);
	winpop();	/* make sure at top! */
    redraw_screen ();
}
