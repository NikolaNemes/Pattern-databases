#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include "MemoryBank.h"
#include <ctime>

void initialize_table_partition6633();
void initialize_table_partition6631();
void initialize_table_partition6632();
void initialize_table_partition6633ida();

namespace Partition1
{
	void create_partition_inplace();
}

namespace Partition3
{
	void create_partition_inplace();
}



std::vector<vector<int>> initialize_index_lookup();