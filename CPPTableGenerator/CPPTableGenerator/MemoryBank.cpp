#include "MemoryBank.h"

//deprecated
MemoryBank::MemoryBank()
{
}

MemoryBank::MemoryBank(int chunk_size, int slot_count)
{
	this->memory = new int[slot_count * chunk_size];
	this->top = 0;
	this->empty_pt = 0;
	this->chunk_size = chunk_size;
}

MemoryBank::~MemoryBank()
{
	delete[] this->memory;
	delete[] this->temp_slot;
}

int * MemoryBank::get_top()
{
	return &this->memory[this->top * chunk_size];
}

int * MemoryBank::get_empty()
{
	return &this->memory[this->empty_pt * chunk_size];
}

void  MemoryBank::pop()
{
	this->empty_pt -= this->chunk_size;
	this->top -= this->chunk_size;
	
}

void  MemoryBank::push()
{
	this->empty_pt += this->chunk_size;
	this->top = empty_pt - this->chunk_size;
	
}

bool MemoryBank::empty()
{
	return top == - this->chunk_size;
}

