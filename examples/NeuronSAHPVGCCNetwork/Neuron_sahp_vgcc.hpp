
#ifndef INCLUDED_NEURON_SAHP_VGCC_HPP
#define INCLUDED_NEURON_SAHP_VGCC_HPP

#include "insilico/core/engine.hpp"
#include "insilico/neuron/helper/spike_list.hpp"

#include "insilico/current/I_K.hpp"
#include "insilico/current/I_Leak.hpp"
#include "insilico/current/I_Na.hpp"
#include "insilico/current/I_sahp.hpp"
//#include "insilico/current/I_vgcc.hpp"
//#include "insilico/current/Ca_conc.hpp"
//#include "(R + CA1R + CA2R + CA3R + CA4R + O).hpp"

namespace insilico {

class Neuron_sahp_vgcc : public Neuron {
 public: 
   void ode_set(state_type &variables, state_type &dxdt,
               const double t,unsigned index) {
    std::vector<unsigned> g1_indices;
    std::vector<double> esyn_values;

    unsigned v_index = engine::neuron_index(index, "v");
    double v = variables[v_index];

    // note the spike
    double last_spiked = engine::neuron_value(index, "last_spike");
    double spike_duration = engine::neuron_value(index, "spike_duration");
    double thresh = engine::neuron_value(index, "thresh");

    // associated delay for next spikes
    if((v > thresh) && (t - last_spiked) > spike_duration){
      engine::neuron_value(index, "last_spike", t);
    }

    // incoming synaptic currents
    double I_Syn = 0;
    g1_indices = engine::get_pre_neuron_indices(index, "g1");
    esyn_values = engine::get_pre_neuron_values(index, "esyn");


    for(unsigned iterator = 0; iterator < g1_indices.size(); ++iterator) {
      I_Syn += variables[g1_indices[iterator]] * (v - esyn_values[iterator]);
    }

    // ODE set
    I_Na::current(variables, dxdt, t, index);
    I_K::current(variables, dxdt, t, index);
    I_Leak::current(variables, dxdt, t, index);
   // I_sahp::current(variables, dxdt, t, index);
    I_vgcc::current(variables, dxdt, t, index);
   // Ca_conc::current(variables, dxdt, t, index);

    double I_Na = engine::neuron_value(index, "I_Na");
    double I_K = engine::neuron_value(index, "I_K");
    double I_Leak = engine::neuron_value(index, "I_Leak");
    double I_Ext = engine::neuron_value(index, "iext");
   double I_sahp = engine::neuron_value(index, "I_sahp");
   // double I_vgcc = engine::neuron_value(index, "I_vgcc");
 //   double Ca_conc = engine::neuron_value(index, "Ca_conc");

    dxdt[v_index] = I_Ext - I_Na - I_K - I_Leak - I_Syn - I_sahp /*- I_vgcc*/;

  }// function ode_set
}; // class N_SquidAxon_HH1952

} // insilico

#endif
