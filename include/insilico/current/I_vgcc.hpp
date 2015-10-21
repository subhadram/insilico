// Reference : Peter Jonas(2002)

#ifndef INCLUDED_I_VGCC
#define INCLUDED_I_VGCC

#include "insilico/core/engine.hpp"

namespace insilico {

class I_vgcc {
 public:
  static void current(state_type &variables, state_type &dxdt, const double t, const unsigned index)
 {
    double G_vgcc =  31.222, E_vgcc = 60.33;
    //double G_vgcc =  31.222, E_vgcc = 60.33;
    unsigned v_index = insilico::engine::neuron_index(index, "v");
    unsigned C0_index = insilico::engine::neuron_index(index, "I_vgcc_C0");
    unsigned C1_index = insilico::engine::neuron_index(index, "I_vgcc_C1");
    unsigned C2_index = insilico::engine::neuron_index(index, "I_vgcc_C2");
    unsigned C3_index = insilico::engine::neuron_index(index, "I_vgcc_C3");
    unsigned OP_index = insilico::engine::neuron_index(index, "I_vgcc_OP");  
  

    double v = variables[v_index];
    
    double C0 = variables[C0_index] = std::max<double>(variables[C0_index],0.000001);
    double C1 = variables[C1_index] = std::max<double>(variables[C1_index],0.000001);
    double C2 = variables[C2_index] = std::max<double>(variables[C2_index],0.000001);
    double C3 = variables[C3_index] = std::max<double>(variables[C2_index],0.000001);
    double OP = variables[OP_index] = std::max<double>(variables[OP_index],0.000001);


    //variables[C0_index] = std::max<double>(variables[C0_index],0.0);
    //variables[C1_index] = std::max<double>(variables[C1_index],0.0);
    //variables[C2_index] = std::max<double>(variables[C2_index],0.0);
    //variables[C3_index] = std::max<double>(variables[C3_index],0.0);
    //variables[OP_index] = std::max<double>(variables[OP_index],0.0);


    //double a1 = insilico::engine::neuron_value(index, "I_vgcc_a1");
    //double a2 = insilico::engine::neuron_value(index, "I_vgcc_a2");
    //double a3 = insilico::engine::neuron_value(index, "I_vgcc_a3");
    //double a4 = insilico::engine::neuron_value(index, "I_vgcc_a4");
    //double b1 = insilico::engine::neuron_value(index, "I_vgcc_b1");
    //double b2 = insilico::engine::neuron_value(index, "I_vgcc_b2");
    //double b3 = insilico::engine::neuron_value(index, "I_vgcc_b3");
    //double b4 = insilico::engine::neuron_value(index, "I_vgcc_b4");

    double a1 = 4.04*(exp(v/49.14));
    double b1 = 2.88*(exp(-v/49.14));
    double a2 = 6.70*(exp(v/42.08));
    double b2 = 6.30*(exp(-v/42.08));
    double a3 = 4.39*(exp(v/55.31));
    double b3 = 8.16*(exp(-v/55.31));
    double a4 = 17.33*(exp(v/26.55));
    double b4 = 1.84*(exp(-v/26.55));

    // ODE set
    dxdt[C0_index] = (-a1*C0) + (b1*C1); 
    dxdt[C1_index] = (-b1*C1)+(-a2*C1)+(a1*C0)+(b2*C2);
    dxdt[C2_index] = (-b2*C2)+(-a3*C2)+(a2*C1)+(b3*C3);
    dxdt[C3_index] = (-b3*C3)+(-a4*C3)+(a3*C2)+(b4*OP);
    dxdt[OP_index] = (-b4*OP)+(a4*C3);
  
    double fraction_of_open_channels = (OP/(C0 + C1 + C2 + C3 + OP)); 
    double I_vgcc =  G_vgcc * fraction_of_open_channels  * (v - E_vgcc);

    insilico::engine::neuron_value(index, "I_vgcc", I_vgcc);
    
  } // function current
}; // class I_VGCC

} // insilico

#endif
