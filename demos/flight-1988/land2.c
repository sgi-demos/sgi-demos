/**************************************************************************
 *									  *
 *  Copyright (C)  1988 Silicon Graphics, Inc.	  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/* contains world definitions	*/
#include "flight.h"

#define max_int 500000
make_world ()
{
    register int x,y;
    Matrix mtn_range2;

    static world[][3] = {
	{max_int,0,max_int},
	{-max_int,0,max_int},
	{-max_int,0,-max_int},
	{max_int,0,-max_int},
    };
    static sky1[][3] = {
	{-max_int,0,-max_int},
	{-max_int,0,max_int},
	{0,max_int,0},
    };
    static sky2[][3] = {
	{max_int,0,-max_int},
	{max_int,0,max_int},
	{0,max_int,0},
    };
    static sky3[][3] = {
	{-max_int,0,-max_int},
	{max_int,0,-max_int},
	{0,max_int,0},
    };
    static sky4[][3] = {
	{-max_int,0,max_int},
	{max_int,0,max_int},
	{0,max_int,0},
    };

#define mtn_dist 200000
#define mtn_left 100000
    static north_mtn_dark0 [][3] = {
	{-mtn_left-20000,0,-mtn_dist},
	{-mtn_left,5000,-mtn_dist},
	{mtn_left,5000,-mtn_dist},
	{mtn_left+20000,0,-mtn_dist},
    };

    static north_mtn_lite1 [][3] = {
	{-mtn_left-15000,0,-mtn_dist-5000},
	{-100000,8500,-mtn_dist-5000},
	{-80000,0,-mtn_dist-5000},
    };

    static north_mtn_lite2 [][3] = {
	{-90000,0,-mtn_dist-5000},
	{-70000,12000,-mtn_dist-5000},
	{-50000,5000,-mtn_dist-5000},
    };

    static north_mtn_lite3 [][3] = {
	{-70000,5000,-mtn_dist-5000},
	{-40000,21000,-mtn_dist-5000},
	{-20000,5000,-mtn_dist-5000},
    };

    static north_mtn_lite4 [][3] = {
	{-30000,5000,-mtn_dist-5000},
	{0,22500,-mtn_dist-5000},
	{50000,5000,-mtn_dist-5000},
    };

    static north_mtn_lite5 [][3] = {
	{12000,10000,-mtn_dist-5000},
	{28000,19000,-mtn_dist-5000},
	{37300,17500,-mtn_dist-5000},
    };

    static north_mtn_lite6 [][3] = {
	{12000,10000,-mtn_dist-5000},
	{50000,22000,-mtn_dist-5000},
	{80000,5000,-mtn_dist-5000},
    };

    static snow_cap2 [][3] = {
	{43700,20000,-mtn_dist-5000},
	{50000,22000,-mtn_dist-5000},
	{53500,20000,-mtn_dist-5000},
    };

    static north_mtn_dark1 [][3] = {
	{-100000,5000,-mtn_dist},
	{-85000,10000,-mtn_dist},
	{-70000,5000,-mtn_dist},
    };

    static north_mtn_dark2 [][3] = {
	{-60000,5000,-mtn_dist},
	{-25000,20000,-mtn_dist},
	{0,5000,-mtn_dist},
    };

    static north_mtn_dark3 [][3] = {
	{-10000,5000,-mtn_dist},
	{5000,17500,-mtn_dist},
	{30000,5000,-mtn_dist},
    };

    static north_mtn_dark4 [][3] = {
	{15000,5000,-mtn_dist},
	{30000,15000,-mtn_dist},
	{50000,10000,-mtn_dist},
    };

    static north_mtn_dark5 [][3] = {
	{15000,5000,-mtn_dist},
	{62000,20000,-mtn_dist},
	{100000,5000,-mtn_dist},
    };

    static snow_cap1 [][3] = {
	{-34333,16000,-mtn_dist},
	{-25000,20000,-mtn_dist},
	{-18444,16000,-mtn_dist},
    };

    makeobj (MTN_RANGE);
	color (purple1);
	polfi (3,north_mtn_lite1);
	polfi (3,north_mtn_lite2);
	polfi (3,north_mtn_lite3);
	polfi (3,north_mtn_lite4);
	polfi (3,north_mtn_lite5);	
	polfi (3,north_mtn_lite6);	
	color (grey0);
	polfi (3, snow_cap2);

	color (purple3);
	polfi (4,north_mtn_dark0);
	polfi (3,north_mtn_dark1);
	polfi (3,north_mtn_dark2);
	polfi (3,north_mtn_dark3);
	polfi (3,north_mtn_dark4);
	polfi (3,north_mtn_dark5);	

	color (grey0);
	polfi (3, snow_cap1);
    closeobj ();

    callobj (PUSH_IDENTITY);
    rotate (2400,'y');		/* rotate around		*/
    scale (-1.7,0.90,1.0);	/* stretch out and shrink down	*/
    getmatrix (mtn_range2);	/* fetch matrix and save	*/
    popmatrix ();

    make_lights ();
    make_vasi ();

    makeobj (SETUP_WORLD);	/* setup world viewport		*/
	if (hud)
	then viewport(0,XMAXSCREEN,0,YMAXSCREEN);
	else viewport(1,XMAXSCREEN-1,YMIDDLE,YMAXSCREEN-1);
    maketag (FOV_EDIT);		/* now load any perspective	*/
	perspective (600,2.0,1.0,1.0e9);
    closeobj ();

    makeobj (WORLD_OBJECT);
	color (green);
	polfi (4,world);

	color (bitplanes >= 6?skyblue:blue);
	polfi (3,sky1);
	polfi (3,sky2);
	polfi (3,sky3);
	polfi (3,sky4);

	if (bitplanes > 4) {
	    callobj (MTN_RANGE);
	    pushmatrix ();
	    multmatrix (mtn_range2);
	    callobj (MTN_RANGE);
	    popmatrix ();
	}

	pushmatrix();
	rotate (-900,'x');		/* z = -y			*/
	color (bitplanes>4?dirt:brown);		/* grid lines	*/
	for (x = -55000; x <= 55000; x += 10000) {
	    move2i(x,-50000);
	    draw2i(x,50000);
	}
	for (x = -50000; x <= 50000; x += 10000) {
	    move2i(-55000,x);
	    draw2i(55000,x);
	}

	genstripe (150,0,210,1000);		/* VASI patches	*/
	rectfs (-20,-3100,20,-1000);		/* dirt		*/
	rectfs (-100,-1000,100,0);		/* over runs	*/
	rectfs (-100,8500,100,9500);

	rectfs (6000,-14000,6020,-14030);	/* threats	*/
	rectfi (-20000,-15000,-20040,-15020);
	rectfi (3000,-34000,3010,-34030);

	color(bitplanes>4?grey9:grey8);
	{
	    static Scoord p23 [][2] = {
		-2300,2500,
		-2250,2500,
		-650,-3300,
		-700,-3300,
	    };
	    static Scoord p24 [][2] = {
		-700,-3250,
		600,-3350,
		600,-3400,
		-700,-3300,
	    };
	    static Scoord p25 [][2] = {
		600,-3400,
		550,-3400,
		1050,1600,
		1100,1600,
	    };
	    polf2s(4,p23);
	    polf2s(4,p24);
	    polf2s(4,p25);
	    rectfs (-2300,2500,-2000,4200);
	    rectfs (1000,1500,1300,2100);
	}
	color (bitplanes>4?grey7:grey8);	/* taxi ways		*/
	rectfs (-700,0,-100,100);
	rectfs (-1200,2000,700,2100);

    {
	static Scoord parray[][2]={
	    -700,3100,
	    -700,3300,
	    -100,4000,
	    -100,3800,
	};
	polf2s(4,parray);
    }
    {
	static Scoord parray[][2]={
	    -700,4700,
	    -700,4900,
	    -100,4200,
	    -100,4000,
	};
	polf2s(4,parray);
    }
	rectfs (-700,5900, -100,6000);		/* roads	*/
	rectfs (-700,8400, -100,8500);
	rectfs (-1200,3100, -800,3300);
	rectfs (-1200,4700, -800,4900);

	color (bitplanes>4?grey6:brown);
	rectfs (-800,0, -700,8500);
	rectfs (-2000,2000, -1200,4900);
	rectfs (700,1600, 1000,2500);

	color (bitplanes>4?grey3:grey2);	/* asphalt		*/
	rectfs (-100,0,100,8500);		/* main runway		*/
    closeobj ();

    makeobj (FAKE_STRIPES);
	color (bitplanes>4?grey1:white);
	genstripe (8,10,63,150);
	rectfi (-1,450,2,8000);
    closeobj ();

    makeobj (RUNWAY_STRIPES);
    {
	static Scoord parray[][2]={		/* tire marks		*/
	    5,400,
	    -7,410,
	    -35,800,
	    -30,1200,
	    -4,2300,
	    1,2350,
	    30,1270,
	    36,720,
	};
	color (bitplanes>4?grey7:grey8);
	polf2s (8,parray);
    }

	color (bitplanes>4?grey1:white);
	for (y = 450; y < 8000; y+=350)		/* center stripes	*/
	    rectfs (-1,y,2,y+150);
	rectfs (72,0,75,8500);			/* long side stripes	*/
	rectfs (-72,0,-75,8500);
	for (x=8; x<=53; x+= 15)		/* 4 big ones		*/
	    genstripe (x,10,x+10,150);
	for (x=38; x<=58; x+= 10)		/* 3 small ones		*/
	    genstripe (x,500,x+5,575);
	genstripe (38,1000,63,1150);		/* 1 big fat one	*/
	genstripe (38,1500,43,1575);
	genstripe (38,1500,43,1575);		/* 2	*/
	genstripe (48,1500,53,1575);
	genstripe (38,2000,43,2075);		/* 2	*/
	genstripe (48,2000,53,2075);
	genstripe (38,2500,43,2575);		/* 1	*/
	genstripe (38,3000,43,3075);		/* 1	*/
    {
	static Scoord parray [][2] = {		/* runway numbers "10	*/
		-20,250,
		-15,260,
		-15,250,
	};
	polf2s (3,parray);			/* "1"	*/
    }
	rectfs (-20,200,-5,210);
	rectfs (-15,210,-10,260);
    {
	static Scoord parray[][2] = {		/* "0"	*/
		5,255,
		10,260,
		25,260,
		30,255,
		30,205,
		25,200,
		10,200,
		5,205,
	};
	polf2s (8,parray);
    }
	color(bitplanes>4?grey3:grey2);
	rectfs (10,210,25,250);		/* inside of "0"	*/
    closeobj ();
}

genstripe (x1,y1,x2,y2)
    Icoord x1,y1,x2,y2;
{
    rectfs (x1,y1,x2,y2);
    rectfs (-x1,y1,-x2,y2);
    rectfs (x1,8500-y1,x2,8500-y2);
    rectfs (-x1,8500-y1,-x2,8500-y2);
}

make_lights()
{
    register int x,y;

    makeobj(LIGHTS);
	/* RANDOM LIGHTS	*/
	color(white);
	for (x=0; x<40; x++) pnt2s (random(2000), random(2000)-6000);
        /* city lights */
	for (x=0; x<30; x++) pnt2i (random(3000),random(3000)+60000);

	/* RIGHT SIDE WHITE LIGHTS ON RUNWAY EDGE */
	for (y= 200;y<=6400;y+=200) pnt2s (80,y);

	/* LEFT SIDE WHITE LIGHTS - NEAR END */
	for (y= -200;y<=3600;y+=200) pnt2s (-80,y);

	/* LEFT SIDE WHITE LIGHTS - FAR END */
	for (y= 4400;y<=6400;y+=200) pnt2s (-80,y);

	/* APPROACH LIGHTS TO RUNWAY */
	for (y= -3000;y<=-100;y+=200)
	for (x= -8;x<=8;x+=4)
	    pnt2s(x,y);

	/* RUNWAY CENTERLINE LIGHTS */
	for (y= 0;y<=8500;y+=100) pnt2s (2,y);

	/* RIGHT AND LEFT SIDE ORANGE LIGHTS */
	color (orange);
	for (y=6600;y<=8500;y+=200) {
	    pnt2s (80,y);
	    pnt2s (-80,y);
	}
        /* city street lights */
	color (orange);
	for (x= -30000; x<0; x+=1500) {
	    pnt2i (x,60000+x);
	    pnt2i (x,60000-x);
	}

	/* NEAR END GREEN LIGHTS */
	color (green0);
	for (x= -90;x<=-50;x+=10) pnt2s (x,0);
	for (x=50;x<=90;x+=10) pnt2s(x,0);

	/* FAR END RED LIGHTS */
	color (red);
	for (x= -90;x<=-50;x+=10) pnt2s (x,8500);
	for (x=50;x<=90;x+=10) pnt2s (x,8500);

        /* city lights */
	for (x=0; x<10; x++) pnt2i (random(1500),random(1500)+60000);
    closeobj();
}

make_vasi_lights ()
{
    register int x;

    for (x=160; x<=200; x+=20) {
	rectfs (x,0,x+3,3);
	rectfs (-x,0,-x-3,3);
    }
}

make_vasi ()
{
    makeobj (VASI1);
	pushmatrix ();
    maketag (0);
	color (white);
	translate (0.0,0.0,-800.0);
	make_vasi_lights ();
    maketag (1);
	color (white);
	translate (0.0,0.0,700.0);
	make_vasi_lights ();
	popmatrix ();
    closeobj ();

    makeobj (VASI2);
	pushmatrix ();
    maketag (0);
	color (white);
	translate (0.0,0.0,-7700.0);
	make_vasi_lights ();
    maketag (1);
	color (white);
	translate (0.0,0.0,-700.0);
	make_vasi_lights ();
	popmatrix ();
    closeobj ();
}

/* draw VASI lights , plane is at pz	*/
draw_vasi (pp)
    register Plane pp;
{
    register Object obj;
    register float temp1,temp2;

    temp1 = temp2 = 0.0;
    if (pp -> z > -4000.0) {
	obj = VASI1;
	if (pp -> z != -1150.0) temp1 = pp -> y/(pp -> z + 1150.0);
	if (pp -> z != -500.0) temp2 = pp -> y/(pp -> z + 500.0);
    }
    else {
	obj = VASI2;
	if (pp -> z != -6850.0) temp1 = pp -> y/(-6850.0 - pp -> z);
	if (pp -> z != -7500.0) temp2 = pp -> y/(-7500.0 - pp -> z);
    }
    editobj (obj);
	objreplace (0);
	color (temp1 < 12.0/200.0 ? red:white);
	objreplace (1);
	color (temp2 < 10.0/200.0 ? red:white);
    closeobj ();
    callobj (obj);
}
