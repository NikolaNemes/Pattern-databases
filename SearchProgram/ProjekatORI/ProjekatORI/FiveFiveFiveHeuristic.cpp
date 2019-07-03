#include "Heuristic.h"

void initialize_partitions(int****** p1, int****** p2, int****** p3)
{
	int***** partition1 = *p1;
	int***** partition2 = *p2;
	int***** partition3 = *p3;
	
	ifstream file1;
	ifstream file2;
	ifstream file3;

	file1.open("parition1.txt");
	file2.open("parition2.txt");
	file3.open("parition3.txt");

	for (int i1 = 0; i1 < 16; i1++)
	{
		partition1[i1] = new int***[16];
		partition2[i1] = new int***[16];
		partition3[i1] = new int***[16];
		for (int i2 = 0; i2 < 16; i2++)
		{
			partition1[i1][i2] = new int**[16];
			partition2[i1][i2] = new int**[16];
			partition3[i1][i2] = new int**[16];
			for (int i3 = 0; i3 < 16; i3++)
			{
				partition1[i1][i2][i3] = new int*[16];
				partition2[i1][i2][i3] = new int*[16];
				partition3[i1][i2][i3] = new int*[16];
				for (int i4 = 0; i4 < 16; i4++)
				{
					partition1[i1][i2][i3][i4] = new int[16];
					partition2[i1][i2][i3][i4] = new int[16];
					partition3[i1][i2][i3][i4] = new int[16];
					for (int i5 = 0; i5 < 16; i5++)
					{
						 file1 >> partition1[i1][i2][i3][i4][i5];
						 file2 >> partition2[i1][i2][i3][i4][i5];
						 file3 >> partition3[i1][i2][i3][i4][i5];
					}
				}
			}
		}
	}
}

void initialize_partitions(int***** p1, int***** p2, int***** p3)
{

}



int five_five_five_heuristic(int***** p1, int***** p2, int***** p3, int* state)
{
	int indexes[16] = { 0,0,0,0,
					    0,0,0,0,
					    0,0,0,0,
					    0,0,0,0 };
	for (int i = 0; i < 16; i++)
	{
		indexes[state[i]] = i;
	}
	int total1 = p1[indexes[1]][indexes[2]][indexes[4]][indexes[5]][indexes[8]];
	int total2 = p2[indexes[3]][indexes[6]][indexes[7]][indexes[10]][indexes[11]];
	int total3 = p3[indexes[9]][indexes[12]][indexes[13]][indexes[14]][indexes[15]];
	return total1 + total2 + total3;
}