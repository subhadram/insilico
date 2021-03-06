#ifndef INCLUDED_I_CAV
#define INCLUDED_I_CAV

#include "insilico/core/engine.hpp"

namespace insilico {

class I_cav {
 public:
  static void current(state_type &variables, state_type &dxdt, const double t, const unsigned index)
 {
    double G_cav =  0.125, E_cav =25,tau = 2.5;
    unsigned v_index = insilico::engine::neuron_index(index, "v");
    unsigned S0_index = insilico::engine::neuron_index(index, "I_cav_S0");
    unsigned S1_index = insilico::engine::neuron_index(index, "I_cav_S1");
    unsigned S2_index = insilico::engine::neuron_index(index, "I_cav_S2");

    double v = variables[v_index];
    
    double S0 = variables[S0_index] = std::max<double>(variables[S0_index],0.000001);
    double S1 = variables[S1_index] = std::max<double>(variables[S1_index],0.000001);
    double S2 = variables[S2_index] = std::max<double>(variables[S2_index],0.000001);

    unsigned x = 1.0/(1 + exp(-(v+30.0)/6.0));
    double a = sqrt(x)/tau;
    double b = (1- sqrt(x))/tau;
   
    // ODE set
    dxdt[S0_index] = (-2*a*S0) + (b*S1); 
    dxdt[S1_index] = (-b*S1)+(-a*S1)+(2*a*S0)+(2*b*S2);
    dxdt[S2_index] = (a*S1) - (2*b*S2);

  
    double fraction_of_open_channels = (S2/(S0 + S1 + S2)); 
    double I_cav =  G_cav * fraction_of_open_channels  * (v - E_cav);

    insilico::engine::neuron_value(index, "I_cav", I_cav);
    
  } // function current
}; // class I_CAV

} // insilico

#endif
