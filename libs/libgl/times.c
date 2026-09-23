// Shim for sys/times.h times() on Windows and Emscripten

#if defined(__EMSCRIPTEN__)

#include <sys/times.h>
#include <emscripten.h>

// Emscripten's musl times() does not advance, so flight's ticks-per-second
// estimate (frames per times()-tick) explodes ~100x per measurement and the
// integer engine-thrust ramp (thrust += 50/tps) truncates to zero — frozen
// physics. Provide a real one: wall clock in 100Hz ticks (the IRIX HZ both
// flight demos are built with, matching -DHZ=100). Emscripten's libstubs owns
// the times symbol (wasm-ld: duplicate), so this lives under its own name;
// demo web compiles redirect with -Dtimes=sgi_demos_times (platform.mk).
clock_t sgi_demos_times(struct tms *buf)
{
    double ms = emscripten_get_now();
    clock_t t = (clock_t)(ms / 10.0);   // 100 ticks per second
    if (buf) {
        buf->tms_utime = t;
        buf->tms_stime = 0;
        buf->tms_cutime = 0;
        buf->tms_cstime = 0;
    }
    return t;
}

#elif defined(_WIN32) && !defined(EMSCRIPTEN)

#include "sys/times.h"
#include <windows.h> 

static clock_t filetime_to_clock_t(FILETIME ft) {
    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    // 100ns units to CLK_TCK ticks
    return (clock_t)(uli.QuadPart / (10000000ULL / CLK_TCK));
}

// Windows has no times(): elapsed time since boot, and this process's user
// and kernel CPU time (children's are 0)
clock_t times(struct tms *buf) {
    ULONGLONG current_ticks_val;
    ULONGLONG ms_since_boot = GetTickCount64();

    if (CLK_TCK == 1000) { // Common case: 1 tick = 1 millisecond
        current_ticks_val = ms_since_boot;
    } else {
        current_ticks_val = (ms_since_boot * CLK_TCK / 1000);
    }

    if (buf != NULL) {
        FILETIME ftCreationTime_unused, ftExitTime_unused, ftKernelTime, ftUserTime;

        if (GetProcessTimes(GetCurrentProcess(), &ftCreationTime_unused, &ftExitTime_unused, &ftKernelTime, &ftUserTime)) {
            buf->tms_utime = filetime_to_clock_t(ftUserTime);
            buf->tms_stime = filetime_to_clock_t(ftKernelTime);
        } else {
            buf->tms_utime = 0;
            buf->tms_stime = 0;
        }
        buf->tms_cutime = 0;
        buf->tms_cstime = 0;
    }
    return (clock_t)current_ticks_val;
}

#endif // _WIN32 && !EMSCRIPTEN
