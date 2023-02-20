//
//  SDL window and input event handling
//
#include "geom_types.h"

extern void sdlInit(const char* windowTitle);
extern SDL_Renderer* sdlRenderer();
extern Size2D sdlWindowSize();
extern Vec2D sdlViewport();
extern Size2D sdlFramebufferSize();
extern void sdlProcessEvents();
extern void sdlPresent();
extern bool sdlViewChanged();