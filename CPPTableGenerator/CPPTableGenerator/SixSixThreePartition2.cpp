//Particija za plocice : 3, 6, 7, 10, 11, 15
//ukupan broj clanova: 16*15*14*13*12*11= 5.765.760
#include "SixSixThreePartition.h"

#define INDEX_COUNT 6
#define SLOT_COUNT 1000000

using namespace std;

/*

int****** initialize_table6632()
{
	int****** retval = new int*****[16];
	for (int i1 = 0; i1 < 16; i1++)
	{
		retval[i1] = new int****[16];
		for (int i2 = 0; i2 < 16; i2++)
		{
			retval[i1][i2] = new int***[16];
			for (int i3 = 0; i3 < 16; i3++)
			{
				retval[i1][i2][i3] = new int**[16];
				for (int i4 = 0; i4 < 16; i4++)
				{
					retval[i1][i2][i3][i4] = new int*[16];
					for (int i5 = 0; i5 < 16; i5++)
					{
						retval[i1][i2][i3][i4][i5] = new int[16];
						for (int i6 = 0; i6 < 16; i6++)
						{
							retval[i1][i2][i3][i4][i5][i6] = -1;
						}
					}
				}
			}
		}
	}
	return retval;
}

void clear_table6632(int****** table)
{
	for (int i1 = 0; i1 < 16; i1++)
	{
		for (int i2 = 0; i2 < 16; i2++)
		{
			for (int i3 = 0; i3 < 16; i3++)
			{
				for (int i4 = 0; i4 < 16; i4++)
				{
					for (int i5 = 0; i5 < 16; i5++)
					{
						delete[] table[i1][i2][i3][i4][i5];
					}
					delete[] table[i1][i2][i3][i4];
				}
				delete[] table[i1][i2][i3];
			}
			delete[] table[i1][i2];
		}
		delete[] table[i1];
	}
	delete[] table;
}

int find_index6632(int* current_indices, int value)
{
	for (int i = 0; i < INDEX_COUNT; i++)
	{
		if (current_indices[i] == value)
		{
			return i;
		}
	}
	return -1;
}


void fill_successor6632(int* current_indices, int* to_fill, int index, int value)
{
	for (int i = 0; i < INDEX_COUNT; i++)
	{
		to_fill[i] = current_indices[i];
	}
	to_fill[index] = value;
}

vector<int*>* process_successors6632(int* current_indices, MemoryBank& memory_bank, vector<vector<int>>& lookup, int****** table, int current_val)
{
	vector<int*>* retval = new vector<int*>();
	int new_pos;
	int index;
	for (int i = 0; i < INDEX_COUNT; i++)
	{
		for (int action : lookup[current_indices[i]])
		{
			new_pos = current_indices[i] + action;
			index = find_index6632(current_indices, new_pos);
			if (index == -1)
			{
				int* temp = memory_bank.temp_slot;
				fill_successor6632(current_indices, temp, i, new_pos);
				int* value = &table[temp[0]][temp[1]][temp[2]][temp[3]][temp[4]][temp[5]];
				if (*value == -1)
				{

					int* temp = memory_bank.free_slots.top();
					fill_successor6632(memory_bank.temp_slot, temp, i, new_pos);
					memory_bank.free_slots.pop();
					memory_bank.remaining.push(temp);
					*value = current_val + 1;
				}


			}
		}
	}
	return retval;
}

void save_partition_to_file6632(int****** table)
{
	ofstream file;
	file.open("sixsixthreepartitiontwo.txt");
	for (int i1 = 0; i1 < 16; i1++)
	{
		for (int i2 = 0; i2 < 16; i2++)
		{
			for (int i3 = 0; i3 < 16; i3++)
			{
				for (int i4 = 0; i4 < 16; i4++)
				{
					for (int i5 = 0; i5 < 16; i5++)
					{
						for (int i6 = 0; i6 < 16; i6++)
						{
							file << table[i1][i2][i3][i4][i5][i6] << " ";
						}
					}
				}

			}
		}
	}
	file.close();
}




void initialize_table_partition6632()
{
	int****** table = initialize_table6632();
	int counter = 1;
	int current_value;
	MemoryBank memory_bank(INDEX_COUNT, SLOT_COUNT);
	int* current_indices = memory_bank.free_slots.top();
	memory_bank.free_slots.pop();
	current_indices[0] = 3;
	current_indices[1] = 6;
	current_indices[2] = 7;
	current_indices[3] = 10;
	current_indices[4] = 11;
	current_indices[5] = 15;
	table[1][2][4][5][8][9] = 0;
	memory_bank.remaining.push(current_indices);
	vector<vector<int>> lookup = initialize_index_lookup();
	int special_val = 0;
	while (!memory_bank.remaining.empty())
	{
		current_indices = memory_bank.remaining.front();
		memory_bank.remaining.pop();
		current_value = table[current_indices[0]][current_indices[1]][current_indices[2]][current_indices[3]][current_indices[4]][current_indices[5]];
		process_successors6632(current_indices, memory_bank, lookup, table, current_value);
		memory_bank.free_slots.push(current_indices);
		if (current_value > special_val)
		{
			special_val = current_value;
			cout << "Counter: " << counter << endl;
			cout << "Depth: " << special_val << endl;
		}
	}
	cout << counter << endl;
	save_partition_to_file6632(table);
	clear_table6632(table);

}




*/