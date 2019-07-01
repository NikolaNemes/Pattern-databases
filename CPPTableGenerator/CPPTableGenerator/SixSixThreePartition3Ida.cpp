//Particija za plocice: 12, 13, 14 0 + AKCIJA(1)
//ukupan broj clanova: 16*15*14=3360
#include "SixSixThreePartition.h"

#define INDEX_COUNT 4
#define CHUNK_SIZE 5
#define SLOT_COUNT 40000000
#define ACTION_OFFSET 4

using namespace std;

int**** initialize_table6633ida()
{
	int**** retval = new int***[16];
	for (int i1 = 0; i1 < 16; i1++)
	{
		retval[i1] = new int**[16];
		for (int i2 = 0; i2 < 16; i2++) {
			retval[i1][i2] = new int*[16];
			for (int i3 = 0; i3 < 16; i3++)
			{
				retval[i1][i2][i3] = new int[16];
				for (int i4 = 0; i4 < 16; i4++)
				{
					retval[i1][i2][i3][i4] = -1;
				}
			}
		}
	}
	return retval;
}

void clear_table6633ida(int**** table)
{
	for (int i1 = 0; i1 < 16; i1++)
	{
		for (int i2 = 0; i2 < 16; i2++)
		{
			for (int i3 = 0; i3 < 16; i3++)
			{
				delete[] table[i1][i2][i3];
			}
			delete[] table[i1][i2];
		}
		delete[] table[i1];
	}
	delete[] table;
}

void initialize_table_partition6633ida()
{
	int**** table = initialize_table6633ida();
	MemoryBank memory_bank(16, 30000);
	int depth = 0;
	int counter = 0; //we want to find 3360*13=43360
	while (true)
	{
		depth++;
		cout << "Depth: " << depth << endl;
		dfs(table, memory_bank, depth);

	}
}

void dfs(int**** table, MemoryBank& memory_bank, int depth)
{
	
}