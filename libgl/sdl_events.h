/*
    Window and input event handling
*/
extern bool* sdlLeftMouse;
extern bool* sdlMiddleMouse;
extern bool* sdlRightMouse;
extern Pixel2D* sdlMousePos;
extern char* sdlKeyDown;
extern bool *sdlLeftShift;
extern bool *sdlRightShift;
extern bool *sdlLeftCtrl;
extern bool *sdlRightCtrl;

extern void sdlEventsInit(const char* windowTitle);
extern void sdlEventsProcess();
extern void sdlEventsSwapWindow();

extern int sdlMousePosX();
extern int sdlMousePosY();
extern unsigned char sdlMouseButtonState();
extern unsigned char* sdlGetKeyboardState();
extern int sdlPeepEvents();