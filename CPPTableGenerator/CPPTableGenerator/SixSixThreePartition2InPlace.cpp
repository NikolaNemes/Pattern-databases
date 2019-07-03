//3, 6, 7, 10, 11, 15
#include "SixSixThreePartition.h"
#include <cmath>

using namespace std;


namespace Partition2
{
	int****** initialize_tableInPlace(int default)
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
								retval[i1][i2][i3][i4][i5][i6] = default;
							}
						}
					}
				}
			}
		}
		return retval;
	}

	void clear_tableInPlace(int****** table)
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

	void save_to_file(int****** table)
	{
		FILE* file;
		errno_t error_code = fopen_s(&file, "partition2.bin", "wb");

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
							fwrite(table[i1][i2][i3][i4][i5], 4, 16, file);
						}
					}
				}
			}
		}
		fclose(file);

	}


	void read_file(int****** table)
	{
		FILE* file;
		errno_t error_code = fopen_s(&file, "partition2.bin", "rb");

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
							fread(table[i1][i2][i3][i4][i5], 4, 16, file);
						}
					}
				}
			}
		}
		fclose(file);
	}



	void indices_to_board(int* board, int index3, int index6, int index7, int index10, int index11, int index15)
	{
		for (int i = 0; i < 16; i++)
		{
			board[i] = -1;
		}
		board[index3] = 3;
		board[index6] = 6;
		board[index7] = 7;
		board[index10] = 10;
		board[index11] = 11;
		board[index15] = 15;
	}
	//3, 6, 7, 10, 11, 15
	void table_to_indices(int& index3, int& index6, int& index7, int& index10, int& index11, int& index15, int* board)
	{
		for (int i = 0; i < 16; i++)
		{
			if (board[i] == 3)
			{
				index3 = i;
			}
			else if (board[i] == 6)
			{
				index6 = i;
			}
			else if (board[i] == 7)
			{
				index7 = i;
			}
			else if (board[i] == 10)
			{
				index10 = i;
			}
			else if (board[i] == 11)
			{
				index11 = i;
			}
			else if (board[i] == 15)
			{
				index15 = i;
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

	void drawBrd(int* brd) {
		int r; std::cout << "\n\n";
		for (int y = 0; y < 4; y++) {
			std::cout << "+----+----+----+----+\n";
			for (int x = 0; x < 4; x++) {
				r = brd[x + y * 4];
				std::cout << "| ";
				if (r < 10 && r != -1) std::cout << " ";
				if (!r) std::cout << "  ";
				else std::cout << r << " ";
			}
			std::cout << "|\n";
		}
		std::cout << "+----+----+----+----+\n";
	}

	void create_partition_inplace()
	{
		int******  table = initialize_tableInPlace(120);
		int******  delayed_zeroes = initialize_tableInPlace(0);
		int******  zero_pos = initialize_tableInPlace(0);
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

		//3, 6, 7, 10, 11, 15
		int index3;
		int index6;
		int index7;
		int index10;
		int index11;
		int index15;
		int zeroIndex;
		int tempIndex;
		int switchIndex;
		int actionIndex;
		int board[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		int prime_positions[16];
		int counter = 1;
		prime_positions[0] = 0;

		table_to_indices(index3, index6, index7, index10, index11, index15, board);
		zeroIndex = get_zero_index(board);
		table[index3][index6][index7][index10][index11][index15] = 0;

		zero_pos[index3][index6][index7][index10][index11][index15] |= 1UL << zeroIndex;

		double time_elapser = 0;

		while (true)
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
								for (int i6 = 0; i6 < 16; i6++)
								{
									if (table[i1][i2][i3][i4][i5][i6] <= depth)
									{
										int temp = zero_pos[i1][i2][i3][i4][i5][i6];
										for (int zeroIndexIterator = 0; zeroIndexIterator < 16; zeroIndexIterator++)
										{
											if ((temp & 1) != 1)
											{
												temp >>= 1; continue;
											}

											zeroIndex = zeroIndexIterator;
											temp >>= 1;

											indices_to_board(board, i1, i2, i3, i4, i5, i6);
											board[zeroIndex] = 0;

											//drawBrd(board);

											zeroIndex = get_zero_index(board);
											prime_positions[0] = 0; //moras resetovati ovo cudo pred svako koriscenje

											get_prime_positions(board, prime_positions, zeroIndex, lookup);

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
													table_to_indices(index3, index6, index7, index10, index11, index15, board);

													if (table[index3][index6][index7][index10][index11][index15] == 120)
													{
														table[index3][index6][index7][index10][index11][index15] = depth + 1;;
														delayed_zeroes[index3][index6][index7][index10][index11][index15] |= 1UL << zeroIndex;
														counter++;
													}
													else
													{
														delayed_zeroes[index3][index6][index7][index10][index11][index15] |= 1UL << zeroIndex;
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
						}
					}
				}
			}
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
									zero_pos[i1][i2][i3][i4][i5][i6] |= delayed_zeroes[i1][i2][i3][i4][i5][i6];
								}
							}
						}
					}
				}
			}
			depth++;
			std::cout << "Dubina: " << depth << endl;
			std::cout << "Counter: " << counter << endl;
			if (counter == 5765760)
			{
				break;
			}
		}

		save_to_file(table);

		//testiranje snimanja i citanja fajlova
		read_file(delayed_zeroes);
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
								if (table[i1][i2][i3][i4][i5][i6] != delayed_zeroes[i1][i2][i3][i4][i5][i6])
								{
									cout << "Oh nou" << endl;
								}
							}
						}
					}
				}
			}
		}
		cout << "Istestirao fajl" << endl;


		clear_tableInPlace(table);
		clear_tableInPlace(zero_pos);
		clear_tableInPlace(delayed_zeroes);
	}
}

