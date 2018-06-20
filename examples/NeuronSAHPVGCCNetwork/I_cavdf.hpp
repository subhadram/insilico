#ifndef INCLUDED_I_CAV
#define INCLUDED_I_CAV

#include "insilico/core/engine.hpp"
#include "math.h" 
namespace insilico {

class I_cav {
 public:
  static void current(state_type &variables, state_type &dxdt, const double t, const unsigned index)
 {
    double E_cav = 25,tau = 2.5;
    //double G_cav =  0.005, E_cav = 25,tau = 2.5;
    unsigned v_index = insilico::engine::neuron_index(index, "v");
    unsigned S0_index = insilico::engine::neuron_index(index, "I_cav_S0");
    unsigned S1_index = insilico::engine::neuron_index(index, "I_cav_S1");
    unsigned S2_index = insilico::engine::neuron_index(index, "I_cav_S2");
	double rt = engine::neuron_value(index, "rt");
	double td = engine::neuron_value(index, "td");
    double v = variables[v_index];
    
    double S0 = variables[S0_index];
    double S1 = variables[S1_index];
    double S2 = variables[S2_index];
	double tq = engine::neuron_value(index, "tq");
    double G_cav = engine::neuron_value(index, "G_cav");
    double fail = engine::neuron_value(index, "fail");
    /*fstream f;
    f = open("cav.dat", 'a');
    f.cout << S0<<","<<S1<<","<<S2;*/

    double xi = 1.0/(1.0 + exp(-(v+30.0)/6.0));
    double a = sqrt(xi)/tau;
    double b = (1.0- sqrt(xi))/tau;

    //std::cout << S0<<","<<S1<<","<<S2<<xi<<"\n";
   
    // ODE set
    dxdt[S0_index] = (-2*a*S0) + (b*S1); 
    dxdt[S1_index] = (-b*S1)+(-a*S1)+(2*a*S0)+(2*b*S2);
    dxdt[S2_index] = (a*S1) - (2*b*S2);
    
   
 if (tq < t){
  	fail = 1.0;
  }
  
 if (t> tq+td){
  if (fail == 1.0){
  	if (v > 0){
  	
   			fail = 0.0;
   			//c = c +1;
   			
   			tq = t +7;}
   	
 }
}   

//std::cout << tq<<","<<t<<","<<S2<<"\n";

	insilico::engine::neuron_value(index, "tq", tq);
    insilico::engine::neuron_value(index, "fail", fail);
    double fraction_of_open_channelss = (S2/(S0 + S1 + S2));
    double il = fraction_of_open_channelss;
    double I_cav =  G_cav * fraction_of_open_channelss * (v - E_cav)*fail;
   /* double I_cav = 0.0;
   if (fmod(t,50.0)==0.0)
    {I_cav = 0.01;
    }	
    else
    {I_cav = 0.0;
    }*/
    insilico::engine::neuron_value(index, "I_cav", I_cav);
    insilico::engine::neuron_value(index, "il", il);
    
  } // function current
}; // class I_CAV

} // insilico

#endif
