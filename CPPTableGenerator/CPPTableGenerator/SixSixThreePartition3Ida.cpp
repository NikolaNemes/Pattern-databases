//Particija za plocice: 12, 13, 14 0 + AKCIJA(1)
//ukupan broj clanova: 16*15*14=3360
#include "SixSixThreePartition.h"


using namespace std;

int*** initialize_index_lookup6633ida()
{
	//vector<vector<int>> retval(16);
	int*** retval = new int**[9];
	int action_indexes[] = { 0, 3, 4, 5, 8 };

	for (int i = 0; i < 5; i++)
	{
		retval[action_indexes[i]] = new int*[16];
		for (int j = 0; j < 16; j++)
		{
			retval[action_indexes[i]][j] = new int[4];
		}
	}
	for (int i = 0; i < 16; i++)
	{
		vector<int> action_none;
		vector<int> action_left;
		vector<int> action_right;
		vector<int> action_up;
		vector<int> action_down;

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
		int* none_actions_pt = retval[4][i];
		int* right_actions_pt = retval[5][i];
		int* left_actions_pt = retval[3][i];
		int* up_actions_pt = retval[0][i];
		int* down_actions_pt = retval[8][i];

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


int**** initialize_table6633ida(int default)
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
					retval[i1][i2][i3][i4] = default;
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



int find_index6633ida(int* current_indices, int value)
{
	for (int i = 0; i < 3; i++)
	{
		if (current_indices[i] == value)
		{
			return i;
		}
	}
	return -1;
}

void copy_prunes_6633ida(int* current, int* next, MemoryBank& memory_bank)
{
	for (int i = 0; i < 3; i++)
	{
		next[i] = current[i];
	}
}

void copy_prunes_and_zero(int* current, int* next)
{
	for (int i = 0; i < 4; i++)
	{
		next[i] = current[i];
	}
}

void copy_everything(int* current, int* next, MemoryBank& memory_bank)
{
	for (int i = 0; i < 6; i++)
	{
		next[i] = current[i];
	}
}

void dfs(int**** table, MemoryBank& memory_bank, int depth, int*** lookup, int**** versions, int& counter)
{
	int* current_board = memory_bank.get_empty();
	int* action_pt;
	int* next_board;
	int* child_value;
	int* child_version;
	int new_pos;
	int index;
	current_board[0] = 12;
	current_board[1] = 13;
	current_board[2] = 14;
	current_board[3] = 0; //position for blank
	current_board[4] = 0; //none_action
	current_board[5] = 0; //depth
	memory_bank.push();
	current_board = new int[6];
	while (!memory_bank.empty())
	{
		copy_everything(memory_bank.get_top(), current_board, memory_bank);
		memory_bank.pop();
		action_pt = lookup[current_board[4] + 4][current_board[3]];
		for (int i = 0; i < action_pt[0]; i++)
		{
			new_pos = current_board[3] + action_pt[i + 1];
			index = find_index6633ida(current_board, new_pos);
			if (index == -1)
			{
				next_board = memory_bank.get_empty();
				copy_prunes_6633ida(current_board, next_board, memory_bank);
				next_board[3] = new_pos;
				child_version = &versions[next_board[0]][next_board[1]][next_board[2]][next_board[3]];
				if (*child_version == depth) continue;
				*child_version = depth;
				next_board[4] = action_pt[i + 1];
				next_board[5] = current_board[5]; 
				memory_bank.push();
				child_value = &table[next_board[0]][next_board[1]][next_board[2]][next_board[3]];
				if (*child_value == -1)
				{
					*child_value = current_board[5];
					if (*child_value == 1)
					{
						cout << "Boardu: " << next_board[0] << " " << next_board[1] << " " << next_board[2] << " " << next_board[3] << endl << "Dodeljeno: " << current_board[5] << endl;
					}
					counter++;
				}
			}
			else
			{
				next_board = memory_bank.get_empty();
				copy_prunes_and_zero(current_board, next_board);
				next_board[3] = next_board[index];
				next_board[index] = current_board[3];
				child_version = &versions[next_board[0]][next_board[1]][next_board[2]][next_board[3]];
				if (*child_version == depth) continue;
				*child_version = depth;
				next_board[4] = action_pt[i + 1];
				next_board[5] = current_board[5] + 1;
				if (next_board[5] > depth) continue;

				memory_bank.push();
				child_value = &table[next_board[0]][next_board[1]][next_board[2]][next_board[3]];
				if (*child_value == -1)
				{
					*child_value = current_board[5] + 1; //ovde si stavio depth umesto current+1, zasto je ovo napravilo razliku, pomozi bog, ali izgleda da onako uspevaju da se penju u debilne verndosti

					cout << "Boardu: " << next_board[0] << " " << next_board[1] << " " << next_board[2] << " " << next_board[3] << endl << "Dodeljeno peasentski: " << current_board[5] + 1 << endl;


					counter++;
				}
			}
		}
	}



}

void save_partition_to_file6633(int**** table)
{
	ofstream file;
	file.open("../Output/sixsixthreepartitionthree.txt");
	int twocounter = 0;
	for (int i1 = 0; i1 < 16; i1++)
	{
		for (int i2 = 0; i2 < 16; i2++)
		{
			for (int i3 = 0; i3 < 16; i3++)
			{
				for (int i4 = 0; i4 < 16; i4++)
				{
					file << table[i1][i2][i3][i4] << " ";
					if (table[i1][i2][i3][i4] == 2)
					{
						twocounter++;
					}
				}
			}
		}
	}
	cout << "Two  counter: " << twocounter << endl;
	file.close();
}

void initialize_table_partition6633ida()
{
	clock_t begin = clock();
	int**** table = initialize_table6633ida(-1);
	int**** versions = initialize_table6633ida(0);
	int*** lookup = initialize_index_lookup6633ida();
	MemoryBank memory_bank(6, 300000);
	int depth = 0;
	int counter = 1; //we want to find 3360*13=43360
	while (true)
	{
		depth++;
		dfs(table, memory_bank, depth, lookup, versions, counter);
		if (counter == 43680)
		{
			break;
			cout << counter << endl;
		}
		
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Seconds" << elapsed_secs << endl;
	save_partition_to_file6633(table);
}




