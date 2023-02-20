//
//  Window and input event handling
//
#define false 0
#define true 1

extern void sdlEventsInit(const char* windowTitle);
extern void sdlEventsProcess();
extern void sdlEventsPresent();
extern SDL_Renderer* sdlRenderer();
extern Size2D sdlGetFramebufferSize();