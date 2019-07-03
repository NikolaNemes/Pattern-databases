#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include "GameLogic.h"

using namespace std;

enum Heuristic { MANHATTAN, P663, MANHHATTAN_ANDP663 };

int manhattan_heuristic(int* table);
void initialize_partitions663(int****** p1, int****** p2, int*** p3);
int six_six_three_heuristic(int****** p1, int****** p2, int*** p3, int* state, Heuristic heuristic_enum);