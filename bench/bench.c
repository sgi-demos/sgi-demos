#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gl.h>
#include <math.h>
#include <device.h>

#define X 0
#define Y 1
#define Z 2

float ident_matrix[4][4] =
{
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0},
};

typedef struct vertex_ {
    float v[3];
    float n[3];
} vertex;

#define MESH_ROWS_QUADS 100
#define MESH_COLS_QUADS 100

vertex vertices[MESH_ROWS_QUADS + 1][MESH_COLS_QUADS + 1];

float scale_value = 0.2;

void create_mesh()
{
    printf("mesh is %d vertices submitted, %d triangles.\n",
        MESH_ROWS_QUADS * (MESH_COLS_QUADS + 1) * 2,
        MESH_ROWS_QUADS * MESH_COLS_QUADS * 2);


    for(int j = 0; j < MESH_ROWS_QUADS + 1; j++)
        for(int i = 0; i < MESH_COLS_QUADS + 1; i++) {
            float u = i / (float)MESH_COLS_QUADS;
            float v = j / (float)MESH_ROWS_QUADS;
            vertices[j][i].v[0] = scale_value * (2.0 * u - 1.0);
            vertices[j][i].v[1] = scale_value * (2.0 * v - 1.0);
            vertices[j][i].v[2] = -1;
            float nx = (drand48() - .5) * .5;
            float ny = (drand48() - .5) * .5;
            float nz = 1.0;
            float d = sqrt(nx * nx + ny * ny + nz * nz);
            vertices[j][i].n[0] = nx / d;
            vertices[j][i].n[1] = ny / d;
            vertices[j][i].n[2] = nz / d;
        }
}

void draw_mesh()
{
    for(int j = 0; j < MESH_ROWS_QUADS; j++) {
        bgntmesh();
        for(int i = 0; i < MESH_COLS_QUADS + 1; i++) {
            n3f(vertices[j][i].n);
            v3f(vertices[j][i].v);
            n3f(vertices[j + 1][i].n);
            v3f(vertices[j + 1][i].v);
        }
        endtmesh();
    }
}

float my_material[] =
{
    AMBIENT,	0.0, 0.0, 0.0,
    DIFFUSE,	1.0, 1.0, 1.0,
    SPECULAR,	0.1, 0.1, 0.1,
    SHININESS,	20.0,
    LMNULL
};


float my_light[] =
{
    AMBIENT, 0.0, 0.0, 0.0, 
    LCOLOR,   1.0, 1.0, 1.0, 
    POSITION, 0.0, 0.5, 1.0, 1.0, 
    LMNULL
};

float infinite[] =
{
    AMBIENT, 0.0, 0.0, 0.0, // 0.3, 0.3, 0.3, 
    LOCALVIEWER, 0.0, 
    LMNULL
};

#define MY_MATERIAL 1
#define MY_LIGHT 1
#define INFINITE 1

init_lighting()
{
    lmdef (DEFMATERIAL, MY_MATERIAL, 0, my_material);

    lmdef (DEFLIGHT, MY_LIGHT, 0, my_light);

    lmdef (DEFLMODEL, INFINITE, 0, infinite);

    lmbind(LIGHT0, MY_LIGHT);

    lmbind(LMODEL, INFINITE);

    lmbind(MATERIAL, MY_MATERIAL);
}


main (argc, argv)
int	argc;
char	*argv[];
{
    initialize(argv[0]);

    while(TRUE) {

        while(qtest()) {
            short val;
            short dev=qread(&val);
            switch(dev) {
            case ESCKEY :
                if (!val) {
                    gexit();
                    exit(0);
                }
                break;
            case REDRAW:
                reshapeviewport();
                break;
            }
        }

        draw_everything();
    }
}


initialize()
{
    create_mesh();

    int gid=winopen("benchmark");
    lsetdepth(0, 0x7fffff);

    doublebuffer();
    RGBmode();
    gconfig();
    RGBcolor(0, 0, 0);
    clear(); 
    swapbuffers(); 
    clear();
    qdevice(INPUTCHANGE);
    qdevice(REDRAW);
    qdevice(ESCKEY);

    zbuffer(TRUE);
    zclear();
    init_lighting();
    
    lmbind(MATERIAL, MY_MATERIAL);
}

draw_everything()
{
    RGBcolor(0, 0, 0);
    czclear(0, 0xFFFFFFFF);

    mmode(MPROJECTION);
    perspective(400, (float)XMAXSCREEN/YMAXSCREEN, .1, 2);

    mmode(MVIEWING);
    loadmatrix(ident_matrix);

    lmbind(LIGHT0, MY_LIGHT);

    lookat(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0);

    draw_mesh();

    // mmode(MSINGLE); // ??

    swapbuffers();
}
