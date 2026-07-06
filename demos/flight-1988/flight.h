/**************************************************************************
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

#include "gl.h"
#include "device.h"
#include "math.h"
#include "colors.h"
#include "objects.h"
/*#include <xns/Xzmsg.h>*/

#define START_X 850.0
#define START_Y 0.0
#define START_Z -2050.0
#define START_AZIMUTH 900

#define HEADER_VERSION HEADER(2.4)
#define then
#define NULL 0
#define IN_BOX(p,llx,urx,llz,urz) \
	(llx <= p -> x && p -> x <= urx && llz <= p -> z && p -> z <= urz)

extern short debug, bitplanes, dogfight, hud, threat_mode;
extern int xasin (), dist_for_lines;
extern float eye_x, eye_y, eye_z;
extern float (*my_ptw)[4];

#define MAX_PLANES 16
#define NAME_LENGTH 15

struct zmsg {
    int src[3];
};


struct plane {
    long planeid;

    char  version;		/* flight version	*/
    char  cmd;			/* type of packet	*/
    short type;			/* plane type		*/
    short alive;
    char  myname[NAME_LENGTH+1];

    unsigned short status;
    unsigned short won;		/* for msgs these 2 shorts */
    unsigned short lost;	/* hold the plane id	*/

    float x;			/* plane position	*/
    float y;
    float z;
    short azimuth;
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
    float tps;
    int airspeed;
    int thrust;
    short wheels;		/* wheel position 	*/
    short elevator;		/* elevator position 	*/
    char mtype;
    char place_holder;		/* XXX use later	*/
    short rollers;		/* rollers position 	*/
};

typedef struct plane *Plane;
extern Plane planes[], get_indata(), lookup_plane(), find_closest_plane();
extern Plane *find_plane();

#define DATA_PACKET 0
#define MSG_PACKET 1
#define SUPERKILL_PACKET 2
#define KILL_PACKET 23

#define FOR_EACH_MSG(p,pp) for (pp=messages,p= *pp++; p->alive > 0; p = *pp++)
#define FOR_EACH_PLANE(p,pp) for (pp=planes,p= *pp++; p->alive > 0; p = *pp++)
/*#define PLANE_ID(p) (*(long *) &((p) -> header.src[2]))*/
#define PLANE_ID(p) ((p)->planeid)
#define NULL_PLANE_ID -1

#define TYPE_ROCKET 0
#define TYPE_SIDEWINDER 1
#define TYPE_CANNON 2

/*
 *  ticks per second (frames drawn per second)
 */
#ifdef _4D
extern int int_tps;
extern float tps;
#else
#define int_tps tps
extern int tps;
#endif

#define TPS tps
/*#define TPS 20*/

#define G_ACC 32.0
#define GRAVITY gravity
/*#define GRAVITY (G_ACC/TPS/TPS)*/

/* hard code it to 20 to be compatable with GL1 versions
#define MEXPLODE (2 * TPS)	*/
#define MEXPLODE 20
#define MFINISH (MEXPLODE + 1)
#define MLIFE (10 * int_tps)
#define MSTART (MFINISH + MLIFE)

/* define NTSC if you want flight to run on NTSC monitors	*/
/* some meter screen coordinates	*/
#ifdef NTSC
#undef XMAXSCREEN
#undef YMAXSCREEN
#define XMAXSCREEN 618
#define YMAXSCREEN 465

#define XMIDDLE 300
#define YMIDDLE 230
#define METER_VLLX 30
#define METER_VURX 600
#define METER_VLLY 70
#define METER_VURY 190

#else
#define XMIDDLE XMAXSCREEN/2
#define YMIDDLE YMAXSCREEN/2
#define METER_VLLX 50
#define METER_VURX 930
#define METER_VLLY 100
#define METER_VURY 300
#endif
#define FUEL_VLLX (METER_VURX-METER_VLLX)

#define METER_LLY 100
#define METER_URY 300
#define THRUST_LLX 50
#define HEADING_CX 750
#define SPEED_LLX (THRUST_LLX*3)
#define CLIMB_LLX (THRUST_LLX*5)
#define FUEL_LLX 880
#define HUD_MARGIN 250
