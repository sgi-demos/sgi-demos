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
/*	PLANE definition for cessna 150
/************************************************************/
/* parts for Cessna 150 */

static Scoord cesswing[][3] = {
	{18,6,-20},
	{18,6,-16},
	{8,6,-15},
	{-8,6,-15},
	{-18,6,-16},
	{-18,6,-20},
};

static Scoord cessrstab[][3] = {
	{0,4,-3},
	{5,4,-3},
	{5,4,-1},
	{1,4,0},
	{0,4,-2},	
};
static Scoord cesslstab[][3] = {
	{0,4,-3},
	{-5,4,-3},
	{-5,4,-1},
	{-1,4,0},
	{0,4,-2},	
};

static Scoord cessfin[][3] = {
	{0,3,-1},
	{0,8,0},
	{0,8,-3},
	{0,4,-5},
	{0,2,-5},
};

static Scoord cessrfus[][3] = {
	{0,4,-5},
	{0,2,-5},
	{2,1,-15},
	{2,6,-15},
};

static Scoord cesslfus[][3] = {
	{0,4,-5},
	{0,2,-5},
	{-2,1,-15},
	{-2,6,-15},

};

static Scoord cesstfus[][3] = {
	{0,4,-5},
	{2,6,-15},
	{-2,6,-15},
};

static Scoord cessbfus[][3] = {
	{0,2,-5},
	{2,1,-15},
	{-2,1,-15},
};

static Scoord cessrcabin[][3] = {
	{2,4,-15},
	{2,1,-15},
	{2,1,-21},
	{2,4,-21},
};

static Scoord cesslcabin[][3] = {
	{-2,4,-15},
	{-2,1,-15},
	{-2,1,-21},
	{-2,4,-21},
};

static Scoord cessbcabin[][3] = {
	{2,1,-21},
	{2,1,-15},
	{-2,1,-15},
	{-2,1,-21},
};

static Scoord cessws[][3] = {
	{2,4,-21},
	{2,6,-20},
	{-2,6,-20},
	{-2,4,-21},
};

static Scoord cesstcowl[][3] = {
	{2,4,-21},
	{-2,4,-21},
	{-1,4,-24},
	{1,4,-24},
};

static Scoord cessrcowl[][3] = {
	{2,4,-21},
	{2,1,-21},
	{1,3,-24},
	{1,4,-24},
};

static Scoord cesslcowl[][3] = {
	{-2,4,-21},
	{-2,1,-21},
	{-1,3,-24},
	{-1,4,-24},
};

static Scoord cessbcowl[][3] = {
	{2,1,-21},
	{-2,1,-21},
	{-1,3,-24},
	{1,3,-24},
};

static Scoord cessnose[][3] = {
	{1,4,-24},
	{-1,4,-24},
	{-1,3,-24},
	{1,3,-24},
};

static Scoord cessrgear[][3] = {
	{5,0,-15},
	{5,0,-18},
	{5,1,-18},
	{5,1,-15},
};

static Scoord cesslgear[][3] = {
	{-5,0,-15},
	{-5,0,-18},
	{-5,1,-18},
	{-5,1,-15},
};

static Scoord cessngear[][3] = {
	{0,0,-22},
	{0,0,-23},
	{0,1,-23},
	{0,1,-22},
};

static Scoord cesslwindow[][3] = {
	{-2,4,-21},
	{-2,6,-20},
	{-2,6,-15},
	{-2,4,-15},
};


static Scoord cessrwindow[][3] = {
	{2,4,-21},
	{2,6,-20},
	{2,6,-15},
	{2,4,-15},
};
 
static Scoord cessfw[][3] = {
	{-20,6,-15},
	{20,6,-15},
	{20,6,-20},
	{-20,6,-20},
};

static Scoord cessff[][3] = {
	{0,0,0},
	{0,6,0},
	{0,6,-25},
	{0,0,-25},
};

make_c150 (obj)
    register Object obj;
{
    makeobj (obj++);	/* below, left, front	*/
	color(silver9);
	polfs(5,cessrstab);

	color(purple3);
	polfs(5,cessfin);

	color(silver9);
	polfs(5,cesslstab);

	color(purple3);
	polfs(4,cesslfus);

	color(silver8);
	polfs(6,cesswing);

	color(grey9);
	polfs(4,cessws);

	color(grey10);
	polfs(4,cesslwindow);

	color(purple3);
	polfs(4,cesslcabin);
	polfs(4,cessrcowl);
	polfs(4,cesslcowl);

	color(purple4);
	polfs(3,cessbfus);
	polfs(4,cessbcabin);
	polfs(4,cessbcowl);
	color(silver6);
	polfs(4,cessrgear);
	polfs(4,cesslgear);
	polfs(4,cessngear);

	color(brown);
	polfs(4,cessnose);
    closeobj ();

    makeobj (obj++);	/* below, right, front	*/
	color(silver9);
	polfs(5,cesslstab);

	color(purple3);
	polfs(5,cessfin);

	color(silver9);
	polfs(5,cessrstab);

	color(purple3);
	polfs(4,cessrfus);

	color(silver8);
	polfs(6,cesswing);

	color(grey9);
	polfs(4,cessws);

	color(grey10);
	polfs(4,cessrwindow);

	color(purple3);
	polfs(4,cessrcabin);
	polfs(4,cesslcowl);
	polfs(4,cessrcowl);

	color(purple4);
	polfs(3,cessbfus);
	polfs(4,cessbcabin);
	polfs(4,cessbcowl);
	color(silver6);
	polfs(4,cesslgear);
	polfs(4,cessrgear);
	polfs(4,cessngear);

	color(brown);
	polfs(4,cessnose);
    closeobj ();

    makeobj (obj++);	/* above, left, front	*/
	color(silver6);
	polfs(4,cessrgear);
	polfs(4,cesslgear);
	polfs(4,cessngear);

	color(silver3);
	polfs(5,cessrstab);

	color(purple3);
	polfs(5,cessfin);

	color(silver3);
	polfs(5,cesslstab);

	color(purple3);
	polfs(4,cesslfus);
	polfs(4,cesslcabin);

	polfs(4,cessrcowl);
	polfs(4,cessbcowl);
	polfs(4,cesslcowl);

	color(purple1);
	polfs(3,cesstfus);
	polfs(4,cesstcowl);

	color(grey10);
	polfs(4,cesslwindow);
	color(grey9);
	polfs(4,cessws);

	color(silver1);
	polfs(6,cesswing);

	color(brown);
	polfs(4,cessnose);
    closeobj ();

    makeobj (obj++);	/* above, right, front	*/
	color(silver6);
	polfs(4,cesslgear);
	polfs(4,cessrgear);
	polfs(4,cessngear);

	color(silver3);
	polfs(5,cesslstab);

	color(purple3);
	polfs(5,cessfin);

	color(silver3);
	polfs(5,cessrstab);

	color(purple3);
	polfs(4,cessrfus);
	polfs(4,cessrcabin);

	polfs(4,cesslcowl);
	polfs(4,cessbcowl);
	polfs(4,cessrcowl);

	color(purple1);
	polfs(3,cesstfus);
	polfs(4,cesstcowl);

	color(grey10);
	polfs(4,cessrwindow);
	color (grey9);
	polfs(4,cessws);

	color(silver1);
	polfs(6,cesswing);

	color(brown);
	polfs(4,cessnose);
    closeobj ();

    makeobj (obj++);	/* below, left, behind	*/
	color(silver8);
	polfs(6,cesswing);

	color(grey10);
	polfs(4,cesslwindow);

	color(purple1);
	polfs(3,cesstfus);
	color(purple3);
	polfs(4,cessrfus);

	color(purple4);
	polfs(3,cessbfus);
	polfs(4,cessbcabin);
	polfs(4,cessbcowl);

	color(purple3);
	polfs(4,cesslcowl);
	polfs(4,cesslcabin);
	polfs(4,cesslfus);

	color(silver9);
	polfs(5,cessrstab);

	color(purple3);
	polfs(5,cessfin);

	color(silver9);
	polfs(5,cesslstab);

	color(silver6);
	polfs(4,cessrgear);
	polfs(4,cesslgear);
	polfs(4,cessngear);
    closeobj ();

    makeobj (obj++);	/* below, right, behind	*/
	color(silver8);
	polfs(6,cesswing);

	color(grey10);
	polfs(4,cessrwindow);

	color(purple1);
	polfs(3,cesstfus);
	color(purple3);
	polfs(4,cesslfus);

	color(purple3);
	polfs(4,cessrcowl);
	polfs(4,cessrcabin);

	color(purple4);
	polfs(3,cessbfus);
	polfs(4,cessbcabin);
	polfs(4,cessbcowl);

	color(purple3);
	polfs(4,cessrfus);

	color(silver9);
	polfs(5,cesslstab);

	color(purple3);
	polfs(5,cessfin);

	color(silver9);
	polfs(5,cessrstab);

	color(silver6);
	polfs(4,cesslgear);
	polfs(4,cessrgear);
	polfs(4,cessngear);
    closeobj();

    makeobj (obj++);	/* above, left, behind	*/
	color(silver6);
	polfs(4,cessrgear);
	polfs(4,cesslgear);
	polfs(4,cessngear);

	color(purple3);
	polfs(4,cessrfus);
	polfs(4,cesslcowl);
	polfs(4,cesslcabin);
	polfs(4,cesslfus);

	color(purple1);
	polfs(4,cesstcowl);
	color(grey9);
	polfs(4,cessws);
	color(grey10);
	polfs(4,cesslwindow);
	color(purple1);
	polfs(3,cesstfus);

	color(silver1);
	polfs(6,cesswing);

	color(silver3);
	polfs(5,cessrstab);

	color(purple3);
	polfs(5,cessfin);

	color(silver3);
	polfs(5,cesslstab);
    closeobj ();

    makeobj (obj++);	/* above, right, behind	*/
	color(silver6);
	polfs(4,cesslgear);
	polfs(4,cessrgear);
	polfs(4,cessngear);

	color(purple3);
	polfs(4,cesslfus);
	polfs(4,cessrcowl);
	polfs(4,cessrcabin);
	polfs(4,cessrfus);

	color(purple1);
	color(grey9);
	polfs(4,cessws);
	color(grey10);
	polfs(4,cessrwindow);
	color(purple1);

	color(silver1);
	polfs(6,cesswing);

	color(silver3);
	polfs(5,cesslstab);

	color(purple3);
	polfs(5,cessfin);

	color(silver3);
	polfs(5,cessrstab);
    closeobj ();

    makeobj (obj++);		/* real far away	*/
	color(purple3);
	polfs(4,cessff);
	color(silver1);
	polfs(4,cessfw);
    closeobj ();

    makeobj (obj++);		/* shadow	*/
	color (black);
	setpattern(3);
	polfs(6,cesswing);
	polfs(5,cessfin);
	polfs(5,cessrstab);
	polfs(5,cesslstab);
	polfs(4,cesslfus);
	polfs(4,cessrfus);
	polfs(3,cesstfus);

	polfs(4,cesslcabin);
	polfs(4,cessrcabin);

	polfs(4,cessrcowl);
	polfs(4,cesslcowl);
	polfs(4,cesstcowl);
	setpattern(0);
    closeobj ();

    makeobj (obj+100);		/* shadow far away	*/
	color (black);
	setpattern(3);
	polfs(4,cessff);
	polfs(4,cessfw);
	setpattern(0);
    closeobj ();
}
