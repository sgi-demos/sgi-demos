/*
 Version 2.29

 Original program from: howardl@landis.csd.sgi.com (Howard Look)
   Here's yet another little background program. It looks like the
   sky at sunset. It will only run properly on 24 or more bit plane systems.
 Enjoy.

 night enhancements uunet!alberta!calgary!paquette
 Jun-19-1990: Trevor Paquette
	      - hacked up data structures for 'square stars' 
	      - added twinkle feature
    Please email any enhancements to me so I can keep an upto date version

 Jun-25-1990: Reuel Nash
	      - changed timers from timeout/signal handler to 
		queued device TIMER1: you can't do graphics reliably 
	        from inside a signal handler and main, too.
		Change overall timer rate with noise() call.
	      - removed unecessary stuff from trand().
	      - the pixel readback scheme to find out what color
		to "blink" to won't work if there are windows obscuring 
		the background on startup. This is now calculated 
		by the program from background colors and Y1 and Y2.
		See get_sky().
	      - stars don't need to be shaded. Use single packed color
		for each star and background of star.
	      - added "comets". (really more like shooting stars). 

 Jun-26-1990: tristram@sgi.com for:
              - aspect ratio of screen added. Makes stars look 'squarer'
	        (rounder?)
	      - added 'venus'

 Jul-03-1990: Trevor Paquette
              - Stars are brighter nearer the top of the screen then the bottom
	        (allows for 'sunset dimming of stars')
              - No stars should be in the actual 'sunset' area.
	      - added 'mars'
 
 Jul-06-1990: John Mitchell
              - added command line switches for number of big stars, number of
                groups of small stars, and twinkle rate.
	      - added a new color scheme, and mail checker

 Jul-06-1990: Trevor Paquette
              - added command line switch for color schemes
	      - changed mail checker to make big stars turn green when new mail
	        arrives instead of changing size. The old way would create
		'holes' in the sky when the star changed back. There is a
		bug in the mail checker in that it thinks 'new' mail has
		arrived whenever the file is 'accessed'. This is wrong. It
		should only think there is new mail, when there is NEW mail.
 Jul-16-1990
              - stars are now back to being circles.
	      - fixed comets outside of window bug
	      - added load average checker

 Compile it with:
 cc -O3 -s -o night night.c -lm -lsun -lbsd -lgl_s -lc_s

*/

#include <stdio.h>
#include <gl.h>
#include <device.h>
#include <sys/time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <sys/sysmp.h>
#include <sys/sysinfo.h>

/* a star was a "square", is now a circle

     /-----\
    /       \
   /   x,y   \
   |    .--->|  color   = col
   \     rad /  bgcolor = back
    \       /
     \-----/
*/
        
/* DO NOT CHANGE THE ORDER OF THE DECLARATIONS in starstruct, if you want to add
   something, add it at the end of the structure */
typedef struct _dummy {
  float x, y, rad;	/* location and radius of star 	*/
  long color;		/* color of star		*/
  long back;		/* background color behind star	*/
} starstruct;
 
struct {
  float x0,y0,x1,y1;
  int active;
} comet;

starstruct venus, moon, mars;

#define Y1 		0.0
#define Y2 		0.2
#define SMALL_MAX_BLINK	128
#define BIG_MAX_BLINK   4
#define MOONSCALE       0.04
#define INMOON(a) sqrt(((moon.x-a.x)*(moon.x-a.x))+((moon.y-a.y)*(moon.y-a.y))) < MOONSCALE
#define NUMCOLSCHEMES   1  /* actually from 0 to NUMCOLSCHEMES */
#define MAILCHECKCTR 100
#define	INTERVAL	1
#define	NSAMPLES (15 /* minutes */ * 60 /* sec/min */ / INTERVAL)

/* default num of groups of 256 stars */
int numgroups = 8;
/* default num of big stars */
int numbig =  175;
/* default twinkle rate of the stars */
int twinkle_rate = 30;
/* default color scheme */
int colorscheme = 0;
/* check mail or not */
int mailcheck = 0;
/* default load average turn off rate */
int loadaverage = 1.00;

/* pointer to locations of small stars */
starstruct *small_stars = NULL;
/* pointer to locations of big stars */
starstruct *big_stars = NULL;
/* at most SMALL_MAX_BLINK small stars blink at a time */
starstruct *small_blinker[SMALL_MAX_BLINK];
/* at most BIG_MAX_BLINK big_stars blink at a time */
starstruct *big_blinker[BIG_MAX_BLINK];

/* mail checker vars */
long mailstarcolor = 0;
int mailcheckctr = MAILCHECKCTR;
char mailfile[100];

/* load average vars */
int ringload[NSAMPLES];
int ringindex = 0;
int loadflag = 0;

/* colors now global so get_sky() works */
int red[][3] = {
  {255,  0,  0},
  {255, 72,  0},
};
int orange[][3] = {
  {255, 72,  0},
  {152,  0,194},
};
int blueish[][3] = {
  {  0,110,189},
  { 45,  0,175},
};
int black[][3] = {
  {  0,  0,  0},
  {  0,  0,  0},
};

/* venus is actually a cross */
float cross[][2] = {
  { 0.0, 3.0 },
  { 0.15, 0.15 },
  { 3.0, 0.0 },
  { 0.15, -0.15 },
  { 0.0, -6.0 },
  { -0.15, -0.15 },
  { -3.0, 0.0 },
  { -0.15, 0.15 },
};

/* this is bogus, should just be a rotation in y */
static float arcparm[][2] = {
  { 1.0002, 88.8542 },
  { 1.0008, 87.7094 },
  { 1.0018, 86.5664 },
  { 1.00319, 85.4261 },
  { 1.00499, 84.2894 },
  { 1.00717, 83.1572 },
  { 1.00975, 82.0304 },
  { 1.01272, 80.9097 },
  { 1.01607, 79.796 },
  { 1.0198, 78.6901 },
  { 1.02391, 77.5926 },
  { 1.0284, 76.5043 },
  { 1.03325, 75.4258 },
};
 
long width, height, owidth, oheight;
float aspect;

main(argc, argv)
int argc;
char *argv[];
{
 int gid, skyevent(), i;
 short val;
 long dev;
 char *malloc(), *user;
 
   /* parse arguments */
 parse: {
    extern char *optarg;
    extern int optind;
    int c, usage=0;

    while ((c = getopt(argc, argv, "g:b:r:c:ml")) != -1) {
       switch (c) {

	  /* -g (n) = set number of 256-groups of stars */
       case 'g':
	  numgroups = atoi(optarg);
	  break;

	  /* -b (n) = set number of big stars */
       case 'b':
	  numbig = atoi(optarg);
	  break;

	  /* -r (n) = set rate of twinkle */
       case 'r':
	  twinkle_rate = atoi(optarg);
	  break;

	  /* -m = check mail or not */
       case 'm':
	  mailcheck = 1;
	  break;

	  /* -l = toggle load average checker */
       case 'l':
	  loadaverage = 100000;
	  break;

	  /* -c (n) = colorscheme number */
       case 'c':
	  colorscheme = atoi(optarg);
	  if((colorscheme < 0) || (colorscheme > NUMCOLSCHEMES))
             usage++;
          break;

       default:
	  usage++;
       }

       if (usage) {
	  fprintf(stderr, "usage: %s [-r twinkle_rate] [-g #stargroups] [-b #bigstars] [-c colorscheme] [-m]\n", argv[0]);
	  fprintf(stderr, "          [-l]\n");
	  fprintf(stderr,"             r: try between 10 and 40 (default %d)\n", twinkle_rate);
	  fprintf(stderr,"             g: try between 5 and 14 (default %d)\n", numgroups);
	  fprintf(stderr,"             b: try between 140 and 250 (default %d)\n", numbig);
	  fprintf(stderr,"             c: try from 0 to %d (default 0)\n", NUMCOLSCHEMES);
	  fprintf(stderr,"             m: mail checker\n");
	  fprintf(stderr,"             l: toggle load average slowing down rate(default on)\n");
	  fprintf(stderr,"                (when load increases, less cpu is used by night)\n");
	  exit(0);
       }
    }
 }

 user = (char *)getlogin(NULL);
 if(!user)
    user = getpwuid(getuid())->pw_name;
 sprintf(mailfile, "/usr/mail/%s", user);

 for(i = 0; i < SMALL_MAX_BLINK; i++) {
   small_blinker[i] = NULL;
 }
 for(i = 0; i < BIG_MAX_BLINK; i++) {
   big_blinker[i] = NULL;
 }
  
 small_stars = (starstruct *) malloc(numgroups*256*sizeof(starstruct));
 big_stars =  (starstruct *) malloc(numbig*sizeof(starstruct));

#ifdef DEBUG
 foreground();
#else
 imakebackground() ;
#endif
 gid = winopen("") ;
#ifdef DEBUG
 getsize(&owidth, &oheight);
#else
 owidth = XMAXSCREEN;
 oheight = YMAXSCREEN;
#endif
 RGBmode();
 gconfig();
 shademodel(GOURAUD);
	
 aspect = ((float)owidth/(float)oheight);
 ortho2(0.0, aspect, 0.0, 1.0) ;

 glcompat(GLC_OLDPOLYGON,0);

 qdevice(TIMER1);
 noise(TIMER1, twinkle_rate);
 qenter(REDRAW,gid);

 while (1) {
   dev = qread(&val) ;
   switch(dev) {
   case REDRAW:
#ifdef DEBUG
        getsize(&width, &height);
	if((width != owidth) || (height != oheight)) {
          reshapeviewport();
          owidth = width;
	  oheight = height;
	}
#endif
	draw_background();
	break;
   case TIMER1:    
	skyevent();
	break;
   }
 }
}


draw_background()
{
 int i,j, skyevent(), col[3];
 static int first = 1;
 float v1[2],v2[2],v3[2],v4[2];
 register int counter;

 v1[0] = v4[0] = 0.0;
 v2[0] = v3[0] = aspect;

 v1[1] = v2[1] = 0.0;
 v3[1] = v4[1] = Y1;

 bgnpolygon();
   c3i(red[colorscheme]);
   v2f(v1);
   v2f(v2);
   c3i(orange[colorscheme]);
   v2f(v3);
   v2f(v4);
 endpolygon();

 v1[1] = v2[1] = Y2;
 bgnpolygon();
   c3i(orange[colorscheme]);
   v2f(v4);
   v2f(v3);
   c3i(blueish[colorscheme]);
   v2f(v2);
   v2f(v1);
 endpolygon();

 v3[1] = v4[1] = 1.0;
   bgnpolygon();
   c3i(blueish[colorscheme]);
   v2f(v1);
   v2f(v2);
   c3i(black[colorscheme]);
   v2f(v3);
   v2f(v4);
 endpolygon();

 if(first) {
   setup_sky();
   first = 0;
 }

 counter = 0;
 for(j=0; j<numgroups; j++) {
   bgnpoint();
   for(i=0; i<256; i++) {
     cpack(small_stars[counter].color);
     v2f(&small_stars[counter].x);
     counter++;
   }
   endpoint();
 }

 for(j=0; j<numbig; j++) {
   if(mailstarcolor)
     cpack(mailstarcolor);
   else
     cpack(big_stars[j].color);
   circf(big_stars[j].x, big_stars[j].y, big_stars[j].rad);
 }

}

/* ----------------------------------------------------------------------
 *  Random number generator
 *  Author: Trevor Paquette
 *  Modified 6/25: Reuel Nash
 *  Purpose: returns a random number between x and y
 *           (positive only)
 */

long
trand(x,y)
int x,y;
{
 long ret;
 static int seeded = 0;

 if(!seeded) {
   srand((int)time(0));
   seeded = 1;
 }

 ret = x + rand() % (y-x+1);
 return(ret);
}
						       

skyevent()
{
 /* anything like comets .. astral events etc,, should be added here */
 long event, trand(), tmp;
 register int starnum, i, counter;
 static small_numstars = 0, big_numstars = 0;
 char *malloc();
 int col[3];
 float v1[2], v2[2], v3[2], v4[2], t, load(), l;

 l = load();
 if(l > (float)loadaverage) {
   noise(TIMER1, twinkle_rate * (int)(l*2.5));
 }
 else {
    noise(TIMER1, twinkle_rate);
 }

 if(mailcheck) {
   /* check for mail.  If there is, make the big stars blimp up */
   if(mailcheckctr-- < 0) {
     long oldmailstarcolor = mailstarcolor;
     struct stat statb;

     mailcheckctr = MAILCHECKCTR;
     if(!stat(mailfile, &statb)) {
       mailstarcolor = 0x0000FF00; /* set 'has mail' color to green */
     } else {
       mailstarcolor = 0;
     }
     if(mailstarcolor != oldmailstarcolor)
       draw_background();
   }
 }

 event = trand(1, 100); 	/* an event is based on percentage chance of happening */
				/* star twinkle = all of the time */
				/* comet = 2% ?? */
				/* percentages should total 100 */

 /* turn on the stars that we turned off last time we were here */
 if(small_numstars) {
   for(i = 0; i < small_numstars; i++) {
     bgnpoint();
       cpack(small_blinker[i]->color);
       v2f(&small_blinker[i]->x);
     endpoint();
   }
 }
 if(big_numstars) {
   for(i = 0; i < big_numstars; i++) {
     cpack(big_blinker[i]->color);
     circf(big_blinker[i]->x, big_blinker[i]->y, big_blinker[i]->rad);
   }
 }

 if(comet.active) {
   bgnline();
   cpack(get_sky(comet.y0));
   v2f(&comet.x0);
   cpack(get_sky(comet.y1));
   v2f(&comet.x1);
   endline();
   comet.active = 0;
 }

 small_numstars = trand(1, SMALL_MAX_BLINK); /* blink between 0 and SMALL_MAX_BLINK stars */
 for(i = 0; i < small_numstars; i++) {
   starnum = trand(0, numgroups*256);
   small_blinker[i] = &small_stars[starnum];
   bgnpoint();
     cpack(small_stars[starnum].back);
     v2f(&small_stars[starnum].x);
   endpoint();
 }
 big_numstars = trand(1, BIG_MAX_BLINK); /* blink between 0 and BIG_MAX_BLINK stars */
 for(i = 0; i < big_numstars; i++) {
   starnum = trand(0, numbig);
   big_blinker[i] = &big_stars[starnum];
   cpack(big_blinker[i]->color);
   circf(big_blinker[i]->x, big_blinker[i]->y, big_blinker[i]->rad);
 }

 if((event >= 1) && (event <= 10)) { /* shooting star event */
   do {
     comet.x0 = ((float)trand(0,32767))/32767.0;
     do {
       comet.y0 = ((float)trand(0,32767))/32767.0;
     }
     while(comet.y0  < Y2);
     comet.x1 = comet.x0 + ((float)trand(0,32767))/327670.0;
     comet.y1 = comet.y0 + ((float)trand(0,32767))/327670.0;
   }
   while((comet.x0 > aspect) || (comet.y0 > 1.0) || (comet.x1 > aspect) || (comet.y1 > 1.0));
   bgnline();
   /* use height of head of comet as basis for color. */
   t = comet.y0 - Y2; /* number between 0.0 and 1.0-Y2 */
   t /= (1.0-Y2);                   /* number between 0.0 and 1.0    */
   tmp = 127 + (long)(t*128.0);     /* color from 128 - 255 based on height */
   tmp += (trand(0,40) - 20);       /* fudge the color a bit */
   tmp |= tmp << 8 | tmp << 16;
   cpack(tmp);
   v2f(&comet.x0);
   cpack(get_sky(comet.y1));
   v2f(&comet.x1);
   endline();
   comet.active = 1;
 }

/* mars */
  cpack(mars.color);
  circf(mars.x, mars.y, mars.rad);

/* venus */
  cpack(venus.color);
  pushmatrix();
  translate(venus.x, venus.y, 0.0);
  scale(0.004, 0.004, 0.0);
  bgnpolygon();
  for(i = 0; i < 8; i++)
    v2f(&cross[i][0]);
  endpolygon();
  popmatrix();

/* moon */
  pushmatrix();
  pushattributes();
  linewidth(3);
  translate(moon.x, moon.y, 0.0);
  scale(MOONSCALE, MOONSCALE, 0.0);
  rotate(-600, 'z');
  cpack(moon.color);
  for(i = 0; i < 13; i++ ) {
    arc(0.0, 0.0, arcparm[i][0], (int)(-10.0 * arcparm[i][1]),
                                 (int)(10.0 * arcparm[i][1]));
    translate(-0.02, 0.0, 0.0);
  }
  popattributes();
  popmatrix();
}

setup_sky()
{
 register int i, j;
 register int counter;
 long tmp, trand(), get_sky();
 float t;

 comet.active = 0;
 /* moon */
 do {
   moon.x = aspect * ((float)trand(0, 32767))/32767.0;
   moon.y = ((float)trand(0,32767))/32767.0;
 }
 while(moon.y < 0.75); /* make sure moon is high in the sky */
 moon.color = 0x00DDDDDD;

 /* setup big stars , should be done BEFORE small stars */
 for(j =0; j<numbig; j++) {
   /* no stars should be visible in the 'sunset' area */
   do {
     big_stars[j].x = aspect * (((float)trand(0,32767))/32767.0);
     big_stars[j].y = ((float)trand(0,32767))/32767.0;
   }
   while((big_stars[j].y < Y2) || INMOON(big_stars[j]));
   big_stars[j].rad = 1.2 * (((float)trand(0,32767))/32767.0/500.0);
   big_stars[j].back = get_sky(big_stars[j].y);
   /* star color depends on height to the top of the screen plus some random
    * number between -20 and 20. stars nearer the top of the screen should on
    * average be brighter the those nearer the bottom
    */
   /* use height of star as basis for color. */
   t = big_stars[j].y - Y2;    /* number between 0.0 and 1.0-Y2 */
   t /= (1.0-Y2);              /* number between 0.0 and 1.0    */
   tmp = 127 + (long)(t*128.0);/* color from 128 - 255 based on height */
   tmp += (trand(0,40) - 20);  /* fudge the color a bit */
   tmp |= tmp << 8 | tmp << 16;
   big_stars[j].color =  tmp;
 }

 /* set up small stars. */
 counter = 0;
 for(j=0; j<numgroups; j++) {
   for(i=0; i<256; i++) {
     do {
       small_stars[counter].x = aspect * (((float)trand(0,32767))/32767.0);
       small_stars[counter].y = ((float)trand(0,32767))/32767.0;
     }
     while((small_stars[counter].y < Y2) || INMOON(small_stars[counter]));
     small_stars[counter].rad = 0.0;
     small_stars[counter].back = get_sky( small_stars[counter].y);
     /* use height of star as basis for color. */
     t = small_stars[counter].y - Y2; /* number between 0.0 and 1.0-Y2 */
     t /= (1.0-Y2);                   /* number between 0.0 and 1.0    */
     tmp = 127 + (long)(t*128.0);     /* color from 128 - 255 based on height */
     tmp += (trand(0,40) - 20);       /* fudge the color a bit */
     tmp |= tmp << 8 | tmp << 16;
     small_stars[counter].color = tmp;
     counter++;
   }
 }

 /* venus */
 do {
   venus.x = aspect * ((float)trand(0, 32767))/32767.0;
   venus.y = ((float)trand(0,32767))/32767.0;
 }
 while(venus.y < Y2*3 || INMOON(venus));
 venus.color = 0x00FFFFFF;

 /* mars */
 do {
   mars.x = aspect * ((float)trand(0, 32767))/32767.0;
   mars.y = ((float)trand(0,32767))/32767.0;
 }
 while(mars.y < Y2*3 || INMOON(mars));
 mars.rad = (((float)trand(0,32767))/32767.0/500.0);
 mars.color = 0x000F0FFF;

}

long
get_sky(y)
float y;
{
    int r,g,b;

    if(y < Y1) {
	y /= Y1;
	r = red[colorscheme][0] * (1.-y) + orange[colorscheme][0] * y;
	g = red[colorscheme][1] * (1.-y) + orange[colorscheme][1] * y;
	b = red[colorscheme][2] * (1.-y) + orange[colorscheme][2] * y;
    } else if( y < Y2) {
	y = (y - Y1)/(Y2 - Y1);
	r = orange[colorscheme][0] * (1.-y) + blueish[colorscheme][0] * y;
	g = orange[colorscheme][1] * (1.-y) + blueish[colorscheme][1] * y;
	b = orange[colorscheme][2] * (1.-y) + blueish[colorscheme][2] * y;
    } else {
	y = (y - Y2)/(1 - Y2);
	r = blueish[colorscheme][0] * (1.-y) + black[colorscheme][0] * y;
	g = blueish[colorscheme][1] * (1.-y) + black[colorscheme][1] * y;
	b = blueish[colorscheme][2] * (1.-y) + black[colorscheme][2] * y;
    }

    return (r&0xff) + ((g&0xff)<<8) + ((b&0xff)<<16);
}

float
load()
{
/*
 From: rayan@ai.toronto.edu (Rayan Zachariassen)
 Subject: Re: Finding load average on Iris 4D
*/
 struct sysinfo sinfo;
 int now, last1, last5, last15;

 now = ringindex;
 sysmp(MP_SAGET, MPSA_SINFO, &sinfo, sizeof sinfo);
 ringload[ringindex++] = sinfo.runque;
 if(!loadflag) {
   while(loadflag < NSAMPLES)
     ringload[loadflag++] = sinfo.runque;
 }
 ringindex %= NSAMPLES;
 last1 = (NSAMPLES + now - 60 / INTERVAL)%NSAMPLES;
 return((float)((ringload[now] - ringload[last1])/60.0));
}
