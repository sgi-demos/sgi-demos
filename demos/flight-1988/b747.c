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
	B747 plane definitions  Don Hill 10-10-84
/************************************************************/
static Scoord Ehanger [][3] = {
    {  0,  0,   0},
    {  0,  0,  17},
    {  0, -4,   5},
    {  0, -4, -10},
};
static Scoord EL1 [][3] = {
    { -3, -3, -12},
    { -3, -9, -12},
    { -3, -9,  -4},
    { -3, -3,  -4},
};
static Scoord EL2 [][3] = {
    { -2, -4,  -4},
    { -2, -8,  -4},
    { -2, -8,   4},
    { -2, -4,   4},
};
static Scoord EL3 [][3] = {
    { -1, -5,   4},
    {  0, -6,  10},
    { -1, -7,   4},
};
static Scoord ER1 [][3] = {
    {  3, -3, -12},
    {  3, -9, -12},
    {  3, -9,  -4},
    {  3, -3,  -4},
};
static Scoord ER2 [][3] = {
    {  2, -4,  -4},
    {  2, -8,  -4},
    {  2, -8,   4},
    {  2, -4,   4},
};
static Scoord ER3 [][3] = {
    {  1, -5,   4},
    {  0, -6,  10},
    {  1, -7,   4},
};
static Scoord EFRONT [][3] = {
    { -3, -3, -11},
    { -3, -9, -11},
    {  3, -9, -11},
    {  3, -3, -11},
};
static Scoord EFIRE  [][3] = {
    { -2, -4, 3},
    { -2, -8, 3},
    {  2, -8, 3},
    {  2, -4, 3},
};
static Scoord ET1 [][3] = {
    { -3, -3, -12},
    {  3, -3, -12},
    {  3, -3,  -4},
    { -3, -3,  -4},
};
static Scoord EB1 [][3] = {
    { -3, -9, -12},
    {  3, -9, -12},
    {  3, -9,  -4},
    { -3, -9,  -4},
};
static Scoord ET2 [][3] = {
    { -2, -4,  -4},
    {  2, -4,  -4},
    {  2, -4,   4},
    { -2, -4,   4},
};
static Scoord EB2 [][3] = {
    { -2, -8,  -4},
    {  2, -8,  -4},
    {  2, -8,   4},
    { -2, -8,   4},
};
static Scoord ET3 [][3] = {
    {  1, -5,   4},
    {  0, -6,  10},
    { -1, -5,   4},
};
static Scoord EB3 [][3] = {
    {  1, -7,   4},
    {  0, -6,  10},
    { -1, -7,   4},
};
static Scoord B1 [][3] = {
    {  0, 20, -100},
    { -4, 16,  -98},
    {  4, 16,  -98},
};
static Scoord B2 [][3] = {
    {  4, 16, -98},
    { -4, 16, -98},
    {-10, 10, -84},
    { 10, 10, -84},
};
static Scoord B3 [][3] = {
    { 10, 10, -84},
    {-10, 10, -84},
    {-10, 10,  66},
    { 10, 10,  66},
};
static Scoord B4 [][3] = {
    { 10, 10,  66},
    {-10, 10,  66},
    {-10, 17,  99},
    {  0, 24, 132},
    { 10, 17,  99},
};
static Scoord L1 [][3] = {
    {  0, 20,-100},
    { -4, 24, -98},
    { -4, 16, -98},
};
static Scoord L2 [][3] = {
    { -4, 16, -98},
    { -4, 24, -98},
    {-10, 30, -84},
    {-10, 10, -84},
};
static Scoord L3 [][3] = {
    {-10, 10, -84},
    {-10, 30, -84},
    {-10, 30,  99},
    {-10, 17,  99},
    {-10, 10,  66},
};
static Scoord L4 [][3] = {
    {-10, 17,  99},
    {-10, 30,  99},
    {  0, 30, 132},
    {  0, 24, 132},
};
static Scoord R1 [][3] = {
    {  0, 20,-100},
    {  4, 24, -98},
    {  4, 16, -98},
};
static Scoord R2 [][3] = {
    {  4, 16, -98},
    {  4, 24, -98},
    { 10, 30, -84},
    { 10, 10, -84},
};
static Scoord R3 [][3] = {
    { 10, 10, -84},
    { 10, 30, -84},
    { 10, 30,  99},
    { 10, 17,  99},
    { 10, 10,  66},
};
static Scoord R4 [][3] = {
    { 10, 17,  99},
    { 10, 30,  99},
    {  0, 30, 132},
    {  0, 24, 132},
};
static Scoord T0 [][3] = {	/* used for shadow	*/
    {  0, 30,-100},
    {  4, 30, -98},
    { 10, 30, -84},
    { 10, 30,  99},
    {  0, 30, 132},
    {-10, 30,  99},
    {-10, 30, -84},
    { -4, 30, -98},
};
static Scoord T1 [][3] = {
    {  0, 20,-100},
    { -4, 24, -98},
    {  4, 24, -98},
};
static Scoord T2 [][3] = {
    {  4, 24, -98},
    { -4, 24, -98},
    { -2, 30, -90},
    {  2, 30, -90},
};
static Scoord T3 [][3] = {
    {  4, 24, -98},
    {  2, 30, -90},
    {  8, 30, -84},
    { 10, 30, -84},
};
static Scoord T4 [][3] = {
    { -4, 24, -98},
    { -2, 30, -90},
    { -8, 30, -84},
    {-10, 30, -84},
};
static Scoord T5 [][3] = {
    { 10, 30, -84},
    {  8, 30, -84},
    {  6, 32, -84},
    {  6, 34, -84},
};
static Scoord T6 [][3] = {
    {-10, 30, -84},
    { -8, 30, -84},
    { -6, 32, -84},
    { -6, 34, -84},
};
static Scoord T7 [][3] = {
    { -2, 30, -90},
    {  2, 30, -90},
    {  2, 32, -88},
    { -2, 32, -88},
};
static Scoord T8 [][3] = {
    {  2, 30, -90},
    {  2, 32, -88},
    {  6, 32, -84},
    {  8, 30, -84},
};
static Scoord T9 [][3] = {
    { -2, 30, -90},
    { -2, 32, -88},
    { -6, 32, -84},
    { -8, 30, -84},
};
static Scoord T10 [][3] = {
    {  2, 32, -88},
    {  6, 34, -84},
    { -6, 34, -84},
    { -2, 32, -88},
};
static Scoord T13 [][3] = {
    {  6, 34, -84},
    {  6, 34, -68},
    { -6, 34, -68},
    { -6, 34, -84},
};
static Scoord T14 [][3] = {
    {  6, 34, -84},
    { 10, 30, -84},
    { 10, 30, -52},
    {  6, 34, -68},
};
static Scoord T15 [][3] = {
    { -6, 34, -84},
    {-10, 30, -84},
    {-10, 30, -52},
    { -6, 34, -68},
};
static Scoord T16 [][3] = {
    {  6, 34, -68},
    { 10, 30, -52},
    {-10, 30, -52},
    { -6, 34, -68},
};
static Scoord T17 [][3] = {
    { 10, 30, -52},
    { 10, 30,  99},
    {  0, 30, 132},
    {-10, 30,  99},
    {-10, 30, -52},
};
static Scoord rudder[][3] = {
    {  0, 30, 126},
    {  0, 64, 140},
    {  0, 64, 128},
    {  0, 30,  92},
};
static Scoord fakeside[][3] = {
    {  0, 30, 132},
    {  0, 16, 132},
    {  0, 16,-100},
    {  0, 30,-100},
};
static Scoord rightelevator1[][3] = {
    {  0, 26, 126},
    { 49, 30, 140},
    { 49, 30, 130},
    { 10, 26,  99},
};
static Scoord rightelevator2[][3] = {
    { 10, 26,  89},
    { 10, 26,  99},
    { 49, 30, 130},
    { 49, 30, 126},
};
static Scoord leftelevator1[][3] = {
    { -0, 26, 126},
    {-49, 30, 140},
    {-49, 30, 130},
    {-10, 26,  99},
};
static Scoord leftelevator2[][3] = {
    {-10, 26,  89},
    {-10, 26,  99},
    {-49, 30, 130},
    {-49, 30, 126},
};
static Scoord rightwing1[][3] = {
    { 10, 16, -55+20},
    { 10, 16, -15+20},
    { 98, 24,  31+20},
    { 98, 24,  13+20},
};
static float rightwing2[][3] = {
    { 10, 16, -15+20},
    { 10, 16,  -7+20},
    { 38, 18.5555, -3+20},
};
static Scoord leftwing1[][3] = {
    {-10, 16, -55+20},
    {-10, 16, -15+20},
    {-98, 24,  31+20},
    {-98, 24,  13+20},
};
static float leftwing2[][3] = {
    {-10, 16, -15+20},
    {-10, 16,  -7+20},
    {-38, 18.5555, -3+20},
};
static Scoord fakewing[][3] = {
    { 98, 24,  31+20},
    { -98, 24,  31+20},
    { 0,  16, -55+20}
};

#define C_TOPNOSE silver4
#define C_LEFTNOSE silver6
#define C_TOPBUBBLE silver1
#define C_FRONTBUBBLE silver3
#define C_TOPBACK silver2
#define C_RIGHTRUDDER silver3
#define C_LEFTRUDDER silver4
#define C_UNDERWING silver8
#define C_UNDERBODY silver9


make_b747 (obj)
    register Object obj;
{
    Object eng_alf,eng_arf,eng_blf,eng_brf;
    Object eng_alb,eng_arb,eng_blb,eng_brb;

    eng_alf = 2000;
    eng_arf = 2001;
    eng_blf = 2002;
    eng_brf = 2003;
    eng_alb = 2004;
    eng_arb = 2005;
    eng_blb = 2006;
    eng_brb = 2007;

    makeobj (eng_alf);
	color (C_UNDERBODY);
	polfs (3,EB3);
	polfs (4,EB2);
	polfs (4,EB1);
	color (C_LEFTRUDDER);
	polfs (3,ER3);
	polfs (4,ER2);
	polfs (4,ER1);
	color (red);
	polfs (4,EFIRE);
	color (C_UNDERBODY);
	polfs (4,EFRONT);
	color (C_LEFTRUDDER);
	polfs (3,EL3);
	polfs (4,EL2);
	polfs (4,EL1);
	color (C_RIGHTRUDDER);
	polfs (3,ET3);
	polfs (4,ET2);
	polfs (4,ET1);
	color (C_LEFTRUDDER);
	polfs (4,Ehanger);
    closeobj();

    makeobj (eng_arf);
	color (C_UNDERBODY);
	polfs (3,EB3);
	polfs (4,EB2);
	polfs (4,EB1);
	color (C_LEFTRUDDER);
	polfs (3,EL3);
	polfs (4,EL2);
	polfs (4,EL1);
	color (red);
	polfs (4,EFIRE);
	color (C_UNDERBODY);
	polfs (4,EFRONT);
	color (C_LEFTRUDDER);
	polfs (3,ER3);
	polfs (4,ER2);
	polfs (4,ER1);
	color (C_RIGHTRUDDER);
	polfs (3,ET3);
	polfs (4,ET2);
	polfs (4,ET1);
	color (C_LEFTRUDDER);
	polfs (4,Ehanger);
    closeobj();

    makeobj (eng_blf);
	color (C_LEFTRUDDER);
	polfs (4,Ehanger);
	color (C_RIGHTRUDDER);
	polfs (4,ET1);
	polfs (4,ET2);
	polfs (3,ET3);
	color (C_LEFTRUDDER);
	polfs (4,ER1);
	polfs (4,ER2);
	polfs (3,ER3);
	color (red);
	polfs (4,EFIRE);
	color (C_UNDERBODY);
	polfs (4,EFRONT);
	color (C_LEFTRUDDER);
	polfs (4,EL1);
	polfs (4,EL2);
	polfs (3,EL3);
	color (C_UNDERBODY);
	polfs (4,EB1);
	polfs (4,EB2);
	polfs (3,EB3);
    closeobj();

    makeobj (eng_brf);
	color (C_LEFTRUDDER);
	polfs (4,Ehanger);
	color (C_RIGHTRUDDER);
	polfs (4,ET1);
	polfs (4,ET2);
	polfs (3,ET3);
	color (C_LEFTRUDDER);
	polfs (4,EL1);
	polfs (4,EL2);
	polfs (3,EL3);
	color (red);
	polfs (4,EFIRE);
	color (C_UNDERBODY);
	polfs (4,EFRONT);
	color (C_LEFTRUDDER);
	polfs (4,ER1);
	polfs (4,ER2);
	polfs (3,ER3);
	color (C_UNDERBODY);
	polfs (4,EB1);
	polfs (4,EB2);
	polfs (3,EB3);
    closeobj();

    makeobj (obj++);	/* below, left, front	*/
	color (C_RIGHTRUDDER);
	polfs (4,rudder);
	    color (white);
	    pnts (0,64, 140);
	color (C_UNDERWING);
	polfs (4,rightelevator1);
	polfs (4,rightelevator2);
	polfs (4,rightwing1);
	polf (3,rightwing2);
	    moves (98,24,31);
	    draws (98,24,40);
	    color (green0);
	    pnts (98,24,31);

	color (C_TOPBACK);	/*	top back to front from left 	*/
	polfs (5,T17);
	color (silver0);
	polfs (4,T14);
	polfs (4,T16);
	color (C_TOPBACK);
	polfs (4,T13);
	color (silver0);
	polfs (4,T15);
	color (C_TOPBUBBLE);
	polfs (4,T8);
	polfs (4,T7);
	polfs (4,T9);
	color (C_UNDERBODY);
	polys (4,T8);
	polys (4,T7);
	polys (4,T9);
	color (silver0);
	polfs (4,T10);
	color (C_RIGHTRUDDER);
	polfs (4,T5);
	color (C_TOPBACK);
	polfs (4,T3);
	color (silver0);
	polfs (4,T2);
	color (C_TOPBACK);
	polfs (4,T4);
	color (C_RIGHTRUDDER);
	polfs (4,T6);
	color (silver0);
	polfs (3,T1);

	color (C_RIGHTRUDDER);	/*	right side back to front 	*/
	polfs (4,R4);
	polfs (5,R3);
	polfs (4,R2);
	polfs (3,R1);

	color (C_RIGHTRUDDER);	/*	left side back to front 	*/
	polfs (4,L4);
	polfs (5,L3);
	polfs (4,L2);
	polfs (3,L1);

	color (C_UNDERBODY);	/*	bottom back to front	*/
	polfs (5,B4);
	polfs (4,B3);
	polfs (4,B2);
	polfs (3,B1);

	color (C_UNDERWING);
	polfs (4,leftelevator1);
	polfs (4,leftelevator2);
	polfs (4,leftwing1);
	polf (3,leftwing2);
	    moves (-98,24,31);
	    draws (-98,24,40);
	    color (red);
	    pnts (-98,24,31);
    closeobj ();

    makeobj (obj++);	/* below ,right, front */
	color (C_RIGHTRUDDER);
	polfs (4,rudder);
	    color (white);
	    pnts (0,64, 140);
	color (C_UNDERWING);
	polfs (4,leftelevator1);
	polfs (4,leftelevator2);
	polfs (4,leftwing1);
	polf (3,leftwing2);
	    moves (-98,24,31);
	    draws (-98,24,40);
	    color (red);
	    pnts (-98,24,31);

	color (C_TOPBACK);	/*	top back to front 	*/
	polfs (5,T17);
	color (silver0);
	polfs (4,T15);
	polfs (4,T16);
	color (C_TOPBACK);
	polfs (4,T13);
	color (silver0);
	polfs (4,T14);
	color (C_TOPBUBBLE);
	polfs (4,T9);
	polfs (4,T7);
	polfs (4,T8);
	color (C_UNDERBODY);
	polys (4,T9);
	polys (4,T7);
	polys (4,T8);
	color (silver0);
	polfs (4,T10);
	color (C_RIGHTRUDDER);
	polfs (4,T6);
	color (C_TOPBACK);
	polfs (4,T4);
	color (silver0);
	polfs (4,T2);
	color (C_TOPBACK);
	polfs (4,T3);
	color (C_RIGHTRUDDER);
	polfs (4,T5);
	color (silver0);
	polfs (3,T1);

	color (C_RIGHTRUDDER);	/*	left side back to front 	*/
	polfs (4,L4);
	polfs (5,L3);
	polfs (4,L2);
	polfs (3,L1);

	color (C_RIGHTRUDDER);	/*	right side back to front 	*/
	polfs (4,R4);
	polfs (5,R3);
	polfs (4,R2);
	polfs (3,R1);

	color (C_UNDERBODY);	/*	bottom back to front	*/
	polfs (5,B4);
	polfs (4,B3);
	polfs (4,B2);
	polfs (3,B1);

	color (C_UNDERWING);
	polfs (4,rightelevator1);
	polfs (4,rightelevator2);
	polfs (4,rightwing1);
	polf (3,rightwing2);
	    moves (98,24,31);
	    draws (98,24,40);
	    color (green0);
	    pnts (98,24,31);
    closeobj ();

    makeobj (obj++);	/* above, left, front	*/
	color (C_UNDERBODY);	/*	bottom back to front	*/
	polfs (4,B2);
	polfs (3,B1);

	pushmatrix();
	translate ( 68.0, 21.27, -9.0+20);
	callobj(eng_alf);
	popmatrix();

	pushmatrix();
	translate ( 40.0, 18.73, -21.0+20);
	callobj(eng_alf);
	popmatrix();

	pushmatrix();
	translate (-40.0, 18.73, -21.0+20);
	callobj(eng_alf);
	popmatrix();

	pushmatrix();
	translate (-68.0, 21.27, -9.0+20);
	callobj(eng_alf);
	popmatrix();

	color (silver0);
	polfs (4,rightelevator1);
	color (silver1);
	polfs (4,rightelevator2);
	color (silver0);
	polfs (4,rightwing1);
	color (silver1);
	polf (3,rightwing2);
	    moves (98,24,31);
	    draws (98,24,40);
	    color (green0);
	    pnts (98,24,31);

	color (C_RIGHTRUDDER);	/*	right side back to front 	*/
	polfs (4,R2);
	polfs (3,R1);

	color (C_RIGHTRUDDER);	/*	left side back to front 	*/
	polfs (4,L4);
	polfs (5,L3);
	polfs (4,L2);
	polfs (3,L1);

	color (C_TOPBACK);	/*	top back to front from left 	*/
	polfs (5,T17);
	color (silver0);
	polfs (4,T14);
	polfs (4,T16);
	color (C_TOPBACK);
	polfs (4,T13);
	color (silver0);
	polfs (4,T15);
	color (C_RIGHTRUDDER);
	polfs (4,T5);
	color (C_TOPBACK);
	polfs (4,T3);
	color (silver0);
	polfs (4,T2);
	color (C_TOPBACK);
	polfs (4,T4);
	color (C_RIGHTRUDDER);
	polfs (4,T6);
	color (silver0);
	polfs (3,T1);
	color (C_TOPBUBBLE);
	polfs (4,T8);
	polfs (4,T7);
	polfs (4,T9);
	color (C_UNDERBODY);
	polys (4,T8);
	polys (4,T7);
	polys (4,T9);
	color (silver0);
	polfs (4,T10);

	color (C_RIGHTRUDDER);
	polfs (4,rudder);
	    color (white);
	    pnts (0,64, 140);
	color (silver0);
	polfs (4,leftelevator1);
	color (silver1);
	polfs (4,leftelevator2);
	color (silver0);
	polfs (4,leftwing1);
	color (silver1);
	polf (3,leftwing2);
	    moves (-98,24,31);
	    draws (-98,24,40);
	    color (red);
	    pnts (-98,24,31);
    closeobj ();

    makeobj (obj++);	/* above, right, front		*/
	color (C_UNDERBODY);	/*	bottom back to front	*/
	polfs (4,B2);
	polfs (3,B1);

	pushmatrix();
	translate ( 68.0, 21.27, -9.0+20);
	callobj(eng_arf);
	popmatrix();

	pushmatrix();
	translate ( 40.0, 18.73, -21.0+20);
	callobj(eng_arf);
	popmatrix();

	pushmatrix();
	translate (-40.0, 18.73, -21.0+20);
	callobj(eng_arf);
	popmatrix();

	pushmatrix();
	translate (-68.0, 21.27, -9.0+20);
	callobj(eng_arf);
	popmatrix();

	color (silver0);
	polfs (4,leftelevator1);
	color (silver1);
	polfs (4,leftelevator2);
	color (silver0);
	polfs (4,leftwing1);
	color (silver1);
	polf (3,leftwing2);
	    moves (-98,24,31);
	    draws (-98,24,40);
	    color (red);
	    pnts (-98,24,31);

	color (C_RIGHTRUDDER);	/*	left side back to front 	*/
	polfs (4,L2);
	polfs (3,L1);

	color (C_RIGHTRUDDER);	/*	right side back to front 	*/
	polfs (4,R4);
	polfs (5,R3);
	polfs (4,R2);
	polfs (3,R1);

	color (C_TOPBACK);	/*	top back to front 	*/
	polfs (5,T17);
	color (silver0);
	polfs (4,T15);
	polfs (4,T16);
	color (C_TOPBACK);
	polfs (4,T13);
	color (silver0);
	polfs (4,T14);
	color (C_RIGHTRUDDER);
	polfs (4,T6);
	color (C_TOPBACK);
	polfs (4,T4);
	color (silver0);
	polfs (4,T2);
	color (C_TOPBACK);
	polfs (4,T3);
	color (C_RIGHTRUDDER);
	polfs (4,T5);
	color (silver0);
	polfs (3,T1);

	color (C_TOPBUBBLE);
	polfs (4,T9);
	polfs (4,T7);
	polfs (4,T8);
	color (C_UNDERBODY);
	polys (4,T9);
	polys (4,T7);
	polys (4,T8);
	color (silver0);
	polfs (4,T10);

	color (silver0);
	polfs (4,rightelevator1);
	color (silver1);
	polfs (4,rightelevator2);
	color (silver0);
	polfs (4,rightwing1);
	color (silver1);
	polf (3,rightwing2);
	    moves (98,24,31);
	    draws (98,24,40);
	    color (green0);
	    pnts (98,24,31);
	color (C_RIGHTRUDDER);
	polfs (4,rudder);
	    color (white);
	    pnts (0,64, 140);
    closeobj ();

    makeobj (obj++);	/* below, left, behind		*/

	color (C_RIGHTRUDDER);
	polfs (4,rudder);
	    color (white);
	    pnts (0,64, 140);
	color (C_UNDERWING);
	polfs (4,rightelevator1);
	polfs (4,rightelevator2);
	polfs (4,rightwing1);
	polf (3,rightwing2);
	    moves (98,24,31);
	    draws (98,24,40);
	    color (green0);
	    pnts (98,24,31);

	color (silver0);	/* top front to back */
	polfs (3,T1);
	color (silver0);
	polfs (4,T2);
	color (C_TOPBACK);
	polfs (4,T3);
	color (C_RIGHTRUDDER);
	polfs (4,T5);
	color (C_RIGHTRUDDER);
	polfs (4,T6);
	color (C_TOPBACK);
	polfs (4,T4);
	color (silver0);
	polfs (4,T10);
	color (C_TOPBACK);
	polfs (4,T13);
	color (silver0);
	polfs (4,T14);
	color (silver0);
	polfs (4,T15);
	polfs (4,T16);
	color (C_TOPBACK);
	polfs (5,T17);
	color (C_RIGHTRUDDER);	/*	rightside front to back 	*/
	polfs (3,R1);
	polfs (4,R2);
	polfs (5,R3);
	polfs (4,R4);

	color (C_UNDERBODY);	/*	bottom front to back	*/
	polfs (3,B1);
	polfs (4,B2);
	polfs (4,B3);
	polfs (5,B4);

	color (C_RIGHTRUDDER);	/*	left side front to back  	*/
	polfs (3,L1);
	polfs (4,L2);
	polfs (5,L3);
	polfs (4,L4);

	color (C_UNDERWING);
	polfs (4,leftelevator1);
	polfs (4,leftelevator2);
	polfs (4,leftwing1);
	polf (3,leftwing2);
	    moves (-98,24,31);
	    draws (-98,24,40);
	    moves (-98,24,31);
	    draws (-98,24,40);
	    color (red);
	    pnts (-98,24,31);
    closeobj ();

    makeobj (obj++);	/* below, right, behind		*/
	color (C_RIGHTRUDDER);
	polfs (4,rudder);
	    color (white);
	    pnts (0,64, 140);
	color (C_UNDERWING);
	polfs (4,leftelevator1);
	polfs (4,leftelevator2);
	polfs (4,leftwing1);
	polf (3,leftwing2);
	    moves (-98,24,31);
	    draws (-98,24,40);
	    color (red);
	    pnts (-98,24,31);

	color (silver0);	/* top front to back */
	polfs (3,T1);
	color (silver0);
	polfs (4,T2);
	color (C_TOPBACK);
	polfs (4,T3);
	color (C_RIGHTRUDDER);
	polfs (4,T5);
	color (C_RIGHTRUDDER);
	polfs (4,T6);
	color (C_TOPBACK);
	polfs (4,T4);
	color (silver0);
	polfs (4,T10);
	color (C_TOPBACK);
	polfs (4,T13);
	color (silver0);
	polfs (4,T14);
	color (silver0);
	polfs (4,T15);
	polfs (4,T16);
	color (C_TOPBACK);
	polfs (5,T17);

	color (C_RIGHTRUDDER);	/*	left side front to back 	*/
	polfs (3,L1);
	polfs (4,L2);
	polfs (5,L3);
	polfs (4,L4);

	color (C_RIGHTRUDDER);	/*	right side front to back 	*/
	polfs (3,R1);
	polfs (4,R2);
	polfs (5,R3);
	polfs (4,R4);

	color (C_UNDERBODY);	/*	bottom front to back	*/
	polfs (3,B1);
	polfs (4,B2);
	polfs (4,B3);
	polfs (5,B4);

	color (C_UNDERWING);
	polfs (4,rightelevator1);
	polfs (4,rightelevator2);
	polfs (4,rightwing1);
	polf (3,rightwing2);
	    moves (98,24,31);
	    draws (98,24,40);
	    color (green0);
	    pnts (98,24,31);
    closeobj ();

    makeobj (obj++);	/* above, left, behind		*/
	color (silver0);
	polfs (4,rightelevator1);
	color (silver1);
	polfs (4,rightelevator2);
	color (silver0);
	polfs (4,rightwing1);
	color (silver1);
	polf (3,rightwing2);
	    moves (98,24,31);
	    draws (98,24,40);
	    color (green0);
	    pnts (98,24,31);

	color (C_UNDERBODY);	/*	bottom front to back	*/
	polfs (5,B4);
	color (C_RIGHTRUDDER);	/*	right side front to back 	*/
	polfs (4,R4);

	color (C_RIGHTRUDDER);	/*	left side front to back  	*/
	polfs (3,L1);
	polfs (4,L2);
	polfs (5,L3);
	polfs (4,L4);
	color (C_TOPBUBBLE);
	polfs (4,T8);
	polfs (4,T7);
	polfs (4,T9);
	color (C_UNDERBODY);
	polys (4,T8);
	polys (4,T7);
	polys (4,T9);

	color (silver0);	/* top front to back */
	polfs (3,T1);
	color (silver0);
	polfs (4,T2);
	color (C_TOPBACK);
	polfs (4,T3);
	color (C_RIGHTRUDDER);
	polfs (4,T5);
	color (C_RIGHTRUDDER);
	polfs (4,T6);
	color (C_TOPBACK);
	polfs (4,T4);
	color (silver0);
	polfs (4,T10);
	color (silver0);
	polfs (4,T14);
	color (silver0);
	polfs (4,T15);
	polfs (4,T16);
	color (C_TOPBACK);
	polfs (5,T17);
	color (C_TOPBACK);
	polfs (4,T13);

	color (C_RIGHTRUDDER);
	polfs (4,rudder);
	    color (white);
	    pnts (0,64, 140);
	color (silver0);
	polfs (4,leftelevator1);
	color (silver1);
	polfs (4,leftelevator2);
	color (silver0);
	polfs (4,leftwing1);
	color (silver1);
	polf (3,leftwing2);
	    moves (-98,24,31);
	    draws (-98,24,40);
	    color (red);
	    pnts (-98,24,31);
    closeobj ();

    makeobj (obj++);	/* above, right, behind		*/
	color (silver0);
	polfs (4,leftelevator1);
	color (silver1);
	polfs (4,leftelevator2);
	color (silver0);
	polfs (4,leftwing1);
	color (silver1);
	polf (3,leftwing2);
	    moves (-98,24,31);
	    draws (-98,24,40);
	    color (red);
	    pnts (-98,24,31);


	color (C_UNDERBODY);	/*	bottom front to back	*/
	polfs (5,B4);
	color (C_RIGHTRUDDER);	/*	left side front to back 	*/
	polfs (4,L4);

	color (C_RIGHTRUDDER);	/*	right side front to back 	*/
	polfs (3,R1);
	polfs (4,R2);
	polfs (5,R3);
	polfs (4,R4);

	color (C_TOPBUBBLE);
	polfs (4,T9);
	polfs (4,T7);
	polfs (4,T8);
	color (C_UNDERBODY);
	polys (4,T9);
	polys (4,T7);
	polys (4,T8);

	color (silver0);	/*  top front to back 	*/
	polfs (3,T1);
	color (silver0);
	polfs (4,T2);
	color (C_TOPBACK);
	polfs (4,T3);
	color (C_RIGHTRUDDER);
	polfs (4,T5);
	color (C_RIGHTRUDDER);
	polfs (4,T6);
	color (C_TOPBACK);
	polfs (4,T4);
	color (silver0);
	polfs (4,T10);
	color (silver0);
	polfs (4,T14);
	color (silver0);
	polfs (4,T15);
	polfs (4,T16);
	color (C_TOPBACK);
	polfs (5,T17);
	color (C_TOPBACK);
	polfs (4,T13);

	color (silver0);
	polfs (4,rightelevator1);
	color (silver1);
	polfs (4,rightelevator2);
	color (silver0);
	polfs (4,rightwing1);
	color (silver1);
	polf (3,rightwing2);
	    moves (98,24,31);
	    draws (98,24,40);
	    color (green0);
	    pnts (98,24,31);
	color (C_RIGHTRUDDER);
	polfs (4,rudder);
	    color (white);
	    pnts (0,64, 140);

    closeobj ();

    makeobj (obj++);		/* real far away	*/
	color (silver1);
	polfs (3,fakewing);
	color (C_RIGHTRUDDER);
	polfs (4,rudder);
	polfs (3,fakeside);
	    color (red);
	    pnts (-98,24,31);
	    color (white);
	    pnts (0,64, 140);
	    color (green0);
	    pnts (98,24,31);
    closeobj ();

    makeobj (obj++);		/* shadow	*/
	color (black);
	setpattern(3);
	polfs (4,rudder);
	polfs (4,rightelevator1);
	polfs (4,rightelevator2);
	polfs (4,rightwing1);
	polf (3,rightwing2);
	polfs (4,leftelevator1);
	polfs (4,leftelevator2);
	polfs (4,leftwing1);
	polf (3,leftwing2);
	polfs (4,L4);
	polfs (5,L3);
	polfs (4,L2);
	polfs (3,L1);
	polfs (4,R4);
	polfs (5,R3);
	polfs (4,R2);
	polfs (3,R1);
	polfs (8,T0);
	setpattern(0);
    closeobj ();

    makeobj (obj+100);		/* shadow far away	*/
	color (black);
	setpattern(3);
	polfs (3,fakewing);
	polfs (4,rudder);
	polfs (3,fakeside);
	setpattern(0);
    closeobj ();
}
