#include "Heuristic.h"

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
	int total1 = p1[indexes[1]][indexes[2]][indexes[4]][indexes[5]][indexes[8]][indexes[9]];
	int total2 = p2[indexes[3]][indexes[6]][indexes[7]][indexes[10]][indexes[11]][indexes[15]];
	int total3 = p3[indexes[12]][indexes[13]][indexes[14]];

	int my_total = total1 + total2 + total3;

	int manhattan = manhattan_heuristic(state);

	if (heuristic_enum == MANHATTAN)
	{
		return manhattan;
	}
	else if (heuristic_enum == P663)
	{
		return my_total;
	}
	else
	{
		if (my_total > manhattan)
		{
			return my_total;
		}
		else
		{
			return manhattan;
		}
	}
}