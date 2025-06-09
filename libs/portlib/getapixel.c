/* 
 *	getapixel - 
 *		Read a pixel from a specific screen location.
 *
 *				Paul Haeberli - 1985
 */
#include "gl.h"
#include "device.h"

getapixel(mousex, mousey)
short mousex, mousey;
{
    short pixel;

    pushviewport();
    pushmatrix();
    pushattributes();
    screenspace();
    cmov2i(mousex, mousey); 
    readpixels(1,&pixel);
    popviewport();
    popmatrix();
    popattributes();
    return(pixel);
}
