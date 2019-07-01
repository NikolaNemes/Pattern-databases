#include "MemoryBank.h"

//deprecated
MemoryBank::MemoryBank()
{
}

MemoryBank::MemoryBank(int chunk_size, int slot_count)
{
	this->memory = new char[slot_count * chunk_size];
	first_taken = &this->memory[0];
	first_free = &this->memory[0];
	this->temp_slot = new char[16];
	this->turnover = &this->memory[slot_count * chunk_size];
}

MemoryBank::~MemoryBank()
{
	delete[] this->memory;
	delete[] this->temp_slot;
}

