/*
    Window and input event handling
*/
extern bool* sdlLeftMouse;
extern bool* sdlMiddleMouse;
extern bool* sdlRightMouse;
extern Pixel2D* sdlMousePos;
extern char* sdlKeyDown;

extern void sdlEventsInit(const char* windowTitle);
extern void sdlEventsProcess();
extern void sdlEventsSwapWindow();
