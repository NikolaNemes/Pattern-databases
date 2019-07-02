#include <iostream>
#include "SixSixThreePartition.h"
using namespace std;

namespace Partition3
{

	int*** initialize_table6633InPlace(int default)
	{
		int*** retval = new int**[16];
		for (int i1 = 0; i1 < 16; i1++)
		{
			retval[i1] = new int*[16];
			for (int i2 = 0; i2 < 16; i2++) {
				retval[i1][i2] = new int[16];
				for (int i3 = 0; i3 < 16; i3++)
				{
					retval[i1][i2][i3] = default;

				}
			}
		}
		return retval;
	}

	void clear_table6633InPlace(int*** table)
	{
		for (int i1 = 0; i1 < 16; i1++)
		{
			for (int i2 = 0; i2 < 16; i2++)
			{
				delete[] table[i1][i2];
			}
			delete[] table[i1];
		}
		delete[] table;
	}

	void indices_to_board(int* board, int index12, int index13, int index14, int*** zero_pos)
	{
		for (int i = 0; i < 16; i++)
		{
			board[i] = -1;
		}
		board[index12] = 12;
		board[index13] = 13;
		board[index14] = 14;
		board[zero_pos[index12][index13][index14]] = 0;

	}

	void table_to_indices(int& index12, int& index13, int& index14, int* board)
	{
		for (int i = 0; i < 16; i++)
		{
			if (board[i] == 12)
			{
				index12 = i;
			}
			else if (board[i] == 13)
			{
				index13 = i;
			}
			else if (board[i] == 14)
			{
				index14 = i;
			}
		}
	}

	int get_zero_index(int* board)
	{
		for (int i = 0; i < 16; i++)
		{
			if (board[i] == 0)
			{
				return i;
			}
		}
		return -1;
	}

	void get_prime_positions(int* board, int* positions, int starting_pos, int* lookup)
	{
		int action_index = starting_pos * 5;
		int next_pos;
		bool add_self = false;
		while (true)
		{
			if (lookup[action_index] == 0) break;
			next_pos = starting_pos + lookup[action_index];
			if (board[next_pos] == -1)
			{
				board[next_pos] = 0;
				get_prime_positions(board, positions, next_pos, lookup);
			}
			else if (board[next_pos] > 0)
			{
				add_self = true;
			}
			action_index++;
		}
		if (add_self)
		{
			positions[++positions[0]] = starting_pos;
		}

	}


	void create_partition_inplace()
	{
		int***  table = initialize_table6633InPlace(120);
		int***  zero_pos = initialize_table6633InPlace(-1);
		int depth = 0;
		int lookup[80] =
		{
			1, 4, 0, 0, 0,    //pozicija 0, moze desno i dole
			1, 4, -1, 0, 0,   //pozicija 1 moze desno, dole, i levo
			1, 4, -1, 0, 0,   //pozicija 2 moze desno, dole i levo
			-1, 4, 0, 0, 0,   //pozicija 3, moze levo i dole
			1, -4, 4, 0, 0,   //pozicija 4, moze gore, desno i dole
			1, -1, 4, -4, 0,  //pozicija 5, moze u svim smerovima
			1, -1, 4, -4, 0,  //pozicija 6, moze u svim smerovima
			-4, -1, 4, 0, 0,  //pozicija 7, moze gore,levo i dole
			-4, 1, 4, 0, 0,   //pozicija 8, moze gore, desno i dole
			1, -1, 4, -4, 0,  //pozicija 9, moze u svim smerovima
			1, -1, 4, -4, 0,  //pozicija 10, moze u svim smerovima
			-4, -1, 4, 0, 0,  //pozicija 11, moze gore, levo i dole
			-4, 1, 0, 0, 0,   //pozicija 12, moze gore i desno
			-1, -4, 1, 0, 0,  //pozicija 13, moze levo, gore i desno
			-1, -4, 1, 0, 0,  //pozicija 14, moze levo, gore i desno
			-1, -4, 0, 0,  0  //pozicija 15, moze levo i gore
		};

		int index12;
		int index13;
		int index14;
		int zeroIndex;
		int tempIndex;
		int switchIndex;
		int actionIndex;
		int board[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		int prime_positions[16];
		int counter = 1;
		int value;
		prime_positions[0] = 0;

		table_to_indices(index12, index13, index14, board);
		zeroIndex = get_zero_index(board);
		table[index12][index13][index14] = 0;
		zero_pos[index12][index13][index14] = zeroIndex;
		clock_t begin = clock();

		double time_elapser = 0;

		while (true)
		{
			for (int i1 = 0; i1 < 16; i1++)
			{
				for (int i2 = 0; i2 < 16; i2++)
				{
					for (int i3 = 0; i3 < 16; i3++)
					{
						if (table[i1][i2][i3] == depth) //ovo svaba kaze da bi trebalo biti <= al to cemo jos testirati
						{
							index12 = i1;
							index13 = i2;
							index14 = i3;
							value = table[i1][i2][i3];
							indices_to_board(board, index12, index13, index14, zero_pos);
							zeroIndex = get_zero_index(board);
							prime_positions[0] = 0; //moras resetovati ovo cudo pred svako koriscenje
							clock_t begin2 = clock();
							get_prime_positions(board, prime_positions, zeroIndex, lookup);
							clock_t end2 = clock();
							time_elapser += double(end2 - begin2);
							for (int i = 0; i < prime_positions[0]; i++)
							{
								zeroIndex = prime_positions[i + 1];
								actionIndex = zeroIndex * 5;
								while (true)
								{
									if (lookup[actionIndex] == 0) break;
									switchIndex = zeroIndex + lookup[actionIndex];
									if (board[switchIndex] <= 0)
									{
										actionIndex++;
										continue;
									}

									board[zeroIndex] = board[switchIndex];
									board[switchIndex] = 0;
									tempIndex = zeroIndex; //cuvamo stari indeks
									zeroIndex = switchIndex;
									table_to_indices(index12, index13, index14, board);
									if (table[index12][index13][index14] == 120)
									{

										table[index12][index13][index14] = value + 1;
										zero_pos[index12][index13][index14] = zeroIndex;
										counter++;
									}
									board[zeroIndex] = board[tempIndex];
									zeroIndex = tempIndex;
									board[zeroIndex] = 0;
									actionIndex++;
								}
							}

						}
					}
				}
			}
			if (counter == 3360)
			{
				break;
			}
			depth++;
			cout << "Dubina: " << depth << endl;


			//cout << depth << endl;
		}
		clock_t end = clock();
		double elapsed = double(end - begin) / CLOCKS_PER_SEC;
		cout << "Time: " << elapsed << endl;
		cout << "Partial time: " << time_elapser / CLOCKS_PER_SEC << endl;
		clear_table6633InPlace(table);
		clear_table6633InPlace(zero_pos);
	}
}
