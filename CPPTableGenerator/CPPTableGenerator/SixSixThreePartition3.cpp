//Particija za plocice: 12, 13, 14 0 + AKCIJA(1)
//ukupan broj clanova: 16*15*14=3360
#include "SixSixThreePartition.h"

#define INDEX_COUNT 4
#define CHUNK_SIZE 5
#define SLOT_COUNT 40000000
#define ACTION_OFFSET 4

using namespace std;

/*

int**** initialize_table6633()
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

void clear_table6633(int**** table)
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

int find_index6633(char* current_indices, char value)
{
	for (int i = 0; i < INDEX_COUNT - 1; i++)
	{
		if (current_indices[i] == value)
		{
			return i;
		}
	}
	return -1;
}


void fill_successor6633(char* current_indices, char* to_fill, int index)
{
	for (int i = 0; i < INDEX_COUNT - 1; i++)
	{
		to_fill[i] = current_indices[i];
	}
	to_fill[INDEX_COUNT - 1] = current_indices[index];
	to_fill[index] = current_indices[INDEX_COUNT - 1];
}

void fill_empty_move663(char* current_indices, char* to_fill, char new_pos)
{
	for (int i = 0; i < INDEX_COUNT - 1; i++)
	{
		to_fill[i] = current_indices[i];
	}
	to_fill[INDEX_COUNT - 1] = new_pos;
}

void coppy_completely663(char* current_indices, char* to_fill)
{
	for (int i = 0; i < INDEX_COUNT; i++)
	{
		to_fill[i] = current_indices[i];
	}
}

std::vector<vector<int>> initialize_index_lookup() {
	std::vector<vector<int>> a;
	return a;
}

char*** initialize_index_lookup6633()
{
	//vector<vector<int>> retval(16);
	char*** retval = new char**[9];
	int action_indexes[] = { 0, 3, 4, 5, 8 };

	for (int i = 0; i < 5; i++)
	{
		retval[action_indexes[i]] = new char*[16];
		for (int j = 0; j < 16; j++)
		{
			retval[action_indexes[i]][j] = new char[4];
		}
	}
	for (int i = 0; i < 16; i++)
	{
		vector<char> action_none;
		vector<char> action_left;
		vector<char> action_right;
		vector<char> action_up;
		vector<char> action_down;

		int new_pos = i - 4;
		if (new_pos >= 0)
		{
			action_none.push_back(-4);
			action_up.push_back(-4);
			action_left.push_back(-4);
			action_right.push_back(-4);
		}
		new_pos = i + 4;
		if (new_pos <= 15)
		{
			action_none.push_back(4);
			action_down.push_back(4);
			action_left.push_back(4);
			action_right.push_back(4);
		}
		new_pos = i - 1;
		if (new_pos >= 0 && new_pos % 4 != 3)
		{
			action_none.push_back(-1);
			action_left.push_back(-1);
			action_up.push_back(-1);
			action_down.push_back(-1);
		}
		new_pos = i + 1;
		if (new_pos <= 15 && new_pos % 4 != 0)
		{
			action_none.push_back(1);
			action_right.push_back(1);
			action_up.push_back(1);
			action_down.push_back(1);
		}
		char* none_actions_pt = retval[4][i];
		char* right_actions_pt = retval[5][i];
		char* left_actions_pt = retval[3][i];
		char* up_actions_pt = retval[0][i];
		char* down_actions_pt = retval[8][i];

		none_actions_pt[0] = action_none.size();
		for (int j = 0; j < action_none.size(); j++)
		{
			none_actions_pt[j + 1] = action_none[j];
		}

		right_actions_pt[0] = action_right.size();
		for (int j = 0; j < action_right.size(); j++)
		{
			right_actions_pt[j + 1] = action_right[j];
		}

		left_actions_pt[0] = action_left.size();
		for (int j = 0; j < action_left.size(); j++)
		{
			left_actions_pt[j + 1] = action_left[j];
		}

		up_actions_pt[0] = action_up.size();
		for (int j = 0; j < action_up.size(); j++)
		{
			up_actions_pt[j + 1] = action_up[j];
		}

		down_actions_pt[0] = action_down.size();
		for (int j = 0; j < action_down.size(); j++)
		{
			down_actions_pt[j + 1] = action_down[j];
		}
	}
	return retval;
}


void process_successors6633(char* current_indices, MemoryBank& memory_bank, char*** lookup, int**** table, int current_val, double& time_elapser, int& counter2)
{
	int new_pos;
	int index;
	//int* action_pt = lookup[current_indices[INDEX_COUNT] + ACTION_OFFSET][current_indices[INDEX_COUNT - 1]];
	char* action_pt = lookup[current_indices[INDEX_COUNT] + ACTION_OFFSET][current_indices[INDEX_COUNT - 1]];
	for (int i = 0; i < action_pt[0]; i++)
	{
		new_pos = current_indices[INDEX_COUNT - 1] + action_pt[i + 1];
		index = find_index6633(current_indices, new_pos);
		if (index == -1)
		{
			char* temp = memory_bank.temp_slot;
			fill_empty_move663(current_indices, temp, new_pos);
			int* value = &table[temp[0]][temp[1]][temp[2]][temp[3]];

			if (*value == -1)
			{
				char* temp = memory_bank.first_free;
				memory_bank.first_free += CHUNK_SIZE;
				if (memory_bank.first_free == memory_bank.turnover)
				{
					cout << "Full circle" << endl;
					memory_bank.first_free = &memory_bank.memory[0];
				}
				counter2++;
				coppy_completely663(memory_bank.temp_slot, temp);
				//postavi uradjenu akciju
				temp[INDEX_COUNT] = action_pt[i + 1];
				*value = current_val;
			}
		}
		else
		{
			char* temp = memory_bank.temp_slot;
			fill_successor6633(current_indices, temp, index);
			int* value = &table[temp[0]][temp[1]][temp[2]][temp[3]];
			if (*value == -1)
			{
				char* temp = memory_bank.first_free;
				memory_bank.first_free+= CHUNK_SIZE;
				if (memory_bank.first_free == memory_bank.turnover)
				{
					cout << "Full circle" << endl;
					memory_bank.first_free = &memory_bank.memory[0];
				}
				counter2++;
				coppy_completely663(memory_bank.temp_slot, temp);
				temp[INDEX_COUNT] = action_pt[i + 1];
				*value = current_val + 1;
			}
		}
	}
}

void save_partition_to_file6633(int**** table)
{
	ofstream file;
	file.open("../Output/sixsixthreepartitionthree.txt");
	for (int i1 = 0; i1 < 16; i1++)
	{
		for (int i2 = 0; i2 < 16; i2++)
		{
			for (int i3 = 0; i3 < 16; i3++)
			{
				for (int i4 = 0; i4 < 16; i4++)
				{
					file << table[i1][i2][i3][i4] << " ";
				}
			}
		}
	}
	file.close();
}


void initialize_table_partition6633()
{
	int imax = std::numeric_limits<int>::max();
	int**** table = initialize_table6633();
	int counter = 1;
	int counter_all = 0;
	int current_value;
	MemoryBank memory_bank(CHUNK_SIZE, SLOT_COUNT);


	char* current_indices = memory_bank.first_free;
	memory_bank.first_free += CHUNK_SIZE;
	if (memory_bank.first_free == memory_bank.turnover)
	{
		memory_bank.first_free = &memory_bank.memory[0];
	}


	counter_all++;
	current_indices[0] = 12;
	current_indices[1] = 13;
	current_indices[2] = 14;
	current_indices[3] = 0;
	current_indices[4] = 0; //none action
	table[12][13][14][0] = 0;
	char*** lookup = initialize_index_lookup6633();
	double time_elapser = 0;
	clock_t begin = clock();
	while (memory_bank.first_free != memory_bank.first_taken)
	{


		current_indices = memory_bank.first_taken;
		memory_bank.first_taken += CHUNK_SIZE;
		if (memory_bank.first_taken == memory_bank.turnover)
		{
			memory_bank.first_taken = &memory_bank.memory[0];
		}
		//ali ne zelis da ga odma popujes, ovo je bitno, on leti tek na kraju ove metode, da ga ne bi neko drugi pregazio

		current_value = table[current_indices[0]][current_indices[1]][current_indices[2]][current_indices[3]];
		//clock_t begin2 = clock();
		process_successors6633(current_indices, memory_bank, lookup, table, current_value, time_elapser, counter_all);
		//clock_t end2 = clock();
		//time_elapser += double(end2 - begin2);
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Elapsed time: " << elapsed_secs << " secs" << endl;
	cout << "Summed time" << time_elapser / CLOCKS_PER_SEC << endl;

	//provera
	counter = 0;
	for (int i1 = 0; i1 < 16; i1++)
	{
		for (int i2 = 0; i2 < 16; i2++)
		{
			for (int i3 = 0; i3 < 16; i3++)
			{
				for (int i4 = 0; i4 < 16; i4++)
				{
					if (table[i1][i2][i3][i4] != -1)
					{
						counter++;
						break;
					}
				}
			}
		}
	}

	cout << "Counter distinct: " << counter << "/3360" << endl;
	cout << "Chunk size: " << CHUNK_SIZE << endl;
	cout << "Counter all: " << counter_all << endl;
	save_partition_to_file6633(table);
	clear_table6633(table);
}

*/