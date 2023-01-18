#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gl.h>
#include <math.h>
#include <device.h>
#include <time.h>
#include "event.h"
#include "bartfont.h"
#include "buttonfly.h"
#include "data.h"

// Stop at the slow frame in the animation so we can analyze it.
#define BLOCK_AT_SLOW_FRAME 0

#define X 0
#define Y 1
#define Z 2

short dev,val;
long originx, originy, sizex, sizey;
long s_originx, s_originy, s_sizex, s_sizey;

int flyinflag = 0;
int flyoutflag = 0;
int selectflag = 0;
int exitflag = 0;

static int esc_pressed = 0;
static struct timespec esc_press_time;

button_struct *load_buttons(), *which_button();
extern button_struct *new_button(char *);

button_struct *current_buttons=NULL, *selected=NULL, *secret_buttons=NULL;

path_struct *path=NULL;

button_struct *rootbutton;

float *curbackcolor;	/* current background color */

/* matrix for projecting next set of buttons
   on the back of the selected button */

float tv[4][4] = {

    {SCREEN, 0.0, 0.0, 0.0},
    {0.0, SCREEN, 0.0, 0.0},
    {0.0, 0.0, SCREEN, -1.0},
    {0.0, 0.0, 0.0, 0.0},
};

void bf_redraw(), bf_exit(), bf_selecting(), bf_deselect();
void bf_quick(), bf_fly(), do_popup(), toggle_window();
void bf_escdown(), bf_escup();
void flyindraw(), flyoutdraw(), selectdraw();
void parse_args(), doclear();

static double diff_timespecs(struct timespec *t1, struct timespec *t2) {
    return (t1->tv_sec - t2->tv_sec) + (t1->tv_nsec - t2->tv_nsec)/1000000000.0;
}

main (argc, argv)
int	argc;
char	*argv[];
{
    rootbutton = new_button("");
    selected = rootbutton;
    parse_args(argc, argv);
    selected = NULL;

    keepaspect(5, 4);

    {
	char *t, *strrchr();
	winopen((t=strrchr(argv[0], '/')) != NULL ? t+1 : argv[0]);
    }
	if (getplanes() < 12)
	{
		fprintf(stderr, "You must have at least 12 bitplane to run %s",
			argv[0]);
		gexit();
		exit(1);
	}

    getorigin(&originx, &originy);
    getsize(&sizex, &sizey);

    winattach();
    doublebuffer();
    RGBmode();
    gconfig();

    backface(TRUE);

    shademodel(FLAT);

    lmdef(DEFMATERIAL, 1, 0, mat);
    lmdef(DEFLIGHT, 1, 0, light1);
    lmdef(DEFLIGHT, 2, 0, light2);
    lmdef(DEFLMODEL, 1, 0, light_model);

	qdevice(REDRAW);
	add_event(ANY, REDRAW, ANY, bf_redraw, 0);

    qdevice(ESCKEY);
	add_event(ANY, ESCKEY, DOWN, bf_escdown, 0);
	add_event(ANY, ESCKEY, UP, bf_escup, 0);

	qdevice(WINQUIT);
	add_event(ANY, WINQUIT, ANY, bf_exit, 0);

    qdevice(MIDDLEMOUSE);
    tie(MIDDLEMOUSE, MOUSEX, MOUSEY);
	add_event(ANY, MIDDLEMOUSE, DOWN, bf_selecting, 0);
	add_event(ANY, MIDDLEMOUSE, UP, bf_quick, 0);

    qdevice(LEFTMOUSE);
    tie(LEFTMOUSE, MOUSEX, MOUSEY);
	add_event(ANY, LEFTMOUSE, DOWN, bf_selecting, 0);
	add_event(ANY, LEFTMOUSE, UP, bf_fly, 0);

	qdevice(RIGHTMOUSE);
	tie(RIGHTMOUSE, MOUSEX, MOUSEY);
	add_event(ANY, RIGHTMOUSE, DOWN, do_popup, 0);

#if 0  // LK: We don't want windowed mode.
    qdevice(SPACEKEY);
	add_event(ANY, SPACEKEY, UP, toggle_window, 0);
#endif

	add_update(&flyinflag, flyindraw, 0);
	add_update(&flyoutflag, flyoutdraw, 0);
	add_update(&selectflag, selectdraw, 0);

    mmode(MPROJECTION);

    perspective(450, (float)XMAXSCREEN/YMAXSCREEN, THICK, 9.0);
    translate(0.0, 0.0, -5.0/4.0);

    mmode(MVIEWING);
    loadmatrix(idmat);

    curbackcolor=rootbutton->backcolor;
    doclear();

    draw_buttons(current_buttons);
    swapbuffers();

	while(exitflag == FALSE)
	{
		event();
	}
	gexit();
	exit(0);
}

button_struct *load_buttons_from_file(char *program_name, char *filename)
{
    button_struct *buttons;
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "%s: can't open file %s\n",
                program_name, filename);
        exit(1);
    }
    buttons = load_buttons(fp);
    fclose(fp);

    return buttons;
}

void parse_args(argc, argv)
int argc;
char **argv;
{
    if (argc>3) {
        fprintf(stderr, "usage: %s [infile] [secretfile]\n", argv[0]);
        exit(1);
    } else if (argc == 3) {
        current_buttons = load_buttons_from_file(argv[0], argv[1]);
        secret_buttons = load_buttons_from_file(argv[0], argv[2]);
    } else if (argc == 2) {
        current_buttons = load_buttons_from_file(argv[0], argv[1]);
    } else {
        current_buttons = load_buttons_from_file(argv[0], ".menu");
    }
}


void bf_exit()
{
	exitflag = TRUE;
}


void  bf_selecting()
{
	short mx, my;
    qread(&mx); qread(&my);	/* Yank off queue */
	selectflag = TRUE;
	flyinflag = flyoutflag = FALSE;
}


/*
 *	Middle mouse up == quick selection, no flipping
 */
void bf_quick()
{
	short mx, my;
    qread(&mx); qread(&my);	/* Yank off queue */

	selectflag = flyinflag = flyoutflag = FALSE;
	selected = which_button(mx, my);
	if (selected) {
		push_button(selected);
		if (selected->forward) {
			add_button_to_path(current_buttons, selected);
			current_buttons = selected->forward;
		}
		selected = NULL;
	}
	else if (path) {
	    path_struct *step;
	    selected = path->button;
	    draw_selected_button(selected, 1.0);
	    selected = NULL;
	    current_buttons = path->current_buttons;
	    step = path;
	    path = path->back;
	    free(step);
	    if (path) curbackcolor=path->button->backcolor;
	    else curbackcolor=rootbutton->backcolor;
	}
	bf_redraw();
}

void bf_escdown()
{
    // Keep track of when Esc is pressed so we can see how long it was pressed.
    if (!esc_pressed) {
        esc_pressed = 1;
        clock_gettime(CLOCK_MONOTONIC, &esc_press_time);
    }
}

void bf_escup()
{
    // See how long Esc was pressed.
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    double elapsed = diff_timespecs(&now, &esc_press_time);
    if (elapsed > 1 && secret_buttons != NULL) {
        // Show secret menu.
	selectflag = flyinflag = flyoutflag = FALSE;
        add_button_to_path(current_buttons, secret_buttons);
        current_buttons = secret_buttons;
	bf_redraw();
    } else {
        bf_deselect();
    }
    esc_pressed = 0;
}

void bf_deselect()
{
    if (path) {
	path_struct *step;
	flyoutflag = TRUE;
	selected = path->button;
	current_buttons = path->current_buttons;
	step = path;
	path = path->back;
	free(step);
	if (path) curbackcolor=path->button->backcolor;
	else curbackcolor=rootbutton->backcolor;
    }
}

void bf_fly()
{
	short mx, my;
    qread(&mx); qread(&my);	/* Yank off queue */

	selectflag = flyinflag = flyoutflag = FALSE;
	selected = which_button(mx, my);
	if (selected) {
		push_button(selected);
		if (selected->forward) {
		    add_button_to_path(current_buttons, selected);
		    flyinflag = TRUE;
		}
		else {
		    selected = NULL;
		    bf_redraw();
		}
	}
	else if (path) {
	    path_struct *step;
	    flyoutflag = TRUE;
	    selected = path->button;
	    current_buttons = path->current_buttons;
	    step = path;
	    path = path->back;
	    free(step);
	    if (path) curbackcolor=path->button->backcolor;
	    else curbackcolor=rootbutton->backcolor;
	}
}


void bf_redraw()
{
    reshapeviewport();
    getorigin(&originx, &originy);
    getsize(&sizex, &sizey);
    doclear();
    draw_buttons(current_buttons);
    swapbuffers();
}


#define BIG	0
#define LITTLE	1
void  toggle_window()
{
	static int size=LITTLE;

	if (size==BIG) {
		size = LITTLE;
	    winposition(s_originx, s_originx+s_sizex,
			s_originy, s_originy+s_sizey);
	    reshapeviewport();
	    keepaspect(XMAXSCREEN, YMAXSCREEN);
	    winconstraints();
	    getorigin(&originx, &originy);
	    getsize(&sizex, &sizey);
	} else {
	    size = BIG;
	    getorigin(&s_originx, &s_originy);
	    getsize(&s_sizex, &s_sizey);
	    winposition(0, XMAXSCREEN, 0, YMAXSCREEN);
	    reshapeviewport();
	    prefposition(0, XMAXSCREEN, 0, YMAXSCREEN);
	    winconstraints();
	    originx=0; originy=0;
	    sizex=XMAXSCREEN; sizey=YMAXSCREEN;
	}
}


void  do_popup()
{
	short mx, my;
	button_struct *b;
	void do_buttons_menu();
	
	qread(&mx); qread(&my);
	b = which_button(mx, my);
	if (b)
	{
		do_buttons_menu(b, mx, my);
	}
	else if (path)
	{
		do_buttons_menu(path->button, mx, my);
	}
	else if (rootbutton->popup)
	{
		do_buttons_menu(rootbutton, mx, my);
	}
}


void do_buttons_menu(b, mx, my)
button_struct *b;
short mx, my;
{
	long menu;
	int i, num;
	char t[128];
	popup_struct *scan;
	
	menu = newpup();

	if (b != rootbutton) {
		sprintf(t, "Do It");
	        addtopup(menu, t);
	}

	for (num=0, scan=b->popup; scan != NULL; num++, scan=scan->next) {

		sprintf(t, "%s%%x%d", scan->title, num+2);
		addtopup(menu, t);
	}

	i = dopup(menu);
	freepup(menu);

	if (i == 1) {	/* Execute button */

		qenter(LEFTMOUSE, UP);
		qenter(MOUSEX, mx);
		qenter(MOUSEY, my);

	} else if ((i > 1) && (i <= num+1)) {

		for (num=0, scan=b->popup; num != (i-2);
		     num++, scan=scan->next)
		;	/* Keep on scanning... */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
		system(scan->action);
#pragma GCC diagnostic pop
	}
}


void selectdraw()
{
	doclear();
	draw_buttons(current_buttons);
	draw_highlighted_button(which_button(
		getvaluator(MOUSEX), getvaluator(MOUSEY)));
	swapbuffers();
}


void flyindraw()
{
	static float t = 1.0;
	if (t > 0.2 || !BLOCK_AT_SLOW_FRAME) {
	    t -= 0.02;
	}
	if (t<=0.0) {
	    current_buttons = selected->forward;
	    selected=NULL;
	    flyinflag = 0;
	    t=1.0;
	    curbackcolor = path->button->backcolor;
	    doclear();
	    draw_buttons(current_buttons);
	} else {
	    doclear();
	    draw_buttons(current_buttons);
	    draw_selected_button(selected, t);
	}
	swapbuffers();
}


void flyoutdraw()
{
	static float t = 0.0;

	doclear();

	t += 0.02;
	if (t>=1.0) {
	    t = 0.0;
	    selected = NULL;
	    flyoutflag = 0;
	    draw_buttons(current_buttons);
	} else {
		    draw_buttons(current_buttons);
		    draw_selected_button(selected, t);
	}
	swapbuffers();
}


/*
 *	This is called to do whatever action is required when a button is
 * pushed.  It just mucks with the button given to it.
 */
push_button(selected)
button_struct *selected;
{
	int needpipe;
	FILE *fp;

	/* Need to open a pipe if submenu == "-" */
	if ((selected->submenu != NULL) && 
		(strcmp(selected->submenu, "-") == 0))
			needpipe = 1;
	else needpipe = 0;

	/* First, figure out where we'll build submenus from */
	fp = NULL;
	if ((selected->action != NULL) && needpipe)
	{
		/* This performs the action, saving output */
		fp = popen(selected->action, "r");
	}
	else if (selected->submenu != NULL)
	{
		fp = fopen(selected->submenu, "r");
	}
	/* Now, do action */
	if ((selected->action != NULL) && !needpipe)
	{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
		system(selected->action);
#pragma GCC diagnostic pop
	}
	/* Ok, now build submenus if we can */
	if (fp != NULL)
	{
		selected->forward = load_buttons(fp);
		if (needpipe)
			pclose(fp);
		else fclose(fp);
	}
}

draw_buttons(buttons)
button_struct *buttons;
{
    lmbind(LIGHT1, 1);
    lmbind(MATERIAL, 1);
/*    lmbind(LIGHT2, 2); */

    if (buttons) do {
	if (buttons!=selected) draw_button(buttons);
    } while((buttons=buttons->next) != 0);
}


draw_button(button)
button_struct *button;
{
	float r=1.0, g=1.0, b=1.0;
	pushmatrix();

	tmp_mat[1] = tmp_mat[5] = button->color[0];
	tmp_mat[2] = tmp_mat[6] = button->color[1];
	tmp_mat[3] = tmp_mat[7] = button->color[2];
	lmdef(DEFMATERIAL, 1, 0, tmp_mat);

	translate(button->tx, button->ty, button->tz);

	rotate(button->ax, 'x');
/*	rotate(button->ay, 'y');*/
	rotate(button->az, 'z');

	draw_edge();

	draw_front(button);

	popmatrix();
}


draw_highlighted_button(button)
button_struct *button;
{
    if (button) {

	tmp_mat[1] = tmp_mat[5] = button->highcolor[0];
	tmp_mat[2] = tmp_mat[6] = button->highcolor[1];
	tmp_mat[3] = tmp_mat[7] = button->highcolor[2];
	lmdef(DEFMATERIAL, 1, 0, tmp_mat);

	pushmatrix();

	translate(button->tx, button->ty, button->tz);

	rotate(button->ax, 'x');
	rotate(button->az, 'z');

	draw_edge();
	draw_front(button);

	popmatrix();
    }
}


draw_selected_button(button, t)
button_struct *button;
float t;
{
    float gls, glc;
    Angle ax, ay, az;
    float tx, ty, tz;
    int bc[3], i;


    pushmatrix();

    ax = (Angle)((float)button->ax*t);
/*	ay = (Angle)((float)button->ay*t);*/
    az = (Angle)((float)button->az*t);

    tx = t*button->tx;
    ty = t*button->ty;
    tz = t*button->tz;

    translate(tx, ty, tz);

    rotate(ax, 'x');
/*	rotate(ay, 'y'); */
    rotate(az, 'z');

    if (flyinflag) {

	tmp_mat[1] = tmp_mat[5] = button->highcolor[0];
	tmp_mat[2] = tmp_mat[6] = button->highcolor[1];
	tmp_mat[3] = tmp_mat[7] = button->highcolor[2];

    } else {

	tmp_mat[1] = tmp_mat[5] = button->color[0];
	tmp_mat[2] = tmp_mat[6] = button->color[1];
	tmp_mat[3] = tmp_mat[7] = button->color[2];
    }

    lmdef(DEFMATERIAL, 1, 0, tmp_mat);

    draw_edge();

    gl_sincos(ax-900, &gls, &glc);

    if (gls<glc*ty/(-tz+SCREEN+THICK)) {

	    /* draw back of button */

	    pushmatrix();

	    for (i=0; i<3; i++)
		bc[i] = (int)(t*255.0 + (1.0-t)*selected->backcolor[i]*255.0);


	    RGBcolor(bc[0], bc[1], bc[2]);

	    bgnpolygon();
		v3f(back_polys[0][0]);
		v3f(back_polys[0][1]);
		v3f(back_polys[0][2]);
		v3f(back_polys[0][3]);
	    endpolygon();

	    translate(0.0, 0.0, THICK);

	    translate(0.0, 0.0, SCREEN);
	    multmatrix (tv);
	    translate(0.0, 0.0, -SCREEN-THICK);

	    draw_buttons(button->forward);

	    popmatrix();

    } else {

	    draw_front(button);
    }

    popmatrix();

}


button_struct *load_buttons(fp)
FILE *fp;
{
	button_struct *scan;
	int nb, i;
	extern FILE *lex_fp;
	extern button_struct *buttons_input;

	lex_fp = fp;
	yyparse();

	nb = 0;	/* Figure out how many buttons were made */
	for (scan = buttons_input; scan != NULL; scan = scan->next)
		++nb;

	if (nb > MAX_SPOTS)
	{
		fprintf(stderr,
		    "Buttonfly Warning: %d is too many buttons\n", nb);
		fprintf(stderr, "(Maximum number is %d)\n", MAX_SPOTS);
		return NULL;
	}

	i = 0;	/* And now figure out where to put them */
	for (scan = buttons_input; scan != NULL; scan = scan->next)
	{
		scan->tx = spots[nb-1][i+0];
		scan->ty = spots[nb-1][i+1];
		scan->tz = spots[nb-1][i+2];
		i += 3;
		scan->ax = (int)(random(1.0)+0.5)*3600-1800;
		scan->ay = 0;
		scan->az = (int)(random(1.0)+0.5)*3600-1800;
	}
	return buttons_input;
}


stroke(str)
char *str;
{
    register int i, j;
    int nextv;

    while (*str) {

	if (chrtbl[*str][0][0]) {

	    i=0;

	    while ((j=chrtbl[*str][i][0]) != 0) {

		switch (j) {

		    case 3:
			rmv2i(chrtbl[*str][i][1], chrtbl[*str][i][2]);
			break;

		    case 2:
			rdr2i(chrtbl[*str][i][1], chrtbl[*str][i][2]);
			break;
		}
		i++;
	    }
	}
	str++;
    }
}


draw_button_label(button)
button_struct *button;
{

    RGBcolor(200, 200, 200);
    RGBcolor(255, 255, 255);

    scale(-0.015, 0.015, 0.015);

    // linewidth(sizex*3/1000 + 1);
    linewidth((sizex*3/1000 + 1) * 800 / 1280);

    switch (button->wc) {

	case 1:
	    move2i(-6 * (long)strlen(button->name[0])/2, -4);
	    stroke(button->name[0]);
	    break;

	case 2:
	    move2i(-6 * (long)strlen(button->name[0])/2, 1);
	    stroke(button->name[0]);
	    move2i(-6 * (long)strlen(button->name[1])/2, -9);
	    stroke(button->name[1]);
	    break;

	case 3:
	    move2i(-6 * (long)strlen(button->name[0])/2, 6);
	    stroke(button->name[0]);
	    move2i(-6 * (long)strlen(button->name[1])/2, -4);
	    stroke(button->name[1]);
	    move2i(-6 * (long)strlen(button->name[2])/2, -14);
	    stroke(button->name[2]);
	    break;
    }

    linewidth(1);
}


button_struct *which_button(mx, my)
int mx, my;
{
    float x, y;
    button_struct *button;

    button = current_buttons;

    if (button) do {

	x = (float)(mx-sizex/2-originx)/(float)sizex;
	y = (float)(my-sizey/2-originy)/(float)sizey/1.25;

	x = x * (-button->tz+SCREEN+THICK*2.0);
	y = y * (-button->tz+SCREEN+THICK*2.0);

	if (button->tx-0.625<x && button->tx+0.625>x &&
	    button->ty-0.5<y && button->ty+0.5>y) {

	    return (button);
	}

    } while ((button = button->next) != 0);

    return(NULL);
}


add_button_to_path(current, button)
button_struct *current;
button_struct *button;
{
    path_struct *step;

    step = (path_struct *)malloc(sizeof(path_struct));

    step->current_buttons = current;
    step->button = button;
    step->back = path;
    path = step;
}


draw_edge() {

    int i;

    lmbind(LMODEL, 1);

    for (i=0; i<8; i++) {

	bgnpolygon();
	    n3f(edge_normals[i]);
	    v3f(edge_polys[i][0]);
	    v3f(edge_polys[i][1]);
	    v3f(edge_polys[i][2]);
	    v3f(edge_polys[i][3]);
	endpolygon();
    }

    lmbind(LMODEL, 0);
}


draw_front(button)
button_struct *button;
{

    lmbind(LMODEL, 1);

    bgnpolygon();
	n3f(front_normals[0]);
	v3f(front_polys[0][0]);
	v3f(front_polys[0][1]);
	v3f(front_polys[0][2]);
	v3f(front_polys[0][3]);
    endpolygon();

    lmbind(LMODEL, 0);

    translate(0.0, 0.0, -THICK);

    draw_button_label(button);
}


void doclear() {

    c3f(curbackcolor);
    clear();    
}
