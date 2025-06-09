#ifndef EM_SYSTEM_H
#define EM_SYSTEM_H 1

#ifdef __EMSCRIPTEN__
#include <string.h>

// Buttonfly web: Invoke the demo web page on system() call
int em_system(const char *command) 
{ 
    // Transform command line command into web page equivalent, e.g.:
    // "../bounce/bin/bounce ../bounce/x29.bin" ---> "bounce/web/bounce_full.html"
    printf ("command = %s\n", command);

    // copy command into url, trim "../" if present
    char url[256]; 
    char* dotdot = strstr(command, "../");
    if (dotdot)
        strcpy (url, command+strlen("../")); 
    else
        strcpy (url, command);
    
    // replace "/bin/" with "/web/"
    char* rep = strstr(url, "/bin/"); 
    if (rep) {
        strcpy(rep, "/web"); rep[4] = '/'; 

        // snip out command parameter 
        rep = strstr(url, " ../");
        if (rep)
            rep[0] = 0;

        // append "_full.html"
        strcat(url, "_full.html"); 
        printf("url = %s\n", url);

        // generate js to visit full path url
        char sys_js[256]; 
        snprintf (sys_js, 256, "window.location.href = 'https://sgi-demos.github.io/sgi-demos/%s';",url); 
        printf("sys_js = %s\n",sys_js);

        // run js
        extern void emscripten_run_script(const char *); 
        emscripten_run_script(sys_js); 
    }
}
#define system em_system
#endif

// Buttonfly web: Redirect to fopen() on popen() call
#ifdef __EMSCRIPTEN__
#include <string.h>
#include <stdio.h>
FILE *em_popen(const char *command, const char *mode)
{
    // Transform pipe command into file open, e.g.:
    // fp = popen("cat menus/m_bounce", "r");  --->  fp = fopen("menus/m_bounce", "r")
    char command_cpy[256];
    strcpy(command_cpy, command);

    char *cat = strstr(command_cpy, "cat ");
    if (cat && strcmp(mode, "r") == 0)
    {
        char *menu_file = command_cpy + strlen("cat ");
        return fopen(menu_file, "r");
    }
    else
        return NULL;
}
#define popen em_popen
#endif


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
#define M_PI 3.141596
#endif

// SGI        sizeof(long) == 4, sizeof(int) == 4, sizeof(size_t) == 4
// Mac M1     sizeof(long) == 8, sizeof(int) == 4, sizeof(size_t) == 8  <--- Bad things happen mixing longs and ints
// Wintel     sizeof(long) == 4, sizeof(int) == 4, sizeof(size_t) == 8

//#define long int

#endif /* EM_SYSTEM_H */