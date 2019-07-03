#include "GameLogic.h"

void GameLogic::init_lookup_tables()
{
	int* no_action = new int[16*4];
	int* left_action = new int[16 * 4];
	int* right_action = new int[16 * 4];
	int* up_action = new int[16 * 4];
	int* down_action = new int[16 * 4];
	for (int i = 0; i < 16; i++) 
	{
		vector<Action> temp_none;
		vector<Action> temp_left;
		vector<Action> temp_right;
		vector<Action> temp_up;
		vector<Action> temp_down;
		if (((i + 3) / 4) == ((i + 4) / 4))
		{
			temp_none.push_back(Action::LEFT);
			temp_left.push_back(Action::LEFT);
			temp_up.push_back(Action::LEFT);
			temp_down.push_back(Action::LEFT);
		}
		if (((i + 1) / 4) == (i / 4))
		{
			temp_none.push_back(Action::RIGHT);
			temp_right.push_back(Action::RIGHT);
			temp_up.push_back(Action::RIGHT);
			temp_down.push_back(Action::RIGHT);
		}
		if ((i - 4) >= 0)
		{
			temp_none.push_back(Action::UP);
			temp_left.push_back(Action::UP);
			temp_right.push_back(Action::UP);
			temp_up.push_back(Action::UP);
		}
		if ((i + 4) <= 15)
		{
			temp_none.push_back(Action::DOWN);
			temp_left.push_back(Action::DOWN);
			temp_right.push_back(Action::DOWN);
			temp_down.push_back(Action::DOWN);
		}
		for (int j = 0; j < 5; j++) {
			if ((temp_none.size() < j))
			{
				temp_none.push_back(Action::NONE);
			}
			if ((temp_up.size()) < j)
			{
				temp_up.push_back(Action::NONE);
			}
			if ((temp_left.size()) < j)
			{
				temp_left.push_back(Action::NONE);
			}
			if ((temp_right.size()) < j) 
			{
				temp_right.push_back(Action::NONE);
			}
			if ((temp_down.size()) < j)
			{
				temp_down.push_back(Action::NONE);
			}
		}
		for (int j = 0; j < 4; j++)
		{
			no_action[4 * i + j] = temp_none[j];
			left_action[4 * i + j] = temp_left[j];
			right_action[4 * i + j] = temp_right[j];
			up_action[4 * i + j] = temp_up[j];
			down_action[4 * i + j] = temp_down[j];
		}
	}
	this->lookup_table[Action::NONE] = no_action;
	this->lookup_table[Action::UP] = up_action;
	this->lookup_table[Action::RIGHT] = right_action;
	this->lookup_table[Action::LEFT] = left_action;
	this->lookup_table[Action::DOWN] = down_action;

}

GameLogic::GameLogic()
{
	this->init_lookup_tables();
	for (int i = 0; i < 16; i++) {
		this->goal_state[i] = i;
	}
}

bool GameLogic::is_goal_state(table state)
{
	for (int i = 0; i < 16; i++)
	{
		if (state[i] != this->goal_state[i])
		{
			return false;
		}
	}
	return true;
}

int * GameLogic::get_possible_actions(table state, Action previous_action)
{
	int index = 0;
	for (int i = 0; i < 16; i++) {
		if (state[i] == 0)
		{
			index = i;
			break;
		}
	}
	return &this->lookup_table[previous_action][index * 4];
}

int * GameLogic::apply_action(table state, Action action)
{

	//int* new_state = new int[17];
	int* new_state = this->mem_bank->free_slots.top();
	this->mem_bank->free_slots.pop();
	int zero_index = 0;
	for (int i = 0; i < 16; i++)
	{
		new_state[i] = state[i];
		if (state[i] == 0)
		{
			zero_index = i;
		}
	}
	new_state[16] = action;
	if (action == Action::UP)
	{
		new_state[zero_index] = new_state[zero_index - 4];
		new_state[zero_index - 4] = 0;
	}
	else if (action == Action::DOWN)
	{
		new_state[zero_index] = new_state[zero_index + 4];
		new_state[zero_index + 4] = 0;
	}
	else if (action == Action::LEFT)
	{
		new_state[zero_index] = new_state[zero_index - 1];
		new_state[zero_index - 1] = 0;
	}
	else if (action == Action::RIGHT)
	{
		new_state[zero_index] = new_state[zero_index + 1];
		new_state[zero_index + 1] = 0;
	}
	else
	{
		//do nothing because action is none
	}
	return new_state;
}

void GameLogic::apply_action_inplace(table state, Action action)
{
	int zero_index = 0;
	for (int i = 0; i < 16; i++)
	{
		if (state[i] == 0)
		{
			zero_index = i;
			break;
		}
	}
	state[16] = action;
	if (action == Action::UP)
	{
		state[zero_index] = state[zero_index - 4];
		state[zero_index - 4] = 0;
	}
	else if (action == Action::DOWN)
	{
		state[zero_index] = state[zero_index + 4];
		state[zero_index + 4] = 0;
	}
	else if (action == Action::LEFT)
	{
		state[zero_index] = state[zero_index - 1];
		state[zero_index - 1] = 0;
	}
	else if (action == Action::RIGHT)
	{
		state[zero_index] = state[zero_index + 1];
		state[zero_index + 1] = 0;
	}
	else
	{
		//do nothing because action is none
	}
}


int ** GameLogic::get_successors(table state, Action action)
{
	int** ret_val = new int*[4];
	int* actions = this->get_possible_actions(state, action);
	for (int i = 0; i < 4; i++)
	{
		if (actions[i] != Action::NONE)
		{
			ret_val[i] = this->apply_action(state, (Action)actions[i]);
		}
		else
		{
			ret_val[i] = nullptr;
		}
	}
	return ret_val;
}


MemoryBank * GameLogic::get_mem_bank()
{
	return this->mem_bank;
}

void GameLogic::set_memory_bank(MemoryBank* mem_bank)
{
	this->mem_bank = mem_bank;
}
