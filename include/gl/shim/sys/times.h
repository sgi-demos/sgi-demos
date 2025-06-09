#if defined(_WIN32) && !defined(EMSCRIPTEN)

#ifndef SYS_TIMES_WINDOWS_H_
#define SYS_TIMES_WINDOWS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h> // For clock_t. This is a standard C header and generally safe.

// Definition of struct tms. This needs to be in the header
// as code calling times() will declare variables of this type
// and access its members.
struct tms {
    clock_t tms_utime;  /* user time */
    clock_t tms_stime;  /* system time */
    clock_t tms_cutime; /* user time of children */
    clock_t tms_cstime; /* system time of children */
};

// Declaration of your times() function.
// This is the function that other code will call.
// It will have external linkage.
clock_t times(struct tms *buf);

// The CLK_TCK definition can also go here if user code might need it,
// or it can be solely an implementation detail in the .c file if preferred.
// For consistency with how times() results are interpreted, it's good here.
#ifndef CLK_TCK
    // CLOCKS_PER_SEC is typically 1000 on Windows (ms resolution)
    #define CLK_TCK ((clock_t)CLOCKS_PER_SEC)
#endif

#ifdef __cplusplus
}
#endif

#endif // SYS_TIMES_WINDOWS_H_
#endif // _WIN32 && !EMSCRIPTEN
