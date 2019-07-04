#include <iostream>
#include "GameLogic.h"
#include "SearchObject.h"
#include "IDAStar.h"
#include "Heuristic.h"
#include <string>
#include <iostream>

using namespace std;


void copy_table_with_action(int* to_copy, int* target)
{
	for (int i = 0; i < 17; i++)
	{
		target[i] = to_copy[i];
	}
}

void drawBrd(int* brd) {
	int r; std::cout << "\n\n";
	for (int y = 0; y < 4; y++) {
		std::cout << "+----+----+----+----+\n";
		for (int x = 0; x < 4; x++) {
			r = brd[x + y * 4];
			std::cout << "| ";
			if (r < 10 && r != -1) std::cout << " ";
			if (!r) std::cout << "  ";
			else std::cout << r << " ";
		}
		std::cout << "|\n";
	}
	std::cout << "+----+----+----+----+\n";
}

void select_table(int* current_table, int& moves_away)
{
	int input;
	cout << "Possible distances" << endl;
	cout << "==========================" << endl;
	cout << "1. 50 moves away" << endl;
	cout << "2. 56 moves away" << endl;
	cout << "3. 58 moves away" << endl;
	cout << "4. 60 moves away" << endl;
	cout << "==========================" << endl;
	cout << "Input: ";
	cin >> input;
	if (input == 1)
	{
		moves_away = 50;
		int temp_table[17] = { 4, 15, 0, 10, 2, 14, 13, 3, 9, 12, 1, 6, 5, 7, 11, 8, 0 };
		copy_table_with_action(temp_table, current_table);
	}
	else if (input == 2)
	{
		moves_away = 56;
		int temp_table[17] = { 8, 12, 13, 1, 14, 15, 5, 10, 6, 9, 0, 4, 2, 11, 7, 3, 0 };
		copy_table_with_action(temp_table, current_table);
	}
	else if (input == 3)
	{
		moves_away = 58;
		int temp_table[17] = { 8, 12, 13, 1, 14, 15, 5, 10, 6, 11, 9, 4, 2, 0, 7, 3, 0 };
		copy_table_with_action(temp_table, current_table);
	}
	else if (input == 4)
	{
		moves_away = 60;
		int temp_table[17] = { 8, 12, 13, 1, 14, 5, 9, 0, 2, 6, 15, 10, 11, 7, 3, 4, 0 };
		copy_table_with_action(temp_table, current_table);
	}
	else
	{
		cout << "Invalid option selected, no changes will be made" << endl;
	}
	//ovo je najudaljenija - 80 poteza
	//int temp_table[17] = { 15, 14, 8, 12, 10, 11, 9, 13, 2, 6, 5, 1, 3, 7, 4, 0, 0 };

}

void select_heuristic(string& heuristic, Heuristic& heuristic_enum)
{
	int input;
	cout << "Possible heuristics" << endl;
	cout << "==========================" << endl;
	cout << "1. Manhattan" << endl;
	cout << "2. 663 Heuristic" << endl;
	cout << "3. Manhattan+663 heuristic" << endl;
	cout << "==========================" << endl;
	cin >> input;
	if (input == 1)
	{
		heuristic = "Manhattan";
		heuristic_enum = MANHATTAN;
	}
	else if (input == 2)
	{
		heuristic = "663 Heuristic";
		heuristic_enum = P663;
	}
	else if (input == 3)
	{
		heuristic = "Manhattan+663";
		heuristic_enum = MANHHATTAN_ANDP663;
	}
	else
	{
		cout << "No valid option selected, no changes will be made" << endl;
	}
}



void run_test(GameLogic& game_logic, table real_table, int****** partition1, int****** partition2, int*** partition3, Heuristic heuristic_enum)
{
	int counter = 0;
	int search_node_counter = 0;
	int* actions = solve_puzzle(game_logic, real_table, partition1, partition2, partition3, heuristic_enum, search_node_counter);

	cout << "Table solution" << endl;
	cout << "==============================" << endl;
	int* temp_table = new int[17];
	copy_table_with_action(real_table, temp_table);
	drawBrd(temp_table);
	while (true)
	{
		if (*actions == Action::NONE)
		{
			cout << "Done";
			break;
		}
		else
		{
			cout << "Action: " << *actions << endl;
			
			
			game_logic.apply_action_inplace(temp_table, (Action)*actions);
			drawBrd(temp_table);
			cout << "==============================" << endl;
			actions = actions + 1;
			counter++;
		}
	}
	cout << "Solved in: " << counter << " moves" << endl;
	cout << "Search nodes expanded: " << search_node_counter << endl;
	cout << "==============================" << endl;
	delete[] temp_table;
}




int main() {

	//initialization of tables for 663 pattern database
	int****** partition1 = new int*****[16];
	int****** partition2 = new int*****[16];
	int*** partition3 = new int**[16];
	initialize_partitions663(partition1, partition2, partition3);

	//udaljena za 50
	int real_table[17] = { 4, 15, 0, 10, 2, 14, 13, 3, 9, 12, 1, 6, 5, 7, 11, 8, 0 };

	int moves_away = 50;
	string heuristic = "Manhattan";
	Heuristic heuristic_enum = MANHATTAN;

	GameLogic game_logic;

	int input;
	while (true)
	{
		cout << "Status" << endl;
		cout << "Currently selected table is: " << moves_away << " moves away." << endl;
		cout << "Currently selected heuristic is: " << heuristic << endl;
		cout << "Menu" << endl;
		cout << "==========================" << endl;
		cout << "1. Select another table" << endl;
		cout << "2. Select another heuristic" << endl;
		cout << "3. Run test" << endl;
		cout << "4. Quit" << endl;
		cout << "==========================" << endl;
		cout << "Input: ";
		cin >> input;
		if (input == 1)
		{
			select_table(real_table, moves_away);
		}
		else if (input == 2)
		{
			select_heuristic(heuristic, heuristic_enum);
		}
		else if (input == 3)
		{
			run_test(game_logic, real_table, partition1, partition2, partition3, heuristic_enum);
		}
		else if (input == 4)
		{
			break;
		}
	}
}