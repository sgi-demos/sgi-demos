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

// redefine main loop to child_main_loop - change while(1) to em_while(1) in child app
#define em_while(cond) \
} \
\
void child_main_loop() \
{ \
    static short dev; \
    static short val; \
    static int started = 1; \
    static int i,j; \
	double dx, dy, dz; \
    static float x, y, z, c; \
    static float current_time = 0.0; \
    static float previous_time; \
	static int r=100, g=255, b=255; \
    static Boolean attached; \
    if((cond))

