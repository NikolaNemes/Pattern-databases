#include "Heuristic.h"
#include <chrono>
#include <thread>

//ona ce da hendla 1 2 4 5 8 9 0

int positions_to_index_one(int* positions)
{
	int coef[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	int total = 0;
	total += 3603600 * coef[positions[0]];
	for (int i = positions[0] + 1; i < 16; i++)
	{
		coef[i]--;
	}
	total += 240240 * coef[positions[1]];
	for (int i = positions[1] + 1; i < 16; i++)
	{
		coef[i]--;
	}
	total += 17160 * coef[positions[2]];
	for (int i = positions[2] + 1; i < 16; i++)
	{
		coef[i]--;
	}
	total += 1320 * coef[positions[3]];
	for (int i = positions[3] + 1; i < 16; i++)
	{
		coef[i]--;
	}
	total += 110 * coef[positions[4]];
	for (int i = positions[4] + 1; i < 16; i++)
	{
		coef[i]--;
	}
	total += 10 * coef[positions[5]];
	for (int i = positions[5] + 1; i < 16; i++)
	{
		coef[i]--;
	}
	total += 1 * coef[positions[6]];
	return total;
}

void helper_method(int* coef, int& temp, int& index, int division_num, int* positions, int positions_index)
{
	temp = index / division_num;
	index -= division_num * temp;
	for (int i = 0; i < 16; i++)
	{
		if (coef[i] == temp)
		{
			positions[positions_index] = i;
			coef[i] = -1;
			for (int j = i + 1; j < 16; j++)
			{
				coef[j]--;
			}
			break;
		}
	}
}


void index_to_position_one(int index, int* positions)
{
	int coef[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	int temp = 0;
	helper_method(coef, temp, index, 3603600, positions, 0);
	helper_method(coef, temp, index, 240240, positions, 1);
	helper_method(coef, temp, index, 17160, positions, 2);
	helper_method(coef, temp, index, 1320, positions, 3);
	helper_method(coef, temp, index, 110, positions, 4);
	helper_method(coef, temp, index, 10, positions, 5);
	helper_method(coef, temp, index, 1, positions, 6);
	temp = index / 1320;
}

//ona ce da hendla 1 2 4 5 8 9 0
void positions_to_table_one(int* table, int* positions)
{
	for (int i = 0; i < 16; i++)
	{
		table[i] = -1;
	}
	table[positions[0]] = 1;
	table[positions[1]] = 2;
	table[positions[2]] = 4;
	table[positions[3]] = 5;
	table[positions[4]] = 8;
	table[positions[5]] = 9;
	table[positions[6]] = 0;
}

void table_to_positions_one(int * table, int* positions)
{
	for (int i = 0; i < 16; i++)
	{
		if (table[i] == 1)
		{
			positions[0] = i;
		}
		if (table[i] == 2)
		{
			positions[1] = i;
		}
		if (table[i] == 4)
		{
			positions[2] = i;
		}
		if (table[i] == 5)
		{
			positions[3] = i;
		}
		if (table[i] == 8)
		{
			positions[4] = i;
		}
		if (table[i] == 9)
		{
			positions[5] = i;
		}
		if (table[i] == 0)
		{
			positions[6] = i;
		}
	}
}

int check_if_real_change_one(int* table_action)
{
	int zero_index = 0;
	for (int i = 0; i < 16; i++)
	{
		if (table_action[i] == 0)
		{
			zero_index = i;
			break;
		}
	}
	if ((Action)table_action[16] == Action::UP)
	{
		if (table_action[zero_index + 4] != -1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if ((Action)table_action[16] == Action::DOWN)
	{
		if (table_action[zero_index - 4] != -1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if ((Action)table_action[16] == Action::LEFT)
	{
		if (table_action[zero_index + 1] != -1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if ((Action)table_action[16] == Action::RIGHT)
	{
		if (table_action[zero_index - 1] != -1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	return 0;
}

void initialize_partition_one()
{
	//treba nam 57 657 600 elemenata
	int* temp = new int[57657600];
	int* condensed = new int[5765760];
	int counter = 1;
	int special_counter = 0;
	int special_display = 0;
	for (int i = 0; i < 57657600; i++)
	{
		temp[i] = -1;
	}
	queue<int> structure;
	GameLogic game_logic;
	MemoryBank mem_bank;
	game_logic.set_memory_bank(&mem_bank);
	int my_table[16] = { -1, -1, -1, -1,
		-1, -1, -1, -1,
		-1, -1, -1, -1,
		-1, -1, -1, -1 };
	int* current_indices = new int[7];
	////ona ce da hendla 1 2 4 5 8 9 0
	current_indices[0] = 1;
	current_indices[1] = 2;
	current_indices[2] = 4;
	current_indices[3] = 5;
	current_indices[4] = 8;
	current_indices[5] = 9;
	current_indices[6] = 0;
	int index = positions_to_index_one(current_indices);
	temp[index] = 0;
	structure.push(index);
	while (!structure.empty())
	{
		int current = structure.front();
		structure.pop();
		index_to_position_one(current, current_indices);
		positions_to_table_one(my_table, current_indices);
		int** successors = game_logic.get_successors(my_table, Action::NONE);
		
		for (int i = 0; i < 4; i++)
		{
			if (successors[i] == nullptr)
			{
				break;
			}
			table_to_positions_one(successors[i], current_indices);
			int new_index = positions_to_index_one(current_indices);
			if (temp[new_index] == -1)
			{

				structure.push(new_index);
				temp[new_index] = temp[current] + check_if_real_change_one(successors[i]);
				counter++;
				special_counter++;
				
			}
			game_logic.get_mem_bank()->free_slots.push(successors[i]);

		}
		delete[] successors;
		if (special_counter >= 1000000) {
			cout << ++special_display << endl;
			special_counter = 0;
		}
	}

	ofstream file;
	file.open("sixsixsixpartitionone.txt");
	for (int i = 0; i < 57657600; i++)
	{
		file << temp[i] << " ";
	}



	delete[] temp;
	delete[] current_indices;
}

