/* jello.c
 * Thant Tessman - August, '87
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gl.h>
#include <math.h>
#include <device.h>
#include <time.h>

#define X 0
#define Y 1
#define Z 2
#define W 3

#define XB 10
#define YB 10
#define ZB 10

#define HALFTONE 1

#define RAD 1.8

#define HEIGHT 3.0
#define SHADOW_HEIGHT 0.015
#define ANG 42.861
#define PI 3.1415926536

short halftone[] = { 0x5555, 0xaaaa, 0x5555, 0xaaaa,
	0x5555, 0xaaaa, 0x5555, 0xaaaa,
	0x5555, 0xaaaa, 0x5555, 0xaaaa,
	0x5555, 0xaaaa, 0x5555, 0xaaaa };

float dot();
float plane_point_d();
float light_vector[3];

float view[4][4] = { {1.0, 0.0, 0.0, 0.0} ,
		     {0.0, 1.0, 0.0, 0.0} ,
		     {0.0, 0.0, 1.0, 0.0} ,
		     {0.0, 0.0, 0.0, 1.0} };

float ident_matrix[4][4] = { {1.0, 0.0, 0.0, 0.0} ,
		     {0.0, 1.0, 0.0, 0.0} ,
		     {0.0, 0.0, 1.0, 0.0} ,
		     {0.0, 0.0, 0.0, 1.0} };

float shadow[6][4][4];

short dev, val;
int active;
long gid;

short mx, my, omx, omy;

short ory2, orx2;

float dt = 0.5;
float dw = 0.9;
float damp = 0.3;
float fric = 0.3;
float dist = 15.0;

static int esc_pressed = 0;
static int esc_long_press = 0;
static struct timespec esc_press_time;

typedef struct atom_struct {

	float acc[3];

	float vel[3];

	float pos[3];

	float norm[3];

	int center;

	float colur;

	struct atom_struct *next;

	struct atom_struct *surf;

} Atom;


typedef struct conec_struct {

	float r;

	Atom *from;

	Atom *tu;

	struct conec_struct *next;

} Conec;


typedef struct triangle_struct {

    Atom *vertex[3];

    float norm[4];

    struct triangle_struct *next;

} Triangle;


typedef struct normal_struct {

	float norm[3];

} Normal;


typedef struct polygon_struct {

	int n;

	float *polygon;	/* malloced 3 at a time */

	Normal *normals;	/* list of normal structs */

	Colorindex *c;

	struct polygon_struct *next;

} Poly;


typedef struct thing_struct {

	Poly *polygons;

	int (*move)();

	struct thing_struct *sub;	/* sub things */

	struct thing_struct *next;	/* next (not affected by matrix) */

} Thing;

static double diff_timespecs(struct timespec *t1, struct timespec *t2) {
    return (t1->tv_sec - t2->tv_sec) + (t1->tv_nsec - t2->tv_nsec)/1000000000.0;
}

Conec *new_conec(next, a1, a2)
Conec *next;
Atom *a1, *a2;
{

	Conec *conec;


	conec = (Conec *)malloc(sizeof(Conec));

	conec->from = a1;
	conec->tu = a2;

	conec->next = next;

	return(conec);

}


Atom *new_atom(next)
Atom *next;
{
    Atom *atom;

    atom = (Atom *)malloc(sizeof(Atom));

    atom->pos[X] = 0.0;
    atom->pos[Y] = 0.0;
    atom->pos[Z] = 0.0;

    atom->vel[X] = 0.0;
    atom->vel[Y] = 0.0;
    atom->vel[Z] = 0.0;

    atom->acc[X] = 0.0;
    atom->acc[Y] = 0.0;
    atom->acc[Z] = 0.0;

    atom->norm[X] = 0.0;
    atom->norm[Y] = 0.0;
    atom->norm[Z] = 0.0;

    atom->center = FALSE;

    atom->surf = NULL;

    atom->next = next;

    return(atom);
}


Triangle *new_triangle(next, a1, a2, a3)
Triangle *next;
Atom *a1, *a2, *a3;
{
    Triangle *new;

    new = (Triangle *)malloc(sizeof(Triangle));

    new->next = next;

    new->vertex[0] = a1;
    new->vertex[1] = a2;
    new->vertex[2] = a3;

    return new;
}

Poly *new_polygon() {

	Poly *new;

	new = (Poly *)malloc(sizeof(Poly));

	new->n = 0;
	new->polygon = NULL;
	new->next = NULL;

	return(new);
}


Conec *tmp_conec;
Atom *tmp_atom;


Atom *jello_atoms = NULL;
Atom *surface_atoms = NULL;
Triangle *surface_triangles;
Conec *jello_conec = NULL;
float grav = 0.0;
float grav_vec[3] = {0.0, 0.0, 0.0};

int function=0;
#define REORIENT 1

int display_mode=4;
#define DOTS 1
#define CONECS 2
#define SURFACE_DOTS 3
#define SURFACE_TRIANGLES 4
#define GOURAUD_SURFACE 5

int menu, surface_menu;

void reorient(short ax, short ay);

short tilt_left = -200;
short tilt_right = 200;
short tilt_forward = 650;
short tilt_back = 150;
static const short tilt_horiz_center = 0;
static const short tilt_horiz_span = 200;
static const short tilt_vert_center = 320;
static const short tilt_vert_span = 200;

void get_tilt(short *tiltx, short *tilty)
{
    *tiltx = XMAXSCREEN * (getvaluator(DIAL1) - tilt_forward) / (tilt_back - tilt_forward) ;
    *tilty = YMAXSCREEN * (getvaluator(DIAL0) - tilt_left) / (tilt_right - tilt_left);
}

main (argc, argv)
int	argc;
char	*argv[];
{
 
    int i, j;
    int started = 0;

	if (argc != 1)
	{
		fprintf(stderr, "%s takes no arguments\n", argv[0]);
		exit(1);
	}
    initialize(argv[0]);

    // XXX grantham
    get_tilt(&orx2, &ory2);

    if (!started) {
	grav = -0.008;
	damp = 0.995;
	light_vector[X] = view[0][1];
	light_vector[Y] = view[1][1];
	light_vector[Z] = view[2][1];

	grav_vec[X] = light_vector[X] * grav;
	grav_vec[Y] = light_vector[Y] * grav;
	grav_vec[Z] = light_vector[Z] * grav;
	started = 1;
    }

    while(TRUE) {

	while(qtest()) {
	    dev=qread(&val);
	    switch(dev) {

		case INPUTCHANGE:
		    active = val;
		    if (val) draw_everything();
		    break;

		case REDRAW:
		    reshapeviewport();
		    break;

		case ESCKEY :
			if (val) {
			    // Keep track of when it was pressed.
			    esc_pressed = 1;
			    esc_long_press = 0;
			    clock_gettime(CLOCK_MONOTONIC, &esc_press_time);
			} else {
			    // If this wasn't long-held, exit.
			    if (!esc_long_press) {
				gexit();
				exit(0);
			    }

			    esc_pressed = 0;
			}
		    break;

		case LEFTMOUSE :
		    if (val) {
                        if (!started) {
                            grav = -0.008;
                            damp = 0.995;
                            light_vector[X] = view[0][1];
                            light_vector[Y] = view[1][1];
                            light_vector[Z] = view[2][1];

                            grav_vec[X] = light_vector[X] * grav;
                            grav_vec[Y] = light_vector[Y] * grav;
                            grav_vec[Z] = light_vector[Z] * grav;
                            started = 1;
                        }
		    }

                    if (val) {
			qread(&omx); qread(&omy);
			function = REORIENT;
		    } else {
			function = 0;
			get_tilt(&orx2, &ory2);
		    }

		    break;

		case MIDDLEMOUSE:
		    qread(&omx); qread(&omy);
		    if (val) function = REORIENT;
		    else function = 0;
		    break;

		case RIGHTMOUSE:
		    if (val) {
			switch (dopup(menu)) {

			    case 1:
				reset_jello();
				break;

			    case 2:
				i = dopup(surface_menu);
				if (i>0) display_mode=i;
				break;

			    case 3:
				gexit(); exit(0);
			}
		    }
		    break;
	    }
	}

	switch(function) {

	    case REORIENT: {
		short nmx = getvaluator(MOUSEX);
		short nmy = getvaluator(MOUSEY);

		short ax = (nmx-omx)*2;
		short ay = (omy-nmy)*2;

		omx=nmx; omy=nmy;

		reorient(ax, ay);
		break;
	    }

	    default : {
		short rx2, ry2;

		get_tilt(&rx2, &ry2);

		short ax = (ry2 - ory2) / 2;
		short ay = (orx2 - rx2) / 2;

		orx2 = rx2;
		ory2 = ry2;

		// Don't use tilt, we use it for gravity.
		ax = 0;
		ay = 0;

		reorient(ax, ay);
		break;
	    }
	}

	draw_everything();
	iterate();

	// See if ESC is being held down.
	if (esc_pressed) {
	    struct timespec now;
	    clock_gettime(CLOCK_MONOTONIC, &now);
	    double elapsed = diff_timespecs(&now, &esc_press_time);
	    if (elapsed > 0.5) {
		// If ESC is hold for more than half a second, reset the physics.
		reset_jello();
		esc_long_press = 1;
	    }
	}
    }
}


initialize(name)
char *name;
{

    float sx, sy, sz;
    int i, j, k;

    keepaspect(5, 4);
	{
		char *t, *strrchr();
		gid=winopen((t=strrchr(name, '/')) != NULL ? t+1 : name);
	}
	if (getplanes() < 12) {
		fprintf(stderr, "You need at least 12 bitplanes to run %s\n",name);
		gexit();
		exit(1);
	}

    doublebuffer();
    RGBmode();
    gconfig();


    zbuffer(TRUE);
    lsetdepth(0x0, 0x7fffff);
    perspective(400, (float)XMAXSCREEN/YMAXSCREEN, dist-(HEIGHT*1.74), dist+(HEIGHT*1.74));
    translate(0.0, 0.0, -dist);
    RGBcolor(0, 0, 0);
    clear(); swapbuffers(); clear();

    qdevice(INPUTCHANGE);
    qdevice(REDRAW);
    qdevice(ESCKEY);
    qdevice(LEFTMOUSE);
    tie(LEFTMOUSE, MOUSEX, MOUSEY);
    qdevice(MIDDLEMOUSE);
    tie(MIDDLEMOUSE, MOUSEX, MOUSEY);
    qdevice(RIGHTMOUSE);

    defpattern(HALFTONE, 16, (uint16_t *) halftone);

    for (k=0; k<6; k++)
	for (i=0; i<4; i++)
	    for (j=0; j<4; j++)
		shadow[k][i][j] = (i==j);

    build_icosahedron();

    light_vector[X] = view[0][1];
    light_vector[Y] = view[1][1];
    light_vector[Z] = view[2][1];

    menu = defpup("Jello%t|reset|display|exit");
    surface_menu = defpup("Jello Display%t|dots|conecs|surface dots|surface triangles|gouraud");

}


build_icosahedron() {

    int i, j;

    Atom *a[13];
    Conec *conec;
    float x, y, z, xy, ang=0.0;

    a[0] = new_atom(NULL);

    for (i=1; i<13; i++) {

	a[i] = new_atom(a[i-1]);
    }

    jello_atoms = a[12];

    conec = new_conec(NULL, a[0], a[2]);
    conec = new_conec(conec, a[0], a[3]);
    conec = new_conec(conec, a[0], a[4]);
    conec = new_conec(conec, a[0], a[5]);
    conec = new_conec(conec, a[0], a[6]);

    conec = new_conec(conec, a[1], a[7]);
    conec = new_conec(conec, a[1], a[8]);
    conec = new_conec(conec, a[1], a[9]);
    conec = new_conec(conec, a[1], a[10]);
    conec = new_conec(conec, a[1], a[11]);

    conec = new_conec(conec, a[2], a[3]);
    conec = new_conec(conec, a[2], a[6]);
    conec = new_conec(conec, a[2], a[9]);
    conec = new_conec(conec, a[2], a[10]);

    conec = new_conec(conec, a[3], a[4]);
    conec = new_conec(conec, a[3], a[10]);
    conec = new_conec(conec, a[3], a[11]);

    conec = new_conec(conec, a[4], a[5]);
    conec = new_conec(conec, a[4], a[7]);
    conec = new_conec(conec, a[4], a[11]);

    conec = new_conec(conec, a[5], a[6]);
    conec = new_conec(conec, a[5], a[7]);
    conec = new_conec(conec, a[5], a[8]);

    conec = new_conec(conec, a[6], a[8]);
    conec = new_conec(conec, a[6], a[9]);

    conec = new_conec(conec, a[7], a[8]);
    conec = new_conec(conec, a[7], a[11]);

    conec = new_conec(conec, a[8], a[9]);

    conec = new_conec(conec, a[9], a[10]);

    conec = new_conec(conec, a[10], a[11]);

    conec = new_conec(conec, a[0], a[12]);
    conec = new_conec(conec, a[1], a[12]);
    conec = new_conec(conec, a[2], a[12]);
    conec = new_conec(conec, a[3], a[12]);
    conec = new_conec(conec, a[4], a[12]);
    conec = new_conec(conec, a[5], a[12]);
    conec = new_conec(conec, a[6], a[12]);
    conec = new_conec(conec, a[7], a[12]);
    conec = new_conec(conec, a[8], a[12]);
    conec = new_conec(conec, a[9], a[12]);
    conec = new_conec(conec, a[10], a[12]);
    conec = new_conec(conec, a[11], a[12]);

    jello_conec = conec;

    a[0]->pos[X] = 0.0;
    a[0]->pos[Y] = 0.0;
    a[0]->pos[Z] = -1.0;

    a[1]->pos[X] = 0.0;
    a[1]->pos[Y] = 0.0;
    a[1]->pos[Z] = 1.0;

    z = cos(ANG);
    xy = sin(ANG);

    a[2]->pos[Z] = -z;
    a[3]->pos[Z] = -z;
    a[4]->pos[Z] = -z;
    a[5]->pos[Z] = -z;
    a[6]->pos[Z] = -z;

    a[7]->pos[Z] = z;
    a[8]->pos[Z] = z;
    a[9]->pos[Z] = z;
    a[10]->pos[Z] = z;
    a[11]->pos[Z] = z;

    ang=0.0;
    for (i=2; i<7; i++) {
	x = xy * cos(ang); y = xy * sin(ang);
	a[i]->pos[X] = x; a[i]->pos[Y] = y;
	a[i+5]->pos[X] = -x; a[i+5]->pos[Y] = -y;
	ang += 2.0 * PI / 5.0;
    }

    find_surface();
}



iterate() {

	do_clear(jello_atoms);

	do_accel(jello_conec);

	do_bounds(jello_atoms);

	do_vel(jello_atoms);

	do_pos(jello_atoms);
}


do_clear(atom)
Atom *atom;
{
	if (atom) {

	    do {
		atom->acc[X] = grav_vec[X];
		atom->acc[Y] = grav_vec[Y];
		atom->acc[Z] = grav_vec[Z];
	    } while ((atom = atom->next) != NULL);
	}
}


do_accel(conec)
Conec *conec;
{
	int i=0;
	float dx, dy, dz, dr, ax, ay, az;

	if (conec) do {

		dx = conec->from->pos[X] - conec->tu->pos[X];
		dy = conec->from->pos[Y] - conec->tu->pos[Y];
		dz = conec->from->pos[Z] - conec->tu->pos[Z];

		dr = sqrt(dx*dx + dy*dy + dz*dz);

		if (conec->from->center) {
		    conec->tu->norm[X] = -dx/dr;
		    conec->tu->norm[Y] = -dy/dr;
		    conec->tu->norm[Z] = -dz/dr;
		    conec->tu->colur = dot(conec->tu->norm,
		    light_vector);
		} else if (conec->tu->center) {
		    conec->from->norm[X] = dx/dr;
		    conec->from->norm[Y] = dy/dr;
		    conec->from->norm[Z] = dz/dr;
		    conec->from->colur = dot(conec->from->norm,
		    light_vector);
		}


		ax = dt * (dx - dx/dr);
		ay = dt * (dy - dy/dr);
		az = dt * (dz - dz/dr);

		conec->from->acc[Y] -= ay;
		conec->from->acc[X] -= ax;
		conec->from->acc[Z] -= az;

		conec->tu->acc[X] += ax;
		conec->tu->acc[Y] += ay;
		conec->tu->acc[Z] += az;

	} while ((conec = conec->next) != NULL);
}


do_bounds(atom)
Atom *atom;
{
    if (atom) do {

	if (atom->pos[Y] < -(HEIGHT-0.1)) {
	    atom->acc[Y] -= (atom->pos[Y] + (HEIGHT-0.1)) * dw;
	    atom->vel[X] *= fric;
	    atom->vel[Z] *= fric;
	}

	if (atom->pos[Y] > (HEIGHT-0.1)) {
	    atom->acc[Y] -= (atom->pos[Y] - (HEIGHT-0.1)) * dw;
	    atom->vel[X] *= fric;
	    atom->vel[Z] *= fric;
	}

	if (atom->pos[X] < -(HEIGHT-0.1)) {
	    atom->acc[X] -= (atom->pos[X] + (HEIGHT-0.1)) * dw;
	    atom->vel[Y] *= fric;
	    atom->vel[Z] *= fric;
	}

	if (atom->pos[X] > (HEIGHT-0.1)) {
	    atom->acc[X] -= (atom->pos[X] - (HEIGHT-0.1)) * dw;
	    atom->vel[Y] *= fric;
	    atom->vel[Z] *= fric;
	}

	if (atom->pos[Z] < -(HEIGHT-0.1)) {
	    atom->acc[Z] -= (atom->pos[Z] + (HEIGHT-0.1)) * dw;
	    atom->vel[X] *= fric;
	    atom->vel[Y] *= fric;
	}

	if (atom->pos[Z] > (HEIGHT-0.1)) {
	    atom->acc[Z] -= (atom->pos[Z] - (HEIGHT-0.1)) * dw;
	    atom->vel[X] *= fric;
	    atom->vel[Y] *= fric;
	}

    } while ((atom = atom->next) != NULL);
}


do_vel(atom)
Atom *atom;
{
	if (atom) {

	    do {
		atom->vel[X] += atom->acc[X];
		atom->vel[Y] += atom->acc[Y];
		atom->vel[Z] += atom->acc[Z];

		atom->vel[X] *= damp;
		atom->vel[Y] *= damp;
		atom->vel[Z] *= damp;


	    } while ((atom = atom->next) != NULL);
	}
}


do_pos(atom)
Atom *atom;
{
	if (atom) {

	    do {
		atom->pos[X] += atom->vel[X];
		atom->pos[Y] += atom->vel[Y];
		atom->pos[Z] += atom->vel[Z];

	    } while ((atom = atom->next) != NULL);
	}
}


draw_everything()
{


    swapbuffers();
    RGBcolor(0, 0, 0);
    czclear(0, 0xFFFFFFFF);

    pushmatrix();
    multmatrix(view);
    draw_floor();
    draw_jello();
    draw_frame();
    popmatrix();
}


draw_jello()
{
    switch (display_mode) {

	case DOTS:
	    draw_dots(jello_atoms);
	    break;

	case CONECS:
	    draw_conecs(jello_conec);
	    break;

	case SURFACE_DOTS:
	    draw_surface_dots(surface_atoms);
	    break;

	case SURFACE_TRIANGLES:
	    draw_surface_triangles(surface_triangles);
	    break;

	case GOURAUD_SURFACE:
	    draw_gouraud(surface_triangles);
	    break;
    }
}


void reorient(short ax, short ay)
{
	pushmatrix();

	loadmatrix(ident_matrix);

	rotate((Angle) ax, 'y');
	rotate((Angle) ay, 'x');

	multmatrix(view);

	getmatrix(view);

	light_vector[X] = view[0][1];
	light_vector[Y] = view[1][1];
	light_vector[Z] = view[2][1];

        // Compute gravity.
	{
	    float ax = getvaluator(DIAL5) / 256.0;
	    float ay = getvaluator(DIAL6) / 256.0;
	    float az = getvaluator(DIAL7) / 256.0;

	    grav_vec[X] = (view[X][0]*ax + view[X][1]*ay + view[X][2]*az)*grav*2;
	    grav_vec[Y] = (view[Y][0]*ax + view[Y][1]*ay + view[Y][2]*az)*grav*2;
	    grav_vec[Z] = (view[Z][0]*ax + view[Z][1]*ay + view[Z][2]*az)*grav*2;
	}

	popmatrix();
}


draw_floor() {

	int i;
	float c;
        float ht = HEIGHT;

	if (view[0][2]<ht/dist) {

	    if (0.0<(c = view[0][1])) c=0.0;
	    c = c * -100.0 + 55.0;

	    RGBcolor((RGBvalue)c, (RGBvalue)c, (RGBvalue)c);

	    pmv(ht, ht, ht);
	    pdr(ht, ht, -ht);
	    pdr(ht, -ht, -ht);
	    pdr(ht, -ht, ht);
	    pclos();

	    if (view[0][1]<0.0) {

		pushmatrix();

		shadow[0][0][0] = 0.000001;
		shadow[0][0][1] = -view[1][1]/view[0][1];
		shadow[0][0][2] = -view[2][1]/view[0][1];
		translate((HEIGHT-SHADOW_HEIGHT), 0.0, 0.0);
		multmatrix(shadow[0]);
		translate(-(HEIGHT-SHADOW_HEIGHT), 0.0, 0.0);
		draw_shadow(surface_triangles);

		popmatrix();
	    }

	}

	if (view[0][2]>-ht/dist) {

	    if (0.0>(c = view[0][1])) c=0.0;
	    c = c * 100.0 + 55.0;

	    RGBcolor((RGBvalue)c, (RGBvalue)c, (RGBvalue)c);

	    pmv(-ht, ht, ht);
	    pdr(-ht, -ht, ht);
	    pdr(-ht, -ht, -ht);
	    pdr(-ht, ht, -ht);
	    pclos();

	    if (view[0][1]>0.0) {

		pushmatrix();

		shadow[1][0][0] = 0.000001;
		shadow[1][0][1] = -view[1][1]/view[0][1];
		shadow[1][0][2] = -view[2][1]/view[0][1];
		translate(-(HEIGHT-SHADOW_HEIGHT), 0.0, 0.0);
		multmatrix(shadow[1]);
		translate((HEIGHT-SHADOW_HEIGHT), 0.0, 0.0);
		draw_shadow(surface_triangles);

		popmatrix();
	    }
	} 

	if (view[2][2]>-ht/dist) {

	    if (0.0>(c = view[2][1])) c=0.0;
	    c = c * 100.0 + 55.0;

	    RGBcolor((RGBvalue)c, (RGBvalue)c, (RGBvalue)c);

	    pmv(ht, ht, -ht);
	    pdr(-ht, ht, -ht);
	    pdr(-ht, -ht, -ht);
	    pdr(ht, -ht, -ht);
	    pclos();

	    if (view[2][1]>0.0) {

		pushmatrix();

		shadow[2][2][0] = -view[0][1]/view[2][1];
		shadow[2][2][1] = -view[1][1]/view[2][1];
		shadow[2][2][2] = 0.000001;
		translate(0.0, 0.0, -(HEIGHT-SHADOW_HEIGHT));
		multmatrix(shadow[2]);
		translate(0.0, 0.0, (HEIGHT-SHADOW_HEIGHT));
		draw_shadow(surface_triangles);

		popmatrix();
	    }
	}

	if (view[2][2]<ht/dist) {

	    if (0.0<(c = view[2][1])) c=0.0;
	    c = c * -100.0 + 55.0;

	    RGBcolor((RGBvalue)c, (RGBvalue)c, (RGBvalue)c);

	    pmv(ht, ht, ht);
	    pdr(ht, -ht, ht);
	    pdr(-ht, -ht, ht);
	    pdr(-ht, ht, ht);
	    pclos();

	    if (view[2][1]<0.0) {

		pushmatrix();

		shadow[3][2][0] = -view[0][1]/view[2][1];
		shadow[3][2][1] = -view[1][1]/view[2][1];
		shadow[3][2][2] = 0.000001;
		translate(0.0, 0.0, (HEIGHT-SHADOW_HEIGHT));
		multmatrix(shadow[3]);
		translate(0.0, 0.0, -(HEIGHT-SHADOW_HEIGHT));
		draw_shadow(surface_triangles);

		popmatrix();
	    }

	}

	if (view[1][2]<ht/dist) {

	    if (0.0<(c = view[1][1])) c=0.0;
	    c = c * -100.0 + 55.0;

	    RGBcolor((RGBvalue)c, (RGBvalue)c, (RGBvalue)c);

	    pmv(ht, ht, ht);
	    pdr(-ht, ht, ht);
	    pdr(-ht, ht, -ht);
	    pdr(ht, ht, -ht);
	    pclos();

	    if (view[1][1]<0.0) {

		pushmatrix();

		shadow[4][1][0] = -view[0][1]/view[1][1];
		shadow[4][1][1] = 0.000001;
		shadow[4][1][2] = -view[2][1]/view[1][1];
		translate(0.0, (HEIGHT-SHADOW_HEIGHT), 0.0);
		multmatrix(shadow[4]);
		translate(0.0, -(HEIGHT-SHADOW_HEIGHT), 0.0);
		draw_shadow(surface_triangles);

		popmatrix();
	    }

	}

	if (view[1][2]>-ht/dist) {

	    if (0.0>(c = view[1][1])) c=0.0;
	    c = c * 100.0 + 55.0;

	    RGBcolor((RGBvalue)c, (RGBvalue)c, (RGBvalue)c);

	    pmv(ht, -ht, ht);
	    pdr(ht, -ht, -ht);
	    pdr(-ht, -ht, -ht);
	    pdr(-ht, -ht, ht);
	    pclos();

	    if (view[1][1]>0.0) {

		pushmatrix();

		shadow[5][1][0] = -view[0][1]/view[1][1];
		shadow[5][1][1] = 0.000001;
		shadow[5][1][2] = -view[2][1]/view[1][1];
		translate(0.0, -(HEIGHT-SHADOW_HEIGHT), 0.0);
		multmatrix(shadow[5]);
		translate(0.0, (HEIGHT-SHADOW_HEIGHT), 0.0);
		draw_shadow(surface_triangles);

		popmatrix();
	    }

	}

}

draw_frame() {

	int i;

	RGBcolor(50, 100, 255);

	move(-HEIGHT+0.02, -HEIGHT+0.02, -HEIGHT+0.02);
	draw(-HEIGHT+0.02, -HEIGHT+0.02, HEIGHT-0.02);
	draw(-HEIGHT+0.02, HEIGHT-0.02, HEIGHT-0.02);
	draw(-HEIGHT+0.02, HEIGHT-0.02, -HEIGHT+0.02);
	draw(-HEIGHT+0.02, -HEIGHT+0.02, -HEIGHT+0.02);
	draw(HEIGHT-0.02, -HEIGHT+0.02, -HEIGHT+0.02);
	draw(HEIGHT-0.02, -HEIGHT+0.02, HEIGHT-0.02);
	draw(HEIGHT-0.02, HEIGHT-0.02, HEIGHT-0.02);
	draw(HEIGHT-0.02, HEIGHT-0.02, -HEIGHT+0.02);
	draw(HEIGHT-0.02, -HEIGHT+0.02, -HEIGHT+0.02);

	move(-HEIGHT+0.02, -HEIGHT+0.02, HEIGHT-0.02);
	draw(HEIGHT-0.02, -HEIGHT+0.02, HEIGHT-0.02);

	move(-HEIGHT+0.02, HEIGHT-0.02, -HEIGHT+0.02);
	draw(HEIGHT-0.02, HEIGHT-0.02, -HEIGHT+0.02);

	move(-HEIGHT+0.02, HEIGHT-0.02, HEIGHT-0.02);
	draw(HEIGHT-0.02, HEIGHT-0.02, HEIGHT-0.02);
}


reset_jello() {

    surface_atoms = NULL;
    free_atoms(jello_atoms);
    jello_atoms = NULL;
    free_conecs(jello_conec);
    jello_conec = NULL;
    free_triangles(surface_triangles);
    surface_triangles = NULL;

    grav_vec[X] = 0.0;
    grav_vec[Y] = 0.0;
    grav_vec[Z] = 0.0;
    damp = 0.995;

    build_icosahedron();
}


free_atoms(atom)
Atom *atom;
{
    if (atom) {
	if (atom->next) {
	    free_atoms(atom->next);
	    atom->next=NULL;
	} else {
	    free(atom);
	}
    }
}


free_conecs(conec)
Conec *conec;
{
    if (conec) {
	if (conec->next) {
	    free_conecs(conec->next);
	} else {
	    free(conec);
	}
    }
}


free_triangles(triangle)
Triangle *triangle;
{
    if (triangle) {
	if (triangle->next) {
	    free_triangles(triangle->next);
	} else {
	    free(triangle);
	}
    }
}


find_surface()
{

    int i;
    Atom *atom, *a1, *a2, *a3, *a4;
    Conec *conec, *c1, *c2, *c3, *c4;
    Triangle *triangle;

    free_triangles(surface_triangles);
    surface_triangles = NULL;
    triangle = NULL;
    surface_atoms = NULL;
    atom = jello_atoms;

    if (atom && jello_conec) do {

	conec = jello_conec;
	i=0;

	do {
	    if (conec->from == atom || conec->tu == atom) i++;
	} while ((conec = conec->next) != NULL);

	if (i<12) {
	    atom->surf = surface_atoms;
	    surface_atoms = atom;
	} else {
	    atom->center = TRUE;
	}

    } while ((atom = atom->next) != NULL);

    a1 = surface_atoms;

    do {

	a2 = a1;
	while ((a2 = a2->surf) != NULL) {

	    a3 = a2;
	    while ((a3 = a3->surf) != NULL) {

		c1 = jello_conec;
		do {

		    if ((c1->from==a1 && c1->tu==a2) ||
			(c1->tu==a1 && c1->from==a2)) {

			c2 = jello_conec;
			do {

			    if ((c2->from==a2 && c2->tu==a3) ||
				(c2->tu==a2 && c2->from==a3)) {

				c3 = jello_conec;
				do {

				    if ((c3->from==a3 && c3->tu==a1) ||
					(c3->tu==a3 && c3->from==a1)) {

					triangle =
					new_triangle(triangle, a1,
					a2, a3);

					face_right(triangle);
				    }
				} while ((c3=c3->next) != NULL);
			    }
			} while ((c2=c2->next) != NULL);
		    }
		} while ((c1=c1->next) != NULL);
	    }
	}

    } while ((a1 = a1->surf) != NULL);

    surface_triangles = triangle;
}


draw_dots(atom)
Atom *atom;
{
	RGBcolor(200, 100, 50);

	if (atom) do {
	    pnt(atom->pos[X], atom->pos[Y], atom->pos[Z]);
	} while ((atom = atom->next) != NULL);

}


draw_surface_dots(atom)
Atom *atom;
{
	RGBcolor(100, 200, 50);

	if (atom) do {
	    pnt(atom->pos[X], atom->pos[Y], atom->pos[Z]);
	} while ((atom = atom->surf) != NULL);

}


draw_surface_triangles(triangle)
Triangle *triangle;
{
    float norm[3], r, c;
    float v1[3], v2[3];
    float polygon[3][3];

    if (triangle) do {

	polygon[0][X] = triangle->vertex[0]->pos[X];
	polygon[0][Y] = triangle->vertex[0]->pos[Y];
	polygon[0][Z] = triangle->vertex[0]->pos[Z];

	polygon[1][X] = triangle->vertex[1]->pos[X];
	polygon[1][Y] = triangle->vertex[1]->pos[Y];
	polygon[1][Z] = triangle->vertex[1]->pos[Z];

	polygon[2][X] = triangle->vertex[2]->pos[X];
	polygon[2][Y] = triangle->vertex[2]->pos[Y];
	polygon[2][Z] = triangle->vertex[2]->pos[Z];

	v1[X] = polygon[1][X] - polygon[0][X];
	v1[Y] = polygon[1][Y] - polygon[0][Y];
	v1[Z] = polygon[1][Z] - polygon[0][Z];

	v2[X] = polygon[2][X] - polygon[0][X];
	v2[Y] = polygon[2][Y] - polygon[0][Y];
	v2[Z] = polygon[2][Z] - polygon[0][Z];

	cross(v1, v2, norm);

	r = sqrt(norm[X] * norm[X] + 
		 norm[Y] * norm[Y] + 
		 norm[Z] * norm[Z]);

	norm[X] /= r;
	norm[Y] /= r;
	norm[Z] /= r;

	if ((c = dot(norm, light_vector))<0.0) c = 0.0;

	RGBcolor((int)(c * 100.0 + 100.0),
		 (int)(c * 50.0 + 50.0), 
		 (int)(c * 120.0 + 120.0));

	polf(3, polygon);

    } while ((triangle=triangle->next) != NULL);

}


draw_shadow(triangle)
Triangle *triangle;
{
    setpattern(HALFTONE);

    RGBcolor(0, 0, 0);

    if (triangle) do {

	pmv(triangle->vertex[0]->pos[X],
	    triangle->vertex[0]->pos[Y],
	    triangle->vertex[0]->pos[Z]);


	pdr(triangle->vertex[1]->pos[X],
	    triangle->vertex[1]->pos[Y],
	    triangle->vertex[1]->pos[Z]);


	pdr(triangle->vertex[2]->pos[X],
	    triangle->vertex[2]->pos[Y],
	    triangle->vertex[2]->pos[Z]);

	pclos();

    } while ((triangle=triangle->next) != NULL);

    setpattern(0);
}

draw_gouraud(triangle)
Triangle *triangle;
{
    float c;

    if (triangle) do {

	if ((c = triangle->vertex[0]->colur)<0.0) c = 0.0;

	RGBcolor((int)(c * 100.0 + 30.0),
		 (int)(c * 50.0 + 15.0), 
		 (int)(c * 200.0 + 50.0));

	pmv(triangle->vertex[0]->pos[X],
	    triangle->vertex[0]->pos[Y],
	    triangle->vertex[0]->pos[Z]);

	if ((c = triangle->vertex[1]->colur)<0.0) c = 0.0;

	RGBcolor((int)(c * 100.0 + 30.0),
		 (int)(c * 50.0 + 15.0), 
		 (int)(c * 200.0 + 50.0));

	pdr(triangle->vertex[1]->pos[X],
	    triangle->vertex[1]->pos[Y],
	    triangle->vertex[1]->pos[Z]);

	if ((c = triangle->vertex[2]->colur)<0.0) c = 0.0;

	RGBcolor((int)(c * 100.0 + 30.0),
		 (int)(c * 50.0 + 15.0), 
		 (int)(c * 200.0 + 50.0));

	pdr(triangle->vertex[2]->pos[X],
	    triangle->vertex[2]->pos[Y],
	    triangle->vertex[2]->pos[Z]);

	pclos();

    } while ((triangle=triangle->next) != NULL);

}


draw_conecs(conec)
Conec *conec;
{
    RGBcolor(100, 255, 200);

    if (conec) do {

	move(conec->from->pos[X],
	     conec->from->pos[Y],
	     conec->from->pos[Z]);

	draw(conec->tu->pos[X],
	     conec->tu->pos[Y],
	     conec->tu->pos[Z]);

    } while ((conec = conec->next) != NULL);
}


cross(v1, v2, norm)
float v1[3], v2[3], norm[3];
{
    norm[X] = v1[Y] * v2[Z] - v2[Y] * v1[Z];
    norm[Y] = v1[Z] * v2[X] - v2[Z] * v1[X];
    norm[Z] = v1[X] * v2[Y] - v2[X] * v1[Y];
}


float dot(v1, v2)
float v1[3], v2[3];
{
    return( v1[X] * v2[X] +
	    v1[Y] * v2[Y] +
	    v1[Z] * v2[Z]);
}


face_right(triangle)
Triangle *triangle;
{

    Atom *ta;
    float p[3];

    p[X] = 0.0;
    p[Y] = 0.0;
    p[Z] = 0.0;

    if (plane_point_d(triangle, p)>0.0) {
	ta = triangle->vertex[2];
	triangle->vertex[2] =
	triangle->vertex[1];
	triangle->vertex[1] = ta;
    }
}


float plane_point_d(triangle, atom)
Triangle *triangle;
Atom *atom;
{
    float v1[3], v2[3], norm[4], d, r;

    v1[X] = triangle->vertex[1]->pos[X]-triangle->vertex[0]->pos[X];
    v1[Y] = triangle->vertex[1]->pos[Y]-triangle->vertex[0]->pos[Y];
    v1[Z] = triangle->vertex[1]->pos[Z]-triangle->vertex[0]->pos[Z];

    v2[X] = triangle->vertex[2]->pos[X]-triangle->vertex[0]->pos[X];
    v2[Y] = triangle->vertex[2]->pos[Y]-triangle->vertex[0]->pos[Y];
    v2[Z] = triangle->vertex[2]->pos[Z]-triangle->vertex[0]->pos[Z];

    cross(v1, v2, norm);

    r = sqrt(norm[X] * norm[X] + 
	     norm[Y] * norm[Y] + 
	     norm[Z] * norm[Z]);

    norm[X] /= r;
    norm[Y] /= r;
    norm[Z] /= r;

    norm[W] = -(triangle->vertex[0]->pos[X] * norm[X] +
		triangle->vertex[0]->pos[Y] * norm[Y] +
		triangle->vertex[0]->pos[Z] * norm[Z]);

    d = norm[X] * atom->pos[X] + 
	norm[Y] * atom->pos[Y] + 
	norm[Z] * atom->pos[Z] + norm[W];

    if (d<0.0) {
	triangle->norm[X] = -norm[X];
	triangle->norm[Y] = -norm[Y];
	triangle->norm[Z] = -norm[Z];
    } else {
	triangle->norm[X] = norm[X];
	triangle->norm[Y] = norm[Y];
	triangle->norm[Z] = norm[Z];
    }

    return(d);
}
