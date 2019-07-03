#include "Heuristic.h"
#include <ctime>

using namespace std;

int positions_to_index(int* positions)
{
	int coef[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	int total = 0;
	total += 2730 * coef[positions[0]];
	for (int i = positions[0] + 1; i < 16; i++)
	{
		coef[i]--;
	}
	total += 182 * coef[positions[1]];
	for (int i = positions[1] + 1; i < 16; i++)
	{
		coef[i]--;
	}
	total += 13 * coef[positions[2]];
	for (int i = positions[2] + 1; i < 16; i++)
	{
		coef[i]--;
	}
	total += 1 * coef[positions[3]];
	return total;
}

void index_to_positions(int index, int* positions)
{
	int coef[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	int temp = index / 2730;
	index -= 2730 * temp;
	for (int i = 0; i < 16; i++)
	{
		if (coef[i] == temp)
		{
			positions[0] = i;
			coef[i] = -1;
			for (int j = i + 1; j < 16; j++)
			{
				coef[j]--;
			}
			break;
		}
	}
	temp = index / 182;
	index -= 182 * temp;
	for (int i = 0; i < 16; i++)
	{
		if (coef[i] == temp)
		{
			positions[1] = i;
			coef[i] = -1;
			for (int j = i + 1; j < 16; j++)
			{
				coef[j]--;
			}
			break;
		}
		
	}
	temp = index / 13;
	index -= 13 * temp;
	for (int i = 0; i < 16; i++)
	{
		if (coef[i] == temp)
		{
			positions[2] = i;
			coef[i] = -1;
			for (int j = i + 1; j < 16; j++)
			{
				coef[j]--;
			}
			break;
		}
		
	}
	temp = index / 1;
	index -= 1 * temp;
	for (int i = 0; i < 16; i++)
	{
		if (coef[i] == temp)
		{
			positions[3] = i;
			coef[i] = -1;
			break;
		}
	}

}


void positions_to_table(int* table, int* positions)
{
	for (int i = 0; i < 16; i++)
	{
		table[i] = -1;
	}
	table[positions[0]] = 12;
	table[positions[1]] = 13;
	table[positions[2]] = 14;
	table[positions[3]] = 0;
}

void table_to_positions(int* table, int* positions)
{
	for (int i = 0; i < 16; i++)
	{
		if (table[i] == 12)
		{
			positions[0] = i;
		}
		if (table[i] == 13)
		{
			positions[1] = i;
		}
		if (table[i] == 14)
		{
			positions[2] = i;
		}
		if (table[i] == 0)
		{
			positions[3] = i;
		}
	}
}

int check_if_real_change_partition_three(int* table_action)
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

//ovo regulise kockice 12 13 14 0
void initialize_partition_three()
{
	//treba nam 43680 elemenata

	int* temp = new int[43680];
	int counter = 1;
	for (int i = 0; i < 43680; i++)
	{
		temp[i] = -1;
	}
	queue<int> structure;
	GameLogic game_logic;
	MemoryBank mem_bank;
	game_logic.set_memory_bank(&mem_bank);
	int my_table[16] = {-1, -1, -1, -1,
					 -1, -1, -1, -1,
					 -1, -1, -1, -1,
					 -1, -1, -1, -1 };
	int* current_indices = new int[4];
	current_indices[0] = 12;
	current_indices[1] = 13;
	current_indices[2] = 14;
	current_indices[3] = 0;
	int index = positions_to_index(current_indices);
	temp[index] = 0;
	structure.push(index);
	double time_elapsed = 0.0;
	clock_t begin = clock();
	while (!structure.empty())
	{
		
		int current = structure.front();
		structure.pop();
		index_to_positions(current, current_indices);
		positions_to_table(my_table, current_indices);


		int** successors = game_logic.get_successors(my_table, Action::NONE);

		

		for (int i = 0; i < 4; i++)
		{
			if (successors[i] == nullptr)
			{
				break;
			}
			table_to_positions(successors[i], current_indices);
			int new_index = positions_to_index(current_indices);
			
			if (temp[new_index] == -1)
			{
				clock_t begin2 = clock();
				structure.push(new_index);
				temp[new_index] = temp[current] + check_if_real_change_partition_three(successors[i]);
				
				counter++;
				
				clock_t end2 = clock();
				time_elapsed += double(end2 - begin2);
				
				
			}
			game_logic.get_mem_bank()->free_slots.push(successors[i]);
			

		}

		


		
		if (counter >= 20000) 
		{
			break;
		}


		
		delete[] successors;
		

	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Elapsed time: " << elapsed_secs << " secs" << endl;
	cout << "Partial time: " << time_elapsed / CLOCKS_PER_SEC;
	ofstream file;
	file.open("sixsixsixpartitionthree.txt");
	for (int i = 0; i < 43680; i++)
	{
		file << temp[i] << " ";
	}


	
	delete[] temp;
	delete[] current_indices;
}

 