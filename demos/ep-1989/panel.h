/*****************************************************************
    Panel Library/Electropaint Copyright (c) 1986 David A. Tristram.
    Electropaint (TM) is a Registered U.S. Trademark of Tristram Visual.
    Tristram Visual can be contacted at www.tristram.com.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. 
*****************************************************************/

/* sgi-demos: ep.c's main loop uses igl's IGL_MSG_PROCESS macro to pump
   Win32/X11 window events.  In sgi-demos the SDL event pump runs inside
   the IRIS GL calls themselves, so the macro expands to nothing. */
#ifndef IGL_MSG_PROCESS
#define IGL_MSG_PROCESS
#endif

/* external functions */

#ifdef lint
#ifdef IRIS_4D
long lseek(int, long, int);
char *calloc(unsigned, unsigned);
void exit(int);
void perror(char *);
int write(int, char *, unsigned);
int read(int, char *, unsigned);
#else  IRIS_4D
long lseek();
char *calloc();
void exit();
void perror();
int write();
int read();
#endif IRIS_4D
#endif lint

/* constants */

#ifndef PNL_EDITOR_PARSING
#ifndef PNL_EXTERN
#define PNL_EXTERN  extern
#endif
#ifndef PNL_INIT
#define PNL_INIT(x) /* nothing */
#endif

#if 0
#ifndef FILE
#include <stdio.h>
#endif
#include <string.h>
#include <sys/types.h>
#endif

#ifndef HZ
/* IGL: not needed/doesn't compile on Win32
#include <sys/param.h>
*/
#endif

#ifndef MAXSIG
#include <signal.h>
/* IGL: MAXSIG is not defined in signal.h */
#   ifndef MAXSIG
#       define MAXSIG 256
#   endif
#endif

#if 0			/* turned on in experimental version */
#ifdef IRIS_GT
#define PNL_ZBUFFER	/* turn on zbuffering in panels */
#endif
#endif

#ifdef PNL_ZBUFFER
#define PNL_DIM_Z_INC	PNL_DIM_5
#define PNL_ZTRANSLATE	translate(0.0, 0.0, PNL_DIM_Z_INC)
#else  PNL_ZBUFFER
#define PNL_ZTRANSLATE
#endif


#ifdef TRUE
#undef TRUE
#endif TRUE
#define TRUE	1
#ifndef NULL
#define NULL	0
#endif
#ifndef forever
#define forever for (;;)
#endif
#ifndef PI
#define PI	3.14159265358979323846	    /* from math.h */
#endif
#define	PNL_RAD_TO_DEG	(0.31830988618379067154*180.0)
#define PNL_TABLE_SIZE	4096		/* max number of panels + actuators */

#define PNL_EOF	-1

#ifndef MAXSGIDEVICE
#define MAXSGIDEVICE	20000
#endif  MAXSGIDEVICE
#define PNL_DEVICE_OFFSET   (MAXSGIDEVICE+1)
#define PNL_TOKEN_REDRAW    (PNL_DEVICE_OFFSET+0)
#define PNL_TOKEN_SIGNAL    (PNL_DEVICE_OFFSET+1)

#define PNL_PIXELS_PER_UNIT	50.0 /* used to size the panel */
#define PNL_CHAR_THRESHOLD	35.0 /* ppu below this, draw chars as rects */
#define PNL_PPU_MIN_DELTA	0.5  /* smallest change to cause recalc */

#define PNL_CHAR_PIXEL_HEIGHT	10
#define PNL_CHAR_PIXEL_WIDTH	10

#ifdef IRIS_NEWS
#  define PNL_SCREEN_BORDER	12
#  define PNL_TITLE_BAR_HEIGHT	19
#else
#  define PNL_SCREEN_BORDER	6
#  define PNL_TITLE_BAR_HEIGHT	18
#endif

/* panel dimensions */

#define PNL_MARGIN		0.2	/* absolute edge of panel left blank */
#define PNL_DIM_1		0.2	/* absolute dist tween actuators */
#define PNL_DIM_2		0.1	/* absolute dist to a label */
#define PNL_DIM_3		0.05	/* a tiny little distance */
#define PNL_DIM_4		0.025	/* half of THAT! */
#define PNL_DIM_5		0.0125	/* almost nothin', used for zbuffer */
#define PNL_BEVEL_WIDTH		PNL_DIM_3

/* actuator dimensions */

#define PNL_SLIDER_HEIGHT	(6.0-PNL_DIM_1)	/* w/o label */
#define PNL_SLIDER_WIDTH	(1.0-PNL_DIM_1)
#define PNL_SLIDER_BAR_HEIGHT	(0.05*PNL_SLIDER_HEIGHT)
#define PNL_DIFFERENTIAL_FACTOR	0.1
#define PNL_FINE_CONTROL_FACTOR 0.05
#define PNL_BUTTON_EDGE		(0.5-0.5*PNL_DIM_1)
#define PNL_WIDE_BUTTON_WIDTH   (2.0-PNL_DIM_1)
#define PNL_WIDE_BUTTON_HEIGHT  PNL_BUTTON_EDGE
#define PNL_TYPEIN_LENGTH	40  /* default length in characters */
#define PNL_TYPEIN_MAX_STRING	256
#define PNL_TYPEOUT_BUFSIZ	4096
#define PNL_TYPEOUT_COLUMNS	PNL_TYPEIN_LENGTH
#define PNL_TYPEOUT_LINES	4
#define PNL_TYPEOUT_MAX_COLUMNS 256
#define PNL_SCROLLBAR_WIDTH	(2.0*PNL_DIM_1)
#define PNL_TYPEOUT_ARROW_HEIGHT    (PNL_SCROLLBAR_WIDTH/2.0)
#define PNL_PUCK_EDGE		(4.0-PNL_DIM_1)
#define PNL_PUCK_SIZE		(1.0-PNL_DIM_1)
#define PNL_FLOATING_PUCK_EDGE	(1.0-PNL_DIM_1)
#define PNL_FLOATING_PUCK_SENS	10.0	/* units per full range output */
#define PNL_METER_HEIGHT        (2.0-PNL_DIM_1)
#define PNL_METER_WIDTH         (3.0-PNL_DIM_1)
#define PNL_METER_LINEWIDTH     4 /* Pixels for meter pointer and bar line */
#define PNL_STRIP_HEIGHT        (2.0-PNL_DIM_1)
#define PNL_STRIP_WIDTH         (4.0-PNL_DIM_1)
#define PNL_STRIP_LINEWIDTH	2
#define PNL_STRIP_CHART_NPTS    200
#define PNL_SLIDEROID_HEIGHT	(1.5-PNL_DIM_1)
#define PNL_SLIDEROID_WIDTH	(2.0-PNL_DIM_1)
#define PNL_DIAL_EDGE		(1.0-PNL_DIM_1)
#define PNL_DIAL_WINDS		0.88	/* revs per full range output */
#define PNL_MULTISLIDER_DIVISIONS 5
#define PNL_MENU_WIDTH		PNL_WIDE_BUTTON_WIDTH
#define PNL_MENU_TITLE_HEIGHT	PNL_WIDE_BUTTON_HEIGHT
#define PNL_ICON_WIDTH		(2.0-PNL_DIM_1)
#define PNL_ICON_HEIGHT		(0.5-PNL_DIM_2)
#define PNL_SCROLL_WIDTH	(4.0-PNL_DIM_1)
#define PNL_SCROLL_HEIGHT	(6.0-PNL_DIM_1)

/* Actuator types */

#define PNL_MAXACT		0x7ffff	    /* user types start here+1 */
#define PNL_USER_OFFSET		0x80000	    /* first user actuator */

#define PNL_SLIDER		0
#define PNL_VSLIDER		PNL_SLIDER
#define PNL_HSLIDER		1
#define PNL_FILLED_SLIDER	2
#define PNL_FILLED_VSLIDER	PNL_FILLED_SLIDER
#define PNL_FILLED_HSLIDER 	3
#define PNL_DVSLIDER		4
#define PNL_DHSLIDER 		5
#define PNL_BUTTON 			310
#define PNL_TOGGLE_BUTTON 		311
#define PNL_RADIO_BUTTON 		312
#define PNL_WIDE_BUTTON 		313
#define PNL_SHADOW_BUTTON		314
#define PNL_LEFT_ARROW_BUTTON		315
#define PNL_RIGHT_ARROW_BUTTON		316
#define PNL_UP_ARROW_BUTTON		317
#define PNL_DOWN_ARROW_BUTTON		318
#define PNL_LEFT_DOUBLE_ARROW_BUTTON	319
#define PNL_RIGHT_DOUBLE_ARROW_BUTTON	320
#define PNL_UP_DOUBLE_ARROW_BUTTON	321
#define PNL_DOWN_DOUBLE_ARROW_BUTTON	322
#define PNL_TYPEIN 		20
#define PNL_OLDTYPEIN 		29
#define PNL_LABEL 		21
#define PNL_TYPEOUT 		30
#define PNL_METER 		40
#define PNL_ANALOG_METER 	PNL_METER
#define PNL_ANALOG_BAR 		41
#define PNL_STRIP_CHART 	42
#define PNL_SCALE_CHART 	43
#define PNL_PUCK 		50
#define PNL_FLOATING_PUCK 	51
#define PNL_RUBBER_PUCK 	52
#define PNL_SLIDEROID		60
#define PNL_PALETTE		70
#define PNL_DIAL		80
#define PNL_MULTISLIDER		90
#define PNL_VMULTISLIDER	PNL_MULTISLIDER
#define PNL_HMULTISLIDER	91
#define PNL_MULTISLIDER_BAR		96
#define PNL_MULTISLIDER_OPEN_BAR	97
#define PNL_VMULTISLIDER_BAR		PNL_MULTISLIDER_BAR
#define PNL_VMULTISLIDER_OPEN_BAR	PNL_MULTISLIDER_OPEN_BAR
#define PNL_HMULTISLIDER_BAR		98
#define PNL_HMULTISLIDER_OPEN_BAR	99
#define PNL_MENU		100
#define PNL_MENU_ITEM		110
#define PNL_ICON		120
#define PNL_ICON_MENU		130
#define PNL_SUB_MENU		132
#define PNL_FRAME		140
#define PNL_VIEWFRAME		142
#define PNL_GRAPHFRAME		144
#define PNL_CYCLE		150
#define PNL_SCROLL		160
#define PNL_MOUSE		1000
#define PNL_SIGNAL		1010

/* slider modes */

#define PNL_SM_NORMAL		0x0
#define PNL_SM_DIFFERENTIAL	0x1
#define PNL_SM_FINE_CONTROL	0x2
#define PNL_SM_NOSNAP		0x4

/* multislider modes */

#define PNL_MSM_FREE		0x00	/* these three mutually exclusive */
#define PNL_MSM_ORDERED		0x01
#define PNL_MSM_CONSTRAINED	0x02
#define PNL_MSM_ADD		0x04	/* these two mutually exclusive */
#define PNL_MSM_DELETE		0x08

/* dial modes */

#define PNL_DM_NORMAL		0x00
#define PNL_DM_WRAP		0x01
#define PNL_DM_NOSNAP		0x02

/* icon modes */

#define PNL_IM_STOWED		0x01
#define PNL_IM_OPEN		0x02

/* typein modes */

#define PNL_TIM_NORMAL		0x00
#define PNL_TIM_TERM_ENTER	0x01

/* typein return codes */

#define PNL_TIR_EOF		0
#define PNL_TIR_NORM		1
#define PNL_TIR_QUIT		2
#define PNL_TIR_ERASE   	3
#define PNL_TIR_RESET		4
#define PNL_TIR_TOOLONG 	5

/* typeout modes */

#define PNL_TOM_NORMAL		0x00
#define PNL_TOM_NOCURSOR	0x01
#define PNL_TOM_NOREGION	0x02

/* frame modes */

#define PNL_FM_FREE		0x00	/* these three mutually exclusive */
#define PNL_FM_FIXED		0x01
#define PNL_FM_FIXED_SIZE	0x02

/* viewframe viewing object tags */

#define PNL_VFT_TRANSLATE1	0
#define PNL_VFT_ROTATE_X1	1
#define PNL_VFT_ROTATE_Z	2
#define PNL_VFT_ROTATE_X2	3
#define PNL_VFT_TRANSLATE2	4
#define PNL_VFT_SCALE		5

/* cycle modes */

#define PNL_CM_NORMAL		0x00
#define PNL_CM_UNDER_CONSTRUCTION	0x01

/* drawing styles */

#define PNL_OPEN		0
#define PNL_FILLED		1

/* label placement (anti-clockwise from right) */

#define PNL_LABEL_RIGHT		0
#define PNL_LABEL_RIGHT_TOP	1
#define PNL_LABEL_UPPER_RIGHT	2
#define PNL_LABEL_TOP_RIGHT	3
#define PNL_LABEL_TOP		4
#define PNL_LABEL_TOP_LEFT	5
#define PNL_LABEL_UPPER_LEFT	6
#define PNL_LABEL_LEFT_TOP	7
#define PNL_LABEL_LEFT		8
#define PNL_LABEL_LEFT_BOTTOM	9
#define PNL_LABEL_LOWER_LEFT	10
#define PNL_LABEL_BOTTOM_LEFT	11
#define PNL_LABEL_BOTTOM	12
#define PNL_LABEL_BOTTOM_RIGHT	13
#define PNL_LABEL_LOWER_RIGHT	14
#define PNL_LABEL_RIGHT_BOTTOM	15
#define PNL_LABEL_CENTER	16
#define	PNL_LABEL_NORMAL	17     /* no offset, actually quite abnormal */

#define PNL_MAX_LABEL_TYPE	17

/* colors */

#define PNL_RGB_WHITE_COLOR		255, 255, 255	/* RGB triples */
#define PNL_RGB_BEVEL_LIGHT_COLOR	209, 236, 255
#define PNL_RGB_NORMAL_COLOR		125, 165, 223
#define PNL_RGB_OTHER_COLOR		 62, 116, 207
#define PNL_RGB_BACKGROUND_COLOR	 88, 134, 213
#define PNL_RGB_HIGHLIGHT_COLOR		  0,  65, 191
#define PNL_RGB_BEVEL_DARK_COLOR	 19,  42,  80
#define PNL_RGB_LABEL_COLOR		  0,   0,  60
#define PNL_RGB_BLACK_COLOR		  0,   0,   0

#define PNL_12BIT_WHITE_COLOR		30		/* map indices */
#define PNL_12BIT_BEVEL_LIGHT_COLOR	229
#define PNL_12BIT_NORMAL_COLOR		178
#define PNL_12BIT_BACKGROUND_COLOR	173
#define PNL_12BIT_OTHER_COLOR		147
#define PNL_12BIT_HIGHLIGHT_COLOR	96
#define PNL_12BIT_BEVEL_DARK_COLOR	66
#define PNL_12BIT_LABEL_COLOR		36
#define PNL_12BIT_BLACK_COLOR		31

#define PNL_8BIT_WHITE_COLOR		30
#define PNL_8BIT_BEVEL_LIGHT_COLOR	29
#define PNL_8BIT_NORMAL_COLOR		23
#define PNL_8BIT_BACKGROUND_COLOR	20
#define PNL_8BIT_OTHER_COLOR		18
#define PNL_8BIT_HIGHLIGHT_COLOR	13
#define PNL_8BIT_BEVEL_DARK_COLOR	11
#define PNL_8BIT_LABEL_COLOR		9
#define PNL_8BIT_BLACK_COLOR		8

#define PNL_4BIT_WHITE_COLOR		WHITE
#define PNL_4BIT_BEVEL_LIGHT_COLOR	15
#define PNL_4BIT_NORMAL_COLOR		14
#define PNL_4BIT_BACKGROUND_COLOR	13
#define PNL_4BIT_OTHER_COLOR		12
#define PNL_4BIT_HIGHLIGHT_COLOR	11
#define PNL_4BIT_BEVEL_DARK_COLOR	10
#define PNL_4BIT_LABEL_COLOR		9
#define PNL_4BIT_BLACK_COLOR		BLACK

PNL_EXTERN Colorindex pnl_white_color	    PNL_INIT(0);
PNL_EXTERN Colorindex pnl_bevel_light_color PNL_INIT(0);
PNL_EXTERN Colorindex pnl_normal_color	    PNL_INIT(0);
PNL_EXTERN Colorindex pnl_background_color  PNL_INIT(0);
PNL_EXTERN Colorindex pnl_other_color	    PNL_INIT(0);
PNL_EXTERN Colorindex pnl_highlight_color   PNL_INIT(0);
PNL_EXTERN Colorindex pnl_bevel_dark_color  PNL_INIT(0);
PNL_EXTERN Colorindex pnl_label_color	    PNL_INIT(0);
PNL_EXTERN Colorindex pnl_black_color	    PNL_INIT(0);

/* mouse action sources */

#define PNL_SRC_QUEUE	0
#define PNL_SRC_SCRIPT	1

/* script message types */

#define PNL_MT_STATE	0xabc0
#define PNL_MT_MOUSE	0xabc1
#define PNL_MT_DELAY	0xabc2
#define PNL_MT_ENDBLOCK	0xabc3

/* function modes, ie, the context an actuator's function is called in */

#define PNL_FCNM_NONE	0
#define PNL_FCNM_DOWN	1
#define PNL_FCNM_ACTIVE	2
#define PNL_FCNM_UP	3

/* dopanel return modes, global control over dopanel return values */

#define PNL_DRM_RETURN_NULL	0
#define PNL_DRM_RETURN_PNL_CA	1

/* math relations */

#define PNL_HITRECT(x,y,x1,y1,x2,y2)    \
    ((x)>(x1) && (x)<(x2) && (y)>(y1) && (y)<(y2))
#define PNL_HITACT(a,wx,wy)						\
  (a->beveled?								\
    PNL_HITRECT((wx),(wy),						\
		(a)->x-PNL_BEVEL_WIDTH,					\
		(a)->y-PNL_BEVEL_WIDTH,					\
		(a)->x+(a)->w+PNL_BEVEL_WIDTH,				\
		(a)->y+(a)->h+PNL_BEVEL_WIDTH):				\
    PNL_HITRECT((wx),(wy),(a)->x,(a)->y,(a)->x+(a)->w,(a)->y+(a)->h))

#ifndef ABS
#define ABS(a)		((a)>0.0?(a):-(a))
#endif
#ifndef MIN
#define	MIN(a, b)	((a)<(b)?(a):(b))
#endif
#ifndef MAX
#define	MAX(a, b)	((a)>(b)?(a):(b))
#endif
#define	RANGE(a, b1, b2)			\
						\
        ((b1)<(b2)?				\
	     ((a)<(b1)?				\
		  (b1):				\
		  ((a)>(b2)?			\
		       (b2):(a))):		\
	     ((a)<(b2)?				\
		  (b2):				\
		  ((a)>(b1)?			\
		       (b1):(a))))

#ifndef INTERP
#define INTERP(x1, x2, a) ((a)*(x2)+(1.0-(a))*(x1))
#endif

#define PNL_VAL_TO_WORLD(val, min, max, dist)     \
  (((val)-(min))/((max)-(min))*(dist))

#define PNL_WORLD_TO_VAL(x, min, max, dist)       \
  ((x)/(dist)*((max)-(min))+(min))

/* structure references */

#define	PNL_ACCESS(type, ptr, member)    (((type *)(ptr->data))->member)
#define PNL_MKUSERACT(struct_type, type)			\
    ((struct struct_type *)				\
    _mkuseract (sizeof (struct struct_type), type))

#endif PNL_EDITOR_PARSING

/* structure declarations */

typedef struct panel {
    short id;			/* unique id  */
    struct actuator *a;		/* current actuator */
    struct actuator *al;		/* actuator list */
    struct alist *autolist;		/* list of auto actuators */
    struct actuator *lastgroup;		/* last actuator added to a group */
    Boolean active, selectable;
    long x, y, w, h;	/* screen location of the window and its size */
    Coord minx;	   /* bounding box enclosing all actuators and labels */
    Coord maxx;
    Coord miny;
    Coord maxy;
    Coord cw,ch;   /* char width and height */
    short gid;	   /* mex window number of this panels window */
    short usergid; /* mex window number of one of the user's windows */
    Object vobj;   /* viewing transformations */
    float ppu;	   /* pixels per unit */
    char *label;
#ifdef IRIS_4D
    void (*delfunc)(struct panel *);
    void (*fixfunc)(struct panel *);
#else  IRIS_4D
    void (*delfunc)();
    void (*fixfunc)();
#endif IRIS_4D
    void (*drawfunc)();
    void (*downfunc)();
    void (*activefunc)();
    void (*upfunc)();
    Boolean visible;		/* crank up a window for this guy? */
    int somedirty;		/* is there a dirty act on this panel */
    int dirtycnt;
    struct panel *next;
} Panel;

typedef struct actuator {
    short id;			/* unique id */
    struct panel *p;		/* pointer to enclosing panel */
    struct actuator *pa;	/* parent actuator */
    struct actuator *ca;	/* current subactuator (if any) */
    struct actuator *al;	/* list of sub-actuators */
    int na;			/* number of sub-actuators */
    int type;			/* type id, init func sets this */
    Boolean active;
    Coord x, y, w, h;
    Coord lx, ly, lw, lh;	/* offset and size of label */
    Coord ld;			/* descender size */
    float val, extval, initval, maxval, minval;
    float scalefactor;
    char *label;
    Device key;			/* keyboard equivalent */
    int labeltype;  /* location of the label relative to the actuator */
    void (*initfunc)();		/* the function that created me */
    void (*addfunc)();
#ifdef IRIS_4D
    void (*addsubfunc)(struct actuator *, struct actuator *);	/* to add a sub act to this act */
    void (*fixfunc)(struct actuator *);
    Boolean (*pickfunc)(/*struct actuator *,struct panel *,float,float*/);
    void (*delfunc)(struct actuator *);
    void (*newvalfunc)(/*struct actuator *,struct panel *,float,float*/);
    void (*dumpfunc)(struct actuator *, int);
    void (*loadfunc)(struct actuator *, int);
#else  IRIS_4D
    void (*addsubfunc)();	/* to add a sub act to this act */
    void (*fixfunc)();
    Boolean (*pickfunc)();
    void (*delfunc)();
    void (*newvalfunc)();
    void (*dumpfunc)();
    void (*loadfunc)();
#endif IRIS_4D
    void (*drawfunc)();
    void (*downfunc)();
    void (*activefunc)();
    void (*upfunc)();
    int dirtycnt;
    char *u;	    /* pointer to arbitrary user data */
    char *data;	    /* pointer to data peculiar to a particular actuator */
    int datasize;   /* size of data struct plus everyting it points to */
    Boolean automatic;   /* true ==> newvalfunc called every dopanel */
    Boolean selectable;	/* false ==> unpickable, newvalfunc never called */
    Boolean visible; /* does this actuator have a visible manifestation? */
    Boolean beveled; /* is this actuator got a beveled edge? */
    struct actuator *group;
    struct actuator *next;
} Actuator;

#ifndef PNL_EDITOR_PARSING

typedef struct alist {		/* generic list cons cell */
    Actuator *a;
    struct alist *next;
} Alist;

typedef struct charstruct {
  char c;
  struct charstruct *next;
} Charstruct;

typedef struct {
  float x, y;
} Point;

/* actuator specific data */

typedef struct {
  int firstpt, lastpt;
  Boolean Bind_Low, Bind_High;
  float *y;
  Actuator *lowlabel, *highlabel;
} Stripchart;

typedef struct {
  int mode;
  float finefactor;
  float differentialfactor;
  float valsave;
  Coord wsave;
  Coord bh;		/* slider bar height */
} Slider;

typedef struct {
  int mode;
  int n;		/* number of sliderbars */
  float finefactor;
  Coord wsave;
  Actuator *sa;		/* last selected sub actuator */
  Coord bh;		/* slider bar height */
  Coord clrx, clry, clrw, clrh;	/* expanded label clearing area */
  void (*acttype)();	/* the init function for the slider bar act */
} Multislider;

typedef struct {
  int mode;
  char *str;
  int len;
} Typein;

typedef struct {
  int mode;
  char *buf;		/* text to be displayed */
  char *delimstr;	/* auto 'word' selction delimiters */
  int start;		/* first char to display (appears in upper-left) */
  int dot;		/* insertion point */
  int mark;		/* other end of selection region */
  int col,lin;		/* width and height in character positions */
  int len;		/* number of chars in buffer */
  int size;		/* buffer size */
  Coord ch, cw, cd;     /* character dimensions */
} Typeout;

typedef Point Puck;

typedef struct {
  Coord x;
  Coord y;
} Mouse;

typedef struct {
  int mode;
  Boolean finemode, resetmode;
  float *resettarget, resetval;
  float valsave;
  Coord wsave;
} Slideroid;

typedef Slider Palette;

typedef struct {
  int mode;
  float finefactor;
  float valsave;
  Coord wsave;
  float winds;
} Dial;

typedef struct {
  Coord th;	/* title height */
} Menu;

typedef struct {
  int mode;
  Coord xstowed, ystowed, wstowed, hstowed;
  Coord xopen, yopen, wopen, hopen;
  char *labelsave;
} Icon;

typedef struct {	/* has extra junk for View- and Graphframe */
  int mode;
  Object vobj;
  Coord tx1, ty1, tz1;		/* translate arguments */
  float rotx1, rotz, rotx2;	/* rotation args */
  Coord tx2, ty2, tz2;		/* 2nd translation */
  float sx, sy, sz;		/* final scaling */
  Coord offx, offy;	/* offset for drawing, allows scrolling */
  Coord minx;	   /* bounding box enclosing all actuators and labels */
  Coord maxx;
  Coord miny;
  Coord maxy;
  Coord x, y;	/* frame coords avail to user in graphframe */
  void (*userdrawfunc)();
} Frame;	/* eventually change name to Panel? */

typedef Frame Viewframe;	/* not exactly the same but for convenience */
typedef Frame Graphframe;

typedef struct {
  int mode;
  Actuator *shiftleftbutton;
  Actuator *shiftrightbutton;
  Actuator *frame;
  Alist *memberlist, *currentmember;
} Cycle;

typedef struct {
  Actuator *vslider, *hslider;
  Actuator *frame, *subframe;
} Scroll;

typedef struct {
  int signal;
  Boolean activate;
} Signal;


/* globals */

PNL_EXTERN int pnl_id		PNL_INIT(0);
			/* an incrementing index into the table */

PNL_EXTERN char *pnl_table[PNL_TABLE_SIZE];
			/* table of pointers to all panels and actuators */

PNL_EXTERN Panel *pnl_pl 	PNL_INIT(NULL);
			/* list of all control panels */

PNL_EXTERN Alist *pnl_kl	PNL_INIT(NULL);
			/* a list of actuators with key equivalents */

PNL_EXTERN Panel *pnl_cp	PNL_INIT(NULL);
			/* panel being moused (current panel) */

PNL_EXTERN Actuator *pnl_ca	PNL_INIT(NULL);
			/* actuator being moused (current actuator) */

PNL_EXTERN Panel *pnl_cp_save	PNL_INIT(NULL);
			/* last cp from queue */

PNL_EXTERN Actuator *pnl_ca_save	PNL_INIT(NULL);
			/* last ca from queue */

PNL_EXTERN Boolean pnl_ca_active_save	PNL_INIT(FALSE);
			/* state of active field in pnl_ca_save */

PNL_EXTERN Boolean pnl_cp_active_save	PNL_INIT(FALSE);
			/* state of active field in pnl_cp_save */

/* these h ave not been documented */
PNL_EXTERN Panel *pnl_intr_cp_save 	PNL_INIT(NULL);
PNL_EXTERN Actuator *pnl_intr_ca_save	PNL_INIT(NULL);
PNL_EXTERN Boolean pnl_intr_ca_active_save	PNL_INIT(FALSE);
PNL_EXTERN Boolean pnl_intr_cp_active_save	PNL_INIT(FALSE);
PNL_EXTERN Boolean pnl_intr_pending	PNL_INIT(FALSE);
			/* true when a signal act has been returned */

PNL_EXTERN Actuator *pnl_mouse_act	PNL_INIT(NULL);
			/* the mouse actuator, if any */

PNL_EXTERN Screencoord pnl_mx, pnl_my;
PNL_EXTERN Coord pnl_x, pnl_y;	/* screen coords if outside a panel */
			/* where the mouse is */

PNL_EXTERN long int pnl_frame_number	PNL_INIT(0);
			/* frames since last delay message */

PNL_EXTERN int pnl_delay	PNL_INIT(0);
			/* frames 'til next message allowed from the queue */

PNL_EXTERN Boolean pnl_delayvirgin	PNL_INIT(TRUE);
			/* flag prevents writing initial delay token */

PNL_EXTERN Boolean pnl_readscript	PNL_INIT(FALSE);
			/* true when reading a script */

PNL_EXTERN Boolean pnl_writescript	PNL_INIT(FALSE);
			/* true when writing a script */

PNL_EXTERN int pnl_scriptinfd		PNL_INIT(0);

PNL_EXTERN int pnl_scriptoutfd		PNL_INIT(0);

/* IGL: writing to read-only memory segment is unwanted nowadays */
#if 0
PNL_EXTERN char *pnl_scriptinfile	PNL_INIT("panel.script");

PNL_EXTERN char *pnl_scriptoutfile	PNL_INIT("panel.script");
#else
PNL_EXTERN char pnl_scriptinfile[1024];

PNL_EXTERN char pnl_scriptoutfile[1024];
#endif

PNL_EXTERN Boolean pnl_virgin		PNL_INIT(TRUE);
			/* haven't done a dopanel yet */

PNL_EXTERN Boolean pnl_saveuserredraw	PNL_INIT(FALSE);
			/* if the user is using them, requeue them */

PNL_EXTERN Screencoord pnl_ox, pnl_oy;
			/* last window origin */

PNL_EXTERN Boolean pnl_justdown;
			/* true when button first goes down */

PNL_EXTERN Boolean pnl_justup;
			/* true when button first goes up */

PNL_EXTERN Boolean pnl_mousedown;
			/* true when button is (was) down */
			/* (according to the queue) */

PNL_EXTERN Boolean pnl_shiftkey		PNL_INIT(FALSE);
			/* true when the shift key is down */

PNL_EXTERN Boolean pnl_controlkey	PNL_INIT(FALSE);
			/* true when the control key is down */

PNL_EXTERN int pnl_winsave;
			/* gid of (user's) window when dopanel() is called */

PNL_EXTERN int pnl_action_source	PNL_INIT(PNL_SRC_QUEUE);
			/* where last mouse action came from */

PNL_EXTERN float pnl_char_threshold	PNL_INIT(PNL_CHAR_THRESHOLD);
			/* see PNL_CHAR_THRESHOLD above */

PNL_EXTERN Boolean pnl_dont_draw	PNL_INIT(FALSE);
			/* don't update panels (to avoid swapbuffers) */

PNL_EXTERN Boolean pnl_beveled		PNL_INIT(TRUE);
			/* global control for disabling drawing bevels */

PNL_EXTERN int pnl_funcmode		PNL_INIT(PNL_FCNM_NONE);
			/* role of called up-, active-, or downfuncs */
			/* also used in signal.c to control longjmp() */

PNL_EXTERN Boolean pnl_ignore_delay	PNL_INIT(FALSE);
			/* ignore delay packets when reading script */

PNL_EXTERN Boolean pnl_panel_bell	PNL_INIT(TRUE);
			/* ring bell for hits on unselectable panels */
			/* and in typeins in ignore mouse mode */

PNL_EXTERN int pnl_dopanel_return_mode	PNL_INIT(PNL_DRM_RETURN_PNL_CA);
			/* to ground out dopanel() when in build mode */

PNL_EXTERN Coord pnl_aox		PNL_INIT(0);
PNL_EXTERN Coord pnl_aoy		PNL_INIT(0);
			/* current actuator origin relative to window */

PNL_EXTERN float pnl_sf			PNL_INIT(1);
			/* current combined scalefactor */

PNL_EXTERN long pnl_naptime		PNL_INIT(-1);
			/* backoff time for inactive panel applications */
			/* use -1 for no backoff, HZ/10 is also reasonable */

PNL_EXTERN Boolean pnl_block		PNL_INIT(FALSE);
			/* set this to true to cause the library to do */
			/* blocking qreads in dopanel().  This keeps apps */
			/* from using any cycles when they are not busy. */

PNL_EXTERN Actuator *pnl_sl[MAXSIG];	/* assumed to init to NULL */
			/* array of signal actuators, one for each signal */

PNL_EXTERN Actuator *pnl_activetypein	PNL_INIT(NULL);
			/* the currently active typein, if any */

PNL_EXTERN Charstruct *pnl_charlisthead	PNL_INIT(NULL);
PNL_EXTERN Charstruct *pnl_charlisttail PNL_INIT(NULL);
			/* the head and tail of the typein char queue */

#define PNL_FADE_PATTERN_INDEX		1
#define PNL_FADE_PATTERN_SIZE		16
#define PNL_FADE_PATTERN						\
/* wide diagonals */	      { 0xf0f0, 0x7878, 0x3c3c, 0x1e1e, 	\
				0x0f0f, 0x8787, 0xc3c3, 0xe1e1, 	\
				0xf0f0, 0x7878, 0x3c3c, 0x1e1e, 	\
				0x0f0f, 0x8787, 0xc3c3, 0xe1e1 }
/* #ifdef 0 replaced */
#ifdef PNL_FADE_PATTERN_fine_diagonals
/* fine diagonals */	      { 0x9999, 0xcccc, 0x6666, 0x3333, 	\
				0x9999, 0xcccc, 0x6666, 0x3333, 	\
				0x9999, 0xcccc, 0x6666, 0x3333, 	\
				0x9999, 0xcccc, 0x6666, 0x3333 }

			      { 0xf0f0, 0xf0f0, 0xf0f0, 0xf0f0, 	\
				0x0f0f, 0x0f0f, 0x0f0f, 0x0f0f, 	\
				0xf0f0, 0xf0f0, 0xf0f0, 0xf0f0, 	\
				0x0f0f, 0x0f0f, 0x0f0f, 0x0f0f }

			      { 0x5555, 0x5555, 0x5555, 0x5555,		\
				0x5555, 0x5555, 0x5555, 0x5555, 	\
				0x5555, 0x5555, 0x5555, 0x5555, 	\
				0x5555, 0x5555, 0x5555, 0x5555 }
#endif

PNL_EXTERN short pnl_fade_pattern_index	PNL_INIT(PNL_FADE_PATTERN_INDEX);
PNL_EXTERN short pnl_fade_pattern_size	PNL_INIT(PNL_FADE_PATTERN_SIZE);
PNL_EXTERN short pnl_fade_pattern[]	PNL_INIT(PNL_FADE_PATTERN);
			/* pattern used to cover unselectable actuators */

/* function declarations */

/* panel library utilities */

#ifdef IRIS_4D
void *alloc(int);
void *pnl_alloc(int);
#else  IRIS_4D
void *alloc();
void *pnl_alloc();
#endif IRIS_4D

/* user functions */

PNL_EXTERN Panel    *mkpanel();
PNL_EXTERN Actuator *dopanel();
PNL_EXTERN void	    dumpstate();
PNL_EXTERN void	    drawpanel();
PNL_EXTERN short    userredraw();
PNL_EXTERN void	    needredraw();
PNL_EXTERN Boolean  dumppanel();

PNL_EXTERN Panel    *pnl_mkpanel();
PNL_EXTERN Actuator *pnl_dopanel();
PNL_EXTERN void	    pnl_dumpstate();
PNL_EXTERN void	    pnl_drawpanel();
PNL_EXTERN short    pnl_userredraw();
PNL_EXTERN void	    pnl_needredraw();
PNL_EXTERN Boolean  pnl_dumppanel();

#ifdef IRIS_4D

PNL_EXTERN Actuator *mkact(/*void (*)()*/); /* parameter decl doesn't seem to work */
PNL_EXTERN Actuator *_mkuseract(/*int, void (*)()*/); /* parameter decl doesn't seem to work */
PNL_EXTERN void	newvalact(/*Actuator *,Panel *,Coord, Coord*/);
PNL_EXTERN void	addact(Actuator *,Panel *);
PNL_EXTERN void	addsubact(Actuator *,Actuator *);
PNL_EXTERN void	delact(Actuator *);
PNL_EXTERN void	endgroup(Panel *);
PNL_EXTERN void	addtogroup(Actuator *,Panel *);
PNL_EXTERN void	fixpanel(Panel *);
PNL_EXTERN void	fixact(Actuator *);
PNL_EXTERN void	labeloffsets(Actuator *);
PNL_EXTERN void	labeldimensions(Actuator *);
PNL_EXTERN char	*g_gets(Colorindex,Colorindex,Colorindex);
PNL_EXTERN char	*g_getstring(Colorindex,Colorindex,Colorindex,char *,int);
PNL_EXTERN char	*g_mode_getstring(Colorindex,Colorindex,Colorindex,
				  char *,int,int);
PNL_EXTERN Boolean pnl_beginreadscript(char *);
PNL_EXTERN Boolean pnl_beginwritescript(char *);
PNL_EXTERN Boolean pnl_beginappendscript(char *);
PNL_EXTERN void pnl_endreadscript();
PNL_EXTERN void pnl_endwritescript();
PNL_EXTERN float pnl_strwidth(Panel *, char *);
PNL_EXTERN void pnl_listadd(Alist *, Alist **);
PNL_EXTERN void pnl_listdelete(Alist *, Alist **);
PNL_EXTERN Boolean pnl_listin(Alist *, Alist *);

PNL_EXTERN Actuator *pnl_mkact(/*void (*)()*/); /* parameter decl doesn't seem to work */
PNL_EXTERN Actuator *pnl_mkuseract(/*int, void (*)()*/); /* parameter decl doesn't seem to work */
PNL_EXTERN void	pnl_newvalact(/*Actuator *,Panel *,Coord, Coord*/);
PNL_EXTERN void	pnl_addact(Actuator *,Panel *);
PNL_EXTERN void	pnl_addsubact(Actuator *,Actuator *);
PNL_EXTERN void	pnl_delact(Actuator *);
PNL_EXTERN void	pnl_endgroup(Panel *);
PNL_EXTERN void	pnl_addtogroup(Actuator *,Panel *);
PNL_EXTERN void	pnl_fixpanel(Panel *);
PNL_EXTERN void	pnl_fixact(Actuator *);
PNL_EXTERN void	pnl_labeloffsets(Actuator *);
PNL_EXTERN void	pnl_labeldimensions(Actuator *);
PNL_EXTERN Boolean pnl_beginreadscript(char *);
PNL_EXTERN Boolean pnl_beginwritescript(char *);
PNL_EXTERN Boolean pnl_beginappendscript(char *);
PNL_EXTERN void pnl_endreadscript();
PNL_EXTERN void pnl_endwritescript();
PNL_EXTERN float pnl_strwidth(Panel *, char *);
PNL_EXTERN void pnl_listadd(Alist *, Alist **);
PNL_EXTERN void pnl_listdelete(Alist *, Alist **);
PNL_EXTERN Boolean pnl_listin(Alist *, Alist *);
PNL_EXTERN int pnl_getchar();
PNL_EXTERN Boolean pnl_testchar();


#else  IRIS_4D

PNL_EXTERN Actuator *mkact();
PNL_EXTERN Actuator *_mkuseract();
PNL_EXTERN void	newvalact();
PNL_EXTERN void	addact();
PNL_EXTERN void	addsubact();
PNL_EXTERN void	delact();
PNL_EXTERN void	endgroup();
PNL_EXTERN void	addtogroup();
PNL_EXTERN void	fixpanel();
PNL_EXTERN void	fixact();
PNL_EXTERN void	labeloffsets();
PNL_EXTERN void	labeldimensions();
PNL_EXTERN char	*g_gets();
PNL_EXTERN char	*g_getstring();
PNL_EXTERN char	*g_mode_getstring();
PNL_EXTERN Boolean pnl_beginreadscript();
PNL_EXTERN Boolean pnl_beginwritescript();
PNL_EXTERN void pnl_endreadscript();
PNL_EXTERN void pnl_endwritescript();
PNL_EXTERN Boolean pnl_beginappendscript();
PNL_EXTERN float pnl_strwidth();
PNL_EXTERN void pnl_listadd();
PNL_EXTERN void pnl_listdelete();
PNL_EXTERN Boolean pnl_listin();

PNL_EXTERN Actuator *pnl_mkact();
PNL_EXTERN Actuator *pnl__mkuseract();
PNL_EXTERN void	pnl_newvalact();
PNL_EXTERN void	pnl_addact();
PNL_EXTERN void	pnl_addsubact();
PNL_EXTERN void	pnl_delact();
PNL_EXTERN void	pnl_endgroup();
PNL_EXTERN void	pnl_addtogroup();
PNL_EXTERN void	pnl_fixpanel();
PNL_EXTERN void	pnl_fixact();
PNL_EXTERN void	pnl_labeloffsets();
PNL_EXTERN void	pnl_labeldimensions();
PNL_EXTERN char	*g_gets();
PNL_EXTERN char	*g_getstring();
PNL_EXTERN Boolean pnl_beginreadscript();
PNL_EXTERN Boolean pnl_beginwritescript();
PNL_EXTERN void pnl_endreadscript();
PNL_EXTERN void pnl_endwritescript();
PNL_EXTERN Boolean pnl_beginappendscript();
PNL_EXTERN float pnl_strwidth();
PNL_EXTERN void pnl_listadd();
PNL_EXTERN void pnl_listdelete();
PNL_EXTERN Boolean pnl_listin();
PNL_EXTERN int pnl_getchar();
PNL_EXTERN Boolean pnl_testchar();

#endif IRIS_4D

/* initialization functions */

#ifdef IRIS_4D
extern void pnl_slider(Actuator *);
extern void pnl_vslider(Actuator *);
extern void pnl_hslider(Actuator *);
extern void pnl_dvslider(Actuator *);
extern void pnl_dhslider(Actuator *);
extern void pnl_filled_slider(Actuator *);
extern void pnl_filled_vslider(Actuator *);
extern void pnl_filled_hslider(Actuator *);
extern void pnl_button(Actuator *);
extern void pnl_wide_button(Actuator *);
extern void pnl_toggle_button(Actuator *);
extern void pnl_radio_button(Actuator *);
extern void pnl_left_arrow_button(Actuator *);
extern void pnl_right_arrow_button(Actuator *);
extern void pnl_up_arrow_button(Actuator *);
extern void pnl_down_arrow_button(Actuator *);
extern void pnl_left_double_arrow_button(Actuator *);
extern void pnl_right_double_arrow_button(Actuator *);
extern void pnl_up_double_arrow_button(Actuator *);
extern void pnl_down_double_arrow_button(Actuator *);
extern void pnl_meter(Actuator *);
extern void pnl_analog_meter(Actuator *);
extern void pnl_analog_bar(Actuator *);
extern void pnl_strip_chart(Actuator *);
extern void pnl_scale_chart(Actuator *);
extern void pnl_puck(Actuator *);
extern void pnl_floating_puck(Actuator *);
extern void pnl_rubber_puck(Actuator *);
extern void pnl_typein(Actuator *);
extern void pnl_oldtypein(Actuator *);
extern void pnl_typeout(Actuator *);
extern void pnl_label(Actuator *);
extern void pnl_mouse(Actuator *);
extern void pnl_slideroid(Actuator *);
extern void pnl_palette(Actuator *);
extern void pnl_vpalette(Actuator *);
extern void pnl_hpalette(Actuator *);
extern void pnl_dial(Actuator *);
extern void pnl_multislider(Actuator *);
extern void pnl_hmultislider(Actuator *);
extern void pnl_vmultislider(Actuator *);
extern void pnl_multislider_bar(Actuator *);
extern void pnl_multislider_open_bar(Actuator *);
extern void pnl_vmultislider_bar(Actuator *);
extern void pnl_vmultislider_open_bar(Actuator *);
extern void pnl_hmultislider_bar(Actuator *);
extern void pnl_hmultislider_open_bar(Actuator *);
extern void pnl_menu(Actuator *);
extern void pnl_icon_menu(Actuator *);
extern void pnl_sub_menu(Actuator *);
extern void pnl_menu_item(Actuator *);
extern void pnl_icon(Actuator *);
extern void pnl_frame(Actuator *);
extern void pnl_viewframe(Actuator *);
extern void pnl_graphframe(Actuator *);
extern void pnl_cycle(Actuator *);
extern void pnl_scroll(Actuator *);
extern void pnl_signal(Actuator *);
#else  IRIS_4D
extern void pnl_slider();
extern void pnl_vslider();
extern void pnl_hslider();
extern void pnl_dvslider();
extern void pnl_dhslider();
extern void pnl_filled_slider();
extern void pnl_filled_vslider();
extern void pnl_filled_hslider();
extern void pnl_button();
extern void pnl_wide_button();
extern void pnl_toggle_button();
extern void pnl_radio_button();
extern void pnl_left_arrow_button();
extern void pnl_right_arrow_button();
extern void pnl_up_arrow_button();
extern void pnl_down_arrow_button();
extern void pnl_left_double_arrow_button();
extern void pnl_right_double_arrow_button();
extern void pnl_up_double_arrow_button();
extern void pnl_down_double_arrow_button();
extern void pnl_meter();
extern void pnl_analog_meter();
extern void pnl_analog_bar();
extern void pnl_strip_chart();
extern void pnl_scale_chart();
extern void pnl_puck();
extern void pnl_floating_puck();
extern void pnl_rubber_puck();
extern void pnl_typein();
extern void pnl_oldtypein();
extern void pnl_typeout();
extern void pnl_label();
extern void pnl_mouse();
extern void pnl_slideroid();
extern void pnl_palette();
extern void pnl_vpalette();
extern void pnl_hpalette();
extern void pnl_dial();
extern void pnl_multislider();
extern void pnl_vmultislider();
extern void pnl_hmultislider();
extern void pnl_multislider_bar();
extern void pnl_multislider_open_bar();
extern void pnl_vmultislider_bar();
extern void pnl_vmultislider_open_bar();
extern void pnl_hmultislider_bar();
extern void pnl_hmultislider_open_bar();
extern void pnl_menu();
extern void pnl_icon_menu();
extern void pnl_sub_menu();
extern void pnl_menu_item();
extern void pnl_icon();
extern void pnl_frame();
extern void pnl_viewframe();
extern void pnl_graphframe();
extern void pnl_cycle();
extern void pnl_scroll();
extern void pnl_signal();
#endif IRIS_4D

#endif PNL_EDITOR_PARSING

