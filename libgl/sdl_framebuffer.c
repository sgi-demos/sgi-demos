//
//  SDL framebuffer - displays an image in the center of the window
//
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "sdl_events.h"
#include "EM_CHILD_APP_DECL.h"

static SDL_Texture * pFramebuffer = NULL;

void build_framebuffer_tex()
{
    // Create grey checkerboard surface with yellow border
    int bitsPerPixel = 32;

    SDL_Surface* pSurface = SDL_CreateRGBSurface(0, sdlFramebufferSize().width, sdlFramebufferSize().height, bitsPerPixel, 0, 0, 0, 0);
    unsigned int* surfacePixels = (unsigned int*)pSurface->pixels;
    
    for (int y = 0; y < pSurface->h; ++y)
        for (int x = 0; x < pSurface->w; ++x)
        {
            const int i = x + y * pSurface->w;
            if (y == 0 || x == 0 || y == pSurface->h-1 || x == pSurface->w - 1)
                surfacePixels[i] = 0xff00ffff; // yellow
            else 
            {
                const int checkerSize = 100, halfChecker = checkerSize / 2,
                        yMod = y % checkerSize, xMod = x % checkerSize;
                if ((yMod < halfChecker && xMod < halfChecker) 
                    || (yMod >= halfChecker && xMod >= halfChecker))
                    surfacePixels[i] = 0xffc4c4c4; // light grey
                else
                    surfacePixels[i] = 0xff808080; // dark grey
            }
        }
    
    // Create texture from surface
    pFramebuffer = SDL_CreateTextureFromSurface(sdlRenderer(), pSurface);
    SDL_FreeSurface(pSurface);
}

void update_framebuffer_tex()
{
    if (sdlFramebuffer())
    {
        unsigned char* pixels = sdlFramebuffer();
        Size2D fbSize = sdlFramebufferSize();
        SDL_Rect rect = (SDL_Rect){ .x = 0, .y = 0, 
                                    .w = fbSize.width, .h = fbSize.height };
        int pitch = fbSize.width * 4;
        SDL_UpdateTexture(pFramebuffer, NULL, pixels, pitch);
    }
}

void free_framebuffer_tex()
{
    // Free existing SDL image and GL texture
    if (pFramebuffer)
    {
        SDL_DestroyTexture(pFramebuffer);
        pFramebuffer = NULL;
    }
}

void redraw()
{
    SDL_SetRenderDrawColor(sdlRenderer(), 0, 0, 0, 0);
    SDL_RenderClear(sdlRenderer());

    update_framebuffer_tex();
    SDL_Rect destRect = (SDL_Rect) {
        .x = sdlWindowToFramebufferOffsetX(), 
        .y = sdlWindowToFramebufferOffsetY(), 
        sdlFramebufferSize().width, 
        sdlFramebufferSize().height };
    SDL_RenderCopy(sdlRenderer(), pFramebuffer, NULL, &destRect);
    sdlPresent();
}

const int SCREEN_FPS = 25;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
void main_loop(void* main_loop_arg) 
{   
    #ifdef MAIN_LOOP_DEBUG
    static int main_loop_count = 0;
    if (main_loop_count % SCREEN_FPS == 0)
        printf("main_loop BEGIN %d\n",main_loop_count);
    #endif

    Uint32 startTicks = SDL_GetTicks();

    sdlProcessEvents();

    // Run child main loop - let child process events and redraw its stuff
    child_main_loop();

    redraw();

    Uint32 frameTicks = SDL_GetTicks() - startTicks;
    if( frameTicks < SCREEN_TICKS_PER_FRAME )
    {
        SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
    }    

    #ifdef MAIN_LOOP_DEBUG
    if (main_loop_count % SCREEN_FPS == 0)
        printf("main_loop END %d\n",main_loop_count);
    ++main_loop_count;
    #endif
}

int main(int argc, char* argv[])
{
    // Initialize SDL window
    sdlInit(NULL);

    build_framebuffer_tex();

    // Run child main
    child_main(argc, argv);

    // Start the main loop
    void* main_loop_arg = NULL;
    #ifdef __EMSCRIPTEN__
        int fps = 0; // Set to 0 to use browser's requestAnimationFrame (recommended)
        int simulate_infinite_loop = 1;
        emscripten_set_main_loop_arg(main_loop, main_loop_arg, fps, simulate_infinite_loop);
    #else
        while(true) 
            main_loop(main_loop_arg);
    #endif

    free_framebuffer_tex();
    return 0;
}