/*
    orig.c
*/
#include <stdio.h>

/* type is long */
#define MYLONG_T long

MYLONG_T myvar2 = 5;
long myvar = 4;
long myconst = 3;
struct Mystruct {
  long mylong;
  int myint;
  long *mylongptr;
};

long *mylongptr = (long*)0xdeadbeef;

struct Mystruct ms;

long myfunc(long x, long y)
{
    return x + y;
}

int main (int argc, char *argv[])
{
    long foo = myvar;
    ms.mylong = myconst;

    int myint = 42;
    ms.myint = myint;

    long* mylongptrlocal = ms.mylongptr = mylongptr;

    long result = myfunc(ms.mylong, myconst);
    printf("Hello world long = %d,%d,%d,%d,%p\n", foo, myvar, result ,ms.myint,ms.mylongptr);
    printf("size(long)=%d sizeof(int)=%d sizeof(size_t)=%d\n", 
        sizeof(long),sizeof(int),sizeof(size_t));
    return result;
}

