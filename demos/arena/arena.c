
#include <gl.h>
#include <stdio.h>
#include "arena.h"

Object arena, maze_N, maze_S, maze_E, maze_W, maze_top_t, maze_top_b;
Tag WORLD_ROT, WORLD_POS;

def_objs()
{
    int x, z;

    arena = genobj();
    maze_N = genobj();
    maze_S = genobj();
    maze_E = genobj();
    maze_W = genobj();
    maze_top_t = genobj();
    maze_top_b = genobj();

    makeobj(arena);
    {
	/*
	color(SKY);
	pmvi(-BORDER, 10, -(MAZE+BORDER));
	pdri(-BORDER, 10, BORDER);
	pdri((MAZE+BORDER), 10, BORDER);
	pdri((MAZE+BORDER), 10, -(MAZE+BORDER));
	pclos();
	*/

	color(LGRAY);
	pmvi(-BORDER, 0, -(MAZE+BORDER));
	pdri(-BORDER, 0, BORDER);
	pdri((MAZE+BORDER), 0, BORDER);
	pdri((MAZE+BORDER), 0, -(MAZE+BORDER));
	pclos();

	color(MGRAY);
	for (x = -(BORDER-GRID); x <= MAZE+BORDER-GRID; x+=GRID)
	{
	    movei(x, 0, BORDER);
	    drawi(x, 0,  -(MAZE+BORDER));
	}
	color(MGRAY);
	for (z = BORDER-GRID; z >= -(MAZE+BORDER-GRID); z-=GRID)
	{
	    movei(-BORDER, 0, z);
	    drawi(MAZE+BORDER, 0, z);
	}

	color(MGRAY);
	pmvi(-BORDER,  0, -(MAZE+BORDER));		/* north wall */
	pdri(MAZE+BORDER,  0, -(MAZE+BORDER));
	pdri(MAZE+BORDER, 10, -(MAZE+BORDER));
	pdri(-BORDER, 10, -(MAZE+BORDER));
	pclos();
	pmvi(MAZE+BORDER,  0, -(MAZE+BORDER));	/* east wall */
	pdri(MAZE+BORDER,  0, BORDER);
	pdri(MAZE+BORDER, 10, BORDER);
	pdri(MAZE+BORDER, 10, -(MAZE+BORDER));
	pclos();
	pmvi(MAZE+BORDER,  0, BORDER);	/* south wall */
	pdri(-BORDER,  0, BORDER);
	pdri(-BORDER, 10, BORDER);
	pdri(MAZE+BORDER, 10, BORDER);
	pclos();
	pmvi(-BORDER,  0, BORDER);		/* west wall */
	pdri(-BORDER,  0, -(MAZE+BORDER));
	pdri(-BORDER, 10, -(MAZE+BORDER));
	pdri(-BORDER, 10, BORDER);
	pclos();

	color(BLACK);
	movei(-BORDER,  0, -(MAZE+BORDER));		/* north wall */
	drawi(-BORDER, 10, -(MAZE+BORDER));
	drawi(MAZE+BORDER, 10, -(MAZE+BORDER));
	drawi(MAZE+BORDER,  0, -(MAZE+BORDER));
	drawi(-BORDER,  0, -(MAZE+BORDER));
	movei(MAZE+BORDER,  0, -(MAZE+BORDER));	/* east wall */
	drawi(MAZE+BORDER, 10, -(MAZE+BORDER));
	drawi(MAZE+BORDER, 10, BORDER);
	drawi(MAZE+BORDER,  0, BORDER);
	drawi(MAZE+BORDER,  0, -(MAZE+BORDER));
	movei(MAZE+BORDER,  0, BORDER);	/* south wall */
	drawi(MAZE+BORDER, 10, BORDER);
	drawi(-BORDER, 10, BORDER);
	drawi(-BORDER,  0, BORDER);
	drawi(MAZE+BORDER,  0, BORDER);
	movei(-BORDER,  0, BORDER);		/* west wall */
	drawi(-BORDER, 10, BORDER);
	drawi(-BORDER, 10, -(MAZE+BORDER));
	drawi(-BORDER,  0, -(MAZE+BORDER));
	drawi(-BORDER,  0, BORDER);
    }
    closeobj();

    makeobj(maze_N);
    {
	color(MGRAY);
	pmvi((MAZE>>1)-4, 0, -MAZE);
	pdri(          0, 0, -MAZE);
	pdri(          0, 2, -MAZE);
	pdri((MAZE>>1)-4, 2, -MAZE);
	pclos();
	pmvi(       MAZE, 0, -MAZE);
	pdri((MAZE>>1)+4, 0, -MAZE);
	pdri((MAZE>>1)+4, 2, -MAZE);
	pdri(       MAZE, 2, -MAZE);
	pclos();
	color(BLACK);
	movei((MAZE>>1)-4, 0, -MAZE);
	drawi(          0, 0, -MAZE);
	drawi(          0, 2, -MAZE);
	drawi((MAZE>>1)-4, 2, -MAZE);
	drawi((MAZE>>1)-4, 0, -MAZE);
	movei(       MAZE, 0, -MAZE);
	drawi((MAZE>>1)+4, 0, -MAZE);
	drawi((MAZE>>1)+4, 2, -MAZE);
	drawi(       MAZE, 2, -MAZE);
	drawi(       MAZE, 0, -MAZE);
    }
    closeobj();

    makeobj(maze_E);
    {
	color(MGRAY);
	pmvi(MAZE, 0,     0);
	pdri(MAZE, 0, -MAZE);
	pdri(MAZE, 2, -MAZE);
	pdri(MAZE, 2,     0);
	pclos();
	color(BLACK);
	movei(MAZE, 0,     0);
	drawi(MAZE, 2,     0);
	drawi(MAZE, 2, -MAZE);
	drawi(MAZE, 0, -MAZE);
	drawi(MAZE, 0,     0);
    }
    closeobj();

    makeobj(maze_S);
    {
	color(MGRAY);
	pmvi(          0, 0, 0);
	pdri((MAZE>>1)-4, 0, 0);
	pdri((MAZE>>1)-4, 2, 0);
	pdri(          0, 2, 0);
	pclos();
	pmvi((MAZE>>1)+4, 0, 0);
	pdri(       MAZE, 0, 0);
	pdri(       MAZE, 2, 0);
	pdri((MAZE>>1)+4, 2, 0);
	pclos();
	color(BLACK);
	movei(          0, 0, 0);
	drawi(          0, 2, 0);
	drawi((MAZE>>1)-4, 2, 0);
	drawi((MAZE>>1)-4, 0, 0);
	drawi(          0, 0, 0);
	movei((MAZE>>1)+4, 0, 0);
	drawi((MAZE>>1)+4, 2, 0);
	drawi(       MAZE, 2, 0);
	drawi(       MAZE, 0, 0);
	drawi((MAZE>>1)+4, 0, 0);
    }
    closeobj();

    makeobj(maze_W);
    {
	color(MGRAY);
	pmvi(0, 0, -MAZE);
	pdri(0, 0,     0);
	pdri(0, 2,     0);
	pdri(0, 2, -MAZE);
	pclos();
	color(BLACK);
	movei(0, 0, -MAZE);
	drawi(0, 2, -MAZE);
	drawi(0, 2,     0);
	drawi(0, 0,     0);
	drawi(0, 0, -MAZE);
    }
    closeobj();

    makeobj(maze_top_b);
    {
	color(LGRAY);
#ifndef CLOVER
	backface(FALSE);
#endif
	pmvi(   0, 2,     0);
	pdri(   0, 2, -MAZE);
	pdri(MAZE, 2, -MAZE);
	pdri(MAZE, 2,     0);
	pclos();
#ifndef CLOVER
	backface(TRUE);
#endif

	color(DGRAY);
	movei(   0, 2,     0);
	drawi(   0, 2, -MAZE);
	drawi(MAZE, 2, -MAZE);
	drawi(MAZE, 2,     0);
	drawi(   0, 2,     0);

	color(MGRAY);
	for (x = GRID; x <= MAZE-GRID; x+=GRID)
	{
	    movei(x, 2, 0);
	    drawi(x, 2, -MAZE);
	}
	color(MGRAY);
	for (z = -GRID; z >= -(MAZE-GRID); z-=GRID)
	{
	    movei(0, 2, z);
	    drawi(MAZE, 2, z);
	}
    }
    closeobj();

    makeobj(maze_top_t);
    {
	color(LGRAY);
	pmvi(   0, 2,     0);
	pdri(MAZE, 2,     0);
	pdri(MAZE, 2, -MAZE);
	pdri(   0, 2, -MAZE);
	pclos();

	color(DGRAY);
	movei(   0, 2,     0);
	drawi(   0, 2, -MAZE);
	drawi(MAZE, 2, -MAZE);
	drawi(MAZE, 2,     0);
	drawi(   0, 2,     0);

	/*
	color(DGRAY);
	for (x = GRID; x <= MAZE-GRID; x+=GRID)
	{
	    movei(x, 2, 0);
	    drawi(x, 2, -MAZE);
	}
	color(DGRAY);
	for (z = -GRID; z >= -(MAZE-GRID); z-=GRID)
	{
	    movei(0, 2, z);
	    drawi(MAZE, 2, z);
	}
	*/
    }
    closeobj();
}

