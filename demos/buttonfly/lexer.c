/*
 *	A very simple lexical analyzer for buttonfly.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buttonfly.h"
#include "parser.tab.h"

/*
 *	Externally visible globals, used to communicate between
 * parser/lexer and the main buttonfly.c routines.
 */
FILE *lex_fp;
button_struct *buttons_input;

int
yylex()
{
    char *get_line();
    int c;

    while (1) {

	while ((c = fgetc(lex_fp)) == '\n')
		;	/* Eat blank lines */
	/* First character on line decides what to do */
	switch(c)
	{
		case EOF:
			return 0;

		case '\t':
			return parse_action(get_line(lex_fp));

		case '#':
			/* Eat Comments -- free space used in reading in */
			free(get_line(lex_fp));
			break;

		default:
			ungetc(c, lex_fp);
			yylval.string = get_line(lex_fp);
			return TITLE;
	}
    }
}

/*
 *	mallocs and reads in to end of line, returning resulting string
 */
char *
get_line(fp)
FILE *fp;
{
	char *c;
	int count, in;

	count = 1;
	c = malloc(count);
	for (in = fgetc(fp) ; in != EOF && in != '\n' ;
		in = fgetc(fp))
	{
		c[count-1] = (char) in ;
		++count ;
		c = realloc(c, count);
	}
	c[count-1] = '\0' ;
	return c;
}
/*
 *	Decides if a given string matches a special keyword, or is just a
 * generic action.
 */
int
parse_action(c)
char *c;
{
	int i;

	/* Ok, look for special keywords... */
	for (i = 0 ; i < NUM_TOKENS ; i++)
	{
		int ssize ;
		ssize = strlen(dot_tokens[i]) ;
		if (strncmp(c, dot_tokens[i],ssize) == 0)
		{	/* Matched! */
			yylval.string = malloc(strlen(c+ssize) + 1) ;
			strcpy(yylval.string, c+ssize) ;
			free(c) ;
			return token_nums[i];
		}
	}
	/* No match, nothing special, just a generic action */
	yylval.string = c ;
	return ACTION;
}
