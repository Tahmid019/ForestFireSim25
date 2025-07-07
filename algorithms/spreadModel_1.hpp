#pragma once
#include "ISpreadModel.hpp"

class SpreadModel_1 : public ISpreadModel {
public:
	void step(const Grid& curr, Grid& next) override {
		int rows = curr.size(), cols = curr[0].size();
		next = curr;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (curr[i][j] == 2) { 
					next[i][j] = 0;
					for (int di = -1; di <= 1; di++) {
						for (int dj = -1; dj <= 1; dj++) {
							int ni = i + di, nj = j + dj;
							if (ni >= 0 && ni < rows &&
								nj >= 0 && nj < cols &&
								curr[ni][nj] == 1) {
								next[ni][nj] = 2;
							}
						}
					}
				}
			}
		}
	}
};