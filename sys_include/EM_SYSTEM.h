
#ifdef __EMSCRIPTEN__
int em_system(const char *command) \
{ \
    char sys_js[256]; \
    snprintf (sys_js, 256, "window.location.href = 'https://sgi-demos.github.io/sgi-demos/%s';",command); \
    printf("sys_js=%s\n",sys_js); \
    extern void emscripten_run_script(const char *); \
    emscripten_run_script(sys_js); \
}
#else
int em_system(const char *command) \
{ \
    system(command); \
}
#endif

#define system em_system
