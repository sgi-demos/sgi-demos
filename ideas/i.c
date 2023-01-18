#include <gl.h>

float i_data[][2] = {
	{0.548767, 9.414791},
	{2.795284, 9.757771},
	{1.457663, 9.311897},
	{2.503751, 9.157557},
	{1.714898, 8.986067},
	{2.109325, 7.785638},
	{1.286174, 7.013934},
	{1.800643, 6.070740},
	{0.994641, 5.161843},
	{1.783494, 4.767417},
	{0.943194, 4.167202},
	{1.852090, 4.304394},
	{1.063237, 3.549839},
	{2.023580, 3.978564},
	{1.406217, 3.172562},
	{2.315113, 3.875670},
	{2.006431, 3.018221},
	{2.812433, 3.944266},
	{2.726688, 3.429796},
	{3.258307, 4.132905},

	{1.989282, 10.923902},
	{2.778135, 12.295820},
	{2.966774, 11.678456},
	{3.687031, 12.947481},

};


draw_i() {

    bgntmesh();
	v2f(i_data[0]);
	v2f(i_data[1]);
	v2f(i_data[2]);
	v2f(i_data[3]);
	v2f(i_data[4]);
	v2f(i_data[5]);
	v2f(i_data[6]);
	v2f(i_data[7]);
	v2f(i_data[8]);
	v2f(i_data[9]);
	v2f(i_data[10]);
	v2f(i_data[11]);
	v2f(i_data[12]);
	v2f(i_data[13]);
	v2f(i_data[14]);
	v2f(i_data[15]);
	v2f(i_data[16]);
	v2f(i_data[17]);
	v2f(i_data[18]);
	v2f(i_data[19]);
    endtmesh();

    bgntmesh();
	v2f(i_data[20]);
	v2f(i_data[21]);
	v2f(i_data[22]);
	v2f(i_data[23]);
    endtmesh();

    bgnline();
	v2f(i_data[0]);
	v2f(i_data[2]);
	v2f(i_data[4]);
	v2f(i_data[6]);
	v2f(i_data[8]);
	v2f(i_data[10]);
	v2f(i_data[12]);
	v2f(i_data[14]);
	v2f(i_data[16]);
	v2f(i_data[18]);
	v2f(i_data[19]);
	v2f(i_data[17]);
	v2f(i_data[15]);
	v2f(i_data[13]);
	v2f(i_data[11]);
	v2f(i_data[9]);
	v2f(i_data[7]);
	v2f(i_data[5]);
	v2f(i_data[3]);
	v2f(i_data[1]);
    endline();

    bgnline();
	v2f(i_data[20]);
	v2f(i_data[22]);
	v2f(i_data[23]);
	v2f(i_data[21]);
    endline();

}

