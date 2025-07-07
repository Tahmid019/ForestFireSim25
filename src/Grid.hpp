#pragma once
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

#include "../algorithms/ISpreadModel.hpp"

using namespace std;
using Grid = vector<vector<int>>;

class GridManager {
	Grid grid;
public:
	GridManager(int r, int c) : grid(r, vector<int>(c, 1)) {}
	void ignite(int i, int j) { grid[i][j] = 2; }

	void display() {
		system("clear");
		for (const auto& row : grid) {
			for (int cell : row) {
				if (cell == 0) cout << ". ";
				else if (cell == 1) cout << "O ";
				else if (cell == 2) cout << "X ";
			}
			cout << endl;
		}
	}

	void simulate(ISpreadModel& model, int steps, int delay_ms = 200) {
		Grid next = grid;
		for (int t = 0; t < steps; t++) {
			model.step(grid, next);
			grid = next;
			display();
			this_thread::sleep_for(chrono::milliseconds(delay_ms));
		}
	}
};
