#ifndef INCLUDED_I_NA
#define INCLUDED_I_NA

#include "insilico/core/engine.hpp"

namespace insilico {

class I_Na {
 public:
  static void current(state_type &variables, state_type &dxdt, const double t, int index) {
    double gna = 120.0, ena = 50.0;

    int v_index = engine::neuron_index(index, "v");
    int m_index = engine::neuron_index(index, "m");
    int h_index = engine::neuron_index(index, "h");
    
    double v = variables[v_index];
    double m = variables[m_index];
    double h = variables[h_index];
    
    double alpha_m = 0.01*(v+40.0)/(1-exp(-(v+40.0)/10.0));
    double beta_m  = 4.0*exp(-(v+65)/18.0);
    double alpha_h = 0.07*exp(-(v+65)/ 20.0);
    double beta_h  = 1.0/(1.0+(exp(-(v+35.0)/10.0)));

    // ODE set
    dxdt[m_index]=(alpha_m*(1-m)-beta_m*m);
    dxdt[h_index]=(alpha_h*(1-h)-beta_h*h);

    // Current
    engine::neuron_value(index, "I_Na", (gna * pow(m, 3) * h * (v - ena)));

  } // function current
}; // class I_Na

} // insilico

#endif
