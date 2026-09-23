#ifndef SYS_TIMES_SHIM_H_
#define SYS_TIMES_SHIM_H_

#if defined(_WIN32)

#ifdef __cplusplus
extern "C" {
#endif

// POSIX <sys/times.h> for Windows (times() is in libs/libgl/times.c)
#include <time.h>

struct tms {
    clock_t tms_utime;  /* user time */
    clock_t tms_stime;  /* system time */
    clock_t tms_cutime; /* user time of children */
    clock_t tms_cstime; /* system time of children */
};

clock_t times(struct tms *buf);

#ifndef CLK_TCK
    #define CLK_TCK ((clock_t)CLOCKS_PER_SEC)
#endif

#ifdef __cplusplus
}
#endif

#endif // _WIN32

#endif // SYS_TIMES_SHIM_H_
