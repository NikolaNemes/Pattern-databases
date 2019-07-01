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
	int* memory;
	int* temp_slot;
	stack<int*> free_slots;
	int first_taken;
	int first_free;
	queue<int*> remaining;
};