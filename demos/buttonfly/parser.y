%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buttonfly.h"
button_struct *current_button;
extern button_struct *buttons_input;
extern button_struct *selected;

button_struct *new_button(char *s);
char *strip(char *s);

%}

%union
{
	button_struct *b;
	popup_struct *p;
	char *string;
}

%start starting

/*
 * These tokens are returned by the lexer (lexer.c) -- add more as
 * needed, but be sure to change the dot_tokens and token_num arrays
 * below and NUM_TOKENS in buttonfly.h
 */
%token <string> MENU POPUP COLOR BACKCOLOR HIGHCOLOR

%token <string> ACTION TITLE
%type <b> starting defaults default
%type <b> buttons button
%type <p> popup
%type <string> commands command actions

%%

starting :
	    defaults buttons	{ $$ = NULL; }
	|   buttons { $$ = NULL; }
	;

defaults:	default   { $$ = NULL; }
	|	defaults default    { $$ = NULL; }

default:	COLOR
		{
		    do_color($1, selected->default_color, ".color.");
		    /*do_color($1, selected->color, ".color.");*/
		    $$ = NULL;
		}
	|	BACKCOLOR
		{
		    do_color($1, selected->default_backcolor, ".backcolor.");
		    do_color($1, selected->backcolor, ".backcolor.");
		    $$ = NULL;
		}
	|	HIGHCOLOR
		{
		    do_color($1, selected->default_highcolor, ".highcolor.");
		    /*do_color($1, selected->highcolor, ".highcolor.");*/
		    $$ = NULL;
		}
	|	popup
		{
			if (selected->popup == NULL)
				selected->popup = $1;
			else
			{
				$1->next = selected->popup;
				selected->popup = $1;
			}
			$$ = NULL;
		}
	|	actions
		{
			fprintf(stderr, "\ncough, gasp, ack, pbht!\n");
fprintf(stderr, "buttonfly: can't put an action before a button in a menu file.\n");
			$$ = NULL;
		}
	;

buttons :	button
		{
			buttons_input = $1 ;
			$$ = $1;
		}
	|	buttons button
		{
			$2->next = $1;
			buttons_input = $2 ;
			$$ = $2;
		}
	|	error
		{
			buttons_input = NULL;
			$$ = NULL;
		}
	;

button :	TITLE
		{
			/* Create a 'button' structure here */
			current_button = new_button($1);
			$<b>$ = current_button;
		}
		commands
		{
			/* Commands all add to current_button's structure */
			$$ = $<b>2;
		}
	;

commands : command
	|	commands command	{ $$ = NULL; }
	;

command : actions
		{
			if (current_button->action == NULL)
			{	/* No actions before... */
				current_button->action = $1;
			}
			else if ($1 != NULL)
			{	/* Add to list of actions */
				char *cat_strings();
				cat_strings(current_button->action,	";");
				cat_strings(current_button->action, $1);
			}
			$$ = NULL;
		}
	|	MENU
		{
			if (current_button->submenu != NULL)
			{
				fprintf(stderr, "Warning: two submenus specicied for");
				fprintf(stderr, " menu %s\n", current_button->name[0]);
				free(current_button->submenu);
			}
			current_button->submenu = strip($1);
			$$ = NULL;
		}
	|	COLOR
		{
			do_color($1, current_button->color, ".color.");
			$$ = NULL;
		}
	|	BACKCOLOR
		{
			do_color($1, current_button->backcolor, ".backcolor.");
			$$ = NULL;
		}
	|	HIGHCOLOR
		{
			do_color($1, current_button->highcolor, ".highcolor.");
			$$ = NULL;
		}
	|	popup
		{
			if (current_button->popup == NULL)
				current_button->popup = $1;
			else
			{
				$1->next = current_button->popup;
				current_button->popup = $1;
			}
			$$ = NULL;
		}
	;

popup :	POPUP actions
		{
			popup_struct *p;
			p = (popup_struct *)malloc(sizeof(popup_struct));
			p->title = $1 +1; /* +1 to account for space after .popup. */
			p->action = $2;
			p->next = NULL;
			$$ = p;
		}
		;

actions :	ACTION
		{	/* Return a single string */
			$$ = $1;
		}
	|	actions ACTION
		{	/* Return strings separated by ';' */
			char *t, *cat_strings();
			t = cat_strings($1, ";");
			t = cat_strings(t, $2);
			free($2);
			$$ = t;
		}
	|
		{	/* Null action */
			$$ = NULL;
		}
	;
%%
/* Subroutines used by rules above */

/*
 * If more .whatever. tokens are added, change the following two
 * arrays, the %token <string> command below, and NUM_TOKENS in
 * buttonfly.h
 */
int token_nums[NUM_TOKENS] =
{
	MENU,
	POPUP, 
	COLOR,
	BACKCOLOR,
	HIGHCOLOR,
};
char *dot_tokens[NUM_TOKENS] =
{
	".menu.",
	".popup.",
	".color.",
	".backcolor.",
	".highcolor.",
};

button_struct *new_button(s)
char *s;
{
	button_struct *result;
	int i;

	result = (button_struct *)malloc(sizeof(button_struct));
	result->name[0][0] = '\0';
	result->name[1][0] = '\0';
	result->name[2][0] = '\0';
	result->wc = 0;
	find_words(0, s, result);
	result->action = result->submenu = NULL;
	result->popup = NULL;
	if (selected) for (i=0; i<3; i++) {
	    result->color[i] = selected->default_color[i];
	    result->backcolor[i] = selected->default_backcolor[i];
	    result->highcolor[i] = selected->default_highcolor[i];
	    result->default_color[i] = selected->default_color[i];
	    result->default_backcolor[i] = selected->default_backcolor[i];
	    result->default_highcolor[i] = selected->default_highcolor[i];
	} else for (i=0; i<3; i++) {
	    result->color[i] = 0.7;
	    result->highcolor[i] = 1.0;
	    result->backcolor[i] = 0.0;
	    result->default_color[i] = 0.7;
	    result->default_highcolor[i] = 1.0;
	    result->default_backcolor[i] = 0.0;
	}
	result->next = result->forward = NULL;
	return result;
}


char *cat_strings(s1, s2)
char *s1, *s2;
{
	s1 = realloc(s1, strlen(s1)+strlen(s2)+1);
	strcat(s1, s2);
	return s1;
}

/*
 *	Strip of leading and trailing spaces and tabs
 */
char *
strip(s)
char *s;
{
	int i, j;
	
	/* Ok, handle beginning of string */
	if ((i = strspn(s, " \t")) != 0)
	{
		for (j = i; j < (strlen(s)+1); j++)
			s[j-i] = s[j];
	}
	/* Now handle end */
	for (i = strlen(s); i > 0; i--)
	{
		if (s[i] == ' ' || s[i] == '\t')
			s[i] = '\0';
		else
			break;
	}
	return s;
}

yyerror()
{
	/* In case of error... be quiet.
	 *	fprintf(stderr, "Syntax Error\n");
	 */
}

find_words(n, str, button)
int n;
char *str;
button_struct *button;
{
    int i;

    button->wc++;
    if (strlen(str)<WORDLENGTH+1)
	{
		strcpy(button->name[n], str);
    } 
	else
	{
		i=WORDLENGTH+1;
		while ((--i)>0 && str[i]!=' ');
		if (i)
		{
		    strncpy(button->name[n], str, i);
		    button->name[n][i]=0;
                    // LK: Replacing strcpy() with memmove() because overlapping
                    // strcpy() on MacOS can cause an abort:
		    // strcpy(str, str+i+1);
		    memmove(str, str+i+1, strlen(str+i+1)+1);
		    if (n<2) find_words(n+1, str, button);
		}
		else
		{
		    strncpy(button->name[n], str, WORDLENGTH);
		    button->name[n][WORDLENGTH]=0;
		    if (n<2)
			{
				for (i=WORDLENGTH; str[i]!=' ' && str[i]; i++);
				if (i<strlen(str))
				{
				    strcpy(str, str+i+1);
				    find_words(n+1, str, button);
				}
		    }
		}
    }
}


do_color(s, c, e)
char *s;
float *c;
char *e;
{
    float r, g, b;

    if (sscanf(s, "%f %f %f", &r, &g, &b) != 3) {

	fprintf(stderr, "buttonfly: syntax error: %s\n", e);

    } else {

	c[0] = r;
	c[1] = g;
	c[2] = b;
    }
}
