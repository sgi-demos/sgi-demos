/* 

   Redefine child app's infinite loop ("while (true)") to a separate child_main_loop() function 
   because Emscripten is driving the bus.
    
   This is going to be a bit ugly because variables declared before but used within the while loop
   will need to be redeclared or passed into the new child_main_loop() function.  So it will be done 
   on a case by case basis with each child app.

   Longer term, look into web/WASM worker in which the child app can happily run with source 
   unmmodified, with events communicated to it from the main Emscripten thread via shared memory. For 
   now though, we just want to get some pixels in the browser.

*/
#define while \
} \
\
void child_main_loop(void *arg) \
{ \
    if
