//
// Native resize test harness (shim test, NOT an original SGI demo).
// Mimics buttonfly's window setup (keepaspect 5:4, projection set once),
// then drives real SDL window resizes and verifies the framebuffer re-fits.
//
#include <stdio.h>
#include <stdlib.h>
#include <gl.h>
#include <device.h>
#include <SDL.h>

static int failures = 0;

static void check(const char *label, int setW, int setH)
{
    // find the SDL window the shim created
    SDL_Window *win = SDL_GL_GetCurrentWindow();
    SDL_SetWindowSize(win, setW, setH);

    // let the shim's event pump see the SIZE_CHANGED (+ possible snap)
    for (int i = 0; i < 30; ++i) {
        short val; long dev = qtest();
        if (dev) { dev = qread(&val); }  // drain (REDRAWs etc.)
        SDL_Delay(20);
    }

    int wW, wH;
    SDL_GetWindowSize(win, &wW, &wH);
    long fbW, fbH;
    getsize(&fbW, &fbH);

    // expected: window conforms to displayed 4:3 (5:4 x PAR 16:15),
    // fb = 15/16 the window columns, full height
    double winAspect = (double)wW / (double)wH;
    long expFbW = (wW * 15 + 8) / 16;
    int aspectOK = winAspect > 1.30 && winAspect < 1.37;
    int fbOK = (fbW >= expFbW - 2 && fbW <= expFbW + 2) && (fbH >= wH - 2 && fbH <= wH + 2);
    printf("TEST %-22s request %4dx%-4d -> window %4dx%-4d (%.3f) fb %ldx%ld (expect ~%ldx%d) %s%s\n",
           label, setW, setH, wW, wH, winAspect, fbW, fbH, expFbW, wH,
           aspectOK ? "" : "WINDOW-ASPECT-FAIL ", fbOK ? "OK" : "FB-FAIL");
    if (!aspectOK || !fbOK) failures++;
}

int main(void)
{
    keepaspect(5, 4);
    winopen("resizetest");
    RGBmode();
    doublebuffer();
    gconfig();
    qdevice(REDRAW);

    mmode(MPROJECTION);
    perspective(450, 5.0/4.0, 0.001, 9.0);
    mmode(MVIEWING);

    // draw something so swaps occur
    for (int i = 0; i < 5; ++i) { cpack(0x00404040); clear(); swapbuffers(); SDL_Delay(20); }

    check("grow-wide",       1400, 900);
    check("grow-tall",        900, 1100);
    check("grow-big",        1600, 1150);
    check("shrink",           600, 500);
    check("grow-after-shrink",1500, 1150);
    check("odd-1",           1234, 777);
    check("odd-2",            801, 799);

    // drag-like burst: many sizes queued before the shim pumps once
    {
        SDL_Window *win = SDL_GL_GetCurrentWindow();
        for (int w = 810; w <= 1290; w += 60)
            SDL_SetWindowSize(win, w, 700);
        check("drag-burst",      1350, 700);
    }

    // display-move: park the window on each display in turn (exercises
    // macOS backing-scale changes, the shot-3 suspect)
    {
        SDL_Window *win = SDL_GL_GetCurrentWindow();
        int n = SDL_GetNumVideoDisplays();
        printf("TEST displays: %d\n", n);
        for (int d = 0; d < n; ++d) {
            SDL_Rect r; SDL_GetDisplayBounds(d, &r);
            float ddpi, hdpi, vdpi; SDL_GetDisplayDPI(d, &ddpi, &hdpi, &vdpi);
            printf("TEST display %d: %dx%d at %d,%d dpi %.0f\n", d, r.w, r.h, r.x, r.y, ddpi);
            SDL_SetWindowPosition(win, r.x + 80, r.y + 80);
            for (int i = 0; i < 30; ++i) { short val; if (qtest()) qread(&val); SDL_Delay(20); }
            int wW, wH, dW, dH; SDL_GetWindowSize(win, &wW, &wH); SDL_GL_GetDrawableSize(win, &dW, &dH);
            long fbW, fbH; getsize(&fbW, &fbH);
            printf("TEST on-display-%d: window %dx%d drawable %dx%d fb %ldx%ld\n", d, wW, wH, dW, dH, fbW, fbH);
            check("resize-on-display", 1300, 900);
        }
    }

    printf(failures ? "RESULT: %d FAILURES\n" : "RESULT: ALL OK\n", failures);
    exit(failures != 0);
}
