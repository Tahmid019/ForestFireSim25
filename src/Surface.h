#ifndef SURFACE_H
#define SURFACE_H

#include<vector>
#include "Cell.h"

class Surface{
private:
    int width;
    int height;
    
    // add the input GIS layers in this class

    std::vector<std::vector<Cell>> grid;
public:
    Surface(int width, int height);

    Cell getCell(int i, int j);
};

#endif
