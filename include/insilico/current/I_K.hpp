#ifndef INCLUDED_I_K
#define INCLUDED_I_K

#include "insilico/core/engine.hpp"

namespace insilico {

class I_K {
 public:
  static void current(state_type &variables, state_type &dxdt, const double t, int index) {
    double gk = 36.0, ek = -77.0;

    int v_index = engine::neuron_index(index, "v");
    int n_index = engine::neuron_index(index, "n");

    double v = variables[v_index];
    double n = variables[n_index];

    double alpha_n = (0.01*(v+55.0))/(1.0-(exp(-(v+55.0)/10.0)));
    double beta_n = 0.125*exp(-(v+65.0 / 80.0));

    // ODE set
    dxdt[n_index]=(alpha_n*(1 - n)-beta_n * n);

    // Current
    engine::neuron_value(index, "I_K", (gk * pow(n,4) * (v - ek)));

  } // function current
}; // class I_K

} // insilico

#endif
