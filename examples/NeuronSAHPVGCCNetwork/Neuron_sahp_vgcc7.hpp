
#ifndef INCLUDED_NEURON_SAHP_VGCC_HPP
#define INCLUDED_NEURON_SAHP_VGCC_HPP

#include "insilico/core/engine.hpp"
#include "insilico/neuron/helper/spike_list.hpp"

#include "I_K_HH.hpp"
#include "I_Leak_HH.hpp"
#include "I_Na_HH.hpp"
#include "I_cavr7.hpp"
#include "Ca_conc.hpp"
#include "I_sahp.hpp"

namespace insilico {

class Neuron_sahp_vgcc : public Neuron {
 public:
  void ode_set(state_type &variables, state_type &dxdt,
               const double t, unsigned index){
  

    unsigned v_index = engine::neuron_index(index, "v");
    double v = variables[v_index];
    double tq = engine::neuron_value(index, "tq");
    double fail = engine::neuron_value(index, "fail");
    double vv = engine::neuron_value(index, "vv");
    double rt = engine::neuron_value(index, "rt");
    // note the spike
    double last_spiked = engine::neuron_value(index, "last_spike");
     double tstop = engine::neuron_value(1, "tstop");
    double spike_duration = engine::neuron_value(index, "spike_duration");
    double thresh = engine::neuron_value(index, "thresh");
	
    // associated delay for next spikes
    if((v > thresh) && (t - last_spiked) > spike_duration){
      engine::neuron_value(index, "last_spike", t);
    }
    double I_Syn = 0;
    std::vector<unsigned int> s_indices = engine::get_pre_neuron_indices(index, "s");
    std::vector<double> esyn_values = engine::get_pre_neuron_values(index, "esyn");
    std::vector<double> gsyn_values = engine::get_pre_neuron_values(index, "gsyn");
   
    for(std::vector<int>::size_type iterator = 0; iterator < s_indices.size(); ++iterator) {
      I_Syn = I_Syn + gsyn_values[iterator]*variables[s_indices[iterator]] * (v - esyn_values[iterator]);
    }
    insilico::engine::neuron_value(index, "I_Syn", I_Syn);
     double ts2 = engine::neuron_value(index, "ts2");
    // ODE set
    I_Na_HH::current(variables, dxdt, t, index);
    I_K_HH::current(variables, dxdt, t, index);
    I_Leak_HH::current(variables, dxdt, t, index);
    I_sahp::current(variables, dxdt, t, index);
    Ca_conc::current(variables, dxdt, t, index);
    
    std::vector<double> I_Noise = injector::external_current(index, t);
    double current = 0;
    if(!I_Noise.empty())
      current = I_Noise[0];
		
	 	
    double I_Na = engine::neuron_value(index, "I_Na_HH");
    double I_K = engine::neuron_value(index, "I_K_HH");
    double I_Leak = engine::neuron_value(index, "I_Leak_HH");
    double I_Ext = engine::neuron_value(index, "iext");
    double I_sahp = engine::neuron_value(index, "I_sahp");
    
   if (tq < tstop){
  	fail = 1.0;
  }
  
 if (tstop> tq){
  if (fail == 1.0){
  	if (v > -70){
  	
  		std::random_device sd;
    	std::mt19937_64 gn(sd());
    	std::uniform_real_distribution<double> distibution(0.0, 1.0);
   		double sn = distibution(gn);
   		if (sn < rt){
   			fail = 0.0;
   		
   			}
   			tq = tstop +15;
   	}
 }
}  
    double I_cav2 = engine::neuron_value(index, "I_cav2");
    
    
      
    double amp_noise = engine::neuron_value(index, "amp_noise");
   
     double gg = 1.0;
   if (tstop < 1000.0){
   gg = 0.0;}
    dxdt[v_index] = (gg*I_Ext) - I_Na - I_K - I_Leak -I_Syn -I_sahp- (I_cav2) ;
   
  
        insilico::engine::neuron_value(index, "tq", tq);
    insilico::engine::neuron_value(index, "fail", fail);
     insilico::engine::neuron_value(index, "vv", vv);
     
  } // function ode_set
}; // class N_SquidAxon_HH1952

} // insilico

#endif
