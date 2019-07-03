#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "MemoryBank.h"


typedef int* table;

using namespace std;

enum Action { NONE = 0, UP=1, DOWN=2, LEFT=3, RIGHT=4};

class GameLogic 
{
private:
	int goal_state[16];
	map<Action, int*> lookup_table;
	void init_lookup_tables();
	MemoryBank* mem_bank;
public:
	GameLogic();
	bool is_goal_state(table state);
	int* get_possible_actions(table state, Action previous_action);
	int* apply_action(table state, Action action);
	void apply_action_inplace(table state, Action action);
	int** get_successors(table state, Action action);
	MemoryBank* get_mem_bank();
	void set_memory_bank(MemoryBank* mem_bank);
};