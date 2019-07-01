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
	char* temp_slot;
	char* memory;
	char* stack_memory;
	char* first_taken;
	char* first_free;
	char* turnover;
};