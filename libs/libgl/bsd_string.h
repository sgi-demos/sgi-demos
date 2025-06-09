#ifndef BSD_STRING_H
#define BSD_STRING_H

#include <string.h>

#ifdef _WIN32
// BSD string functions implementation for Windows
static inline size_t strlcpy(char *dst, const char *src, size_t size) {
    size_t srclen = strlen(src);
    if (size > 0) {
        size_t len = (srclen >= size) ? size - 1 : srclen;
        strncpy(dst, src, len);
        dst[len] = '\0';
    }
    return srclen;
}

static inline char* stpcpy(char* dest, const char* src) {
    while ((*dest = *src) != '\0') {
        dest++;
        src++;
    }
    return dest;
}

static char* strsep(char** stringp, const char* delim) {
    char* start = *stringp;
    char* p;

    if (start == NULL)
        return NULL;

    p = start + strcspn(start, delim);

    if (*p) {
        *p++ = 0;
        *stringp = p;
    } else {
        *stringp = NULL;
    }

    return start;
}
#endif /* _WIN32 */
#endif /* BSD_STRING_H */