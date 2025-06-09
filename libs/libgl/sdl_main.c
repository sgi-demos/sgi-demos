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

// Framerate control:
// - Simulate a decent SGI machine for the time, 60 fps is too fast for some demos (like ideas)
// - Also, in the 80s and 90s, we had less than 60 fps and we liked it!
// - TODO: Make this a per-demo option
const int SCREEN_FPS = 30; 

Uint32 beginMaintainFPS()
{
    return SDL_GetTicks();
}

void endMaintainFPS(int fps, Uint32 startTicks)
{
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    Uint32 frameTicks = SDL_GetTicks() - startTicks;
    if (frameTicks < SCREEN_TICKS_PER_FRAME)
    {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }    
}

void main_loop(void* main_loop_arg) 
{   
    Uint32 startTicks = beginMaintainFPS();

    // Translate input events into IRIS GL events
    sdlProcessEvents();

    // Run IRIS GL demo's main loop, so it can process events and redraw its stuff
    child_main_loop();

    // Update framebuffer texture with rendered pixels
    sdlUpdateFramebufferTexture();

    // Render framebuffer texture
    sdlRenderFramebufferTexture();

    endMaintainFPS(SCREEN_FPS, startTicks);
}

int main(int argc, char* argv[])
{
    // Initialize SDL
    sdlInitWindow();
    sdlInitFramebufferTexture();

    // Run IRIS GL demo's child main
    child_main(argc, argv);

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