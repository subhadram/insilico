
/*
  main.cpp - insilico's example using neuron and synapse for illustrations

  Copyright (C) 2014 Collins Assisi, Collins Assisi Lab, IISER, Pune
  Copyright (C) 2014 Arun Neru, Collins Assisi Lab,
                     IISER, Pune <areinsdel@gmail.com>
  Copyright (C) 2014-2015 Pranav Kulkarni, Collins Assisi Lab,
                          IISER, Pune <pranavcode@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "insilico/core.hpp"

#include "insilico/neuron/helper/spike_list.hpp" //storing spike-list
#include "Neuron_sahp_vgccs.hpp"
#include "I_sahpr.hpp"
#include "S_TanHSynapse.hpp"

#include <boost/numeric/odeint.hpp>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <random>

using namespace boost::numeric::odeint;
using namespace insilico;
using namespace std;


using namespace boost::numeric::odeint;
using namespace insilico;
using namespace std;
int main(int argc, char **argv) {
  //std::cout << "hi1";
  configuration::initialize(argc, argv);
  configuration::observe_delimiter(' ');
  configuration::observe_startrecording(0);
  configuration::observe_header(false);
  configuration::observe_neuron(1,"v");
  //configuration::observe_neuron(0,"v");
  configuration::observe_skipiters(20);
  configuration::observe_neuron(1,"Ca_conc");
  //configuration::observe_neuron(0,"Ca_conc");
  //configuration::observe_neuron(1,"fail");
  //configuration::observe_neuron(1,"fraction_of_open_channels");
  //configuration::observe_neuron(0,"fraction_of_open_channels");
  configuration::observe_neuron(1,"is2");
   //configuration::observe_neuron(0,"is2");
   //configuration::observe_neuron(1,"I_cav");
   //configuration::observe_neuron(1,"I_sahp");
  engine::generate_neuron<Neuron_sahp_vgcc>(2);
  engine::generate_synapse<S_TanHSynapse>(2); 
  engine::spike_list.resize(2);
  
  double tstop = engine::neuron_value(1, "tstop");
  state_type variables = engine::get_variables(); 
  
  while(tstop <=1000000.0){
  	typedef std::vector< double > deriv_type;	
  	unsigned res = variables.size();
	deriv_type det(res); 
	tstop = engine::neuron_value(1, "tstop");
	double ts2 = engine::neuron_value(1, "ts2");
	
	double tw = engine::neuron_value(1, "tw");
	//std::cout << ts2<< "  "<<"1"<< "  "<< tstop<< std::endl;;	
	engine::driver()(variables , det, tstop ) ;	
	//ts2 = engine::neuron_value(1, "ts2");
	//std::cout << ts2<<" "<<  "2"<< std::endl;
	 //std::cout << 1<< " "<<tw<< " "<<ts2 << " " << tstop <<std::endl ; 
	double tdet = 0.01 + tstop;
	double tl = tstop +10.0;
	//std::cout << 2<< " "<<tw<< " "<<ts2 << " " << tstop <<std::endl ; 
    double tt = std::min({ts2,tdet,tl});
	double dt = tt - tstop ;
	//dt = tw;
	//std::cout << tstop<< " "<< tt << " " <<dt<< std::endl ;
  for(unsigned i=0 ; i < variables.size() ; ++i) {
			variables[i] += dt * det[i];
		
		}
		
		tstop += dt;
		 insilico::engine::neuron_value(1, "dt", dt);
		  insilico::engine::neuron_value(1, "tstop", tstop);
		I_sahp2::current(variables, det, tstop, 1);
		ts2 = engine::neuron_value(1, "ts2");
		//std::cout << ts2<<" "<<  "2"<< std::endl;
		  insilico::engine::neuron_value(1, "dt", dt);
		  insilico::engine::neuron_value(1, "tstop", tstop);
		  //insilico::engine::neuron_value(1, "tw", tw);
		//std::cout << tstop<< " "<< dt << std::endl ;
		// std::cout << 2<< " "<<tw<< " "<<ts2 << " " << tstop <<std::endl ; 
		 //std::cout << tstop;	
		configuration::observer()(variables,tstop);
  }            
  configuration::finalize();
 
}
