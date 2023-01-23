/*
    Window and input event handling
*/
extern bool* sdlLeftMouse;
extern Pixel2D* sdlMousePos;
extern char* sdlKeyDown;

extern void sdlEventsInit(const char* windowTitle);
extern void sdlEventsProcess();
extern void sdlEventsSwapWindow();
