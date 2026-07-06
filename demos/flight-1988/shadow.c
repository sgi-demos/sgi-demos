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

/*	SHADOW.C	*/
#include "flight.h"
#include "iconize.h"
#include <stdio.h>

short debug,hud,threat_mode;		/* debug flag		*/
int dist_for_lines;			/* distance to draw building lines */
int number_planes;			/* number of planes in game	*/
float eye_x, eye_y, eye_z;		/* eye position		*/
float (*my_ptw)[4];			/* pointer to my matrix	*/
int daytime;		/* TRUE if daytime colormap	*/

#ifdef _4D
int int_tps = 20;
float tps = 20.0;
#else
int tps = 20;
#endif


main (argc,argv)
    int argc;
    char *argv[];
{
    short type,val,		/* queue reading variables	*/
	timeit;			/* TRUE if timing the loop	*/

    int plane_fov, tower_fov,	/* plane, tower field of view	*/
	view_switch,		/* <0 (none), 1 (plane), 2 (tower) */
	view_angle,		/* rotation of pilot's head	*/
	tick_counter;		/* counts the loop ticks	*/
    long missile_target;	/* plane to watch		*/
    register int itemp;		/* temp integer variable	*/
    float pilot_y,pilot_z;
    float temp;				/* temp float variable	*/

    register Plane pp;		/* my plane data structure	*/

    while (--argc > 0 && **++argv == '-') {
	register char *token;
	extern char *infile,*outfile;

	for (token = argv[0] + 1; *token; token++) 
	switch (*token) {
	    case 'i':
		if (--argc > 0) infile = *++argv;
		break;
	    default:
		fprintf (stderr,"illegal option %c\n", *token);
		break;
	}
    }
    if (argc > 1) {
	fprintf (stderr,"Usage: shadow [-i filename]\n");
	exit (0);
    }

    eye_x = -1950.0;
    eye_y = 400.0;
    eye_z = -3150.0;
    pilot_y = -10.0;
    pilot_z = 22.0;
    prefposition(0, XMAXSCREEN, 0, YMAXSCREEN);
    init_graphics ("shadow");

    InitComm ("shadow");
    make_c150 (C150);
    make_b747 (B747);
    make_f15 (F15);
    make_f16 (F16);
    make_f18 (F18);
    make_p38 (P38);
    make_f16w(F16W);
    make_p38w(P38W);
    number_planes = 0;

start:
#define PLANE_VIEW 1
#define TOWER_VIEW 2
    view_switch = PLANE_VIEW;			/* view from plane	*/
    plane_fov = tower_fov = 400;
    make_my_objects (plane_fov);
    view_angle = 0;
    debug = timeit = FALSE;

    display_help ();
    map_daynight (daytime = TRUE);

    /* read network buffers	*/
    for (itemp=0; itemp<16; itemp++) get_indata (1);
    qdevice(REDRAW);
    qdevice(WINQUIT);	/* in case of quit while an icon */
    qenter(REDRAW);
    qenter (KEYBD,'t');

    /****************************************************************
    /*	Main loop
    /****************************************************************/
    while (1) {
	/* read all queue entries	*/
        while (qtest ()) {
	    type = qread (&val);
   	    if (type == REDRAW) {
doredraw:
			make_my_objects(view_switch == TOWER_VIEW ? 
				tower_fov : plane_fov);
	    }
   	    else if (type == WINQUIT)
			goto end_of_program;
	    else if (type == KEYBD) {
		if (val == 27)
			goto end_of_program;
		else if(val == 18) 
			goto doredraw;	/* ^R; wsh bleeds through sometimes when scrolling */
		else if(val == 26) 
			stopit();	/* ^Z suspends (iconizes) the game */
		else if (val == 'z' || val == 'x') {
		    if (view_switch == TOWER_VIEW) {
			if (val == 'x')
			then {if (tower_fov > 30) then tower_fov -= 25;}
			else if (tower_fov < 600) then tower_fov += 25;
			make_my_objects (tower_fov);
		    }
		}
		else if (val == 'd') {
		    if (view_switch == PLANE_VIEW) {
			view_switch = TOWER_VIEW;
			make_my_objects (tower_fov);
		    }
		    else if (view_switch == TOWER_VIEW) {
			view_switch = PLANE_VIEW;
			make_my_objects (plane_fov);
		    }
		}
		else if (val == 't') {	/* get next plane in array	*/
		    static int index = -1;

		    if (planes[++index]->alive <= 0) index = 1;
		    missile_target = PLANE_ID(planes[index]);
		}
		else if (val == 'n') then map_daynight (daytime = !daytime);
		else if (val == 'h') then display_help ();
		else if (val == 'r') then goto start;
		else if (val == 'p') then wait_for_input ();
		else if (val == 'T') threat_mode = !threat_mode;
		else if (val == '?') {
		    timeit = !timeit;
		    tick_counter = TPS;
		}
#ifdef DEBUG
		else if (val >= '0' && val <= '9')
		then debug ^= 1 << (val-'0');
#endif
	    }
	    else if (val) {	/* only read button down presses	*/
		if (type == LEFTARROWKEY && view_switch == PLANE_VIEW) {
		    view_angle += 900;
		    if (view_angle > 1800) then view_angle -= 3600;
		}
		else if (type == RIGHTARROWKEY && view_switch == PLANE_VIEW) {
		    view_angle -= 900;
		    if (view_angle < -1800) then view_angle += 3600;
		}	/* and ignore any other types	*/
	    }
	}

	get_indata (1);			/* read network packets	*/
	/* set pointers to incoming data buffers	*/
	pp = lookup_plane (missile_target);
	if (pp == NULL) {		/* if its not there, use first	*/
	    missile_target = PLANE_ID(planes[0]);
	    pp = lookup_plane (missile_target);
	}
	if (pp == NULL) {		/* if its still not there	*/
	    pp = planes[0];
	    strcpy (pp->myname,"no one");
	    pp -> x = START_X;
	    pp -> y = START_Y;
	    pp -> z = START_Z;
	    pp -> elevation = 0;
	    pp -> twist = 0;
	    pp -> azimuth = START_AZIMUTH;
	    pp -> type = F15;
	}
	else {				/* swap pp and planes[0]	*/
	    *(find_plane(pp)) = planes[0];
	    planes[0]=pp;
	}

	/****************************************************************
	/* set up windshield, push the ortho, and load perspective
	/****************************************************************/
	callobj (SETUP_WORLD);
	if (view_switch == TOWER_VIEW) {	/* view from the tower	*/
	    my_lookat (eye_x,eye_y,eye_z, pp->x,pp->y,pp->z);
	    callobj (WORLD_OBJECT);	/* draw the world	*/
	    callobj (RUNWAY_STRIPES);
	    if (!daytime) then callobj (LIGHTS);
	    popmatrix();
	    draw_vasi (pp);		/* show VASI lights	*/
	    draw_buildings(eye_x, eye_y, eye_z, 0,number_planes);
	    draw_missiles ();
	}
	else if (view_switch == PLANE_VIEW) {	/* view from the plane	*/
	    if (view_angle != 0) then rotate (-view_angle,'y');
	    translate (0.0, pilot_y, pilot_z);	/* pilot's seat loc.	*/
	    rotate (-pp -> twist,'z');
	    rotate (-pp -> elevation,'x');
	    rotate (-pp -> azimuth,'y');
	    translate (-pp -> x, -pp -> y, -pp -> z);
	    callobj (WORLD_OBJECT);		/* draw the world	*/
	    if (pp->x*pp->x + pp->y*pp->y + pp->z*pp->z < 15000.0*15000.0)
	    then callobj (RUNWAY_STRIPES);
	    else callobj (FAKE_STRIPES);
	    if (!daytime) then callobj (LIGHTS);
	    popmatrix();
	    draw_vasi (pp);			/* show VASI lights	*/
	    draw_buildings (pp -> x, pp -> y, pp -> z, 1,number_planes);
	    draw_missiles ();
	    callobj (CROSS_HAIRS);	/* pop back to ortho, draw cross */
	    if (view_angle == 0) charstr ("Front view of ");
	    else if (view_angle == 900) then charstr ("Left view of ");
	    else if (view_angle == -900) then charstr ("Right view of ");
	    else charstr ("Back view of ");
	    charstr(pp->myname);
	    if (view_angle == 0) {
		setlinestyle (1);
		recti (-40,-20,40,20);
		setlinestyle (0);
	    }
	}
	draw_messages ();
	if (timeit) {
	    tick_counter--;
	    if (tick_counter == 0) {
		tick_counter = TPS;
		viewport (0,100,0,100);
		color (0);
		clear ();
	    }
	}
	swapbuffers ();
    }

end_of_program:
    ExitComm ();
    gexit ();
}

addplane ()
{
    number_planes++;
}

delplane ()
{
    return (--number_planes);
}

make_my_objects (fov)
    register int fov;
{
    float sin,cos;

    makeobj (SETUP_WORLD);
	viewport (0,XMAXSCREEN,0,YMAXSCREEN);
	ortho2 (-200.0,200.0,-100.0,100.0);
	perspective (fov,XMAXSCREEN/(float)YMAXSCREEN,2.0,1.0e6);
    closeobj ();

    fov >>= 1;		/* half field of view	*/
    gl_sincos (fov,&sin,&cos);
    dist_for_lines = 25 * 200/3 * cos/sin;
    dist_for_lines >>= 5;
    dist_for_lines *= dist_for_lines;
}

redraw_screen ()
{
}

display_help ()
{
#define HEADER(vnum)\
"          SGI Flight Simulator Shadower Version vnum"
    static char *helpmsg[] = {
HEADER_VERSION,
" ",
"This program shadows another plane that is playing  dogfight.  You  cannot",
"control  the  plane,  you  can only control your view from the plane.  The",
"left and right  arrow  keys  rotate  your  head  90 degrees left and right",
"when viewing from the plane, check the upper left of the screen for status",
"Press any character to continue",
" ",
"                     Keyboard commands",
"                     -------- --------",
"  t   - track next plane           n  - toggle day/night time",
"  d   - toggle tower/plane view    x  - zoom in (tower view)",
"  r   - restart the game           z  - zoom out (tower view)",
"  ESC - quit                       h  - display help and pause",
"  ^R  - redraw screen              ^Z - suspend (iconize) game",
""
    };
    display_message (helpmsg);
}

stopit()
{
	int mousex, mousey;
	extern PSFILE *PostScript;

	/* do most of same stuff as when we exit in ExitComm() */
    replacecolors();
	mousex = getvaluator(MOUSEX);	/* save mouse position */
	mousey = getvaluator(MOUSEY);

	flipiconic(winget());

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

    init_graphics ("shadow");
	map_daynight (daytime);

	/* restore mouse position */
	setvaluator(MOUSEX, mousex, 0,XMAXSCREEN);
	setvaluator(MOUSEY, mousey, 0,YMAXSCREEN);

	winpop();	/* make sure at top! */
	qenter(REDRAW);
}
