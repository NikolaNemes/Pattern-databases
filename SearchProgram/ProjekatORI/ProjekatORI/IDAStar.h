#pragma once
#include "GameLogic.h"
#include "SearchObject.h"
#include <iostream>
#include <stack>
#include "Heuristic.h"
#include "MemoryBank.h"

int* dfs(GameLogic& game_logic, table state_and_action, int depth, int****** partition1, int****** partition2, int*** partition3, MemoryBank& mem_bank, Heuristic heuristic_enum, int& search_node_counter);
int* solve_puzzle(GameLogic& game_logic, table state, int****** partition1, int****** partition2, int*** partition3, Heuristic heuristic_enum, int& search_node_counter);