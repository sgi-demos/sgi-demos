#include <gl.h>
gl_IdentifyMatrix(mat)
Matrix mat;
{
int i,j;

for (i = 0; i < 4; i++)
for (j = 0; j < 4; j++)
mat[i][j] = ((i == j) ? 1.0 : 0.0);
}
