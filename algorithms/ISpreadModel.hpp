#pragma once
#include <vector>

using namespace std;

using Grid = vector<vector<int>>;

class ISpreadModel {
public:
	virtual ~ISpreadModel() = default;

	virtual void step(const Grid& curr_grid, Grid& next_grid) = 0;
};