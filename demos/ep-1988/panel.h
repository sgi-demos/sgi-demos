/*
 *	this software is in the public domain, it may not be resold
 *	or relicensed.  Do not remove this notice.  Send modifications
 *	and requests for most recent version to:
 *
 *	Author:  David A. Tristram
 *		 NASA  Ames Research Center
 *		 MS 258-5
 *		 Moffett Field, CA  94035
 *		 415-694-4404
 *		 dat@orville.nas.nasa.gov
 */
#ifndef PNL_EDITOR_PARSING
#ifndef PNL_EXTERN
#define PNL_EXTERN  extern
#endif
#ifndef PNL_INIT
#define PNL_INIT(x) /* nothing */
#endif
#ifndef FILE
#include <stdio.h>
#endif
#ifndef NULL
#define NULL	0
#endif
#ifndef PI
#define PI	3.14159265358979323846	    /* from math.h */
#endif
#define	PNL_RAD_TO_DEG	(0.31830988618379067154*180.0)
#define PNL_TABLE_SIZE	4096		/* max number of panels + actuators */

#ifndef MAXSGIDEVICE
#define MAXSGIDEVICE	20000
#endif  MAXSGIDEVICE
#define PNL_DEVICE_OFFSET   (MAXSGIDEVICE+1)
#define PNL_TOKEN	    (PNL_DEVICE_OFFSET+0)

#define PNL_PIXELS_PER_UNIT	50.0 /* used to size the panel */
#define PNL_CHAR_THRESHOLD	35.0 /* ppu below this, draw chars as rects */

#define PNL_CHAR_PIXEL_HEIGHT	10
#define PNL_CHAR_PIXEL_WIDTH	10

#ifdef IRIS_NEWS
#  define PNL_SCREEN_BORDER	12
#  define PNL_TITLE_BAR_HEIGHT	19
#else
#  define PNL_SCREEN_BORDER	6
#  define PNL_TITLE_BAR_HEIGHT	18
#endif

/* dimensions */
#define PNL_MARGIN		0.2	/* absolute edge of panel left blank */
#define PNL_DIM_1		0.2	/* absolute dist tween actuators */
#define PNL_DIM_2		0.1	/* absolute dist to a label */
#define PNL_DIM_3		0.05	/* a tiny little distance */
#define PNL_DIM_4		0.025	/* half of THAT! */
#define PNL_SLIDER_HEIGHT	(6.0-PNL_DIM_1)	/* w/o label */
#define PNL_SLIDER_WIDTH	(1.0-PNL_DIM_1)
#define PNL_SLIDER_BAR_HEIGHT	(0.05*PNL_SLIDER_HEIGHT)
#define PNL_BUTTON_EDGE		(0.5-0.5*PNL_DIM_1)
#define PNL_WIDE_BUTTON_WIDTH   (2.0-PNL_DIM_1)
#define PNL_WIDE_BUTTON_HEIGHT  PNL_BUTTON_EDGE
#define PNL_TYPEIN_LENGTH	40  /* default length in characters */
#define PNL_TYPEIN_MAX_STRING	256
#define PNL_TYPEOUT_BUFSIZ	4096
#define PNL_TYPEOUT_COLUMNS	PNL_TYPEIN_LENGTH
#define PNL_TYPEOUT_LINES	4
#define PNL_TYPEOUT_MAX_COLUMNS 256
#define PNL_SCROLL_WIDTH	(2.0*PNL_DIM_1)
#define PNL_TYPEOUT_ARROW_HEIGHT    (PNL_SCROLL_WIDTH/2.0)
#define PNL_PUCK_EDGE		(4.0-PNL_DIM_1)
#define PNL_PUCK_SIZE		(1.0-PNL_DIM_1)
#define PNL_FLOATING_PUCK_EDGE	(1.0-PNL_DIM_1)
#define PNL_FLOATING_PUCK_SENS	10.0	/* units per full range output */
#define PNL_METER_HEIGHT        (1.8-PNL_DIM_1)
#define PNL_METER_WIDTH         (3.0-PNL_DIM_1)
#define PNL_METER_LINEWIDTH     4 /* Pixels for meter pointer and bar line */
#define PNL_STRIP_HEIGHT        (1.8-PNL_DIM_1)
#define PNL_STRIP_WIDTH         (6.0-PNL_DIM_1)
#define PNL_STRIP_LINEWIDTH	2
#define PNL_STRIP_CHART_NPTS            200
#define PNL_SLIDEROID_HEIGHT	(1.5-PNL_DIM_1)
#define PNL_SLIDEROID_WIDTH	(2.0-PNL_DIM_1)
#define PNL_DIAL_EDGE		(1.0-PNL_DIM_1)
#define PNL_DIAL_WINDS		0.88	/* revs per full range output */

/* Actuator types */
#define PNL_MAXACT		0x7ffff	    /* user types start here+1 */
#define PNL_SLIDER		0
#define PNL_VSLIDER		PNL_SLIDER
#define PNL_HSLIDER		1
#define PNL_FILLED_SLIDER	2
#define PNL_FILLED_VSLIDER	PNL_FILLED_SLIDER
#define PNL_FILLED_HSLIDER 	3
#define PNL_DVSLIDER		4
#define PNL_DHSLIDER 		5
#define PNL_BUTTON 		10
#define PNL_TOGGLE_BUTTON 	11
#define PNL_RADIO_BUTTON 	12
#define PNL_WIDE_BUTTON 	13
#define PNL_TYPEIN 		20
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
#define PNL_MOUSE		1000

/* drawing styles */
#define PNL_OPEN		0
#define PNL_FILLED		1

/* label styles */
#define PNL_LABEL_LEFT		0
#define PNL_LABEL_RIGHT		1
#define PNL_LABEL_BOTTOM	2
#define PNL_LABEL_TOP		3
#define	PNL_LABEL_NORMAL	4
#define PNL_LABEL_CENTER	5

/* colors */
#ifdef IRIS_4D
#define PNL_WHITE_COLOR		WHITE
#define PNL_NORMAL_COLOR	490
#define PNL_OTHER_COLOR		474	/* light enough? */
#define PNL_BACKGROUND_COLOR	27
#define PNL_HIGHLIGHT_COLOR	457
#define PNL_OUTLINE_COLOR	321
#else  IRIS_4D
#define PNL_WHITE_COLOR		WHITE
#define PNL_NORMAL_COLOR	30
#define PNL_OTHER_COLOR		27
#define PNL_BACKGROUND_COLOR	25
#define PNL_HIGHLIGHT_COLOR	21
#define PNL_OUTLINE_COLOR	BLACK
#endif IRIS_4D

PNL_EXTERN Colorindex pnl_background_color  PNL_INIT(PNL_BACKGROUND_COLOR);
PNL_EXTERN Colorindex pnl_white_color	    PNL_INIT(PNL_WHITE_COLOR);
PNL_EXTERN Colorindex pnl_normal_color	    PNL_INIT(PNL_NORMAL_COLOR);
PNL_EXTERN Colorindex pnl_other_color	    PNL_INIT(PNL_OTHER_COLOR);
PNL_EXTERN Colorindex pnl_highlight_color   PNL_INIT(PNL_HIGHLIGHT_COLOR);
PNL_EXTERN Colorindex pnl_outline_color	    PNL_INIT(PNL_OUTLINE_COLOR);

/* mouse action sources */

#define PNL_SRC_QUEUE	0
#define PNL_SRC_SCRIPT	1

/* script message types */

#define PNL_MT_STATE	0
#define PNL_MT_MOUSE	1
#define PNL_MT_DELAY	2
#define PNL_MT_ENDBLOCK	3

#define PNL_HITACT(a,wx,wy)    \
    ((wx)>(a)->x && (wx)<(a)->x+(a)->w && (wy)>(a)->y && (wy)<(a)->y+(a)->h)
#define	PNL_ACCESS(type, ptr, member)    (((type *)(ptr->data))->member)
#define PNL_MKUSERACT(struct_type, type)			\
    ((struct struct_type *)				\
    _mkuseract (sizeof (struct struct_type), type))

#define ABS(a)		((a)>0.0?(a):-(a))
#define	MIN(a, b)	((a)<(b)?(a):(b))
#define	MAX(a, b)	((a)>(b)?(a):(b))
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

#define PNL_VAL_TO_WORLD(val, min, max, dist)     \
  (((val)-(min))/((max)-(min))*(dist))

#define PNL_WORLD_TO_VAL(x, min, max, dist)       \
  ((x)/(dist)*((max)-(min))+(min))  

#endif PNL_EDITOR_PARSING

typedef struct panel {
    short id;			/* unique id  */
    struct actuator *a;		/* current actuator */
    struct actuator *al;		/* actuator list */
    struct alist *autolist;		/* list of auto actuators */
    struct actuator *lastgroup;		/* last actuator added to a group */
    Boolean active, enabled;
    long x, y, w, h;
    Coord minx;
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
    void (*fixfunc)(struct actuator *);
#else  IRIS_4D
    void (*fixfunc)();
#endif IRIS_4D
    void (*drawfunc)();
    void (*downfunc)();
    void (*activefunc)();
    void (*upfunc)();
    int dirtycnt;
    struct panel *next;
} Panel;

typedef struct actuator {
    short id;			/* unique id */
    struct panel *p;		/* pointer to enclosing panel */
    int type;			/* type id, init func should set this */
    Boolean active;
    Coord x, y, w, h;
    Coord lx, ly, lw, lh;	/* offset and size of label */
    Coord ld;			/* descender size */
    float val, initval, maxval, minval;
    char *label;
    Device key;			/* keyboard equivalent */
    int labeltype;  /* location of the label relative to the actuator */
    void (*addfunc)();
#ifdef IRIS_4D
    void (*fixfunc)(struct actuator *);
    Boolean (*pickfunc)(/*struct actuator *,struct panel *,float,float*/);
    void (*newvalfunc)(struct actuator *,struct panel *,short,short);
    void (*dumpfunc)(struct actuator *, int);
    void (*loadfunc)(struct actuator *, int);
#else  IRIS_4D
    void (*fixfunc)();
    Boolean (*pickfunc)();
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
    struct actuator *group;
    struct actuator *next;
} Actuator;

#ifndef PNL_EDITOR_PARSING

typedef struct alist {
    Actuator *a;
    struct alist *next;
} Alist;

/* actuator specific data */

typedef struct {
    float x, y;
} Point;

typedef struct {
  int firstpt, lastpt;
  Boolean Bind_Low, Bind_High;
  float *y;
} Stripchart;

typedef struct {
  int mode;
  float finefactor;
  float valsave;
  Coord wsave;
} Slider;

typedef struct {
  char * str;
  int len;
} Typein;

typedef struct {
  char *buf;
  int start;		/* first char to display (appears in upper-left) */
  int dot;		/* insertion point */
  int col,lin;		/* width and height in character positions */
  int len;		/* number of chars in buffer */
  int size;		/* buffer size */
  Coord ch, cw, cd;     /* character dimensions */
} Typeout;

typedef Point Puck;

typedef struct {
  Screencoord x;
  Screencoord y;
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

PNL_EXTERN Actuator *pnl_mouse_act	PNL_INIT(NULL);
			/* the mouse actuator, if any */

PNL_EXTERN Screencoord pnl_mx, pnl_my;
			/* where the mouse is */

PNL_EXTERN long int pnl_frame	PNL_INIT(0);
			/* frames since last delay message */

PNL_EXTERN int pnl_delay	PNL_INIT(0);
			/* frames 'til next message allowed from the queue */

PNL_EXTERN Boolean pnl_delayvirgin	PNL_INIT(TRUE);
			/* flag prevents writing initial delay token */

PNL_EXTERN Boolean pnl_readscript	PNL_INIT(FALSE);

PNL_EXTERN Boolean pnl_writescript	PNL_INIT(FALSE);

PNL_EXTERN int pnl_scriptinfd		PNL_INIT(0);

PNL_EXTERN int pnl_scriptoutfd		PNL_INIT(0);

PNL_EXTERN char *pnl_scriptinfile	PNL_INIT("panel.script");

PNL_EXTERN char *pnl_scriptoutfile	PNL_INIT("panel.script");

PNL_EXTERN Boolean pnl_virgin		PNL_INIT(TRUE);	
			/* haven't done a dopanel yet */

PNL_EXTERN Boolean pnl_saveuserredraw	PNL_INIT(FALSE);	
			/* if the user is using them, requeue them */

PNL_EXTERN Boolean pnl_scripting	PNL_INIT(FALSE);
			/* writing a script file */

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

/* panel library utilities */

#ifdef IRIS_4D
char *alloc(int);
#else  IRIS_4D
char *alloc();
#endif IRIS_4D

/* user functions */

PNL_EXTERN Panel    *mkpanel();
PNL_EXTERN Actuator *dopanel();
PNL_EXTERN void	    dumpstate();
PNL_EXTERN void	    drawpanel();
PNL_EXTERN short    userredraw();
PNL_EXTERN void	    needredraw();
PNL_EXTERN Boolean  dumppanel();

#ifdef IRIS_4D

PNL_EXTERN Actuator *mkact(/*void (*)()*/); /* parameter decl doesn't seem to work */
PNL_EXTERN Actuator *_mkuseract(/*int, void (*)()*/); /* parameter decl doesn't seem to work */
PNL_EXTERN void	addact(Actuator *,Panel *);
PNL_EXTERN void	endgroup(Panel *);
PNL_EXTERN char	*g_gets(Colorindex,Colorindex,Colorindex);
PNL_EXTERN char	*g_getstring(Colorindex,Colorindex,Colorindex,char *,int);
PNL_EXTERN Boolean pnl_beginreadscript(char *);
PNL_EXTERN Boolean pnl_beginwritescript(char *);
PNL_EXTERN void pnl_endreadscript();
PNL_EXTERN void pnl_endwritescript();

#else  IRIS_4D

PNL_EXTERN Actuator *mkact();
PNL_EXTERN Actuator *_mkuseract();
PNL_EXTERN void	addact();
PNL_EXTERN void	endgroup();
PNL_EXTERN char	*g_gets();
PNL_EXTERN char	*g_getstring();
PNL_EXTERN Boolean pnl_beginreadscript();
PNL_EXTERN Boolean pnl_beginwritescript();
PNL_EXTERN void pnl_endreadscript();
PNL_EXTERN void pnl_endwritescript();

#endif IRIS_4D

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
extern void pnl_meter(Actuator *);
extern void pnl_analog_meter(Actuator *);
extern void pnl_analog_bar(Actuator *);
extern void pnl_strip_chart(Actuator *);
extern void pnl_scale_chart(Actuator *);
extern void pnl_puck(Actuator *);
extern void pnl_floating_puck(Actuator *);
extern void pnl_rubber_puck(Actuator *);
extern void pnl_typein(Actuator *);
extern void pnl_typeout(Actuator *);
extern void pnl_label(Actuator *);
extern void pnl_mouse(Actuator *);
extern void pnl_slideroid(Actuator *);
extern void pnl_palette(Actuator *);
extern void pnl_dial(Actuator *);
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
extern void pnl_meter();
extern void pnl_analog_meter();
extern void pnl_analog_bar();
extern void pnl_strip_chart();
extern void pnl_scale_chart();
extern void pnl_puck();
extern void pnl_floating_puck();
extern void pnl_rubber_puck();
extern void pnl_typein();
extern void pnl_typeout();
extern void pnl_label();
extern void pnl_mouse();
extern void pnl_slideroid();
extern void pnl_palette();
extern void pnl_dial();
#endif IRIS_4D

#endif PNL_EDITOR_PARSING
