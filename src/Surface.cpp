#include "Surface.h"
#include "Cell.h"
#include <random>
#include <vector>

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

Cell Surface::getCell(int i, int j){
    return grid[i][j];
}
