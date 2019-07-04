#pragma once
#include <stack>

using namespace std;


class MemoryBank
{
public:
	MemoryBank();
	~MemoryBank();
	int* memory;
	stack<int*> free_slots;
};