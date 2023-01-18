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

/*	UFLIGHT.C	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"
#define TYPE_BUILDING 0
#define TYPE_MOUNTAIN 1
#define TYPE_THREAT 2

typedef struct building *Building;
struct building {
    int type;	/* building/mountain	*/
    int cx;
    int cy;
    int cz;

    int llx;
    int urx;
    int llz;
    int urz;
    int ury;

    int ury_obj;		/* for mountains this is THE object	*/
    int llx_obj, llx_obj1;
    int urx_obj, urx_obj1;
    int llz_obj, llz_obj1;
    int urz_obj, urz_obj1;
};

static int current_building = 0;
static int current_building_object = BUILDING_OBJECTS;
static Building buildings[MAX_BUILDINGS];

/* make all the buildings (and mountains) including data structures etc. */
make_buildings ()
{
    int ex,ey,ez;
    static mtn1[] = {	/* color delta x, delta z	*/
	36, -15000,8000,	/* lime	*/
	37, 1000,10000,
	39, 15000,6000,
	38, 1000,-8000,
	35, -15000,-8000,
    };
    static mtn2[] = {	/* color delta x, delta z	*/
	46, -10000,8000,	/* tan	*/
	47, -2000,6000,
	49, 5000,3000,
	48, 4000,-9000,
	45, -12000,-7000,
    };
    static mtn3[] = {	/* color delta x, delta z	*/
	41, -2000,5000,		/* orange	*/
	42, 1200,1500,
	43, 1000,-5000,
	40, -3000,-7000,
    };
    static mtn4[] = {	/* color delta x, delta z	*/
	45, -6000,6000,		/* tan	*/
	47, 8000,10000,
	48, 18000,-15000,
	46, -5000,-8000,
    };
    static mtn5[] = {	/* color delta x, delta z	*/
	40, -17000,10000,	/* orange	*/
	42, 8000,20000,
	43, 11000,-12000,
	41, -7000,-15000,
    };
    static mtn6[] = {	/* color delta x, delta z	*/
	35, -8000,1000,		/* lime	*/
	37, -500,4000,
	38, 2000,0,
	36, 0,-2000,
    };
    static mtn7[] = {	/* color delta x, delta z	*/
	45, -2000,5000,		/* tan	*/
	47, 1500,0,
	46, 0,-1500,
    };
    static mtn8[] = {	/* color delta x, delta z	*/
	46, -2500,8000,		/* tan	*/
	47, 8000,5000,
	48, 10000,-6000,
	45, -18000,-5000,
    };
    static mtn9[] = {	/* color delta x, delta z	*/
	40, -26000,12000,	/* orange	*/
	42, 10000,10000,
	43, 30000,0,
	44, 15000,-18000,
	41, -18000,-10000,
    };
    static mtn10[] = {	/* color delta x, delta z	*/
	19, -5000,18000,	/* grey	*/
	21, 10000,6000,
	20, 8000,-10000,
	18, -15000,-2000,
    };

    ex = eye_x;
    ey = eye_y;
    ez = eye_z;		/* note buildings are sorted from tower view	*/
    makebox (borange,	-2000,0,-3200,	100,150,100);
    makebox (btan,	-2000,0,-2400,	200,60,300);
    makebox (blime,	-1900,0,-4000,	250,50,400);
    makebox (btan,	-1800,0,-4900,	400,45,200);
    makebox (bgrey,	1000,0,-1900,	200,40,350);

    makemtn (-40000,2900,45000, 5, mtn1);
    makemtn (-2000,2200,45000, 5, mtn2);
    makemtn (5000,2000,43000, 4, mtn3);
    makemtn (16000,2400,44000, 4, mtn4);
    makemtn (41000,3600,44000, 4, mtn5);
    makemtn (15000,400,0, 4, mtn6);
    makemtn (-12000,500,-8000, 3, mtn7);
    makemtn (-28000,2300,-46000, 4, mtn8);
    makemtn (33000,2700,-37000, 5, mtn9);
    makemtn (-55000,2500,15000, 4, mtn10);

    /* threat patches are in land2.c	*/
    makethreat (6000,14000,red,17000.0);
    makethreat (-20000,15000,red,10700.0);
    makethreat (3000,34000,red,2700.0);
}

draw_missiles ()
{
    register Plane p,*pp;

    linewidth (2);
    FOR_EACH_PLANE (p,pp) {
	if (p -> mstatus) {		/* if launched		*/
	    if (p -> mstatus <= MEXPLODE) {	/* if exploding	*/
		pushmatrix();
		/* replace with balls of fire	*/
		translate (p -> mx, p -> my, p -> mz);
		callobj (EXPLOSION + p -> mstatus);
		popmatrix();
	    }
	    else {
		color (red);
		move (p -> last_mx, p -> last_my, p -> last_mz);
		draw (p -> mx, p -> my, p -> mz);
	    }
	}
    }
    linewidth (1);
}

my_lookat(vx, vy, vz, px, py, pz)
    float vx, vy, vz, px, py, pz;
{
    float sine, cosine, hyp, hyp1, dx, dy, dz;
    static Matrix mat = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

    dx = px - vx;
    dy = py - vy;
    dz = pz - vz;

    hyp = dx * dx + dz * dz;	/* hyp squared	*/
    hyp1 = sqrt (dy*dy + hyp);
    hyp = sqrt (hyp);		/* the real hyp	*/

    if (hyp1 != 0.0) {		/* rotate X	*/
	sine = -dy / hyp1;
	cosine = hyp / hyp1;
    } else {
	sine = 0.0;
	cosine = 1.0;
    }
    mat[1][1] = cosine;		/* rotate X	*/
    mat[1][2] = sine;
    mat[2][1] = -sine;
    mat[2][2] = cosine;
    multmatrix (mat);
    mat[1][1] = 1.0;
    mat[1][2] = 0.0;
    mat[2][1] = 0.0;

    if (hyp != 0.0) {		/* rotate Y	*/
	sine = dx / hyp;
	cosine = -dz / hyp;
    } else {
	sine = 0.0;
	cosine = 1.0;
    }
    mat[0][0] = cosine;		/* rotate Y	*/
    mat[0][2] = -sine;
    mat[2][0] = sine;
    mat[2][2] = cosine;
    multmatrix (mat);
    mat[0][0] = 1.0;
    mat[0][2] = 0.0;
    mat[2][0] = 0.0;
    translate (-vx,-vy,-vz); 	/* translate viewpoint */
}

Matrix shadow_matrix;

set_sun (x,y,z)
    float x,y,z;
{
    gl_IdentifyMatrix (shadow_matrix);
    shadow_matrix[1][0] = -x/y;
    shadow_matrix[1][1] =0.0;
    shadow_matrix[1][2] = -z/y;
}

draw_shadow (pp,near)
    register Plane pp;
    int near;
{
    pushmatrix ();
    multmatrix (shadow_matrix);
    if (pp == planes[0] && my_ptw != NULL)
    then multmatrix (my_ptw);	/* pre-cat ptw		*/
    else {
	translate (pp -> x, pp -> y, pp -> z);
	rotate (pp -> azimuth,'y');
	rotate (pp -> elevation,'x');
	rotate (pp -> twist,'z');
    }
    callobj (pp -> type + (near?9:110));	/* shadow object	*/
    popmatrix ();
}

/* draw the buildings from viewpoint (rx,ry,rz)	*/
draw_buildings (rx,ry,rz, start_plane, num_planes)
    float rx,ry,rz;
    int start_plane, num_planes;
{
    register int i,n,x,z;
    int ex,ey,ez;
    register int *parray;
    register int *is_plane;
    float *f;
    void **parray_tag;
    register Plane pp;
    Matrix mat;
    static int static_array[MAX_BUILDINGS+MAX_PLANES];
    static void *static_array_tag[MAX_BUILDINGS+MAX_PLANES];
    static int static_is_plane[MAX_BUILDINGS+MAX_PLANES];

    ex = rx;	ey = ry;	ez = rz;
    parray = static_array;		/* copy data into sort arrays	*/
    parray_tag = static_array_tag;
    is_plane = static_is_plane;
    n = 0;				/* count number of items	*/
    for (i = 0; i < current_building; i++) {
	Building b = buildings[i];
	z = ez - b -> cz;
	if (z < 0) then z = -z;
	x = ex - b -> cx;
	if (x < 0) x = -x;
	if (x < 1024000 && z < 1024000) {
	    x >>= 5;
	    z >>= 5;
	    n++;
	    *parray++ = x * x + z * z;
	    *parray_tag++ = b;
            *is_plane++ = 0;
	}
    }
    for (i = start_plane; i < num_planes; i++) {
	pp = planes[i];
	z = ez - (int)pp -> z;
	if (z < 0) then z = -z;
	x = ex - (int)pp -> x;
	if (x < 0) x = -x;
	if (x < 1024000 && z < 1024000) {
	    x >>= 5;
	    z >>= 5;
	    n++;
	    *parray++ = x * x + z * z;	/* flag plane with high bit	*/
	    *parray_tag++ = pp;
            *is_plane++ = 1;
	}
    }
    sink_sort (n,static_array,static_array_tag,static_is_plane);

#ifdef DEBUG
if (debug & (1<<2)) {
    printf ("start_plane: %d, num_planes: %d,   dist_for_lines: %d\n",
		start_plane,num_planes, dist_for_lines);
    printf ("--------------AFTER SORT-------------------\n");
    for (i = 0; i < n; i++) {
	x = (int) static_array_tag[i];
	printf ("%s ",x>=0?"building":"plane   ");
	x &= 0x7fffffff;			/* turn off high bit	*/
	printf ("%3d %12d\n", x,static_array[i]);
    }
}
#endif
    x = ex;	z = ez;
    /* plot the data from back to front	*/
    for (is_plane = &static_is_plane[n-1],
            parray_tag = &static_array_tag[n-1],
            parray = &static_array[n-1];
	 parray_tag >= static_array_tag;
         is_plane--,parray_tag--,parray--)
     {
         if (*is_plane) {
	    /* its a plane - compute above/below	*/
	    pp = (Plane) *parray_tag;
	    if (*parray < (dist_for_lines<<1)){	/* if close enough	*/
		n = TRUE;	    
		callobj (PUSH_IDENTITY);	/* build WTP	*/
		rotate (-pp -> twist,'z');	/* twist	*/
		rotate (-pp -> elevation,'x');	/* elevation	*/
		rotate (-pp -> azimuth,'y');	/* azimuth	*/
		translate (rx - pp -> x, ry - pp -> y, rz - pp -> z);
		getmatrix (mat);
		popmatrix ();			/* pop back to wte	*/
	    }
	    else n = FALSE;

	    if (pp->y < 5000.0)
	    then draw_shadow (pp,n);		/* show my shadow	*/
	    pushmatrix ();
	    /*if (pp == planes[0] && my_ptw != NULL)*/
	    if (FALSE)
	    then multmatrix (my_ptw);		/* pre-cat ptw		*/
	    else {
		translate (pp -> x, pp -> y, pp -> z);
		rotate (pp -> azimuth,'y');
		rotate (pp -> elevation,'x');
		rotate (pp -> twist,'z');
	    }
	    if (n) {
		n = 0;
		/* test right/left, above/below, front/behind of plane	*/
		if (mat[3][0] >= 0.0) then n += 1;
		if (mat[3][1] >= 0.0) then n += 2;
		if (mat[3][2] >= 0.0) then n += 4;
		if (pp->type == F16W) {
		    editobj(RWHEEL_ANGLE);
		    objreplace(0);
			if(pp->wheels < 5)
			then rotate(pp->wheels * 100, 'y');
			else rotate(500, 'y');
		    closeobj();

		    editobj(LWHEEL_ANGLE);
		    objreplace(0);
			if(pp->wheels < 5)
			then rotate(-pp->wheels * 100, 'y');
			else rotate(-500, 'y');
		      closeobj();
		    
		    editobj(WHEEL_ANGLE);
		    objreplace(1);
			rotate(pp->wheels * 100, 'x');
		    closeobj();
		}
		callobj (pp->type + n);	/* call appropriate plane*/
	    }
	    else callobj (pp->type + 8);
	    if (pp->status < MEXPLODE)	/* explosion if needed	*/
	    then callobj (EXPLOSION + pp->status);

	    popmatrix ();
	} else {
	    Building b = (Building) *parray_tag;
            if (b -> type == TYPE_BUILDING) {	/* its a building	*/
	    if (*parray < dist_for_lines)	/* if close enough	*/
	    then n = TRUE;			/* then draw detail	*/
	    else n = FALSE;
	    if (x < b -> llx) {
		callobj (b -> llx_obj);
		if (n) then callobj (b -> llx_obj1);
	    }
	    else if (x > b -> urx) {
		callobj (b -> urx_obj);
		if (n) then callobj (b -> urx_obj1);
	    }

	    if (z < b -> llz) {
		callobj (b -> llz_obj);
		if (n) then callobj (b -> llz_obj1);
	    }
	    else if (z > b -> urz) {
		callobj (b -> urz_obj);
		if (n) then callobj (b -> urz_obj1);
	    }

	    if (ey > b -> ury) then callobj (b -> ury_obj);
	}
	else if (b -> type == TYPE_MOUNTAIN)
	then callobj (b -> ury_obj);	/* its a mountain	*/
	else {				/* its a threat		*/
	    if (threat_mode) then callobj (b -> ury_obj);
	}
        }
    }	/* end of each object	*/
    /* always draw my shadow	*/
    if (start_plane > 0) draw_shadow(planes[0],TRUE);
}

Building new_building(type)
    int type;
{
    register Building b;

    if (current_building == MAX_BUILDINGS) {
	printf ("ERROR: too many buildings defined.\n");
	exit (1);
    }
    b = (Building) malloc (sizeof (struct building));
    buildings[current_building++] = b;
    b -> type = type;
    return b;
}

static float thcircle[] = {	/* 20 point unit circle	*/
	0.951057,0,-0.309017,
	0.809017,0,-0.587785,
	0.587785,0,-0.809017,
	0.309017,0,-0.951057,
	0,0,-1,
	-0.309017,0,-0.951057,
	-0.587785,0,-0.809017,
	-0.809017,0,-0.587785,
	-0.951057,0,-0.309017,
	-1,0,0,
	-0.951057,0,0.309017,
	-0.809017,0,0.587785,
	-0.587785,0,0.809017,
	-0.309017,0,0.951057,
	0,0,1,
	0.309017,0,0.951057,
	0.587785,0,0.809017,
	0.809017,0,0.587785,
	0.951057,0,0.309017,
	1,0,0,
};

makethreat (cx,cz, col, radius)
    register int cx,cz;
    int col;
    float radius;
{
    register int i,j;
    register float *f;
    register Building b;

    b = new_building(TYPE_THREAT);
    b -> cx = cx;
    b -> cy = 0;
    b -> cz = cz;
    makeobj (b -> ury_obj = current_building_object++);
	color (col);
	pushmatrix ();
	translate ((float)cx,0.0,(float)cz);
	scale (radius,radius,radius);
	move2s(-1,0);
	for (i=0, f=thcircle+30; i<10; i++,f+=3)
	    draw2(f[0],f[2]);
	for (j=0; j<5; j++) {
	    rotate(300,'y');
	    move2s(-1,0);
	    for (i=0, f=thcircle+30; i<10; i++,f+=3)
		draw2(f[0],f[2]);
	}
	poly(20,(Coord (*)[3]) thcircle);
	/*
	translate (0.0,0.5,0.0);
	scale (.866,.866,.866);
	*/
	translate (0.0,0.33,0.0);
	scale (.94,.94,.94);
	poly(20,(Coord (*)[3]) thcircle);
	translate (0.0,0.33/.94,0.0);
	scale (.794,.794,.794);
	poly(20,(Coord (*)[3]) thcircle);
	popmatrix ();
    closeobj ();
}

/* make a mountain given center [x,y,z], number of faces, and data array */
makemtn (cx,cy,cz, n, savearray)
    register int cx,cy,cz, n;
    int savearray[];
{
    register int *array=savearray;
    register Building b;

    b = new_building(TYPE_MOUNTAIN);
    b -> cx = cx;
    b -> cy = cy;
    b -> cz = cz;
    makeobj (b -> ury_obj = current_building_object++);
	backface (TRUE);
	while (n-- > 0) {
	    color (array[0]);
	    pmvi (cx,cy,cz);
	    pdri (cx+array[1],0,cz+array[2]);
	    array += 3;		/* advance to next point	*/
	    if (n == 0) then array = savearray;
	    pdri (cx+array[1],0,cz+array[2]);
	    pclos ();
	}
	backface (FALSE);
    closeobj;
}

/* create the data structure for a box shaped building	*/
makebox (col,llx,lly,llz,dx,dy,dz)
    int col;
    register int llx,lly,llz;
    int dx,dy,dz;
{
    register short *shade;
    register int i,*p, *obj;
    int urx,ury,urz;
    int mat[4][3];
    register Building b;
    extern short building_shade[][5];

    urx = llx + dx;
    ury = lly + dy;
    urz = llz + dz;

    b = new_building(TYPE_BUILDING);
    b -> llx = llx;
    b -> urx = urx;
    b -> llz = llz;
    b -> urz = urz;
    b -> ury = ury;

    b -> cx = (llx + urx) >> 1;
    b -> cy = (lly + ury) >> 1;
    b -> cz = (llz + urz) >> 1;

    if (bitplanes == 4) then col = bgrey;	/* force to grey	*/
    shade = &building_shade[col][0];

    makeobj (b -> ury_obj = current_building_object++);
	p = &mat[0][0];
	color (shade[0]);		/* top face	*/
	*p++ = llx;	*p++ = ury;	*p++ = llz;
	*p++ = urx;	*p++ = ury;	*p++ = llz;
	*p++ = urx;	*p++ = ury;	*p++ = urz;
	*p++ = llx;	*p++ = ury;	*p++ = urz;
	polfi (4,mat);
	color (red);
	pnti (llx,ury,llz);
	pnti (urx,ury,llz);
	pnti (llx,ury,urz);
	pnti (urx,ury,urz);
    closeobj ();

    for (i=llz; i<=urz; i+=dz) {	/* front and back	*/
	if (i == llz) {
	    makeobj (b -> llz_obj = current_building_object++);
	    obj = &b -> llz_obj1;
	    color (shade[3]);
	}
	else {
	    makeobj (b -> urz_obj = current_building_object++);
	    obj = &b -> urz_obj1;
	    color (shade[2]);
	}
	p = &mat[0][0];
	*p++ = llx;	*p++ = lly;	*p++ = i;
	*p++ = urx;	*p++ = lly;	*p++ = i;
	*p++ = urx;	*p++ = ury;	*p++ = i;
	*p++ = llx;	*p++ = ury;	*p++ = i;
	facet (obj,4,mat);
    }

    for (i=llx; i<=urx; i+=dx) {	/* left and right	*/
	if (i == llx) {
	    makeobj (b -> llx_obj = current_building_object++);
	    obj = &b -> llx_obj1;
	    color (shade[1]);
	}
	else {
	    makeobj (b -> urx_obj = current_building_object++);
	    obj = &b -> urx_obj1;
	    color (shade[4]);
	}
	p = &mat[0][0];
	*p++ = i;	*p++ = lly;	*p++ = llz;
	*p++ = i;	*p++ = ury;	*p++ = llz;
	*p++ = i;	*p++ = ury;	*p++ = urz;
	*p++ = i;	*p++ = lly;	*p++ = urz;
	facet (obj,4,mat);
    }
}

/* draw the face of the building and then lines	*/
facet (obj,n,p)
    register Object *obj;
    int n;
    register int p[][3];
{
    float a1, b1, c1, a2, b2, c2, x1, y1, z1, x2, y2, z2;
    float dx,dy,dz,da,db,dc;
    register Matrix mat;

    polfi (n,p);	/* draw the polygon		*/
    closeobj ();	/* close the open object	*/
    x1 = p[0][0];	y1 = p[0][1];	z1 = p[0][2];
    if (p[1][1] == p[0][1]) {
	a1 = p[1][0];	b1 = p[1][1];	c1 = p[1][2];
	a2 = p[2][0];	b2 = p[2][1];	c2 = p[2][2];
	if (n==3) {
	    x2 = a2; y2 = b2; z2 = c2;
	}
	else {
	    x2 = p[3][0]; y2 = p[3][1];	z2 = p[3][2];
	}
    }
    else {
	x2 = p[1][0];	y2 = p[1][1];	z2 = p[1][2];
	if (n==3) {
	    a1 = p[2][0];	b1 = p[2][1];	c1 = p[2][2];
	    a2 = x2; b2 = y2; c2 = z2;
	}
	else {
	    a2 = p[2][0];	b2 = p[2][1];	c2 = p[2][2];
	    a1 = p[3][0]; b1 = p[3][1];	c1 = p[3][2];
	}
    }
    dy = y2 - y1;
    if (dy > 50.0) then db = 25.0;
    else db = 0.5 * dy;

    dx = (x2 - x1) * db/dy;
    dz = (z2 - z1) * db/dy;
    da = (a2 - a1) * db/dy;
    dc = (c2 - c1) * db/dy;

    makeobj (*obj = current_building_object++);
    color (black);
    y2 -= 2.0;
    if (y1 < 2.0) {		/* if on ground, skip first line	*/
	y1 += db;
	x1 += dx;	a1 += da;
	z1 += dz;	c1 += dc;
    }
    else {
	move (x1,y1,z1);
	draw (a1,y1,c1);
    }

    if (dy > 26.0) {
	while (y1 < y2) {
	    move (x1,y1,z1);
	    draw (a1,y1,c1);
	    y1 += db;
	    x1 += dx;	a1 += da;
	    z1 += dz;	c1 += dc;
	}
    }
    closeobj ();
}

/* sort an array (and an associated tag array) in increasing order	*/
sink_sort (n, array, array_tag, array_is_plane)
    register int n;
    int *array, **array_tag, *array_is_plane;
{
    register int *tag, is_plane, *end;
    register int *top, **top_tag, *bot, **bot_tag, *top_is_plane, *bot_is_plane;

    end = &array[n];

    for (bot = array+1, bot_tag = array_tag+1, bot_is_plane = array_is_plane+1;
            bot < end;
            bot++, bot_tag++, bot_is_plane++) {

	top = bot - 1;
        top_tag = bot_tag - 1;
        top_is_plane = bot_is_plane - 1;
	n = *bot;
	if (*top > n) {
	    tag = *bot_tag;
            is_plane = *bot_is_plane;
	sinktest:
	    top[1] = *top;	top_tag[1] = *top_tag;  top_is_plane[1] = *top_is_plane;
	    top--;		top_tag--;              top_is_plane--;
	    if (top >= array) {
		if (*top > n) goto sinktest;
	    }

	    top[1] = n;	top_tag[1] = tag; top_is_plane[1] = is_plane;
	}
    }
}

/* generate a random number x, where -maxr <= x <= maxr	*/
int flight_random (maxr)
    register int maxr;
{
    static unsigned long randx = 1;
    register int n,retval;

    for (n=1; n<32; n++)
	if ((1 << n) > maxr) then break;

    retval = maxr << 1;
    while (retval > maxr) {
	randx = randx*1103515245 + 12345;
	retval = (randx & 0x7fffffff) >> (31-n);
    }
    randx = randx*1103515245 + 12345;
    if (randx & 0x40000000)
    then return (retval);
    else return (-retval);
}
