#ifndef SYS_TIMEB_SHIM_H_
#define SYS_TIMEB_SHIM_H_

// The toolchain's <sys/timeb.h>, minus the name ftime. mingw's <time.h>
// includes this header, and its ftime() declaration collides with flight
// 3.4's global ftime (its time of day in minutes), where POSIX <time.h>
// declares no ftime. No demo calls ftime(); the declaration is renamed
// (its asm label still binds it to the CRT's ftime64) and the name freed.
#if defined(_WIN32)
#define ftime sgi_demos_mingw_ftime
#include_next <sys/timeb.h>
#undef ftime
#else
#include_next <sys/timeb.h>
#endif

#endif // SYS_TIMEB_SHIM_H_
