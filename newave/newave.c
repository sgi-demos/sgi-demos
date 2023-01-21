#include <stdio.h>
#include <gl.h>
#include <math.h>
#include <device.h>

#define PI 3.1415926536
#define NRAMPB 832
#define NRAMPE 1023
#define DRAMPB 768
#define DRAMPE 831
#define CRAMPB 700
#define CRAMPE 767
#define SRAMP 1024
#define MYRED 1536
#define MYGREEN 1552
#define MYCYAN 1568

#define X 0
#define Y 1
#define Z 2

#define GRID 21	    /* largest possible grid size */

int grid = 17;
float dt = 0.004;

Angle dtheta=0, dphi=0;
Angle sphi=0, stheta=450;
Coord sdepth;

float light[3],phi=PI/4.0,theta=PI/4.0;
float dot();
int getpolycolor(), getpolycolor2();

short dev,val;
Boolean attached,smode=FALSE;
Boolean spin;
int x,y;
short omx,omy,nmx,nmy;

float force[GRID][GRID],
      veloc[GRID][GRID],
      posit[GRID][GRID],
      vertvec[GRID][GRID][3];

int   colur[GRID][GRID];

int menu, killmenu, display_menu, grid_menu, speed_menu;

int dmode=1;
#define NORMAL 1
#define DEPTHCUED 2
#define FLAT_SHADED 3
#define GOURAUD_SHADED 4
#define TOPVIEW 5

int antialias=FALSE;
int editing = FALSE;

Coord near=1.0, far=40.0, onear=1.0, ofar=40;
float aspect = 5.0/4.0;
short oldcolors[1024][3];

long xsize, ysize, xorig, yorig;

menukill() 
{
	int really;

	qreset();
	really = dopup(killmenu);
	if (really != 1) return;

	restore_colors();
	gexit();
	exit(0);
}


menugrid()
{
    qreset();
    switch (dopup(grid_menu)) {
	case 1:
	    grid = 13;
	    break;
	case 2:
	    grid = 17;
	    break;
	case 3:
	    grid = 21;
	break;
    }
    
}

menuspeed()
{
    qreset();
    switch (dopup(speed_menu)) {
	case 1:
	    dt = 0.001;
	    break;
	case 2:
	    dt = 0.004;
	    break;
	case 3:
	    dt = 0.008;
	break;
    }
    
}


selectmode()
{
	smode=TRUE;
	sphi=0; stheta=450;
	nmx=getvaluator(MOUSEX); nmy=getvaluator(MOUSEY);
	omx=nmx; omy=nmy;
	spin=TRUE; spin_scene(); spin=getbutton(MOUSE2);
	near=1.0; far=40.0; fixwindow();

    if (antialias) {
	smoothline(TRUE);
	zbuffer(TRUE);
	zsource(ZSRC_COLOR);
	zfunction(ZF_GEQUAL);
    } else {
	smoothline(FALSE);
	zfunction(ZF_LEQUAL);
	zsource(ZSRC_DEPTH);
    }
}

go()
{
	switch (dmode) {
	case NORMAL:
	    normal_mode();
	    break;
	case DEPTHCUED:
	    depthcued_mode();
	    break;
	case FLAT_SHADED:
	    flat_shaded_mode();
	    break;
	case GOURAUD_SHADED:
	    gouraud_shaded_mode();
	break;
	case TOPVIEW:
	    top_mode();
	    break;
	default:
	    break;
	}
}

reverse()
{
	int i,j;

	for(i=1;i<(grid-1);i++)
	for(j=1;j<(grid-1);j++)
		veloc[i][j]= -veloc[i][j];
	while(getbutton(MOUSE3)) i=1;
}

resetpoints()
{
	int i,j;
	for(i=0;i<grid;i++)
	for(j=0;j<grid;j++)
	{
		force[i][j]=0.0;
		veloc[i][j]=0.0;
		/*posit[i][j]=0.0;*/
        posit[i][j]= (i==j && i == grid/2) ? grid*0.01 : 0.0; /* middle spike */
		vertvec[i][j][X]=0.0;
		vertvec[i][j][Y]=0.0;
		vertvec[i][j][Z]=0.0;
		colur[i][j]=0;
	}
}

normal_mode() {
    dmode = NORMAL;
    depthcue(FALSE);
    near=1.0; far=40.0; fixwindow();
    smode=FALSE;

    if (antialias) {
	smoothline(TRUE);
	zbuffer(TRUE);
	zsource(ZSRC_COLOR);
	zfunction(ZF_GEQUAL);
    } else {
	smoothline(FALSE);
	zfunction(ZF_LEQUAL);
	zsource(ZSRC_DEPTH);
    }
}

depthcued_mode() {
    dmode = DEPTHCUED;
    depthcue(TRUE);
    near=grid/2.0; far=grid*2.0; fixwindow();
    smode=FALSE;

    if (antialias) {
	lshaderange(SRAMP, SRAMP+ 32*16, 0x00, 0x7fffff);
	smoothline(TRUE);
	zbuffer(TRUE);
	zsource(ZSRC_COLOR);
	zfunction(ZF_GEQUAL);
    } else {
	lshaderange(DRAMPB,DRAMPE, 0x00, 0x7fffff);
	smoothline(FALSE);
	zfunction(ZF_LEQUAL);
	zsource(ZSRC_DEPTH);
    }
}

flat_shaded_mode() {
    dmode = FLAT_SHADED;
    depthcue(FALSE);
    near=1.0; far=40.0; fixwindow();
    smode=FALSE;
    smoothline(FALSE);
    zfunction(ZF_LEQUAL);
    zsource(ZSRC_DEPTH);
}

gouraud_shaded_mode() {
    dmode = GOURAUD_SHADED;
    depthcue(FALSE);
    near=1.0; far=40.0; fixwindow();
    smode=FALSE;
    smoothline(FALSE);
    zfunction(ZF_LEQUAL);
    zsource(ZSRC_DEPTH);
}

top_mode() {
    sphi= 150; stheta=0;
    near = 13.0; far = 27.0; fixwindow();
    dmode = TOPVIEW;
    depthcue(TRUE);
    lshaderange(CRAMPB, CRAMPB+65, 0x00, 0x7fffff);
    smode=FALSE;
    smoothline(FALSE);
    zfunction(ZF_LEQUAL);
    zsource(ZSRC_DEPTH);
}

antialias_mode() {
    antialias = !antialias;

    if (smode) {

	selectmode();

    } else switch(dmode) {

	case DEPTHCUED:
	    depthcued_mode();
	    break;

	case NORMAL:
	    normal_mode();
	    break;
    }
}


long gid;


main (argc, argv)
int	argc;
char	*argv[];
{
	Colorindex c;
	int i;
	int r=100, g=255, b=255;

	sdepth = 5.0/4.0 * grid;

	{
		char *t, *strrchr();
		if (getgdesc(GD_BITS_NORM_SNG_RED) == 0)
		{
			system("inform 'Your system must support RGB mode to run newave'");
   	 		exit(1);
		}
		if (getgdesc(GD_BITS_NORM_DBL_CMODE) < 12) {
			system("inform 'Your system must support 890 color entries to run newave'");
			exit(1);
		}
		if (getgdesc(GD_BITS_NORM_ZBUFFER) == 0)
		{
		 	system("inform 'Your system must have a z-buffer to run newave'");
		 	exit(1);
		}
		gid=winopen((t=strrchr(argv[0], '/')) != NULL ? t+1 : argv[0]);
	}

	save_colors();

	getlightvector();

	/* regular */
	makerange(NRAMPB,NRAMPE-25,0,200,0,50,30,255);
	makerange(NRAMPE-24,NRAMPE,200, 255, 50, 255, 255, 255);

	makerange(DRAMPB, DRAMPE,0,50,50,255,50,200);

	/* rainbow */
	makerange(CRAMPB, CRAMPB+5, 255, 255, 0, 255, 0, 0);
	makerange(CRAMPB+6, CRAMPB+11, 255, 0, 255, 255, 0, 0);
	makerange(CRAMPB+12, CRAMPB+17, 0, 0, 255, 255, 0, 255);
	makerange(CRAMPB+18, CRAMPB+23, 0, 0, 255, 0, 255, 255);
	makerange(CRAMPB+24, CRAMPB+29, 0, 255, 0, 0, 255, 255);
	makerange(CRAMPB+30, CRAMPB+35, 255, 255, 0, 0, 255, 0);
	makerange(CRAMPB+36, CRAMPB+41, 255, 255, 0, 255, 0, 0);
	makerange(CRAMPB+42, CRAMPB+47, 255, 0, 255, 255, 0, 0);
	makerange(CRAMPB+48, CRAMPB+53, 0, 0, 255, 255, 0, 255);
	makerange(CRAMPB+54, CRAMPB+58, 0, 0, 255, 0, 255, 255);
	makerange(CRAMPB+59, CRAMPB+63, 0, 255, 0, 0, 255, 255);
	/* lsetdepth(0x00, 0x7fffff); */
	lsetdepth(0x00,(getgdesc(GD_ZMAX)));
	zbuffer(TRUE);

	for (i=0; i<32; i++) {
	
	    makerange (SRAMP + i*16, SRAMP + i*16 + 15,
		    0, r*i/31,
		    0, g*i/31,
		    0, b*i/31);
	}
	makerange (MYRED, MYRED+16, 0, 255, 0, 0, 0, 0);
	makerange (MYGREEN, MYGREEN+16, 0, 0, 0, 255, 0, 0);
	makerange (MYCYAN, MYCYAN+16, 0, 0, 0, 255, 0, 255);


	killmenu = defpup("Really? %t|yes|no");

    display_menu = defpup("Display Type %t|normal %f|depthcued %f|flat shaded %f|gouraud shaded %f|top view %f|antialias %f", normal_mode, depthcued_mode, flat_shaded_mode, gouraud_shaded_mode, top_mode, antialias_mode );

    speed_menu = defpup("Speed %t|weak|medium|strong");
    grid_menu = defpup("Grid Size %t|small|medium|large");

    menu=defpup("WAVE %t|edit|go|reverse|display menu|spring menu|grid menu|reset|kill");

	doublebuffer();
	gconfig();	
	color(BLACK);
	clear(); swapbuffers(); clear();
	color(CYAN);
/*	shaderange(20,50,0,40);	*/
	reshapeviewport();
	fixwindow();
	resetpoints();
	qdevice(UPARROWKEY);
	qdevice(DOWNARROWKEY);
	qdevice(INPUTCHANGE);
	qdevice(REDRAW);
	qdevice(ESCKEY);
	qdevice(WINQUIT);
	qdevice(WINSHUT);
	qdevice(RIGHTMOUSE);
	qdevice(LEFTMOUSE);
	qdevice(MIDDLEMOUSE);
	tie (MIDDLEMOUSE, MOUSEX, MOUSEY);
	tie (LEFTMOUSE, MOUSEX, MOUSEY);

	while(TRUE) {

		while(qtest()) {
			dev=qread(&val);
			switch(dev) {
				case ESCKEY :	/* Ignore ESC up */
					if (val) break;
				case WINQUIT :	/* ESC down or exiting... */
					restore_colors();
					gexit();
					exit(0);
					break;
				case INPUTCHANGE :
					attached=val;
					break;
				case REDRAW :
					reshapeviewport();
					fixwindow();
					break;
				case RIGHTMOUSE :
					if (val)
					    switch(dopup(menu)) {
						case 1:
						    selectmode();
						    break;
						case 2:
						    go();
						    break;
						case 3:
						    reverse();
						    break;
						case 4:
						    dopup(display_menu);
						    break;
						case 5:
						    menuspeed();
						    break;
						case 6:
						    menugrid();
						    break;
						case 7:
						    resetpoints();
						    break;
						case 8:
						    menukill();
						    break;
					    }
					break;
				case MIDDLEMOUSE :
					spin = val;
					omx = nmx; omy = nmy;
					qread(&nmx); qread(&nmy);
					if (!spin) {
						sphi+=(Angle)(nmx-omx);
						stheta+=(Angle)(omy-nmy);
						dtheta = 0;
						dphi = 0;
					}
					break;
				case LEFTMOUSE:
					qread(&nmx); qread(&nmy);
					if (editing=val) {
					    setvaluator(MOUSEX, nmx,
					    xorig, xorig+xsize-1);
					    setvaluator(MOUSEY, nmy,
					    yorig, yorig+ysize-1);
					} else {
					    setvaluator(MOUSEX, nmx,
					    0, getgdesc(GD_XPMAX));
					    setvaluator(MOUSEY, nmy,
					    0, getgdesc(GD_YPMAX));
					}
					break;
			}
		}
		viewit();
		if(smode) {
		    depthcue(FALSE);
		    doscreen();
		} else {
		    switch (dmode) {
		    case NORMAL:
			doscreen();
		        break;
		    case DEPTHCUED:
			depthcue(TRUE);
			doscreen();
		        break;
		    case FLAT_SHADED:
		        facet_shade();
		        break;
		    case GOURAUD_SHADED:
			gouraud_shade();
			break;
		    case TOPVIEW:
			depthcue(TRUE);
			doscreen();
		        break;
		    default:
		        break;
		    }
		    
		}

		if (!smode) {
		    getforce();
		    getvelocity();
		    getposition();
		}

		spin_scene();


	}
}


getforce()
{
	register int i,j;
	register float d;

	for(i=1;i<grid-1;i++) for(j=1;j<grid-1;j++) force[i][j]=0.0;


	for(i=1;i<(grid+1)/2;i++)
	for(j=1;j<(grid+1)/2;j++) {

	    d=posit[i][j]-posit[i][j-1];
	    force[i][j] -= d;
	    force[i][j-1] += d;

	    d=posit[i][j]-posit[i-1][j];
	    force[i][j] -= d;
	    force[i-1][j] += d;

	    d=posit[i][j]-posit[i-1][j-1];
	    force[i][j] -= d ;
	    force[i-1][j-1] += d;
	}

	for(i=(grid+1)/2;i<grid;i++)
	for(j=(grid+1)/2;j<grid;j++) {

	    d=posit[i][j]-posit[i][j-1];
	    force[i][j] -= d;
	    force[i][j-1] += d;

	    d=posit[i][j]-posit[i-1][j];
	    force[i][j] -= d;
	    force[i-1][j] += d;

	    d=posit[i][j]-posit[i-1][j-1];
	    force[i][j] -= d ;
	    force[i-1][j-1] += d;
	}

	for(i=(grid+1)/2;i<grid;i++)
	for(j=i-(grid+1)/2+1;j<(grid+1)/2;j++) {

	    d=posit[i][j]-posit[i][j-1];
	    force[i][j] -= d;
	    force[i][j-1] += d;

	    d=posit[i][j]-posit[i-1][j];
	    force[i][j] -= d;
	    force[i-1][j] += d;

	    d=posit[i][j]-posit[i-1][j-1];
	    force[i][j] -= d ;
	    force[i-1][j-1] += d;
	}

	for(i=1;i<(grid+1)/2;i++)
	for(j=(grid+1)/2;j<i+(grid+1)/2;j++) {

	    d=posit[i][j]-posit[i][j-1];
	    force[i][j] -= d;
	    force[i][j-1] += d;

	    d=posit[i][j]-posit[i-1][j];
	    force[i][j] -= d;
	    force[i-1][j] += d;

	    d=posit[i][j]-posit[i-1][j-1];
	    force[i][j] -= d ;
	    force[i-1][j-1] += d;	    	

	}
}


getvelocity()
{
	register int i,j;
	register float d;

	for(i=1;i<(grid+1)/2;i++)
	for(j=1;j<(grid+1)/2;j++)
	    veloc[i][j]+=force[i][j] * dt;

	for(i=(grid+1)/2;i<grid-1;i++)
	for(j=(grid+1)/2;j<grid-1;j++)
	    veloc[i][j]+=force[i][j] * dt;

	for(i=(grid+1)/2;i<grid-1;i++)
	for(j=i-(grid+1)/2+2;j<(grid+1)/2;j++)
	    veloc[i][j]+=force[i][j] * dt;

	for(i=2;i<(grid+1)/2;i++)
	for(j=(grid+1)/2;j<i+(grid+1)/2-1;j++)
	    veloc[i][j]+=force[i][j] * dt;
	    
}

getposition()
{
	register int i,j;
	register float d;

	for(i=1;i<(grid+1)/2;i++)
	for(j=1;j<(grid+1)/2;j++)
		posit[i][j]+=veloc[i][j];

	for(i=(grid+1)/2;i<grid-1;i++)
	for(j=(grid+1)/2;j<grid-1;j++)
		posit[i][j]+=veloc[i][j];

	for(i=(grid+1)/2;i<grid-1;i++)
	for(j=i-(grid+1)/2+2;j<(grid+1)/2;j++)
		posit[i][j]+=veloc[i][j];

	for(i=2;i<(grid+1)/2;i++)
	for(j=(grid+1)/2;j<i+(grid+1)/2-1;j++)
		posit[i][j]+=veloc[i][j];
}


getvertvec()
{
	register int i,j;
	register float d;

	for(i=0;i<grid;i++) for(j=0;j<grid;j++) {
	    vertvec[i][j][X] = 0.0;
	    vertvec[i][j][Y] = 0.0;
	    vertvec[i][j][Z] = 0.0;
	    colur[i][j] = 0.0;
	}

	for(i=1;i<(grid+1)/2;i++)
	for(j=1;j<(grid+1)/2;j++) {

	    do_vertvec(i, j);
	}

	for(i=(grid+1)/2;i<grid;i++)
	for(j=(grid+1)/2;j<grid;j++) {
	    do_vertvec(i, j);

	}

	for(i=(grid+1)/2;i<grid;i++)
	for(j=i-(grid+1)/2+1;j<(grid+1)/2;j++) {
	    do_vertvec(i, j);

	}

	for(i=1;i<(grid+1)/2;i++)
	for(j=(grid+1)/2;j<i+(grid+1)/2;j++) {
	    do_vertvec(i, j);
	}
}


doscreen()
{

	register int i,j;

	rotate(-450, 'z');
	scale(1.732051, 1.0, 1.0);
	rotate(450, 'z');

	for(i=1;i<(grid+1)/2;i++)
	for(j=1;j<(grid+1)/2;j++)
	{
		move( (Coord) i, (Coord) j-1, (Coord) posit[i][j-1]);
		draw( (Coord) i, (Coord) j, (Coord) posit[i][j]);
		draw( (Coord) i-1, (Coord) j, (Coord) posit[i-1][j]);
		move( (Coord) i, (Coord) j, (Coord) posit[i][j]);
		draw( (Coord) i-1, (Coord) j-1, (Coord) posit[i-1][j-1]);
	}

	for(i=(grid+1)/2;i<grid;i++)
	for(j=(grid+1)/2;j<grid;j++) {
		move( (Coord) i, (Coord) j-1, (Coord) posit[i][j-1]);
		draw( (Coord) i, (Coord) j, (Coord) posit[i][j]);
		draw( (Coord) i-1, (Coord) j, (Coord) posit[i-1][j]);
		move( (Coord) i, (Coord) j, (Coord) posit[i][j]);
		draw( (Coord) i-1, (Coord) j-1, (Coord) posit[i-1][j-1]);
	}

	for(i=(grid+1)/2;i<grid-1;i++)
	for(j=i-(grid+1)/2+2;j<(grid+1)/2;j++) {
		move( (Coord) i, (Coord) j-1, (Coord) posit[i][j-1]);
		draw( (Coord) i, (Coord) j, (Coord) posit[i][j]);
		draw( (Coord) i-1, (Coord) j, (Coord) posit[i-1][j]);
		move( (Coord) i, (Coord) j, (Coord) posit[i][j]);
		draw( (Coord) i-1, (Coord) j-1, (Coord) posit[i-1][j-1]);
	}

	for(i=2;i<(grid+1)/2;i++)
	for(j=(grid+1)/2;j<i+(grid+1)/2-1;j++) {
		move( (Coord) i, (Coord) j-1, (Coord) posit[i][j-1]);
		draw( (Coord) i, (Coord) j, (Coord) posit[i][j]);
		draw( (Coord) i-1, (Coord) j, (Coord) posit[i-1][j]);
		move( (Coord) i, (Coord) j, (Coord) posit[i][j]);
		draw( (Coord) i-1, (Coord) j-1, (Coord) posit[i-1][j-1]);
	}

	for(i=(grid+1)/2-1;i<grid-1;i++) {
	    move( (Coord) i, (Coord) i-(grid+1)/2+2, (Coord) posit[i][i-(grid+1)/2+2]);
	    draw( (Coord) (i+1), (Coord) (i-(grid+1)/2+2), 0.0);
	}
	
	for(i=1;i<(grid+1)/2;i++) {
	    move( (Coord) i, (Coord) (i+(grid+1)/2-2), (Coord)posit[i][i+(grid+1)/2-2]);
	    draw( (Coord) i, (Coord) (i+(grid+1)/2-1), 0.0);
	}
	

	move((float)((grid+1)/2-1), (float)(grid-1), 0.0);
	draw(0.0, (float)((grid+1)/2-1), 0.0);
	draw(0.0, 0.0, 0.0);
	draw((float)((grid+1)/2-1), 0.0, 0.0);
	draw((float)(grid-1), (float)((grid+1)/2-1), 0.0);

	if (smode) select_point();
    
	swapbuffers();
	if (antialias && (dmode!=TOPVIEW)) {
	    czclear(0, 0);
	    if (smode) color(MYRED); else color(MYCYAN);
	} else {
	    color(BLACK); clear(); zclear();
	    if (smode) color(RED); else color(CYAN);
	}

}


facet_shade() {
    int i, j, c;
    Coord triangle[3][3];

    rotate(-450, 'z');
    scale(1.732051, 1.0, 1.0);
    rotate(450, 'z');

    for (j=grid-1;j>(grid+1)/2-1;j--) {

        for (i=(j-((grid+1)/2-1));i<grid-1;i++) {
	    triangle[0][0] = (Coord) (i+1);
	    triangle[0][1] = (Coord) j;
	    triangle[0][2] = (Coord) posit[i+1][j];

	    triangle[1][0] = (Coord) i;
	    triangle[1][1] = (Coord) j;
	    triangle[1][2] = (Coord) posit[i][j];

	    triangle[2][0] = (Coord) i;
	    triangle[2][1] = (Coord) (j-1);
	    triangle[2][2] = (Coord) posit[i][j-1];

	    color(c=getpolycolor(triangle));
	    polf(3, triangle);
        }

	for (i=(j-((grid+1)/2-1));i<grid;i++) {

	    triangle[0][0] = (Coord) i;
	    triangle[0][1] = (Coord) j;
	    triangle[0][2] = (Coord) posit[i][j];

	    triangle[1][0] = (Coord) (i-1);
	    triangle[1][1] = (Coord) (j-1);
	    triangle[1][2] = (Coord) posit[i-1][j-1];

	    triangle[2][0] = (Coord) i;
	    triangle[2][1] = (Coord) (j-1);
	    triangle[2][2] = (Coord) posit[i][j-1];

	    color(getpolycolor2(triangle));
	    polf(3, triangle);
	}
    }

    for (j=(grid+1)/2-1;j>0;j--) {

        for (i=0;i<((grid+1)/2-1+j);i++) {


	    triangle[0][0] = (Coord) (i+1);
	    triangle[0][1] = (Coord) j;
	    triangle[0][2] = (Coord) posit[i+1][j];

	    triangle[1][0] = (Coord) i;
	    triangle[1][1] = (Coord) j;
	    triangle[1][2] = (Coord) posit[i][j];

	    triangle[2][0] = (Coord) i;
	    triangle[2][1] = (Coord) (j-1);
	    triangle[2][2] = (Coord) posit[i][j-1];

	    color(getpolycolor(triangle));
	    polf(3, triangle);
        }

	for (i=1;i<((grid+1)/2-1+j);i++) {

	    triangle[0][0] = (Coord) i;
	    triangle[0][1] = (Coord) j;
	    triangle[0][2] = (Coord) posit[i][j];

	    triangle[1][0] = (Coord) (i-1);
	    triangle[1][1] = (Coord) (j-1);
	    triangle[1][2] = (Coord) posit[i-1][j-1];

	    triangle[2][0] = (Coord) i;
	    triangle[2][1] = (Coord) (j-1);
	    triangle[2][2] = (Coord) posit[i][j-1];

	    color(getpolycolor2(triangle));
	    polf(3, triangle);
	}
    }
    swapbuffers();
    color(BLACK); clear();
    zclear();
}


gouraud_shade() {
    int i, j;
    Coord triangle[3][3];
    float c, r;

    getvertvec();

    for(i=0;i<grid;i++)	for(j=0;j<grid;j++) {

	r = sqrt(vertvec[i][j][X] * vertvec[i][j][X] +
		 vertvec[i][j][Y] * vertvec[i][j][Y] +
		 vertvec[i][j][Z] * vertvec[i][j][Z]);

        vertvec[i][j][X] /= r;
        vertvec[i][j][Y] /= r;
        vertvec[i][j][Z] /= r;

	c = dot(vertvec[i][j], light);
	if (c<0.0) c=0.0;

	c=(((float)(NRAMPE))-((float)(NRAMPE))) * c + ((float)(NRAMPE));

	colur[i][j] = c;

    }

    rotate(-450, 'z');
    scale(1.732051, 1.0, 1.0);
    rotate(450, 'z');


    for (j=grid-1;j>(grid+1)/2-1;j--) {

        for (i=(j-((grid+1)/2-1));i<grid-1;i++) {

	    color(colur[i+1][j]);
	    pmv( (Coord) (i+1), (Coord) j, posit[i+1][j]);

	    color(colur[i][j]);
	    pdr( (Coord) i, (Coord) j, posit[i][j]);

	    color(colur[i][j-1]);
	    pdr( (Coord) i, (Coord) (j-1), posit[i][j-1]);

	    pclos();
        }

	for (i=(j-((grid+1)/2-1));i<grid;i++) {

	    color(colur[i][j]);
	    pmv( (Coord) i, (Coord) j, posit[i][j]);

	    color(colur[i-1][j-1]);
	    pdr( (Coord) (i-1), (Coord) (j-1), posit[i-1][j-1]);

	    color(colur[i][j-1]);
	    pdr( (Coord) i, (Coord) (j-1), posit[i][j-1]);

	    pclos();
	}
    }

    for (j=(grid+1)/2-1;j>0;j--) {

        for (i=0;i<((grid+1)/2-1+j);i++) {

	    color(colur[i+1][j]);
	    pmv( (Coord) (i+1), (Coord) j, posit[i+1][j]);

	    color(colur[i][j]);
	    pdr( (Coord) i, (Coord) j, posit[i][j]);

	    color(colur[i][j-1]);
	    pdr( (Coord) i, (Coord) (j-1), posit[i][j-1]);

	    pclos();
        }

	for (i=1;i<((grid+1)/2-1+j);i++) {

	    color(colur[i][j]);
	    pmv( (Coord) i, (Coord) j, posit[i][j]);

	    color(colur[i-1][j-1]);
	    pdr( (Coord) (i-1), (Coord) (j-1), posit[i-1][j-1]);

	    color(colur[i][j-1]);
	    pdr( (Coord) i, (Coord) (j-1), posit[i][j-1]);

	    pclos();
	}
    }

    swapbuffers();
    color(BLACK); clear();
    zclear();
}


spin_scene()
{
	if (!attached) return;

	if (getbutton(UPARROWKEY)) {
		sdepth-=0.1;
		return;
	}
	if (getbutton(DOWNARROWKEY)) {
		sdepth+=0.1;
		return;
	}
	if (spin) {
	    dtheta = nmy-getvaluator(MOUSEY);
	    dphi = getvaluator(MOUSEX) - nmx;
	}
}


fixwindow() {

	getsize(&xsize, &ysize);
	getorigin(&xorig, &yorig);
	aspect = (float)xsize/(float)ysize;
}

select_point()
{
    int mx, my;

    mx = getvaluator(MOUSEX);
    my = getvaluator(MOUSEY);

    if (!editing) {
	x=(mx-xorig) * (grid-2) / xsize + 1;
	y=(my-yorig) * (grid-2) / ysize + 1;

	if((x-y)>(grid+2)/2-2) x -= (x-y)-(grid+2)/2+2;
	if((y-x)>(grid+2)/2-2) y -= (y-x)-(grid+2)/2+2;
		    
    } else {
	posit[x][y]= 0.006*(float)((my-yorig+2) * grid / ysize - grid/2);
    }

    if ((mx>xorig) && (mx-xorig<xsize) &&
	(my>yorig) && (my-yorig<ysize)) {

	depthcue(FALSE);
	if (antialias) color(MYGREEN);
	else color(GREEN);
	move((Coord)(x+1), (Coord)y, (Coord) posit[x+1][y]);
	draw((Coord)x, (Coord)y, (Coord) posit[x][y]);
	draw((Coord)(x-1), (Coord)y, (Coord) posit[x-1][y]);
	move((Coord)x, (Coord)(y-1), (Coord) posit[x][y-1]);
	draw((Coord)x, (Coord)y, (Coord) posit[x][y]);
	draw((Coord)x, (Coord)(y+1), (Coord) posit[x][y+1]);
	move((Coord)(x-1), (Coord)(y-1), (Coord)posit[x-1][y-1]);
	draw((Coord)x, (Coord)y, (Coord) posit[x][y]);
	draw((Coord)(x+1), (Coord)(y+1), (Coord)posit[x+1][y+1]);
    }

    if((dmode==DEPTHCUED)||(dmode==TOPVIEW)) depthcue(TRUE);
	    
}



int getpolycolor(pts)
float pts[][3];
{
    float norm[3]; 
    float v1[3],v2[3], constant;
    int i,get;
    float c;

    for (i = 0; i < 3; i++) norm[i] = 0.0;
    i = 0;
    get = 1;
    i = 1;
/*    v1[0] = pts[1][0] - pts[0][0];
    v1[1] = pts[1][1] - pts[0][1];
    v1[2] = pts[1][2] - pts[0][2];
*/

    v1[0] = -0.965926;
    v1[1] = 0.258819;
    v1[2] = (pts[1][2] - pts[0][2]) * 200.0;

/*
        v2[0] = pts[2][0] - pts[0][0];
        v2[1] = pts[2][1] - pts[0][1];
        v2[2] = pts[2][2] - pts[0][2];
*/
	v2[0] = -0.707107;
	v2[1] = -0.707107;
	v2[2] = (pts[2][2] - pts[0][2]) * 200.0;

        norm[0] = v1[1] * v2[2] - v1[2] * v2[1];
        norm[1] = v1[2] * v2[0] - v1[0] * v2[2];
        norm[2] = v1[0] * v2[1] - v1[1] * v2[0];

    constant = sqrt((norm[0] * norm[0]) +
     (norm[1] * norm[1]) + (norm[2] * norm[2]));
    norm[0] /= constant;
    norm[1] /= constant;
    norm[2] /= constant;

    c = dot(norm,light);
    if (c<0.0) c=0.0;

    c = (((float)(NRAMPE)) - ((float)(NRAMPE))) * c + (((float)(NRAMPE)));

    return((int)c);
}


int getpolycolor2(pts)
float pts[][3];
{
    float norm[3];
    float v1[3],v2[3], constant;
    int i,get;
    float c;

    for (i = 0; i < 3; i++) norm[i] = 0.0;
    i = 0;
    get = 1;
    i = 1;
/*    v1[0] = pts[1][0] - pts[0][0];
    v1[1] = pts[1][1] - pts[0][1];
    v1[2] = pts[1][2] - pts[0][2];
*/

    v1[0] = -0.707107;
    v1[1] = -0.707107;
    v1[2] = (pts[1][2] - pts[0][2]) * 200.0;

/*
        v2[0] = pts[2][0] - pts[0][0];
        v2[1] = pts[2][1] - pts[0][1];
        v2[2] = pts[2][2] - pts[0][2];
*/
	v2[0] = 0.258819;
	v2[1] = -0.965926;
	v2[2] = (pts[2][2] - pts[0][2]) * 200.0;

        norm[0] = v1[1] * v2[2] - v1[2] * v2[1];
        norm[1] = v1[2] * v2[0] - v1[0] * v2[2];
        norm[2] = v1[0] * v2[1] - v1[1] * v2[0];

    constant = sqrt((norm[0] * norm[0]) +
		    (norm[1] * norm[1]) +
		    (norm[2] * norm[2]));
    norm[0] /= constant;
    norm[1] /= constant;
    norm[2] /= constant;

    c = dot(norm,light);
    if (c<0.0) c=0.0;

    c = (((float)(NRAMPE))-((float)(NRAMPE))) * c + ((float)(NRAMPE));

    return(c);
}

float dot(vec1,vec2)
float vec1[3],vec2[3];
{
	float xx;
	xx = (vec1[1] * vec2[1])
	   + (vec1[2] * vec2[2])
	   + (vec1[0] * vec2[0]);
	return((float) xx);
}

getlightvector() {
	float f;
	light[2]= cos(theta);
	f = sin(theta);
	light[1] = -sin(phi) * f;
	light[0] = -cos(phi) * f;
}

makerange(a,b,r1,r2,g1,g2,b1,b2)
int a,b;
int r1,r2,g1,g2,b1,b2;
{
	float i;
	int j;
	float dr,dg,db;

	i = (float)(b-a);
	dr = (float)(r2-r1)/i;
	dg = (float)(g2-g1)/i;
	db = (float)(b2-b1)/i;

	for (j=0;j<=(int)i;j++)
		mapcolor((Colorindex)j+a,
			 (RGBvalue) (dr * (float)j + r1),
			 (RGBvalue) (dg * (float)j + g1),
			 (RGBvalue) (db * (float)j + b1));
}


save_colors() {

	Colorindex i;

	for (i=0; i<1024; i++)
	   getmcolor(i, &oldcolors[i][0], &oldcolors[i][1], &oldcolors[i][2]);
}

restore_colors() {

	Colorindex i;

	for (i=0; i<1024; i++)
	   mapcolor(i, oldcolors[i][0], oldcolors[i][1], oldcolors[i][2]);
}



do_vertvec(i, j)
int i, j;
{
    float d;

    d=posit[i][j]-posit[i][j-1];
    vertvec[i][j][Z] += 1.0/200.0;
    vertvec[i][j][X] += d * 0.2558819;
    vertvec[i][j][Y] += d * -0.965926;
    vertvec[i][j-1][Z] += 1.0/200.0;
    vertvec[i][j-1][X] += d * 0.2558819;
    vertvec[i][j-1][Y] += d * -0.965926;

    d=posit[i][j]-posit[i-1][j];
    vertvec[i][j][Z] += 1.0/200.0;
    vertvec[i][j][X] += d * -0.9659258;
    vertvec[i][j][Y] += d * 0.258819;
    vertvec[i-1][j][Z] += 1.0/200.0;
    vertvec[i-1][j][X] += d * -0.9659258;
    vertvec[i-1][j][Y] += d * 0.258819;

    d=posit[i][j]-posit[i-1][j-1];
    vertvec[i][j][Z] += 1.0/200.0;
    vertvec[i][j][X] += d * -0.70710678;
    vertvec[i][j][Y] += d * -0.70710678;
    vertvec[i-1][j-1][Z] += 1.0/200.0;
    vertvec[i-1][j-1][X] += d * -0.70710678;
    vertvec[i-1][j-1][Y] += d * -0.70710678;    
}


viewit() {
    perspective(640, aspect, near, far);
    translate(0.0,0.0,-sdepth);
    rotate(-stheta-dtheta,'x');
    rotate(sphi+dphi,'z');
    translate(-(float)((grid+1)/2-1), -(float)((grid+1)/2-1), 0.0);
    scale(1.0, 1.0, 200.0);
}
