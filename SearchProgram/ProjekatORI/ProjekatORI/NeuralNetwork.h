#pragma once
#include "tiny_dnn\tiny_dnn.h"
#include<string>

void trainPartition3(int*** partition3);
void trainPartition3Encoded(int*** partition3);
void trainPartition1or2Encoded(int****** partition, std::string partition_name);