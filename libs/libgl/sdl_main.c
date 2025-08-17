//
//  SDL main rendering loop
//
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include "sdl_framebuffer.h"
#include "sdl_events.h"
#include "EM_CHILD_APP_DECL.h"

void main_loop(void* main_loop_arg)
{
    // Run IRIS GL demo's demo_main_loop as a child of this loop,
    // so it can process events and redraw its stuff
    sdlRunEventLoop(demo_main_loop);
}

int main(int argc, char* argv[])
{
    // Initialize SDL
    sdlInitWindow();
    sdlInitFramebufferTexture();

    // Run IRIS GL demo's demo main
    demo_main(argc, argv);

    // Start the main event/redraw loop
    void* main_loop_arg = NULL;
    #ifdef __EMSCRIPTEN__
        int fps = 0; // Set to 0 to use browser's requestAnimationFrame (recommended)
        int simulate_infinite_loop = 1;
        emscripten_set_main_loop_arg(main_loop, main_loop_arg, fps, simulate_infinite_loop);
    #else
        while(true)
            main_loop(main_loop_arg);
    #endif

    sdlFreeFramebufferTexture();
    return 0;
}
