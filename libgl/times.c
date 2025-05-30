// Shim for sys/times.h times() on Windows

#if defined(_WIN32) && !defined(EMSCRIPTEN)

#include "gl/shim/sys/times.h"
#include <windows.h> 

static clock_t filetime_to_clock_t(FILETIME ft) {
    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    // Convert 100ns units to CLK_TCK units
    // If CLK_TCK is 1000 (ms), this is uli.QuadPart / 10000
    return (clock_t)(uli.QuadPart / (10000000ULL / CLK_TCK));
}

// Definition of the times() function.
// This function will have external linkage.
clock_t times(struct tms *buf) {
    ULONGLONG current_ticks_val;
    // GetTickCount64() returns milliseconds since system boot.
    ULONGLONG ms_since_boot = GetTickCount64();

    // Convert milliseconds to CLK_TCK units for the return value.
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
            // On error, or if times are not available, fill with 0
            // This is a reasonable fallback.
            buf->tms_utime = 0;
            buf->tms_stime = 0;
        }
        // Child process times are not easily or directly mapped from Windows.
        // Stub them to 0, which is common for such shims.
        buf->tms_cutime = 0;
        buf->tms_cstime = 0;
    }
    // POSIX specifies that times() returns the current time even if buf is NULL.
    // If buf was NULL and filling was strictly required before returning time,
    // and an error occurred during a hypothetical fill, one might return (clock_t)-1.
    // However, this implementation prioritizes returning the current time.
    // An error in GetProcessTimes() above only affects the buffer, not GetTickCount64().
    return (clock_t)current_ticks_val;
}

#endif // _WIN32 && !EMSCRIPTEN
