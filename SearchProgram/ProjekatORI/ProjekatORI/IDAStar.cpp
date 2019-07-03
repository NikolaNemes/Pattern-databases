#include "IDAStar.h"

using namespace std;

int* dfs(GameLogic& game_logic, table state_and_action, int depth, int****** partition1, int****** partition2, int*** partition3, MemoryBank& mem_bank, Heuristic heuristic_enum, int& search_node_counter)
{
	stack<SearchObject*> my_stack;
	SearchObject* root = new SearchObject(state_and_action, 0, nullptr, &mem_bank);
	search_node_counter++;
	my_stack.push(root);
	int* ret_val = nullptr;
	SearchObject* solution = nullptr;
	int max_price = 0;
	while (!my_stack.empty())
	{
		SearchObject* current = my_stack.top();
		my_stack.pop();
		if (game_logic.is_goal_state(current->get_state()))
		{
			solution = current;
			break;
		}
		int** successors = game_logic.get_successors(current->get_state(), (Action)current->get_state()[16]);
		for (int i = 0; i < 4; i++)
		{
			if (successors[i] == nullptr)
			{
				break;
			}
			if (six_six_three_heuristic(partition1, partition2, partition3, successors[i], heuristic_enum) + 1 + current->get_price() <= depth)
			{
				SearchObject* new_succ = new SearchObject(successors[i], 1 + current->get_price(), current, &mem_bank);
				search_node_counter++;
				current->incr_ref_count();
				my_stack.push(new_succ);
				if (new_succ->get_price() > max_price)
				{
					max_price = new_succ->get_price();
					//cout << "Maksimalna dubina: " << max_price << endl;
				}
			}
			else
			{
				//delete[] successors[i];
				mem_bank.free_slots.push(successors[i]);
			}

		}
		//za ovo nisam napravio memory bank, jos
		delete[] successors;
		if (current->get_ref_count() == 0)
		{
			if (current->get_previous() != nullptr)
			{
				delete current;
			}
		}
	}
	if (solution != nullptr)
	{
		SearchObject* to_delete = solution;
		vector<Action> temp;
		while (solution->get_previous() != nullptr)
		{
			temp.insert(temp.begin(), (Action)solution->get_state()[16]);
			solution = solution->get_previous();
		}
		temp.push_back(Action::NONE);
		ret_val = new int[temp.size()];
		for (int i = 0; i < temp.size(); i++)
		{
			ret_val[i] = temp[i];
		}
		delete to_delete;
	}
	return ret_val;
}

int* solve_puzzle(GameLogic& game_logic, table state, int****** partition1, int****** partition2, int*** partition3, Heuristic heuristic_enum, int& search_node_counter)
{
	MemoryBank mem_bank;
	game_logic.set_memory_bank(&mem_bank);
	int* ret_val = nullptr;
	int depth = 0;
	while (true)
	{
		depth++;
		cout << "Depth: " << depth << endl;
		ret_val = dfs(game_logic, state, depth, partition1, partition2, partition3, mem_bank, heuristic_enum, search_node_counter);
		if (ret_val != nullptr)
		{
			break;
		}
	}
	return ret_val;
}

