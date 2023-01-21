/* 
   Redefine demo infinite loop to separate mainLoop() function because Emscripten is driving the bus.
    
   This is going to be a bit ugly because variables declared before but used within the while loop
   will need to be redeclared or passed into the new mainLoop() function.  So it will be done on a 
   case by case basis.

   Longer term, look into web/WASM worker in which the demo can happily run with source unmmodified,
   with events communicated to it from the main Emscripten thread via shared memory. For now though,
   we just want to get some old SGI pixels in the browser.

    arg = User-defined data
    fps = Use browser's requestAnimationFrame (recommended)
    simulate_infinite_loop = Throw an exception in order to stop execution of the caller

*/
#define while \
    void *arg = NULL; \
    int fps = 0; \
    int simulate_infinite_loop = FALSE; \
    emscripten_set_main_loop_arg(&mainLoop, arg, fps, simulate_infinite_loop); \
} \
\
void mainLoop(void *arg) \
{ \
    static short dev; \
    static short val; \
    static Boolean attached; \
    if
