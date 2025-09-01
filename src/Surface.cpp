#include "../include/Surface.hpp"
#include "../include/Cell.hpp"
#include <random>
#include <vector>
#include <climits>
#include <algorithm>
#include <iostream>

double getRandomDouble(double min, double max){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);
    return dist(gen);
}

Surface::Surface(int width, int height) : 
    width(width),
    height(height)
    {
        grid.resize(width);

        for(int i=0; i<width; i++){
            grid[i].reserve(height);
            for(int j=0; j<height; j++){

                double w0   = getRandomDouble(0.01, 1.5);
                double depth= getRandomDouble(0.1, 1.0);
                double rhop = getRandomDouble(20, 50);
                double sigma= getRandomDouble(1000, 2500);
                double St   = getRandomDouble(0.01, 0.06);
                double Se   = getRandomDouble(0.005, 0.02);
                double Mf   = getRandomDouble(0.02, 0.4);
                double Mx   = getRandomDouble(0.2, 0.35);
                double wind = getRandomDouble(0, 880);           // ft/min
                double h    = getRandomDouble(7000, 9000);
                double slope= getRandomDouble(0, 30);            // degrees
                
                grid[i].emplace_back(w0, depth, rhop, sigma, St, Se, Mf, Mx, wind, h, slope);
            }
        }
    }

Cell* Surface::getCell(int i, int j){
    return &grid[i][j];
}

void Surface::update(Surface& surface){
    std::vector<std::pair<int, int>> to_be_burnt;
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            Cell* cell = surface.getCell(i, j);
            if(cell->status() == 1){
                // cell is burning
                // check on neighbours and update the burning status of them
                std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
                int maxRos = INT_MIN;
                std::pair<int, int>next_burning_cell = {-1, -1}; 
                for (auto [dx, dy] : directions){
                    int nx = i + dx;
                    int ny = j + dy;
                    // int cell_status = ;
                    if(nx >= 0 && ny >= 0 && nx < width && ny < height && surface.getCell(nx,ny)->status()==0){
                        Cell* neigh_cell = surface.getCell(nx, ny);
                        int ros = neigh_cell->getRos();
                        if(maxRos < ros){
                            maxRos = ros;
                            next_burning_cell.first = nx;
                            next_burning_cell.second = ny;
                        }
                    }
                }
                if(next_burning_cell.first != -1 && next_burning_cell.second != -1 )
                    to_be_burnt.push_back(next_burning_cell);
            }
        }   
    }

    if(to_be_burnt.size() != 0){
        for(auto [i, j] : to_be_burnt){
            // std::cout << "Burning " << i << " " << j << "\n";
            Cell* tobeburnt_cell = surface.getCell(i, j);
            tobeburnt_cell->setBurning();
        }
    }
}

void Surface::ignite(Surface& surface, int i, int j){
    Cell* cell = surface.getCell(i, j);
    cell->setBurning();
    // std::cout << "Testing: " << cell->status() << "\n"; 
}
