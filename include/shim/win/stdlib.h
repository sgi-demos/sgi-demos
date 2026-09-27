#ifndef STDLIB_SHIM_H_
#define STDLIB_SHIM_H_

// The toolchain's <stdlib.h>, plus the POSIX drand48 family it lacks on
// Windows (ep-1994 seeds and draws its random numbers with them). The
// functions are in libs/libgl/win_posix.c.
#include_next <stdlib.h>

#if defined(_WIN32)

#ifdef __cplusplus
extern "C" {
#endif

double drand48(void);
void srand48(long seedval);

#ifdef __cplusplus
}
#endif

#endif // _WIN32

#endif // STDLIB_SHIM_H_
