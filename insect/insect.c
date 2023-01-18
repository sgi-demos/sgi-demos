/* 8/29/88 dbl David B. Ligon
*   . inserted code changes to run in color map mode on 8 bit plane Eclipse
*   as well as 24 bit plane machine.
*   . saves existing color map and restores on exit.
*   . will now take and scale input for window anywhere on screen also allows
*   moving and scaling of windows (REDRAW).
*   . compiled with shared libraries.
*/

#include <stdio.h>
#include <stdlib.h>
#include <gl.h>
#include <math.h>
#include <device.h>
#include <democolors.c>
#include "insect.h"

Linestyle ls = 0xaaaa;

short   halftone[] = {
    0x5555, 0xaaaa, 0x5555, 0xaaaa,
    0x5555, 0xaaaa, 0x5555, 0xaaaa,
    0x5555, 0xaaaa, 0x5555, 0xaaaa,
    0x5555, 0xaaaa, 0x5555, 0xaaaa
};

Coord sdepth = 10.;
float   light[3],
        phi = PI / 4.0,
        theta = PI / 4.0;
Angle ctheta = -900, cphi, cvtheta, cvphi;
float   fabso ();

static const short tilt_horiz_center = 0;
static const short tilt_horiz_span = 200;
static const short tilt_vert_center = 320;
static const short tilt_vert_span = 200;

/*	main routine -- handle tokens of window manager
		-- display shadow and insect
*/

/* Changes for ECLIPSE 8 bit machine */
/*  don't use 7 and 8 for appearances. These are the text standards */
Colorindex ECLIPSE8_RAMP[10] = {4, 5, 6, 8, 9, 10, 11, 12, 13, 14};
long nplanes;
short savearray[384];

/** change for new window control */
float halfwinx, halfwiny;
long worgx, worgy;
long wsizex, wsizey;
long pikx, piky;


int main (argc, argv)
int	argc;
char	*argv[];
{
 
    int     i,
            j,
            k;
    short   dev,
            val;
    Boolean attached;

    follow = TRUE;
	{
		char *t, *strrchr();
		winopen((t=strrchr(argv[0], '/')) != NULL ? t+1 : argv[0]);
	}
    getsize (&wsizex, &wsizey);
    getorigin (&worgx, &worgy);
    halfwinx = (float)wsizex / 2.0;
    halfwiny = (float)wsizey / 2.0;

    glcompat(GLC_OLDPOLYGON, FALSE);	/* this is only significant on a GT */

    shademodel(FLAT);

    defpattern (HALFTONE, 16, (uint16_t *) halftone);
    deflinestyle (HALFTONE, ls);
    getlightvector ();

/* Changes for ECLIPSE 8 bit machine */
    doublebuffer ();
    gconfig ();

    nplanes = getplanes();
    /* save color map in savearray */
    if (nplanes == 4)
	savemap (savearray,0,15);
    else
	savemap (savearray,0,127);

    createobjects ();
/* end of changes */

    setupcolors ();

/* Changes for ECLIPSE 8 bit machine */
    if (nplanes == 4)
	color (ECLIPSE8_SKYBLUE);
    else 
	color (SKYBLUE);

    clear ();
    swapbuffers ();
    clear ();
    reshapeviewport ();
    fixwindow ();
    qdevice (INPUTCHANGE);
    qdevice (REDRAW);
    qdevice (ESCKEY);
    qdevice (CTRLKEY);
    qdevice (FKEY);
    qdevice (LEFTMOUSE);
    qdevice (MIDDLEMOUSE);

    qdevice (LEFTARROWKEY);
    qdevice (RIGHTARROWKEY);
    qdevice (DOWNARROWKEY);
    qdevice (UPARROWKEY);

/* Queue WINQUIT to restore color map after program -
new for ECLIPSE 8 bit machine  */
    qdevice (WINQUIT);

    getstuff ();

    spin_scene ();
    move_insect ();
    dolegs ();
    frontbuffer (TRUE);

    /* new for ECLIPSE 8 bit version */
    if (nplanes == 4)
	color (ECLIPSE8_SKYBLUE);
    else 
	color (SKYBLUE);

    clear ();
    gflush ();
    callobj (viewit);
    callobj (screen);
    draw_shadow ();
    draw_insect ();
    frontbuffer (FALSE);

    while (TRUE) {

	while (qtest ()) {
	    dev = qread (&val);
	    switch (dev) {
		case ESCKEY:
			if (val) break;

		/* new for ECLIPSE 8 bit machine */
		case WINQUIT: 
		    /* restore color map */
		    if (nplanes == 4)
			restoremap(savearray,0,15);
		    else
			restoremap(savearray,0,127);
			gexit();
		    exit (0);
		    break;
		case INPUTCHANGE: 
		    attached = val;

		    /* new for ECLIPSE 8 bit */
		    if (nplanes == 4)
			color (ECLIPSE8_SKYBLUE);
		    else 
			color (SKYBLUE);

		    clear ();
		    gflush ();
		    callobj (viewit);
		    callobj (screen);
		    draw_shadow ();
		    draw_insect ();
		    break;
		case REDRAW: 
		    reshapeviewport ();
		    fixwindow ();
		    frontbuffer (TRUE);

		    /* new for ECLIPSE 8 bit */
		    if (nplanes == 4)
			color (ECLIPSE8_SKYBLUE);
		    else 
			color (SKYBLUE);

		    clear ();
		    gflush ();
		    callobj (viewit);
		    callobj (screen);
		    draw_shadow ();
		    draw_insect ();
		    frontbuffer (FALSE);
		    break;
		case FKEY: 
		    if (val) {
			follow = !follow;
		    }
		    break;

                case LEFTARROWKEY: printf("left\n"); break;
                case RIGHTARROWKEY: printf("right\n"); break;
                case DOWNARROWKEY: printf("down\n"); break;
                case UPARROWKEY: printf("up\n"); break;
	    }
            swapbuffers();
	}
	if (attached) {

	    /* new for ECLIPSE 8 bit machine */
	    if (nplanes == 4)
		color (ECLIPSE8_SKYBLUE);
	    else 
		color (SKYBLUE);

	    clear ();
	    gflush ();

	    spin_scene ();
	    move_insect ();
	    dolegs ();
	    callobj (viewit);
	    callobj (screen);
	    draw_shadow ();
	    draw_insect ();
	}
	    swapbuffers ();	    
    }

}

/*  setupcolors  -- load color map		*/

/* Changed for ECLIPSE 8 bit machine */
    setupcolors () {
    if (nplanes > 4) {
	mapcolor (GRAY, 128, 128, 128);
	mapcolor (GRID, 128, 200, 250);
	mapcolor (SKYBLUE, 50, 50, 150);
	makerange (RAMPB5, RAMPE5, 125, 250, 125, 250, 0, 0);
	makerange (RAMPB4, RAMPE4, 100, 200, 125, 250, 0, 0);
	makerange (RAMPB3, RAMPE3, 75, 150, 125, 250, 0, 0);
	makerange (RAMPB2, RAMPE2, 50, 100, 125, 250, 0, 0);
	makerange (RAMPB, RAMPE, 25, 50, 125, 250, 0, 0);
    } else {
	mapcolor (ECLIPSE8_GRAY, 128, 128, 128);
	mapcolor (ECLIPSE8_GRID, 128, 200, 250);
	mapcolor (ECLIPSE8_SKYBLUE, 50, 50, 150);
	make_eclipse8_range(ECLIPSE8_RAMP, 25, 250, 125, 250, 0, 0);
    }

    cx = 0.0;
    cy = 10.0;
    cz = -2.0;
    cvx = cvy = cvz = 0.0;
    ctheta = -900;
    cphi = 0;
}


/*  makerange  -- color ramp utilities		*/
makerange (a, b, r1, r2, g1, g2, b1, b2)
Colorindex a, b;
RGBvalue r1, r2, g1, g2, b1, b2;

{
    float   i;
    int     j;
    float   dr,
            dg,
            db;

    i = (float) (b - a);
    dr = (float) (r2 - r1) / i;
    dg = (float) (g2 - g1) / i;
    db = (float) (b2 - b1) / i;

    for (j = 0; j <= (int) i; j++)
	mapcolor ((Colorindex) j + a,
		(int) (dr * (float) j + r1),
		(int) (dg * (float) j + g1),
		(int) (db * (float) j + b1));
/*	mapcolor ((Colorindex) j + a,
		(RGBvalue) (dr * (float) j + r1),
		(RGBvalue) (dg * (float) j + g1),
		(RGBvalue) (db * (float) j + b1));
*/
}


/*  fix window  -- change view of insect if size of window is reshaped  */
fixwindow () {
    float   i,
            j;

    getsize (&wsizex, &wsizey);
    i = (float) (wsizex);
    j = (float) (wsizey);

    /** change for window control */
    getorigin (&worgx, &worgy);
    halfwinx = (float)wsizex / 2.0;
    halfwiny = (float)wsizey / 2.0;

    editobj (viewit);
    objreplace (windowtag);
    perspective ((Angle) 640, (i / j), 0.01, 131072.0);
    closeobj ();
}


/*  draw_shadow  -- draw halftone shape of insect onto the floor  */
draw_shadow () {
    int     leg;

    pushmatrix ();
    callobj (shadow);
    setpattern (HALFTONE);
    translate (px, py, 1.0);
    callobj (body_shadow);
    for (leg = 0; leg < 6; leg++) {
	pushmatrix ();
	rotate ((Angle) (-leg * 600), 'z');
	translate (0.0, 0.5, 0.0);
	callobj (hip_shadow);
	rotate (hip_phi[leg], 'z');
	rotate (hip_theta[leg], 'x');
	callobj (thigh_shadow);
	callobj (kneeball_shadow);
	translate (0.0, 1.0, 0.0);
	rotate (knee[leg], 'x');
	callobj (shin_shadow);
	popmatrix ();
    }
    setpattern (0);
    popmatrix ();
}


/*  draw_insect  -- draw rear legs, body and forelegs of insect 
	the order of drawing the objects is important to 
	insure proper hidden surface elimination -- painter's algorithm	*/
draw_insect () {
    Angle a;
    float   o;
    int     order;

    o = atan2 (cy + py, cx + px) + PI - (PI / 3.0);
    order = l05 ((int) integer (o / (PI / 3.0)));
    pushmatrix ();		/* world */
    translate (px, py, 1.0);
    draw_hind (l05 (3 - order));
    draw_hind (l05 (4 - order));
    draw_hind (l05 (2 - order));
    callobj (body);
    draw_fore (l05 (5 - order));
    draw_fore (l05 (1 - order));
    draw_fore (l05 (0 - order));
    popmatrix ();
}


/*  draw_hind  -- draw a rear leg.  First draw hip, then shin, then thigh
	and knee joint			*/
draw_hind (leg)
int     (leg);
{
    pushmatrix ();
    rotate ((Angle) (-leg * 600), 'z');
    translate (0.0, 0.5, 0.0);
    callobj (hip[leg]);
    rotate (hip_phi[leg], 'z');
    rotate (hip_theta[leg], 'x');
    pushmatrix ();		/* draw thigh */
    translate (0.0, 1.0, 0.0);
    rotate (knee[leg], 'x');
    callobj (shin[leg]);
    popmatrix ();
    if (cz < -5.0) {
	callobj (kneeball[leg]);
	callobj (thigh[leg]);
    }
    else {
	callobj (kneeball[leg]);
	callobj (thigh[leg]);
    }
    popmatrix ();
}


/*  draw_fore  -- draw a front leg.  First draw hip, then thigh,
	knee joint and finally shin		*/

draw_fore (leg)
int     leg;
{
    pushmatrix ();
    rotate ((Angle) (-leg * 600), 'z');
    translate (0.0, 0.5, 0.0);
    callobj (hip[leg]);
    rotate (hip_phi[leg], 'z');
    rotate (hip_theta[leg], 'x');
    callobj (thigh[leg]);
    callobj (kneeball[leg]);
    translate (0.0, 1.0, 0.0);
    rotate (knee[leg], 'x');
    callobj (shin[leg]);
    popmatrix ();
}


/*  spin_scene  -- poll input devices, keyboard and mouse
	move eye position based upon user input			*/

spin_scene () {
    float   sin1,
            c1,
            s2,
            c2,
            t;
    int     mx,
            my;

    editobj (viewit);
    objreplace (cposittag);
    translate (cx, cy, cz);
    objreplace (cthetatag);
    rotate (ctheta, 'x');
    objreplace (cphitag);
    rotate (cphi, 'z');
    closeobj ();


    /* big change to keep movement relative to window */
    /* check if still in window x and y are globals - see getcoords */
    getcoords ();
    mx = 64 * ((pikx - worgx) - (wsizex / 2)) / wsizex;
    my = 64 * ((piky - worgy) - (wsizey / 2)) / wsizey;


/*
    mx = (getvaluator (MOUSEX) - 640) / 16;
    my = (getvaluator (MOUSEY) - 512) / 16;
*/

    if (getbutton (LEFTSHIFTKEY)) {
	gl_sincos (ctheta, &sin1, &c1);
	gl_sincos (cphi, &s2, &c2);
	cvz -= c1;
	cvx -= s2 * sin1;
	cvy -= c2 * sin1;
    }
    else if (getbutton (CTRLKEY)) {
	gl_sincos (ctheta, &sin1, &c1);
	gl_sincos (cphi, &s2, &c2);
	cvz += c1;
	cvx += s2 * sin1;
	cvy += c2 * sin1;
    }
    else if (getbutton (LEFTMOUSE)) {
	cvz = (float) - my;
	gl_sincos (cphi, &sin1, &c1);
	cvx = c1 * (float) (-mx);
	cvy = -sin1 * (float) (-mx);
    }
    else {
	cvx = cvx * 0.7;
	cvy = cvy * 0.7;
	cvz = cvz * 0.7;
    }
    if (getbutton (MIDDLEMOUSE)) {
	cvtheta = my;
	cvphi = mx;
    }
    else {
	cvtheta += -cvtheta / 4;
	if ((cvtheta < 4) && (cvtheta > -4))
	    cvtheta = 0;
	cvphi += -cvphi / 4;
	if ((cvphi < 4) && (cvphi > -4))
	    cvphi = 0;
    }

    cx += cvx * 0.0078125;
    cy += cvy * 0.0078125;
    if (cz > 0.0) {
	cz = 0.0;
	cvz = 0.0;
    }
    else
	cz += cvz * 0.0078125;
    ctheta += cvtheta;
    cphi += cvphi;
}

Angle degrees (a)
float   a;
{
    return ((Angle) (a * 1800.0 / PI));
}


getstuff () {
    int     x,
            y,
            i;
    int     tr;

    legup[0] = FALSE;
    legup[2] = FALSE;
    legup[4] = FALSE;
    legup[1] = TRUE;
    legup[3] = TRUE;
    legup[5] = TRUE;

    px = 0.0;
    py = 0.0;
    for (i = 0; i < 6; i++) {
	legx[i] = RES_FLOAT / 2.0 + (float) i;
	legy[i] = RES_FLOAT / 2.0 + (float) i;
    }
}


dolegs () {
    int     i;
    float   r,
            l,
            gx,
            gy,
            k,
            t,
            a,
            ux,
            uy;
    int     leg,
            tr;

    for (leg = 0; leg < 6; leg++) {
	gx = legx[leg] - RES_FLOAT / 2.0;
	gy = legy[leg] - RES_FLOAT / 2.0;
	ux = gx / (RES_FLOAT / 2.0);
	uy = gy / (RES_FLOAT / 2.0);

	switch (leg) {
	    case 0: 
		gx += 0.0;
		gy += RES_FLOAT;
		break;
	    case 1: 
		gx += (RES_FLOAT * 0.8660254);
		gy += (RES_FLOAT * 0.5);
		break;
	    case 2: 
		gx += (RES_FLOAT * 0.8660254);
		gy += (RES_FLOAT * -0.5);
		break;
	    case 3: 
		gx += 0.0;
		gy += -RES_FLOAT;
		break;
	    case 4: 
		gx += (RES_FLOAT * -0.8660254);
		gy += (RES_FLOAT * -0.5);;
		break;
	    case 5: 
		gx += (RES_FLOAT * -0.8660254);
		gy += (RES_FLOAT * 0.5);
		break;
	}
	r = sqrt ((gx * gx) + (gy * gy)) / RES_FLOAT;
	l = sqrt (1.0 + (r * r));
	k = acos ((5.0 - (l * l)) / 4.0);

	knee[leg] = (Angle) degrees (k);

	t = (2.0 * sin (k)) / l;
	if (t > 1.0)
	    t = 1.0;

	a = asin (t);
	if (l < 1.7320508)
	    a = PI - a;

	hip_theta[leg] =
	    (Angle) (degrees (a - atan2 (1.0, r)));

	if (gx == 0.0) {
	    hip_phi[leg] = (Angle) (900 * sgn (gy));
	}
	else {
	    hip_phi[leg] = (Angle) (degrees (atan2 (gy, gx)));
	}
	hip_phi[leg] += (-900 + 600 * leg);

	if (legup[leg]) {
	    hip_theta[leg] += (Angle)
		(200.0 * ((fr[leg] / 2.0) - fabso (dmr[leg] - (fr[leg] / 2.0))));
	}
    }
}


move_insect () {
    register int    i;
    register float  mx,
                    my,
                    vx,
                    vy,
                    dx,
                    dy,
                    dr,
                    lx,
                    ly,
                    lr,
                    dmx,
                    dmy;
    float   s,
            c;

/*  mx = (float) getvaluator (MOUSEX) / 640.0 - 1.0;
    my = (float) getvaluator (MOUSEY) / 512.0 - 1.0;
*/

/* changed to keep input within the window.
 x and y are globals - see getcoords */
    getcoords ();
    mx = ((float)pikx - (float)worgx) / halfwinx - 1.0;
    my = ((float)piky - (float)worgy) / halfwiny - 1.0;

    /* Use accelerometer to move insect. */
    {
	float dx = (getvaluator(DIAL0) - tilt_horiz_center) / (float) tilt_horiz_span;
	float dy = (getvaluator(DIAL1) - tilt_vert_center) / (float) tilt_vert_span;
	if (dx < -0.5) dx = -0.5;
	if (dx > 0.5) dx = 0.5;
	if (dy < -0.5) dy = -0.5;
	if (dy > 0.5) dy = 0.5;
	mx += dx;
	my -= dy;
    }

    gl_sincos (cphi, &s, &c);
    dx = mx * c + my * s;
    dy = -mx * s + my * c;
    mx = dx;
    my = dy;

    px += mx / (float) (RES_INT);
    py += my / (float) (RES_INT);

    if (follow) {
	cx -= mx / (float) (RES_INT);
	cy -= my / (float) (RES_INT);
    }

    dr = sqrt (mx * mx + my * my);
    dx = mx / dr;
    dy = my / dr;

    for (i = 0; i < 6; i++) {
	lx = legx[i] - (float) (RES_INT / 2);
	ly = legy[i] - (float) (RES_INT / 2);
	lr = (float) (RES_INT / 2);
	lx = lx / lr;
	ly = ly / lr;
	dmx = (dx - lx);
	dmy = (dy - ly);
	dmr[i] = sqrt (dmx * dmx + dmy * dmy);
	if (legup[i]) {
	    dmx = 3 * dr * dmx / dmr[i];
	    dmy = 3 * dr * dmy / dmr[i];
	    legx[i] += dmx;
	    legy[i] += dmy;
	    if ((dmr[i]) < 0.15) {
		legup[i] = FALSE;
	    }
	}
	else {
	    legx[i] -= mx;
	    legy[i] -= my;

	    if (!legup[l05 (i - 1)] && !legup[l05 (i + 1)] &&
		    (dmr[i] > REACH) &&
		    ((lx * dx + ly * dy) < 0.0)) {
		legup[i] = TRUE;
		fr[i] = dmr[i];
		legx[i] += dmx;
		legy[i] += dmy;
	    }
	}
    }
}


int     sgn (i)
float   i;
{
    if (i < 0)
	return (-1);
    if (i > 0)
	return (1);
    return (0);
}


rotate60 (c, n, a)
char    c;
int     n;
Coord a[][3];
{
    int     i,
            j,
            l;
    float   nx,
            ny;

    switch (c) {
	case 'z': 
	    i = 0;
	    j = 1;
	    break;
	case 'y': 
	    i = 2;
	    j = 0;
	    break;
	case 'x': 
	    i = 1;
	    j = 2;
	    break;
    };
    for (l = 0; l < n; l++) {
	nx = a[l][i] * COS60 - a[l][j] * SIN60;
	ny = a[l][i] * SIN60 + a[l][j] * COS60;
	a[l][i] = nx;
	a[l][j] = ny;
    }
}


getpolycolor (p, pts)
int     p;
float   pts[][3];
{
    float   norm[3];
    float   v1[3],
            v2[3],
            cons;
    int     i,
            get;
    float   c;

    for (i = 0; i < 3; i++)
	norm[i] = 0.0;
    i = 0;
    get = 1;
    i = 1;
    v1[0] = pts[1][0] - pts[0][0];
    v1[1] = pts[1][1] - pts[0][1];
    v1[2] = pts[1][2] - pts[0][2];

    v2[0] = pts[2][0] - pts[0][0];
    v2[1] = pts[2][1] - pts[0][1];
    v2[2] = pts[2][2] - pts[0][2];

    norm[0] = v1[1] * v2[2] - v1[2] * v2[1];
    norm[1] = v1[2] * v2[0] - v1[0] * v2[2];
    norm[2] = v1[0] * v2[1] - v1[1] * v2[0];

    cons = sqrt ((norm[0] * norm[0]) +
	    (norm[1] * norm[1]) + (norm[2] * norm[2]));
    for (i = 0; i < 3; i++)
	norm[i] = norm[i] / cons;

    c = dot (norm, light);
    if (c < 0.0)
	c = 0.0;
    if (c > 1.0)
	c = 1.0;
    switch (p) {
	case 0: 
	    c = (float) (RAMPE - RAMPB) * c + (float) (RAMPB);
            if (((Colorindex) c) > RAMPE) c = (float) RAMPE;
	    break;
	case 1: 
	    c = (float) (RAMPE2 - RAMPB2) * c + (float) (RAMPB2);
            if (((Colorindex) c) > RAMPE2) c = (float) RAMPE2;
	    break;
	case 2: 
	    c = (float) (RAMPE3 - RAMPB3) * c + (float) (RAMPB3);
            if (((Colorindex) c) > RAMPE3) c = (float) RAMPE3;
	    break;
	case 3: 
	    c = (float) (RAMPE4 - RAMPB4) * c + (float) (RAMPB4);
            if (((Colorindex) c) > RAMPE4) c = (float) RAMPE4;
	    break;
	case 4: 
	    c = (float) (RAMPE5 - RAMPB5) * c + (float) (RAMPB5);
            if (((Colorindex) c) > RAMPE5) c = (float) RAMPE5;
	    break;
    }

    /* Changed for 8 bit ECLIPSE machine */
    if (nplanes == 4)
	c = (float)reduce_index((int)c);
    color ((Colorindex) c);	
}


lit (p, pts)
int     p;
float   pts[][3];
{
    float   norm[3];
    float   v1[3],
            v2[3],
            cons;
    int     i,
            get;
    float   c;

    for (i = 0; i < 3; i++)
	norm[i] = 0.0;
    i = 0;
    get = 1;
    i = 1;
    v1[0] = pts[1][0] - pts[0][0];
    v1[1] = pts[1][1] - pts[0][1];
    v1[2] = pts[1][2] - pts[0][2];

    v2[0] = pts[2][0] - pts[0][0];
    v2[1] = pts[2][1] - pts[0][1];
    v2[2] = pts[2][2] - pts[0][2];

    norm[0] = v1[1] * v2[2] - v1[2] * v2[1];
    norm[1] = v1[2] * v2[0] - v1[0] * v2[2];
    norm[2] = v1[0] * v2[1] - v1[1] * v2[0];

    cons = sqrt ((norm[0] * norm[0]) +
	    (norm[1] * norm[1]) + (norm[2] * norm[2]));
    for (i = 0; i < 3; i++)
	norm[i] = norm[i] / cons;

    c = dot (norm, light);
    return (c > 0.0);
};


float   dot (vec1, vec2)
float   vec1[3],
        vec2[3];

{
    float   xx;
    xx = (vec1[1] * vec2[1])
	+ (vec1[2] * vec2[2])
	+ (vec1[0] * vec2[0]);
    return ((float) xx);
}


getlightvector () {
    float   f;
    light[2] = cos (theta);
    f = sin (theta);
    light[1] = -sin (phi) * f;
    light[0] = -cos (phi) * f;
}


float   integer (x)
float   x;
{
    if (x < 0.0)
	x -= 1.0;
    x = (float) (int) x;
    return (x);
}


float   frac (x)
float   x;
{
    return (x - integer (x));
}


l05 (i)
int     i;
{
    if (i < 0)
	return (i + 6);
    if (i > 5)
	return (i - 6);
    return (i);
}


float   fabso (x)
float   x;
{
    if (x < 0.0)
	return (-x);
    else
	return (x);
}


/**** New routines for ECLIPSE 8 bit machine */

/* reduces color index value to the lower 16 indices in the color table
	see ECLIPSE8_RAMP[] for which entries are used for ramp */

reduce_index(c)
short c;
{
    c = c - RAMPB + 4;
    while (c > 13)
	c -= 10;
    if (c > 6)
	c++;
    return(c);
}


/*  Set up Eclipse 8 bit color ramp */

make_eclipse8_range(ECLIPSE8_RAMP,r1,r2,g1,g2,b1,b2)
short ECLIPSE8_RAMP[];
int r1,r2,b1,b2,g1,g2;
{
    int i;
    float rinc, ginc, binc;

    rinc = (float)(r2 - r1) / (float)ECLIPSE8_NCOLORS;
    ginc = (float)(g2 - g1) / (float)ECLIPSE8_NCOLORS;
    binc = (float)(b2 - b1) / (float)ECLIPSE8_NCOLORS;

    for (i = 0; i < ECLIPSE8_NCOLORS; i++) {
	mapcolor(ECLIPSE8_RAMP[i],
	    (short)(i * rinc + r1),
	    (short)(i * ginc + g1),
	    (short)(i * binc + b1));
    }
}


/*  Savemap saves bit map colors from c1 to c2 in the savearray.  Savearray
	should be ((c2 - c1) * 3) shorts in length. Also see Restoremap. */

savemap(savearray,c1,c2)
short savearray[];
Colorindex c1, c2;
{
    Colorindex i;
    int n;

    for (i = c1, n = 0; i <= c2; i++) {
	getmcolor(i, &savearray[n], &savearray[n+1], &savearray[n+2]);
	n += 3;
    }
}


/*  Restoremap restores the colors from c1 to c2 to the colormap. Also see
	Savemap() */

restoremap(savearray,c1,c2)
short savearray[];
Colorindex c1, c2;
{
    Colorindex i;
    int n;

    for (i = c1, n = 0; i <= c2; i++) { 
	mapcolor(i, savearray[n], savearray[n+1], savearray[n+2]);
	n += 3;
    }
}

getcoords()
{
    pikx = getvaluator(MOUSEX);
    piky = getvaluator(MOUSEY);
    if (pikx <= worgx || pikx >= worgx + wsizex || 
	piky <= worgy || piky >= worgy + wsizey) {
	pikx = worgx + wsizex / 2 + 1;
	piky = worgy + wsizey / 2 + 1;
    }
}
