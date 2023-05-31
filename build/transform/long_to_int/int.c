/*
    orig.c
*/
#include <stdio.h>

/* type is long */
#define MYLONG_T int

MYLONG_T myvar2 = 5;
int myvar = 4;
int myconst = 3;
struct Mystruct {
  int mylong;
  int myint;
  int *mylongptr;
};

int *mylongptr = (int*)0xdeadbeef;

struct Mystruct ms;

int myfunc(int x, int y)
{
    return x + y;
}

int main (int argc, char *argv[])
{
    int foo = myvar;
    ms.mylong = myconst;

    int myint = 42;
    ms.myint = myint;

    int * mylongptrlocal = ms.mylongptr = mylongptr;

    int result = myfunc(ms.mylong, myconst);
    printf("Hello world long = %d,%d,%d,%d,%p\n", foo, myvar, result ,ms.myint,ms.mylongptr);
    printf("size(long)=%d sizeof(int)=%d sizeof(size_t)=%d\n", 
        sizeof(int),sizeof(int),sizeof(size_t));
    return result;
}

