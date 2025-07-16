#ifndef CELL_H
#define CELL_H

#include<vector>
#include "../algorithms/Rothermel.h"

class Cell : public Rothermel{
    private:
        double w0;
        double depth;
        double rhop;
        double sig;
        double St;
        double Se;
        double Mf;
        double Mx;
        double wind;
        double h_val;
        double slope_angle;
        bool isBurning;
        std::vector<double> wind_vec;
    public:
        Cell( 
            double w0,
            double depth,
            double rhop,
            double sig,
            double St,
            double Se,
            double Mf,
            double Mx,
            double wind,
            double h_val,
            double slope_angle
            );
        
        Cell() : 
            w0(0), depth(0), rhop(0), sig(0), St(0), Se(0),
            Mf(0), Mx(0), wind(0), h_val(0), slope_angle(0), 
            Rothermel(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) // instantiate model
            {}
        // methods
        void setBurning();
        int status();
        double getRos();
};
#endif
