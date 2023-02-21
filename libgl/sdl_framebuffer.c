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
#include "EM_MAIN_DEFN.h"

static SDL_Texture * pFramebuffer = NULL;

void buildTexture()
{
    // Create grey checkerboard surface with yellow border
    int winWidth = sdlWindowSize().width,
        winHeight = sdlWindowSize().height;
    int bitsPerPixel = 32;

    SDL_Surface* pSurface = SDL_CreateRGBSurface(0, winWidth, winHeight, bitsPerPixel, 0, 0, 0, 0);
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

void updateTexture()
{
    if (sdlFramebuffer())
    {
        unsigned char* pixels = sdlFramebuffer();
        Size2D fbSize = sdlFramebufferSize();
        SDL_Rect rect = (SDL_Rect){ .x = sdlWindowToFramebufferOffsetX(), .y = sdlWindowToFramebufferOffsetY(), 
                                    .w = fbSize.width, .h = fbSize.height };
        int pitch = fbSize.width * 4;
        SDL_UpdateTexture(pFramebuffer, &rect, pixels, pitch);
    }
}

void freeTexture()
{
    // Free existing SDL image and GL texture
    if (pFramebuffer)
    {
        SDL_DestroyTexture(pFramebuffer);
        pFramebuffer = NULL;
    }
}

void main_loop(void* main_loop_arg) 
{    
    sdlProcessEvents();

    // Run child main loop - let child process events and redraw
    child_main_loop(main_loop_arg);

    // Redraw
    updateTexture();
    SDL_RenderCopy(sdlRenderer(), pFramebuffer, NULL, NULL);
    sdlPresent();
}

int main(int argc, char* argv[])
{
    // Initialize SDL window
    sdlInit("sgi-demos-sdl");

    buildTexture();

    // Run child main
    child_main(argc, argv);

    // Start the main loop
    void* main_loop_arg = NULL; // User-defined data to pass to main_loop() and child_main_loop()
    #ifdef __EMSCRIPTEN__
        int fps = 0; // Set to 0 to use browser's requestAnimationFrame (recommended)
        int simulate_infinite_loop = 1;
        emscripten_set_main_loop_arg(main_loop, main_loop_arg, fps, simulate_infinite_loop);
    #else
        while(true) 
            main_loop(main_loop_arg);
    #endif

    freeTexture();
    return 0;
}