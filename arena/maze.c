
#include <gl.h>
#include <stdio.h>
#include <stdlib.h>

#include "arena.h"


/*
 *  Wall drawing macros
 */
#define DRAW_N(X, Z) (x1 = X<<2, x2 = x1+WL, z1 = -((Z<<2)+WL),\
		      color(MGRAY), pmvi(x2, 0, z1), pdri(x2, 2, z1),\
		      pdri(x1, 2, z1), pdri(x1, 0, z1), pclos(),\
		      color(DGRAY), movei(x1, 0, z1), drawi(x1, 2, z1),\
		      drawi(x2, 2, z1), drawi(x2, 0, z1), drawi(x1, 0, z1))

#define DRAW_S(X, Z) (x1 = X<<2, x2 = x1+WL, z1 = -(Z<<2),\
		      color(MGRAY), pmvi(x1, 0, z1), pdri(x1, 2, z1),\
		      pdri(x2, 2, z1), pdri(x2, 0, z1), pclos(),\
		      color(DGRAY), movei(x2, 0, z1), drawi(x2, 2, z1),\
		      drawi(x1, 2, z1), drawi(x1, 0, z1), drawi(x2, 0, z1))

#define DRAW_W(X, Z) (x1 = X<<2, z1 = -(Z<<2), z2 = z1-WL,\
		      color(MGRAY), pmvi(x1, 0, z2), pdri(x1, 2, z2),\
		      pdri(x1, 2, z1), pdri(x1, 0, z1), pclos(),\
		      color(DGRAY), movei(x1, 0, z1), drawi(x1, 2, z1),\
		      drawi(x1, 2, z2), drawi(x1, 0, z2), drawi(x1, 0, z1))

#define DRAW_E(X, Z) (x1 = (X<<2)+WL, z1 = -(Z<<2), z2 = z1-WL,\
		      color(MGRAY), pmvi(x1, 0, z1), pdri(x1, 2, z1),\
		      pdri(x1, 2, z2), pdri(x1, 0, z2), pclos(),\
		      color(DGRAY), movei(x1, 0, z2), drawi(x1, 2, z2),\
		      drawi(x1, 2, z1), drawi(x1, 0, z1), drawi(x1, 0, z2))

#define pushr() if(!visited[pos])\
		{\
		    int i = (facing % 2)? (pos & LOWBITS) : (pos >> MSHIFT);\
		    rrtop[i]++;\
		    rrooms[i][rrtop[i]] = (facing % 2)? (pos >> MSHIFT) :\
							(pos & LOWBITS);\
		    visited[pos] = TRUE;\
		}\
		else\
		return

#define pushl() if(!visited[pos])\
		{\
		    int i = (facing % 2)? (pos & LOWBITS) : (pos >> MSHIFT);\
		    lrtop[i]++;\
		    lrooms[i][lrtop[i]] = (facing % 2)? (pos >> MSHIFT) :\
							(pos & LOWBITS);\
		    visited[pos] = TRUE;\
		}\
		else\
		return

#define ALLBITS (MSIZ*MSIZ - 1)

int maze_exit;
#define NO_EXIT		0
#define NORTH_EXIT	1
#define SOUTH_EXIT	2



short maze_w[MSIZ*MSIZ][4];
short maze_s[MSIZ*MSIZ]; /* solid areas of maze */

int facing;
#define N 0
#define E 1
#define S 2
#define W 3

int maze_vw[MSIZ*MSIZ];	/* maze visible walls */
#define NW  01
#define EW  02
#define SW  04
#define WW 010

short rrooms[MSIZ][MSIZ];	/* right visible maze rooms */
short lrooms[MSIZ][MSIZ];	/* left visible maze rooms */
short rrtop[MSIZ];		/* right visible maze rooms top*/
short lrtop[MSIZ];		/* left visible maze rooms top*/
visited[MSIZ*MSIZ];

int f, b, l, r;
int fw, bw, lw, rw;

struct thing *maze_obj[MSIZ*MSIZ];	/* lists of things in each room */

char def_maze[33][66] =
{
" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ ",
"|  _   _   _  |   |_|_|_|  _ _ _ _ _ _  |_|_|_|_|_|_|_|_|       |",
"| |_| |_| |_|  _|  _  |_| |   |_|_|_|  _|_|_|_|_|_|_|_|_|       |",
"|  _   _   _  |  _|_| |_| | | |_|_|_| |_|_|_|_|_|_|_|_|_|       |",
"| |_| |_| |_| | |_|_| |_| | | |_|_|_| |_|  _ _  |_|_|_|_|       |",
"|  _   _   _  | |_|_|   |_ _| |_|_|_| |_| |_|_| |    _ _   _ _ _|",
"| |_| |_| |_| | |_|_|_    |_| |_|_|_|_ _ _|_|_| | | |_|_| |_|_|_|",
"|_   _   _ _ _| |_|_|_|     |  _  |_|_|_|_|_|_| | | |_|_| |_|_|_|",
"|_| | | |_|_|_|_ _ _  |_    | | | |_|_|_|_|_|_| | |_ _ _  |_|_|_|",
"|_| |_| |_|_|_|_|_|_| |_|_ _| | | |_|_|_|_|_|_| |  _ _ _  |_|_|_|",
"|_|_   _|_|_|_|_|_|_| |_|_|_| | | |_|_|_|_|_|_|_ _|_|_|_|  _ _  |",
"|_|_| |_|_|_|_|_|_|_| |_|_|_| |  _|_|_|_|_|_|_|_|_|_|_|_|_|  _ _|",
"|_|_| |_|_|  _ _ _ _   _ _ _ _| |_|_|_|_|_|_|_|_|_|_|_|_|_|_ _  |",
"|_|_| |_|_| |_|_|_|_| |_|_|_|  _  |_|_|_|_|_|_|_|_|_|_|_|_|  _ _|",
"|_|_| |_|_| |_|_|_|_| |_|  _   _   _  |_|_|_|_|_|_|_|_|_|_|_ _  |",
"|_|_|_ _ _ _|_|_|_|_| |_|  _|  _  |_  |_|_|_|_|_|_|_|_|_|_|  _ _|",
"|_|_|_|_|_|_|_|_|_|_| |_|_ _   _   _ _|_|_|_|_|_|_|_|_|_|_|_ _  |",
"|_|_|_|_|_|_|_|_|_|_| |_|_|_|  _  |_|  _   _   _  |_|_|_|_|  _ _|",
"|_|_|_|_|_|_|_|_|_|_| |_|_|_| | | |_| |_| |_| |_| |_|_|_|_|_ _  |",
"|  _ _ _ _ _ _ _ _  | |_|_|_|_ _ _|  _   _   _   _  |_|_|_|  _ _|",
"| |  _ _ _ _ _ _  | | |_|_|_|_|_|_| |_| |_| |_| |_| |_|_|_|_ _  |",
"| | |  _ _ _ _  | | | |_|_|_|_|_|_|_   _   _   _   _|_|_|_|  _ _|",
"| | | |  _ _  | | | | |_|_|_|_|_|_|_| |_| |_| |_| |_|_|_|_|_ _  |",
"| | | | |   | | | | | |_|_|_|_|_|_|_|_   _ _ _   _|_|_|_|_|  _ _|",
"| | | | | | | | | | | |_|_|_|_|_|_|_|_|_ _   _ _|_|_|_|_|_|_ _  |",
"| | | | | | | | | | | |_|_|_|_|_|_|_|_|_|_| |_|_|_|_|_|_|_|  _ _|",
"| | | | | | | | | | | |_|_|_|_|_|_|_|_|_|_| |_|_|_|_|_|_|_|_ _  |",
"| | | | | |_ _| | | | |_|_|_|_|_|_|_|_|_|_| |_|_|  _  |_|_|  _ _|",
"| | | | |_ _ _ _| | | |_|_|  _ _ _ _  |_|_| |_|_| |_| |         |",
"| | | |_ _ _ _ _ _| | |_|_| |       | |_|_| |_|_| |_| |         |",
"| | |_ _ _ _ _ _ _ _| |_|_| | |   | |  _ _ _ _ _ _|_|           |",
"| |_ _ _ _ _ _ _ _ _ _ _ _ _| |   | | |_|_|_|_|_|_|_| |         |",
"|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|   |_ _|_|_|_|_|_|_|_|_|_ _ _ _ _|"
};


init_maze()
{
    int i, j;

    read_def_maze();

    for (i=0; i < MSIZ*MSIZ; i++)
    {
	visited[i] = FALSE;
	maze_obj[i] = NULL;

	if (maze_w[i][N] && maze_w[i][S] && maze_w[i][E] && maze_w[i][W])
	    maze_s[i] = TRUE;
	else
	    maze_s[i] = FALSE;
    }

    for (i=0; i < MSIZ; i++)
    {
	rrtop[i] = -1;
	lrtop[i] = -1;
    }
}


search_F(pos)
    int pos;
{
    if ((((unsigned)pos) & ~ALLBITS))
    {
	if(pos < 0)
	    maze_exit = SOUTH_EXIT;
	else
	    maze_exit = NORTH_EXIT;
	return;
    }

    pushr();

    if (!maze_w[pos][fw])
	search_F(pos + f);

    if (/*rtop > 0 &&*/ !maze_w[pos][rw])
	search_R(pos + r);
    if (/*ltop > 0 &&*/ !maze_w[pos][lw])
	search_L(pos + l);
}


search_R(pos)
    int pos;
{
    if (((unsigned)pos) & ~ALLBITS)
    {
	if(pos < 0)
	    maze_exit = SOUTH_EXIT;
	else
	    maze_exit = NORTH_EXIT;
	return;
    }

    pushr();

    if (!maze_w[pos][fw])
	search_R(pos + f);

    if (!maze_w[pos][rw])
	search_R(pos + r);
}


search_L(pos)
    int pos;
{
    if (((unsigned)pos) & ~ALLBITS)
    {
	if(pos < 0)
	    maze_exit = SOUTH_EXIT;
	else
	    maze_exit = NORTH_EXIT;
	return;
    }

    pushl();

    if (!maze_w[pos][fw])
	search_L(pos + f);

    if (!maze_w[pos][lw])
	search_L(pos + l);
}



draw_maze(xp, zp)
    int xp, zp;	/* starting point */
{
    int count, i;
    int x1, x2, z1, z2, sx, sz, x, z, pos;
    short fbbuf[20];
    struct thing *tmp;

    sx = (int)xp >> SHIFT;
    sz = (int)zp >> SHIFT;

    maze_exit = NO_EXIT;

    if (sx < 0 || sx >= MSIZ || sz < 0 || sz >= MSIZ)
	return;

    if (wrot >= 3150 || wrot <= 450)
	facing = N;
    else if (wrot >= 450 && wrot <= 1350)
	facing = E;
    else if (wrot >= 1350 && wrot <= 2250)
	facing = S;
    else if (wrot >= 2250 && wrot <= 3150)
	facing = W;

    switch(facing)
    {
	case N:
	    f =  MSIZ;	fw = N;
	    b = -MSIZ;	bw = S;
	    r =   1;	rw = E;
	    l =  -1;	lw = W;
	    break;
	case E:
	    f =   1;	fw = E;
	    b =  -1;	bw = W;
	    r = -MSIZ;	rw = S;
	    l =  MSIZ;	lw = N;
	    break;
	case S:
	    f = -MSIZ;	fw = S;
	    b =  MSIZ;	bw = N;
	    r =  -1;	rw = W;
	    l =   1;	lw = E;
	    break;
	case W:
	    f =  -1;	fw = W;
	    b =   1;	bw = E;
	    r =  MSIZ;	rw = N;
	    l = -MSIZ;	lw = S;
	    break;
    }

    search_F((sz << MSHIFT) + sx);

    if (maze_exit == SOUTH_EXIT && sect == INMAZE)
    {
	DRAW_SECT_SW();
	DRAW_SECT_SE();
	DRAW_SECT_S();
    }
    else if (maze_exit == NORTH_EXIT && sect == INMAZE)
    {
	DRAW_SECT_NW();
	DRAW_SECT_NE();
	DRAW_SECT_N();
    }

    switch(facing)
    {
	case N:
	    for(z = MSIZ - 1; z >= sz; z--)
	    {
		count = lrtop[z];
		for(i=count; i >= 0; i--)
		{
		    x = lrooms[z][i];
		    pos = (z << MSHIFT) + x;
		    visited[pos] = FALSE;
		    if (maze_w[pos][N]) 
			DRAW_N(x, z);
		    if (maze_w[pos][W]) 
			DRAW_W(x, z);
		    if (maze_obj[pos])
		    {
			draw_obj(maze_obj[pos]);
			maze_obj[pos] = NULL;
		    }
		}

		count = rrtop[z];
		for(i=count; i >= 0; i--)
		{
		    x = rrooms[z][i];
		    pos = (z << MSHIFT) + x;
		    visited[pos] = FALSE;
		    if (maze_w[pos][N]) 
			DRAW_N(x, z);
		    if (maze_w[pos][E]) 
			DRAW_E(x, z);
		    if (x == sx && maze_w[pos][W]) 
			DRAW_W(x, z);
		    if (maze_obj[pos])
		    {
			draw_obj(maze_obj[pos]);
			maze_obj[pos] = NULL;
		    }
		}
		lrtop[z] = -1;
		rrtop[z] = -1;
	    }
	    break;
	case E:
	    for(x=MSIZ-1; x >= sx; x--)
	    {
		count = lrtop[x];
		for(i=count; i >= 0; i--)
		{
		    z = lrooms[x][i];
		    pos = (z << MSHIFT) + x;
		    visited[pos] = FALSE;
		    if (maze_w[pos][E]) 
			DRAW_E(x, z);
		    if (maze_w[pos][N]) 
			DRAW_N(x, z);
		    if (maze_obj[pos])
		    {
			draw_obj(maze_obj[pos]);
			maze_obj[pos] = NULL;
		    }
		}

		count = rrtop[x];
		for(i=count; i >= 0; i--)
		{
		    z = rrooms[x][i];
		    pos = (z << MSHIFT) + x;
		    visited[pos] = FALSE;
		    if (maze_w[pos][E])
			DRAW_E(x, z);
		    if (maze_w[pos][S]) 
			DRAW_S(x, z);
		    if (z == sz && maze_w[pos][N]) 
			DRAW_N(x, z);
		    if (maze_obj[pos])
		    {
			draw_obj(maze_obj[pos]);
			maze_obj[pos] = NULL;
		    }
		}
		lrtop[x] = -1;
		rrtop[x] = -1;
	    }
	    break;
	case S:
	    for(z=0; z <= sz; z++)
	    {
		count = lrtop[z];
		for(i=count; i >= 0; i--)
		{
		    x = lrooms[z][i];
		    pos = (z << MSHIFT) + x;
		    visited[pos] = FALSE;
		    if (maze_w[pos][S]) 
			DRAW_S(x, z);
		    if (maze_w[pos][E]) 
			DRAW_E(x, z);
		    if (maze_obj[pos])
		    {
			draw_obj(maze_obj[pos]);
			maze_obj[pos] = NULL;
		    }
		}

		count = rrtop[z];
		for(i=count; i >= 0; i--)
		{
		    x = rrooms[z][i];
		    pos = (z << MSHIFT) + x;
		    visited[pos] = FALSE;
		    if (maze_w[pos][S]) 
			DRAW_S(x, z);
		    if (maze_w[pos][W]) 
			DRAW_W(x, z);
		    if (x == sx && maze_w[pos][E]) 
			DRAW_E(x, z);
		    if (maze_obj[pos])
		    {
			draw_obj(maze_obj[pos]);
			maze_obj[pos] = NULL;
		    }
		}
		lrtop[z] = -1;
		rrtop[z] = -1;
	    }
	    break;
	case W:
	    for(x=0; x <= sx; x++)
	    {
		count = lrtop[x];
		for(i=count; i >= 0; i--)
		{
		    z = lrooms[x][i];
		    pos = (z << MSHIFT) + x;
		    visited[pos] = FALSE;
		    if (maze_w[pos][W]) 
			DRAW_W(x, z);
		    if (maze_w[pos][S]) 
			DRAW_S(x, z);
		    if (maze_obj[pos])
		    {
			draw_obj(maze_obj[pos]);
			maze_obj[pos] = NULL;
		    }
		}

		count = rrtop[x];
		for(i=count; i >= 0; i--)
		{
		    z = rrooms[x][i];
		    pos = (z << MSHIFT) + x;
		    visited[pos] = FALSE;
		    if (maze_w[pos][W]) 
			DRAW_W(x, z);
		    if (maze_w[pos][N]) 
			DRAW_N(x, z);
		    if (z == sz && maze_w[pos][S]) 
			DRAW_S(x, z);
		    if (maze_obj[pos])
		    {
			draw_obj(maze_obj[pos]);
			maze_obj[pos] = NULL;
		    }
		}
		lrtop[x] = -1;
		rrtop[x] = -1;
	    }
	    break;
    }
}


read_maze(fname)
    char *fname;
{
    FILE *fp, *fopen();
    register int x, z;
    register int pos;

    if ((fp = fopen(fname, "r")) == NULL)
    {
	fprintf(stderr, "Can't open maze file \"%s\"\n", fname);
	exit(1);
    }

    for (x=0, z=MSIZ-1; x < MSIZ; x++)
    {
	pos = (z << MSHIFT) + x;
	fgetc(fp);
	if (fgetc(fp) == '_')
	    maze_w[pos][N] = 1;
	else
	    maze_w[pos][N] = 0;
    }
    fgetc(fp); /* read the eoln */

    for (z=MSIZ-1; z > 0; z--)
    {
	pos = (z << MSHIFT);
	if (fgetc(fp) == '|')
	    maze_w[pos][W] = 1;
	else
	    maze_w[pos][W] = 0;

	for (x=0; x < MSIZ-1; x++)
	{
	    pos = (z << MSHIFT) + x;
	    if (fgetc(fp) == '_')
	    {
		maze_w[pos][S] = 1;
		maze_w[pos-MSIZ][N] = 1;
	    }
	    else
	    {
		maze_w[pos][S] = 0;
		maze_w[pos-MSIZ][N] = 0;
	    }
	    if (fgetc(fp) == '|')
	    {
		maze_w[pos][E] = 1;
		maze_w[pos+1][W] = 1;
	    }
	    else
	    {
		maze_w[pos][E] = 0;
		maze_w[pos+1][W] = 0;
	    }
	}

	pos = (z << MSHIFT) + x;
	if (fgetc(fp) == '_')
	{
	    maze_w[pos][S] = 1;
	    maze_w[pos-MSIZ][N] = 1;
	}
	else
	{
	    maze_w[pos][S] = 0;
	    maze_w[pos-MSIZ][N] = 0;
	}
	if (fgetc(fp) == '|')
	    maze_w[pos][E] = 1;
	else
	    maze_w[pos][E] = 0;

	fgetc(fp); /* read the eoln */
    }

    pos = 0;
    if (fgetc(fp) == '|')
	maze_w[pos][W] = 1;
    else
	maze_w[pos][W] = 0;

    for (x=0; x < MSIZ-1; x++)
    {
	pos = x;
	if (fgetc(fp) == '_')
	    maze_w[pos][S] = 1;
	else
	    maze_w[pos][S] = 0;
	if (fgetc(fp) == '|')
	{
	    maze_w[pos][E] = 1;
	    maze_w[pos+1][W] = 1;
	}
	else
	{
	    maze_w[pos][E] = 0;
	    maze_w[pos+1][W] = 0;
	}
    }

    pos = x;
    if (fgetc(fp) == '_')
	maze_w[pos][S] = 1;
    else
	maze_w[pos][S] = 0;
    if (fgetc(fp) == '|')
	maze_w[pos][E] = 1;
    else
	maze_w[pos][E] = 0;
    fclose(fp);
}


read_def_maze()
{
    register int x, z;
    register int pos;
    int i = 0, j = 0;

    for (x=0, z=MSIZ-1; x < MSIZ; x++)
    {
	pos = (z << MSHIFT) + x;
	i++;
	if (def_maze[j][i++] == '_')
	    maze_w[pos][N] = 1;
	else
	    maze_w[pos][N] = 0;
    }
    j++;
    i = 0;

    for (z=MSIZ-1; z > 0; z--)
    {
	pos = (z << MSHIFT);
	if (def_maze[j][i++] == '|')
	    maze_w[pos][W] = 1;
	else
	    maze_w[pos][W] = 0;

	for (x=0; x < MSIZ-1; x++)
	{
	    pos = (z << MSHIFT) + x;
	    if (def_maze[j][i++] == '_')
	    {
		maze_w[pos][S] = 1;
		maze_w[pos-MSIZ][N] = 1;
	    }
	    else
	    {
		maze_w[pos][S] = 0;
		maze_w[pos-MSIZ][N] = 0;
	    }
	    if (def_maze[j][i++] == '|')
	    {
		maze_w[pos][E] = 1;
		maze_w[pos+1][W] = 1;
	    }
	    else
	    {
		maze_w[pos][E] = 0;
		maze_w[pos+1][W] = 0;
	    }
	}

	pos = (z << MSHIFT) + x;
	if (def_maze[j][i++] == '_')
	{
	    maze_w[pos][S] = 1;
	    maze_w[pos-MSIZ][N] = 1;
	}
	else
	{
	    maze_w[pos][S] = 0;
	    maze_w[pos-MSIZ][N] = 0;
	}
	if (def_maze[j][i++] == '|')
	    maze_w[pos][E] = 1;
	else
	    maze_w[pos][E] = 0;

	j++;
	i = 0;
    }

    pos = 0;
    if (def_maze[j][i++] == '|')
	maze_w[pos][W] = 1;
    else
	maze_w[pos][W] = 0;

    for (x=0; x < MSIZ-1; x++)
    {
	pos = x;
	if (def_maze[j][i++] == '_')
	    maze_w[pos][S] = 1;
	else
	    maze_w[pos][S] = 0;
	if (def_maze[j][i++] == '|')
	{
	    maze_w[pos][E] = 1;
	    maze_w[pos+1][W] = 1;
	}
	else
	{
	    maze_w[pos][E] = 0;
	    maze_w[pos+1][W] = 0;
	}
    }

    pos = x;
    if (def_maze[j][i++] == '_')
	maze_w[pos][S] = 1;
    else
	maze_w[pos][S] = 0;
    if (def_maze[j][i++] == '|')
	maze_w[pos][E] = 1;
    else
	maze_w[pos][E] = 0;
}
