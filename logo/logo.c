/* logo.c
 * Thant Tessman - July, '87
 *
 * (Three days and much ugly hacking.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gl.h>
#include <math.h>
#include <device.h>
#include "light.h"

// See the ../NOTES file:
#undef STOP_AFTER_ANIMATION

#define X 0
#define Y 1
#define Z 2

#define S_CYL 6.0
#define D_CYL 8.0
#define ELBOW_RAD 1.0
#define JOINT 900

float radius, s_cyl, d_cyl, elbow_rad;
int cres, bres;
Angle joint;
float mycirc[100][3];
int num;

short dev, val;
int active=TRUE;
long gid;

// In degrees.
double twist = 0;
double horiz = 0;
double vert = 0;

float ident_matrix[4][4] = {
	{1.0, 0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0},
};

float view[4][4] = {
	{1.0, 0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0},
};

float tmp[4][4];
short mx, my, omx, omy, nmx, nmy;

short ory2, orx2;

int bend_left(), bend_right(), bend_forward(), move_single(), move_double();

typedef struct polygon_struct {
	int n;
	float *polygon;	/* malloced 3 at a time */
	float *norm;	/* ditto */
	Colorindex *c;
	struct polygon_struct *next;
} Poly;


typedef struct thing_struct {
	Poly *polygons;
	int (*move)();
	struct thing_struct *sub;	/* sub things */
	struct thing_struct *next;	/* next (not affected by matrix) */
} Thing;


Poly *new_polygon()
{
	Poly *new;

	new = (Poly *)malloc(sizeof(Poly));
	new->n = 0;
	new->polygon = NULL;
	new->norm = NULL;
	new->next = NULL;
	return(new);
}


Thing *new_thing()
{
	int i, j;
	Thing *new;

	new = (Thing *)malloc(sizeof(Thing));
	new->sub = NULL;
	new->next = NULL;
	return(new);
}


Thing *logo;
Poly *elbow, *double_cylinder, *single_cylinder;

int function=0;
#define REORIENT 1

void reorient(short ax, short ay);

short tilt_left = -200;
short tilt_right = 200;
short tilt_forward = 650;
short tilt_back = 150;

void get_tilt(short *tiltx, short *tilty)
{
    if (0) {
        *tiltx = XMAXSCREEN * (getvaluator(DIAL1) - tilt_forward) / (tilt_back - tilt_forward) ;
        *tilty = YMAXSCREEN * (getvaluator(DIAL0) - tilt_left) / (tilt_right - tilt_left);
    } else {
	*tiltx = 0;
	*tilty = 0;
    }
}


#ifndef MAIN
#define MAIN main
#endif

MAIN (argc, argv)
int	argc;
char	*argv[];
{

	int i, j;
	double dx, dy, dz;

	initialize(argv[0]);

	get_tilt(&orx2, &ory2);

	while(TRUE) {

		while(qtest()) {
			dev=qread(&val);
			switch(dev) {
			case INPUTCHANGE:
				active = val;
				if (val) draw_everything();
				break;
			case ESCKEY :
				if (!val) {
					gexit();
					exit(0);
				}
				break;
			case LEFTMOUSE :
				/*qread(&mx); qread(&my);*/
				if (val) {
					reset_values();

					for (i=0; i<4; i++) for (j=0; j<4; j++)
						view[i][j] = (float)(i==j);
				}
				break;
			case MIDDLEMOUSE:
				/*qread(&omx); qread(&omy);*/
				if (val) function = REORIENT;
				else function = 0;
				break;
			case REDRAW:
				reshapeviewport();
				break;
			}
		}

		nmx = getvaluator(MOUSEX);
		nmy = getvaluator(MOUSEY);

		switch(function) {

		    case REORIENT: {

			reorient(nmx-omx, omy-nmy);
			break;
		    }

		    default : {
			short rx2, ry2;

			get_tilt(&rx2, &ry2);

			short ax = (ry2 - ory2) / 2;
			short ay = (orx2 - rx2) / 2;

			orx2 = rx2;
			ory2 = ry2;

			reorient(ax, ay);
			break;
		    }
		}

		omx=nmx; 
		omy=nmy;

		// Gyro. These are in degrees per second.
		dx = getvaluator(DIAL2) / 65536.0;
		dy = getvaluator(DIAL3) / 65536.0;
		dz = getvaluator(DIAL4) / 65536.0;

		// Assume 50 FPS.
		horiz -= dx/50;
		vert -= dy/50;
		// twist -= dz/50; // Disable, it breaks the "object in a box" model.

		// Slowly go back to normal.
		horiz *= 0.99;
		vert *= 0.99;
		twist *= 0.99;

		draw_everything();

	}
}


initialize(title)
char *title;
{

	keepaspect(5, 4);
	{
		char *t, *strrchr();
		gid=winopen((t=strrchr(title, '/'))!=NULL ? t+1 : title);
		if (getplanes() < 12) {
			fprintf(stderr, "You need at least 12 bitplanes to run %s\n",t);
			gexit();
			exit(1);
		}
	}
	lsetdepth(0, 0x7fffff);

	doublebuffer();
	RGBmode();
	gconfig();
	RGBcolor(0, 0, 0);
	clear(); 
	swapbuffers(); 
	clear();
	qdevice(INPUTCHANGE);
	qdevice(REDRAW);
	qdevice(ESCKEY);
	qdevice(LEFTMOUSE);
	qdevice(MIDDLEMOUSE);
	/*tie(LEFTMOUSE, MOUSEX, MOUSEY);*/
	/*tie(MIDDLEMOUSE, MOUSEX, MOUSEY);*/

	/*    makerange(RAMPB, RAMPE, 50, 255, 0, 50, 50, 255); */

	reset_values();
	zbuffer(TRUE);
	zclear();
	init_lighting();

	build_logo();
}



draw_everything() {

	int i, j;
	float t;


	RGBcolor(0, 0, 0);
	czclear(0, 0xFFFFFFFF);

	mmode(MPROJECTION);
	perspective(350, (float)XMAXSCREEN/YMAXSCREEN, 34, 72);

	mmode(MVIEWING);

	loadmatrix(ident_matrix);
	lmbind(LIGHT0, OVER_LIGHT);
	lmbind(LIGHT1, UNDER_LIGHT);

	// We moved the lookat() call for gyro, but be sure it looks like it did
	// when no gyro is being done.
	double orig_offset = 30;
	double new_offset = 5;
	double difference = sqrt(orig_offset*orig_offset*3) - sqrt(new_offset*new_offset*3);
	translate(0, 0, -difference);
	rotate((int) (horiz*10 + 0.5), 'y');
	rotate((int) (vert*10 + 0.5), 'x');

	lookat(-new_offset, new_offset, new_offset, 0.0, 0.0, 0.0, (int) (twist*10 + 0.5));

	multmatrix(view);

	t = (2.0*radius + 2*d_cyl - s_cyl)/2.0;

	translate(t, -t, t);

	draw_thing(logo);

	mmode(MSINGLE);

#ifdef STOP_AFTER_ANIMATION
	int finished = joint == JOINT;
#endif

	if (joint>JOINT) {

		joint-=9;
		t = (float)(1800-joint)/((float)JOINT);
		s_cyl = t * S_CYL;
		d_cyl = t * D_CYL;
		edit_parts();

	} else {

		joint = JOINT;
	}

	swapbuffers();

#ifdef STOP_AFTER_ANIMATION
	if (finished) {
	    exit(0);
	}
#endif
}


build_logo() {

	int i;

	Thing *tmp;

	build_parts();

	logo = new_thing();

	for (i=0; i<3; i++) {

		if (i==0) {
			tmp = logo;
		} else {
			tmp->sub = new_thing();
			tmp=tmp->sub;
		}

		tmp->polygons = double_cylinder;
		tmp->move = move_double;

		tmp->sub = new_thing(); 
		tmp = tmp->sub;
		tmp->polygons = elbow;
		tmp->move = bend_forward;

		tmp->sub = new_thing(); 
		tmp = tmp->sub;
		tmp->polygons = double_cylinder;
		tmp->move = move_double;

		tmp->sub = new_thing(); 
		tmp = tmp->sub;
		tmp->polygons = elbow;
		tmp->move = bend_forward;

		tmp->sub = new_thing(); 
		tmp = tmp->sub;
		tmp->polygons = single_cylinder;
		tmp->move = move_single;

		tmp->sub = new_thing(); 
		tmp = tmp->sub;
		tmp->polygons = elbow;
		tmp->move = bend_right;


		tmp->sub = new_thing(); 
		tmp = tmp->sub;
		tmp->polygons = double_cylinder;
		tmp->move = move_double;

		tmp->sub = new_thing(); 
		tmp = tmp->sub;
		tmp->polygons = elbow;
		tmp->move = bend_forward;

		tmp->sub = new_thing(); 
		tmp = tmp->sub;
		tmp->polygons = double_cylinder;
		tmp->move = move_double;

		tmp->sub = new_thing(); 
		tmp = tmp->sub;
		tmp->polygons = elbow;
		tmp->move = bend_forward;

		tmp->sub = new_thing(); 
		tmp = tmp->sub;
		tmp->polygons = single_cylinder;
		tmp->move = move_single;

		tmp->sub = new_thing(); 
		tmp = tmp->sub;
		tmp->polygons = elbow;
		tmp->move = bend_left;
	}
}


bend_right() {

	rotate(joint, 'z');
	translate(0.0, elbow_rad, 0.0);
	rotate(joint, 'x');
	translate(0.0, -elbow_rad, 0.0);

}


int bend_left() {

	rotate(-joint, 'z');
	translate(0.0, elbow_rad, 0.0);
	rotate(joint, 'x');
	translate(0.0, -elbow_rad, 0.0);

}

bend_forward() {

	translate(0.0, elbow_rad, 0.0);
	rotate(joint, 'x');
	translate(0.0, -elbow_rad, 0.0);

}


move_double() {

	translate(0.0, 0.0, -d_cyl);
}

move_single() {

	translate(0.0, 0.0, -s_cyl);
}

void reorient(short ax, short ay)
{
	pushmatrix();

	loadmatrix(ident_matrix);

	rotate(-450, 'y');

	rotate((Angle) ax, 'y');
	rotate((Angle) ay, 'x');

	rotate(450, 'y');

	multmatrix(view);

	getmatrix(view);

	popmatrix();
}


print_matrix(m)
float m[4][4];
{
	int i, j;

	for (i=0; i<4; i++) {

		for (j=0; j<4; j++) {

			printf("%8.4f  ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

reset_values() {

	radius = 1.0;
	s_cyl = 0.0;
	d_cyl = 0.0;
	elbow_rad = ELBOW_RAD;
	cres = 8;
	bres = 8;
	joint = 1800;
}


draw_thing(thing)
Thing *thing;
{
	while(thing) {

		(*thing->move)();

		draw_polygons(thing->polygons);

		draw_thing(thing->sub);

		thing = thing->next;
	}
}

draw_polygons(polygon)
Poly *polygon;
{
	int i;

	lmbind(MATERIAL, MAT_LOGO);
	lighting(TRUE);

	while((polygon=polygon->next) != NULL) {
		bgnpolygon();
		for (i=0; i<polygon->n; i++) {
			n3f(&polygon->norm[i*3]);
			v3f(&polygon->polygon[i*3]);
		}
		endpolygon();

		/*bgnclosedline();
	for (i=0; i<polygon->n; i++) {
	    n3f(&polygon->norm[i*3]);
	    v3f(&polygon->polygon[i*3]);
	}
	endclosedline();*/

		/*	poly(polygon->n, polygon->polygon);*/
		/*	splf(polygon->n, polygon->polygon, polygon->c);*/

		/* I'm only going to draw the first normal as a test case.  The rest are
       really there (norm[3 * vertex_num])
    */

		/*	RGBcolor(BLUE);
	move(polygon->polygon[X], polygon->polygon[Y], polygon->polygon[Z]);
	rdr(polygon->norm[X], polygon->norm[Y], polygon->norm[Z]);
*/
	}
}


build_parts() {

	float ct1[100][3], ct2[100][3];
	float norm1[100][3], norm2[100][3];
	Angle a;
	float glsin, glcos;
	int i;

	Poly *polygon;

	num = 0;
	elbow = new_polygon();
	polygon = elbow;

	for (a=0; a<=3600; a += 3600/cres) {

		gl_sincos(a, &mycirc[num][Y], &mycirc[num][X]);
		mycirc[num++][Z] = 0.0;
	}

	for (i=0; i<num; i++) {
		ct1[i][X] = mycirc[i][X];
		ct1[i][Y] = mycirc[i][Y];
		ct1[i][Z] = mycirc[i][Z];

		norm1[i][X] = mycirc[i][X];
		norm1[i][Y] = mycirc[i][Y];
		norm1[i][Z] = mycirc[i][Z];
	}

	for (a=joint/bres; a<=joint; a += joint/bres) {

		gl_sincos(a, &glsin, &glcos);

		for (i=0; i<num; i++) {

			ct2[i][X] = mycirc[i][X];
			ct2[i][Y] = (mycirc[i][Y] - elbow_rad) * glcos + elbow_rad;
			ct2[i][Z] = -(mycirc[i][Y]-elbow_rad) * glsin;

			norm2[i][X] = mycirc[i][X];
			norm2[i][Y] = mycirc[i][Y] * glcos;
			norm2[i][Z] = -mycirc[i][Y] * glsin;
		}

		for (i=0; i<num-1; i++) {

			polygon->next = new_polygon();
			polygon = polygon->next;

			polygon->polygon = (float *)malloc(sizeof(float) * 3 * 4);
			polygon->norm = (float *)malloc(sizeof(float) * 3 * 4);
			polygon->c = (Colorindex *)malloc(sizeof(float) * 4);
			polygon->n=4;

			polygon->polygon[X] = ct1[i][X];
			polygon->polygon[Y] = ct1[i][Y];
			polygon->polygon[Z] = ct1[i][Z];
			polygon->norm[X] = norm1[i][X];
			polygon->norm[Y] = norm1[i][Y];
			polygon->norm[Z] = norm1[i][Z];

			polygon->polygon[3+X] = ct2[i][X];
			polygon->polygon[3+Y] = ct2[i][Y];
			polygon->polygon[3+Z] = ct2[i][Z];
			polygon->norm[3+X] = norm2[i][X];
			polygon->norm[3+Y] = norm2[i][Y];
			polygon->norm[3+Z] = norm2[i][Z];

			polygon->polygon[6+X] = ct2[i+1][X];
			polygon->polygon[6+Y] = ct2[i+1][Y];
			polygon->polygon[6+Z] = ct2[i+1][Z];
			polygon->norm[6+X] = norm2[i+1][X];
			polygon->norm[6+Y] = norm2[i+1][Y];
			polygon->norm[6+Z] = norm2[i+1][Z];

			polygon->polygon[9+X] = ct1[i+1][X];
			polygon->polygon[9+Y] = ct1[i+1][Y];
			polygon->polygon[9+Z] = ct1[i+1][Z];
			polygon->norm[9+X] = norm2[i+1][X];
			polygon->norm[9+Y] = norm2[i+1][Y];
			polygon->norm[9+Z] = norm2[i+1][Z];
		}

		for (i=0; i<num; i++) {
			ct1[i][X] = ct2[i][X];
			ct1[i][Y] = ct2[i][Y];
			ct1[i][Z] = ct2[i][Z];

			norm1[i][X] = norm2[i][X];
			norm1[i][Y] = norm2[i][Y];
			norm1[i][Z] = norm2[i][Z];
		}

	}

	double_cylinder = new_polygon();
	polygon = double_cylinder;

	gl_sincos(0, &glsin, &glcos);

	for (a = 3600/cres; a<=3600; a += 3600/cres) {

		polygon->next = new_polygon();
		polygon = polygon->next;

		polygon->polygon = (float *)malloc(sizeof(float) * 3 * 4);
		polygon->norm = (float *)malloc(sizeof(float) * 3 * 4);
		polygon->c = (Colorindex *)malloc(sizeof(float) * 4);
		polygon->n=4;

		polygon->polygon[X] = glcos;
		polygon->polygon[Y] = glsin;
		polygon->polygon[Z] = -0.1;
		polygon->norm[X] = glcos;
		polygon->norm[Y] = glsin;
		polygon->norm[Z] = 0.0;

		polygon->polygon[3+X] = glcos;
		polygon->polygon[3+Y] = glsin;
		polygon->polygon[3+Z] = d_cyl;
		polygon->norm[3+X] = glcos;
		polygon->norm[3+Y] = glsin;
		polygon->norm[3+Z] = 0.0;

		gl_sincos(a, &glsin, &glcos);

		polygon->polygon[6+X] = glcos;
		polygon->polygon[6+Y] = glsin;
		polygon->polygon[6+Z] = d_cyl;
		polygon->norm[6+X] = glcos;
		polygon->norm[6+Y] = glsin;
		polygon->norm[6+Z] = 0.0;

		polygon->polygon[9+X] = glcos;
		polygon->polygon[9+Y] = glsin;
		polygon->polygon[9+Z] = -0.1;
		polygon->norm[9+X] = glcos;
		polygon->norm[9+Y] = glsin;
		polygon->norm[9+Z] = 0.0;
	}

	single_cylinder = new_polygon();
	polygon = single_cylinder;

	gl_sincos(0, &glsin, &glcos);

	for (a = 3600/cres; a<=3600; a += 3600/cres) {

		polygon->next = new_polygon();
		polygon = polygon->next;

		polygon->polygon = (float *)malloc(sizeof(float) * 3 * 4);
		polygon->norm = (float *)malloc(sizeof(float) * 3 * 4);
		polygon->c = (Colorindex *)malloc(sizeof(float) * 4);
		polygon->n=4;

		polygon->polygon[X] = glcos;
		polygon->polygon[Y] = glsin;
		polygon->polygon[Z] = -0.1;
		polygon->norm[X] = glcos;
		polygon->norm[Y] = glsin;
		polygon->norm[Z] = 0.0;

		polygon->polygon[3+X] = glcos;
		polygon->polygon[3+Y] = glsin;
		polygon->polygon[3+Z] = s_cyl;
		polygon->norm[3+X] = glcos;
		polygon->norm[3+Y] = glsin;
		polygon->norm[3+Z] = 0.0;

		gl_sincos(a, &glsin, &glcos);

		polygon->polygon[6+X] = glcos;
		polygon->polygon[6+Y] = glsin;
		polygon->polygon[6+Z] = s_cyl;
		polygon->norm[6+X] = glcos;
		polygon->norm[6+Y] = glsin;
		polygon->norm[6+Z] = 0.0;

		polygon->polygon[9+X] = glcos;
		polygon->polygon[9+Y] = glsin;
		polygon->polygon[9+Z] = -0.1;
		polygon->norm[9+X] = glcos;
		polygon->norm[9+Y] = glsin;
		polygon->norm[9+Z] = 0.0;
	}

}


edit_parts() {

	float ct1[100][3], ct2[100][3];
	float norm1[100][3], norm2[100][3];
	Angle a;
	float glsin, glcos;
	int i;

	Poly *polygon;

	polygon = elbow;

	for (i=0; i<num; i++) {
		ct1[i][X] = mycirc[i][X];
		ct1[i][Y] = mycirc[i][Y];
		ct1[i][Z] = mycirc[i][Z];

		norm1[i][X] = mycirc[i][X];
		norm1[i][Y] = mycirc[i][Y];
		norm1[i][Z] = mycirc[i][Z];
	}

	for (a=joint/bres; a<=joint; a += joint/bres) {

		gl_sincos(a, &glsin, &glcos);

		for (i=0; i<num; i++) {

			ct2[i][X] = mycirc[i][X];
			ct2[i][Y] = (mycirc[i][Y] - elbow_rad) * glcos + elbow_rad;
			ct2[i][Z] = -(mycirc[i][Y]-elbow_rad) * glsin;

			norm2[i][X] = mycirc[i][X];
			norm2[i][Y] = mycirc[i][Y] * glcos;
			norm2[i][Z] = -mycirc[i][Y] * glsin;
		}

		for (i=0; i<num-1; i++) {

			polygon = polygon->next;


			polygon->polygon[X] = ct1[i][X];
			polygon->polygon[Y] = ct1[i][Y];
			polygon->polygon[Z] = ct1[i][Z];
			polygon->norm[X] = norm1[i][X];
			polygon->norm[Y] = norm1[i][Y];
			polygon->norm[Z] = norm1[i][Z];

			polygon->polygon[3+X] = ct2[i][X];
			polygon->polygon[3+Y] = ct2[i][Y];
			polygon->polygon[3+Z] = ct2[i][Z];
			polygon->norm[3+X] = norm2[i][X];
			polygon->norm[3+Y] = norm2[i][Y];
			polygon->norm[3+Z] = norm2[i][Z];

			polygon->polygon[6+X] = ct2[i+1][X];
			polygon->polygon[6+Y] = ct2[i+1][Y];
			polygon->polygon[6+Z] = ct2[i+1][Z];
			polygon->norm[6+X] = norm2[i+1][X];
			polygon->norm[6+Y] = norm2[i+1][Y];
			polygon->norm[6+Z] = norm2[i+1][Z];

			polygon->polygon[9+X] = ct1[i+1][X];
			polygon->polygon[9+Y] = ct1[i+1][Y];
			polygon->polygon[9+Z] = ct1[i+1][Z];
			polygon->norm[9+X] = norm1[i+1][X];
			polygon->norm[9+Y] = norm1[i+1][Y];
			polygon->norm[9+Z] = norm1[i+1][Z];
		}

		for (i=0; i<num; i++) {
			ct1[i][X] = ct2[i][X];
			ct1[i][Y] = ct2[i][Y];
			ct1[i][Z] = ct2[i][Z];

			norm1[i][X] = norm2[i][X];
			norm1[i][Y] = norm2[i][Y];
			norm1[i][Z] = norm2[i][Z];
		}

	}

	polygon = double_cylinder;

	gl_sincos(0, &glsin, &glcos);

	for (a = 3600/cres; a<=3600; a += 3600/cres) {

		polygon = polygon->next;

		polygon->polygon[X] = glcos;
		polygon->polygon[Y] = glsin;
		polygon->polygon[Z] = -0.1;
		polygon->norm[X] = glcos;
		polygon->norm[Y] = glsin;
		polygon->norm[Z] = 0.0;

		polygon->polygon[3+X] = glcos;
		polygon->polygon[3+Y] = glsin;
		polygon->polygon[3+Z] = d_cyl;
		polygon->norm[3+X] = glcos;
		polygon->norm[3+Y] = glsin;
		polygon->norm[3+Z] = 0.0;

		gl_sincos(a, &glsin, &glcos);

		polygon->polygon[6+X] = glcos;
		polygon->polygon[6+Y] = glsin;
		polygon->polygon[6+Z] = d_cyl;
		polygon->norm[6+X] = glcos;
		polygon->norm[6+Y] = glsin;
		polygon->norm[6+Z] = 0.0;

		polygon->polygon[9+X] = glcos;
		polygon->polygon[9+Y] = glsin;
		polygon->polygon[9+Z] = -0.1;
		polygon->norm[9+X] = glcos;
		polygon->norm[9+Y] = glsin;
		polygon->norm[9+Z] = 0.0;
	}


	polygon = single_cylinder;

	gl_sincos(0, &glsin, &glcos);

	for (a = 3600/cres; a<=3600; a += 3600/cres) {

		polygon = polygon->next;

		polygon->polygon[X] = glcos;
		polygon->polygon[Y] = glsin;
		polygon->polygon[Z] = -0.1;
		polygon->norm[X] = glcos;
		polygon->norm[Y] = glsin;
		polygon->norm[Z] = 0.0;

		polygon->polygon[3+X] = glcos;
		polygon->polygon[3+Y] = glsin;
		polygon->polygon[3+Z] = s_cyl;
		polygon->norm[3+X] = glcos;
		polygon->norm[3+Y] = glsin;
		polygon->norm[3+Z] = 0.0;

		gl_sincos(a, &glsin, &glcos);

		polygon->polygon[6+X] = glcos;
		polygon->polygon[6+Y] = glsin;
		polygon->polygon[6+Z] = s_cyl;
		polygon->norm[6+X] = glcos;
		polygon->norm[6+Y] = glsin;
		polygon->norm[6+Z] = 0.0;

		polygon->polygon[9+X] = glcos;
		polygon->polygon[9+Y] = glsin;
		polygon->polygon[9+Z] = -0.1;
		polygon->norm[9+X] = glcos;
		polygon->norm[9+Y] = glsin;
		polygon->norm[9+Z] = 0.0;
	}

}
