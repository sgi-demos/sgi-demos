#include <stdbool.h>

extern uint32_t sdlInitWindow();
extern bool sdlGLContextReady();
extern void sdlOpenWindow(char *title);
extern void sdlSetFramebufferSourceMem(unsigned char* pSrcPixels);
extern void sdlSetFramebufferSourceTex(uint32_t tex);
extern bool sdlResizeWindow(Uint32 windowID); // true = framebuffer size changed
extern void sdlGetFramebufferSize(int32_t *width, int32_t *height);
extern void sdlSetFramebufferAspect(int32_t x, int32_t y);
extern void sdlSetFramebufferFixedSize(int32_t width, int32_t height);
extern bool sdlApplyFramebufferSize(void); // true = framebuffer size changed

extern bool sdlInsideFramebuffer(int windowX, int windowY);
extern int  sdlClampToFramebufferX(int windowX);
extern int  sdlClampToFramebufferY(int windowY);

extern void sdlInitFramebufferTexture();
extern void sdlUpdateFramebufferTexture();
extern void sdlRenderFramebufferTexture();
extern void sdlFreeFramebufferTexture();
