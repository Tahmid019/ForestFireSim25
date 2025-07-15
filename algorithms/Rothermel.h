#ifndef ROTHERMEL_H
#define ROTHERMEL_H

#include <cmath>

class Rothermel {
private:
    // Input & intermediate parameters
    double beta;         // packing ratio
    double beta_op;      // optimum packing ratio
    double rho_p;        // oven dry particle density
    double rho_b;        // oven dry bulk density
    double w_0;          // oven dry fuel load
    double del;          // fuel depth
    double w_n;          // net fuel load
    double sigma;        // surface area to volume ratio
    double S_t;          // total mineral content
    double S_e;          // effective mineral content
    double neu_M;        // moisture damping coefficient
    double neu_s;        // mineral damping coefficient
    double M_f;          // fuel moisture
    double M_x;          // extinction moisture
    double A;            // empirical constant
    double h;            // heat content
    double U;            // wind velocity
    double theta;        // slope angle in degrees
    const double PI = 3.141592653589793;

    // Internal helper methods
    double calc_E_total_fuel();
    double calc_A();
    double calc_beta_op();
    double calc_beta();
    double calc_rho_b();
    double calc_w_n();
    double calc_neu_M();
    double calc_neu_s();
    double calc_max_rxn_vel();
    double calc_optim_rxn_vel(double max_rxn_vel);
    double calc_rxn_vel(double optim_rxn_vel, double moisture_damp_coeff, double mineral_damp_coeff);
    double calc_reaction_intensity(double rxn_vel, double E_total_fuel);
    double calc_prop_flux_ratio();
    double calc_wind_factor();
    double calc_slope_factor();
    double calc_eff_heating_number();
    double calc_heat_of_preignition();

public:
    Rothermel() : Rothermel(0,0,0,0,0,0,0,0,0,0,0) {} 
    Rothermel(
        double w0, double depth, double rhop, double sig,
        double St, double Se, double Mf, double Mx,
        double wind, double h_val, double slope_angle
    );
    double get_ros();
};

#endif // ROTHERMEL_H
