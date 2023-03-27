/* 

   Redefine child app's main() to child_main(), and its infinite event loop ("while (1)") to a 
   separate child_main_loop() function, because Emscripten is driving the bus.
    
   This is going to be a bit ugly because variables declared before but used within the while loop
   will need to be redeclared or passed into the new child_main_loop() function.  So it will be done 
   on a case by case basis with each child app.

   Longer term, look into web/WASM worker in which the child app can happily run with source 
   unmmodified, with events communicated to it from the main Emscripten thread via shared memory. For 
   now though, we just want to get some pixels in the browser.

*/

// redefine main to child_main
#define main child_main

/*

    demo            # local vars in main(), used in child_main_loop
    -----------     ----------------------
    bounce.c        0
    buttonfly.c     0
    cedit.c         0
    flight.c        100+ - moved all to global static - comment out instead, and repeat below?
    shadow.c        13 - TBD
    track.c         0
    insect.c        3
    jello.c         3
    logo.c          2
    newave.c        0
    twilight.c      0

*/

// re-define main's locals for child_main_loop, if used in child_main_loop
#define EM_BOUNCE       0
#define EM_BUTTONFLY    1
#define EM_CEDIT        2
#define EM_FLIGHT       3
#define EM_SHADOW       4
#define EM_IDEAS        5
#define EM_INSECT       6
#define EM_JELLO        7
#define EM_LOGO         8
#define EM_NEWAVE       9
#define EM_TWILIGHT     10

#if EM_CHILD_APP_NAME == EM_INSECT
    #define EM_CHILD_APP_LOCALS static short dev,val; static Boolean attached;
#elif EM_CHILD_APP_NAME == EM_JELLO
    #define EM_CHILD_APP_LOCALS static int i,j;
#elif EM_CHILD_APP_NAME == EM_LOGO
    #define EM_CHILD_APP_LOCALS static int i,j;
#elif EM_CHILD_APP_NAME == EM_IDEAS
    #define EM_CHILD_APP_LOCALS static float x, y, z, c;
#else
    #define EM_CHILD_APP_LOCALS
#endif

// redefine main loop to child_main_loop - change while(1) to em_while(1) in child app
#define em_while(cond) \
} \
\
void child_main_loop() \
{ \
    EM_CHILD_APP_LOCALS \
    if((cond))

#if EM_CHILD_APP_NAME == EM_INSECT
    /* begin Emscripten emcc crashes on -fcommon, so must fwd define */
    Object screen,viewit,shadow,body,hip[6],thigh[6],shin[6],kneeball[6];
    Object body_shadow,hip_shadow,thigh_shadow,shin_shadow,kneeball_shadow;

    Tag cphitag,cthetatag,cposittag,windowtag;

    Angle knee[6];
    Angle hip_phi[6];
    Angle hip_theta[6];

    Coord sdepth;
    float glsin,glcos;
    float px,py;
    float light[3],phi,theta;
    Boolean legup[6];
    float legx[6],legy[6];

    float cx,cy,cz,cvx,cvy,cvz;
    float dmr[6],fr[6];
    Angle ctheta,cphi,cvtheta,cvphi;
    Boolean follow;

    Coord k2[6][3];
    Coord k3[6][3];
    Coord b7[12][3];
    Coord b8[12][3];
    Icoord scr[4][2];
    /* end Emscripten emcc crashes on -fcommon, so must fwd define */
#endif
