#ifndef GLDEF	/* Release 2.3 */
#define GLDEF
/**************************************************************************
 *                                                                        *
 *       Copyright (C) 1984, Silicon Graphics, Inc.                       *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
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
#define RED		    1
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

typedef unsigned short Byte;
typedef int Boolean;
typedef char *String;

typedef short Angle;
typedef short Screencoord;
typedef short Scoord;
typedef int Icoord;
typedef float Coord;
typedef float Matrix[4][4];

typedef unsigned short Colorindex;
typedef unsigned short RGBvalue;

typedef unsigned short Device;

#define PATTERN_16 16
#define PATTERN_32 32
#define PATTERN_64 64

#define PATTERN_16_SIZE	16
#define PATTERN_32_SIZE	64
#define PATTERN_64_SIZE	256

typedef unsigned short Pattern16[PATTERN_16_SIZE];
typedef unsigned short Pattern32[PATTERN_32_SIZE];
typedef unsigned short Pattern64[PATTERN_64_SIZE];

typedef unsigned short Linestyle;
typedef unsigned short Cursor[16];

typedef struct {
	unsigned short offset;
	Byte w,h;
	char xoff,yoff;
	short width;
} Fontchar;

typedef int Object;
typedef int Tag;
typedef int Offset;

extern void	addtopup(long menu, char *add);
extern void	arc();
extern void	arcf();
extern void	arcfi();
extern void	arci();
extern void	arcfs();
extern void	arcs();
extern void	attachcursor();
extern void	backbuffer(Boolean enable);
extern void	backface(int enable);
extern void	bbox2();
extern void	bbox2i();
extern void	bbox2s();
extern void	blankscreen();
extern void	blanktime();
extern void	blink();
extern int	blkqread();
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
extern void	curorigin(short index, short xorigin, short yorigin);
extern void	cursoff();
extern void	curson();
extern void	curvebasis();
extern void	curveit();
extern void	curveprecision();
extern void	cyclemap();
extern void	dbtext();
extern void	defbasis();
extern void	defcursor(int index, short *cursor);
extern void	deflinestyle(int index, Linestyle pattern);
extern void	defpattern(int index, int size, Pattern16 mask);
extern int  defpup(char *menu, ...);
extern void	defrasterfont();
extern void	delobj(Object obj);
extern void	deltag();
extern void	depthcue(Boolean enable);
extern void	devport();
extern int	dopup(int pup);
extern int	dopupbut();
extern void	doublebuffer();
extern void	draw(Coord x, Coord y, Coord z);
extern void	draw2(Coord x, Coord y);
extern void	draw2i(Icoord x, Icoord y);
extern void	draw2s(Scoord x, Scoord y);
extern void drawmode(int drawmode);
extern void	drawi(Icoord x, Icoord y, Icoord z);
extern void	draws(Scoord x, Scoord y, Scoord z);
extern void	editobj(Object obj);
extern int	endfeedback();
extern void	endfullscrn();
extern int	endpick();
extern void	endpupmode();
// extern int endselect();
extern void	feedback();
extern void	finish();
extern void	font();
extern void	foreground();
extern void	freepup(int popup);
extern void	frontbuffer(Boolean enable);
extern void	fudge();
extern void	fullscrn();
extern void	gbegin();
extern void	gconfig();
extern Object	genobj();
extern Tag	gentag();
extern int	getbuffer();
extern Boolean	getbutton(int button);
extern Boolean	getcmmode();
extern int	getcolor();
extern void	getcpos();
extern void	getcursor();
extern Boolean	getdcm();
extern void	getdepth();
extern void	getdev();
extern int	getdisplaymode();
extern int	getfont();
extern int getgdesc (int inquiry);
extern void	getgpos();
extern int	getheight();
extern int	gethitcode();
extern Boolean	getlsbackup();
extern int	getlsrepeat();
extern int	getlstyle();
extern int	getlwidth();
extern int	getmap();
extern void	getmatrix(Matrix m);
extern void	getmcolor(Colorindex index, short *red, short *green, short *blue);
extern int	getmem();
extern int	getmonitor();
extern void	getorigin(long *x, long *y);
extern Object	getopenobj();
extern int	getothermonitor();
extern int	getpattern();
extern int	getplanes();
extern void	getport();
extern Boolean	getresetls();
extern void	getscrmask();
extern int	getshade();
extern void	getsize(long *width, long *height);
extern void	gettp();
extern int	getvaluator(int device);
extern void	getviewport();
extern int	getwritemask();
extern Boolean	getzbuffer();
extern void	gewrite();
extern void	gexit();
extern void	gflush();
extern void	ginit();
extern void	gselect();
extern void	greset();
extern void	gsync();
extern void	gRGBcolor(int r, int g, int b);
extern void	gRGBcursor();
extern void	gRGBmask();
extern void icontitle(char *name);
extern void	imakebackground();
extern void	initnames();
extern Boolean	ismex();
extern Boolean	isobj(Object obj);
extern Boolean	isqueued();
extern Boolean	istag();
extern void keepaspect(int x, int y);
extern void	lampoff();
extern void	lampon();
extern void	linewidth(int w);
extern void	loadmatrix(Matrix m);
extern void	loadname();
extern void	lookat(Coord viewx, Coord viewy, Coord viewz, Coord pointx, Coord pointy, Coord pointz, Angle twist);
extern void	lsbackup();
extern void lshaderange (Colorindex lowin, Colorindex highin, long znear, long zfar);
extern void	lsrepeat();
extern void	makeobj(Object obj);
extern void	maketag(Tag tag);
extern void mapcolor(Colorindex index, int red, int green, int blue);
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
extern void	multmatrix(Matrix m);
extern int	newpup();
extern void	newtag();
extern void noborder();
extern void	noise();
extern void	noport();
extern void	objdelete();
extern void	objinsert();
extern void	objreplace(Tag tag);
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
extern void	pmv2(Coord x, Coord y);
extern void	pmv2i(Icoord x, Icoord y);
extern void	pmv2s(Scoord x, Scoord y);
extern void	pmvi(Icoord x, Icoord y, Icoord z);
extern void	pmvs(Scoord x, Scoord y, Scoord z);
extern void	pnt(Coord x, Coord y, Coord z);
extern void	pnt2(Coord x, Coord y);
extern void	pnt2i(Icoord x, Icoord y);
extern void	pnt2s(Scoord x, Scoord y);
extern void	pnti(Icoord x, Icoord y, Icoord z);
extern void	pnts(Scoord x, Scoord y, Scoord z);
extern void	polarview();
extern void	polf2(int n, Coord p[][2]);
extern void	polf2i(int n, Icoord p[][2]);
extern void	polf2s(int n, Scoord p[][2]);
extern void	polfi(int n, Icoord p[][3]);
extern void	polfs(int n, Scoord p[][3]);
extern void	poly(int n, Coord p[][3]);
extern void	polf(int n, Coord p[][3]);
extern void	poly2(int n, Coord p[][2]);
extern void	poly2i(int n, Icoord p[][2]);
extern void	poly2s(int n, Scoord p[][2]);
extern void	polyi(int n, Icoord p[][3]);
extern void	polys(int n, Scoord p[][3]);
extern void	popattributes();
extern void	popmatrix();
extern void	popname();
extern void	popviewport();
extern void	prefposition(int x1, int x2, int y1, int y2);
extern void	prefsize();
extern void	pupcolor();
extern void	pupmode();
extern void	pushattributes();
extern void	pushmatrix();
extern void	pushname();
extern void	pushviewport();
extern void	qdevice(Device device);
extern void	qenter(short qtype, short value);
extern int	qread(short *val);
extern void	qreset();
extern int	qtest();
extern void	rcapture();
extern void	rcrv();
extern void	rcrvn();
extern void	rdr();
extern void	rdr2();
extern void	rdr2i(Icoord dx, Icoord dy);
extern void	rdr2s();
extern void	rdri();
extern void	rdrs();
extern int	readpixels();
extern int	readRGB();
extern void     rect(Coord x1, Coord y1, Coord x2, Coord y2);
extern void	rectcopy();
extern void     rectf(Coord x1, Coord y1, Coord x2, Coord y2);
extern void	rectfi(Icoord x1, Icoord y1, Icoord x2, Icoord y2);
extern void     rectfs(Scoord x1, Scoord y1, Scoord x2, Scoord y2);
extern void	recti(Icoord x1, Icoord y1, Icoord x2, Icoord y2);
extern void	rects(Scoord x1, Scoord y1, Scoord x2, Scoord y2);
extern void	resetls();
extern void	reshapeviewport();
extern void	RGBcolor(int r, int g, int b);
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
extern void	setcursor(short index, Colorindex color, Colorindex  writemask);
extern void	setdblights();
extern void	setdepth();
extern void	lsetdepth(int near, int far);
extern Boolean	setfastcom();
extern void	setlinestyle(int index);
extern void	setmap();
extern void	setmonitor();
extern void	setpattern(int pattern);
extern void	setshade();
extern Boolean	setslowcom();
extern void	setvaluator(Device device, int init, int min, int max);
extern void	shaderange();
extern void	singlebuffer();
extern void smoothline (long mode);
extern void	spclos();
extern void	splf();
extern void	splf2();
extern void	splf2i();
extern void	splf2s();
extern void	splfi();
extern void	splfs();
extern void	stepunit();
extern int	strwidth();
extern void	swapbuffers();
extern void	swapinterval();
extern void	textcolor();
extern void	textinit();
extern void	textport();
extern void	textwritemask();
extern void     tie(int button, int val1, int val2);
extern void	tpoff();
extern void	tpon();
extern void	translate(Coord x, Coord y, Coord z);
extern void	unqdevice(Device device);
extern void	viewport(Screencoord left, Screencoord right, Screencoord bottom, Screencoord top);
extern int	winattach();
extern void	winclose();
extern void	winconstraints();
extern void	window(Coord left, Coord right, Coord bottom, Coord top, Coord near, Coord far);
extern int	winget();
extern void	winmove();
extern int	winopen(char *title);
extern void	winpop();
extern void	winposition(int x1, int x2, int y1, int y2);
extern void	winpush();
extern void	winreshape();
extern int	winset();
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
extern void zsource (long src);

extern void glcompat(int mode, int value);
extern void shademodel(int mode);
extern void c3f(float c[3]);
extern void n3f(float n[3]);
extern void v3f(float v[3]);
extern void v2f(float v[2]);
extern void bgnpolygon();
extern void endpolygon();
extern void mmode(int mode);
extern void lmdef(int deftype, int index, int numpoints, float properties[]);
extern void lmbind(int target, int index);

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

extern void gl_sincos(Angle angle, float *s, float *c);

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

/* defines for zfunction() */
#define ZF_NEVER        0
#define ZF_LESS         1
#define ZF_EQUAL        2
#define ZF_LEQUAL       3
#define ZF_GREATER      4
#define ZF_NOTEQUAL     5
#define ZF_GEQUAL       6
#define ZF_ALWAYS       7
    
/* defines for zsource() */
#define ZSRC_DEPTH      0
#define ZSRC_COLOR      1

/* defines for getgdesc() */
#define GD_XPMAX                0
#define GD_YPMAX                1
#define GD_XMMAX                2
#define GD_YMMAX                3
#define GD_ZMIN                 4
#define GD_ZMAX                 5
#define GD_BITS_NORM_SNG_RED    6
#define GD_BITS_NORM_SNG_GREEN  7
#define GD_BITS_NORM_SNG_BLUE   8
#define GD_BITS_NORM_DBL_RED    9
#define GD_BITS_NORM_DBL_GREEN  10
#define GD_BITS_NORM_DBL_BLUE   11
#define GD_BITS_NORM_SNG_CMODE  12
#define GD_BITS_NORM_DBL_CMODE  13
#define GD_BITS_NORM_SNG_MMAP   14
#define GD_BITS_NORM_DBL_MMAP   15
#define GD_BITS_NORM_ZBUFFER    16
#define GD_BITS_OVER_SNG_CMODE  17
#define GD_BITS_UNDR_SNG_CMODE  18
#define GD_BITS_PUP_SNG_CMODE   19
#define GD_BITS_NORM_SNG_ALPHA  21 
#define GD_BITS_NORM_DBL_ALPHA  22
#define GD_BITS_CURSOR          23
#define GD_OVERUNDER_SHARED     24
#define GD_BLEND                25
#define GD_CIFRACT              26
#define GD_CROSSHAIR_CINDEX     27
#define GD_DITHER               28
#define GD_LINESMOOTH_CMODE     30
#define GD_LINESMOOTH_RGB       31
#define GD_LOGICOP              33
#define GD_NSCRNS               35
#define GD_NURBS_ORDER          36
#define GD_NBLINKS              37
#define GD_NVERTEX_POLY         39
#define GD_PATSIZE_64           40
#define GD_PNTSMOOTH_CMODE      41
#define GD_PNTSMOOTH_RGB        42
#define GD_PUP_TO_OVERUNDER     43
#define GD_READSOURCE           44
#define GD_READSOURCE_ZBUFFER   48
#define GD_STEREO               50
#define GD_SUBPIXEL_LINE        51
#define GD_SUBPIXEL_PNT         52
#define GD_SUBPIXEL_POLY        53
#define GD_TRIMCURVE_ORDER      54
#define GD_WSYS                 55
#define GD_ZDRAW_GEOM           57
#define GD_ZDRAW_PIXELS         58
#define GD_SCRNTYPE             61
#define GD_TEXTPORT             62
#define GD_NMMAPS               63
#define GD_FRAMEGRABBER         64
#define GD_TIMERHZ              66
#define GD_DBBOX                67
#define GD_AFUNCTION            68
#define GD_ALPHA_OVERUNDER      69
#define GD_BITS_ACBUF           70
#define GD_BITS_ACBUF_HW        71
#define GD_BITS_STENCIL         72
#define GD_CLIPPLANES           73
#define GD_FOGVERTEX            74
#define GD_LIGHTING_TWOSIDE     76
#define GD_POLYMODE             77
#define GD_POLYSMOOTH           78
#define GD_SCRBOX               79
#define GD_TEXTURE              80
#define GD_FOGPIXEL             81
#define GD_TEXTURE_PERSP        82
#define GD_MUXPIPES             83
#define GD_MULTISAMPLE          84
#define GD_TEXTURE_3D           85
#define GD_TEXTURE_LUT          86
#define GD_TEXTURE_SHARP        87
#define GD_TEXTURE_DETAIL       88
#define GD_STEREO_IN_WINDOW     89
#define GD_BLENDCOLOR           90
#define GD_LIGHTING_SPOTLIGHT   91
#define GD_LIGHTING_ATT2        92
#define GD_AFUNCTION_MODES      93
#define GD_TEXTURE_MEMORY_SIZE  94
#define GD_IS_IGLOO             95
#define GD_NOLIMIT              -2
#define GD_WSYS_NONE            0
#define GD_WSYS_4S              1
#define GD_SCRNTYPE_WM          0
#define GD_SCRNTYPE_NOWM        1

/* defines for glcompat */
#define GLC_OLDPOLYGON          0
#define GLC_ZRANGEMAP           1
#define GLC_MQUEUERATE          2
#define GLC_SOFTATTACH          3
#define GLC_MANAGEBG            4
#define GLC_SLOWMAPCOLORS       5
#define GLC_INPUTCHANGEBUG      6
#define GLC_NOBORDERBUG         7
#define GLC_SET_VSYNC           8
#define GLC_GET_VSYNC           9
#define GLC_VSYNC_SLEEP         10
#define GLC_FORCECIMAP          11
#define GLC_TABLETSCALE         12
#define GLC_NODESTALPHA         13
#define GLC_COMPATRATE          15

#endif // GLDEF
