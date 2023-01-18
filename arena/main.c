
#include <gl.h>
#include <device.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/times.h>

#include "arena.h"

int screen_size[2];

char buf[80];
double zoom = 1.0;
int sect, last_sect;
int did_colide;
int id = 0;
int tilt = FALSE;
int loops = 0;
long starttime;
int mech_type = GREEN_MECH;
#if NETWORKING
int network = FALSE;
#endif

#ifdef CLOVER
Cursor null_cur = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

struct thing *murderer;

main(argc, argv)
    int argc;
    char **argv;
{
    int i, j;
    short val;

    if (argc > 1)
    {
	for(i=1; i < argc; i++)
	{
	    if (argv[i][0] == '-')
		argv[i]++;
	    switch(argv[i][0])
	    {
		case 'b':
		    mech_type = BLUE_MECH;
		    break;
		case 'g':
		    mech_type = GREEN_MECH;
		    break;
#if NETWORKING
		case 'n':
		    network = TRUE;
		    break;
#endif
		case 'd':
		    player[0].id = 0;
		    player[1].id = 1;
		    player[2].id = 2;
		    player[3].id = 3;
		    player[4].id = 4;
		    player[5].id = 5;
		    player[6].id = 6;
		    player[7].id = 7;
		    player[8].id = 8;
		    player[9].id = 9;
		    player[0].type = PLAYER | BLUE_MECH;
		    player[0].xpos = 50.0;
		    player[0].zpos = 200.0;
		    player[0].yrot = 200;/*1300;*/
		    player[2].type = PLAYER | BLUE_MECH;
		    player[2].xpos = 5.0;
		    player[2].zpos = 20.0;
		    player[2].yrot = 1300;
		    player[3].type = PLAYER;
		    player[3].xpos = 1.8;
		    player[3].zpos = 39.0;
		    player[3].yrot = 1900;
		    player[8].type = PLAYER | BLUE_MECH;
		    player[8].xpos = 2.2;
		    player[8].ypos = 2.0;
		    player[8].zpos = 37.0;
		    player[8].yrot = 1300;
		    player[5].type = PLAYER;
		    player[5].xpos = 20.0;
		    player[5].zpos = 2.0;
		    player[5].yrot = 1300;
		    player[7].type = PLAYER | BLUE_MECH;
		    player[7].xpos = 30.0;
		    player[7].zpos = 30.0;
		    player[7].yrot = 1300;
		    player[1].type = PLAYER | BLUE_MECH;
		    player[1].xpos = 150.0;
		    player[1].zpos = 38.0;
		    player[1].yrot = 3300;
		    player[4].type = PLAYER;
		    player[4].xpos = -3.0;
		    player[4].zpos = 38.0;
		    player[4].yrot = 2300;
		    player[6].type = PLAYER | BLUE_MECH;
		    player[6].xpos = 50.5;
		    player[6].zpos = -36.6;
		    player[6].yrot = 0;
		    player[6].anckle_rot = -150;
		    player[6].knee_rot = 300;
		    player[6].torso_z_rot = -150;
		    player[9].type = PLAYER | BLUE_MECH;
		    player[9].xpos = 3.2;
		    player[9].zpos = 37.5;
		    player[9].yrot = 0;
		    break;
		default:
		    break;
	    }
	}
    }

    srand(getpid());

    /*
     *  open the window
     */
	prefposition(0, XMAXSCREEN, 0, YMAXSCREEN);
	{
		char *t, *strrchr();
		winopen((t=strrchr(argv[0], '/')) != NULL ? t+1 : argv[0]);
                getsize(&screen_size[0], &screen_size[1]);
	}
    startup();
    color(BLACK);
    clear();

    save_map();		/* save the color map */

    doublebuffer();

#ifdef CLOVER
    cmode();
    shademodel(FLAT);
    defcursor(5, null_cur);
    setcursor(5, 0, 0);
#endif

    gconfig();
    cursoff();

#ifndef CLOVER
    backface(TRUE);
#endif

    set_color_table();
    make_mech(&green_mech, GREEN1, GREEN2);
    make_mech(&blue_mech, BLUE1, BLUE2);
    make_missiles();
    init_maze();
    def_objs();
    make_hud();

    callobj(base_hud);
    cursoff();
    swapbuffers();
    callobj(base_hud);
    cursoff();
    swapbuffers();

    /*
     *  set up world view
     */
    perspective(400, (float)XMAXSCREEN/YMAXSCREEN, 0.01, 10000.0);
    lookat(0.0, 0.98, 0.0, 0.0, 0.98, -1.0, 0.0);

    // setvaluator(MOUSEX, MOUSE_CENT, -200+MOUSE_CENT, 200+MOUSE_CENT);
    // setvaluator(MOUSEY, MOUSE_CENT, -100+MOUSE_CENT, 200+MOUSE_CENT);

    /*
     *  set up queue
     */
    qdevice(CKEY);
    qdevice(EKEY);
    qdevice(RKEY);
    /*qdevice(SKEY);*/
    qdevice(XKEY);
    qdevice(ZKEY);
    qdevice(ESCKEY);
    qdevice(KEYBD);
    qdevice(RIGHTMOUSE);
    qdevice(MIDDLEMOUSE);
    qdevice(LEFTMOUSE);

    /* time loops */
    {
	struct tms tbuf;
	starttime = times(&tbuf);
    }

    while(1)
    {
	while (qtest())
	{
	    switch(qread(&val))
	    {
		case ESCKEY:
			if (!val)
			{	/* Exit on ESC key going UP */
#if NETWORKING
			    if (network)
				send_death();
#endif
			    restore_map();	/* restore the color map */
			    curson();
			    setvaluator(MOUSEX, 512, 0, XMAXSCREEN);
			    setvaluator(MOUSEY, 384, 0, YMAXSCREEN);
			    gexit();
			    exit(0);
			}
		    break;
		/*
		case SKEY:
		    if (val && !(player[id].type & EXPLODE))
			thrust = TRUE;
		    else
			thrust = FALSE;
		    break;
		*/
		case CKEY:
		    if (val)
			tilt = !tilt;
		    break;
		case LEFTMOUSE:
		case EKEY:
		    if (val && !(player[id].type & EXPLODE))
			fire_missile(CANNON);
		    break;
		case XKEY:
		    if (val)
		    {
			if (getbutton(LEFTSHIFTKEY) ||
			    getbutton(RIGHTSHIFTKEY))
			{
			    if (radar_zoom > 0.55)
				radar_zoom -= 0.5;
			}
			else
			    radar_zoom += 0.5;
			
			if (bitplanes >= 7)
			{
			    pushmatrix();
			    frontbuffer(TRUE);
			    loadmatrix(hud_matrix);
			    writemask(HUD_Y_MASK);
			    color(BLACK);
			    rectfi(10, 18, 128, 31);
			    color(HUD_YELLOW);
			    cmov2i(10, 20);
			    sprintf(buf, "RADAR X %3f", radar_zoom);
			    buf[11] = '\0';
			    charstr(buf);
			    frontbuffer(FALSE);
			    writemask(MASK_HUD);
			    popmatrix();
			}
		    }
		    break;
		case ZKEY:
		    if (val)
		    {
			if (getbutton(LEFTSHIFTKEY) ||
			    getbutton(RIGHTSHIFTKEY))
			{
			    if (zoom > 0.55)
				zoom -= 0.1;
			}
			else
			    zoom += 0.1;
			
			if (bitplanes >= 7)
			{
			    pushmatrix();
			    frontbuffer(TRUE);
			    loadmatrix(hud_matrix);
			    writemask(HUD_Y_MASK);
			    color(BLACK);
			    rectfi(10, 738, 120, 751);
			    color(HUD_YELLOW);
			    cmov2i(10, 740);
			    sprintf(buf, "ZOOM X %3f", zoom);
			    buf[10] = '\0';
			    charstr(buf);
			    frontbuffer(FALSE);
			    writemask(MASK_HUD);
			    popmatrix();
			}

			perspective((int)(400/zoom), 800.0/480.0, 0.01, 10000.0);
			lookat(0.0, 1.0, 0.0, 0.0, 1.0, -1.0, 0.0);
		    }
		    break;
		case RKEY:
		    if (player[id].type & DEAD)
			restart();
		    break;
		default:
		    break;
	    }
	}

	was_shot = FALSE;
#if NETWORKING
	if (network)
	    read_net();
#endif
	pushmatrix();
	if ((player[id].type & EXPLODE) &&
	    !(player[id].type & DEAD))
	{
	    if (--explode_counter <= 0)
		player[id].type |= DEAD;
	}
	else
	{
	    throttle = ((int)getvaluator(MOUSEY) - screen_size[1] / 2) / 2.0;
	    turn = ((int)getvaluator(MOUSEX) - screen_size[0] / 2) / 10.0;
	}

	for(i=0; i<NUMSECTORS; i++)
	    sector[i] = NULL;
	push_pos(-1);		/* clear maze objects */

	for (i=0; i<MAXPLAYERS; i++)
	    if (player[i].type && i != id)
		place_obj(&player[i]);

        do_shots();

	if (getbutton(SKEY))
	    thrust = TRUE;
	else
	    thrust = FALSE;

	if (getbutton(MIDDLEMOUSE))
	{
	    /*
	    setvaluator(MOUSEY, MOUSE_CENT, -100+MOUSE_CENT, 200+MOUSE_CENT);
	    */
	    throttle = 0;
	}

	if(!(player[id].type & DEAD))
	    move_mech();

	if (getbutton(LEFTMOUSE))
	{
	    setvaluator(MOUSEX, MOUSE_CENT, -200+MOUSE_CENT, 200+MOUSE_CENT);
	    turn = 0;
	}

	last_sect = sect;
	get_sect();
	if (check_colision())
	{
	    player[id].type |= HIT_WALL;
	    colide();
	    did_colide = TRUE;
	}
	
	get_sect();
	if (check_obj_colision())
	    did_colide = TRUE;
	    
	if ((player[id].type & EXPLODE) && !(player[id].type & DEAD))
	    explode(&player[id]);

#if NETWORKING
	if (network)
	    send_my_stuff();
#endif

	for (i=0; i<MAXPLAYERS; i++)
	    if (player[i].type)
		for (j=0; j<3; j++)
		    if (shots[i][j].type)
			place_obj(&shots[i][j]);

	if (tilt)
	    rotate(player[id].torso_x_rot, 'z');
	rotate(wrot, 'y');
	translate(-xpos, -ypos, zpos);

	callobj(arena);
	draw_view();
	popmatrix();

	draw_hud_obj();

	if (player[id].type & EXPLODE)
	{
	    color(BLACK);
	    clear();
	}
	else if (was_shot)
	{
	    color(RED);
	    setpattern(HALFTONE);
	    clear();
	    setpattern(0);
	    player[id].type &= CLEAR_WHAT;
	    did_colide = FALSE;
	}
	else if (did_colide)
	{
	    color(BLACK);
	    setpattern(HALFTONE);
	    clear();
	    setpattern(0);
	    player[id].type &= CLEAR_WHAT;
	    did_colide = FALSE;
	}

#if NETWORKING
	if (network)
	    exit_comm();
#endif

    	swapbuffers();
	color(SKY);
	if (bitplanes >= 7)
	    writemask(~(HUD_Y_MASK));
	clear();
	if (bitplanes >= 7)
	    writemask(MASK_HUD);
	loops++;
    }
}


draw_view()
{
    if (xpos <= 0)
    {
	if (zpos <= 0)		/* south west */
	{
	    DRAW_SECT_NE();
	    DRAW_SECT_N();
	    DRAW_SECT_E();
	    DRAW_SECT_NW();
	    DRAW_SECT_SE();
	    if (ypos <= 1.0)
	    {
	        DRAW_SECT_M();
		callobj(maze_top_b);
		draw_maze((MAZE >> 1)-1, 1);
	    }
	    else
	    {
		draw_maze((MAZE >> 1)-1, 1);
		callobj(maze_top_t);
	        DRAW_SECT_M();
	    }
	    callobj(maze_W);
	    callobj(maze_S);
	    DRAW_SECT_S();
	    DRAW_SECT_W();
	    DRAW_SECT_SW();
	}
	else if (zpos <= MAZE)	/* west */
	{
	    DRAW_SECT_E();
	    DRAW_SECT_NE();
	    DRAW_SECT_SE();
	    DRAW_SECT_N();
	    DRAW_SECT_S();
	    DRAW_SECT_NW();
	    DRAW_SECT_SW();
	    if (ypos > 1.0)
		callobj(maze_top_t);
	    DRAW_SECT_M();
	    callobj(maze_W);
	    DRAW_SECT_W();
	}
	else			/* north west */
	{
	    DRAW_SECT_SE();
	    DRAW_SECT_S();
	    DRAW_SECT_E();
	    DRAW_SECT_SW();
	    DRAW_SECT_NE();
	    if (ypos <= 1.0)
	    {
	        DRAW_SECT_M();
	        callobj(maze_top_b);
	        draw_maze((MAZE >> 1)-1, MAZE-1);
	    }
	    else
	    {
	        draw_maze((MAZE >> 1)-1, MAZE-1);
	        callobj(maze_top_t);
	        DRAW_SECT_M();
	    }
	    callobj(maze_W);
	    callobj(maze_N);
	    DRAW_SECT_W();
	    DRAW_SECT_N();
	    DRAW_SECT_NW();
	}
    }
    else if (xpos <= MAZE)
    {
	if (zpos <= 0)		/* south */
	{
	    DRAW_SECT_N();
	    DRAW_SECT_NE();
	    DRAW_SECT_NW();
	    DRAW_SECT_E();
	    DRAW_SECT_W();
	    DRAW_SECT_SE();
	    DRAW_SECT_SW();
	    if (ypos <= 1.0)
	    {
	        DRAW_SECT_M();
	        callobj(maze_top_b);
	        if ((int)xpos < (MAZE >> 1))
		    draw_maze((MAZE >> 1)-1, 1);
	        else
		    draw_maze((MAZE >> 1)+1, 1);
	    }
	    else
	    {
	        if ((int)xpos < (MAZE >> 1))
		    draw_maze((MAZE >> 1)-1, 1);
	        else
		    draw_maze((MAZE >> 1)+1, 1);
	        callobj(maze_top_t);
	        DRAW_SECT_M();
	    }
	    callobj(maze_S);
	    DRAW_SECT_S();
	}
	else if (zpos <= MAZE)	/* maze */
	{
	    if (ypos <= 1.0)
	    {
	        callobj(maze_top_b);
	        draw_maze((int)xpos, (int)zpos);
	    }
	    else
	    {
	        DRAW_SECT_N();
	        DRAW_SECT_S();
	        DRAW_SECT_E();
	        DRAW_SECT_W();
	        DRAW_SECT_SE();
	        DRAW_SECT_SW();
	        DRAW_SECT_NE();
	        DRAW_SECT_NW();
	        callobj(maze_top_t);
	        DRAW_SECT_M();
	    }
	}
	else			/* north */
	{
	    DRAW_SECT_S();
	    DRAW_SECT_SE();
	    DRAW_SECT_SW();
	    DRAW_SECT_E();
	    DRAW_SECT_W();
	    DRAW_SECT_NE();
	    DRAW_SECT_NW();
	    if (ypos <= 1.0)
	    {
	        DRAW_SECT_M();
	        callobj(maze_top_b);
	        if ((int)xpos < (MAZE >> 1))
		    draw_maze((MAZE >> 1)-1, MAZE-1);
	        else
		    draw_maze((MAZE >> 1)+1, MAZE-1);
	    }
	    else
	    {
	        if ((int)xpos < (MAZE >> 1))
		    draw_maze((MAZE >> 1)-1, MAZE-1);
	        else
		    draw_maze((MAZE >> 1)+1, MAZE-1);
	        callobj(maze_top_t);
	        DRAW_SECT_M();
	    }
	    callobj(maze_N);
	    DRAW_SECT_N();
	}
    }
    else
    {
	if (zpos <= 0)		/* south east */
	{
	    DRAW_SECT_NW();
	    DRAW_SECT_W();
	    DRAW_SECT_N();
	    DRAW_SECT_SW();
	    DRAW_SECT_NE();
	    if (ypos <= 1.0)
	    {
	        DRAW_SECT_M();
	        callobj(maze_top_b);
	        draw_maze((MAZE >> 1)+1, 1);
	    }
	    else
	    {
	        draw_maze((MAZE >> 1)+1, 1);
	        callobj(maze_top_t);
	        DRAW_SECT_M();
	    }
	    callobj(maze_E);
	    callobj(maze_S);
	    DRAW_SECT_S();
	    DRAW_SECT_E();
	    DRAW_SECT_SE();
	}
	else if (zpos <= MAZE)	/* east */
	{
	    DRAW_SECT_W();
	    DRAW_SECT_NW();
	    DRAW_SECT_SW();
	    DRAW_SECT_N();
	    DRAW_SECT_S();
	    DRAW_SECT_NE();
	    DRAW_SECT_SE();
	    if (ypos > 1.0)
		callobj(maze_top_t);
	    DRAW_SECT_M();
	    callobj(maze_E);
	    DRAW_SECT_E();
	}
	else			/* north east */
	{
	    DRAW_SECT_SW();
	    DRAW_SECT_W();
	    DRAW_SECT_S();
	    DRAW_SECT_NW();
	    DRAW_SECT_SE();
	    if (ypos <= 1.0)
	    {
	        DRAW_SECT_M();
	        callobj(maze_top_b);
	        draw_maze((MAZE >> 1)+1, MAZE-1);
	    }
	    else
	    {
	        draw_maze((MAZE >> 1)+1, MAZE-1);
	        callobj(maze_top_t);
	        DRAW_SECT_M();
	    }
	    callobj(maze_E);
	    callobj(maze_N);
	    DRAW_SECT_N();
	    DRAW_SECT_E();
	    DRAW_SECT_NE();
	}
    }
}


get_sect()
{
    if (xpos <= 0)
    {
	if (zpos <= 0)		/* south west */
	    sect = SOUTHWEST;
	else if (zpos <= MAZE)	/* west */
	    sect = WEST;
	else			/* north west */
	    sect = NORTHWEST;
    }
    else if (xpos <= MAZE)
    {
	if (zpos <= 0)		/* south */
	    sect = SOUTH;
	else if (zpos <= MAZE)	/* maze */
	    sect = INMAZE;
	else			/* north */
	    sect = NORTH;
    }
    else
    {
	if (zpos <= 0)		/* south east */
	    sect = SOUTHEAST;
	else if (zpos <= MAZE)	/* east */
	    sect = EAST;
	else			/* north east */
	    sect = NORTHEAST;
    }
}

