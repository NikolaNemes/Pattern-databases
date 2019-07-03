#pragma once
#include <stack>
#include <queue>


using namespace std;


class MemoryBank
{
public:
	MemoryBank();
	MemoryBank(int chunk_size, int slot_count);
	~MemoryBank();
	int* temp_slot;
	int* memory;
	int top;
	int empty_pt;
	int* get_top();
	int* get_empty();
	void pop();
	int chunk_size;
	void push();
	bool empty();
};