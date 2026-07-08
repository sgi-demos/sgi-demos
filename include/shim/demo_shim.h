#ifndef DEMO_SHIM_H
#define DEMO_SHIM_H 1

// Pull in all system headers the shims and the demos need, BEFORE any shim
// macros, so the real library declarations are seen first before #define shimming.
#include <stdio.h>
#include <stdlib.h>   // exit, system, rand/srand, drand48/srand48 decls
#include <string.h>   // strlen, strstr, memcpy
#include <stdint.h>   // uint32_t (used by ntohl)

#define MAX_COMMAND_LEN 256

int demo_shim_system(const char *command)
#ifdef DEMO_BUTTONFLY
{
    //
    // Web shim - Transform command line command into web url equivalent, e.g.:
    // "../bounce/bin/bounce ../bounce/x29.bin" ---> "bounce/web/?arg=x29.bin"
    // The page is served from the demo's web/ directory (web/ -> web/index.html),
    // so the URL is just the directory; no per-demo html filename to track.
    // NOTE: This still gets compiled in the native path for debugging and maintenance purposes.
    //
    printf ("command = %s\n", command);
    if (strlen(command) >= MAX_COMMAND_LEN)
        return -1;

    // copy command into url, trim "../"
    char url[MAX_COMMAND_LEN] = "";
    const char* dotdot = strstr(command, "../");
    if (dotdot)
    {
        int n = snprintf(url, sizeof(url), "%s", command+strlen("../"));
        if (n < 0 || (size_t)n >= sizeof(url))
            return -1;
    }
    else
        return -1;

    // replace "/bin/" with "/web/"
    char* rep_bin = strstr(url, "/bin/");
    if (rep_bin)
        memcpy(rep_bin, "/web/", 5);
    else
        return -1;

    // extract parameter from full command string
    char param[128] = "";
    char* rep_dotdot = strstr(url, " ../");
    if (rep_dotdot)
    {
        rep_dotdot[0] = 0;
        const char *param_to_extract = rep_dotdot + strlen(" ../");
        // strip any preceding path so just the basename remains, e.g. "x29.bin"
        const char *slash = strrchr(param_to_extract, '/');
        if (slash)
            param_to_extract = slash + 1;
        snprintf(param, sizeof(param), "%s", param_to_extract);
    }

    // truncate to the demo's web/ directory, dropping the trailing binary
    // name: "bounce/web/bounce" -> "bounce/web/" (served as web/index.html)
    char *web = strstr(url, "/web/");
    if (!web)
        return -1;
    web[strlen("/web/")] = '\0';

    // append ?arg=<param> if present
    size_t url_len = strlen(url);
    size_t param_len = strlen(param) ? strlen("?arg=") + strlen(param) : 0;
    if (url_len + param_len >= sizeof(url))
        return -1;
    if (param_len > 0)
    {
        strcat(url, "?arg=");
        strcat(url, param);
    }
    printf("url = %s\n", url);

    #ifdef __EMSCRIPTEN__
        extern void emscripten_run_script(const char *);
        extern int emscripten_run_script_int(const char *);

        // detect if running locally (page url contains "//127.0.0.1" or "//localhost")
        int is_local = emscripten_run_script_int(
            "(window.location.href.indexOf('//127.0.0.1') !== -1 || "
            "window.location.href.indexOf('//localhost') !== -1) ? 1 : 0");

        char sys_js[MAX_COMMAND_LEN] = "";
        int n;
        if (is_local) {
            n = snprintf(sys_js, sizeof(sys_js),
                "window.location.href = '../../%s';", url);
        } else {
            n = snprintf(sys_js, sizeof(sys_js),
                "window.location.href = 'https://sgi-demos.github.io/sgi-demos/demos/%s';", url);
        }
        if (n < 0 || (size_t)n >= sizeof(sys_js))
            return -1;
        // run js
        emscripten_run_script(sys_js);
    #else
        #ifdef _WIN32
            // Windows shim: Convert demo path to Windows format (fwd to backslashes)
            char win_command[MAX_COMMAND_LEN] = "";
            snprintf(win_command, sizeof(win_command), "%s", command);
            for (size_t i = 0; i < strlen(win_command); i++)
                win_command[i] = (win_command[i] == '/') ? '\\' : win_command[i];
            printf("win_command = %s\n",win_command);
            system(win_command);
        #else
            system(command);
        #endif
    #endif

    return 0;
}
#else
{
    // Other demos: system() shim is only validated for buttonfly's command
    // If another demo needs it, implement it here or reuse buttonfly's
    fprintf(stderr, "demo_shim_system: unimplemented for this demo, ignoring command: %s\n", command);
    return -1;
}
#endif // DEMO_BUTTONFLY

#define system demo_shim_system

FILE *demo_shim_popen(const char *command, const char *mode)
{
#ifdef DEMO_BUTTONFLY
    // Web & native shim: Transform 'cat' pipe command popen() to file open fopen():
    // fp = popen("cat menus/m_bounce", "r");  --->  fp = fopen("menus/m_bounce", "r")
    // NOTE: Required for web, optional for native, but this way we have a unified code path
    if (strlen(command) < MAX_COMMAND_LEN)
    {
        const char *cat = strstr(command, "cat ");
        if (cat && strcmp(mode, "r") == 0)
        {
            const char *menu_file = command + strlen("cat ");
            return fopen(menu_file, "r");
        }
    }

    return NULL;
#else
    // Other demos: popen() shim is only validated for buttonfly
    // If another demo needs it, implement it here or reuse buttonfly's
    fprintf(stderr, "demo_shim_popen: unimplemented for this demo, ignoring command: %s\n", command);
    return NULL;
#endif // DEMO_BUTTONFLY
}

#undef popen
#define popen demo_shim_popen


//
// Various workarounds for 1980s & UNIX code
//

// Private Eyes by Hall and Oates was the #1 song in the US on 9 Nov 1981, the day of SGI founding

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

// Avoid bringing in winsock just to fiddle some bytes from big to little endian
#ifndef ntohl
uint32_t ntohl(uint32_t x) {
    /* Check if we're already big-endian */
    static const int endian_test = 1;
    if (*(char *)&endian_test == 0) {
        /* Big-endian system, no conversion needed */
        return x;
    } else {
        /* Little-endian system, swap bytes */
        return ((x & 0xFF) << 24) |
               ((x & 0xFF00) << 8) |
               ((x & 0xFF0000) >> 8) |
               ((x & 0xFF000000) >> 24);
    }
}
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846	/* was mistyped 3.141596 */
#endif

// Browser-friendly exit(): in the web build a raw exit() tears down the C
// runtime but leaves the page sitting there (looks frozen), so instead we
// navigate away -- back to the previous page, or to the demos home if there
// is none. Native builds exit normally.
static void demo_exit(int status)
{
#ifdef __EMSCRIPTEN__
    // Go to previous page, or if none, to the demos home page.
    const char *exit_js =
        "if (document.referrer) {                                   "
        "     window.history.back();                                "
        "}                                                          "
        "else {                                                     "
        "    window.location.href = 'https://sgi-demos.github.io';  "
        "}                                                          ";
    extern void emscripten_run_script(const char *);
    emscripten_run_script(exit_js);
#endif
    exit(status);
}

#define exit demo_exit

// SGI        sizeof(long) == 4, sizeof(int) == 4, sizeof(size_t) == 4
// Mac M1     sizeof(long) == 8, sizeof(int) == 4, sizeof(size_t) == 8  <--- Bad things happen mixing longs and ints
// Wintel     sizeof(long) == 4, sizeof(int) == 4, sizeof(size_t) == 8
//#define long int


#endif /* DEMO_SHIM_H */
