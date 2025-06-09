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

/* contains plane definitions	*/
#include "flight.h"

/************************************************************
/*	F-18 plane definition
/************************************************************/
static float fakewing[][3] = {
    {0,0,-38},
    {20,0,12},
    {-20,0,12},
};
static float fakestab[][3] = {
    {0,0,0},
    {0,10,12},
    {0,0,12}
};
static float rightfire[][3] = {
    {1.0,1.5,16.0},
    {1.6,2.25,16.0},
    {2.4,2.25,16.0},
    {3.0,1.5,16.0},
    {2.4,.75,16.0},
    {1.6,.75,16.0},
};
static float leftfire[][3] = {
    {-1.0,1.5,16.0},
    {-1.6,2.25,16.0},
    {-2.4,2.25,16.0},
    {-3.0,1.5,16.0},
    {-2.4,.75,16.0},
    {-1.6,.75,16.0},
};

static float rightwing[][3] = {
    {4,3,-8},
    {20,3,-1},
    {20,3,4},
    {4,3,5},
};
static float leftwing[][3] = {
    {-4,3,-8},
    {-20,3,-1},
    {-20,3,4},
    {-4,3,5},
};
static float rightchine[][3] = {
    {1.5,3,-22},
    {4,3,-11},
    {4,3,-8},
    {1.5,3,-8},
};
static float leftchine[][3] = {
    {-1.5,3,-22},
    {-4,3,-11},
    {-4,3,-8},
    {-1.5,3,-8},
};

static float rightrudder[][3] = {
    {3,3,2},
    {6,10,8},
    {6,10,12},
    {3,3,11},
};
static float leftrudder[][3] = {
    {-3,3,2},
    {-6,10,8},
    {-6,10,12},
    {-3,3,11},
};

static float rightelevator[][3] = {
    {4,2,8},
    {11,2,15},
    {11,2,17},
    {10,2,18},
    {4,2,15},
};
static float leftelevator[][3] = {
    {-4,2,8},
    {-11,2,15},
    {-11,2,17},
    {-10,2,18},
    {-4,2,15},
};

static float topback[][3] = {
    {-4,3,-8},
    {4,3,-8},
    {4,3,16},
    {-4,3,16},
};
static float rightback[][3] = {
    {4,3,-8},
    {4,3,16},
    {4,0,16},
    {4,0,-8},
};
static float leftback[][3] = {
    {-4,3,-8},
    {-4,3,16},
    {-4,0,16},
    {-4,0,-8},
};
static float bottomback[][3] = {
    {-4,0,-8},
    {4,0,-8},
    {4,0,16},
    {-4,0,16},
};
static float backback[][3] = {
    {-4,3,16},
    {4,3,16},
    {4,0,16},
    {-4,0,16},
};
static float frontback[][3] = {
    {-4,3,-8},
    {4,3,-8},
    {4,0,-8},
    {-4,0,-8},
};

static float bottomfront[][3] = {
    {1.5,0,-32},
    {1.5,0,-8},
    {-1.5,0,-8},
    {-1.5,0,-32},
};
static float rightfront[][3] = {
    {1.5,0,-32},
    {1.5,0,-8},
    {1.5,4.7272,-8},
    {1.5,5,-14},
    {1.5,2.2,-32},
};
static float leftfront[][3] = {
    {-1.5,0,-32},
    {-1.5,0,-8},
    {-1.5,4.7272,-8},
    {-1.5,5,-14},
    {-1.5,2.2,-32},
};
static float rightnose[][3] = {
    {0,.6,-38},
    {1.5,0,-32},
    {1.5,2.2,-32},
};
static float leftnose[][3] = {
    {0,.6,-38},
    {-1.5,0,-32},
    {-1.5,2.2,-32},
};
static float topnose[][3] = {
    {0,.6,-38},
    {1.5,2.2,-32},
    {-1.5,2.2,-32},
};
static float botnose[][3] = {
    {0,.6,-38},
    {1.5,0,-32},
    {-1.5,0,-32},
};
static float frontbubble[][3] = {
    {-1.5,2.2,-32},
    {-1.5,5,-14},
    {1.5,5,-14},
    {1.5,2.2,-32},
};
static float topbubble[][3] = {
    {-1.5,5,-14},
    {-1.5,4.7272,-8},
    {0,3,8},
    {1.5,4.7272,-8},
    {1.5,5,-14},
};
static float rightbubble[][3] = {
    {1.5,4.7272,-8},
    {0,3,8},
    {1.5,3,-8},
};
static float leftbubble[][3] = {
    {-1.5,4.7272,-8},
    {0,3,8},
    {-1.5,3,-8},
};
static float pit1[][3] = {
    {0,3.14,-26},
    {1.5,4,-21},
    {0,6,-21},
};
static float pit2[][3] = {
    {0,3.14,-26},
    {-1.5,4,-21},
    {0,6,-21},
};
static float pit3[][3] = {
    {0,5,-14},
    {1.5,4,-21},
    {0,6,-21},
};
static float pit4[][3] = {
    {0,5,-14},
    {-1.5,4,-21},
    {0,6,-21},
};

#define C_TOPNOSE silver4
#define C_LEFTNOSE silver6
#define C_TOPBUBBLE silver1
#define C_FRONTBUBBLE silver3
#define C_TOPBACK silver2
#define C_RIGHTRUDDER silver3
#define C_LEFTRUDDER silver4
#define C_PIT1 silver6
#define C_PIT2 silver7
#define C_PIT3 silver8
#define C_PIT4 silver9
#define C_UNDERWING silver8
#define C_UNDERBODY silver9

make_f18 (obj)
    register Object obj;
{
    makeobj (obj++);	/* below, left, front	*/
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    color (red);
	    pnts (5,8,12);
	color (silver6);
	polf (3,leftbubble);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    color (white);
	    pnts (-5,8,12);

	color (C_UNDERWING);
	polf (5,rightelevator);
	polf (4,rightwing);
	    moves (20,3,4);
	    draws (20,3,-5);
	polf (4,leftwing);
	    moves (-20,3,4);
	    draws (-20,3,-5);
	    color (green0);
	    pnts (19,3,-1);
	    color (red);
	    pnts (-19,3,-1);
	color (brown);
	polf (4,frontback);
	color (C_LEFTNOSE);
	polf (3,rightnose);
	polf (4,leftback);
	color (C_UNDERWING);
	polf (5,leftelevator);

 	polf (4,rightchine);
	color (C_FRONTBUBBLE);
	polf (4,frontbubble);
	color (C_PIT4);
	polf (3,pit4);
	color (C_PIT1);
	polf (3,pit1);
	color (C_PIT2);
	polf (3,pit2);
	color (silver5);
	polf (5,leftfront);
	color (C_UNDERWING);
 	polf (4,leftchine);

	color (C_TOPNOSE);
	polf (3,topnose);
	color (C_LEFTNOSE);
	polf (3,leftnose);

	color (C_UNDERBODY);
	polf (4,bottomback);
	polf (4,bottomfront);
	polf (3,botnose);
    closeobj ();

    makeobj (obj++);	/* below, right, front	*/
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    color (white);
	    pnts (-5,8,12);
	color (silver6);
	polf (3,rightbubble);
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    color (red);
	    pnts (5,8,12);

	color (C_UNDERWING);
	polf (5,leftelevator);
	polf (4,leftwing);
	    moves (-20,3,4);
	    draws (-20,3,-5);
	polf (4,rightwing);
	    moves (20,3,4);
	    draws (20,3,-5);
	    color (red);
	    pnts (-19,3,-1);
	    color (green0);
	    pnts (19,3,-1);
	color (brown);
	polf (4,frontback);
	color (C_LEFTNOSE);
	polf (3,leftnose);
	polf (4,rightback);
	color (C_UNDERWING);
	polf (5,rightelevator);

 	polf (4,leftchine);
	color (C_FRONTBUBBLE);
	polf (4,frontbubble);
	color (C_PIT3);
	polf (3,pit3);
	color (C_PIT2);
	polf (3,pit2);
	color (C_PIT1);
	polf (3,pit1);
	color (silver5);
	polf (5,rightfront);
	color (C_UNDERWING);
 	polf (4,rightchine);

	color (C_TOPNOSE);
	polf (3,topnose);
	color (C_LEFTNOSE);
	polf (3,rightnose);

	color (C_UNDERBODY);
	polf (4,bottomback);
	polf (4,bottomfront);
	polf (3,botnose);
    closeobj ();

    makeobj (obj++);	/* above, left, front	*/
	color (silver0);
	polf (5,rightelevator);
	polf (4,rightwing);
	    moves (20,3,4);
	    draws (20,3,-5);
	    color (green0);
	    pnts (19,3,-1);
	color (brown);
	polf (4,frontback);
	color (C_LEFTNOSE);
	polf (4,leftback);
	color (silver0);
	polf (5,leftelevator);
	polf (4,leftwing);
	    moves (-20,3,4);
	    draws (-20,3,-5);
	    color (red);
	    pnts (-19,3,-1);
	color (C_TOPBACK);
	polf (4,topback);

	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    color (red);
	    pnts (5,8,12);
	color (silver2);
 	polf (4,rightchine);
	color (C_TOPBUBBLE);
	polf (5,topbubble);
	color (silver6);
	polf (3,leftbubble);

	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    color (white);
	    pnts (-5,8,12);
	color (silver5);
	polf (5,leftfront);
	color (silver2);
 	polf (4,leftchine);

	color (C_FRONTBUBBLE);
	polf (4,frontbubble);
	color (C_PIT3);
	polf (3,pit3);
	color (C_PIT4);
	polf (3,pit4);
	color (C_PIT1);
	polf (3,pit1);
	color (C_PIT2);
	polf (3,pit2);

	color (C_UNDERBODY);
	polf (3,botnose);
	color (C_LEFTNOSE);
	polf (3,rightnose);
	polf (3,leftnose);
	color (C_TOPNOSE);
	polf (3,topnose);
    closeobj ();

    makeobj (obj++);	/* above, right, front	*/
	color (silver0);
	polf (5,leftelevator);
	polf (4,leftwing);
	    moves (-20,3,4);
	    draws (-20,3,-5);
	    color (red);
	    pnts (-19,3,-1);
	color (brown);
	polf (4,frontback);
	color (C_LEFTNOSE);
	polf (4,rightback);
	color (silver0);
	polf (5,rightelevator);
	polf (4,rightwing);
	    moves (20,3,4);
	    draws (20,3,-5);
	    color (green0);
	    pnts (19,3,-1);

	color (C_TOPBACK);
	polf (4,topback);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    color (white);
	    pnts (-5,8,12);
	color (silver2);
 	polf (4,leftchine);
	color (C_TOPBUBBLE);
	polf (5,topbubble);
	color (silver6);
	polf (3,rightbubble);

	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    color (red);
	    pnts (5,8,12);
	color (silver5);
	polf (5,rightfront);
	color (silver2);
 	polf (4,rightchine);

	color (C_FRONTBUBBLE);
	polf (4,frontbubble);
	color (C_PIT4);
	polf (3,pit4);
	color (C_PIT3);
	polf (3,pit3);
	color (C_PIT2);
	polf (3,pit2);
	color (C_PIT1);
	polf (3,pit1);

	color (C_UNDERBODY);
	polf (3,botnose);
	color (C_LEFTNOSE);
	polf (3,leftnose);
	polf (3,rightnose);
	color (C_TOPNOSE);
	polf (3,topnose);
    closeobj ();

    makeobj (obj++);	/* below, left, behind	*/
	color (C_LEFTNOSE);
	polf (3,leftnose);
	color (C_PIT2);
	polf (3,pit2);
	color (C_PIT3);
	polf (3,pit3);
	color (C_PIT4);
	polf (3,pit4);

	color (C_UNDERWING);
 	polf (4,rightchine);
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    color (red);
	    pnts (5,8,12);
	color (C_TOPBUBBLE);
	polf (5,topbubble);
	color (silver6);
	polf (3,rightbubble);
	polf (3,leftbubble);

	color (silver5);
	polf (5,leftfront);
	color (C_UNDERWING);
 	polf (4,leftchine);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    color (white);
	    pnts (-5,8,12);

	color (C_UNDERWING);
	polf (5,rightelevator);
	polf (4,rightwing);
	    moves (20,3,4);
	    draws (20,3,-5);
	polf (4,leftwing);
	    moves (-20,3,4);
	    draws (-20,3,-5);
	    color (green0);
	    pnts (19,3,-1);
	    color (red);
	    pnts (-19,3,-1);

	color (C_LEFTNOSE);
	polf (4,leftback);
	color (C_UNDERWING);
	polf (5,leftelevator);

	color (C_UNDERBODY);
	polf (3,botnose);
	polf (4,bottomfront);
	polf (4,bottomback);
	color (brown);
	polf (4,backback);
	color (orange);
	polf (6,leftfire);
	polf (6,rightfire);
    closeobj ();

    makeobj (obj++);	/* below, right, behind	*/
	color (C_LEFTNOSE);
	polf (3,rightnose);
	color (C_PIT1);
	polf (3,pit1);
	color (C_PIT4);
	polf (3,pit4);
	color (C_PIT3);
	polf (3,pit3);

	color (C_UNDERWING);
 	polf (4,leftchine);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    color (white);
	    pnts (-5,8,12);
	color (C_TOPBUBBLE);
	polf (5,topbubble);
	color (silver6);
	polf (3,leftbubble);
	polf (3,rightbubble);

	color (silver5);
	polf (5,rightfront);
	color (C_UNDERWING);
 	polf (4,rightchine);
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    color (red);
	    pnts (5,8,12);

	color (C_UNDERWING);
	polf (5,leftelevator);
	polf (4,leftwing);
	    moves (-20,3,4);
	    draws (-20,3,-5);
	polf (4,rightwing);
	    moves (20,3,4);
	    draws (20,3,-5);
	    color (red);
	    pnts (-19,3,-1);
	    color (green0);
	    pnts (19,3,-1);

	color (C_LEFTNOSE);
	polf (4,rightback);
	color (C_UNDERWING);
	polf (5,rightelevator);

	color (C_UNDERBODY);
	polf (3,botnose);
	polf (4,bottomfront);
	polf (4,bottomback);
	color (brown);
	polf (4,backback);
	color (orange);
	polf (6,leftfire);
	polf (6,rightfire);
    closeobj ();

    makeobj (obj++);	/* above, left, behind	*/
	color (silver2);
 	polf (4,rightchine);
	color (C_LEFTNOSE);
	polf (3,leftnose);
	color (C_TOPNOSE);
	polf (3,topnose);

	color (C_FRONTBUBBLE);
	polf (4,frontbubble);
	color (C_PIT1);
	polf (3,pit1);
	color (C_PIT2);
	polf (3,pit2);
	color (C_PIT3);
	polf (3,pit3);
	color (C_PIT4);
	polf (3,pit4);

	color (silver5);
	polf (5,leftfront);
	color (silver2);
 	polf (4,leftchine);

	color (silver0);
	polf (4,rightwing);
	    moves (20,3,4);
	    draws (20,3,-5);
	polf (5,rightelevator);
	    color (green0);
	    pnts (19,3,-1);

	color (C_LEFTNOSE);
	polf (4,leftback);
	color (silver0);
	polf (4,leftwing);
	    moves (-20,3,4);
	    draws (-20,3,-5);
	polf (5,leftelevator);
	    color (red);
	    pnts (-19,3,-1);

	color (C_TOPBACK);
	polf (4,topback);
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    color (red);
	    pnts (5,8,12);
	color (silver6);
	polf (3,rightbubble);
	polf (3,leftbubble);
	color (C_TOPBUBBLE);
	polf (5,topbubble);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    color (white);
	    pnts (-5,8,12);

	color (brown);
	polf (4,backback);
	color (orange);
	polf (6,leftfire);
	polf (6,rightfire);
    closeobj ();

    makeobj (obj++);	/* above, right, behind	*/
	color (silver2);
 	polf (4,leftchine);
	color (C_LEFTNOSE);
	polf (3,rightnose);
	color (C_TOPNOSE);
	polf (3,topnose);

	color (C_FRONTBUBBLE);
	polf (4,frontbubble);
	color (C_PIT2);
	polf (3,pit2);
	color (C_PIT1);
	polf (3,pit1);
	color (C_PIT4);
	polf (3,pit4);
	color (C_PIT3);
	polf (3,pit3);

	color (silver5);
	polf (5,rightfront);
	color (silver2);
 	polf (4,rightchine);

	color (silver0);
	polf (4,leftwing);
	    moves (-20,3,4);
	    draws (-20,3,-5);
	polf (5,leftelevator);
	    color (red);
	    pnts (-19,3,-1);

	color (C_LEFTNOSE);
	polf (4,rightback);
	color (silver0);
	polf (4,rightwing);
	    moves (20,3,4);
	    draws (20,3,-5);
	polf (5,rightelevator);
	    color (green0);
	    pnts (19,3,-1);

	color (C_TOPBACK);
	polf (4,topback);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    color (white);
	    pnts (-5,8,12);
	color (silver6);
	polf (3,rightbubble);
	polf (3,leftbubble);
	color (C_TOPBUBBLE);
	polf (5,topbubble);
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    color (red);
	    pnts (5,8,12);

	color (brown);
	polf (4,backback);
	color (orange);
	polf (6,leftfire);
	polf (6,rightfire);
    closeobj ();

    makeobj (obj++);		/* real far away	*/
	color (silver4);
	polf (3,fakewing);
	color (silver7);
	polf (3,fakestab);
	color (orange);
	polf (6,leftfire);
	polf (6,rightfire);
	    color (white);
	    pnt (-5,8,12);
	    color (green0);
	    pnts (19,3,-1);
    closeobj ();

    makeobj (obj++);		/* shadow	*/
	color (black);
	setpattern(3);
	polf (4,rightwing);
	polf (4,leftwing);
	polf (5,rightelevator);
	polf (5,leftelevator);
	polf (4,rightrudder);
	polf (4,leftrudder);

	polf (4,rightback);
	polf (4,leftback);
	polf (4,topback);

	polf (5,rightfront);
	polf (5,leftfront);
	polf (4,frontbubble);

	polf (3,rightnose);
	polf (3,leftnose);
	polf (3,topnose);
	setpattern(0);
    closeobj ();

    makeobj (obj+100);		/* shadow far away	*/
	color (black);
	setpattern(3);
	polf (3,fakestab);
	polf (3,fakewing);
	setpattern(0);
    closeobj ();
}
