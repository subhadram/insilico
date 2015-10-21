#ifndef INCLUDED_CA_CONC_HPP
#define INCLUDED_CA_CONC_HPP

#include "insilico/core/engine.hpp"

namespace insilico {

class Ca_conc {
 public:
  static void current(state_type &variables, state_type &dxdt, const double t, int index)
 { 
    unsigned I_vgcc_index = insilico::engine::neuron_value(index, "I_vgcc");
    unsigned Ca_conc_index = insilico::engine::neuron_index(index, "Ca_conc");
    unsigned R_index = insilico::engine::neuron_index(index, "I_sahp_R");
    unsigned CA1R_index = insilico::engine::neuron_index(index, "I_sahp_CA1R");
    unsigned CA2R_index = insilico::engine::neuron_index(index, "I_sahp_CA2R");
    unsigned CA3R_index = insilico::engine::neuron_index(index, "I_sahp_CA3R");
    unsigned CA4R_index = insilico::engine::neuron_index(index, "I_sahp_CA4R");
    // unsigned O_index = insilico::engine::neuron_index(index, "I_sahp_O");

    double I_vgcc = variables[I_vgcc_index];
    double Ca_conc = variables[Ca_conc_index];
    double ru = 0.5E-3;
    double rb = 10E-12;
    //double ro = 0.600;
    //double rc = 0.400;
    double R = variables[R_index];
    double CA1R = variables[CA1R_index];
    double CA2R = variables[CA2R_index];
    double CA3R = variables[CA3R_index];
    double CA4R = variables[CA4R_index];
    //double O = variables[O_index]; 

    // ODE set
    dxdt[Ca_conc_index] = ((I_vgcc/(1E-12*2*96490)) + (ru*CA1R) - (4*rb*R*Ca_conc) + (2*ru*CA2R) - (3*rb*Ca_conc*CA1R) + (3*ru*CA3R) - (2*rb*CA2R*Ca_conc) + (4*ru*CA4R) - (rb*CA3R*Ca_conc));
 
    //insilico::engine::neuron_value(index, "Ca_conc", Ca_conc);

  } // function current
}; // class Ca_conc

} // insilico

#endif
