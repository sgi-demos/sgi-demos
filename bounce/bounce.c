#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "gl.h"
#include "device.h"

#define UDIV 12
#define VDIV 12

#define WALLGRID 8
#define EYEZ 3.3

#define TOTALBALLS 3

#define R 0
#define G 1
#define B 2

#define X 0
#define Y 1
#define Z 2
#define W 3

int freeze = FALSE;
int spin = TRUE;
int objecton = FALSE;
int normson = FALSE;
int lighton[3] = {
	TRUE, TRUE, TRUE};

struct {
	float p[3];
	float d[3];
	int color[3];
} balls[TOTALBALLS];

float ballobj[UDIV+1][VDIV+1][4];
float wallobj[WALLGRID+1][WALLGRID+1][4];
float wallnorms[WALLGRID+1][WALLGRID+1][3];
float wallnorm[3] = { 
	0.0, 0.0, -1.0 };

int rx, ry;
int orx, ory;
short   ory2, orx2;

float ballscale;
float ballsize;

long xsize, ysize;

int menu = 0;
int lflag = 0;

char machinetype[12];
static enum {
	MACH_CLOVER1, 
	MACH_CLOVER2, 
	MACH_ECLIPSE
} 
machine;

float rotm[3][3],rotmi[3][3],curmat[3][3];

Matrix ident4 = {
	{1.0, 0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}
};


float ident[3][3] = {
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0}
};

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



float light1[] = {
	AMBIENT,  0.0, 0.0, 0.0,
	LCOLOR,   1.0, 0.1, 0.1,
	POSITION, 0.0, 0.0, 0.0, 1.0,
	LMNULL };

float light2[] = {
	AMBIENT,  0.0, 0.0, 0.0,
	LCOLOR,   0.1, 1.0, 0.1,
	POSITION, 0.0, 0.0, 0.0, 1.0,
	LMNULL };

float light3[] = {
	AMBIENT,  0.0, 0.0, 0.0,
	LCOLOR,   0.1, 0.1, 1.0,
	POSITION, 0.0, 0.0, 0.0, 1.0,
	LMNULL };

float newpos[] = {
	POSITION, 0.0, 0.0, 0.0, 1.0,
	LMNULL };

float planemat[] = {
	EMISSION,   0.0, 0.0, 0.0,
	AMBIENT,    0.0, 0.0, 0.0,
	DIFFUSE,    0.4, 0.4, 0.4,
	SPECULAR,   1.0, 1.0, 1.0,
	SHININESS, 30.0,
	LMNULL };

float wallmat[] = {
	EMISSION,   0.0, 0.0, 0.0,
	AMBIENT,    0.1, 0.1, 0.1,
	DIFFUSE,    0.8, 0.8, 0.8,
	SPECULAR,   1.0, 1.0, 1.0,
	SHININESS, 20.0,
	LMNULL };

float lmodel[] = {
	AMBIENT,0.3,0.3,0.3,
	LOCALVIEWER,1.0,
	ATTENUATION, 1.0, 3.0, 
	LMNULL };

extern float frand();

char ofile[80];


/************************************************************/
/* XXX - The following is an excerpt from spin.h from spin  */
/************************************************************/

#define POLYGON	1
#define LINES	2
#define TRANSPERENT 3
#define DISPLAY	4
#define LMATERIAL 5

#define FASTMAGIC	0x5423

typedef struct fastobj {
	int npoints;
	int colors;
	int type;
	int material;
	int display;
	int ablend;
	int *data;
} fastobj;

fastobj *readfastobj();

/*
 * Wrappers to do either lines or polygons
 */
#define PolyOrLine()	if (lflag == LINES) { \
				bgnclosedline(); \
			} else if (POLYGON) { \
				bgnpolygon(); \
			}

#define EndPolyOrLine() if (lflag == LINES) { \
				endclosedline(); \
			} else if (POLYGON) { \
				endpolygon(); \
			}

/************************* end of spin.h excerpt *************************/


fastobj	*obj = NULL;

void reorient(short ax, short ay)
{
	pushmatrix();

	loadmatrix(ident_matrix);

	// rotate(-450, 'y');

	rotate((Angle) ax, 'y');
	rotate((Angle) ay, 'x');

	// rotate(450, 'y');

	multmatrix(view);

	getmatrix(view);

	popmatrix();
}

short tilt_left = -200;
short tilt_right = 200;
short tilt_forward = 650;
short tilt_back = 150;

void get_tilt(short *tiltx, short *tilty)
{
    *tiltx = XMAXSCREEN * (getvaluator(DIAL1) - tilt_forward) / (tilt_back - tilt_forward) ;
    *tilty = YMAXSCREEN * (getvaluator(DIAL0) - tilt_left) / (tilt_right - tilt_left);
}


main(argc, argv)
int argc;
char **argv;
{
	if (argc > 1)
	{
		int i;

		for (i=0; argv[1][i] != '/' && argv[1][i] != '\0'; i++);
		if (argv[1][i] != '/') {
			strcpy(ofile, "/usr/demos/data/models/");
			strcat(ofile, argv[1]);
		} else
			strcpy(ofile, argv[1]);

		if ((obj = readfastobj(ofile)) != NULL)
			objecton = TRUE;
	}

	ballsize = .04;
	ballscale = 1.0 - ballsize;

	initialize(argv);

	get_tilt(&orx2, &ory2);

	make_menu();

	resetballs();

	/* Use local lights for the box */
	lmbind(LIGHT0, 1);
	lmbind(LIGHT1, 2);
	lmbind(LIGHT2, 3);

	mmode(MPROJECTION);
	getsize(&xsize, &ysize);
	perspective(400, (float)xsize/ysize, EYEZ-2.0, EYEZ+2.0);
	mmode(MVIEWING);
	loadmatrix(ident4);
	translate(0.0, 0.0, -EYEZ);

	while(1)  {
		calcbox();
		if (!freeze)
			calcball();
		drawimage();
	}
}

resetballs()
{
	register short i;

	balls[0].color[R] = 255;
	balls[0].color[G] = 64;
	balls[0].color[B] = 64;
	balls[1].color[R] = 64;
	balls[1].color[G] = 255;
	balls[1].color[B] = 64;
	balls[2].color[R] = 64;
	balls[2].color[G] = 64;
	balls[2].color[B] = 255;
	for (i = 0; i < TOTALBALLS; i++) {
		balls[i].p[0] = 0.0;
		balls[i].p[1] = 0.0;
		balls[i].p[2] = 0.0;
		balls[i].d[0] = .1*frand();
		balls[i].d[1] = .1*frand();
		balls[i].d[2] = .1*frand();
	}
}

drawimage()
{
	register short i;

	check_q();

	zbuffer(FALSE);
	czclear(0,0xffffffff);

	lmbind(LMODEL, 1);

	pushmatrix();

	multmatrix(view);

	for (i=0; i < TOTALBALLS; i++) {
		newpos[1] = balls[i].p[0];
		newpos[2] = balls[i].p[1];
		newpos[3] = balls[i].p[2];
		lmdef( DEFLIGHT, i+1, 6, newpos );
	}

	lmbind(MATERIAL, 1);
	drawbox();

	zbuffer(TRUE);

	if (objecton)
	{
		lmbind(MATERIAL, 2);
		pushmatrix();
		scale(1.5, 1.5, 1.5);
		rotate(1800, 'z');
		if (spin)
		{
			orx += 50.0 / 3.0;
			ory += 50.0 / 3.0;
		}
		rotate(orx, 'x');
		rotate(ory, 'y');
		drawfastobj(obj);
		popmatrix();
	}

	lmbind(LMODEL, 0);

	for (i=0; i < TOTALBALLS; i++) {
		if (lighton[i])
		{
			pushmatrix();
			translate( balls[i].p[0],balls[i].p[1],balls[i].p[2] );
			c3i(balls[i].color);
			drawball();
			popmatrix();
		}
	}

	popmatrix();
	swapbuffers();
}


initialize(argv)
char **argv;
{
	int time();
	void srand();

	{	/* Open window with name of executable */
		char *t, *strrchr();
		winopen((t=strrchr(argv[0], '/')) != NULL ? t+1 : argv[0]);
	}
	if (getplanes() < 12)
	{
		fprintf(stderr, "You must have at least 12 bitplane to run %s",
		    argv[0]);
		gexit();
		exit(1);
	}

	doublebuffer();
	RGBmode();
	gconfig();

	lsetdepth(0, 0x7fffff);

	initobjects();

	srand((unsigned)time(0));

	lmdef(DEFLMODEL, 1, 10, lmodel);
	lmdef(DEFMATERIAL, 1, 19, wallmat);
	lmdef(DEFMATERIAL, 2, 19, planemat);
	lmdef(DEFLIGHT, 1, 14, light1);
	lmdef(DEFLIGHT, 2, 14, light2);
	lmdef(DEFLIGHT, 3, 14, light3);

	qdevice(LEFTMOUSE);
	tie(LEFTMOUSE, MOUSEX, MOUSEY);
	qdevice(RIGHTMOUSE);
	qdevice(ESCKEY);

        loadmatrix(ident_matrix);
}


initobjects()
{
	register float u,v,du,dv;
	register short i,j;

	du = 2.0*3.1416/UDIV;
	dv = 3.1416/VDIV;

	u = 0.;
	for (i=0; i <= UDIV; i++) {
		v = 0.;
		for (j=0; j <= VDIV; j++) {
			ballobj[i][j][X] = ballsize*cos(u)*sin(v);
			ballobj[i][j][Y] = ballsize*sin(u)*sin(v);
			ballobj[i][j][Z] = ballsize*cos(v);
			ballobj[i][j][W] = 1.0;
			v += dv;
		}
		u += du;
	}

	for (i=0; i <= WALLGRID; i++) {
		for (j=0; j <= WALLGRID; j++) {
			wallobj[i][j][X] = -1.0 + 2.0*i/WALLGRID;
			wallobj[i][j][Y] = -1.0 + 2.0*j/WALLGRID;
			wallobj[i][j][Z] = 1.0;
			wallobj[i][j][W] = 1.0;
		}
	}

	for (i=0; i <= WALLGRID; i++) {
		for (j=0; j <= WALLGRID; j++) {
			wallnorms[i][j][X] = wallobj[i][j][X] + wallnorm[X]*0.1;
			wallnorms[i][j][Y] = wallobj[i][j][Y] + wallnorm[Y]*0.1;
			wallnorms[i][j][Z] = wallobj[i][j][Z] + wallnorm[Z]*0.1;
		}
	}
}


drawball()
{
	register int i,j;

	for (i=0; i < UDIV; i++) {
		for (j=0; j < VDIV; j++) {
			bgnpolygon();
			v4f( ballobj[i][j] );
			v4f( ballobj[i+1][j] );
			v4f( ballobj[i+1][j+1] );
			v4f( ballobj[i][j+1] );
			endpolygon();
		}
	}
}


drawface()
{
	register int i,j;

	n3f(wallnorm);
	for (i=0; i < WALLGRID; i++) {
		bgntmesh();
		for (j=0; j <= WALLGRID; j++) {
			v3f(wallobj[i][j]);
			v3f(wallobj[i+1][j]);
		}
		endtmesh();
	}
	/*
    n3f(wallnorm);
    for (i=0; i < WALLGRID; i++) {
	for (j=0; j < WALLGRID; j++) {
	    bgnpolygon();
	    v3f(wallobj[i][j]);
	    v3f(wallobj[i+1][j]);
	    v3f(wallobj[i+1][j+1]);
	    v3f(wallobj[i][j+1]);
	    endpolygon();
	}
    }
*/
}


drawnorms()
{
	register int i,j;

	lmbind(LMODEL, 0);
	RGBcolor(255, 0, 255);
	for (i=0; i <= WALLGRID; i++) {
		for (j=0; j <= WALLGRID; j++) {
			bgnline();
			v3f(wallobj[i][j]);
			v3f(wallnorms[i][j]);
			endline();
		}
	}
	lmbind(LMODEL, 1);
}


drawbox()
{
	backface(TRUE);

	pushmatrix();

	drawface();
	rotate(900, 'y');
	drawface();
	if (normson) drawnorms();
	rotate(900, 'y');
	drawface();
	if (normson) drawnorms();
	rotate(900, 'y');
	drawface();
	rotate(-900, 'x');
	drawface();
	if (normson) drawnorms();
	rotate(1800, 'x');
	drawface();
	popmatrix();

	backface(FALSE);
}


calcbox()
{
    	// mousey = 0 -> rx = -50
	// mousey = 480 -> rx = -850
	rx = -800*getvaluator(MOUSEY)/YMAXSCREEN - 50;
    	// mousex = 0 -> ry = 50
	// mousex = 800 -> ry = 850
	ry = 50 + 800*getvaluator(MOUSEX)/XMAXSCREEN;

	int tilt_left = -200;
	int tilt_right = 200;
	int tilt_forward = 650;
	int tilt_back = 150;
	int rx2 = XMAXSCREEN * (getvaluator(DIAL1) - tilt_forward) / (tilt_back - tilt_forward) ;
	int ry2 = YMAXSCREEN * (getvaluator(DIAL0) - tilt_left) / (tilt_right - tilt_left);
	rx = -800*rx2/YMAXSCREEN - 50;
	ry = 50 + 800*ry2/XMAXSCREEN;
}


calcball()
{
	register short i,j;

	for (j=0; j < TOTALBALLS; j++) {
		for (i=0; i < 3; i++) {
			balls[j].p[i] += balls[j].d[i];
			if (fabs(balls[j].p[i]) > ballscale) {
				balls[j].p[i] = (balls[j].p[i] > 0.0) ?
				    ballscale : -ballscale;
				balls[j].d[i] = -balls[j].d[i];
			}
		}
	}
}


float frand()
{
	return 2.0*((rand() % 32768)/32768.0 - .5);
}

int function = 0;
#define REORIENT 1
short   omx, omy;


check_q()
{
	short val;

	while(qtest())
	{
		switch(qread(&val))
		{
                case LEFTMOUSE:
			if (val) {
			    qread(&omx); qread(&omy);
			    function = REORIENT;
			} else {
			    function = 0;
			    get_tilt(&orx2, &ory2);
			}
                        break;
		case REDRAW:
			reshapeviewport();
			break;
		case ESCKEY:
			if (!val)
			{
				gexit();
				exit(0);
			}
			break;
		case MENUBUTTON:
			if (val)
				switch(dopup(menu)) {
				case 1:
					if ((lighton[0] = !lighton[0]))
						lmbind(LIGHT0, 1);
					else
						lmbind(LIGHT0, 0);
					break;
				case 2:
					if ((lighton[1] = !lighton[1]))
						lmbind(LIGHT1, 2);
					else
						lmbind(LIGHT1, 0);
					break;
				case 3:
					if ((lighton[2] = !lighton[2]))
						lmbind(LIGHT2, 3);
					else
						lmbind(LIGHT2, 0);
					break;
				case 4:
					freeze =  !freeze;
					break;
				case 5:
					if (obj)
						objecton =  !objecton;
					else
						exit(0);
					break;
				case 6:
					spin =  !spin;
					break;
				case 7:
					exit(0);
					break;
				}
			make_menu();
			break;
		default:
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

		reorient(ax, ay);
		break;
	    }
	}
}


make_menu()
{
	char buf[256];

	if (menu)
		freepup(menu);

	strcpy(buf, "bounce %t");

	if (lighton[0])
		strcat(buf, "|red light off");
	else
		strcat(buf, "|red light on");
	if (lighton[1])
		strcat(buf, "|green light off");
	else
		strcat(buf, "|green light on");
	if (lighton[2])
		strcat(buf, "|blue light off");
	else
		strcat(buf, "|blue light on");

	if (freeze)
		strcat(buf, "|unfreeze lights");
	else
		strcat(buf, "|freeze lights");

	if (obj) {
		if (objecton)
			strcat(buf, "|object off");
		else
			strcat(buf, "|object on");
		if (spin)
			strcat(buf, "|object spin off");
		else
			strcat(buf, "|object spin on");
	}

	strcat(buf, "|exit");

	menu = defpup(buf);
}

/**********************************************************/
/* XXX - The following is a clone of fastobj.c from spin  */
/**********************************************************/


fastobj *readfastobj(name)
char *name;
{
	FILE *inf;
	fastobj *obj;
	int i;
	int nlongs;
	int magic;
	int *ip;
	char filename[512];

	inf = fopen(name,"r");
	if(!inf) {
		sprintf(filename,"%s",name);
		inf = fopen(filename,"r");
		if(!inf) {
			fprintf(stderr,"readfast: can't open input file %s\n",name);
			exit(1);
		}
	}
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
	fread(&magic,sizeof(int),1,inf);
#pragma GCC diagnostic pop
        magic = ntohl(magic);
	if(magic != FASTMAGIC) {
		fprintf(stderr,"readfast: bad magic in object file\n");
		fclose(inf);
		exit(1);
	}
	obj = (fastobj *)malloc(sizeof(fastobj));
	obj->type = ntohl(obj->type);
	obj->material = ntohl(obj->material);
	obj->display = ntohl(obj->display);
	obj->ablend = ntohl(obj->ablend);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
	fread(&obj->npoints,sizeof(int),1,inf);
#pragma GCC diagnostic pop
	obj->npoints = ntohl(obj->npoints);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
	fread(&obj->colors,sizeof(int),1,inf);
#pragma GCC diagnostic pop
	obj->colors = ntohl(obj->colors);

	/*
     * Insure that the data is quad-word aligned and begins on a page
     * boundary.  This shields us from the performance loss which occurs 
     * whenever we try to fetch data which straddles a page boundary  (the OS
     * has to map in the next virtual page and re-start the DMA transfer).
     */
	nlongs = 8 * obj->npoints;
	obj->data = (int *) malloc(nlongs*sizeof(int) + 4096);
	//obj->data = (int *) (((int)(obj->data)) + 0xfff);
	//obj->data = (int *) (((int)(obj->data)) & 0xfffff000);

	for (i = 0, ip = obj->data;  i < nlongs/4;  i++, ip += 4) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
		fread(ip, 3 * sizeof(int), 1, inf);
#pragma GCC diagnostic pop
                ip[0] = ntohl(ip[0]);
                ip[1] = ntohl(ip[1]);
                ip[2] = ntohl(ip[2]);
        }
	fclose(inf);
	return obj;
}


drawfastobj(obj)
fastobj *obj;
{
	register int *p,*end;
	register int npolys;

	p = obj->data;
	end = p + 8 * obj->npoints;

	if(obj->colors) {
		npolys = obj->npoints/4;
		p = obj->data;
		while(npolys--) {
			PolyOrLine();
			c3i(p);
			v3f((float *) p+4);
			c3i(p+8);
			v3f((float *) p+12);
			c3i(p+16);
			v3f((float *) p+20);
			c3i(p+24);
			v3f((float *) p+28);
			EndPolyOrLine();
			p += 32;
		}
	} else {
		while ( p < end) {
			PolyOrLine();
			n3f((float *) p);
			v3f((float *) p+4);
			n3f((float *) p+8);
			v3f((float *) p+12);
			n3f((float *) p+16);
			v3f((float *) p+20);
			n3f((float *) p+24);
			v3f((float *) p+28);
			EndPolyOrLine();
			p += 32;
		}
	}
}


/*
 * objmaxpoint
 *
 * find the vertex farthest from the origin,
 * so we can set the near and far clipping planes tightly.
 */

#define MAXVERT(v) if ( (len = sqrt(	(*(v))  *  (*(v))  +	       \
					(*(v+1)) * (*(v+1)) +	       \
					(*(v+2)) * (*(v+2)) )) > max)  \
			max = len;

float
objmaxpoint(obj)
fastobj *obj;
{
	register float *p, *end;
	register int npolys;
	register float len;
	register float max = 0.0;

	p = (float *) (obj->data);

	if (obj->colors) {
		npolys = obj->npoints/4;
		while(npolys--) {
			MAXVERT(p+4);
			MAXVERT(p+12);
			MAXVERT(p+20);
			MAXVERT(p+28);
			p += 32;
		}
	} else {
		end = p + 8 * obj->npoints;
		while ( p < end) {
			MAXVERT(p+4);
			MAXVERT(p+12);
			MAXVERT(p+20);
			MAXVERT(p+28);
			p += 32;
		}
	}

	return max;
}
