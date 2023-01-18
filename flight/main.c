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

/**************************************************************************
 *									  *
 * 		 Copyright (C) 1983, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"

Plane planes[MAX_PLANES];

int main (int argc, char **argv)
{
	flight(argc,argv);
}

reset_meters ()
{
    makeobj (RADAR);
    closeobj ();
    clear_report_card ();
    if (!hud) {
	callobj (CLEAR_TEXT_DISPLAY);
	callobj (CLEAR_METERS);		/* clear all the meters		*/
	callobj (CLEAR_FUEL_METER);
	editobj (HORIZON_METER);
	    objreplace (HORIZON_EDIT);
	    rotate (0,'z');
	    translate (0.0,0.0,0.0);
	    objreplace (YAW_EDIT);
	    translate (0.0,0.0,0.0);
	closeobj ();
	callobj (HORIZON_METER);
    }
}

reset_fov (fov)
    int fov;
{
    float ar,sin,cos;

    editobj (SETUP_WORLD);
    objreplace (FOV_EDIT);
    if (hud)
    then ar = (XMAXSCREEN+1.0)/(YMAXSCREEN+1.0);
    else ar = (XMAXSCREEN-1.0)/(YMAXSCREEN-YMIDDLE);
    perspective (fov,ar,2.0,1.0e6);
    closeobj ();
    fov >>= 1;		/* half field of view	*/
    gl_sincos (fov,&sin,&cos);
    dist_for_lines = 25 * 200/3 * cos/sin;
    if (hud) then dist_for_lines *= 2;
    dist_for_lines >>= 5;
    dist_for_lines *= dist_for_lines;
}

display_score ()
{
    char *plane_name, **msg;
    int i;
    Plane p,*pp;
    static char *score_msg[MAX_PLANES+6];

    /* init the array first	*/
    if (score_msg[0] == NULL) {
	msg = score_msg;
	*msg++ = "               Score Board";
	*msg++ = " ";
	*msg++ = "            Name Plane  Won Lost  Score";
	*msg++ = "---------------- -----  --- ----  -----";
	for (i=0; i < MAX_PLANES+2; i++)
	    *msg++ = (char *) malloc (strlen(score_msg[2])+1);
    };

    msg = &score_msg[4];
    FOR_EACH_PLANE (p,pp) {
	switch (p -> type) {
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
	    case F16W:
		plane_name = F16_NAME;
		break;
	    case F18:
		plane_name = F18_NAME;
		break;
	    case P38:
	    case P38W:
		plane_name = P38_NAME;
		break;
	}
	sprintf (*msg++,"%16s %5s  %3d %4d  %5d",
		p -> myname, plane_name,
		p -> won, p -> lost, p -> won - p -> lost);
    }
    sprintf (*msg++," ");
    sprintf (*msg++,"Press any character to continue.");
    **msg = '\0';
    display_message (score_msg);
}
#define DY 14

void
make_crash (msg)
    char *msg;
{
    int y;
    Plane p;

    p = planes[0];		/* a bold assumption		*/
    if (p -> status <= MEXPLODE) then return;
    p -> lost++;		/* increment my lost count	*/
    p -> status = MEXPLODE;

    y = METER_LLY-40-DY;
    if (hud) {
	makeobj (CLEAR_TEXT_DISPLAY);
	    color (white);
	    cmov2s (50,y);
	    charstr (msg);	/* crash message		*/
	closeobj ();
    }
    else {
	cursoff ();
	frontbuffer (TRUE);
	pushmatrix ();
	pushviewport ();
	callobj (CLEAR_REPORT_CARD);	/* just in case, also set up	*/
	color (white);
	cmov2s (50,y);
	charstr (msg);
	popmatrix ();
	popviewport ();
	frontbuffer (FALSE);
	curson ();
    }
}

clear_report_card ()
{
    if (hud) {
    	if (isobj(CLEAR_TEXT_DISPLAY))
	    delobj(CLEAR_TEXT_DISPLAY);		/* delete all text messages */
    }
    else {
	cursoff ();
	frontbuffer (TRUE);	/* clear report card from both buffers	*/
	callobj (CLEAR_REPORT_CARD);
	frontbuffer (FALSE);
	curson ();
    }
}

int report_card (descent, roll, vx, vz, wheels, p)
    int descent, vx, vz;
    int roll, wheels;
    Plane p;
{
    short on_runway;
    int azimuth,rating,y;
    float xdist,zdist;
    char charbuf[80];

    azimuth = p -> azimuth;
    on_runway = IN_BOX (p, -100.0, 100.0, -8500.0, 0.0);

    roll /= 10;
    if (roll > 180) roll -= 360;
    rating = 1;

    if (hud) makeobj (CLEAR_TEXT_DISPLAY);	/* put text in object	*/
    else {
	cursoff ();
	frontbuffer (TRUE);
	callobj (CLEAR_REPORT_CARD);	/* just in case, also set up	*/
    }
    color (white);
    y = METER_LLY-40-DY;

    cmov2s (50,y);
    charstr ("Landing Report Card:");
    sprintf (charbuf,"Rate of descent: %d fpm", descent * 60);
    cmov2s (50,y-DY);
    charstr (charbuf);
    sprintf (charbuf,"Roll angle: %d", roll);
    cmov2s (50,y-2*DY);
    charstr (charbuf);
    sprintf (charbuf,"Air speed: %d knots", vz);
    cmov2s (50,y-3*DY);
    charstr (charbuf);

    if (!wheels) {
	cmov2s (500,y);
	charstr ("*** Landed with the landing gear up!");
	rating = 0;
    }
    if (descent > 10) {
	cmov2s (350,y-DY);
	charstr ("*** Descending too fast!");
	rating = 0;
    }
    if (roll < 0) then roll = -roll;
    if (roll > 10) {
	cmov2s (350,y-2*DY);
	charstr ("*** Too much roll!");
	rating = 0;
    }
    if (!on_runway) {
	sprintf (charbuf,"*** Landed off the runway!");
	cmov2s (350,y-3*DY);
	charstr (charbuf);
	rating = 0;
    }
    else if (vx > 10 || vx < -10) {
	sprintf (charbuf,"*** Too much drifting: %d fps",vx);
	cmov2s (350,y-3*DY);
	charstr (charbuf);
	rating = 0;
    }
    if (roll > 20 || descent > 20 || vx > 20 || vx < -20) then rating = -1;

    cmov2s (250,y);
    if (rating == 1) {		/* good landing => rate it	*/
	sprintf (charbuf,"Sideways speed: %d fps",vx);
	cmov2s (650,y);
	charstr (charbuf);

	if (azimuth < 900 || azimuth > 2700)
	then zdist = -1075.0 - p -> z;
	else zdist = -7425.0 - p -> z;
	xdist = fabs(p -> x);

	sprintf (charbuf,"Distance from centerline: %d",(int)xdist);
	cmov2s (650,y-DY);
	charstr (charbuf);

	zdist = fabs(zdist);
	sprintf (charbuf,"Distance from touchdown: %d",(int)zdist);
	cmov2s (650,y-2*DY);
	charstr (charbuf);

	if (azimuth > 2700) then azimuth = 3600-azimuth;
	else if (azimuth > 900) then azimuth = 1800 - azimuth;
	if (azimuth < 0) then azimuth = -azimuth;
	azimuth /=10;
	sprintf (charbuf,"Heading error: %d degrees",azimuth);
	cmov2s (650,y-3*DY);
	charstr (charbuf);

	if (vx < 0) then vx = -vx;
	rating = 100 - descent - roll - azimuth - (vx>>1)
		    -(int)(.01 * zdist) - (int)(.1 * xdist);
	if (rating < 0) then rating = 0;
	cmov2s (250,y);
	sprintf (charbuf, "Nice landing! (%d/100)", rating);
	charstr (charbuf);
    }
    else if (rating == 0) then charstr ("CRASH LANDING! (0/100)");
    else {
	charstr ("EXPLODED ON IMPACT!");
	broadcast ("exploded on impact");
    }

    if (hud) then closeobj();
    else {
	frontbuffer (FALSE);
	curson ();
    }
    return (rating);
}

/* check my missile against other planes	*/
void
check_missile (p)
    Plane p;
{
    char buf[NAME_LENGTH+32];
    Plane ptest,*pp;
    long last_kill;

    last_kill = p -> mkill;
    FOR_EACH_PLANE (ptest,pp)
	if (p != ptest && test_blow_up (p,ptest)) {
	    p -> mkill = PLANE_ID (ptest);
	    if (last_kill == NULL_PLANE_ID) {
		p -> mx = .2 * p -> mx + .8 * ptest -> x;
		p -> my = .2 * p -> my + .8 * ptest -> y;
		p -> mz = .2 * p -> mz + .8 * ptest -> z;
	    }
	    if (p -> mkill != last_kill) {	/* debounce	*/
		extern char *WEAPON_NAME[];

		p -> won++;
		sprintf (buf,"destroyed %s with a %s",
			    ptest -> myname,WEAPON_NAME[p -> mtype]);
		broadcast (buf);
	    }
	    return;
	}
}

int test_blow_up (m,p)
    Plane m,p;
{
    int dx,dy,dz;
    static int MDIST[] = {250,350,150};

    /* if the plane is not exploding	*/
    if (p -> status > MEXPLODE) {
	dx = m -> mx - p -> x;
	dy = m -> my - p -> y;
	dz = m -> mz - p -> z;
	if (dx < 0) then dx = -dx;
	if (dy < 0) then dy = -dy;
	if (dz < 0) then dz = -dz;
	if (dx + dy + dz < MDIST[m -> mtype]) {
	    if (m -> mstatus > MEXPLODE) then m -> mstatus = MEXPLODE;
	    return (TRUE);
	}
    }
    return (FALSE);
}

/* find and return the closest plane to me	*/
Plane find_closest_plane (myp)
    Plane myp;
{
    float myx,myy,myz;
    float dx,dy,dz, d,dbest;
    Plane p,*pp,pbest;

    pbest = NULL;
    dbest = 1e30;
    myx = my_ptw[2][0];
    myy = my_ptw[2][1];
    myz = my_ptw[2][2];

    FOR_EACH_PLANE (p,pp)		/* for each plane	*/
    /* if its not me, not exploding, above 150 feet, not C150	*/
    if (p != myp && p -> status > MEXPLODE && 
	p -> y > 150.0 && p -> type != C150)
    {
	dx = myp -> x - p -> x;		/* compute distance	*/
	dy = myp -> y - p -> y;
	dz = myp -> z - p -> z;
	d = sqrt(dx*dx + dy*dy + dz*dz);

	if ((myx*dx + myy*dy + myz*dz)/d > .988) {
	    if (d < dbest) {		/* and compare with best */
		dbest = d;
		pbest = p;
	    }
	}
    }
    return (pbest);
}
