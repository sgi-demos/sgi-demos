#ifndef STRINGS_SHIM_H_
#define STRINGS_SHIM_H_

// The toolchain's <strings.h>, plus the BSD memory functions mingw's lacks
// (flight 3.4 uses them). The functions are in libs/libgl/win_posix.c.
#include_next <strings.h>

#if defined(_WIN32)

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void bcopy(const void *src, void *dst, size_t n);
void bzero(void *s, size_t n);
int bcmp(const void *s1, const void *s2, size_t n);

#ifdef __cplusplus
}
#endif

#endif // _WIN32

#endif // STRINGS_SHIM_H_
