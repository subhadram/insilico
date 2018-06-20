#ifndef INCLUDED_CA_CONC_HPP
#define INCLUDED_CA_CONC_HPP

#include "insilico/core/engine.hpp"

namespace insilico {

class Ca_conc {
 public:
  static void current(state_type &variables, state_type &dxdt, const double t,int index)
 { 
    //double beta = 0.05,tauc = 14.0;
     double beta = 1.0512E-3,tauc = 14.0;
      //double beta = 1.0512,tauc = 14.0;
    //double I_cav2 = insilico::engine::neuron_value(index, "I_cav2");
    //double I_cav2 = insilico::engine::neuron_value(index, "tn");
   double I_cav = insilico::engine::neuron_value(index, "I_cav");
    unsigned Ca_conc_index = insilico::engine::neuron_index(index, "Ca_conc");
    double Ca_conc = variables[Ca_conc_index] = std::max<double>(variables[Ca_conc_index],0.000001);
    /*unsigned R_index = insilico::engine::neuron_index(index, "I_sahp_R");
    unsigned CA1R_index = insilico::engine::neuron_index(index, "I_sahp_CA1R");
    unsigned CA2R_index = insilico::engine::neuron_index(index, "I_sahp_CA2R");
    unsigned CA3R_index = insilico::engine::neuron_index(index, "I_sahp_CA3R");
    unsigned CA4R_index = insilico::engine::neuron_index(index, "I_sahp_CA4R");
    // unsigned O_index = insilico::engine::neuron_index(index, "I_sahp_O");
    //double ru = 0.5E-3;
    //double rb = 10E-6;
    //double ro = 0.600;
    //double rc = 0.400;
    double R = variables[R_index];
    double CA1R = variables[CA1R_index];
    double CA2R = variables[CA2R_index];
    double CA3R = variables[CA3R_index];
    double CA4R = variables[CA4R_index];
    //double O = variables[O_index]; 
*/
    // ODE set
    //dxdt[Ca_conc_index] = ((-(beta*I_cav)*5.3E-9)/(1E-15*2*96490.0)) - (Ca_conc)/tauc ;
    dxdt[Ca_conc_index] = (-1.0*I_cav*2.0E-4) - (Ca_conc)/tauc ;
    //dxdt[Ca_conc_index] = -(0.00*I_cav) - (Ca_conc)/tauc ;
    //std::cout << "hi";
    /*
    if (t==5.0)
    {then Ca_conc = 1.0;
    }
    else
    {Ca_conc = 0.0}
*/
    insilico::engine::neuron_value(index, "Ca_conc", Ca_conc);
	//std::cout << Ca_conc;
  } // function current
}; // class Ca_conc

} // insilico

#endif
