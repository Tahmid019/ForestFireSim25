#include "Grid.hpp"
#include "../algorithms/ISpreadModel.hpp"
#include "../algorithms/spreadModel_1.hpp"

using namespace std;

extern int MainGrid() {

	int rows = 20, cols = 20;
	GridManager gm(rows, cols);
	gm.ignite(rows / 2, cols / 2); 

	SpreadModel_1 model;
	gm.simulate(model, 50, 200);

	return 0;
}