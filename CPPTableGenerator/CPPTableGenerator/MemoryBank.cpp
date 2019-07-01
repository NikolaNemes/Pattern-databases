#include "MemoryBank.h"

MemoryBank::MemoryBank()
{
	this->memory = new int[16 * 20000];
	this->temp_slot = new int[16];
	for (int i = 0; i < 20000; i++)
	{
		this->free_slots.emplace(&(this->memory[i * 17]));
	}
}

MemoryBank::MemoryBank(int chunk_size, int slot_count)
{
	this->memory = new int[chunk_size * slot_count];
	for (int i = 0; i < slot_count; i++)
	{
		this->free_slots.emplace(&(this->memory[i * chunk_size]));
	}
	first_taken = 0;
	first_free = 0;
	this->temp_slot = new int[16];
}

MemoryBank::~MemoryBank()
{
	delete[] this->memory;
	delete[] this->temp_slot;
}
