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
#include <math.h>
#include <gl.h>
#include <device.h>
#include <panel.h>

#define MAXCOLORS	4096	/* for simplicity just make the storage */
				/* the size of the whole map */
#define MARGIN		5

/* IGL: we don't want fullscreen ep yet, so it's 400x400
#define WINSIZE		(YMAXSCREEN-(2*MARGIN)-PNL_TITLE_BAR_HEIGHT)
*/
#define WINSIZE		400

#define NPNTS		128
#define BASECOLOR	640
#define HUECHANINDEX	BASECOLOR+NPNTS
#define FATLINEWIDTH	3
#define NORMALLINEWIDTH 1
#define SQRT3	1.7320508
#define HUE_RATE_FACTOR 0.05;	/* how fast through hue space */
#define HUECHANNELS	5	/* number of huecontrols in colors panel */

#define FAST_CLEAR

#ifdef IRIS_GT
#if 0
/* IGL: this neat trick doesn't work anymore, but can be done differently */
#   define COLOR(ROOT) c4f(ROOT/**/RGBA)
#endif
#  define COLOR(ROOT) c4f(ROOT##RGBA)
#ifdef FAST_CLEAR
#  define CLEAR() clear();
#else  FAST_CLEAR
#  define CLEAR() \
	pushmatrix();			\
  	translate(0.0,0.0,9.8);		\
	rectf(-1.0,-1.0,1.0,1.0);	\
	popmatrix()
#endif FAST_CLEAR
#else  IRIS_GT
#  define COLOR(ROOT) color((int)ROOT)
#  define CLEAR() clear();
#endif IRIS_GT

/* #define ABS(x)	((x)<0?-(x):(x))*/

long	/* position and size of regularscreen window */
  regx = MARGIN,
  regy = MARGIN,
  regw = WINSIZE,
  regh = WINSIZE;

int bkg=BLACK;	/* the background of the data window */
int n;	    /* what one are we drawing now? */
float t;    /* how far are we toward the next triangle? */
int nlimit; /* how many do we draw? */
int ncolors;/* how many colors do we get? */
int basecolor;/* lowest color that we use */
float bkgRGBA[4] = { 0.0, 0.0, 0.0, 1.0 }; /* opaque black */
float colRGBA[4];

int dont_draw_save;

Alist *modsliderlist;
Panel *panel;

Actuator *positionpuck, *speedslider, *zoomslider, *wheelslider, *twistslider,
	 *flipslider, *spinslider, *armslider, *wristslider, *smearbutton,
	 *zbufbutton, *smoothbutton, *outlinebutton, *sizeslider,
	 *stopbutton, *fillbutton, *nslider, *fatlinebutton, *fullbutton,
         *maprangeslider, *maprateslider, *fadebutton, *ribbonbutton,
         *backgroundbutton, *alphaslider, *alphaoutslider, *backrateslider;
Actuator *alphadial, *alphaoutdial, *alphabackdial,
         *hueratedial, *huebackratedial;
Actuator *lightbutton, *shinyslider, *ambientslider;
Actuator *adial[HUECHANNELS], *hslider[HUECHANNELS], *dwellslider[HUECHANNELS];
Actuator *activebutton[HUECHANNELS], *lslider[HUECHANNELS], *chanrateslider;
Actuator *huepalette, *lightpalette, *hueindex[HUECHANNELS];

Actuator *spectrumbutton, *contourbutton, *bandbutton;

#define WRAP	0
#define BOUNCE	1

#if 0
/* IGL: this neat trick doesn't work anymore, but can be done differently */
#define MSLIDERVAL(Mname) (((Modslider *)(Mname/**/slider->u))->valbar->extval)
#endif
#define MSLIDERVAL(Mname) (((Modslider *)(Mname##slider->u))->valbar->extval)
typedef struct {
  int mode;	/* WRAP or BOUNCE */
  float center, range, sense;
  Actuator *ulbar, *valbar, *llbar, *freqslider;
  Actuator *modebutton;
} Modslider;

struct resetbutton {
    Actuator button;
    Actuator *targetact;
    float    *targetvar;
    float    varinitval;
};

void
load_spectrum_map()
{
float h, s, v, r, g, b, x;
int i, ir, ig, ib;

  x = 0.0;
  for (i=0; i<ncolors; i++)
    {
/*      x = 2.0*(float)i / (float)ncolors;
      hls_to_rgb (1.0-ABS(1.0-x), 0.5, 1.0, &r, &g, &b); */
      x = (float)i / (float)ncolors;
      hls_to_rgb (x, 0.5, 1.0, &r, &g, &b);
      rgb_to_irgb (r, g, b, &ir, &ig, &ib);
      mapcolor ((Colorindex)(basecolor+i), ir, ig, ib);
    }
}

void
load_contour_map(a)
  Actuator *a;
{
float h, s, v, r, g, b, x, y;
int i, ir, ig, ib;

  x = 0.0;
  for (i=0; i<=ncolors; i++)
    {
      /* only want to go from red to violet, hence the "0.8" */
      x = (float)i / ((float)ncolors);
      /* quantize in 8 bands */
      y = fmod(x, (0.85/7.99));
      x = x - y;
      hls_to_rgb (x, 6.5*y+0.1, 1.0, &r, &g, &b);
      rgb_to_irgb (r, g, b, &ir, &ig, &ib);
      mapcolor ((Colorindex)(basecolor+i), ir, ig, ib);
    }
}


#define MAPBANDWIDTH 20
#define MAPLINEWIDTH 4

void
load_band_map(a)
  Actuator *a;
{
  int i;
  load_spectrum_map(a);
  for (i=MAPBANDWIDTH; i<(ncolors-MAPBANDWIDTH); i++)
    {
      if (i%MAPBANDWIDTH <= MAPLINEWIDTH)
	mapcolor(basecolor+i, 0, 0, 0);
    }

}

skew(x, y, z)
float x, y, z;
{
  static Matrix mat = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
  };

  mat[0][0] = 1.0+x;
  mat[0][1] = y;
  mat[1][2] = z;
  multmatrix(mat);
}

void
resetact(b)
struct resetbutton *b;
{
    if (b->targetact->val!=b->targetact->initval) {
	b->targetact->val=b->targetact->initval;
        pnl_fixact(b->targetact);
    } else if (b->targetvar) {
	*b->targetvar=b->varinitval;
    }
}

void
resetslider(b)
struct resetbutton *b;
{
  Modslider *au=(Modslider *)b->targetact->u;

  au->ulbar->extval=au->valbar->pa->maxval;
  au->llbar->extval=au->valbar->pa->minval;
  au->freqslider->val=0;
  pnl_fixact(au->freqslider);
  pnl_fixact(au->valbar->pa);

  if (au->valbar->extval!=au->valbar->pa->initval) {
    au->valbar->extval=b->targetact->initval;
    pnl_fixact(b->targetact);
  } else if (b->targetvar) {
    *b->targetvar=b->varinitval;
  }
}

void saverange(a)
Actuator *a;
{
  Modslider *au=(Modslider *)a->pa->u;

  au->range=au->ulbar->extval-au->llbar->extval;
  au->center=au->ulbar->extval-au->range/2.0;
}

void setcenter(a)
Actuator *a;
{
  Modslider *au=(Modslider *)a->pa->u;

  au->ulbar->extval=au->llbar->extval+au->range;
  au->ulbar->extval=RANGE(au->ulbar->extval, au->llbar->extval, a->pa->maxval);
  au->valbar->extval=RANGE(au->valbar->extval,
			   au->llbar->extval,
			   au->ulbar->extval);
  saverange(a);
  pnl_fixact(a->pa);
}

void setrange(a)
Actuator *a;
{
  Modslider *au=(Modslider *)a->pa->u;

  au->ulbar->extval=2*au->center-au->llbar->extval;
  au->ulbar->extval=RANGE(au->ulbar->extval, au->llbar->extval, a->pa->maxval);
  au->valbar->extval=RANGE(au->valbar->extval,
			   au->llbar->extval,
			   au->ulbar->extval);
  saverange(a);
  pnl_fixact(a->pa);
}

static short savR[MAXCOLORS], savG[MAXCOLORS], savB[MAXCOLORS];

savecolors()
{
int i;

  for (i=0;i<ncolors;i++)
    getmcolor(i+basecolor, &savR[i], &savG[i], &savB[i]);
}

restorecolors()
{
int i;

  for (i=0;i<ncolors;i++)
    mapcolor(i+basecolor, savR[i], savG[i], savB[i]);
}

void
cleanexit()
{
  restorecolors();
  exit(0);
}

void
setsmooth(a)
Actuator *a;
{
  if (smearbutton->val==1.0) {
    if (a->val==1.0) {
      frontbuffer(FALSE);
      backbuffer(TRUE);
    } else {
      frontbuffer(TRUE);
      backbuffer(TRUE);
    }
  }
}

void
setsmear(a)
Actuator *a;
{
  if (a->val==1.0) {
    if (smoothbutton->val!=1.0) {
      if (stopbutton->val!=1.0) {
	COLOR(bkg);
	CLEAR();
	drawit();
      }
      frontbuffer(TRUE);
      backbuffer(TRUE);
    }
  } else {
    frontbuffer(FALSE);
    backbuffer(TRUE);
  }
}

void
setzbuf(a)
Actuator *a;
{
    if (a->val!=1.0) {
        zbuffer(FALSE);
    } else {
        zbuffer(TRUE);
	zclear();
    }
}

void
fullscreen(a)
Actuator *a;
{
  if (stopbutton->val==1.0) {	/* a bit of a hack, but expressed nicely */
    a->val=0.0;
    pnl_fixact(a);
    return;
  }
  dont_draw_save=pnl_dont_draw;
  pnl_dont_draw=TRUE;

  getorigin(&regx, &regy);
  getsize(&regw, &regh);
  winconstraints();
  winposition(0, XMAXSCREEN, 0, YMAXSCREEN);
  reshapeviewport();
  perspective(300, (float)XMAXSCREEN/(float)YMAXSCREEN, 0.01, 10000.0);
#ifdef IRIS_GT
  loadident();
#endif IRIS_GT
  polarview(10.0, 0, 0, 0);
#ifdef IRIS_GT
  lsetdepth(0x0, 0x7fffff);
#else  IRIS_GT
  setdepth(0x0000,0x3fff);
#endif IRIS_GT
  winpop();
  COLOR(bkg);
  CLEAR();
  swapbuffers();
  CLEAR();
  swapbuffers();
}

void
regularscreen()
{
  fullbutton->val=0.0;
  pnl_fixact(fullbutton);

  pnl_dont_draw=dont_draw_save;

  winposition(regx, regx+regw, regy, regy+regh);
  reshapeviewport();
  perspective(300, 1.0, 0.01, 10000.0);
#ifdef IRIS_GT
  loadident();
#endif IRIS_GT
  polarview(10.0, 0, 0, 0);
#ifdef IRIS_GT
  lsetdepth(0x0, 0x7fffff);
#else  IRIS_GT
  setdepth(0x0000,0x3fff);
#endif IRIS_GT
  keepaspect(1, 1);
  winconstraints();
  COLOR(bkg);
  CLEAR();
  swapbuffers();
  panel->dirtycnt=2;
  pnl_drawpanel();
  CLEAR();
  swapbuffers();
}

void
togglefullscreen(a)
Actuator *a;
{
  static fullscreenmode=FALSE;

  if (!fullscreenmode) {
    fullscreen(a);
    fullscreenmode=TRUE;
  } else {
    regularscreen(a);
    fullscreenmode=FALSE;
  }
}

animateslider(a)
     Actuator *a;
{
  Modslider *au=(Modslider *)a->u;
  float dx=au->sense*
    au->freqslider->val*
      (au->ulbar->extval-au->llbar->extval)/(a->maxval-a->minval)*
	MSLIDERVAL(speed);
  
  if (pnl_ca==au->valbar) return;
  if (au->freqslider->val==0.0) return;
  
  au->valbar->extval+=dx;
  
  if (au->modebutton->val == BOUNCE) {
    if (au->valbar->extval<au->llbar->extval) {
      au->valbar->extval= -au->valbar->extval+2*au->llbar->extval;
      au->sense=1;
    } else if (au->valbar->extval>au->ulbar->extval) {
      au->valbar->extval= -au->valbar->extval+2*au->ulbar->extval;
      au->sense= -1;
    }
  } else {
    if (au->valbar->extval<au->llbar->extval) {
      au->valbar->extval =
	au->ulbar->extval - (au->llbar->extval - au->valbar->extval);
    } else if (au->valbar->extval>au->ulbar->extval) {
      au->valbar->extval =
	au->llbar->extval + (au->valbar->extval - au->ulbar->extval);
    }
  }
  au->valbar->extval=RANGE(au->valbar->extval,
			   au->llbar->extval,
			   au->ulbar->extval);
  a->val=au->valbar->extval;
  pnl_fixact(a);
}

animatesliders()
{
  Alist *e;

  for (e=modsliderlist;e;e=e->next) animateslider(e->a);
}

deflight()
{
#ifdef IRIS_GT
  static float material1[] = {
    AMBIENT, 	0.2, 0.2, 0.2,
    DIFFUSE, 	0.8, 0.8, 0.8,
    SPECULAR, 	1.0, 1.0, 1.0,
    SHININESS,	80.0,
    LMNULL };

  static float light1[] = {
    LCOLOR,	1.0, 1.0, 1.0,
    POSITION,	1.0, 0.0, 0.5, 0.0,
    LMNULL };

  static float light2[] = {
    LCOLOR,	1.0, 1.0, 1.0,
    POSITION,	-1.0, 0.0, -0.5, 0.0,
    LMNULL };

  static float light3[] = {
    LCOLOR,	1.0, 1.0, 1.0,
    POSITION,	1.0, 0.0, -0.5, 0.0,
    LMNULL };

  static float light4[] = {
    LCOLOR,	1.0, 1.0, 1.0,
    POSITION,	-1.0, 0.0, 0.5, 0.0,
    LMNULL };

  static float light5[] = {
    LCOLOR,	1.0, 1.0, 1.0,
    POSITION,	0.0, 1.0, 0.5, 0.0,
    LMNULL };

  static float light6[] = {
    LCOLOR,	1.0, 1.0, 1.0,
    POSITION,	0.0, -1.0, -0.5, 0.0,
    LMNULL };

  static float light7[] = {
    LCOLOR,	1.0, 1.0, 1.0,
    POSITION,	0.0, 1.0, -0.5, 0.0,
    LMNULL };

  static float model1[] = {
    AMBIENT, 1.0, 1.0, 1.0,
    LOCALVIEWER, 0.0,
    ATTENUATION, 1.0, 1.0,
    LMNULL };

  lmdef(DEFMATERIAL, 1, 15, material1);
  lmdef(DEFLIGHT, 1, 10, light1);
  lmdef(DEFLIGHT, 2, 10, light2);
  lmdef(DEFLIGHT, 3, 10, light3);
  lmdef(DEFLIGHT, 4, 10, light4);
  lmdef(DEFLIGHT, 5, 10, light5);
  lmdef(DEFLIGHT, 6, 10, light6);
  lmdef(DEFLIGHT, 7, 10, light7);
  lmdef(DEFLMODEL, 1, 10, model1);
#endif IRIS_GT
}

uselight()
{
#ifdef IRIS_GT
  lmbind(MATERIAL, 1);
  lmbind(LIGHT5, 5);
  lmbind(LIGHT6, 6);
  lmbind(LMODEL, 1);
#endif IRIS_GT
}

void
ep_lmcolor(float col[4], float ambient, float shiny)
{
#ifdef IRIS_GT
  static float material1[] = {
    AMBIENT, 	0.2, 0.2, 0.2,
    DIFFUSE, 	0.8, 0.8, 0.8,
    SPECULAR, 	1.0, 1.0, 1.0,
    SHININESS,	80.0,
    ALPHA,	1.0,
    LMNULL };

  material1[1]=col[0]*ambient;
  material1[2]=col[1]*ambient;
  material1[3]=col[2]*ambient;
  material1[13]=(float)floor((double)(shiny*128.0));
  material1[5]=col[0];
  material1[6]=col[1];
  material1[7]=col[2];
  material1[15]=col[3];

  lmdef(DEFMATERIAL, 1, 17, material1);
  lmbind(MATERIAL, 1);
#endif IRIS_GT
}

loadident()
{
  static float ident[][4] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
  };

  loadmatrix(ident);
}

float wheel, dwheel;
float *x, *y, *dzoom, *arm, *wrist, *dtwist,
  *flip, *spin, *hue, *light, *alpha, *alphaout;
Boolean *outline, *fatline, *fill;
float *size;
float gflip, dflip, gspin, dspin, gcol;
float *maprange, *maprate, *backrate;
float *shiny, *ambient;
float glight, ghue, bhue;
float gchant;			/* channel selction parameter */
int gchan;			/* current channel */

Coord square[][2] = {
    {-0.1, -0.1},
    { 0.1, -0.1},
    { 0.1,  0.1},
    {-0.1,  0.1}
};

Coord trinormal[3] = {0.0, 0.0, 1.0};

Coord triangle[][2] = {
    { 0.0,  0.0 },
    { 0.2,  0.0 },
    { 0.1, SQRT3/10.0 }
};

main()
{
  Actuator *a;
  Device dev;
  short val;
  int h, i, j, mexwin;
  int itmp;
  float tmp;
  Boolean newn;

  wheel=0.0;
  x=(float *)pnl_alloc(NPNTS*sizeof(float));
  y=(float *)pnl_alloc(NPNTS*sizeof(float));
  dzoom=(float *)pnl_alloc(NPNTS*sizeof(float));
  arm=(float *)pnl_alloc(NPNTS*sizeof(float));
  wrist=(float *)pnl_alloc(NPNTS*sizeof(float));
  dtwist=(float *)pnl_alloc(NPNTS*sizeof(float));
  flip=(float *)pnl_alloc(NPNTS*sizeof(float));
  spin=(float *)pnl_alloc(NPNTS*sizeof(float));
  outline=(Boolean *)pnl_alloc(NPNTS*sizeof(Boolean));
  fatline=(Boolean *)pnl_alloc(NPNTS*sizeof(Boolean));
  fill=(Boolean *)pnl_alloc(NPNTS*sizeof(Boolean));
  size=(float *)pnl_alloc(NPNTS*sizeof(float));
  maprange=(float *)pnl_alloc(NPNTS*sizeof(float));
  hue=(float *)pnl_alloc(NPNTS*sizeof(float));
  alpha=(float *)pnl_alloc(NPNTS*sizeof(float));
  light=(float *)pnl_alloc(NPNTS*sizeof(float));
  alphaout=(float *)pnl_alloc(NPNTS*sizeof(float));
  shiny=(float *)pnl_alloc(NPNTS*sizeof(float));
  ambient=(float *)pnl_alloc(NPNTS*sizeof(float));

#ifdef DEBUG
  foreground();
#endif DEBUG
  prefposition(regx, regx+regw, regy, regy+regh);
  winopen("ep");
  winconstraints();
  keepaspect(1, 1);
  winconstraints();	/* make the window reshapeable */
  winattach();
  mexwin=winget();

  doublebuffer();
#ifdef IRIS_GT
  mmode(MVIEWING);
#endif IRIS_GT

#ifdef IRIS_GT
  RGBmode();
  blendfunction(BF_SA, BF_MSA);
  deflight();
#endif IRIS_GT
  gconfig();

  pnl_needredraw();
  defpanel();

  switch (getplanes()) {
  case 4:
    ncolors=15;
    basecolor=1;
    maprangeslider->minval=0.0;
    maprangeslider->maxval=10.0;
    pnl_fixact(maprangeslider);

    pnl_white_color		= 4;
    pnl_bevel_light_color	= 13;
    pnl_normal_color		= 9;
    pnl_other_color		= 7;
    pnl_background_color	= 8;
    pnl_highlight_color		= 5;
    pnl_bevel_dark_color	= 2;
    pnl_label_color		= 12;
    pnl_black_color		= 0;

    break;
  case 8:
    ncolors=128;
    basecolor=128;
    break;
  case 12:
  default:
    ncolors=128;
    basecolor=BASECOLOR;
    break;
  }
  savecolors();
  load_spectrum_map();

#ifdef IRIS_4D
  shademodel(FLAT);
  concave(FALSE);
#endif IRIS_4D
#ifdef IRIS_GT
  glcompat(GLC_OLDPOLYGON, FALSE);
#endif IRIS_GT

  perspective(300, 1.0, 0.01, 1000000.0);
#ifdef IRIS_GT
  loadident();
#endif IRIS_GT
  polarview(10.0, 0, 0, 0);
  /*   lookat(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0); */
#ifdef IRIS_GT
  lsetdepth(0x0, 0x7fffff);
#else  IRIS_GT
  setdepth(0x0000,0x3fff);
#endif IRIS_GT

  COLOR(bkg);
  CLEAR();
  swapbuffers();
  CLEAR();

  n=0;
  t=0.0;
  gchan=0;
  gchant=0;
  gcol=BASECOLOR+ncolors/2;
  ghue=0.5;
  bhue=0.5;

  pnl_naptime= -1;

  for (;;) {
    /* IGL: we need this line to process Win32/X11 events */
    IGL_MSG_PROCESS

    a=pnl_dopanel();
    if (stopbutton->val==1.0) {
      if (smearbutton->val!=1.0) {
	COLOR(bkg);
	CLEAR();
      }
      drawit();
      swapbuffers();
      do {
        /* IGL: we need this line to process Win32/X11 events */
        IGL_MSG_PROCESS

	a=pnl_dopanel();
	if (!a) sginap(0);
	swapbuffers();
      } while (stopbutton->val==1.0);
    }

    if (fullbutton->val==1.0
        && getbutton(LEFTMOUSE)) regularscreen();

    t+=MSLIDERVAL(speed);
    newn=FALSE;
    if (t>=1.0) newn=TRUE;
    n+=floor(t);
    t=fmod(t,1.0);
    
#ifdef IRIS_GT
    gchant+=chanrateslider->val*MSLIDERVAL(speed);
    gchant=fmod(gchant,1.0);
#endif IRIS_GT

    x[n%NPNTS]=PNL_ACCESS(Puck,positionpuck,x);
    y[n%NPNTS]=PNL_ACCESS(Puck,positionpuck,y);
    dzoom[n%NPNTS]=MSLIDERVAL(zoom);
    arm[n%NPNTS]=MSLIDERVAL(arm);
    wrist[n%NPNTS]=MSLIDERVAL(wrist);
    dwheel=MSLIDERVAL(speed)*MSLIDERVAL(wheel);
    dtwist[n%NPNTS]=MSLIDERVAL(twist);
    nlimit=(int)MSLIDERVAL(n);
    outline[n%NPNTS]=outlinebutton->val==1.0;
    fatline[n%NPNTS]=fatlinebutton->val==1.0;
    fill[n%NPNTS]=fillbutton->val==1.0;
    size[n%NPNTS]=MSLIDERVAL(size);
#ifdef IRIS_GT
    alpha[n%NPNTS]=adial[gchan]->val;
    alphaout[n%NPNTS]=alphaoutdial->val;
    shiny[n%NPNTS]=MSLIDERVAL(shiny);
    ambient[n%NPNTS]=MSLIDERVAL(ambient);
/*    ghue+=MSLIDERVAL(speed)*hueratedial->val*HUE_RATE_FACTOR; */
/*    ghue=MSLIDERVAL(hue); */
    ghue=((Modslider *)hslider[gchan]->u)->valbar->extval;
    glight=((Modslider *)lslider[gchan]->u)->valbar->extval;
    bhue+=MSLIDERVAL(speed)*huebackratedial->val*HUE_RATE_FACTOR;
#else  IRIS_GT
    maprange[n%NPNTS]=MSLIDERVAL(maprange);
    gcol+=MSLIDERVAL(speed)*MSLIDERVAL(maprate);
#endif IRIS_GT

#ifdef IRIS_GT
    while(ghue<0) ghue+=1;
    while(ghue>=1) ghue-=1;
    while(bhue<0) bhue+=1;
    while(bhue>=1) bhue-=1;
#else  IRIS_GT
    while(gcol<basecolor) gcol+=ncolors;
    while(gcol>=basecolor+ncolors) gcol-=ncolors;
#endif IRIS_GT

#ifdef IRIS_GT
    hue[n%NPNTS]=ghue;
    light[n%NPNTS]=glight;

    { int i;
      float hue, light, tot=0.0;
      int ir, ig, ib;
      float r,g,b;
      Boolean holding;

      holding=FALSE;
      for (i=0;i<HUECHANNELS;i++)
	if (pnl_ca==activebutton[i]) {  /* hold on one channel */
	  holding=TRUE;
	  gchan=i;
	  break;
	}

      if (!holding) {
	for (i=0;i<HUECHANNELS;i++) {
	  gchan=0;
	  tot+=dwellslider[i]->val;
	  if (tot>gchant) {
	    gchan=i;
	    break;
	  }
	}
	
	if (activebutton[gchan]->val!=1.0) {
	  for (i=0;i<HUECHANNELS;i++) activebutton[i]->val=0.0;
	  activebutton[gchan]->val=1.0;
	  for (i=0;i<HUECHANNELS;i++) fixact(activebutton[i]);
	}
      }
      
      /* for the color indicator palettes */
      for (i=0;i<HUECHANNELS;i++) {
	hue=((Modslider *)hslider[i]->u)->valbar->extval;
	hue=fmod(hue, 1.0);
	light=((Modslider *)lslider[i]->u)->valbar->extval;
	hls_to_rgb(hue, light, 1.0, &r, &g, &b);
	rgb_to_irgb (r, g, b, &ir, &ig, &ib);
	mapcolor(HUECHANINDEX+i, ir, ig, ib);
      }
    }
#endif IRIS_GT

    if (backgroundbutton->val==1.0) {
      bkg=((int)gcol+ncolors/2);
      if (bkg>=basecolor+ncolors) bkg-=ncolors;
#ifdef IRIS_GT
      hls_to_rgb(bhue, 0.5, 1.0, &bkgRGBA[0], &bkgRGBA[1], &bkgRGBA[2]);
#endif IRIS_GT
    } else {
      bkg=BLACK;
      bkgRGBA[0]=bkgRGBA[1]=bkgRGBA[2]=0.0;
    }
#ifdef IRIS_GT
    bkgRGBA[3]=alphabackdial->val;
#endif IRIS_GT

    if (newn) {
        dflip=MSLIDERVAL(flip);
	dspin=MSLIDERVAL(spin);

        gflip=fmod(gflip+dflip,360.0);
	flip[n%NPNTS]=gflip;

	gspin=fmod(gspin+dspin,360.0);
	spin[n%NPNTS]=gspin;
    }

/*     winset(mexwin); */
    if (pnl_userredraw()) {
	reshapeviewport();
	if (fullbutton->val==1.0)
	  perspective(300, (float)XMAXSCREEN/(float)YMAXSCREEN, 0.01, 10000.0);
	else
	  perspective(300, 1.0, 0.01, 10000.0);
#ifdef IRIS_GT
	loadident();
#endif IRIS_GT
	polarview(10.0, 0, 0, 0);
#ifdef IRIS_GT
	lsetdepth(0x0, 0x7fffff);
#else  IRIS_GT
	setdepth(0x0000,0x3fff);
#endif IRIS_GT
    }

    wheel=fmod(wheel-dwheel,360.0);
/* fprintf(stderr, "wheel:%f  dwheel:%f\n", wheel, dwheel); */

    if (smearbutton->val!=1.0) {
      COLOR(bkg);
      CLEAR();
    } else {
      if (fadebutton->val==1.0) fadebackground(bkg, 1);
      if (smoothbutton->val==1.0) {
	drawit();
	swapbuffers();
	if (fadebutton->val==1.0) fadebackground(bkg, 0);
	pnl_drawpanel();
      }
    }

    animatesliders();
    drawit();
    swapbuffers();
  }
}

float
twixt(i,x,t)
int i;
float *x;
float t;
{
int j=i-1;

    if (j<0) j+=NPNTS;
    return x[i]*t+x[j]*(1.0-t);
}

float
foldtwixt(i,x,t, range)
int i;
float *x;
float t, range;
{
  float r;
  float d;
  int j=i-1;

    if (j<0) j+=NPNTS;
    d=x[i]-x[j];
    if	    (d> range/2.0) r=x[i]*t+(x[j]+range)*(1.0-t);
    else if (d<-range/2.0) r=(x[i]+range)*t+x[j]*(1.0-t);
    else	       r=x[i]*t+x[j]*(1.0-t);

    return r;
}

float outlinecolRGBA[4] = { 0, 0, 1, 1 };
float colRGBA[4] = { 1, 0, 0, 1 };

drawit()
{
  int i,j;
  int outlinecol;
  float tx,ty,tdzoom,tarm,twrist,tsize,thue,talpha,tlight,talphaout,tambient,tshiny;
  float tspin,tflip,tdtwist;
  float col;
  float temphue;

    if (ribbonbutton->val==1.0) {
      drawribbons(); return;
    }
    if (zbufbutton->val==1.0) zclear();
    col=gcol;

    if (lightbutton->val==1.0) uselight();

    pushmatrix();
#ifdef FLOAT_ROTATE
    rot(wheel, 'x');
#else
    rotate((int)(10.0*wheel), 'x');
#endif

    for (i=n;i>n-nlimit;i--) {
      j=i%NPNTS;
      if (j<0) j+=NPNTS;
      if (j>NPNTS-1) j-=NPNTS;

      tx=twixt(j,x,t);
      ty=twixt(j,y,t);
      tdzoom=twixt(j,dzoom,t);
      tarm=twixt(j,arm,t);
      twrist=twixt(j,wrist,t);
      tsize=twixt(j,size,t);
      tspin=foldtwixt(j,spin,t, 360.0);
      tflip=foldtwixt(j,flip,t, 360.0);
      tdtwist=twixt(j,dtwist,t);
      thue=foldtwixt(j,hue,t, 1.0);
      talpha=twixt(j,alpha,t, 1.0);
      tlight=foldtwixt(j,light,t, 1.0);
      talphaout=twixt(j,alphaout,t, 1.0);
      tambient=twixt(j,ambient,t);
      tshiny=twixt(j,shiny,t);

#ifdef IRIS_GT
      hls_to_rgb(thue, tlight, 1.0, &colRGBA[0], &colRGBA[1], &colRGBA[2]);
      colRGBA[3]=talpha;
      outlinecolRGBA[3]=talphaout;
      temphue=thue+0.5;
      if (temphue>1.0) temphue-=1.0;
      hls_to_rgb(temphue, 1.0-tlight, 1.0, &outlinecolRGBA[0],
		 		 &outlinecolRGBA[1],
		 		 &outlinecolRGBA[2]);
#else  IRIS_GT
      if (outline[j]) {
	outlinecol=((int)col+ncolors/2);
	if (outlinecol>=basecolor+ncolors) outlinecol-=ncolors;
      }
      col-=maprange[j];
      while(col<basecolor) col+=ncolors;
      while(col>=basecolor+ncolors) col-=ncolors;
#endif IRIS_GT
      if (lightbutton->val==0) COLOR(col);
      else		       ep_lmcolor(colRGBA, tambient, tshiny);

      if (fatline[j]) {
	linewidth(FATLINEWIDTH);
      } else {
	linewidth(NORMALLINEWIDTH);
      }

      pushmatrix();
      translate(tx, ty, 0.0);
#ifdef FLOAT_ROTATE
      rot(tspin, 'z');
#else  FLOAT_ROTATE
      rotate((int)(10.0*tspin), 'z');
#endif FLOAT_ROTATE
      translate(0.0,tarm,0.0);
#ifdef FLOAT_ROTATE
      rot(tflip, 'y');
#else  FLOAT_ROTATE
      rotate((int)(10.0*tflip), 'y');
#endif FLOAT_ROTATE
      translate(twrist,0.0,0.0);
      scale(tsize,tsize,1.0);
#ifdef IRIS_GT
      if (lightbutton->val==1) n3f(trinormal);
#endif IRIS_GT
      if (fill[j]) polf2(3, triangle);
      if (outline[j]) {
	if (lightbutton->val==0) COLOR(outlinecol);
	else		         ep_lmcolor(outlinecolRGBA, tambient, tshiny);

	if (lightbutton->val==0) COLOR(col);
	else		         ep_lmcolor(colRGBA, tambient, tshiny);
      }
      popmatrix();

      scale(1.0, -1.0, 1.0);

      pushmatrix();
      translate(tx, ty, 0.0);
#ifdef FLOAT_ROTATE
      rot(tspin, 'z');
#else  FLOAT_ROTATE
      rotate((int)(10.0*tspin), 'z');
#endif FLOAT_ROTATE
      translate(0.0,tarm,0.0);
#ifdef FLOAT_ROTATE
      rot(tflip, 'y');
#else  FLOAT_ROTATE
      rotate((int)(10.0*tflip), 'y');
#endif FLOAT_ROTATE
      translate(twrist,0.0,0.0);
      scale(tsize,tsize,1.0);
#ifdef IRIS_GT
      if (lightbutton->val==1) n3f(trinormal);
#endif IRIS_GT
      if (fill[j]) polf2(3, triangle);
      if (outline[j]) {
	if (lightbutton->val==0) COLOR(outlinecol);
	else		         ep_lmcolor(outlinecolRGBA, tambient, tshiny);
	poly2(3, triangle);
	if (lightbutton->val==0) COLOR(col);
	else		         ep_lmcolor(colRGBA, tambient, tshiny);
      }
      popmatrix();

#ifdef FLOAT_ROTATE
      rot(180.0, 'z');
#else  FLOAT_ROTATE
      rotate((int)(10.0*180.0), 'z');
#endif FLOAT_ROTATE

      pushmatrix();
      translate(tx, ty, 0.0);
#ifdef FLOAT_ROTATE
      rot(tspin, 'z');
#else  FLOAT_ROTATE
      rotate((int)(10.0*tspin), 'z');
#endif FLOAT_ROTATE
      translate(0.0,tarm,0.0);
#ifdef FLOAT_ROTATE
      rot(tflip, 'y');
#else  FLOAT_ROTATE
      rotate((int)(10.0*tflip), 'y');
#endif FLOAT_ROTATE
      translate(twrist,0.0,0.0);
      scale(tsize,tsize,1.0);
#ifdef IRIS_GT
      if (lightbutton->val==1) n3f(trinormal);
#endif IRIS_GT
      if (fill[j]) polf2(3, triangle);
      if (outline[j]) {
	if (lightbutton->val==0) COLOR(outlinecol);
	else		         ep_lmcolor(outlinecolRGBA, tambient, tshiny);
	poly2(3, triangle);
	if (lightbutton->val==0) COLOR(col);
	else		         ep_lmcolor(colRGBA, tambient, tshiny);
      }
      popmatrix();

      scale(1.0, -1.0, 1.0);

      pushmatrix();
      translate(tx, ty, 0.0);
#ifdef FLOAT_ROTATE
      rot(tspin, 'z');
#else  FLOAT_ROTATE
      rotate((int)(10.0*tspin), 'z');
#endif FLOAT_ROTATE
      translate(0.0,tarm,0.0);
#ifdef FLOAT_ROTATE
      rot(tflip, 'y');
#else  FLOAT_ROTATE
      rotate((int)(10.0*tflip), 'y');
#endif FLOAT_ROTATE
      translate(twrist,0.0,0.0);
      scale(tsize,tsize,1.0);
#ifdef IRIS_GT
      if (lightbutton->val==1) n3f(trinormal);
#endif IRIS_GT
      if (fill[j]) polf2(3, triangle);
      if (outline[j]) {
	if (lightbutton->val==0) COLOR(outlinecol);
	else		         ep_lmcolor(outlinecolRGBA, tambient, tshiny);
	poly2(3, triangle);
	if (lightbutton->val==0) COLOR(col);
	else		         ep_lmcolor(colRGBA, tambient, tshiny);
      }
      popmatrix();

#ifdef FLOAT_ROTATE
      rot(tdtwist, 'z');
#else  FLOAT_ROTATE
      rotate((int)(10.0*tdtwist), 'z');
#endif FLOAT_ROTATE
      translate(0.0, 0.0, tdzoom);

    }
    popmatrix();
}

drawribbons()
{
#ifdef IRIS_GT
  int ii,i,j;
  int outlinecol;
  float tx,ty,tdzoom,tarm,twrist,tsize,thue,talpha,tlight,talphaout,tambient,tshiny;
  float tspin,tflip,tdtwist;
  float col;
  float temphue;

  if (zbufbutton->val==1.0) zclear();

  pushmatrix();
#ifdef FLOAT_ROTATE
  rot(wheel, 'x');
#else
  rotate((int)(10.0*wheel), 'x');
#endif

  for (ii=0;ii<4;ii++) {
    col=gcol;
    pushmatrix();
    bgntmesh();
    for (i=n;i>n-nlimit;i--) {
      j=i%NPNTS;
      if (j<0) j+=NPNTS;
      if (j>NPNTS-1) j-=NPNTS;

      tx=twixt(j,x,t);
      ty=twixt(j,y,t);
      tdzoom=twixt(j,dzoom,t);
      tarm=twixt(j,arm,t);
      twrist=twixt(j,wrist,t);
      tsize=twixt(j,size,t);
      tspin=foldtwixt(j,spin,t, 360.0);
      tflip=foldtwixt(j,flip,t, 360.0);
      tdtwist=twixt(j,dtwist,t);
      thue=foldtwixt(j,hue,t, 1.0);
      talpha=twixt(j,alpha,t, 1.0);
      tlight=foldtwixt(j,light,t, 1.0);
      talphaout=twixt(j,alphaout,t, 1.0);

#ifdef IRIS_GT
      hls_to_rgb(thue, tlight, 1.0, &colRGBA[0], &colRGBA[1], &colRGBA[2]);
      colRGBA[3]=talpha;
      outlinecolRGBA[3]=talphaout;
      temphue=thue+0.5;
      if (temphue>1.0) temphue-=1.0;
      hls_to_rgb(temphue, 1.0-tlight, 1.0, &outlinecolRGBA[0],
		 		 &outlinecolRGBA[1],
		 		 &outlinecolRGBA[2]);
#else  IRIS_GT
      if (outline[j]) {
	outlinecol=((int)col+ncolors/2);
	if (outlinecol>=basecolor+ncolors) outlinecol-=ncolors;
      }
      col-=maprange[j];
      while(col<basecolor) col+=ncolors;
      while(col>=basecolor+ncolors) col-=ncolors;
#endif IRIS_GT
      if (lightbutton->val==0) COLOR(col);
      else		       ep_lmcolor(colRGBA, tambient, tshiny);

      if (fatline[j]) {
	linewidth(FATLINEWIDTH);
      } else {
	linewidth(NORMALLINEWIDTH);
      }

      pushmatrix();
      translate(tx, ty, 0.0);
#ifdef FLOAT_ROTATE
      rot(tspin, 'z');
#else  FLOAT_ROTATE
      rotate((int)(10.0*tspin), 'z');
#endif FLOAT_ROTATE
      translate(0.0,tarm,0.0);
#ifdef FLOAT_ROTATE
      rot(tflip, 'y');
#else  FLOAT_ROTATE
      rotate((int)(10.0*tflip), 'y');
#endif FLOAT_ROTATE
      translate(twrist,0.0,0.0);
      scale(tsize,tsize,1.0);
      v2f(&triangle[0][0]); v3f(&triangle[1][0]);
      popmatrix();

#ifdef FLOAT_ROTATE
      if (ii<2) rot(tdtwist, 'z');
      else      rot(-tdtwist, 'z');
#else  FLOAT_ROTATE
      if (ii<2) rotate((int)(10.0*tdtwist), 'z');
      else      rotate((int)(-10.0*tdtwist), 'z');
#endif FLOAT_ROTATE
      translate(0.0, 0.0, tdzoom);

    }
    popmatrix();

    if (ii%2)
      scale(1.0, -1.0, 1.0);
    else
      rotate(1800, 'z');

  }
  endtmesh();
  popmatrix();
#endif IRIS_GT
}

Actuator
*mkepslider(label, x, y, min, max, val, var, mode, panel)
  char *label;
  Coord x, y;
  float min, max, val, *var;
  int mode;
  Panel *panel;
{
  Alist *e;
  Actuator *a, *sa;
  Modslider *au;
  struct resetbutton *rb;

    a=mkact(pnl_multislider);
    PNL_ACCESS(Multislider, a, mode)=PNL_MSM_ORDERED;
    PNL_ACCESS(Multislider, a, n)=0;
    a->label=label;
    a->x=x;
    a->y=y;
    a->val=val;
    a->minval=min;
    a->maxval=max;
    au=(Modslider *)(a->u=(char *)pnl_alloc(sizeof(Modslider)));
    au->sense=1;
    addact(a, panel);

    au->ulbar=sa=pnl_mkact(pnl_multislider_open_bar);
    sa->extval= a->maxval;
    sa->downfunc=saverange;
    pnl_addsubact(sa, a);

    au->llbar=sa=pnl_mkact(pnl_multislider_open_bar);
    sa->extval= a->minval;
    sa->downfunc=saverange;
    sa->activefunc=setcenter;
    pnl_addsubact(sa, a);

/* this appears third so it will fall between the other two even if it */
/* is at the end of a slider (that is a property of multisliders) */

    au->valbar=sa=pnl_mkact(pnl_multislider_bar);
    sa->extval=val;
    pnl_addsubact(sa, a);

    au->freqslider=sa=pnl_mkact(pnl_hslider);
    sa->w=a->w;
    sa->h=2*PNL_ACCESS(Multislider, a, bh);
    sa->x=a->x;
    sa->y=a->y+a->h+PNL_DIM_2;
    sa->maxval=(a->maxval-a->minval)/2.0;
    PNL_ACCESS(Slider, sa, mode)|=PNL_SM_NOSNAP;
    sa->downfunc=saverange;
    sa->activefunc=setrange;
    addact(sa, panel);
    sa->pa=a;

    au->modebutton=sa=pnl_mkact(pnl_toggle_button);
    sa->w=a->w;
    sa->h=2*PNL_ACCESS(Multislider, a, bh);
    sa->x=a->x;
    sa->y=a->y+a->h+au->freqslider->h+2*PNL_DIM_2;
    sa->val=mode;
    sa->minval=BOUNCE;
    sa->maxval=WRAP;
    pnl_addact(sa, panel);

    rb=PNL_MKUSERACT(resetbutton, pnl_wide_button);
    rb->targetact=a;
    rb->targetvar=var;
    rb->varinitval=val;
    rb->button.label="R";
    rb->button.w=PNL_SLIDER_WIDTH;
    rb->button.h=PNL_BUTTON_EDGE;
    rb->button.x=x;
    rb->button.y=sa->y+sa->h+PNL_DIM_2;
    rb->button.downfunc=resetslider;
    pnl_addact((Actuator *)rb, panel);

    e=(Alist *)pnl_alloc(sizeof(Alist));
    e->a=a;
    e->next=modsliderlist;
    modsliderlist=e;

    return a;
}

#if 0
updatedwellsliders(i)
int i;
{
  int j,k;
  float tot;

  for (j=0;j<HUECHANNELS;j++) {
    tot=0.0;
    if (j==i) continue;
    for (k=0;k<HUECHANNELS;k++) {
      if (k==j) continue;
      tot+=dwellslider[k]->val;
    }
    dwellslider[j]->val=RANGE(1.0-tot, 0.0, 1.0);
  }
  for (j=0;j<HUECHANNELS;j++) pnl_fixact(dwellslider[j]);
}
#endif

updatedwellsliders(i)
int i;
{
  int j,k;
  float tot;
  static float oldval[3];

  for (j=0, tot=0;j<HUECHANNELS;j++) {
    if (j==i) continue;
    tot+=dwellslider[j]->val;
  }

  for (j=0;j<HUECHANNELS;j++) {
    if (j==i) continue;
    if (tot==0.0) 
      dwellslider[j]->val+=
	-(dwellslider[i]->val-oldval[i])*(1.0/(float)HUECHANNELS);
    else
      dwellslider[j]->val+=
	-(dwellslider[i]->val-oldval[i])*dwellslider[j]->val/tot;
    
    dwellslider[j]->val=RANGE(dwellslider[j]->val, 0, 1);
  }

  for (j=0;j<HUECHANNELS;j++) fixact(dwellslider[j]);

  for (j=0;j<HUECHANNELS;j++)
    oldval[j]=dwellslider[j]->val;  
}

updateactivebutton(i)
int i;
{
  int j;

  for (j=0;j<HUECHANNELS;j++) {
    if (j==i) continue;
    activebutton[j]->val=activebutton[j]->minval;
    fixact(activebutton[j]);
  }
}

void
togglechanmode(a)
Actuator *a;
{
  int i;

  if (a->u[0]=='h') {
    fixact(a);
    huepalette->visible=FALSE;
    lightpalette->visible=TRUE;
    fixact(huepalette);
    fixact(lightpalette);
    for (i=0;i<HUECHANNELS;i++) {
      hslider[i]->visible=FALSE;
      ((Modslider *)(hslider[i]->u))->freqslider->visible=FALSE;
      ((Modslider *)(hslider[i]->u))->modebutton->visible=FALSE;
      lslider[i]->visible=TRUE;
      ((Modslider *)(lslider[i]->u))->freqslider->visible=TRUE;
      ((Modslider *)(lslider[i]->u))->modebutton->visible=TRUE;
      fixact(hslider[i]);
      fixact(((Modslider *)(hslider[i]->u))->freqslider);
      fixact(((Modslider *)(hslider[i]->u))->modebutton);
      fixact(lslider[i]);
      fixact(((Modslider *)(lslider[i]->u))->freqslider);
      fixact(((Modslider *)(lslider[i]->u))->modebutton);
    }
  } else {
    fixact(a);
    lightpalette->visible=FALSE;
    huepalette->visible=TRUE;
    fixact(lightpalette);
    fixact(huepalette);
    for (i=0;i<HUECHANNELS;i++) {
      hslider[i]->visible=TRUE;
      ((Modslider *)(hslider[i]->u))->freqslider->visible=TRUE;
      ((Modslider *)(hslider[i]->u))->modebutton->visible=TRUE;
      lslider[i]->visible=FALSE;
      ((Modslider *)(lslider[i]->u))->freqslider->visible=FALSE;
      ((Modslider *)(lslider[i]->u))->modebutton->visible=FALSE;
      fixact(hslider[i]);
      fixact(((Modslider *)(hslider[i]->u))->freqslider);
      fixact(((Modslider *)(hslider[i]->u))->modebutton);
      fixact(lslider[i]);
      fixact(((Modslider *)(lslider[i]->u))->freqslider);
      fixact(((Modslider *)(lslider[i]->u))->modebutton);
    }
  }
}      


void
constraincolorpanel(p)
Panel *p;
{
  int i;

  for (i=0;i<HUECHANNELS;i++) {
    if (pnl_ca==dwellslider[i]) updatedwellsliders(i);
    if (pnl_ca==activebutton[i]) updateactivebutton(i);
  }
}


Coord
  *pack2f(x, y)
Coord x, y;
{
  static Coord v[2];

  *v=x;
  *(v+1)=y;
  return v;
}

void
drawdoublepalette(a, p)
     Actuator *a;
     Panel *p;
{
  if (!a->dirtycnt) return;

  pushmatrix();
  
  translate(a->x,a->y,0.0);
  
#ifdef IRIS_4D
  bgnpolygon();
  color((Colorindex)a->minval);
  v2f(pack2f(0.0, 0.0));
  v2f(pack2f(a->w, 0.0));
  color((Colorindex)a->maxval);
  v2f(pack2f(a->w, a->h/2.0));
  v2f(pack2f(0.0,  a->h/2.0));
  endpolygon();

  bgnpolygon();
  color((Colorindex)a->minval);
  v2f(pack2f(0.0, a->h/2.0));
  v2f(pack2f(a->w, a->h/2.0));
  color((Colorindex)a->maxval);
  v2f(pack2f(a->w, a->h));
  v2f(pack2f(0.0,  a->h));
  endpolygon();
#else IRIS_4D
  setshade((Colorindex)a->minval);
  pmv2(0.0, 0.0);
  pdr2(a->w, 0.0);
  setshade((Colorindex)a->maxval);
  pdr2(a->w, a->h/2.0);
  pdr2(0.0,  a->h/2.0);
  spclos();

  setshade((Colorindex)a->minval);
  pmv2(0.0, a->h/2.0);
  pdr2(a->w, a->h/2.0);
  setshade((Colorindex)a->maxval);
  pdr2(a->w, a->h);
  pdr2(0.0,  a->h);
  spclos();
#endif IRIS_4D
  
  popmatrix();
  if (a->beveled) pnl_drawbevel(a, p);
  if (a->label) pnl_drawlabel(a, p);
}


/* IGL: the following function was added to display/close the about box */
Panel *aboutPanel;
extern void
_drawwidebutton (Actuator *a, Panel *p);    /* this is a hack for about button */

void
about ()
{
    aboutPanel->visible = !aboutPanel->visible;
    pnl_fixpanel (aboutPanel);
}


defpanel()
{
  Alist *e;
  Actuator *a, *sa;
  Modslider *au;
  struct resetbutton *rb;
  Coord y, dy=0.5;
  Coord x, dx;
  int i;

    initscriptpanel();

    panel=pnl_mkpanel();
#ifdef IRIS_4D
    panel->ppu=40.0;
#else
    panel->ppu=38.0;
#endif
    panel->label="electro-paint";

    a=pnl_mkact(pnl_label);
    a->x=0.2;
    a->y=19.0;
    a->label="...by Dave Tristram";
    pnl_addact(a,panel);
    
    a=pnl_mkact(pnl_wide_button);
    a->x=0.0;
    a->y=0.0;
    a->label="exit";
    a->upfunc=cleanexit;
    pnl_addact(a,panel);

/* IGL: Electropaint is (TM) now, so we present an about button */
    /*
        NOTE: this is a hacked toggle button. its labeltype, width,
        height and drawfunc were overriden with those of a wide button.
        this way, it looks like a normal button, but has an on/off
        state, like a toggle button...
    */
    a = pnl_mkact (pnl_toggle_button);
    a->labeltype = PNL_LABEL_CENTER;
    a->w = PNL_WIDE_BUTTON_WIDTH;
    a->h = PNL_WIDE_BUTTON_HEIGHT;
    a->drawfunc = _drawwidebutton;
    a->x = 0.0;
    a->y = 0.5;
    a->label = "about";
    a->upfunc = about;
    pnl_addact (a, panel);


    y=3.0;

    outlinebutton=pnl_mkact(pnl_toggle_button);
    outlinebutton->label="outline (O)";
    outlinebutton->labeltype=PNL_LABEL_LEFT;
    outlinebutton->x=4.5;
    outlinebutton->y=(y-=dy);
    outlinebutton->key=OKEY;
    pnl_addact(outlinebutton,panel);

    fatlinebutton=pnl_mkact(pnl_toggle_button);
    fatlinebutton->label="fat lines (I)";
    fatlinebutton->labeltype=PNL_LABEL_LEFT;
    fatlinebutton->x=4.5;
    fatlinebutton->y=(y-=dy);
    fatlinebutton->key=IKEY;
    pnl_addact(fatlinebutton,panel);

    fillbutton=pnl_mkact(pnl_toggle_button);
    fillbutton->label="fill (U)";
    fillbutton->labeltype=PNL_LABEL_LEFT;
    fillbutton->x=4.5;
    fillbutton->y=(y-=dy);
    fillbutton->val=1.0;
    fillbutton->key=UKEY;
    pnl_addact(fillbutton,panel);

    ribbonbutton=pnl_mkact(pnl_toggle_button);
#ifdef IRIS_GT
    ribbonbutton->label="ribbons (R)";
    ribbonbutton->labeltype=PNL_LABEL_LEFT;
    ribbonbutton->x=4.5;
    ribbonbutton->y=(y-=dy);
    ribbonbutton->key=RKEY;
    pnl_addact(ribbonbutton,panel);
#endif IRIS_GT

    smoothbutton=pnl_mkact(pnl_toggle_button);
    smoothbutton->label="smooth (M)";
    smoothbutton->labeltype=PNL_LABEL_LEFT;
    smoothbutton->x=4.5;
    smoothbutton->y=(y-=dy);
    smoothbutton->downfunc=setsmooth;
    smoothbutton->key=MKEY;
    pnl_addact(smoothbutton,panel);

    smearbutton=pnl_mkact(pnl_toggle_button);
    smearbutton->label="smear (Q)";
    smearbutton->labeltype=PNL_LABEL_LEFT;
    smearbutton->x=4.5;
    smearbutton->y=(y-=dy);
    smearbutton->downfunc=setsmear;
    smearbutton->key=QKEY;
    pnl_addact(smearbutton,panel);

    fadebutton=pnl_mkact(pnl_toggle_button);
#ifndef IRIS_GT
    fadebutton->label="fade (W)";
    fadebutton->labeltype=PNL_LABEL_LEFT;
    fadebutton->x=4.5;
    fadebutton->y=(y-=dy);
    fadebutton->key=WKEY;
    pnl_addact(fadebutton,panel);
#endif IRIS_GT

    backgroundbutton=pnl_mkact(pnl_toggle_button);
    backgroundbutton->label="back (E)";
    backgroundbutton->labeltype=PNL_LABEL_LEFT;
    backgroundbutton->x=4.5;
    backgroundbutton->y=(y-=dy);
    backgroundbutton->key=EKEY;
    pnl_addact(backgroundbutton,panel);

    zbufbutton=pnl_mkact(pnl_toggle_button);
#ifdef IRIS_GT
    zbufbutton->label="z-buf (Z)";
    zbufbutton->labeltype=PNL_LABEL_LEFT;
    zbufbutton->x=4.5;
    zbufbutton->y=(y-=dy);
    zbufbutton->key=ZKEY;
    zbufbutton->downfunc=setzbuf;
    pnl_addact(zbufbutton,panel);
#endif IRIS_GT

  a=lightbutton=pnl_mkact(pnl_toggle_button);
#ifdef IRIS_GT
  a->label="light (L)";
  a->labeltype=PNL_LABEL_LEFT;
  a->x=4.5;
  a->y=(y-=dy);
  a->key=LKEY;
  pnl_addact(a, panel);

#endif IRIS_GT

    stopbutton=pnl_mkact(pnl_toggle_button);
    stopbutton->label="stop (S)";
    stopbutton->labeltype=PNL_LABEL_LEFT;
    stopbutton->x=4.5;
    stopbutton->y=(y-=dy);
    stopbutton->key= SKEY;
    pnl_addact(stopbutton,panel);

    fullbutton=pnl_mkact(pnl_toggle_button);
    fullbutton->label="full screen (F)";
    fullbutton->labeltype=PNL_LABEL_LEFT;
    fullbutton->x=4.5;
    fullbutton->y=(y-=dy);
    fullbutton->downfunc=togglefullscreen;
    fullbutton->key=FKEY;
    pnl_addact(fullbutton,panel);

    positionpuck=pnl_mkact(pnl_floating_puck);
    positionpuck->x=0.0;
    positionpuck->y=1.5;
    pnl_addact(positionpuck,panel);


    zoomslider=
      mkepslider("zoom", 0.0,	3.5,	-0.5,
		 0.5,	0.0, NULL, BOUNCE, panel);
    twistslider=
      mkepslider("twst",1.0,	3.5,	-100.0,
		 100.0,	0.0, NULL, BOUNCE, panel);
    speedslider=
      mkepslider("spd", 2.0,	3.5,	0.0,
/* IGL: 1.0 is too fast a speed, changed to 0.05 */
#if 0
		 1.0,	1.0, NULL, BOUNCE, panel);
#else
		 1.0,	0.05, NULL, BOUNCE, panel);
#endif

    nslider=
      mkepslider("n",	  3.0,	3.5,	1.0,
		 NPNTS-1.0 ,32.0, NULL, BOUNCE, panel);
#ifdef IRIS_GT
    ambientslider=
      mkepslider("amb",4.0,	3.5,	0.0,
		 1.0,	0.0, NULL, BOUNCE, panel);
    shinyslider=
      mkepslider("shn", 5.0,	3.5,	0.0,
		 1.0,	1.0, NULL, BOUNCE, panel);
#else  IRIS_GT
    maprateslider=
      mkepslider("rat", 4.0,	3.5,	-20.0,
		 20.0,	1.0, NULL, BOUNCE, panel);
    maprangeslider=
      mkepslider("rng",5.0,	3.5,	0.0,
		 100.0,	1.0, NULL, BOUNCE, panel);
#endif IRIS_GT

    wheelslider=
      mkepslider("whl",  0.0,	11.5,	-60.0,
		 60.0,	0.0, &wheel, BOUNCE, panel);
    spinslider=
      mkepslider("spn",   1.0,	11.5,	-20.0,
		 20.0,	0.0, &gspin, BOUNCE, panel);
    flipslider=
      mkepslider("flp",   2.0,	11.5,	-20.0,
		 20.0,	0.0, &gflip, BOUNCE, panel);
    armslider=
      mkepslider("arm",	   3.0,	11.5,	0.0,
		 3.0,	0.0, NULL, BOUNCE, panel);
    wristslider=
      mkepslider("wrst", 4.0,	11.5,	0.0,
		 3.0,	0.0, NULL, BOUNCE, panel);
    sizeslider=
      mkepslider("sz",	   5.0,	11.5,	0.1,
		 10.0,	1.0, NULL, BOUNCE, panel);

#ifdef IRIS_GT
  panel=pnl_mkpanel();
  panel->label="colors";
  panel->ppu=40.0;
  panel->activefunc=constraincolorpanel;

  x=1;
  dx=1;
  y=0;

#define MK_RESET_BUTTON	rb=PNL_MKUSERACT(resetbutton, pnl_wide_button);	rb->button.label="R"; rb->button.x=a->x; rb->button.y=a->y+a->h+PNL_DIM_1; rb->button.w=a->w; rb->targetact=a; rb->targetvar=NULL; rb->varinitval=a->val; rb->button.downfunc=resetact

  a=alphaoutdial=pnl_mkact(pnl_dial);
  a->label="outa";
  a->x=x;x+=dx;
  a->y=y;
  a->val=1;
  pnl_addact(a, panel);
  MK_RESET_BUTTON;
  pnl_addact((Actuator *)rb, panel);

  a=alphabackdial=pnl_mkact(pnl_dial);
  a->label="baka";
  a->x=x;x+=dx;
  a->y=y;
  a->val=1;
  pnl_addact(a, panel);
  MK_RESET_BUTTON;
  pnl_addact((Actuator *)rb, panel);

  a=huebackratedial=pnl_mkact(pnl_dial);
  a->label="outr";
  a->x=x;x+=dx;
  a->y=y;
  a->minval= -20;
  a->maxval=  20;
  a->val=0.2;
  pnl_addact(a, panel);
  MK_RESET_BUTTON;
  rb->varinitval=0;
  pnl_addact((Actuator *)rb, panel);

  x=0;

  for (i=0;i<HUECHANNELS;i++) {
    y=2;

    a=adial[i]=pnl_mkact(pnl_dial);
    a->x=x;
    a->y=y;y+=a->h+PNL_DIM_1;
    a->val=1;
    pnl_addact(a, panel);

    a=hslider[i]=mkepslider(NULL, x, y, 0.0, 2.0, 1.0, NULL, WRAP, panel);
    a=lslider[i]=mkepslider(NULL, x, y, 0.0, 1.0, 0.5, NULL, WRAP, panel);
    a->visible=FALSE;
    ((Modslider *)(lslider[i]->u))->freqslider->visible=FALSE;
    ((Modslider *)(lslider[i]->u))->modebutton->visible=FALSE;
      

    if (i==HUECHANNELS-1) {
      huepalette=a=pnl_mkact(pnl_frame);
      PNL_ACCESS(Frame, a, mode)|=PNL_FM_FIXED;	/* don't resize */
      a->w=0.5-PNL_DIM_1;
      a->h=hslider[0]->h;
      a->x=x+hslider[0]->w+PNL_DIM_1;
      a->y=y;
      a->minval=basecolor;
      a->maxval=basecolor+ncolors-1;
      a->drawfunc=drawdoublepalette;
      a->downfunc=togglechanmode;
      a->u="h";
      pnl_addact(a, panel);

      lightpalette=a=pnl_mkact(pnl_palette);
      a->w=0.5-PNL_DIM_1;
      a->h=hslider[0]->h;
      a->x=x+hslider[0]->w+PNL_DIM_1;
      a->y=y;
      a->minval=512;
      a->maxval=638;
      a->visible=FALSE;
      a->downfunc=togglechanmode;
      a->u="l";
      pnl_addact(a, panel);
    }
    y+=6+4*PNL_ACCESS(Multislider, hslider[0], bh)+PNL_DIM_2
      +PNL_WIDE_BUTTON_HEIGHT+PNL_DIM_1;		/* hack */

    a=hueindex[i]=pnl_mkact(pnl_palette);
    a->h=PNL_BUTTON_EDGE;
    a->w=PNL_SLIDER_WIDTH;
    a->x=x;
    a->y=y;y+=a->h+PNL_DIM_1;
    a->minval=a->maxval=HUECHANINDEX+i;
    pnl_addact(a, panel);
        
    a=dwellslider[i]=pnl_mkact(pnl_filled_slider);
    a->h=3.0-PNL_DIM_1;
    a->x=x;
    a->y=y;y+=a->h+PNL_DIM_1;
    if (i==0) a->val=1;
    pnl_addact(a, panel);

    a=activebutton[i]=pnl_mkact(pnl_button);
    a->w=PNL_SLIDER_WIDTH;
    a->x=x;
    a->y=y;y+=a->h+PNL_DIM_1;
    if (i==0) a->val=1;
    pnl_addact(a, panel);
    
    x+=1;
  }

  ((Modslider *)(hslider[0]->u))->freqslider->val=0.01;

  a=chanrateslider=pnl_mkact(pnl_hslider);
  a->w=x-PNL_DIM_1;
  a->h=2*PNL_ACCESS(Multislider, hslider[0], bh);
  a->x=0;
  a->y=y;y+=a->h;
  pnl_addact(a, panel);

#endif IRIS_GT


/* IGL: Electropaint is (TM) now, so we present an about window */
    aboutPanel = pnl_mkpanel ();
    aboutPanel->label = "About Electropaint";
#ifdef IRIS_4D
    aboutPanel->ppu = 40.0;
#else
    aboutPanel->ppu = 38.0;
#endif
    aboutPanel->visible = FALSE;

    a = pnl_mkact (pnl_label);
    a->x = 0.0;
    a->y = 1.0;
    a->label = "Panel Library/Electropaint Copyright (c) 1986 David A. Tristram";
    pnl_addact (a, aboutPanel);

    a = pnl_mkact (pnl_label);
    a->x = 0.0;
    a->y = 0.6;
    a->label = "Electropaint (TM) is a Registered U.S. Trademark of Tristram Visual.";
    pnl_addact (a, aboutPanel);

    a = pnl_mkact (pnl_label);
    a->x = 0.0;
    a->y = 0.2;
    a->label = "Tristram Visual can be contacted at www.tristram.com.";
    pnl_addact (a, aboutPanel);
}

