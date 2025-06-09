#include <gl.h>

float t_data[][2] = {
	{2.986667, 14.034801},
	{2.445128, 10.088024},
	{1.788718, 9.236438},
	{2.264615, 7.664279},
	{1.165128, 5.666326},
	{2.034872, 4.945752},
	{1.132308, 3.766633},
	{2.182564, 3.570113},
	{1.411282, 2.309109},
	{2.510769, 2.341863},
	{2.149744, 1.048106},
	{3.364103, 1.375640},
	{3.167180, 0.327533},
	{4.381538, 0.736950},
	{5.005128, 0.032753},
	{5.612308, 0.638690},
	{6.235898, 0.540430},
	{7.187692, 1.162743},

	{1.985641, 9.039918},
	{2.133333, 10.186285},
	{1.509744, 9.023541},
	{1.608205, 9.662231},
	{1.050256, 9.023541},
	{1.050256, 9.334698},
	{0.196923, 9.007165},

	{2.363077, 9.711361},
	{2.264615, 9.023541},
	{3.282051, 9.563972},
	{3.446154, 9.023541},
	{4.069744, 9.531218},
	{4.299487, 9.236438},
	{4.644103, 9.613101},
	{5.251282, 9.875128},

};

draw_t() {

    bgntmesh();
	v2f(t_data[0]);
	v2f(t_data[1]);
	v2f(t_data[2]);
	v2f(t_data[3]);
	v2f(t_data[4]);
	v2f(t_data[5]);
	v2f(t_data[6]);
	v2f(t_data[7]);
	v2f(t_data[8]);
	v2f(t_data[9]);
	v2f(t_data[10]);
	v2f(t_data[11]);
	v2f(t_data[12]);
	v2f(t_data[13]);
	v2f(t_data[14]);
	v2f(t_data[15]);
	v2f(t_data[16]);
	v2f(t_data[17]);
    endtmesh();

    bgntmesh();
	v2f(t_data[18]);
	v2f(t_data[19]);
	v2f(t_data[20]);
	v2f(t_data[21]);
	v2f(t_data[22]);
	v2f(t_data[23]);
	v2f(t_data[24]);
    endtmesh();

    bgntmesh();
	v2f(t_data[25]);
	v2f(t_data[26]);
	v2f(t_data[27]);
	v2f(t_data[28]);
	v2f(t_data[29]);
	v2f(t_data[30]);
	v2f(t_data[31]);
	v2f(t_data[32]);
    endtmesh();

    bgnline();
	v2f(t_data[0]);
	v2f(t_data[2]);
	v2f(t_data[4]);
	v2f(t_data[6]);
	v2f(t_data[8]);
	v2f(t_data[10]);
	v2f(t_data[12]);
	v2f(t_data[14]);
	v2f(t_data[16]);
	v2f(t_data[17]);
	v2f(t_data[15]);
	v2f(t_data[13]);
	v2f(t_data[11]);
	v2f(t_data[9]);
	v2f(t_data[7]);
	v2f(t_data[5]);
	v2f(t_data[3]);
	v2f(t_data[1]);
    endline();

    bgnline();
	v2f(t_data[18]);
	v2f(t_data[20]);
	v2f(t_data[22]);
	v2f(t_data[24]);
	v2f(t_data[23]);
	v2f(t_data[21]);
	v2f(t_data[19]);
    endline();

    bgnline();
	v2f(t_data[26]);
	v2f(t_data[28]);
	v2f(t_data[30]);
	v2f(t_data[32]);
	v2f(t_data[31]);
	v2f(t_data[29]);
	v2f(t_data[27]);
	v2f(t_data[25]);
    endline();

}

