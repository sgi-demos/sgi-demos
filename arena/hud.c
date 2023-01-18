
#include <stdio.h>
#include <gl.h>

#include "arena.h"

Object base_hud, hud_turn, hud_throttle, hud_speed, hud_walls,
       hud_mech, hud_radar;
Matrix hud_matrix;

Icoord turn_poly[4][2] = {{510, 40}, {513, 40}, {513, 60}, {510, 60}};
Icoord speed_poly[4][2] = {{763, 162}, {783, 162}, {783, 165}, {763, 165}};

float radar_zoom = 1.0;


make_hud()
{
    makeobj(base_hud = genobj());
    {
	pushmatrix();

        // Note that here we don't want to use XMAXSCREEN because the reset of the numbers
        // below are calibrated to the old 1024x768 screens. The downside is that the
        // circles look like ellipses. --LK
	/*ortho2(0.0, XMAXSCREEN.0, 0.0, YMAXSCREEN.0);*/
        ortho2(0.0, 1023.0, 0.0, 767.0);

	if ((bitplanes >= 7) && (bitplanes <= 12))
	{
	    writemask(HUD_Y_MASK);

	    color(BLACK);
	    clear();
	}

	color(HUD_YELLOW);

	/*
	 *  radar
	 */
	circi(180, 180, 150);
	move2i(180, 330);
	draw2i(180,  30);
	move2i( 30, 180);
	draw2i(330, 180);

	if (bitplanes >= 7)
	{
	    cmov2i(10, 20);
	    charstr("RADAR X 1.0");

	    /*
	     *  zoom x
	     */
	    cmov2i(10, 740);
	    charstr("ZOOM X 1.0");
	}

	/*
	 *  turn bar
	 */
	move2i(313, 50);
	draw2i(710, 50);
	move2i(312, 60);
	draw2i(312, 40);
	move2i(511, 60);
	draw2i(511, 40);
	move2i(512, 60);
	draw2i(512, 40);
	move2i(711, 60);
	draw2i(711, 40);

	/*
	 *  speed bar
	 */
	move2i(773,  65);
	draw2i(773, 362);
	move2i(763,  64);
	draw2i(783,  64);
	move2i(763, 163);
	draw2i(783, 163);
	move2i(763, 164);
	draw2i(783, 164);
	move2i(763, 363);
	draw2i(783, 363);

	/*
	 *  damage meter
	 */
	move2i(900,  35);
	draw2i(905,  35);
	draw2i(905, 236);
	draw2i(900, 236);
	draw2i(900,  35);
	cmov2i(878, 20);
	charstr("DAMAGE");

	/*
	 *  sights
	 */
	move2i(497, 364);
	draw2i(492, 364);
	draw2i(492, 403);
	draw2i(497, 403);
	move2i(526, 364);
	draw2i(531, 364);
	draw2i(531, 403);
	draw2i(526, 403);

	popmatrix();
	if (bitplanes >= 7)
	    writemask(MASK_HUD);
    }
    closeobj();

    pushmatrix();
    ortho2(0.0, 1023.0, 0.0, 767.0);
    getmatrix(hud_matrix);
    popmatrix();

    makeobj(hud_turn = genobj());
    {
	color(HUD_RED);		/* red turn indicator */
	polf2i(4, turn_poly);
    }
    closeobj();

    makeobj(hud_throttle = genobj());
    {
	color(HUD_BLUE);	/* blue throttle indicator */
	polf2i(4, speed_poly);
    }
    closeobj();

    makeobj(hud_speed = genobj());
    {
	color(HUD_RED);		/* red speed indicator */
	polf2i(4, speed_poly);
    }
    closeobj();

    makeobj(hud_radar = genobj());
    {
	color(HUD_RED);
	move2i(-4, 155);	/* red N */
	draw2i(-4, 170);
	draw2i( 4, 155);
	draw2i( 4, 170);
	color(HUD_BLUE);
	move2i( 4, -155);	/* blue S */
	draw2i(-4, -155);
	draw2i(-4, -162);
	draw2i( 4, -162);
	draw2i( 4, -170);
	draw2i(-4, -170);
    }
    closeobj();

    makeobj(hud_walls = genobj());
    {

	/* maze outer walls */
	color(HUD_BLUE);
	move2i(MSIZ-2, 0);
	draw2i(0, 0);
	draw2i(0, MSIZ*2);
	draw2i(MSIZ-2, MSIZ*2);
	move2i(MSIZ+2, MSIZ*2);
	draw2i(MSIZ*2, MSIZ*2);
	draw2i(MSIZ*2, 0);
	draw2i(MSIZ+2, 0);

	/* arena walls */
	color(HUD_GREEN);
	if (bitplanes >= 7)
	    writemask(MASK_HUD);
	move2i(-(MSIZ*2), -(MSIZ*2));
	draw2i( (MSIZ*4), -(MSIZ*2));
	draw2i( (MSIZ*4),  (MSIZ*4));
	draw2i(-(MSIZ*2),  (MSIZ*4));
	draw2i(-(MSIZ*2), -(MSIZ*2));
	if (bitplanes >= 7)
	    writemask(HUD_MASK);
    }
    closeobj();

    makeobj(hud_mech = genobj());
    {
	move2i(-1, 0);
	draw2i( 1, 0);
	move2i(0,  1);
	draw2i(0, -1);
    }
    closeobj();
}

draw_hud_obj()
{
    int i, j;
    float zoom = radar_zoom / 2.0;

    pushmatrix();
    loadmatrix(hud_matrix);

    if (bitplanes >= 7 && bitplanes <= 12)
	writemask(HUD_MASK);
    else
    {
	callobj(base_hud);
	draw_zoom();
    }


    /*
     *  damage meter
     */
    if (damage)
    {
	color(HUD_RED);
	pmv2i(901,  36);
	pdr2i(904,  36);
	pdr2i(904, damage*20+36);
	pdr2i(901, damage*20+36);
	pclos();
    }

    pushmatrix();
    translate((float)turn, 0.0, 0.0);
    callobj(hud_turn);
    popmatrix();

    pushmatrix();
    translate(0.0, (float)throttle, 0.0);
    callobj(hud_throttle);
    popmatrix();

    pushmatrix();
    translate(0.0, (float)speed, 0.0);
    callobj(hud_speed);
    popmatrix();

    pushmatrix();
    translate(180.0, 180.0, 0.0);
    rotate(wrot, 'z');
    callobj(hud_radar);

    pushmatrix();
    translate((-xpos)*zoom, (-zpos)*zoom, 0.0);
    scale(radar_zoom, radar_zoom, 1.0);
    if (sect == INMAZE)
	draw_hud_maze();
    callobj(hud_walls);
    popmatrix();

    for(i=0; i<MAXPLAYERS; i++)
	if (player[i].type)
	{
	    if (i != id)
	    {
	        color(HUD_RED);
	        pushmatrix();
	        translate((-xpos+player[i].xpos)*zoom,
		          (-zpos+player[i].zpos)*zoom, 0.0);
	        callobj(hud_mech);
	        popmatrix();
	    }

	    color(HUD_BLUE);
	    for(j=0; j<3; j++)
		if (shots[i][j].type)
		{
		    pushmatrix();
		    translate((-xpos+shots[i][j].xpos)*zoom,
			      (-zpos+shots[i][j].zpos)*zoom, 0.0);
		    callobj(hud_mech);
		    popmatrix();
		}
	}
    popmatrix();
    popmatrix();
    if (bitplanes >= 7)
	writemask(MASK_HUD);
}


draw_hud_maze()
{
    int xp = ((int)xpos) >> 2;
    int zp = ((int)zpos) >> 2;
    int pos = (zp << MSHIFT) + xp;
    int x = xp << 1;
    int z = zp << 1;

    color(HUD_GREEN);
    if (bitplanes >= 7)
	writemask(MASK_HUD);

    if (maze_w[pos][N])
    {
	move2i(x  , z+2);
	draw2i(x+2, z+2);
    }
    if (maze_w[pos][S])
    {
	move2i(x  , z  );
	draw2i(x+2, z  );
    }
    if (maze_w[pos][E])
    {
	move2i(x+2, z  );
	draw2i(x+2, z+2);
    }
    if (maze_w[pos][W])
    {
	move2i(x  , z  );
	draw2i(x  , z+2);
    }

    if (zp+1 < MSIZ)
    {
	/* NORTH */
        if (maze_w[pos+MSIZ][N])
        {
	    move2i(x  , z+4);
	    draw2i(x+2, z+4);
        }
        if (maze_w[pos+MSIZ][E])
        {
	    move2i(x+2, z+2);
	    draw2i(x+2, z+4);
        }
        if (maze_w[pos+MSIZ][W])
        {
	    move2i(x  , z+2);
	    draw2i(x  , z+4);
        }
	/* NORTH EAST */
        if (xp+1 < MSIZ)
        {
            if (maze_w[pos+MSIZ+1][N])
            {
	        move2i(x+2, z+4);
	        draw2i(x+4, z+4);
            }
            if (maze_w[pos+MSIZ+1][E])
            {
	        move2i(x+4, z+2);
	        draw2i(x+4, z+4);
            }
        }
	/* NORTH WEST */
        if (xp > 0)
        {
            if (maze_w[pos+MSIZ-1][N])
            {
	        move2i(x-2, z+4);
	        draw2i(x  , z+4);
            }
            if (maze_w[pos+MSIZ-1][W])
            {
	        move2i(x-2, z+2);
	        draw2i(x-2, z+4);
            }
        }
    }
    
    if (zp > 0)
    {
        /* SOUTH */
        if (maze_w[pos-MSIZ][S])
        {
	    move2i(x  , z-2);
	    draw2i(x+2, z-2);
        }
        if (maze_w[pos-MSIZ][E])
        {
	    move2i(x+2, z-2);
	    draw2i(x+2, z  );
        }
        if (maze_w[pos-MSIZ][W])
        {
	    move2i(x  , z-2);
	    draw2i(x  , z  );
        }
	/* SOUTH EAST */
        if (xp+1 < MSIZ)
        {
            if (maze_w[pos-MSIZ+1][S])
            {
	        move2i(x+2, z-2);
	        draw2i(x+4, z-2);
            }
            if (maze_w[pos-MSIZ+1][E])
            {
	        move2i(x+4, z-2);
	        draw2i(x+4, z  );
            }
        }
	/* SOUTH WEST */
        if (xp > 0)
        {
            if (maze_w[pos-MSIZ-1][S])
            {
	        move2i(x-2, z-2);
	        draw2i(x  , z-2);
            }
            if (maze_w[pos-MSIZ-1][W])
            {
	        move2i(x-2, z-2);
	        draw2i(x-2, z  );
            }
        }
    }
    
    if (xp+1 < MSIZ)
    {
        if (maze_w[pos+1][N])
        {
	    move2i(x+2, z+2);
	    draw2i(x+4, z+2);
        }
        if (maze_w[pos+1][S])
        {
	    move2i(x+2, z  );
	    draw2i(x+4, z  );
        }
        if (maze_w[pos+1][E])
        {
	    move2i(x+4, z  );
	    draw2i(x+4, z+2);
        }
    }
    
    if (xp > 0)
    {
        if (maze_w[pos-1][N])
        {
	    move2i(x-2, z+2);
	    draw2i(x  , z+2);
        }
        if (maze_w[pos-1][S])
        {
	    move2i(x-2, z  );
	    draw2i(x  , z  );
        }
        if (maze_w[pos-1][W])
        {
	    move2i(x-2, z  );
	    draw2i(x-2, z+2);
        }
    }
    
    if (bitplanes >= 7)
	writemask(HUD_MASK);
}


draw_zoom()
{
    char buf[128];

    pushmatrix();

    loadmatrix(hud_matrix);
    color(HUD_YELLOW);

    cmov2i(10, 20);
    sprintf(buf, "RADAR X %3f", radar_zoom);
    buf[11] = '\0';
    charstr(buf);

    cmov2i(10, 740);
    sprintf(buf, "ZOOM X %3f", zoom);
    buf[10] = '\0';
    charstr(buf);

    popmatrix();
}
