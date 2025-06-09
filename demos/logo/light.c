/*
 *  light.c
 */

#include "gl.h"
#include "light.h"

static int curmaterial = 0;

/*
 *  materials
 */
float mat_logo[] = {
	AMBIENT,	0.0, 0.0, 0.0,
	DIFFUSE,	0.8, 0.4, 1.0,
	SPECULAR,	1.0, 1.0, 1.0,
	SHININESS,	20.0,
	LMNULL};


/*
 *  lights
 */
float light1[] = {
	AMBIENT, 0.0, 0.0, 0.0, 
	LCOLOR,   1.0, 1.0, 1.0, 
	POSITION, 1.0, 0.0, 0.0, 0.0, 
	LMNULL};

float light2[] = {
	AMBIENT, 0.0, 0.0, 0.0, 
	LCOLOR,   0.5, 0.1, 0.0, 
	POSITION, 0.0, -1.0, 0.0, 0.0, 
	LMNULL};

/*
 *  lighting models
 */
float infinite[] = {
	AMBIENT, 0.3,  0.3, 0.3, 
	LOCALVIEWER, 0.0, 
	LMNULL};


init_lighting()
{
	lmdef (DEFMATERIAL, MAT_LOGO, 0, mat_logo);

	lmdef (DEFLIGHT, OVER_LIGHT, 0, light1);
	lmdef (DEFLIGHT, UNDER_LIGHT, 0, light2);

	lmdef (DEFLMODEL, INFINITE, 0, infinite);

	lmbind(LIGHT0, OVER_LIGHT);
	lmbind(LIGHT1, UNDER_LIGHT);

	/*
     *  load the lighting model and then turn off lighting
     */
	lmbind(LMODEL, INFINITE);
	lmbind(LMODEL, 0);
}


lighting(b)
int b;
{
	if (b)
		lmbind(LMODEL, INFINITE);
	else
		lmbind(LMODEL, 0);
}


setmaterial(name)
{
	if (name != curmaterial) {
		curmaterial = name;
		lmbind(MATERIAL, name);
	}
}
