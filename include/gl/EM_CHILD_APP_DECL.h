/*
    Declare demo main and demo main loop.  Demo main will be called by main, to allow
    demo app to initialize before its loop.  Main loop is the Emscripten/SDL main event
    handling and redraw loop. This takes place of the forever loops in the demo apps,
    with Emscripten calling into the demo app's event loop whenever a new SDL event
    occurs.
*/
extern int demo_main (int argc, char* argv[]); // Will be called by main()
extern void demo_main_loop();                  // Will be called by main_loop()

/*
    Define stub demo main and demo main_loop if not already defined.
    Only needed for testing Emscripten/SDL host app in standalone mode.
*/
#ifndef EM_CHILD_APP
int demo_main (int argc, char* argv[]) { return 0; }
void demo_main_loop() {}
#endif
