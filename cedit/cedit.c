/*
 *	cedit - 
 *		A simple color editor. Use the left mouse button to 
 *		pick the color on the screen to edit, then move the
 *		sliders to change the color.
 *
 *				Paul Haeberli - 1984
 *
 */
#include "gl.h"
#include "device.h"
#include "port.h"
#include "stdio.h"

float or = -1.0;
float og = -1.0;
float ob = -1.0;
int cc = -1;
float cr, cg, cb;
int m1, m2, m3;
int xorg, yorg;
int x, y;
int xsize, ysize;
float wx, wy;
int menu;

main(argc,argv)
int argc;
char **argv;
{
    int i, j;

    if (argc>1)
	setcolorsys(atoi(argv[1]));
    keepaspect(1,1);
    winopen("cedit");
    menu = defpup("colorsys %t|rgb|cmy|hsv|hls");
    initmouse();
    cc = 16;
    makeframe();
    while (1) {
	checkmouse();
	if (m3) {
	    x = getvaluator(MOUSEX);
	    y = getvaluator(MOUSEY);
	    wx = 10.0*(x-xorg)/xsize;
	    wy = 10.0*(y-yorg)/ysize;
	    if (wy>0.0 && wy<10.0) {
		if (wx>1.0 && wx<2.0) {
		     cr = (wy-2.0)/7.0;
		     drawsliders(cc,cr,cg,cb);
		} else if (wx>3.0 && wx<4.0) {
		     cg = (wy-2.0)/7.0;
		     drawsliders(cc,cr,cg,cb);
		} else if (wx>5.0 && wx<6.0) {
		     cb = (wy-2.0)/7.0;
		     drawsliders(cc,cr,cg,cb);
		}
	    } 
	}
    }
}

newcolor(c)
int c;
{
    cc = c;
    color(c);
    rectf(7.0,2.0,9.0,9.0);
    color(GREY(0));
    rect(7.0,2.0,9.0,9.0);
    modgetmcolor(c,&cr,&cg,&cb);
    or = og = ob = -1.0;
    drawback();
    drawsliders(cc,cr,cg,cb);
}

drawsliders(c,r,g,b)
int c;
float r, g, b;
{
    int changed;

    changed = 0;
    if (r<0.0) r = 0.0;
    if (r>1.0) r = 1.0;
    if (r != or) {
	 drawknob(0.0,or,r,RED);
         or = r;
	 changed++;
    }
    if (g<0.0) g = 0.0;
    if (g>1.0) g = 1.0;
    if (g != og) {
	 drawknob(2.0,og,g,GREEN);
         og = g;
	 changed++;
    }
    if (b<0.0) b = 0.0;
    if (b>1.0) b = 1.0;
    if (b != ob) {
	 drawknob(4.0,ob,b,BLUE);
         ob = b;
	 changed++;
    }
    if (changed) 
	modmapcolor(c,r,g,b);
}

drawknob(x,old,new,c)
float x, old, new;
int c;
{
     pushmatrix();
	 translate(x,2.0+(7.0*old),0.0);
	 color(GREY(15));
	 rectf(1.2,-0.10,1.8,0.10);	
     popmatrix();
     pushmatrix();
	 translate(x,2.0+(7.0*new),0.0);
	 color(c);
	 rectf(1.2,-0.10,1.8,0.10);	
     popmatrix();
}

makeback(x)
float x;
{
    pushmatrix();
	translate(x,0.0,0.0);
	color(GREY(15));
	rectf(1.0,1.6,2.0,9.4);
	color(GREY(0));
	rect(1.0,1.6,2.0,9.4);
    popmatrix();
}

drawback()
{
    makeback(0.0);
    makeback(2.0);
    makeback(4.0);
}

initmouse()
{
    qdevice(MENUBUTTON);
    qdevice(MIDDLEMOUSE);
    qdevice(LEFTMOUSE);
}

checkmouse()
{
    short dev, val;
    int sel;

    while (1) {
	if (m1 != 0 || m2 != 0 || m3 != 0) {
	    if (!qtest()) 
		return;
	} 
	dev = qread(&val);
	switch (dev) {
		case MENUBUTTON: 
			sel = dopup(menu);	
			if (sel>0) {
			    setcolorsys(sel);
			    newcolor(cc);
			}
			break;
		case MIDDLEMOUSE: 
			m2 = val;
			if (m2 == 0) {
			    x = getvaluator(MOUSEX);
			    y = getvaluator(MOUSEY);
			    wx = 10.0*(x-xorg)/xsize;
			    wy = 10.0*(y-yorg)/ysize;
			    if (wx<-0.5 || wx>10.5 || wy<-0.5 || wy>10.5)
				modmapcolor(getapixel(x,y),cr,cg,cb);
			}
			break;
		case LEFTMOUSE: 
			m3 = val;
			if (m3 == 0) {
			    x = getvaluator(MOUSEX);
			    y = getvaluator(MOUSEY);
			    wx = 10.0*(x-xorg)/xsize;
			    wy = 10.0*(y-yorg)/ysize;
			    if (wx<-0.5 || wx>10.5 || wy<-0.5 || wy>10.5)
				newcolor(getapixel(x,y));
			}
			break;
		case REDRAW: 
			makeframe();
			break;
	}
    }
}

makeframe()
{
    reshapeviewport();
    getorigin(&xorg,&yorg);
    getsize(&xsize,&ysize);
    color(GREY(14));
    clear();
    ortho2(0.0,10.0,0.0,10.0);
    color(0);
    color(GREY(0));
    newcolor(cc);
}

modmapcolor(c,r,g,b)
int c;
float r, g, b;
{
    float fr, fg, fb;
    int ir, ig, ib;

    torgb(r,g,b,&fr,&fg,&fb);
    rgb_to_irgb(fr,fg,fb,&ir,&ig,&ib);
    gammapcolor(c,ir,ig,ib);
}

modgetmcolor(c,r,g,b)
int c;
float *r, *g, *b;
{
    unsigned short cr, cg, cb;
    float fr, fg, fb;

    gamgetmcolor(c,&cr,&cg,&cb);
    irgb_to_rgb(cr,cg,cb,&fr,&fg,&fb);
    fromrgb(fr,fg,fb,r,g,b);
}
