
#include <stdlib.h>
#include <gl.h>
#include "arena.h"

extern Object cannon_hit[3];

explode(v)
    struct thing *v;
{
    v->torso_x_rot = ROLL(3600);
    v->torso_z_rot = ROLL(3600);
    v->anckle_rot = ROLL(3600);
    v->knee_rot = ROLL(3600);
}

boom()
{
    int i;
    float sf;

    color(RED);

    for (i = 0; i < 10; i++)
    {
	pushmatrix();
	translate(ROLL(100)*0.003, ROLL(100)*0.003, ROLL(100)*0.003);
	rotate(-ROLL(1800), 'x');
	rotate(ROLL(3600), 'z');
	sf = (ROLL(10) / 10.0) + 1.0;
	scale(sf, sf, sf);
	callobj(cannon_hit[ROLL(3)]);
	popmatrix();
    }
}
