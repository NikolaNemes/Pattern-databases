#include <algorithm>
#include "Heuristic.h"

int manhattan_heuristic(int* table)
{
	int total = 0;
	for (int i = 0; i < 16; i++)
	{
		if (table[i] != 0)
		{
			int bigger = std::max(i, table[i]);
			int smaller = std::min(i, table[i]);
			while (((bigger - smaller) / 4) > 0)
			{
				bigger -= 4;
				total++;
			}
			while ((bigger != smaller))
			{
				bigger -= 1;
				total += 1;
			}
		}
	}
	return total;
}