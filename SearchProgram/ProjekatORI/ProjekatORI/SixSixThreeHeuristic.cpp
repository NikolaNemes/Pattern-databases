#include "Heuristic.h"

tiny_dnn::network<tiny_dnn::sequential> partition1nn;
tiny_dnn::network<tiny_dnn::sequential> partition2nn;
tiny_dnn::network<tiny_dnn::sequential> partition3nn;
tiny_dnn::vec_t x1(96);
tiny_dnn::vec_t x2(96);
tiny_dnn::vec_t x3(48);

void initialize_neural_networks()
{
	partition1nn.load("../NeuralNetworks/partition1Encoded");
	partition2nn.load("../NeuralNetworks/partition2Encoded");
	partition3nn.load("../NeuralNetworks/partition3Encoded");
	for (int i = 0; i < 96; i++)
	{
		x1[i] = 0;
		x2[i] = 0;
	}
	for (int i = 0; i < 48; i++)
	{
		x3[i] = 0;
	}
}

void initialize_partitions663(int****** p1, int****** p2, int*** p3)
{
	FILE* file1;
	FILE* file2;
	FILE* file3;

	fopen_s(&file1, "../Tables/partition1.bin", "rb");
	fopen_s(&file2, "../Tables/partition2.bin", "rb");
	fopen_s(&file3, "../Tables/partition3.bin", "rb");


	for (int i1 = 0; i1 < 16; i1++)
	{
		p1[i1] = new int****[16];
		p2[i1] = new int****[16];
		p3[i1] = new int*[16];
		for (int i2 = 0; i2 < 16; i2++)
		{
			p1[i1][i2] = new int***[16];
			p2[i1][i2] = new int***[16];
			p3[i1][i2] = new int[16];
			fread(p3[i1][i2], 4, 16, file3);
			for (int i3 = 0; i3 < 16; i3++)
			{
				p1[i1][i2][i3] = new int**[16];
				p2[i1][i2][i3] = new int**[16];
				for (int i4 = 0; i4 < 16; i4++)
				{
					p1[i1][i2][i3][i4] = new int*[16];
					p2[i1][i2][i3][i4] = new int*[16];
					for (int i5 = 0; i5 < 16; i5++)
					{
						p1[i1][i2][i3][i4][i5] = new int[16];
						p2[i1][i2][i3][i4][i5] = new int[16];
						fread(p1[i1][i2][i3][i4][i5], 4, 16, file1);
						fread(p2[i1][i2][i3][i4][i5], 4, 16, file2);
					}
				}
			}
		}
	}
}

int calculate_six_six_three(int****** p1, int****** p2, int*** p3, int* indexes)
{
	int total1 = p1[indexes[1]][indexes[2]][indexes[4]][indexes[5]][indexes[8]][indexes[9]];
	int total2 = p2[indexes[3]][indexes[6]][indexes[7]][indexes[10]][indexes[11]][indexes[15]];
	int total3 = p3[indexes[12]][indexes[13]][indexes[14]];
	int my_total = total1 + total2 + total3;
	return my_total;
}

int calculate_neural(int* indexes)
{
	x1[indexes[1]] = 1;
	x1[indexes[2] + 16] = 1;
	x1[indexes[4] + 32] = 1;
	x1[indexes[5] + 48] = 1;
	x1[indexes[8] + 64] = 1;
	x1[indexes[9] + 80] = 1;

	int total1 = partition1nn.predict(x1)[0];

	x1[indexes[1]] = 1;
	x1[indexes[2] + 16] = 1;
	x1[indexes[4] + 32] = 1;
	x1[indexes[5] + 48] = 1;
	x1[indexes[8] + 64] = 1;
	x1[indexes[9] + 80] = 1;

	x2[indexes[3]] = 1;
	x2[indexes[6] + 16] = 1;
	x2[indexes[7] + 32] = 1;
	x2[indexes[10] + 48] = 1;
	x2[indexes[11] + 64] = 1;
	x2[indexes[15] + 80] = 1;

	int total2 = partition2nn.predict(x2)[0];

	x2[indexes[3]] = 0;
	x2[indexes[6] + 16] = 0;
	x2[indexes[7] + 32] = 0;
	x2[indexes[10] + 48] = 0;
	x2[indexes[11] + 64] = 0;
	x2[indexes[15] + 80] = 0;

	x3[indexes[12]] = 1;
	x3[indexes[13] + 16] = 1;
	x3[indexes[14] + 32] = 1;

	int total3 = partition3nn.predict(x3)[0];

	x3[indexes[12]] = 0;
	x3[indexes[13] + 16] = 0;
	x3[indexes[14] + 32] = 0;

	return total1 + total2 + total3;

}


int calculate_neural_p663_mix(int****** p1, int****** p2, int*** p3, int* indexes)
{
	int total1 = p1[indexes[1]][indexes[2]][indexes[4]][indexes[5]][indexes[8]][indexes[9]];
	int total2 = p2[indexes[3]][indexes[6]][indexes[7]][indexes[10]][indexes[11]][indexes[15]];
	x3[indexes[12]] = 1;
	x3[indexes[13] + 16] = 1;
	x3[indexes[14] + 32] = 1;

	int total3 = partition3nn.predict(x3)[0];

	x3[indexes[12]] = 0;
	x3[indexes[13] + 16] = 0;
	x3[indexes[14] + 32] = 0;

	int total3real = p3[indexes[12]][indexes[13]][indexes[14]];
	return total1 + total2 + total3;
}


int six_six_three_heuristic(int****** p1, int****** p2, int*** p3, int* state, Heuristic heuristic_enum)
{
	int indexes[16] = { 0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0 };
	for (int i = 0; i < 16; i++)
	{
		indexes[state[i]] = i;
	}


	if (heuristic_enum == MANHATTAN)
	{
		return  manhattan_heuristic(state);
	}
	else if (heuristic_enum == P663)
	{
		return calculate_six_six_three(p1, p2, p3, indexes);
	}
	else if (heuristic_enum == MANHHATTAN_ANDP663)
	{
		int my_total = calculate_six_six_three(p1, p2, p3, indexes);
		int manhattan = manhattan_heuristic(state);

		if (my_total > manhattan)
		{
			return my_total;
		}
		else
		{
			return manhattan;
		}
	}
	else if (heuristic_enum == NEURAL)
	{
		return calculate_neural(indexes);
	}
	else
	{
		return calculate_neural_p663_mix(p1, p2, p3, indexes);
	}
}