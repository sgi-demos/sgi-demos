/* #include "democolors.h" */
#ifndef DEMOCOLORDEF
#define DEMOCOLORDEF

#define BUBBLE  1
#define NONBUBBLE 0

int m_type = NONBUBBLE; 

int CLOCKCOLOR[2] = {800+32+32+8,21};
int ARCHCOLORS[2] = {576,128};
int NARCHCOLORS[2] = {64,64};
int ROBOTCOLORS[2] = {528,192};
int LIGHTCOLORS[2] = {96,125};
int LIGHTBACK[2] = {992,224};

int GRAY = 43;
int GRID = 44;
int SKYBLUE = 45;
int RAMPB = 46;
int RAMPE = 55;
int RAMPB2 = 56;
int RAMPE2 = 65;
int RAMPB3 = 66;
int RAMPE3 = 75;
int RAMPB4 = 76;
int RAMPE4 = 85;
int RAMPB5 = 86;
int RAMPE5 = 95;


int GREYRAMP[2] = {640,192}; 
int NGREYRAMP[2] = {128,64};
int GREYRAMP2  = 128;

int CUENUM[2] = {32,16};
int CUECOLOR0[2] = {768,32};                                        /* red */
int CUECOLOR1[2] = {800,32};                                        /* red */
int JETCOLORS[2] = {800,32};
int NJETCOLORS[2] = { 32,16};
int CUECOLOR2[2] = {800+32, 32+16};                                 /* yellow */
int CUECOLOR3[2] = {800+32+32, 32+16+16};                           /* white */
int CUECOLOR4[2] = {800+32+32+32, 32+16+16+16};                     /* purple */
int CUECOLOR5[2] = {800+32+32+32+32, 32+16+16+16+16};               /* cyan */
int CUECOLOR6[2] = {800+32+32+32+32+32, 32+16+16+16+16+16};         /* green */

int SHUTTLE_BODY[2] = {800+32+32, 32+16+16};
int SHUTTLE_DOOR[2] = {800, 32};
/*int SHUTTLE_AXES[2] = {64,14};*/
int SHUTTLE_BKGD[2] = {800+32+32+32+32,15};

int NHEMECOLORS[2] = {704,96};

int SURFCOLORS0[2] = {512,29}; /* see  surfdemo/setupcolors.c */
int SURFCOLORS1[2] = {0,30};
int SURFCOLORS2[2] = {0,31};

int SINGLE1_SWIZZLE[2] = {800+32+32+32+32+16, 18};
int SINGLE2_SWIZZLE[2] = {800+32+32+32+24, 19};
int DOUBLE1_SWIZZLE[2] = {800+32+32+32+32+16, 18};
int DOUBLE2_SWIZZLE[2] = {800+32+32+32+24, 19};

int DITHERRAMPS = 256;

#endif // DEMOCOLORDEF
