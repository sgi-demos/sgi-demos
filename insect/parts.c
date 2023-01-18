#include <stdio.h>
#include <gl.h>
#include <math.h>
#include <device.h>
#include <democolors.h>
#include "insect.h"

/* For ECLIPSE 8 bit machine */	
extern long nplanes;

Coord b1[4][3] = {
    {
	R1 * SIN30 * -SIN15,
	    R1 * SIN30 * COS15,
	    R1 * COS30
    },

    {
	R1 * SIN30 * SIN15,
	    R1 * SIN30 * COS15,
	    R1 * COS30
    },

    {
	A2 * SIN30,
	    A1,
	    A2 * COS30
    },

    {
	-A2 * SIN30,
	    A1,
	    A2 * COS30
    }
};

Coord b4[4][3] = {
    {
	R1 * SIN30 * -SIN15,
	    R1 * SIN30 * COS15,
	    -R1 * COS30
    },

    {
	-A2 * SIN30,
	    A1,
	    -A2 * COS30
    },

    {
	A2 * SIN30,
	    A1,
	    -A2 * COS30
    },

    {
	R1 * SIN30 * SIN15,
	    R1 * SIN30 * COS15,
	    -R1 * COS30
    }
};

Coord b2[4][3] = {{
	R1 * SIN30 * -SIN45,
	    R1 * SIN30 * COS45,
	    R1 * COS30
},

{
    R1 * SIN30 * -SIN15,
	R1 * SIN30 * COS15,
	R1 * COS30
},

{
    -A2 * SIN30,
	A1,
	A2 * COS30
},

{
    (A2 * SIN30) * COS60 - A1 * SIN60,
	A1 * COS60 + (A2 * SIN30) * SIN60,
	A2 * COS30
}
};

Coord b5[4][3] = {{
	R1 * SIN30 * -SIN45,
	    R1 * SIN30 * COS45,
	    -R1 * COS30
},

{
    (A2 * SIN30) * COS60 - A1 * SIN60,
	A1 * COS60 + (A2 * SIN30) * SIN60,
	-A2 * COS30
},

{
    -A2 * SIN30,
	A1,
	-A2 * COS30
},

{
    R1 * SIN30 * -SIN15,
	R1 * SIN30 * COS15,
	-R1 * COS30
}
};

Coord b3[4][3] = {{
	(A2 * SIN30) * COS60 - A1 * SIN60,
	    A1 * COS60 + (A2 * SIN30) * SIN60,
	    A2 * COS30
},

{
    -A2 * SIN30,
	A1,
	A2 * COS30
},

{
    -A2,
	A1,
	0
},

{
    (A2) * COS60 - A1 * SIN60,
	A1 * COS60 + (A2) * SIN60,
	0
}
};

Coord b6[4][3] = {{
	(A2 * SIN30) * COS60 - A1 * SIN60,
	    A1 * COS60 + (A2 * SIN30) * SIN60,
	    -A2 * COS30
},

{
    (A2) * COS60 - A1 * SIN60,
	A1 * COS60 + (A2) * SIN60,
	0.0
},

{
    -A2,
	A1,
	0.0
},

{
    -A2 * SIN30,
	A1,
	-A2 * COS30
}
};

Coord h1[4][3] = {{
	A2, -A2, 0.0
},

{
    R2, 0.0, 0.0
},

{
    R2 * COS60,
	0,
	R2 * SIN60
},

{
    A2 * COS60,
	-A2,
	A2 * SIN60
}

};

Coord h2[4][3] = {{
	R2 * COS60,
	    0.0,
	    R2 * SIN60
},

{
    R2, 0.0, 0.0
},

{
    A2, A2, 0.0
},

{
    A2 * COS60,
	A2,
	A2 * SIN60
}
};

Coord h3[3][3] = {{
	A2, A2, 0.0
},

{
    0.0, R2, 0.0
},

{
    A2 * COS60,
	A2,
	A2 * SIN60
},
};

Coord t1[4][3] = {{
	-A2 * COS60,
	    A2,
	    A2 * SIN60
},

{
    A2 * COS60,
	A2,
	A2 * SIN60
},

{
    A2 * COS60,
	1 - A2 * COS60,
	A2 * SIN60
},

{
    -A2 * COS60,
	1 - A2 * COS60,
	A2 * SIN60
}
};

Coord t2[3][3] = {{
	-A2 * COS60,
	    A2,
	    A2 * SIN60
},

{
    -A2 * COS60,
	1 - A2 * COS60,
	A2 * SIN60
},

{
    -A2,
	A2,
	0.0
}
};

Coord t6[3][3] = {{
	-A2 * COS60,
	    A2,
	    -A2 * SIN60
},

{
    -A2,
	A2,
	0.0
},

{
    -A2 * COS60,
	1 - A2,
	0.0
}

};

Coord t3[3][3] = {{
	A2 * COS60,
	    A2,
	    A2 * SIN60
},

{
    A2,
	A2,
	0.0
},

{
    A2 * COS60,
	1 - A2 * COS60,
	A2 * SIN60
}
};

Coord t7[3][3] = {{
	A2 * COS60,
	    A2,
	    -A2 * SIN60
},

{
    A2 * COS60,
	1 - A2,
	0.0
},

{
    A2,
	A2,
	0.0
}
};

Coord t4[3][3] = {{
	-A2 * COS60,
	    1.0 - A2 * COS60,
	    A2 * SIN60
},

{
    -A2 * COS60,
	1.0 - A2,
	0.0
},

{
    -A2,
	A2,
	0.0
}
};

Coord t5[3][3] = {{
	A2 * COS60,
	    1.0 - A2 * COS60,
	    A2 * SIN60
},

{
    A2,
	A2,
	0.0
},

{
    A2 * COS60,
	1 - A2,
	0.0
}
};

Coord t8[4][3] = {{
	A2 * COS60,
	    A2,
	    -A2 * SIN60
},

{
    -A2 * COS60,
	A2,
	-A2 * SIN60
},

{
    -A2 * COS60,
	1 - A2,
	0.0
},

{
    A2 * COS60,
	1 - A2,
	0.0
}
};

Coord s1[4][3] = {{
	A2 * COS60,
	    -A2 * COS60,
	    -A2 * SIN60
},

{
    A2 * COS60 * 0.4,
	A2 * COS60 - 2.0,
	-A2 * SIN60 * 0.4
},

{
    -A2 * COS60 * 0.4,
	A2 * COS60 - 2.0,
	-A2 * SIN60 * 0.4
},

{
    -A2 * COS60,
	-A2 * COS60,
	-A2 * SIN60
}

};

Coord s2[4][3] = {{
	A2 * COS60,
	    -A2 * COS60,
	    -A2 * SIN60
},

{
    A2 * COS60,
	-A2,
	0.0
},

{
    A2 * COS60 * 0.4,
	-2.0,
	0.0
},

{
    A2 * COS60 * 0.4,
	A2 * COS60 - 2.0,
	-A2 * SIN60 * 0.4
}

};

Coord s3[4][3] = {{
	-A2 * COS60,
	    -A2 * COS60,
	    -A2 * SIN60
},

{
    -A2 * COS60 * 0.4,
	A2 * COS60 - 2.0,
	-A2 * SIN60 * 0.4
},

{
    -A2 * COS60 * 0.4,
	-2.0,
	0.0
},

{
    -A2 * COS60,
	-A2,
	0.0
}

};

Coord s4[4][3] = {{
	A2 * COS60,
	    -A2,
	    0.0
},

{
    -A2 * COS60,
	-A2,
	0.0
},

{
    -A2 * COS60 * 0.4,
	-2.0,
	0.0
},

{
    A2 * COS60 * 0.4,
	-2.0,
	0.0
}

};

Coord s5[4][3] = {{
	A2 * COS60 * 0.4,
	    -2.0,
	    0.0
},

{
    -A2 * COS60 * 0.4,
	-2.0,
	0.0
},

{
    -A2 * COS60 * 0.4,
	A2 * COS60 - 2.0,
	-A2 * SIN60 * 0.4
},

{
    A2 * COS60 * 0.4,
	A2 * COS60 - 2.0,
	-A2 * SIN60 * 0.4
}
};

Coord k1[4][3] = {{
	-A2 * COS60,
	    1.0 - A2 * COS60,
	    A2 * SIN60
},

{
    A2 * COS60,
	1.0 - A2 * COS60,
	A2 * SIN60
},

{
    A2 * COS60,
	1.0 + A2 * COS60,
	A2 * SIN60
},

{
    -A2 * COS60,
	1.0 + A2 * COS60,
	A2 * SIN60
}
};

/*	make display list objects
	screen -- for checkerboard floor
	shadow -- matrix to project insect onto flat surface
	viewit -- viewing transformation
	and various parts of the body and their shadows
*/

createobjects () {
    int     i,
            j,
            k;

    makeobj (screen = genobj ());

    shademodel(FLAT);

/* Changed for ECLIPSE 8 bit machine */
    if (nplanes == 4)
	color (ECLIPSE8_GRID);
    else
	color (GRID);

    k = 1;
    for (i = -8; i < 7; i++)
	for (j = -8; j < 7; j++) {
	    if (k == 0) {
		scr[0][0] = i * 3;
		scr[0][1] = j * 3;
		scr[1][0] = (i + 1) * 3;
		scr[1][1] = j * 3;
		scr[2][0] = (i + 1) * 3;
		scr[2][1] = (j + 1) * 3;
		scr[3][0] = i * 3;
		scr[3][1] = (j + 1) * 3;
		polf2i (4, scr);
	    }
	    k = 1 - k;
	}
    closeobj ();

    makeobj (shadow = genobj ());

    shademodel(FLAT);

    {
	float   sx,
	        sy,
	        sz;
	Matrix mshadow;
	sx = -1.0;
	sy = -1.0;
	sz = 1.0;
	gl_IdentifyMatrix (mshadow);
	mshadow[2][0] = -sx / sz;
	mshadow[2][1] = -sy / sz;
	mshadow[2][2] = 0.;
	multmatrix (mshadow);
    }
    color (BLACK);
    closeobj ();

    makeobj (viewit = genobj ());
    window (-8.0, 8.0, -8.0 * 0.75, 8.0 * 0.75, 10.0, 135.0);
    maketag (windowtag = gentag ());
    perspective (800, (float)XMAXSCREEN/YMAXSCREEN, 0.01, 131072.);
    maketag (cthetatag = gentag ());
    rotate (ctheta, 'x');
    maketag (cphitag = gentag ());
    rotate (cphi, 'z');
    maketag (cposittag = gentag ());
    translate (cx, cy, cz);
    closeobj ();

    for (i = 0; i < 12; i++) {
	b7[i][2] = R1 * SIN60;
	b7[i][0] = R1 * COS60 * cos ((float) i * (PI / 6.0) + (PI / 12.0));
	b7[i][1] = R1 * COS60 * sin ((float) i * (PI / 6.0) + (PI / 12.0));
	b8[11 - i][2] = -R1 * SIN60;
	b8[11 - i][0] = R1 * COS60 * cos ((float) i * (PI / 6.0) + (PI / 12.0));
	b8[11 - i][1] = R1 * COS60 * sin ((float) i * (PI / 6.0) + (PI / 12.0));
    }

    for (i = 0; i < 6; i++) {
	k2[i][0] = A2 * COS60;
	k2[i][1] = A2 * cos ((float) i * (PI / 3.0)) + 1.0;
	k2[i][2] = A2 * sin ((float) i * (PI / 3.0));
	k3[5 - i][0] = -A2 * COS60;
	k3[5 - i][1] = A2 * cos ((float) i * (PI / 3.0)) + 1.0;
	k3[5 - i][2] = A2 * sin ((float) i * (PI / 3.0));
    }

    makeobj (body = genobj ());

    shademodel(FLAT);

    backface (TRUE);
    getpolycolor (0, b7);
    polf (12, b7);
    getpolycolor (0, b8);
    polf (12, b8);
    getpolycolor (0, b1);
    polf (4, b1);
    getpolycolor (0, b2);
    polf (4, b2);
    getpolycolor (0, b3);
    polf (4, b3);
    getpolycolor (0, b4);
    polf (4, b4);
    getpolycolor (0, b5);
    polf (4, b5);
    getpolycolor (0, b6);
    polf (4, b6);
    for (i = 0; i < 5; i++) {
	rotate60 ('z', 4, b1);
	rotate60 ('z', 4, b2);
	rotate60 ('z', 4, b3);
	rotate60 ('z', 4, b4);
	rotate60 ('z', 4, b5);
	rotate60 ('z', 4, b6);
	getpolycolor (0, b1);
	polf (4, b1);
	getpolycolor (0, b2);
	polf (4, b2);
	getpolycolor (0, b3);
	polf (4, b3);
	getpolycolor (0, b4);
	polf (4, b4);
	getpolycolor (0, b5);
	polf (4, b5);
	getpolycolor (0, b6);
	polf (4, b6);
    }
    backface (FALSE);
    closeobj ();

    makeobj (body_shadow = genobj ());

    shademodel(FLAT);

    color (BLACK);
    if (lit (3, b7))
	polf (12, b7);
    if (lit (3, b1))
	polf (4, b1);
    if (lit (3, b2))
	polf (4, b2);
    if (lit (3, b3))
	polf (4, b3);
    if (lit (3, b4))
	polf (4, b4);
    if (lit (3, b5))
	polf (4, b5);
    if (lit (3, b6))
	polf (4, b6);
    for (i = 0; i < 5; i++) {
	rotate60 ('z', 4, b1);
	rotate60 ('z', 4, b2);
	rotate60 ('z', 4, b3);
	rotate60 ('z', 4, b4);
	rotate60 ('z', 4, b5);
	rotate60 ('z', 4, b6);
	if (lit (3, b1))
	    polf (4, b1);
	if (lit (3, b2))
	    polf (4, b2);
	if (lit (3, b3))
	    polf (4, b3);
	if (lit (3, b4))
	    polf (4, b4);
	if (lit (3, b5))
	    polf (4, b5);
	if (lit (3, b6))
	    polf (4, b6);
    }
    closeobj ();

    for (j = 0; j < 6; j++) {
	makeobj (hip[j] = genobj ());

    shademodel(FLAT);

	backface (TRUE);
	getpolycolor (1, h1);
	polf (4, h1);
	getpolycolor (1, h2);
	polf (4, h2);
	getpolycolor (1, h3);
	polf (3, h3);
	for (i = 0; i < 5; i++) {
	    rotate60 ('y', 4, h1);
	    rotate60 ('y', 4, h2);
	    rotate60 ('y', 3, h3);
	    getpolycolor (1, h1);
	    polf (4, h1);
	    getpolycolor (1, h2);
	    polf (4, h2);
	    getpolycolor (1, h3);
	    polf (3, h3);
	}
	phi += PI / 3.0;
	getlightvector ();
	backface (FALSE);
	closeobj ();
    }

    makeobj (hip_shadow = genobj ());

    shademodel(FLAT);

    /*backface (TRUE);*/
    color (BLACK);
    polf (4, h1);
    polf (4, h2);
    polf (3, h3);
    for (i = 0; i < 5; i++) {
	rotate60 ('y', 4, h1);
	rotate60 ('y', 4, h2);
	rotate60 ('y', 3, h3);
	polf (4, h1);
	polf (4, h2);
	polf (3, h3);
    }
    /*backface (FALSE);*/
    closeobj ();

    phi = 0.0;
    theta = PI / 4.0;
    getlightvector ();
    for (j = 0; j < 6; j++) {
	makeobj (thigh[j] = genobj ());

    shademodel(FLAT);

	backface (TRUE);
	getpolycolor (2, t1);
	polf (4, t1);
	getpolycolor (2, t2);
	polf (3, t2);
	getpolycolor (2, t3);
	polf (3, t3);
	getpolycolor (2, t4);
	polf (3, t4);
	getpolycolor (2, t5);
	polf (3, t5);
	getpolycolor (2, t6);
	polf (3, t6);
	getpolycolor (2, t7);
	polf (3, t7);
	getpolycolor (2, t8);
	polf (4, t8);
	backface (FALSE);
	closeobj ();
	makeobj (kneeball[j] = genobj ());

    shademodel(FLAT);

	backface (TRUE);
	getpolycolor (3, k1);
	polf (4, k1);
	for (k = 0; k < 4; k++)
	    k1[k][1] -= 1.0;
	rotate60 ('x', 4, k1);
	for (k = 0; k < 4; k++)
	    k1[k][1] += 1.0;
	for (i = 0; i < 5; i++) {
	    if (i != 0) {
		getpolycolor (3, k1);
		polf (4, k1);
	    }
	    for (k = 0; k < 4; k++)
		k1[k][1] -= 1.0;
	    rotate60 ('x', 4, k1);
	    for (k = 0; k < 4; k++)
		k1[k][1] += 1.0;
	}
	getpolycolor (3, k2);
	polf (6, k2);
	getpolycolor (3, k3);
	polf (6, k3);
	backface (FALSE);
	closeobj ();
	makeobj (shin[j] = genobj ());

    shademodel(FLAT);

	backface (TRUE);
	getpolycolor (4, s1);
	polf (4, s1);
	getpolycolor (4, s2);
	polf (4, s2);
	getpolycolor (4, s3);
	polf (4, s3);
	getpolycolor (4, s4);
	polf (4, s4);
	getpolycolor (4, s5);
	polf (4, s5);
	backface (FALSE);
	closeobj ();
	theta -= PI / 3.0;
	getlightvector ();
    }
    makeobj (thigh_shadow = genobj ());

    shademodel(FLAT);

    /*backface (TRUE);*/
    color (BLACK);
    polf (4, t1);
    polf (3, t2);
    polf (3, t3);
    polf (3, t4);
    polf (3, t5);
    polf (3, t6);
    polf (3, t7);
    polf (4, t8);
    /*backface (FALSE);*/
    closeobj ();
    makeobj (kneeball_shadow = genobj ());

    shademodel(FLAT);

    /*backface (TRUE);*/
    color (BLACK);
    polf (4, k1);
    for (k = 0; k < 4; k++)
	k1[k][1] -= 1.0;
    rotate60 ('x', 4, k1);
    for (k = 0; k < 4; k++)
	k1[k][1] += 1.0;
    for (i = 0; i < 5; i++) {
	if (i != 0) {
	    polf (4, k1);
	}
	for (k = 0; k < 4; k++)
	    k1[k][1] -= 1.0;
	rotate60 ('x', 4, k1);
	for (k = 0; k < 4; k++)
	    k1[k][1] += 1.0;
    }
    polf (6, k2);
    polf (6, k3);
    /*backface (FALSE);*/
    closeobj ();
    makeobj (shin_shadow = genobj ());

    shademodel(FLAT);

    /*backface (TRUE);*/
    color (BLACK);
    polf (4, s1);
    polf (4, s2);
    polf (4, s3);
    polf (4, s4);
    polf (4, s5);
    /*backface (FALSE);*/
    closeobj ();

}
