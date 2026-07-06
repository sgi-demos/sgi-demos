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
 *  flight/flight.h $Revision: 1.1 $
 */

#ifndef __FLIGHT_H__
#define __FLIGHT_H__

#include <gl.h>
#include <device.h>
#include <math.h>
#include <stdio.h>

#include "gobj.h"
#include "colors.h"
#include "objects.h"
#include "collision.h"
#include "Xzmsg.h"

#ifdef AUDIO
#include "sound.h"
#endif

/* order of gobj.h and colors.h is important */

/* Color map thing */
#define DEFAULT_BIT_CMODE 4

#define DATADIR "/usr/demos/data/flight/"

#define START_X 850.0
#define START_Y 0.0
#define START_Z -2050.0
#define START_AZIMUTH 900

#define HEADER_VERSION HEADER(3.4)
#define VERSION_NUMBER 3.4

#ifndef NULL
#define NULL 0
#endif

#define IN_BOX(p, llx, urx, llz, urz) \
	(llx <= p->x && p->x <= urx && llz <= p->z && p->z <= urz)

#define DOT(A, B) (A[0]*B[0] + A[1]*B[1] + A[2]*B[2])

extern int xasin();
extern void set_text_meter(int lnum, char *text, int timeout);	/* added: wasm needs the void return visible at call sites */

#define MAX_PLANES 16
#define NAME_LENGTH 15

struct plane {
    long planeid;

    char  version;		/* flight version	*/
    char  cmd;			/* type of packet	*/
    short type;			/* plane type		*/
    short alive;		/* is this plane still sending packets */
    char  myname[NAME_LENGTH+1];

    unsigned short status;
    unsigned short won;		/* for msgs these 2 shorts */
    unsigned short lost;	/* hold the plane id	*/

    float x;			/* plane position	*/
    float y;			/* in feet		*/
    float z;
    short azimuth;		/* in 10th of degrees	*/
    short elevation;
    short twist;

    short mstatus;		/* missile data		*/
    float mx;
    float my;
    float mz;
    float last_mx;
    float last_my;
    float last_mz;
    long mkill;
    float tps;			/* ticks per second	*/
    int airspeed;		/* air speed in knots	*/
    int thrust;			/* 0-100 percent	*/
    short wheels;		/* wheel position	*/
    short elevator;		/* elevator position	*/
    char mtype;			/* missile type		*/
    unsigned char weapon_state;	/* weapon state bits	*/
    short rollers;		/* rollers position	*/
};


#define RADAR_HISTORY 16*20

typedef struct {
    long id;
    int n;
    int velocity;		/* overall velocity		*/
    float vx, vy, vz;		/* plane velocity in user space	*/
    char buf[80];		/* text buffer			*/
    int status[RADAR_HISTORY];
    float x[RADAR_HISTORY];
    float y[RADAR_HISTORY];
    float z[RADAR_HISTORY];
} radar_hist_t;

extern radar_hist_t radar_history[];

#define NUM_BUILDINGS 5

#define MAX_OBJS	20	/* maximum number of objects */
/*
 *  object types
 */
#define BUILDING_OBJ	0
#define THREAT_OBJ	1
#define HILL_OBJ	2
#define PLANE_OBJ	3
#define MISSILE_OBJ	4

typedef struct {
    int type;
    float cx;
    float cy;
    float cz;
    int mode;
    int id;
    object_t *obj;
} obj_list_t;

extern obj_list_t sort_obj[MAX_OBJS];
extern obj_list_t sort_plane[MAX_PLANES];
extern obj_list_t sort_missile[MAX_PLANES];
extern int obj_count;


typedef struct plane *Plane;
extern Plane planes[], get_indata(), lookup_plane(), find_closest_plane();
extern Plane plane_futures[];
extern Plane *find_plane();
extern int number_planes;	/* number of planes in game */


#define DATA_PACKET 0
#define MSG_PACKET 1
#define SUPERKILL_PACKET 2
#define KILL_PACKET 23


/*
 *  plane history data
 */
#define MT_MAX	30
struct plane_hist {
    int malive;
    float mt[MT_MAX][3];		/* missile track */
    int mtpos, mtspos, mtlen;
};

typedef struct plane_hist *Plane_hist;
extern Plane_hist plane_hists[];

/*
 *  macros for accessing plane data
 */
#define FOR_EACH_MSG(p,pp) \
	for (pp = messages, p = *pp++; p->alive > 0; p = *pp++)

#define FOR_EACH_PLANE(p,pp) \
	for (pp = planes, p = *pp++; p->alive > 0; p = *pp++)

#define FOR_EACH_PLANE_I(i, p) \
	for (i = !shadow, p = planes[i]; p->alive > 0; p = planes[++i])

#define FOR_EACH_PLANE_AND_FUTURE(p,pp,pf,ppf) \
	for (pp = (shadow)? planes : &planes[1], p = *pp++, \
	     ppf = (shadow)? plane_futures : &plane_futures[1], pf = *ppf++; \
	     p->alive > 0; p = *pp++, pf = *ppf++)

#define FOR_EACH_PLANE_AND_HIST(p,pp,ph,pph) \
	for (pp = planes, p = *pp++, pph = plane_hists, ph = *pph++; \
	     p->alive > 0; p = *pp++, ph = *pph++)

#define PLANE_ID(p) ((p)->planeid)
#define NULL_PLANE_ID -1


/*
 *  weapon types
 */
#define TYPE_ROCKET 0
#define TYPE_SIDEWINDER 1
#define TYPE_CANNON 2
#define TYPE_SAM 3

/*
 *  patterns
 */
#define CRASH_PATTERN 1
#define SHADOW_PATTERN 2
#define EXPL_PAT0 80

#define TPS tps
/*#define TPS 20*/
#define G_ACC 32.0
/*#define GRAVITY (G_ACC/TPS/TPS)*/
#define GRAVITY gravity

/*
 *  plane status
 */
/* hard code it to 20 to be compatable with GL1 versions
#define MEXPLODE (2 * TPS)	*/
#define MEXPLODE 20
#define MFINISH (MEXPLODE + 1)
#define MLIFE (10 * int_tps)
#define MSTART (MFINISH + MLIFE)

/*
 *  some meter screen coordinates
 */
#define METER_VLLX 62
#define METER_VURX 1225
#define METER_VLLY 133
#define METER_VURY 400
#define THRUST_LLX 62
#define SPEED_LLX (THRUST_LLX*3)
#define CLIMB_LLX (THRUST_LLX*5)
#define HEADING_CX 937
#define FUEL_LLX 1163
#define HUD_MARGIN 250

/*
 *  timing info
 */
extern int int_tps;				/* integer ticks per second */
extern float tps;				/* ticks per second */
extern short tick_counter;			/* counts the loop ticks */
extern struct tms tms_start_buf, tms_end_buf;	/* timer buffer */
extern int time_start, time_end;		/* start/end times */

/*
 *  screen and window info
 */
extern int xorigin, yorigin;
extern int xmaxscreen, ymaxscreen;
extern int xmaxwindow, ymaxwindow;
extern int xmiddle, ymiddle;
extern int zminscreen, zmaxscreen;
extern int inst_x1, inst_x2, inst_y1, inst_y2;
extern int report_x1, report_x2, report_y1, report_y2;

/*
 *  display state info
 */
extern int plate_ci_mode;
extern int in_cmode;
extern int force_cmode;
extern int force_rgb;
extern int bits_cmode;
extern int bits_over;
extern int bits_under;
extern long over_drawmode;	/* OVERDRAW or PUPDRAW */
extern int ms_samples;


/*
 *  mouse and spaceball positions
 */
extern long mousex, mousey, sbtx, sbtz;

extern char status_text[60];

extern float gravity;

extern int ftime;		/* time of day in flight in minutes */

extern float sunx, suny, sunz;	/* position of sun */
extern int lightson;

extern int fogon;
extern int texon;

extern Matrix identmat;

extern int restart;

/*
 *  flags
 */
extern short debug;			/* TRUE if in debug mode */
extern short dogfight;			/* TRUE if dogfight */
extern short shadow;			/* TRUE if shadow */
extern short radar;			/* TRUE if radar */
extern short hud;			/* TRUE if hud, else meters */
extern short threat_mode;		/* TRUE if threats envelopes */
extern short timeit;			/* TRUE if displaying timing info */
extern short test_mode;			/* test mode uses no fuel */
extern short dials;			/* TRUE if using dials */
extern short new_inst;			/* TRUE if using new instroments */
extern short show_help;			/* TRUE if displaying help */


/*
 *  geomety objects
 */
extern object_t *runwayobj;
extern object_t *lightsobj;
extern object_t *hillsobj;
extern object_t *mtnsobj;
extern object_t *buildingsobj;
extern object_t *planeobj[9];
extern object_t *swobj;
extern object_t *threatobj;
extern object_t *planeboxobj;
extern char datadir[];
extern char sounddir[];
extern char objdir[];
extern char objfname[];
extern grid_t *hillsgrid;


/*
 *  plane design parameters
 */
extern char *plane_type;		/* plane type (i.e. "F-15") */
extern float s;				/* wing area in sq. feet */
extern float W;				/* weight of plane in lbs. */
extern float fuel_weight;		/* weight of fuel */
extern float Mthrust;			/* maximum thrust */
extern float b;				/* wing span in feet */
extern float ef;			/* efficiency factor */
extern float Fmax;			/* maximum flap deflection */
extern float Smax;			/* maximum spoiler deflection */
extern float ELEVF;			/* elevator rate in degrees/sec */
extern float ROLLF;			/* roll rate (both at 300 mph) */
extern float pilot_eye[4];		/* pilots eye position */
extern float Lmax;			/* maximum lift before wing breaks */
extern float Lmin;			/* minimum lift before wing breaks */
extern float plane_height;		/* height of plane midpoint */
extern int MAX_RK, MAX_SW;		/* max rockets and sidewinders */
extern int MIN_LIFT_SPEED;		/* minimum lift-up speed fps */

/*
 *  computed plane design parameters
 */
extern float gefy;			/* maximum height for ground effect */
extern float fuel_rate;			/* fuel consumption rate */
extern float ipi_AR;			/* 1.0 / pi * wing Aspect Ratio */
extern float ie_pi_AR;			/* 1.0 / pi * AR * efficiency */

/*
 *  variable plane design parameters
 */
extern float inverse_mass;		/* 1.0 / mass of plane */
extern float Lmax_g;			/* Lmax * gravity */
extern float Lmin_g;			/* Lmin * gravity */

/*
 *  plane state
 */
extern Matrix ptw;			/* my ptw matrix */
extern float (*my_ptw)[4];		/* pointer to my matrix	*/
extern int sidewinders, rockets;	/* number of armaments		*/
extern float rudder, elevator, rollers;	/* control settings		*/
extern float vx, vy, vz;		/* plane velocity */
extern int twist, elevation, azimuth;	/* plane orientation		*/
extern int roll_speed;			/* roll, elevation, azimuth speeds */
extern int elevation_speed;		/* in 10'ths degrees per tick	*/
extern int azimuth_speed;
extern int flaps, spoilers;		/* flap and spoiler settings	*/
extern float lift;			/* lift acceleration		*/
extern int airspeed, last_airspeed;
extern int climbspeed, last_climbspeed;
extern short g_limit;			/* TRUE if wing g-limit is hit	*/
extern short wing_stall;		/* TRUE if wing is stalling	*/
extern short on_ground;			/* TRUE if plane is on ground	*/
extern short wheels;			/* TRUE if the wheels are down	*/
extern short wheels_retracting;		/* used only			*/
extern short landing_gear_stuck;	/* >= 0 if the gear is stuck	*/
extern int fuel;			/* fuel (0 - 12800)		*/
extern int thrust;			/* thrust (0 - 100)		*/
extern int throttle;			/* throttle (0 - 100)		*/
extern int max_throttle;		/* upper limit on engines	*/
extern int min_throttle;		/* lower limit on engines	*/
extern float last_px, last_py, last_pz;	/* last plane position		*/
extern float max_cl, min_cl;		/* max and min coefficient of lift */
extern float tilt_factor;		/* wing angle tilt due to flaps	*/
extern float Splf, Spdf;		/* spoiler factors on lift and drag */
extern float mach;			/* mach #, crest critical #, ratio */
extern float Cdp;			/* coefficient of parasitic drag */

/*
 *  autopilot state
 */
extern short autopilot_on;		/* TRUE in autopilot mode */
extern int target_twist;		/* target twist for autopilot */
extern int target_speed;		/* target speed for autopilot */
extern int target_climb;		/* target climb for autopilot */


/*
 *  missile status
 */
extern long missile_target;		/* plane my missile is after */
extern float missile_vx,		/* missile velocity */
	     missile_vy,
	     missile_vz;
#define MT_MAX 30

/*
 *  wingman history
 */
extern int wm_twist[10];
extern int wm_elevation[10];
extern int wm_azimuth[10];
extern float wm_x[10], wm_y[10], wm_z[10];
extern int wmpos;
extern int wmspos;
extern int wmfollow;

/*
 *  view state
 */
extern short view_switch;
#define PLANE_VIEW 1
#define TOWER_VIEW 2
extern int wingman_view;
extern int missile_view;
extern int fov;				/* field of view */
extern int plane_fov, tower_fov;	/* plane, tower field of view */
extern float ar;			/* aspect rationo */
extern long dist_for_lines;		/* distance to draw building lines */
extern int view_angle;			/* rotation of pilot's head */
extern int fogit;
extern int texit;
extern float eye_x, eye_y, eye_z;	/* eye position */
extern float current_eye[4];		/* current eye position */

#define TOWER_X -1950.0
#define TOWER_Y   400.0
#define TOWER_Z -3150.0
extern float frustum[4][4];
extern float clip_planes[4][4];


extern int fog_d;

/*
 *  airshow input/output file control
 */
extern char *infile, *outfile;
extern FILE *inf, *outf;
extern int read_pause;
extern int read_reset;
extern int read_backwards;
extern float read_speed;


#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)

#include "proto.h"

#endif /* __FLIGHT_H__ */
