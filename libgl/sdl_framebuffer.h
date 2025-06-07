#include "basic_types.h"
#include "geom_types.h"

extern void sdlInitWindow();
extern void sdlOpenWindow(char *title, int32_t frameWidth, int32_t frameHeight);
extern void sdlSetFramebufferSource(unsigned char* pSrcPixels);
extern void sdlResizeWindow(Uint32 windowID, Size2D windowSize);

extern bool sdlInsideFramebuffer(int windowX, int windowY);
extern int  sdlClampToFramebufferX(int windowX);
extern int  sdlClampToFramebufferY(int windowY);

extern void sdlInitFramebufferTexture();
extern void sdlUpdateFramebufferTexture();
extern void sdlRenderFramebufferTexture();
extern void sdlFreeFramebufferTexture();
