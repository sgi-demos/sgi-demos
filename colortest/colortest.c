#include <stdio.h>
#include <stdlib.h>
#include <gl.h>
#include <math.h>
#include <device.h>

float c1[3];
float c2[3];
float c3[3];
float v1[3];
float v2[3];
float v3[3];

int main(int argc, char *argv[]) {
    long wsizex, wsizey;

    winopen("colortest");
    getsize(&wsizex, &wsizey);
    shademodel(FLAT);
    doublebuffer();
    RGBmode();
    reshapeviewport();

    // RGB corners.
    c1[0] = 1.0;
    c1[1] = 0.0;
    c1[2] = 0.0;
    c2[0] = 0.0;
    c2[1] = 1.0;
    c2[2] = 0.0;
    c3[0] = 0.0;
    c3[1] = 0.0;
    c3[2] = 1.0;

    // All red corners.
    if (1) {
        c2[0] = 1.0;
        c2[1] = 0.0;
        c2[2] = 0.0;
        c3[0] = 1.0;
        c3[1] = 0.0;
        c3[2] = 0.0;
    }

    float t = 0;
    float r = 1.0;
    while (1) {
        czclear(0, 0xff800000);

        v1[0] = sin(t)*r;
        v1[1] = cos(t)*r;
        v1[2] = 0;
        v2[0] = sin(t + M_PI*2/3)*r;
        v2[1] = cos(t + M_PI*2/3)*r;
        v2[2] = 0;
        v3[0] = sin(t + M_PI*4/3)*r;
        v3[1] = cos(t + M_PI*4/3)*r;
        v3[2] = 0;

        bgnpolygon();
        c3f(c1);
        v3f(v1);
        c3f(c2);
        v3f(v2);
        c3f(c3);
        v3f(v3);
        endpolygon();

        swapbuffers();

        t += 0.01;
    }

    return 0;
}
