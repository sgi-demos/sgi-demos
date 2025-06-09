/* 
    Declare child main and child main loop.  Child main will be called by main, to allow
    child app to initialize before its loop.  Main loop is the Emscripten/SDL main event
    handling and redraw loop. This takes place of the forever loops in the child apps, 
    with Emscripten calling into the child app's event loop whenever a new SDL event 
    occurs.
*/
extern int child_main (int argc, char* argv[]); // Will be called by main()
extern void child_main_loop();                  // Will be called by main_loop()

/* 
    Define stub child main and child main_loop if not already defined.
    Only needed for testing Emscripten/SDL host app in standalone mode.
*/
#ifndef EM_CHILD_APP
int child_main (int argc, char* argv[]) { return 0; }
void child_main_loop() {}
#endif
