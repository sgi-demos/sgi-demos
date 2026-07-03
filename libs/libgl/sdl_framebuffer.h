#include <stdbool.h>

extern uint32_t sdlInitWindow();
extern bool sdlGLContextReady();
extern void sdlOpenWindow(char *title, int32_t frameWidth, int32_t frameHeight);
extern void sdlSetFramebufferSourceMem(unsigned char* pSrcPixels);
extern void sdlSetFramebufferSourceTex(uint32_t tex);
extern void sdlResizeWindow(Uint32 windowID);

extern bool sdlInsideFramebuffer(int windowX, int windowY);
extern int  sdlClampToFramebufferX(int windowX);
extern int  sdlClampToFramebufferY(int windowY);

extern void sdlInitFramebufferTexture();
extern void sdlUpdateFramebufferTexture();
extern void sdlRenderFramebufferTexture();
extern void sdlFreeFramebufferTexture();
