/* 
    Stub emscripten_set_main_loop_arg() as preperation for running in Emscrpiten.
    This takes place of the forever loops in the demos, with Emscripten calling 
    into the demo's event loop whenever a new input, redraw, etc. event occurs.   
*/

#ifndef EM_MAIN_LOOP_INIT
#define EM_MAIN_LOOP_INIT
void mainLoop();
typedef void (*em_arg_callback_func)(void*);
void emscripten_set_main_loop_arg(em_arg_callback_func func, void *arg, int fps, int simulate_infinite_loop)
{
    while(TRUE)
        func(arg);
}
#endif