#include <gl.h>
#include <device.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "objects.h"

#define X 0
#define Y 1
#define Z 2

#define DEG *3.14159265359/180.0
#define RAD *180.0/3.14159265359

#define ASPECT ((float) (XMAXSCREEN + 1) / (float) (YMAXSCREEN + 1))

float idmat[4][4] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0},
};
float light1[] = {
    AMBIENT, 0.0, 0.0, 0.0, 
    LCOLOR,   1.0, 1.0, 1.0, 
    POSITION, 0.0, 1.0, 0.0, 0.0, 
    LMNULL
};
float light2[] = {
    AMBIENT, 0.0, 0.0, 0.0, 
    LCOLOR,   0.3, 0.3, 0.5, 
    POSITION, -1.0, 0.0, 0.0, 0.0, 
    LMNULL
};
float light3[] = {
    AMBIENT, 0.2, 0.2, 0.2, 
    LCOLOR,   0.2, 0.2, 0.2, 
    POSITION, 0.0, -1.0, 0.0, 0.0, 
    LMNULL
};
float lmodel[] = {
    AMBIENT, 0.3,  0.3, 0.3, 
    LOCALVIEWER, 0.0, 
    LMNULL
};
float mat_logo[] = {
    AMBIENT,	0.1, 0.1, 0.1,
    DIFFUSE,	0.5, 0.4, 0.7,
    SPECULAR,	1.0, 1.0, 1.0,
    SHININESS,	30.0,
    LMNULL,
};
float mat_holder_base[] = {
    AMBIENT,	0.0, 0.0, 0.0,
    DIFFUSE,	0.6, 0.6, 0.6,
    SPECULAR,	0.8, 0.8, 0.8,
    SHININESS,	30.0,
    LMNULL,
};
float mat_holder_rings[] = {
    AMBIENT,	0.0, 0.0, 0.0,
    DIFFUSE,	0.9, 0.8, 0.0,
    SPECULAR,	1.0, 1.0, 1.0,
    SHININESS,	30.0,
    LMNULL,
};
float mat_hemisphere[] = {
    AMBIENT,	0.0, 0.0, 0.0,
    DIFFUSE,	1.0, 0.2, 0.2,
    SPECULAR,	0.5, 0.5, 0.5,
    SHININESS,	20.0,
    LMNULL,
};
init_materials() {

    lmdef(DEFMATERIAL, MAT_LOGO, 0, mat_logo);
    lmdef(DEFMATERIAL, MAT_HOLDER_BASE, 0, mat_holder_base);
    lmdef(DEFMATERIAL, MAT_HOLDER_RINGS, 0, mat_holder_rings);
    lmdef(DEFMATERIAL, MAT_HEMISPHERE, 0, mat_hemisphere);
}
#define HALFTONE 1

short halftone[] = { 0x5555, 0xaaaa, 0x5555, 0xaaaa,
	0x5555, 0xaaaa, 0x5555, 0xaaaa,
	0x5555, 0xaaaa, 0x5555, 0xaaaa,
	0x5555, 0xaaaa, 0x5555, 0xaaaa };
/*
short halftone[] = { 0xeeee, 0xffff, 0xbbbb, 0xffff,
	0xeeee, 0xffff, 0xbbbb, 0xffff,
	0xeeee, 0xffff, 0xbbbb, 0xffff,
	0xeeee, 0xffff, 0xbbbb, 0xffff };
*/

short dev, val;

float tmplight[] = {
    POSITION, 0.0, 0.0, 0.0, 0.0, LMNULL
};

float tv[4][4] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, -1.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 0.0},
};

#define TABLERES 12

float pcr, pcg, pcb, pca;

typedef float vector[3];
typedef vector parameter[4];

vector table_points[TABLERES+1][TABLERES+1];
int tablecolors[TABLERES+1][TABLERES+1];

vector paper_points[4] = {
    {-0.8, 0.0, 0.4},
    {-0.2, 0.0, -1.4},
    {1.0, 0.0, -1.0},
    {0.4, 0.0, 0.8},
};

float dot(vector, vector);
void draw_table(float current_time);

#define TIME 15

vector light_pos_ctl[] = {

    {0.0, 1.8, 0.0},
    {0.0, 1.8, 0.0},
    {0.0, 1.6, 0.0},

    {0.0, 1.6, 0.0},
    {0.0, 1.6, 0.0},
    {0.0, 1.6, 0.0},
    {0.0, 1.4, 0.0},

    {0.0, 1.3, 0.0},
    {-0.2, 1.5, 2.0},
    {0.8, 1.5, -0.4},
    {-0.8, 1.5, -0.4},

    {0.8, 2.0, 1.0},
    {1.8, 5.0, -1.8},
    {8.0, 10.0, -4.0},
    {8.0, 10.0, -4.0},
    {8.0, 10.0, -4.0},
};

vector logo_pos_ctl[] = {

    {0.0, -0.5, 0.0},

    {0.0, -0.5, 0.0},
    {0.0, -0.5, 0.0},

    {0.0, -0.5, 0.0},
    {0.0, -0.5, 0.0},
    {0.0, -0.5, 0.0},
    {0.0, 0.0, 0.0},

    {0.0, 0.6, 0.0},
    {0.0, 0.75, 0.0},
    {0.0, 0.8, 0.0},
    {0.0, 0.8, 0.0},

    {0.0, 0.5, 0.0},
    {0.0, 0.5, 0.0},
    {0.0, 0.5, 0.0},
    {0.0, 0.5, 0.0},
    {0.0, 0.5, 0.0},
};


vector logo_rot_ctl[] = {

    {0.0, 0.0, -18.4},

    {0.0, 0.0, -18.4},
    {0.0, 0.0, -18.4},

    {0.0, 0.0, -18.4},
    {0.0, 0.0, -18.4},
    {0.0, 0.0, -18.4},
    {0.0, 0.0, -18.4},
    {0.0, 0.0, -18.4},

/*    {90.0, 0.0, -90.0},
    {180.0, 180.0, 90.0}, */
    {240.0, 360.0, 180.0},
    {90.0, 180.0, 90.0},

    {11.9, 0.0, -18.4},
    {11.9, 0.0, -18.4},
    {11.9, 0.0, -18.4},
    {11.9, 0.0, -18.4},
    {11.9, 0.0, -18.4},
};


vector view_from_ctl[] = {

    {-1.0, 1.0, -4.0},

    {-1.0, -3.0, -4.0},	/* 0 */
    {-3.0, 1.0, -3.0},	/* 1 */

    {-1.8, 2.0, 5.4},	/* 2 */
    {-0.4, 2.0, 1.2},	/* 3 */
    {-0.2, 1.5, 0.6},	/* 4 */
    {-0.2, 1.2, 0.6},	/* 5 */

    {-0.8, 1.0, 2.4},	/* 6 */
    {-1.0, 2.0, 3.0},	/* 7 */
    {0.0, 4.0, 3.6},	/* 8 */
    {-0.8, 4.0, 1.2},	/* 9 */

    {-0.2, 3.0, 0.6},	/* 10 */
    {-0.1, 2.0, 0.3},	/* 11 */
    {-0.1, 2.0, 0.3},	/* 12 */
    {-0.1, 2.0, 0.3},	/* 13 */
    {-0.1, 2.0, 0.3},	/* 13 */


};

vector view_to_ctl[] = {

    {-1.0, 1.0, 0.0},

    {-1.0, -3.0, 0.0},
    {-1.0, 1.0, 0.0},

    {0.1, 0.0, -0.3},
    {0.1, 0.0, -0.3},
    {0.1, 0.0, -0.3},
    {0.0, 0.2, 0.0},

    {0.0, 0.6, 0.0},
    {0.0, 0.8, 0.0},
    {0.0, 0.8, 0.0},
    {0.0, 0.8, 0.0},

    {0.0, 0.8, 0.0},
    {0.0, 0.8, 0.0},
    {0.0, 0.8, 0.0},
    {0.0, 0.8, 0.0},
    {0.0, 0.8, 0.0},

};


vector view_from, view_to, light_pos, logo_pos, logo_rot;

parameter *view_from_spline, *view_to_spline,
	  *light_pos_spline, *logo_pos_spline,
	  *logo_rot_spline;

parameter *calc_spline_params(vector *, int);

static double diff_timespecs(struct timespec *t1, struct timespec *t2) {
    return (t1->tv_sec - t2->tv_sec) + (t1->tv_nsec - t2->tv_nsec)/1000000000.0;
}

static struct timespec animation_start_time;
static void reset_animation() {
    clock_gettime(CLOCK_MONOTONIC, &animation_start_time);
}

double a3, a4;

main(argc, argv)
int	argc;
char	*argv[];
{
    float x, y, z, c;
    float current_time = 0.0;
    float previous_time;


    initialize(argv[0]);
    reset_animation();

    while (TRUE) {

	while(qtest()) {

	    switch(dev=qread(&val)) {

		case REDRAW:
		    reshapeviewport();
		    break;

		case ESCKEY:
			if (val) break;	/* Ignore down, exit up */
		case WINQUIT:
		    gexit();
		    exit(0);

		case LEFTMOUSE:
		    if (!val) reset_animation();
		    break;

	    }
	}

	// Advance time.
	previous_time = current_time;
	{
	    struct timespec now;
	    clock_gettime(CLOCK_MONOTONIC, &now);
	    current_time = diff_timespecs(&now, &animation_start_time)*0.7;
	    if (current_time > TIME - 3.0) {
		current_time = TIME - 3.001;
	    }
	}
	if ((int) current_time != (int) previous_time && 0) {
	    printf("time = %d\n", (int) current_time);
	}

	calc_spline(view_from, view_from_spline, current_time);
	calc_spline(view_to, view_to_spline, current_time);
	calc_spline(light_pos, light_pos_spline, current_time);
	calc_spline(logo_pos, logo_pos_spline, current_time);
	calc_spline(logo_rot, logo_rot_spline, current_time);

	tmplight[1] = light_pos[X]-logo_pos[X];
	tmplight[2] = light_pos[Y]-logo_pos[Y];
	tmplight[3] = light_pos[Z]-logo_pos[Z];

	lmdef(DEFLIGHT, 1, 0, tmplight);

	tv[0][0] = tv[1][1] = tv[2][2] = light_pos[Y];

	RGBcolor(0, 0, 0);
	clear(); zclear();

	mmode(MSINGLE);

	perspective(150, ASPECT, 0.5, 20.0);
	lookat(view_from[X], view_from[Y], view_from[Z],
	       view_to[X], view_to[Y], view_to[Z], 0);

	if (view_from[Y] > 0.0) draw_table(current_time);

	zbuffer(FALSE);

    if (logo_pos[Y]<0.0) {

	if (logo_pos[Y]>-0.33) {
	    c = 1.0 - (logo_pos[Y])/-0.33;
	    pca /= 4.0;
	    RGBcolor((int)(128.0*(1.0-c)*0.5 + 255.0*pca*c),
		     (int)(102.0*(1.0-c)*0.5 + 255.0*pca*c), 
		     (int)(179.0*(1.0-c)*0.5 + 200.0*pca*c));
	} else {
	    RGBcolor(128/2, 102/2, 179/2);
	}

	pushmatrix();
	scale(0.04, 0.0, 0.04);
	rotate(-900, 'x');
	rotate((int)(10.0*logo_rot[Z]), 'z');
	rotate((int)(10.0*logo_rot[Y]), 'y');
	rotate((int)(10.0*logo_rot[X]), 'x');
	rotate(353, 'x');
	rotate(450, 'y');
	draw_logo_shadow();
/*	draw_logo_line();*/
	popmatrix();
    }

    if (logo_pos[Y]>0.0) {

	pushmatrix();

	if (logo_pos[Y]<0.33) {
	    pca /= 4.0;
	    c = 1.0 - (logo_pos[Y])/0.33;
	    RGBcolor((int)(255.0*pca*c),
		     (int)(255.0*pca*c),
		     (int)(200.0*pca*c), 0);
	} else {
	    RGBcolor(0, 0, 0);
	}

	translate(light_pos[X], light_pos[Y], light_pos[Z]);
	multmatrix(tv);
	translate(-light_pos[X]+logo_pos[X],
		  -light_pos[Y]+logo_pos[Y],
		  -light_pos[Z]+logo_pos[Z]);
	scale(0.04, 0.04, 0.04);
	rotate(-900, 'x');
	rotate((int)(10.0*logo_rot[Z]), 'z');
	rotate((int)(10.0*logo_rot[Y]), 'y');
	rotate((int)(10.0*logo_rot[X]), 'x');
	rotate(353, 'x');
	rotate(450, 'y');
	setpattern(HALFTONE);
	draw_logo_shadow();
	setpattern(0);
	popmatrix();

    }
	zbuffer(TRUE);

	mmode(MVIEWING);
	perspective(150, ASPECT, 0.5, 20.0);
	loadmatrix(idmat);
	lookat(view_from[X], view_from[Y], view_from[Z],
	       view_to[X], view_to[Y], view_to[Z], 0);

	lmbind(LIGHT0, 3);
	lmbind(LIGHT1, 2);

	lmbind(MATERIAL, MAT_HOLDER_RINGS);

	pushmatrix();
	translate(light_pos[X], light_pos[Y], light_pos[Z]);
	scale(0.1, 0.1, 0.1);

	x = light_pos[X] - logo_pos[X];
	y = light_pos[Y] - logo_pos[Y];
	z = light_pos[Z] - logo_pos[Z];

	if (x!=0.0) {
	    a3 = -atan2(z, x)*10.0 RAD;
	} else a3 = 0.0;

	a4 = -atan2(sqrt(x*x + z*z), y)*10.0 RAD;
/*
printf("light_pos %f %f %f\n",
	light_pos[X], light_pos[Y], light_pos[Z]);
printf("a3 = %f, a4 = %f\n", a3, a4);
*/

	rotate((int)a3, 'y');
	rotate((int)a4, 'z');

	rotate(-900, 'x');
	draw_hemisphere();
	popmatrix();

	lmbind(LIGHT0, 1);
	lmbind(LIGHT1, 0);

    if (logo_pos[Y] > -0.33) {
	pushmatrix();
	translate(logo_pos[X], logo_pos[Y], logo_pos[Z]);
	scale(0.04, 0.04, 0.04);
	rotate(-900, 'x');
	rotate((int)(10.0*logo_rot[Z]), 'z');
	rotate((int)(10.0*logo_rot[Y]), 'y');
	rotate((int)(10.0*logo_rot[X]), 'x');
	rotate(353, 'x');
	rotate(450, 'y');
	lmbind(LMODEL, 1);
	draw_logo();
	lmbind(LMODEL, 0);
	popmatrix();
    }


	if (view_from[Y] < 0.0) draw_under_table();


	swapbuffers();


    }
}

initialize(title)
char *title;
{

    keepaspect(5, 4);
	{
		char *t, *strrchr();
		winopen((t=strrchr(title, '/')) != NULL ? t+1 : title);
	}

    doublebuffer();
    RGBmode();
    gconfig();

	if (getplanes() < 12)
	{
		fprintf(stderr, "%s needs at least 12 bitplanes\n", title);
		gexit();
		exit(1);
	}

    qdevice(LEFTMOUSE);
    qdevice(ESCKEY);
    qdevice(WINQUIT);

    defpattern(HALFTONE, 16, halftone);

    lsetdepth(0x0, 0x7fffff);
    lmdef(DEFLIGHT, 1, 0, light1);
    lmdef(DEFLIGHT, 2, 0, light2);
    lmdef(DEFLIGHT, 3, 0, light3);
    lmdef(DEFLMODEL, 1, 0, lmodel);

    init_materials();

    build_table();

    view_from_spline = calc_spline_params(view_from_ctl, TIME);
    view_to_spline = calc_spline_params(view_to_ctl, TIME);
    light_pos_spline = calc_spline_params(light_pos_ctl, TIME);
    logo_pos_spline = calc_spline_params(logo_pos_ctl, TIME);
    logo_rot_spline = calc_spline_params(logo_rot_ctl, TIME);

    perspective(150, ASPECT, 0.5, 20.0);

    mmode(MVIEWING);
}


build_table() {

    float i, j;

    for (j=0.0; j<=TABLERES; j+=1.0) {
	for (i=0.0; i<=TABLERES; i+=1.0) {
	    table_points[(int)j][(int)i][Z] = (i-TABLERES/2.0)/2.0;
	    table_points[(int)j][(int)i][X] = (j-TABLERES/2.0)/2.0;
	    table_points[(int)j][(int)i][Y] = 0.0;
	}
    }
}


void draw_table(float current_time) {

    float x, z, c;
    int i, j;
    int k, l;
    float m, n;
    float ov[3], lv[3];

    zbuffer(FALSE);

    ov[X] = light_pos[X]-logo_pos[X];
    ov[Y] = light_pos[Y]-logo_pos[Y];
    ov[Z] = light_pos[Z]-logo_pos[Z];

    normalize(ov);

    for (j=0; j<=TABLERES; j++) {
	for (i=0; i<=TABLERES; i++) {
	    lv[X] = light_pos[X] - table_points[j][i][X];
	    lv[Y] = light_pos[Y] - table_points[j][i][Y];
	    lv[Z] = light_pos[Z] - table_points[j][i][Z];
	    normalize(lv);
	    if ((c = dot(lv, ov))<0.0) c = 0.0;
	    c = c * c * c * lv[Y] * 255.0;
/* fade */
	    if ((current_time>TIME-5.0) && (current_time<TIME-3.0)) 
		c *= 1.0 - (current_time-(TIME-5.0)) * 0.5;

	    tablecolors[j][i] = (int)c;
	}
    }


    for (l=0; l<TABLERES; l++) {

	bgntmesh();
	for (k=0; k<=TABLERES; k++) {

	    RGBcolor(tablecolors[l][k],
		     tablecolors[l][k],
		     tablecolors[l][k]);
	    v3f(table_points[l][k]);

	    RGBcolor(tablecolors[l+1][k],
		     tablecolors[l+1][k],
		     tablecolors[l+1][k]);
	    v3f(table_points[l+1][k]);

	}
	endtmesh();
    }

    if (logo_pos[Y]>-0.33 && logo_pos[Y]<0.33) {
	zbuffer(TRUE);
    }

    pca = 0.0;
    bgnpolygon();
    for (i=0; i<4; i++) {
	lv[X] = light_pos[X] - paper_points[i][X];
	lv[Y] = light_pos[Y] - paper_points[i][Y];
	lv[Z] = light_pos[Z] - paper_points[i][Z];
	normalize(lv);
	if ((c = dot(lv, ov))<0.0) c = 0.0;
	c = c * c * c * lv[Y];
/* fade */
	    if ((current_time>TIME-5.0) && (current_time<TIME-3.0)) 
		c *= 1.0 - (current_time-(TIME-5.0)) * 0.5;

	pcr = c * 255; pcg = c * 255; pcb = c * 200;
	pca += c;
	RGBcolor((int)pcr, (int)pcg, (int)pcb);
	v3f(paper_points[i]);
    }
    endpolygon();

/*    RGBcolor(0, 200, 255);
    for (m = 0.4; m>-1.4; m -= 0.33) {
	move(-0.8+(m-4.0)/3.0, 0.0, m);
	draw(1.2-0.8+(m-4.0)/3.0, 0.0, m+0.4);
    }
*/


    zbuffer(FALSE);

    pushmatrix();

    rotate(-184, 'y');

    translate(-0.3, 0.0, -0.8);

    rotate(-900, 'x');

    scale(0.015, 0.015, 0.015);

    if (current_time>TIME-5.0) {
	c = (current_time-(TIME-5.0))/2.0;
	RGBcolor((int)(c*255.0), (int)(c*255.0), (int)(c*255.0));
    } else RGBcolor(0, 0, 0);


    draw_i();
    translate(3.0, 0.0, 0.0);

    draw_d();
    translate(6.0, 0.0, 0.0);

    draw_e();
    translate(5.0, 0.0, 0.0);

    draw_a();
    translate(6.0, 0.0, 0.0);

    draw_s();
    translate(10.0, 0.0, 0.0);

    draw_i();
    translate(3.0, 0.0, 0.0);

    draw_n();
    translate(-31.0, -13.0, 0.0);

    draw_m();
    translate(10.0, 0.0, 0.0);

    draw_o();
    translate(5.0, 0.0, 0.0);

    draw_t();
    translate(4.0, 0.0, 0.0);

    draw_i();
    translate(3.5, 0.0, 0.0);

    draw_o();
    translate(5.0, 0.0, 0.0);

    draw_n();

    popmatrix();

    zbuffer(TRUE);


}



draw_under_table() {

    int k, l;

    zbuffer(FALSE);


    RGBcolor(0, 0, 0);

    for (l=0; l<TABLERES; l++) {

	bgntmesh();
	for (k=0; k<=TABLERES; k++) {

	    v3f(table_points[l][k]);
	    v3f(table_points[l+1][k]);

	}
	endtmesh();
    }

    zbuffer(TRUE);

}



calc_spline(v, params, time)
vector v;
parameter *params;
float time;
{

    float t, tt;
    int i, j;

    tt = t = time - (float)((int)time);

    for (i=0; i<3; i++) {


	v[i] = params[(int)time][3][i] +
	       params[(int)time][2][i] * t +
	       params[(int)time][1][i] * t * t +
	       params[(int)time][0][i] * t * t * t;
    }

}


parameter *calc_spline_params(ctl_pts, n)
vector *ctl_pts;
int n;
{

    int i, j;
    parameter *params;

    if (n<4) {
	fprintf(stderr,
	    "calc_spline_params: not enough control points\n");
	return (NULL);
    }

    params = (parameter *)malloc(sizeof(parameter) * (n-3));

    for (i=0; i<n-3; i++) {

	for (j=0; j<3; j++) {

	    params[i][3][j] = ctl_pts[i+1][j];
	    params[i][2][j] = ctl_pts[i+2][j] - ctl_pts[i][j];
	    params[i][1][j] =  2.0 * ctl_pts[i][j] +
			      -2.0 * ctl_pts[i+1][j] +
			       1.0 * ctl_pts[i+2][j] +
			      -1.0 * ctl_pts[i+3][j];
	    params[i][0][j] = -1.0 * ctl_pts[i][j] +
			       1.0 * ctl_pts[i+1][j] +
			      -1.0 * ctl_pts[i+2][j] +
			       1.0 * ctl_pts[i+3][j];

	}
    }

    return (params);
}


normalize(v)
vector v;
{
    float r;

    r = sqrt(v[X]*v[X] + v[Y]*v[Y] + v[Z]*v[Z]);

    v[X] /= r;
    v[Y] /= r;
    v[Z] /= r;
}


float dot(v1, v2)
vector v1, v2;
{

    return v1[X]*v2[X]+v1[Y]*v2[Y]+v1[Z]*v2[Z];
}


