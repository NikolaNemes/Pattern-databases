#include "SearchObject.h"

SearchObject * SearchObject::get_previous()
{
	return this->previous;
}

SearchObject::~SearchObject()
{
	if (this->previous != nullptr)
	{
		int new_ref_count = this->previous->decr_ref_count();
		if (new_ref_count == 0)
		{
			if (this->previous->get_previous() != nullptr)
			{
				delete previous;
			}
		}
	}
	this->mem_bank->free_slots.push(this->state_and_action);
	//delete[] this->state_and_action;
}

int SearchObject::get_price()
{
	return this->price;
}

int * SearchObject::get_state()
{
	return this->state_and_action;
}

void SearchObject::incr_ref_count()
{
	ref_count++;
}

int SearchObject::decr_ref_count()
{
	ref_count--;
	return ref_count;
}

int SearchObject::get_ref_count()
{
	return ref_count;
}
