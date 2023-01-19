/* 
   Redefine demo infinite loop to separate mainLoop() function because Emscripten is driving the bus.
    
   This is going to be a bit ugly because variables declared before but used within the while loop
   will need to be redeclared or passed into the new mainLoop() function.  So it will be done on a 
   case by case basis.

   Longer term, look into web/WASM worker in which the demo can happily run with source unmmodified,
   with events communicated to it from the main Emscripten thread via shared memory. For now though,
   we just want to get some old SGI pixels in the browser.
*/
#define while \
    emscripten_set_main_loop_arg(&mainLoop, NULL, 0, 0); \
} \
\
void mainLoop() \
{ \
    static short dev; \
    static short val; \
    static Boolean attached; \
    if
