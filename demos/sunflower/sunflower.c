/*
sunflower.c

Make a sunflower-like pattern out of circles.
    Usage: sunflower <<nseeds> <<seedsize> <<growth>
Try "sunflower 400.05 1.1"

Paul Haeberli - 1984
*/

#include <gl.h>
#include <device.h>
#include <stdio.h>
#include <math.h>

int seeds = 0;

main(argc,argv)
int argc;
char **argv;
{
   int nseeds;
   float seedsize, grow;
   short val;    

   if (argc<4) {
      fprintf(stderr,
          "Usage: sunflower <nseeds> <seedsize> <growth>\n");
      exit(1);
   }

   nseeds = atoi(argv[1]);
   seedsize = atof(argv[2]);
   grow = atof(argv[3]);    
   prefposition(XMAXSCREEN/4,XMAXSCREEN*3/4,YMAXSCREEN/4,
       YMAXSCREEN*3/4);
   winopen("sunflower");
        /*singlebuffer(); TODO*/
        zbuffer (FALSE); 
        /*cmode(); TODO*/
    gconfig (); 
   makeframe();
   sunflower(nseeds,seedsize,grow);
   while (1) {
      if (qread(&val) == REDRAW)  {
         makeframe();
         sunflower(nseeds,seedsize,grow);
      }
   }

}

sunflower(nseeds,seedsize,grow)
int nseeds;
float seedsize, grow;
{

   float rad = 20.0;
   int parity = 0;    

   scale(10.0,10.0,0.0);
   pushmatrix();
   while (rad < 100.0) {
      rotate(1800/nseeds,'z');
      scale(grow,grow,0.0);
      makering(nseeds,seedsize);
      rad = rad * grow;
   }

   popmatrix();
}

makering(nseeds,seedsize)
int nseeds;
float seedsize;
{
   int i;

   for (i=0; i<nseeds; i++) {
      pushmatrix();
      rotate((i*3600)/nseeds,'z');
      drawseed(seedsize);
      popmatrix();
   }

}

drawseed(seedsize)
float seedsize;
{
   seeds++;
   circfs(1.0,0.0,seedsize);
}

makeframe()
{

   int xsize, ysize;
   float aspect;    

   reshapeviewport();
   getsize(&xsize,&ysize);
   color(7);
   clear();
   color(0);
   aspect = xsize/(float)ysize;
   ortho2(-50.0,50.0,-50.0/aspect,50.0/aspect);
}