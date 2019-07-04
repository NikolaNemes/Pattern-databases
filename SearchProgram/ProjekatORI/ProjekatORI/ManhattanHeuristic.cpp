#include <algorithm>
#include "Heuristic.h"




int** manhattan_table = generate_manhattan_table();


void set_to_minus_one(int* table_partition)
{
	for (int i = 0; i < 16; i++)
	{
		table_partition[i] = -1;
	}
}



int** generate_manhattan_table()
{
	int** retval = new int*[16];
	GameLogic game_logic;
	for (int i = 1; i < 16; i++) //ne radimo menhetn za nulu
	{
		retval[i] = new int[16];
		set_to_minus_one(retval[i]);
		retval[i][i] = 0;
		int counter = 1;
		while (counter < 16)
		{
			for (int j = 0; j < 16; j++)
			{
				if (retval[i][j] != -1)
				{
					int new_pos;
					int* actions = game_logic.get_possible_actions_by_index(j);
					for (int actionIterator = 0; actionIterator < 4; actionIterator++)
					{
						if (actions[actionIterator] == Action::UP)
						{
							new_pos = j - 4;
						}
						else if (actions[actionIterator] == Action::DOWN)
						{
							new_pos = j + 4;
						}
						else if (actions[actionIterator] == Action::RIGHT)
						{
							new_pos = j + 1;
						}
						else if (actions[actionIterator] == Action::LEFT)
						{
							new_pos = j - 1;
						}
						else
						{
							new_pos = j;
						}
						if (retval[i][new_pos] == -1)
						{
							retval[i][new_pos] = retval[i][j] + 1;
							counter++;
						}
					}
				}
			}
		}

	}
	return retval;
}


int manhattan_heuristic(int* table)
{
	int total = 0;
	for (int i = 0; i < 16; i++)
	{
		if (table[i] != 0)
		{
			total += manhattan_table[table[i]][i];
		}
	}
	return total;
}

