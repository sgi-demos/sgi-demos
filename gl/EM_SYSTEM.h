#ifndef EM_SYSTEM_H
#define EM_SYSTEM_H 1

#ifdef __EMSCRIPTEN__
// Invoke the demo web page
int em_system(const char *command) \
{ \
    char sys_js[256]; \
    snprintf (sys_js, 256, "window.location.href = 'https://sgi-demos.github.io/sgi-demos/%s';",command); \
    printf("sys_js=%s\n",sys_js); \
    extern void emscripten_run_script(const char *); \
    emscripten_run_script(sys_js); \
}
#else
// Invoke the demo binary
int em_system(const char *command) \
{ \
    system(command); \
}
#endif

#define system em_system

//
// Various workarounds for 1980s code
// Fun fact: Private Eyes by Hall and Oates was the #1 song in the US on 9 Nov 1981, the day of SGI's founding
// 

// Avoid promoting signed values to unsigned when mixing 
// strlen() in arithmetic expressions
int strlen32(const char *s)
{
    return strlen(s);
}
#define strlen strlen32

// Just want a double between 0.0 and 1.0
#define drand48() ((float)rand()/(float)(RAND_MAX))
#define srand48(s) (srand(s+1))

#endif // EM_SYSTEM_H