//
//  SDL window and input event handling
//
#include "basic_types.h"
#include "geom_types.h"

extern void sdlInit(const char* windowTitle);
extern void sdlProcessEvents();
extern void sdlPresent();

extern SDL_Renderer* sdlRenderer();

extern Size2D sdlWindowSize();
extern Vec2D sdlViewport();

extern Size2D sdlFramebufferSize();
extern unsigned char* sdlFramebuffer();
extern int sdlWindowToFramebufferOffsetX();
extern int sdlWindowToFramebufferOffsetY();