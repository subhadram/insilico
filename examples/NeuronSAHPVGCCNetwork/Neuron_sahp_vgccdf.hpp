
#ifndef INCLUDED_NEURON_SAHP_VGCC_HPP
#define INCLUDED_NEURON_SAHP_VGCC_HPP

#include "insilico/core/engine.hpp"
#include "insilico/neuron/helper/spike_list.hpp"
//#include<math.h>
#include "I_K_HH.hpp"
#include "I_Leak_HH.hpp"
#include "I_Na_HH.hpp"
#include "I_cavdf.hpp"
//#include "I_cavr.hpp"
#include "Ca_concd.hpp"
//#include "I_sahpc2.hpp"
#include "I_sahp.hpp"

namespace insilico {

class Neuron_sahp_vgcc : public Neuron {
 public:
  void ode_set(state_type &variables, state_type &dxdt,
               const double t, unsigned index){
    //std::vector<unsigned> g1_indices;
    //std::vector<double> esyn_values;

    unsigned v_index = engine::neuron_index(index, "v");
    //std::cout << v_index<< " " <<t<<" "<<std::endl;
    double v = variables[v_index];

    // note the spike
    double last_spiked = engine::neuron_value(index, "last_spike");
    double spike_duration = engine::neuron_value(index, "spike_duration");
    double thresh = engine::neuron_value(index, "thresh");
	double dt = engine::neuron_value(index, "dt");
    // associated delay for next spikes
    if((v > thresh) && (t - last_spiked) > spike_duration){
      engine::neuron_value(index, "last_spike", t);
    }
    //std::cout << engine::neuron_value(index, "last_spike")<<std::endl;
    // incoming synaptic currents
    double I_Syn = 0;
    std::vector<unsigned int> s_indices = engine::get_pre_neuron_indices(index, "s");
    //std::vector<unsigned int> w_indices = engine::get_pre_neuron_indices(index, "w");
    std::vector<double> esyn_values = engine::get_pre_neuron_values(index, "esyn");
    std::vector<double> gsyn_values = engine::get_pre_neuron_values(index, "gsyn");
   // g1_indices = engine::get_pre_neuron_indices(index, "g1");
   // esyn_values = engine::get_pre_neuron_values(index, "esyn");
   
   //std::cout << current;
    for(std::vector<int>::size_type iterator = 0; iterator < s_indices.size(); ++iterator) {
      I_Syn = I_Syn + gsyn_values[iterator]/**(1.0+variables[w_indices[iterator]])*/*variables[s_indices[iterator]] * (v - esyn_values[iterator]);
    }
    insilico::engine::neuron_value(index, "I_Syn", I_Syn);
     //double ts2 = engine::neuron_value(index, "ts2");
    // ODE set
    I_Na_HH::current(variables, dxdt, t, index);
    I_K_HH::current(variables, dxdt, t, index);
    I_Leak_HH::current(variables, dxdt, t, index);
    I_sahp::current(variables, dxdt, t, index);
    //I_sahp2::current(variables, dxdt, t, index);
    I_cav::current(variables, dxdt, t, index);
    double a = 0;
    /*
   if (t + dt > ts2){
     while (ts2 < t+ dt){
    I_cav2::current(variables, dxdt, t, index);
    ts2 = engine::neuron_value(index, "ts2");
    a = a + 1;
      std::cout << ts2<< " " <<t<<" "<<a<<std::endl ;
    }}
    else{
      I_cav2::current(variables, dxdt, t, index);
      }
   */
  /* if (index == 1){
   //std::cout << "Hi"<< " " <<std::endl ;
    I_cav2::current(variables, dxdt, t, index);
  }
  */
    Ca_conc::current(variables, dxdt, t, index);
    //I_cav2::current(variables, dxdt, t, index);
  // I_cav2::current(variables, dxdt, t, index);
    std::vector<double> I_Noise = injector::external_current(index, t);
    double current = 0;
    if(!I_Noise.empty())
      current = I_Noise[0];
		
	 //std::cout << current;
   // std::cout << t << " "<< current << std::endl ; 	
    double I_Na = engine::neuron_value(index, "I_Na_HH");
    double I_K = engine::neuron_value(index, "I_K_HH");
    double I_Leak = engine::neuron_value(index, "I_Leak_HH");
    double I_Ext = engine::neuron_value(index, "iext");
    double I_sahp = engine::neuron_value(index, "I_sahp");
    //double I_sahp2 = engine::neuron_value(index, "I_sahp2");
    	//std::cout << I_sahp<< " " <<std::endl ;
     double I_cav = engine::neuron_value(index, "I_cav");
     //double ts2 = engine::neuron_value(index, "ts2");
    
    //double gg = 1.0 ;
    	
   //double I_cav2 = engine::neuron_value(index, "I_cav2");
 
     // if (t < 1000.0){
   //gg = 0.0;}
    
     // std::cout << t << " "<< current << std::endl ;
    double amp_noise = engine::neuron_value(index, "amp_noise");
    double tn = I_Ext - I_Na - I_K - I_Leak  -I_Syn -I_sahp- I_cav;
    //double I_Syn = engine::neuron_value(index, "I_Syn");
    //unsigned int Ca_conc_index = engine::neuron_index(index,"Ca_conc");
    //double Ca_conc = variables[Ca_conc_index];
   // insilico::engine::neuron_value(index, "I_Syn", I_Syn);
   //double ic = I_Ext - I_Syn -I_sahp- I_cav ;
    dxdt[v_index] = I_Ext - I_Na - I_K - I_Leak -I_Syn -I_sahp- I_cav +current*amp_noise*sqrt(dt) ;
     insilico::engine::neuron_value(index, "tn", tn);
     //insilico::engine::neuron_value(index, "ic", ic);
    // dxdt[v_index] = sin(3.14*t);
  } // function ode_set
}; // class N_SquidAxon_HH1952

} // insilico

#endif
