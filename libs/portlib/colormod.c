/*
 *	colormod -
 *		Define some transforms between different color models.
 *
 *
 *		   Henry Moreton and Paul Haeberli - 1984
 */
#include "math.h"
#include "stdio.h"
#include "port.h"

#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))

int rgb_to_rgb();

static int (*tofunc)() = rgb_to_rgb;
static int (*fromfunc)() = rgb_to_rgb;
static int colorsys = COLORSYS_RGB;

/*
 *	Convert FROM various formats TO rgb.
 *
 *
 */
irgb_to_rgb( ir, ig, ib, r, g, b)
int ir, ig, ib;
float *r, *g, *b;
{
    *r = ir / 255.0;
    *g = ig / 255.0;
    *b = ib / 255.0;
}

cmy_to_rgb ( c, m, y, r, g, b)
float c, m, y;
float *r, *g, *b;
{
    *r = 1.0 - c;
    *g = 1.0 - m;
    *b = 1.0 - y;
}

static float value(n1, n2, hue)
float n1, n2, hue;
{
    if (hue > 360)
	hue -= 360;
    if (hue < 0)
	hue += 360;
    if (hue < 60)
	return(n1 + (n2 - n1)*(hue/60.0));
    if (hue < 180)
	return(n2);
    if (hue < 240)
	return(n1 + (n2 - n1)*((240 - hue)/60.0));
    return(n1);
}

hls_to_rgb (h, l, s, r, g, b)
float	h, l, s;
float	*r, *g, *b;
{
    float	m1, m2;

    h *= 360.0;
    if (l <= 0.5)
	m2 = l * (1 + s);
    else
	m2 = l + s - l*s;
    m1 = 2*l - m2;
    if (s == 0)
	*r = *g = *b = l;
    else {
	*r = value(m1, m2, h + 120.0);
	*g = value(m1, m2, h);
	*b = value(m1, m2, h - 120.0);
    }
}

hsv_to_rgb( h, s, v, r, g, b)
float	h, s, v;
float	*r, *g, *b;
{
    int 	i;
    float	f, p, q, t;

    h *= 360.0;
    if (s == 0) {
	*r = v;
	*g = v;
	*b = v;
    } else {
	if (h == 360) 
	    h = 0;
	h /= 60;
	i = (int) floor(h);
	f = h - i;
	p = v*(1 - s);
	q = v*(1 - (s*f));
	t = v*(1 - (s*(1 - f)));
	switch (i) {
	    case 0 : 
		*r = v;
		*g = t;
		*b = p;
		break;
	    case 1 : 
		*r = q;
		*g = v;
		*b = p;
		break;
	    case 2 : 
		*r = p;
		*g = v;
		*b = t;
		break;
	    case 3 : 
		*r = p;
		*g = q;
		*b = v;
		break;
	    case 4 : 
		*r = t;
		*g = p;
		*b = v;
		break;
	    case 5 : 
		*r = v;
		*g = p;
		*b = q;
		break;
	}
    }
}

yiq_to_rgb (y, i, q, r, g, b)
float	y, i, q;
float	*r, *g, *b;
{
/*
    i = (i * 1.2) - 0.6;
    q = (q * 1.04) - 0.52;
    */
    *r = 1.0 * y + 0.948262 * i + 0.624013 * q;
    *g = 1.0 * y + -0.276066 * i + -0.63981 * q;
    *b = 1.0 * y + -1.10545 * i + 1.72986 * q;

}

/*
 *	Convert FROM rgb TO rgb.
 *
 *
 */
rgb_to_rgb( fr, fg, fb, tr, tg, tb)
float fr, fg, fb;
float *tr, *tg, *tb;
{
    *tr = fr;
    *tg = fg;
    *tb = fb;
}

/*
 *	Convert TO various formats FROM rgb.
 *
 *
 */
rgb_to_cmy( r, g, b, c, m, y)
float r, g, b;
float *c, *m, *y;
{
    *c = 1.0 - r;
    *m = 1.0 - g;
    *y = 1.0 - b;
}

rgb_to_irgb( r, g, b, ir, ig, ib)
float r, g, b;
int *ir, *ig, *ib;
{
    *ir = (int) (r * 255.0);
    *ig = (int) (g * 255.0);
    *ib = (int) (b * 255.0);
}

rgb_to_hls( r, g, b, h, l, s)
float r, g, b;
float *h, *l, *s;
{
    float rc, gc, bc;
    float maxcol, mincol;

    maxcol = max( r, max( g, b));
    mincol = min( r, min( g, b));
    *l = (mincol + maxcol) / 2;		/* lightness */
    if (maxcol == mincol) {		/* achromatic case */
	*s = 0;		/* *h is undefined in the achromatic case */
	*h = 0;
    } else {
	if (*l <= 0.5)
	    *s = (maxcol - mincol) / (maxcol + mincol);
	else
	    *s = (maxcol - mincol) / (2 - maxcol - mincol);
	
	/* find hue */
	rc = (maxcol - r) / (maxcol - mincol);
	gc = (maxcol - g) / (maxcol - mincol);
	bc = (maxcol - b) / (maxcol - mincol);
	if (r == maxcol)
	    *h = bc - gc;
	else if (g == maxcol)
	    *h = 2 + rc - bc;
	else 
	    *h = 4 + gc - rc;
	
	*h *= 60.0;
	if ( *h < 0.0)
	    *h += 360.0;
	*h /= 360.0;
    }
}

rgb_to_hsv (r, g, b, lh, ls, lv)
float r, g, b;
float *lh, *ls, *lv;
{
    float h, s, v;
    float cmax, cmin;
    float rc, gc, bc;

    /* find the cmax and cmin of r g b */
    cmax = r; cmin = r;
    cmax = (g > cmax ? g : cmax);
    cmin = (g < cmin ? g : cmin);
    cmax = (b > cmax ? b : cmax);
    cmin = (b < cmin ? b : cmin);
    v = cmax;		/* value */
    if (cmax != 0)
	s = (cmax - cmin) / cmax;
    else {
	s = 0;
	h = 0;
    }

    if (s == 0)
	h = -1;
    else {
	rc = (cmax - r)/(cmax - cmin);
	gc = (cmax - g)/(cmax - cmin);
	bc = (cmax - b)/(cmax - cmin);
	if (r == cmax)
	    h = bc - gc;
	else
	    if (g == cmax)
		h = 2.0 + rc - bc;
	    else
		h = 4.0 + gc - rc;
	h = h * 60.0;
	if (h < 0.0)
	    h += 360.0;
    }
    *ls = s;
    *lh = h/360.0;
    *lv = v;
}

rgb_to_yiq (r, g, b, y, i, q)
float	r, g, b;
float	*y, *i, *q;
{
    *y = (0.3 * r + 0.59 * g + 0.11 * b);
    *i = ((0.6 * r + -0.28 * g + -0.32 * b));
    *q = ((0.21 * r + -0.52 * g + 0.31 * b));
}

setcolorsys(sys)
{
    switch(sys) {
	case COLORSYS_RGB: tofunc = rgb_to_rgb;
		  fromfunc = rgb_to_rgb;
		  colorsys = sys;
		  break;
	case COLORSYS_CMY: tofunc = cmy_to_rgb;
		  fromfunc = rgb_to_cmy;
		  colorsys = sys;
		  break;
	case COLORSYS_HSV: tofunc = hsv_to_rgb;
		  fromfunc = rgb_to_hsv;
		  colorsys = sys;
		  break;
	case COLORSYS_HLS: tofunc = hls_to_rgb;
		  fromfunc = rgb_to_hls;
		  colorsys = sys;
		  break;
	case COLORSYS_YIQ: tofunc = yiq_to_rgb;
		  fromfunc = rgb_to_yiq;
		  colorsys = sys;
		  break;
 	default:  fprintf(stderr,"bad color system no %d\n",sys);
		  break;
    }
}

getcolorsys(sys)
{
    return colorsys;
}

torgb(r,g,b,tr,tg,tb)
float r, g, b;
float *tr, *tg, *tb;
{
    tofunc(r,g,b,tr,tg,tb);
}

fromrgb(r,g,b,tr,tg,tb)
float r, g, b;
float *tr, *tg, *tb;
{
    fromfunc(r,g,b,tr,tg,tb);
}

