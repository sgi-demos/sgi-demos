#ifndef GLDEF	/* Release 2.3 */
#define GLDEF
/**************************************************************************
 *									  *
 * 		 Copyright (C) 1984, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#include <stdint.h>

/* graphics libary header file */

/* maximum X and Y screen coordinates */

#define XMAXSCREEN	799
#define YMAXSCREEN	479

/* various hardware/software limits	*/

#define ATTRIBSTACKDEPTH	10
#define VPSTACKDEPTH		8
#define MATRIXSTACKDEPTH	32
#define NAMESTACKDEPTH		1025
#define STARTTAG		-2
#define ENDTAG			-3
#define MAXFONTNC		256   /* max size of font offset array */
#define MINFONTNC		128   /* for compatibility with old fonts */

/* names for colors in color map loaded by ginit() */

#define BLACK		0
#define RED		1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define WHITE		7

/* popup colors */

#define PUP_CLEAR	0
#define PUP_CURSOR	1
#define PUP_BLACK	2
#define PUP_WHITE	3

#ifndef FALSE
#define	FALSE		0
#endif
#ifndef TRUE
#define TRUE		(!FALSE)
#endif

// No idea what these should be. For drawmode().
#define OVERDRAW        0
#define UNDERDRAW       1
#define CURSORDRAW      2
#define NORMALDRAW      3

/* typedefs */

typedef uint8_t Byte;
typedef int Boolean;
typedef char *String;

typedef short Angle;
typedef short Screencoord;
typedef short Scoord;
typedef int32_t Icoord;
typedef float Coord;
typedef float Matrix[4][4];

typedef uint16_t Colorindex;
typedef uint8_t RGBvalue;

typedef uint16_t Device;

#define PATTERN_16 16
#define PATTERN_32 32
#define PATTERN_64 64

#define PATTERN_16_SIZE	16
#define PATTERN_32_SIZE	64
#define PATTERN_64_SIZE	256

typedef uint16_t Pattern16[PATTERN_16_SIZE];
typedef uint16_t Pattern32[PATTERN_32_SIZE];
typedef uint16_t Pattern64[PATTERN_64_SIZE];

typedef uint16_t Linestyle;
typedef uint16_t Cursor[16];

typedef struct {
	uint16_t offset;
	Byte w,h;
	char xoff,yoff;
	short width;
} Fontchar;

typedef int32_t Object;
typedef int32_t Tag;
typedef int32_t Offset;

extern void	addtopup(int32_t menu, char *add);
extern void	arc();
extern void	arcf();
extern void	arcfi();
extern void	arci();
extern void	arcfs();
extern void	arcs();
extern void	attachcursor();
extern void	backbuffer();
extern void	backface(int enable);
extern void	bbox2();
extern void	bbox2i();
extern void	bbox2s();
extern void	blankscreen();
extern void	blanktime();
extern void	blink();
extern int32_t	blkqread();
extern void	callfunc();
extern void	callobj(Object obj);
extern void	capture();
extern void	charstr(char *str);
extern void	circ();
extern void	circf();
extern void	circfi();
extern void	circi(Icoord x, Icoord y, Icoord r);
extern void	circfs(Scoord x, Scoord y, Scoord r);
extern void	circs();
extern void	clear();
extern void	clearhitcode();
extern void	clkoff();
extern void	clkon();
extern void	closeobj();
extern void	cmov();
extern void	cmov2();
extern void	cmov2i(Icoord x, Icoord y);
extern void	cmovi();
extern void	cmov2s(Scoord x, Scoord y);
extern void	cmovs();
extern void	color(Colorindex c);
extern void	compactify();
extern void	crv();
extern void	crvn();
extern void	curorigin(int16_t index, int16_t xorigin, int16_t yorigin);
extern void	cursoff();
extern void	curson();
extern void	curvebasis();
extern void	curveit();
extern void	curveprecision();
extern void	cyclemap();
extern void	dbtext();
extern void	defbasis();
extern void	defcursor(int32_t index, uint16_t *cursor);
extern void	deflinestyle();
extern void	defpattern(int32_t index, int size, Pattern16 mask);
extern int32_t     defpup(char *menu);
extern void	defrasterfont();
extern void	delobj(Object obj);
extern void	deltag();
extern void	depthcue();
extern void	devport();
extern int32_t	dopup(int32_t pup);
extern int32_t	dopupbut();
extern void	doublebuffer();
extern void	draw(Coord x, Coord y, Coord z);
extern void	draw2(Coord x, Coord y);
extern void	draw2i(Icoord x, Icoord y);
extern void	draw2s(Scoord x, Scoord y);
extern void     drawmode(int32_t drawmode);
extern void	drawi(Icoord x, Icoord y, Icoord z);
extern void	draws(Scoord x, Scoord y, Scoord z);
extern void	editobj();
extern int32_t	endfeedback();
extern void	endfullscrn();
extern int32_t	endpick();
extern void	endpupmode();
// extern int32_t	endselect();
extern void	feedback();
extern void	finish();
extern void	font();
extern void	foreground();
extern void	freepup();
extern void	frontbuffer();
extern void	fudge();
extern void	fullscrn();
extern void	gbegin();
extern void	gconfig();
extern Object	genobj();
extern Tag	gentag();
extern int32_t	getbuffer();
extern Boolean	getbutton();
extern Boolean	getcmmode();
extern int32_t	getcolor();
extern void	getcpos();
extern void	getcursor();
extern Boolean	getdcm();
extern void	getdepth();
extern void	getdev();
extern int32_t	getdisplaymode();
extern int32_t	getfont();
extern void	getgpos();
extern int32_t	getheight();
extern int32_t	gethitcode();
extern Boolean	getlsbackup();
extern int32_t	getlsrepeat();
extern int32_t	getlstyle();
extern int32_t	getlwidth();
extern int32_t	getmap();
extern void	getmatrix(Matrix m);
extern void	getmcolor(Colorindex index, int16_t *red, int16_t *green, int16_t *blue);
extern int32_t	getmem();
extern int32_t	getmonitor();
extern void	getorigin();
extern Object	getopenobj();
extern int32_t	getothermonitor();
extern int32_t	getpattern();
extern int32_t	getplanes();
extern void	getport();
extern Boolean	getresetls();
extern void	getscrmask();
extern int32_t	getshade();
extern void	getsize();
extern void	gettp();
extern int32_t	getvaluator(int32_t device);
extern void	getviewport();
extern int32_t	getwritemask();
extern Boolean	getzbuffer();
extern void	gewrite();
extern void	gexit();
extern void	gflush();
extern void	ginit();
extern void	gselect();
extern void	greset();
extern void	gsync();
extern void	gRGBcolor(int32_t r, int32_t g, int32_t b);
extern void	gRGBcursor();
extern void	gRGBmask();
extern void     icontitle(char *name);
extern void	imakebackground();
extern void	initnames();
extern Boolean	ismex();
extern Boolean	isobj(Object obj);
extern Boolean	isqueued();
extern Boolean	istag();
extern void	keepaspect();
extern void	lampoff();
extern void	lampon();
extern void	linewidth(int w);
extern void	loadmatrix(Matrix m);
extern void	loadname();
extern void	lookat(Coord viewx, Coord viewy, Coord viewz, Coord pointx, Coord pointy, Coord pointz, Angle twist);
extern void	lsbackup();
extern void	lsrepeat();
extern void	makeobj();
extern void	maketag();
extern void     mapcolor(Colorindex index, int red, int green, int blue);
extern void	mapw();
extern void	mapw2();
extern void	maxsize();
extern void	minsize();
extern void	move(Coord x, Coord y, Coord z);
extern void	move2(Coord x, Coord y);
extern void	move2i(Icoord x, Icoord y);
extern void	move2s(Scoord x, Scoord y);
extern void	movei(Icoord x, Icoord y, Icoord z);
extern void	moves(Scoord x, Scoord y, Scoord z);
extern void	multimap();
extern void	multmatrix();
extern int32_t	newpup();
extern void	newtag();
extern void     noborder();
extern void	noise();
extern void	noport();
extern void	objdelete();
extern void	objinsert();
extern void	objreplace();
extern void	onemap();
extern void	ortho();
extern void	ortho2(Coord left, Coord right, Coord bottom, Coord top);
extern void	pagecolor();
extern void	pagewritemask();
extern void	passthrough();
extern void	patch();
extern void	patchbasis();
extern void	patchcurves();
extern void	patchprecision();
extern void	pclos();
extern void	pdr(Coord x, Coord y, Coord z);
extern void	pdr2();
extern void	pdr2i(Icoord x, Icoord y);
extern void	pdr2s();
extern void	pdri(Icoord x, Icoord y, Icoord z);
extern void	pdrs();
extern void	perspective(Angle fovy_, float aspect, Coord near, Coord far);
extern void	pick();
extern void	picksize();
extern void	pmv(Coord x, Coord y, Coord z);
extern void	pmv2();
extern void	pmv2i(Icoord x, Icoord y);
extern void	pmv2s();
extern void	pmvi(Icoord x, Icoord y, Icoord z);
extern void	pmvs();
extern void	pnt(Coord x, Coord y, Coord z);
extern void	pnt2(Coord x, Coord y);
extern void	pnt2i(Icoord x, Icoord y);
extern void	pnt2s(Scoord x, Scoord y);
extern void	pnti(Icoord x, Icoord y, Icoord z);
extern void	pnts(Scoord x, Scoord y, Scoord z);
extern void	polarview();
extern void	polf2();
extern void	polf2i();
extern void	polf2s();
extern void	polfi();
extern void	polfs();
extern void	poly(int n, Coord p[][3]);
extern void	polf(int32_t n, Coord p[][3]);
extern void	poly2(int n, Coord p[][2]);
extern void	poly2i(int n, Icoord p[][2]);
extern void	poly2s(int n, Scoord p[][2]);
extern void	polyi(int n, Icoord p[][3]);
extern void	polys(int n, Scoord p[][3]);
extern void	popattributes();
extern void	popmatrix();
extern void	popname();
extern void	popviewport();
extern void	prefposition();
extern void	prefsize();
extern void	pupcolor();
extern void	pupmode();
extern void	pushattributes();
extern void	pushmatrix();
extern void	pushname();
extern void	pushviewport();
extern void	qdevice();
extern void	qenter();
extern int32_t	qread();
extern void	qreset();
extern int32_t	qtest();
extern void	rcapture();
extern void	rcrv();
extern void	rcrvn();
extern void	rdr();
extern void	rdr2();
extern void	rdr2i(Icoord dx, Icoord dy);
extern void	rdr2s();
extern void	rdri();
extern void	rdrs();
extern int32_t	readpixels();
extern int32_t	readRGB();
extern void     rect(Coord x1, Coord y1, Coord x2, Coord y2);
extern void	rectcopy();
extern void     rectf(Coord x1, Coord y1, Coord x2, Coord y2);
extern void	rectfi(Icoord x1, Icoord y1, Icoord x2, Icoord y2);
extern void     rectfs(Scoord x1, Scoord y1, Scoord x2, Scoord y2);
extern void	recti(Icoord x1, Icoord y1, Icoord x2, Icoord y2);
extern void	rects(Scoord x1, Scoord y1, Scoord x2, Scoord y2);
extern void	resetls();
extern void	reshapeviewport();
extern void	RGBcolor();
extern void	RGBcursor();
extern void	RGBmode();
extern void	RGBwritemask();
extern void	ringbell();
extern void	rmv();
extern void	rmv2();
extern void	rmv2i(Icoord dx, Icoord dy);
extern void	rmv2s();
extern void	rmvi();
extern void	rmvs();
extern void	rot();
extern void	rotate(Angle angle, char axis);
extern void	rpatch();
extern void	rpdr();
extern void	rpdr2();
extern void	rpdr2i();
extern void	rpdr2s();
extern void	rpdri();
extern void	rpdrs();
extern void	rpmv();
extern void	rpmv2();
extern void	rpmv2i();
extern void	rpmv2s();
extern void	rpmvi();
extern void	rpmvs();
extern void	scale(float x, float y, float z);
extern void	screenspace();
extern void	scrmask();
// extern void	select();
extern void	setbell();
extern void	setbutton();
extern void	setcursor(int16_t index, Colorindex color, Colorindex  writemask);
extern void	setdblights();
extern void	setdepth();
extern Boolean	setfastcom();
extern void	setlinestyle(int32_t index);
extern void	setmap();
extern void	setmonitor();
extern void	setpattern(int32_t pattern);
extern void	setshade();
extern Boolean	setslowcom();
extern void	setvaluator(Device device, int init, int min, int max);
extern void	shaderange();
extern void	singlebuffer();
extern void	spclos();
extern void	splf();
extern void	splf2();
extern void	splf2i();
extern void	splf2s();
extern void	splfi();
extern void	splfs();
extern void	stepunit();
extern int32_t	strwidth();
extern void	swapbuffers();
extern void	swapinterval();
extern void	textcolor();
extern void	textinit();
extern void	textport();
extern void	textwritemask();
extern void     tie(int32_t button, int32_t val1, int32_t val2);
extern void	tpoff();
extern void	tpon();
extern void	translate(Coord x, Coord y, Coord z);
extern void	unqdevice(Device device);
extern void	viewport(Screencoord left, Screencoord right, Screencoord bottom, Screencoord top);
extern int32_t	winattach();
extern void	winclose();
extern void	winconstraints();
extern void	window(Coord left, Coord right, Coord bottom, Coord top, Coord near, Coord far);
extern int32_t	winget();
extern void	winmove();
extern int32_t	winopen();
extern void	winpop();
extern void	winposition();
extern void	winpush();
extern void	winreshape();
extern int32_t	winset();
extern void	wintitle();
extern void	writemask(Colorindex writemask);
extern void	writepixels();
extern void	writeRGB();
extern void	xfpt();
extern void	xfpt2();
extern void	xfpt2i();
extern void	xfpt2s();
extern void	xfpt4();
extern void	xfpt4i();
extern void	xfpt4s();
extern void	xfpti();
extern void	xfpts();
extern void	zbuffer(int enable);
extern void	zclear();

extern void glcompat(int32_t mode, int32_t value);
extern void shademodel(int32_t mode);
extern void c3f(float c[3]);
extern void n3f(float n[3]);
extern void v3f(float v[3]);
extern void v2f(float v[2]);
extern void bgnpolygon();
extern void endpolygon();
extern void mmode(int32_t mode);
extern void lmdef(int deftype, int32_t index, int numpoints, float properties[]);
extern void lmbind(int target, int32_t index);

extern void bgnclosedline();
extern void endclosedline();
extern void bgnline();
extern void endline();
extern void bgntmesh();
extern void endtmesh();
extern int gversion(char *version);
extern void c3i(int c[3]);
extern void v4f(float c[3]);
extern void zfunction(int func);
extern void czclear(int color, int depth);

// Added by LK because demos needed it. I don't know what the real values should be.
#define GLC_OLDPOLYGON 2001
#define WINQUIT 2002

// Materials
#define DEFMATERIAL 0
#define LMNULL 0
#define EMISSION 1
#define AMBIENT 2
#define DIFFUSE 3
#define SPECULAR 4
#define SHININESS 5
#define ALPHA 7

// Lights
#define DEFLIGHT 100
#define LCOLOR 101
#define POSITION 102
#define SPOTDIRECTION 103
#define SPOTLIGHT 104

// Light Model
#define DEFLMODEL 200
#define LOCALVIEWER 201
#define ATTENUATION 202

// lmbind():
#define MATERIAL 1000
#define LIGHT0 1100
#define LIGHT1 1101
#define LIGHT2 1102
#define LIGHT3 1103
#define LIGHT4 1104
#define LIGHT5 1105
#define LIGHT6 1106
#define LIGHT7 1107
#define LMODEL 1200

// lmcolor():
#define LMC_COLOR 0
#define LMC_EMISSION 1
#define LMC_AMBIENT 2
#define LMC_DIFFUSE 3
#define LMC_SPECULAR 4
#define LMC_AD 5
#define LMC_NULL 6

// mmode():
#define MSINGLE 0
#define MPROJECTION 1
#define MVIEWING 2

#define FLAT 0
#define GOURAUD 1

#define ZF_GEQUAL 6

#endif // GLDEF
