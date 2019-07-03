#include "MemoryBank.h"

MemoryBank::MemoryBank()
{
	this->memory = new int[17 * 20000];
	for (int i = 0; i < 20000; i++)
	{
		this->free_slots.emplace(&(this->memory[i * 17]));
	}
}

MemoryBank::~MemoryBank()
{
	delete[] this->memory;
}
