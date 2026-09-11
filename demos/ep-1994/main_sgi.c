/*****************************************************************
    sgi-demos: IRIS GL harness for ElectroPortis, replacing the fork's
    GLUT main (glut/main_glut.c).  Opens a single RGB double-buffered
    window, runs ep's own init/reshape/display, and yields once per frame
    via swapbuffers() -- ep drives its own animation and default script.
*****************************************************************/
#include <gl.h>
#include <device.h>
#include "ep.h"

extern int ep_shipped_ogl;   /* gl_wrap_sgi.c: shipped-1994 look (M) */

/* (ep.c defines oflag/bflag itself; oflag defaults to 0 = quiet.) */

int
main(void)
{
    long w, h;

    winopen("electroportis");
    RGBmode();
    doublebuffer();
    gconfig();
    qdevice(ESCKEY);
    qdevice(REDRAW);
    qdevice(MKEY);              /* toggle shipped-1994 look */

    getsize(&w, &h);
    init_ep();
    ep_reshape((int)w, (int)h);

    for (;;) {
        while (qtest()) {
            short val;
            long dev = qread(&val);

            if (dev == ESCKEY && val)
                return 0;
            if (dev == MKEY && val) {
                ep_shipped_ogl = !ep_shipped_ogl;
                getsize(&w, &h);
                ep_reshape((int)w, (int)h);  /* re-derive the camera */
            }
            if (dev == REDRAW) {
                getsize(&w, &h);
                ep_reshape((int)w, (int)h);
            }
        }

        ep_display(0);         /* clears, advances the script, draws */
        swapbuffers();          /* presents and yields to the host */
    }

    return 0;
}
