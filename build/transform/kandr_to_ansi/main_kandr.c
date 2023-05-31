/*
    main_kandr.c

    To convert from K&R style function declarations to ANSI C, use cproto:

    cp main_kandr.c main_ansi.c
    cproto -a -p main_ansi.c

*/
#include <stdio.h>

short 
baby_func (p1, p2)
short p1;
char p2;
{
    return p1 + (short)p2;
}

int 
main (argc, argv)
int argc;
char *argv[];
{
    int foo = 42;
    printf("Hello world %d\n", foo);
}
