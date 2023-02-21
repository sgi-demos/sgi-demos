/* 
    Declare child main, main loop, and child main loop.  Child main will be called
    by main, to allow child app to set up before its loop.  Main loop is the Emscripten
    main event/redraw loop. This takes place of the forever loops in the child apps, 
    with Emscripten calling into the child app's event loop whenever a new input, 
    redraw, etc. event occurs.   
*/
#ifndef EM_MAIN_DECL
#define EM_MAIN_DECL

// main loop of parent app (Emscripten main loop)
extern void main_loop(void *arg);

// main and main loop for child app
extern int child_main (int argc, char* argv[]); // Will be called by main()
extern void child_main_loop(void *arg);         // Will be called by main_loop()

#endif