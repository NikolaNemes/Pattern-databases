#pragma once
#include "GameLogic.h"

class SearchObject
{
private:
	SearchObject* previous;
	MemoryBank* mem_bank;
	int price;
	int* state_and_action;
	int ref_count = 0;
public:
	SearchObject(int* state_and_action, int price, SearchObject* previous, MemoryBank* mem_bank) : price(price), state_and_action(state_and_action), previous(previous), ref_count(0), mem_bank(mem_bank) {};
	SearchObject* get_previous();
	~SearchObject();
	int get_price();
	int* get_state();
	void incr_ref_count();
	int decr_ref_count();
	int get_ref_count();
};