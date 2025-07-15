#include "Cell.h"

Cell::Cell(
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
        ) : w0(w0), depth(depth), rhop(rhop), sig(sig),
         St(St), Se(Se), Mf(Mf), Mx(Mx), wind(wind), 
         h_val(h_val), slope_angle(slope_angle),
         Rothermel(w0, depth, rhop, sig, St, Se, Mf, Mx, wind, h_val, slope_angle)
        {}

int Cell::status(){
    return 1;
}

double Cell::getRos(){
    return get_ros();
}
