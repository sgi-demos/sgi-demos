#include <gl.h>
#include <device.h>
#include "arena.h"

#undef SHOW_STARTUP_SCREEN

char *intro[] = {
"",
"					ARENA",
"",
"It is the year 2053.  The corporate wars are over, and the once great corporate empires lie",
"in ruin.  Man though, never tired of violence, has changed the war machines of the past into",
"todays sport.  MECHS, fourteen foot tall humanoid fighting machines, and their pilots battle",
"it out in the arenas.",
"",
"Arena simulates this possible future sport.",
"",
"The robots or mechs are effectively fast maneuverable tanks.  They have rollers on their feet",
"and thus skate along the ground.  A computerized balance system keeps them on their feet.",
"Systems include telescopic vision, radar, jump jets, and a 40mm autocannon.  Instrumentation",
"is displayed on a heads-up display.",
"",
"The playing field is square and approximately one kilometer on a side.  There is a maze in",
"the center of the arena with entrances north and south",
"",
"COMMANDS                                            MOUSE",
"",
"z/Z - optics zoom in / zoom out                     left mouse   - stop turn",
"x/X - zoom in radar / zoom out radar                middle mouse - brake",
"e   - fire cannon                                   mouse x      - adjust turn",
"s   - jump                                          mouse y      - adjust throttle",
"c   - toggle visual tilt stabalizer",
"",
"				Hit any key to continue",
(char *) 0 };

// int winw, winh;

startup()
{
    int i;

#ifdef SHOW_STARTUP_SCREEN
    color(BLUE);
    clear();

    // getsize(&winw, &winh);
    // ortho2(0, winw, 0, winh);
    ortho2(0, XMAXSCREEN, 0, YMAXSCREEN);

    color(WHITE);
    for (i=0; intro[i] != (char *) 0; i++)
    {
	cmov2i(30, (YMAXSCREEN-30) - i*16);
	charstr(intro[i]);
    }
#endif

    qdevice(KEYBD);

#if NETWORKING
    if (network)
        init_comm();
    else
#endif
    {
	id = 0;
	player[0].id = 0;
	player[0].type = PLAYER;
    }

    shot = shots[id];

    // LK: Skip waiting for keyboard.
    while (0 && qread(&i) != KEYBD)
#if NETWORKING
	if (network)
	    send_death();
#else
        ;
#endif

    // BG: swap and wait for mouse
    qdevice(LEFTMOUSE);
#ifdef SHOW_STARTUP_SCREEN
    swapbuffers();
    while(qread(&i) != LEFTMOUSE) {
#if NETWORKING
	if (network)
	    send_death();
#else
        ;
#endif
    }
#endif

    unqdevice(KEYBD);
}
