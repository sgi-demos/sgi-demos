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
#include <math.h>
#include <gl.h>
#include <device.h>
#include <panel.h>

#define MAXCOLORS	4096	/* for simplicity just make the storage */
				/* the size of the whole map */
#define MARGIN		5
#define WINSIZE		(YMAXSCREEN-(2*MARGIN)-PNL_TITLE_BAR_HEIGHT)
#define NPNTS		128
#define BASECOLOR	512
#define FATLINEWIDTH	3
#define NORMALLINEWIDTH 1
#define SQRT3	1.7320508

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

Panel *panel;

Actuator *positionpuck, *speedslider, *zoomslider, *wheelslider, *twistslider,
	 *flipslider, *spinslider, *armslider, *wristslider, *smearbutton,
	 *zbufbutton, *smoothbutton, *outlinebutton, *sizeslider,
	 *stopbutton, *fillbutton, *nslider, *fatlinebutton, *fullbutton,
         *maprangeslider, *maprateslider, *fadebutton, *ribbonbutton;

Actuator *spectrumbutton, *contourbutton, *bandbutton;

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
        fixact(b->targetact);
    } else if (b->targetvar) {
	*b->targetvar=b->varinitval;
    }
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
	color(bkg);
	clear();
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
    fixact(a);
    return;
  }
  getorigin(&regx, &regy);
  getsize(&regw, &regh);
  winconstraints();
  winposition(0, XMAXSCREEN, 0, YMAXSCREEN);
  reshapeviewport();
  perspective(300, (float)XMAXSCREEN/(float)YMAXSCREEN, 0.01, 10000.0);
  polarview(10.0, 0, 0, 0);
#ifdef IRIS_GT
  lsetdepth(0x0, 0x7fffff);
#else  IRIS_GT
  setdepth(0x0000,0x3fff);
#endif IRIS_GT
  winpop();
  color(bkg);
  clear();
  swapbuffers();
  color(bkg);
  clear();
  swapbuffers();
}  

void
regularscreen()
{
  fullbutton->val=0.0;
  fixact(fullbutton);

  winposition(regx, regx+regw, regy, regy+regh);
  reshapeviewport();
  perspective(300, 1.0, 0.01, 10000.0);
  polarview(10.0, 0, 0, 0);
#ifdef IRIS_GT
  lsetdepth(0x0, 0x7fffff);
#else  IRIS_GT
  setdepth(0x0000,0x3fff);
#endif IRIS_GT
  keepaspect(1, 1);
  winconstraints();
  
  color(bkg);
  clear();
  swapbuffers();
  panel->dirtycnt=2;
  drawpanel();
  color(bkg);
  clear();
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

float wheel, dwheel;
float *x, *y, *dzoom, *arm, *wrist, *dtwist, *flip, *spin;
Boolean *outline, *fatline, *fill;
float *size;
float gflip, dflip, gspin, dspin, gcol;
float *maprange, *maprate;
Coord square[][2] = {
    {-0.1, -0.1},
    { 0.1, -0.1},
    { 0.1,  0.1},
    {-0.1,  0.1}
};
  
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
  x=(float *)calloc(NPNTS, sizeof(float));
  y=(float *)calloc(NPNTS, sizeof(float));
  dzoom=(float *)calloc(NPNTS, sizeof(float));
  arm=(float *)calloc(NPNTS, sizeof(float));
  wrist=(float *)calloc(NPNTS, sizeof(float));
  dtwist=(float *)calloc(NPNTS, sizeof(float));
  flip=(float *)calloc(NPNTS, sizeof(float));
  spin=(float *)calloc(NPNTS, sizeof(float));
  outline=(Boolean *)calloc(NPNTS, sizeof(Boolean));
  fatline=(Boolean *)calloc(NPNTS, sizeof(Boolean));
  fill=(Boolean *)calloc(NPNTS, sizeof(Boolean));
  size=(float *)calloc(NPNTS, sizeof(float));
  maprange=(float *)calloc(NPNTS, sizeof(float));
  maprate=(float *)calloc(NPNTS, sizeof(float));
  
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
  gconfig();

  needredraw();
  defpanel();

  switch (getplanes()) {
  case 4:
    ncolors=15;
    basecolor=1;
    maprangeslider->minval=0.0;
    maprangeslider->maxval=10.0;
    fixact(maprangeslider);
    pnl_background_color	= 8;
    pnl_white_color		= 4;
    pnl_normal_color		= 9;
    pnl_other_color		= 7;
    pnl_highlight_color		= 4;
    pnl_outline_color		= 11;
    break;
  case 8:
    ncolors=128;
    basecolor=128;
    break;
  case 12:
  default:
    ncolors=128;
    basecolor=512;
    break;
  }
  savecolors();

  load_spectrum_map();
  color(bkg);
  clear();
  swapbuffers();
  clear();
  
#ifdef IRIS_4D
  shademodel(FLAT);
  concave(FALSE);
#endif IRIS_4D
#ifdef IRIS_GT
  glcompat(GLC_OLDPOLYGON, FALSE);
#endif IRIS_GT

  perspective(300, 1.0, 0.01, 1000000.0);
  polarview(10.0, 0, 0, 0);
  /*   lookat(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0); */
#ifdef IRIS_GT
  lsetdepth(0x0, 0x7fffff);
#else  IRIS_GT
  setdepth(0x0000,0x3fff);
#endif IRIS_GT
  
  n=0;
  t=0.0;
  gcol=BASECOLOR+ncolors/2;

  for (;;) {

    a=dopanel();
    if (stopbutton->val==1.0) {
      if (smearbutton->val!=1.0) {
        color(bkg);
	clear();
      }
      drawit();
      swapbuffers();
      do {
	a=dopanel();
	if (!a) sginap(0);
	swapbuffers();
      } while (stopbutton->val==1.0);
    }

    if (fullbutton->val==1.0
        && getbutton(LEFTMOUSE)) regularscreen();

    t+=speedslider->val;
    newn=FALSE;
    if (t>=1.0) newn=TRUE;
    n+=floor(t);
    t=fmod(t,1.0);

    x[n%NPNTS]=PNL_ACCESS(Puck,positionpuck,x);
    y[n%NPNTS]=PNL_ACCESS(Puck,positionpuck,y);
    dzoom[n%NPNTS]=zoomslider->val;
    arm[n%NPNTS]=armslider->val;
    wrist[n%NPNTS]=wristslider->val;
    dwheel=speedslider->val*wheelslider->val;
    dtwist[n%NPNTS]=twistslider->val;
    nlimit=(int)nslider->val;
    outline[n%NPNTS]=outlinebutton->val==1.0;
    fatline[n%NPNTS]=fatlinebutton->val==1.0;
    fill[n%NPNTS]=fillbutton->val==1.0;
    size[n%NPNTS]=sizeslider->val;
    maprange[n%NPNTS]=maprangeslider->val;
    gcol+=speedslider->val*maprateslider->val;
    while(gcol<basecolor) gcol+=ncolors;
    while(gcol>=basecolor+ncolors) gcol-=ncolors;
        
    if (newn) {
        dflip=flipslider->val;
	dspin=spinslider->val;

        gflip=fmod(gflip+dflip,360.0);
	flip[n%NPNTS]=gflip;

	gspin=fmod(gspin+dspin,360.0);
	spin[n%NPNTS]=gspin;
    }

/*     winset(mexwin); */
    if (userredraw()) {
	reshapeviewport();
	if (fullbutton->val==1.0) 
	  perspective(300, (float)XMAXSCREEN/(float)YMAXSCREEN, 0.01, 10000.0);
	else
	  perspective(300, 1.0, 0.01, 10000.0);
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
        color(bkg);
	clear();
    } else {
      if (fadebutton->val==1.0) fadebackground(bkg, 1);
      if (smoothbutton->val==1.0) {
	drawit();
	swapbuffers();
	if (fadebutton->val==1.0) fadebackground(bkg, 0);
	drawpanel();
      }
    }

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
foldtwixt(i,x,t)
int i;
float *x;
float t;
{
  float r;
  float d;
  int j=i-1;

    if (j<0) j+=NPNTS;
    d=x[i]-x[j];
    if	    (d> 180.0) r=x[i]*t+(x[j]+360.0)*(1.0-t);
    else if (d<-180.0) r=(x[i]+360.0)*t+x[j]*(1.0-t);
    else	       r=x[i]*t+x[j]*(1.0-t);

    return r;
}

drawit()
{
int i,j;
int outlinecolor;
float tx,ty,tdzoom,tarm,twrist,tsize;
float tspin,tflip,tdtwist;
float col;

    if (ribbonbutton->val==1.0) {
      drawribbons(); return;
    }
    if (zbufbutton->val==1.0) zclear();
    col=gcol;

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
      tspin=foldtwixt(j,spin,t);
      tflip=foldtwixt(j,flip,t);
      tdtwist=twixt(j,dtwist,t);

      color((int)col);
      if (outline[j]) {
	outlinecolor=((int)col+ncolors/2);
	if (outlinecolor>=basecolor+ncolors) outlinecolor-=ncolors;
      }
      col-=maprange[j];
      while(col<basecolor) col+=ncolors;
      while(col>=basecolor+ncolors) col-=ncolors;

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
      if (fill[j]) polf2(3, triangle);
      if (outline[j]) {
	  color(outlinecolor);
	  poly2(3, triangle);
          color((int)col);
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
      if (fill[j]) polf2(3, triangle);
      if (outline[j]) {
	  color(outlinecolor);
	  poly2(3, triangle);
          color((int)col);
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
      if (fill[j]) polf2(3, triangle);
      if (outline[j]) {
	  color(outlinecolor);
	  poly2(3, triangle);
          color((int)col);
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
      if (fill[j]) polf2(3, triangle);
      if (outline[j]) {
	  color(outlinecolor);
	  poly2(3, triangle);
          color((int)col);
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
  int outlinecolor;
  float tx,ty,tdzoom,tarm,twrist,tsize;
  float tspin,tflip,tdtwist;
  float col;
  
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
      tspin=foldtwixt(j,spin,t);
      tflip=foldtwixt(j,flip,t);
      tdtwist=twixt(j,dtwist,t);
      
      color((int)col);
      if (outline[j]) {
	outlinecolor=((int)col+ncolors/2);
	if (outlinecolor>=basecolor+ncolors) outlinecolor-=ncolors;
      }
      col-=maprange[j];
      while(col<basecolor) col+=ncolors;
      while(col>=basecolor+ncolors) col-=ncolors;
      
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

defpanel()
{
Actuator *a;
struct resetbutton *rb;
Coord y, dy=0.5;

    initscriptpanel();

    panel=mkpanel();
#ifdef IRIS_4D
    panel->ppu=40.0;
#else
    panel->ppu=38.0;
#endif
    panel->label="electro-paint";

    a=mkact(pnl_label);
    a->x=0.2;
    a->y=17.5;
    a->label="...by Dave Tristram";
    addact(a,panel);

    a=mkact(pnl_wide_button);
    a->x=0.0;
    a->y=0.0;
    a->label="exit";
    a->upfunc=cleanexit;
    addact(a,panel);

    y=3.0;

    outlinebutton=mkact(pnl_toggle_button);
    outlinebutton->label="outline (O)";
    outlinebutton->labeltype=PNL_LABEL_LEFT;
    outlinebutton->x=4.5;
    outlinebutton->y=(y-=dy);
    outlinebutton->key=OKEY;
    addact(outlinebutton,panel);

    fatlinebutton=mkact(pnl_toggle_button);
    fatlinebutton->label="fat lines (I)";
    fatlinebutton->labeltype=PNL_LABEL_LEFT;
    fatlinebutton->x=4.5;
    fatlinebutton->y=(y-=dy);
    fatlinebutton->key=IKEY;
    addact(fatlinebutton,panel);

    fillbutton=mkact(pnl_toggle_button);
    fillbutton->label="fill (U)";
    fillbutton->labeltype=PNL_LABEL_LEFT;
    fillbutton->x=4.5;
    fillbutton->y=(y-=dy);
    fillbutton->val=1.0;
    fillbutton->key=UKEY;
    addact(fillbutton,panel);

    ribbonbutton=mkact(pnl_toggle_button);
    ribbonbutton->label="ribbons (R)";
    ribbonbutton->labeltype=PNL_LABEL_LEFT;
    ribbonbutton->x=4.5;
    ribbonbutton->y=(y-=dy);
    ribbonbutton->key=RKEY;
    addact(ribbonbutton,panel);

    smoothbutton=mkact(pnl_toggle_button);
    smoothbutton->label="smooth (M)";
    smoothbutton->labeltype=PNL_LABEL_LEFT;
    smoothbutton->x=4.5;
    smoothbutton->y=(y-=dy);
    smoothbutton->downfunc=setsmooth;
    smoothbutton->key=MKEY;
    addact(smoothbutton,panel);

    smearbutton=mkact(pnl_toggle_button);
    smearbutton->label="smear (Q)";
    smearbutton->labeltype=PNL_LABEL_LEFT;
    smearbutton->x=4.5;
    smearbutton->y=(y-=dy);
    smearbutton->downfunc=setsmear;
    smearbutton->key=QKEY;
    addact(smearbutton,panel);

    fadebutton=mkact(pnl_toggle_button);
    fadebutton->label="fade (W)";
    fadebutton->labeltype=PNL_LABEL_LEFT;
    fadebutton->x=4.5;
    fadebutton->y=(y-=dy);
    fadebutton->key=WKEY;
    addact(fadebutton,panel);

    zbufbutton=mkact(pnl_toggle_button);
    zbufbutton->label="z-buf";
    zbufbutton->labeltype=PNL_LABEL_LEFT;
    zbufbutton->x=4.5;
    zbufbutton->y=(y-=dy);
    zbufbutton->downfunc=setzbuf;
    addact(zbufbutton,panel);

    stopbutton=mkact(pnl_toggle_button);
    stopbutton->label="stop (S)";
    stopbutton->labeltype=PNL_LABEL_LEFT;
    stopbutton->x=4.5;
    stopbutton->y=(y-=dy);
    stopbutton->key= SKEY;
    addact(stopbutton,panel);

    fullbutton=mkact(pnl_toggle_button);
    fullbutton->label="full screen (F)";
    fullbutton->labeltype=PNL_LABEL_LEFT;
    fullbutton->x=4.5;
    fullbutton->y=(y-=dy);
    fullbutton->downfunc=togglefullscreen;
    fullbutton->key=FKEY;
    addact(fullbutton,panel);

    positionpuck=mkact(pnl_floating_puck);
    positionpuck->x=0.0;
    positionpuck->y=1.5;
    addact(positionpuck,panel);

#define MK_EP_SLIDER(Mname,Mlabel,Mx,My,Mmin,Mmax,Mval,Mvar)	\
    Mname/**/slider=mkact(pnl_dvslider);			\
    Mname/**/slider->label=Mlabel;			\
    Mname/**/slider->labeltype=PNL_LABEL_BOTTOM;	\
    Mname/**/slider->x=(Mx);				\
    Mname/**/slider->y=(My);				\
    Mname/**/slider->val=(Mval);			\
    Mname/**/slider->minval=(Mmin);			\
    Mname/**/slider->maxval=(Mmax);			\
    addact(Mname/**/slider,panel);				\
							\
    rb=PNL_MKUSERACT(resetbutton, pnl_wide_button);	\
    rb->targetact=Mname/**/slider;			\
    rb->targetvar=Mvar;					\
    rb->varinitval=0.0;					\
    rb->button.label="R";				\
    rb->button.w=PNL_SLIDER_WIDTH;			\
    rb->button.h=PNL_BUTTON_EDGE;			\
    rb->button.x=Mx;					\
    rb->button.y=(My)+PNL_SLIDER_HEIGHT+PNL_DIM_2;	\
    rb->button.downfunc=resetact;			\
    addact((Actuator *)rb, panel);


    MK_EP_SLIDER(zoom,"zoom",	0.0,	3.5,	-0.5,	0.5,	0.0, NULL);
    MK_EP_SLIDER(twist,"twst",	1.0,	3.5,	-100.0,	100.0,	0.0, NULL);
    MK_EP_SLIDER(speed,"spd",	2.0,	3.5,	0.0,	1.0,	1.0, NULL);
    MK_EP_SLIDER(n,"n",		3.0,	3.5,	1.0,NPNTS.0-1.0 ,32.0, NULL);
    MK_EP_SLIDER(maprate,"rat", 4.0,	3.5,	-20.0,	20.0,	1.0, NULL);
    MK_EP_SLIDER(maprange,"rng",5.0,	3.5,	0.0,	100.0,	1.0, NULL);

    MK_EP_SLIDER(wheel,"whl",	0.0,	10.5,	-60.0,	60.0,	0.0, &wheel);
    MK_EP_SLIDER(spin,"spn",	1.0,	10.5,	-20.0,	20.0,	0.0, &gspin);
    rb->varinitval=15.0;	/* initial value for gspin */
    resetact(rb);
    MK_EP_SLIDER(flip,"flp",	2.0,	10.5,	-20.0,	20.0,	0.0, &gflip);
    MK_EP_SLIDER(arm,"arm",	3.0,	10.5,	0.0,	3.0,	0.0, NULL);
    MK_EP_SLIDER(wrist,"wrst",	4.0,	10.5,	0.0,	3.0,	0.0, NULL);
    MK_EP_SLIDER(size,"sz",	5.0,	10.5,	0.1,	10.0,	1.0, NULL);

}

