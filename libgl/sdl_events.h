//
//  SDL window and input event handling
//
#include "basic_types.h"
#include "geom_types.h"

// Needed by sdl_gl_events.c
void sdlWindowOpen(char *title, int32_t frame_width, int32_t frame_height);
void sdlSetFramebuffer(unsigned char* framebuffer);
void sdlWindowResizeEvent(Uint32 windowID, Size2D windowSize);
bool sdlInsideFramebuffer(int windowX, int windowY);
int sdlClampToFramebufferX(int windowX);
int sdlClampToFramebufferY(int windowY);

// Needed by sdl_framebuffer.c
extern void sdlProcessEvents();
