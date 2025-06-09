
#include <stdio.h>
#include <gl.h>

Coord b[4][3] = {
    { -2, -1, 0 },
    {  1, -1, 0 },
    {  1,  1, 0 },
    { -1,  1, 0 },
};

int main()
{
    long wsizex, wsizey;

    winopen("gltest");
    reshapeviewport();
    getsize (&wsizex, &wsizey);
    perspective((Angle) 640, (float) wsizex / wsizey, 0.01, 131072.0);
    mapcolor(0, 255, 0, 0);
    mapcolor(1, 0, 255, 0);
    for (int i = 0; i < 1800; i += 10) {
        pushmatrix();
        translate(0, 0, -4);
        rotate(i, 'x');
        doublebuffer();
        color(0);
        clear();
        color(1);
        polf(4, b);
        popmatrix();
        swapbuffers();
    }
    return 0;
}
