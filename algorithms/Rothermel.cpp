#include "Rothermel.h"
#include <iostream>

// Constructor
Rothermel::Rothermel(
    double w0, double depth, double rhop, double sig,
    double St, double Se, double Mf, double Mx,
    double wind, double h_val, double slope_angle
) {
    w_0 = w0;
    del = depth;
    rho_p = rhop;
    sigma = sig;
    S_t = St;
    S_e = Se;
    M_f = Mf;
    M_x = Mx;
    h = h_val;
    U = wind;
    theta = slope_angle;

    rho_b = calc_rho_b();
    beta = calc_beta();
    beta_op = calc_beta_op();
    w_n = calc_w_n();
    neu_M = calc_neu_M();
    neu_s = calc_neu_s();
    A = calc_A();
}

// Public Method
double Rothermel::get_ros() {
    double E_total_fuel = calc_E_total_fuel();
    double max_rxn_vel = calc_max_rxn_vel();
    double optim_rxn_vel = calc_optim_rxn_vel(max_rxn_vel);
    double rxn_vel = calc_rxn_vel(optim_rxn_vel, neu_M, neu_s);
    double rxn_intensity = calc_reaction_intensity(rxn_vel, E_total_fuel);
    double prop_flux_ratio = calc_prop_flux_ratio();
    double wind_factor = calc_wind_factor();
    double slope_factor = calc_slope_factor();
    double eff_heating_number = calc_eff_heating_number();
    double heat_of_preignition = calc_heat_of_preignition();

    double heat_source = rxn_intensity * prop_flux_ratio * (1 + wind_factor + slope_factor);
    double heat_sink = rho_b * eff_heating_number * heat_of_preignition;

    return heat_source / heat_sink;
}

// ---- Private Helper Methods ----

double Rothermel::calc_E_total_fuel() {
    return w_n * h;
}

double Rothermel::calc_A() {
    return 133 * pow(sigma, -0.7913);
}

double Rothermel::calc_beta_op() {
    return 3.348 * pow(sigma, -0.8189);
}

double Rothermel::calc_beta() {
    return rho_b / rho_p;
}

double Rothermel::calc_rho_b() {
    return w_0 / del;
}

double Rothermel::calc_w_n() {
    return w_0 * (1 - S_t);
}

double Rothermel::calc_neu_M() {
    double r_M = std::min(1.0, M_f / M_x);
    return (1 - 2.59 * r_M + 5.11 * r_M * r_M - 3.52 * r_M * r_M * r_M);
}

double Rothermel::calc_neu_s() {
    double ns = 0.174 * pow(S_e, -0.19);
    return std::min(1.0, ns);
}

double Rothermel::calc_max_rxn_vel() {
    return pow(sigma, 1.5) / (495 + 0.0594 * pow(sigma, 1.5));
}

double Rothermel::calc_optim_rxn_vel(double max_rxn_vel) {
    double ratio = beta / beta_op;
    return max_rxn_vel * pow(ratio, A) * exp(A * (1 - ratio));
}

double Rothermel::calc_rxn_vel(double optim_rxn_vel, double moisture_damp_coeff, double mineral_damp_coeff) {
    return optim_rxn_vel * moisture_damp_coeff * mineral_damp_coeff;
}

double Rothermel::calc_reaction_intensity(double rxn_vel, double E_total_fuel) {
    return rxn_vel * E_total_fuel;
}

double Rothermel::calc_prop_flux_ratio() {
    double denom = 192 + 0.2595 * sigma;
    double numer = exp((0.792 + 0.681 * sqrt(sigma)) * (beta + 0.1));
    return numer / denom;
}

double Rothermel::calc_wind_factor() {
    double C = 7.47 * exp(-0.133 * pow(sigma, 0.55));
    double B = 0.02526 * pow(sigma, 0.54);
    double E = 0.715 * exp(-3.59e-4 * sigma);
    return C * pow(U, B) * pow(beta / beta_op, -E);
}

double Rothermel::calc_slope_factor() {
    double theta_rad = theta * PI / 180.0;
    return 5.27 * pow(beta, -0.3) * pow(tan(theta_rad), 2);
}

double Rothermel::calc_eff_heating_number() {
    return exp(-138.0 / sigma);
}

double Rothermel::calc_heat_of_preignition() {
    return 250 + 1116 * M_f;
}
