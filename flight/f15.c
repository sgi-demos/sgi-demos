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
/*	F-15 plane definition
/************************************************************/
static float fakewing[][3] = {
    {0,0,-41},
    {21,0,16},
    {-21,0,16},
};
static float fakestab[][3] = {
    {0,0,0},
    {0,14,16},
    {0,0,16}
};
static float rightfire[][3] = {
    {1.0,2.5,16.0},
    {2,4,16.0},
    {3,4,16.0},
    {4.0,2.5,16.0},
    {3,1,16.0},
    {2,1,16.0},
};
static float leftfire[][3] = {
    {-1.0,2.5,16.0},
    {-2,4,16.0},
    {-3,4,16.0},
    {-4.0,2.5,16.0},
    {-3,1,16.0},
    {-2,1,16.0},
};

static float rightwing[][3] = {
    {5,5,7},
    {5,5,-11},
    {21,5,2},
    {19,5,8},
};
static float leftwing[][3] = {
    {-5,5,7},
    {-5,5,-11},
    {-21,5,2},
    {-19,5,8},
};
static float rightchine[][3] = {
    {5,5,-9},
    {5,5,-17},
    {7,5,-12},
    {7,5,-9},
};
static float leftchine[][3] = {
    {-5,5,-9},
    {-5,5,-17},
    {-7,5,-12},
    {-7,5,-9},
};
static float rightinlet[][3] = {
    {2,5,-23},
    {2,5,-17},
    {5,5,-17},
    {5,5,-23},
};
static float leftinlet[][3] = {
    {-2,5,-23},
    {-2,5,-17},
    {-5,5,-17},
    {-5,5,-23},
};

static float rightrudder[][3] = {
    {4.5,5,7},
    {4.5,14,14},
    {4.5,14,17},
    {4.5,5,16},
};
static float leftrudder[][3] = {
    {-4.5,5,7},
    {-4.5,14,14},
    {-4.5,14,17},
    {-4.5,5,16},
};

static float rightelevator[][3] = {
    {5,2,10},
    {13,2,18},
    {12,2,22},
    {5,2,20},
};
static float leftelevator[][3] = {
    {-5,2,10},
    {-13,2,18},
    {-12,2,22},
    {-5,2,20},
};

static float topback[][3] = {
    {-5,5,-17},
    {5,5,-17},
    {5,5,16},
    {-5,5,16},
};
static float rightback[][3] = {
    {5,5,-23},
    {5,5,16},
    {5,0,16},
    {5,0,-17},
};
static float leftback[][3] = {
    {-5,5,-23},
    {-5,5,16},
    {-5,0,16},
    {-5,0,-17},
};
static float bottomback[][3] = {
    {-5,0,-17},
    {5,0,-17},
    {5,0,16},
    {-5,0,16},
};
static float backback[][3] = {
    {-5,5,16},
    {5,5,16},
    {5,0,16},
    {-5,0,16},
};
static float frontback[][3] = {
    {-5,5,-17},
    {5,5,-17},
    {5,0,-17},
    {-5,0,-17},
};

static float bottomfront[][3] = {
    {2,1,-34},
    {2,1,-17},
    {-2,1,-17},
    {-2,1,-34},
};
static float rightfront[][3] = {
    {2,1,-34},
    {2,1,-17},
    {2,7,-17},
    {2,4,-34},
};
static float leftfront[][3] = {
    {-2,1,-34},
    {-2,1,-17},
    {-2,7,-17},
    {-2,4,-34},
};
static float rightnose[][3] = {
    {0,2,-41},
    {2,1,-34},
    {2,4,-34},
};
static float leftnose[][3] = {
    {0,2,-41},
    {-2,1,-34},
    {-2,4,-34},
};
static float topnose[][3] = {
    {0,2,-41},
    {2,4,-34},
    {-2,4,-34},
};
static float botnose[][3] = {
    {0,2,-41},
    {2,1,-34},
    {-2,1,-34},
};
static float frontbubble[][3] = {
    {-2,4,-34},
    {-2,7,-17},
    {2,7,-17},
    {2,4,-34},
};
static float topbubble[][3] = {
    {-2,7,-17},
    {0,5,0},
    {2,7,-17},
};
static float rightbubble[][3] = {
    {2,7,-17},
    {0,5,0},
    {2,5,-17},
};
static float leftbubble[][3] = {
    {-2,7,-17},
    {0,5,0},
    {-2,5,-17},
};
static float pit1[][3] = {
    {0,4.8825,-29},
    {1.8,5.7648,-24},
    {0,8,-24},
};
static float pit2[][3] = {
    {0,4.8825,-29},
    {-1.8,5.7648,-24},
    {0,8,-24},
};
static float pit3[][3] = {
    {0,7,-17},
    {1.8,5.7648,-24},
    {0,8,-24},
};
static float pit4[][3] = {
    {0,7,-17},
    {-1.8,5.7648,-24},
    {0,8,-24},
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

make_f15 (obj)
    register Object obj;
{
    makeobj (obj++);	/* below, left, front	*/
	color (C_LEFTNOSE);
	polf (4,rightback);
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    move (4.5,14.0,12.5);
	    draw (4.5,14.0,17.5);
	    color (red);
	    pnt (4.5,12.0,17.0);
	color (silver6);
	polf (3,leftbubble);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    move (-4.5,14.0,12.5);
	    draw (-4.5,14.0,17.5);
	    color (white);
	    pnt (-4.5,12.0,17.0);

	color (C_UNDERWING);
	polf (4,rightelevator);
	polf (4,rightwing);
 	polf (4,rightchine);
 	polf (4,rightinlet);
	color (green0);
	pnts (20,5,1);
	color (brown);
	polf (4,frontback);
    
	color (C_FRONTBUBBLE);
	polf (4,frontbubble);
	color (C_PIT4);
	polf (3,pit4);
	color (C_PIT1);
	polf (3,pit1);
	color (C_PIT2);
	polf (3,pit2);
	color (silver5);
	polf (4,leftfront);

	color (C_UNDERWING);
	polf (4,leftwing);
 	polf (4,leftchine);
 	polf (4,leftinlet);
	color (red);
	pnts (-20,5,1);

	color (C_LEFTNOSE);
	polf (4,leftback);
	polf (3,rightnose);
	color (C_TOPNOSE);
	polf (3,topnose);
	color (C_LEFTNOSE);
	polf (3,leftnose);

	color (C_UNDERWING);
	polf (4,leftelevator);
	color (C_UNDERBODY);
	polf (4,bottomback);
	polf (4,bottomfront);
	polf (3,botnose);
    closeobj ();

    makeobj (obj++);	/* below, right, front	*/
	color (C_LEFTNOSE);
	polf (4,leftback);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    move (-4.5,14.0,12.5);
	    draw (-4.5,14.0,17.5);
	    color (white);
	    pnt (-4.5,12.0,17.0);
	color (silver6);
	polf (3,rightbubble);
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    move (4.5,14.0,12.5);
	    draw (4.5,14.0,17.5);
	    color (red);
	    pnt (4.5,12.0,17.0);

	color (C_UNDERWING);
	polf (4,leftelevator);
	polf (4,leftwing);
 	polf (4,leftchine);
 	polf (4,leftinlet);
	color (red);
	pnts (-20,5,1);
	color (brown);
	polf (4,frontback);

	color (C_FRONTBUBBLE);
	polf (4,frontbubble);
	color (C_PIT3);
	polf (3,pit3);
	color (C_PIT2);
	polf (3,pit2);
	color (C_PIT1);
	polf (3,pit1);
	color (silver5);
	polf (4,rightfront);

	color (C_UNDERWING);
	polf (4,rightwing);
 	polf (4,rightchine);
 	polf (4,rightinlet);
	color (green0);
	pnts (20,5,1);

	color (C_LEFTNOSE);
	polf (4,rightback);
	polf (3,leftnose);
	color (C_TOPNOSE);
	polf (3,topnose);
	color (C_LEFTNOSE);
	polf (3,rightnose);

	color (C_UNDERWING);
	polf (4,rightelevator);
	color (C_UNDERBODY);
	polf (4,bottomback);
	polf (4,bottomfront);
	polf (3,botnose);
    closeobj ();

    makeobj (obj++);	/* above, left, front	*/
	color (C_LEFTNOSE);
	polf (4,rightback);
	color (silver0);
	polf (4,rightelevator);
	polf (4,rightwing);
 	polf (4,rightchine);
	color (green0);
	pnts (20,5,1);
	color (brown);
	polf (4,frontback);
	color (C_TOPBACK);
 	polf (4,rightinlet);
	polf (4,topback);
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    move (4.5,14.0,12.5);
	    draw (4.5,14.0,17.5);
	    color (red);
	    pnt (4.5,12.0,17.0);
	color (C_TOPBUBBLE);
	polf (3,topbubble);
	color (silver6);
	polf (3,leftbubble);

	color (silver5);
	polf (4,leftfront);
	color (C_LEFTNOSE);
	polf (4,leftback);
	color (C_TOPBACK);
 	polf (4,leftinlet);
	color (silver0);
	polf (4,leftelevator);
	polf (4,leftwing);
 	polf (4,leftchine);
	color (red);
	pnts (-20,5,1);

	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    move (-4.5,14.0,12.5);
	    draw (-4.5,14.0,17.5);
	    color (white);
	    pnt (-4.5,12.0,17.0);

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
	color (C_LEFTNOSE);
	polf (4,leftback);
	color (silver0);
	polf (4,leftelevator);
	polf (4,leftwing);
 	polf (4,leftchine);
	color (red);
	pnts (-20,5,1);
	color (brown);
	polf (4,frontback);
	color (C_TOPBACK);
	polf (4,topback);
 	polf (4,leftinlet);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    move (-4.5,14.0,12.5);
	    draw (-4.5,14.0,17.5);
	    color (white);
	    pnt (-4.5,12.0,17.0);
	color (C_TOPBUBBLE);
	polf (3,topbubble);
	color (silver6);
	polf (3,rightbubble);

	color (silver5);
	polf (4,rightfront);
	color (C_LEFTNOSE);
	polf (4,rightback);
	color (C_TOPBACK);
 	polf (4,rightinlet);
	color (silver0);
	polf (4,rightelevator);
	polf (4,rightwing);
 	polf (4,rightchine);
	color (green0);
	pnts (20,5,1);

	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    move (4.5,14.0,12.5);
	    draw (4.5,14.0,17.5);
	    color (red);
	    pnt (4.5,12.0,17.0);

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
	color (C_UNDERWING);
 	polf (4,rightinlet);
	color (C_LEFTNOSE);
 	polf (4,rightback);
	polf (3,leftnose);
	color (C_PIT2);
	polf (3,pit2);
	color (C_PIT3);
	polf (3,pit3);
	color (C_PIT4);
	polf (3,pit4);

	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    move (4.5,14.0,12.5);
	    draw (4.5,14.0,17.5);
	    color (red);
	    pnt (4.5,12.0,17.0);
	color (C_TOPBUBBLE);
	polf (3,topbubble);
	color (silver6);
	polf (3,rightbubble);
	polf (3,leftbubble);

	color (silver5);
	polf (4,leftfront);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    move (-4.5,14.0,12.5);
	    draw (-4.5,14.0,17.5);
	    color (white);
	    pnt (-4.5,12.0,17.0);

	color (C_UNDERWING);
	polf (4,rightelevator);
	polf (4,rightwing);
 	polf (4,rightchine);
 	polf (4,leftinlet);
	polf (4,leftwing);
 	polf (4,leftchine);
	color (green0);
	pnts (20,5,1);
	color (red);
	pnts (-20,5,1);

	color (C_LEFTNOSE);
	polf (4,leftback);

	color (C_UNDERBODY);
	polf (3,botnose);
	polf (4,bottomfront);
	polf (4,bottomback);
	color (brown);
	polf (4,backback);
	color (orange);
	polf (6,leftfire);
	polf (6,rightfire);

	color (C_UNDERWING);
	polf (4,leftelevator);
    closeobj ();

    makeobj (obj++);	/* below, right, behind	*/
	color (C_UNDERWING);
 	polf (4,leftinlet);
	color (C_LEFTNOSE);
	polf (4,leftback);
	polf (3,rightnose);
	color (C_PIT1);
	polf (3,pit1);
	color (C_PIT4);
	polf (3,pit4);
	color (C_PIT3);
	polf (3,pit3);

	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    move (-4.5,14.0,12.5);
	    draw (-4.5,14.0,17.5);
	    color (white);
	    pnt (-4.5,12.0,17.0);
	color (C_TOPBUBBLE);
	polf (3,topbubble);
	color (silver6);
	polf (3,leftbubble);
	polf (3,rightbubble);

	color (silver5);
	polf (4,rightfront);
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    move (4.5,14.0,12.5);
	    draw (4.5,14.0,17.5);
	    color (red);
	    pnt (4.5,12.0,17.0);

	color (C_UNDERWING);
 	polf (4,leftchine);
	polf (4,leftelevator);
	polf (4,leftwing);
 	polf (4,rightinlet);
	polf (4,rightwing);
 	polf (4,rightchine);
	color (red);
	pnts (-20,5,1);
	color (green0);
	pnts (20,5,1);

	color (C_LEFTNOSE);
	polf (4,rightback);

	color (C_UNDERBODY);
	polf (3,botnose);
	polf (4,bottomfront);
	polf (4,bottomback);
	color (brown);
	polf (4,backback);
	color (orange);
	polf (6,leftfire);
	polf (6,rightfire);

	color (C_UNDERWING);
	polf (4,rightelevator);
    closeobj ();

    makeobj (obj++);	/* above, left, behind	*/
	color (C_LEFTNOSE);
	polf (3,leftnose);
	color (C_TOPNOSE);
	polf (3,topnose);
	color (C_TOPBACK);
 	polf (4,rightinlet);

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
	polf (4,leftfront);

	color (silver0);
 	polf (4,rightchine);
	polf (4,rightwing);
	polf (4,rightelevator);
	color (green0);
	pnts (20,5,1);

	color (brown);
	polf (4,backback);
	color (orange);
	polf (6,leftfire);
	polf (6,rightfire);
    
	color (C_LEFTNOSE);
	polf (4,leftback);
	color (silver0);
 	polf (4,leftchine);
	polf (4,leftwing);
	polf (4,leftelevator);
	color (red);
	pnts (-20,5,1);

	color (C_TOPBACK);
 	polf (4,leftinlet);
	polf (4,topback);
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    move (4.5,14.0,12.5);
	    draw (4.5,14.0,17.5);
	    color (red);
	    pnt (4.5,12.0,17.0);
	color (silver6);
	polf (3,rightbubble);
	polf (3,leftbubble);
	color (C_TOPBUBBLE);
	polf (3,topbubble);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    move (-4.5,14.0,12.5);
	    draw (-4.5,14.0,17.5);
	    color (white);
	    pnt (-4.5,12.0,17.0);
    closeobj ();

    makeobj (obj++);	/* above, right, behind	*/
	color (C_LEFTNOSE);
	polf (3,rightnose);
	color (C_TOPNOSE);
	polf (3,topnose);
	color (C_TOPBACK);
 	polf (4,leftinlet);

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
	polf (4,rightfront);

	color (silver0);
 	polf (4,leftchine);
	polf (4,leftwing);
	polf (4,leftelevator);
	color (red);
	pnts (-20,5,1);

	color (brown);
	polf (4,backback);
	color (orange);
	polf (6,leftfire);
	polf (6,rightfire);

	color (C_LEFTNOSE);
	polf (4,rightback);
	color (silver0);
 	polf (4,rightchine);
	polf (4,rightwing);
	polf (4,rightelevator);
	color (green0);
	pnts (20,5,1);

	color (C_TOPBACK);
 	polf (4,rightinlet);
	polf (4,topback);
	color (C_LEFTRUDDER);
	polf (4,leftrudder);
	    move (-4.5,14.0,12.5);
	    draw (-4.5,14.0,17.5);
	    color (white);
	    pnt (-4.5,12.0,17.0);
	color (silver6);
	polf (3,rightbubble);
	polf (3,leftbubble);
	color (C_TOPBUBBLE);
	polf (3,topbubble);
	color (C_RIGHTRUDDER);
	polf (4,rightrudder);
	    move (4.5,14.0,12.5);
	    draw (4.5,14.0,17.5);
	    color (red);
	    pnt (4.5,12.0,17.0);
    closeobj ();

    makeobj (obj++);		/* real far away	*/
	color (silver4);
	polf (3,fakewing);
	color (silver7);
	polf (3,fakestab);
	color (orange);
	polf (6,leftfire);
	polf (6,rightfire);

	color (green0);
	pnts (20,5,1);
	color (white);
	pnt (-4.5,12.0,17.0);
    closeobj ();

    makeobj (obj++);		/* shadow	*/
	color (black);
	setpattern(3);
	polf (4,rightwing);
	polf (4,leftwing);
	polf (4,rightelevator);
	polf (4,leftelevator);
	polf (4,rightrudder);
	polf (4,leftrudder);

	polf (4,rightback);
	polf (4,leftback);
	polf (4,topback);

	polf (4,rightfront);
	polf (4,leftfront);
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
