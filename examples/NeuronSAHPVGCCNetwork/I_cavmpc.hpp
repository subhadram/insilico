#ifndef INCLUDED_I_CAV2
#define INCLUDED_I_CAV2

#include "insilico/core/engine.hpp"
#include "math.h" 
namespace insilico {

class I_cav2 {
 public:
  static void current(state_type &variables, state_type &dxdt, const double t, const unsigned index)
 {
    double G_cav =  1.5, E_cav = 25,tau = 2.5;
    unsigned v_index = insilico::engine::neuron_index(index, "v");
     unsigned K_index = engine::neuron_index(index, "K");
    double v = variables[v_index];
    double nc = engine::neuron_value(index, "nc");
    double rt = engine::neuron_value(index, "rt");
    double ts2 = engine::neuron_value(index, "ts2");
    double s0 = engine::neuron_value(index, "s0");
    double s1 = engine::neuron_value(index, "s1");
    double s2 = engine::neuron_value(index, "s2");
    //double dt = engine::neuron_value(index, "dt");
    double tq = engine::neuron_value(index, "tq");
    //double c = engine::neuron_value(index, "c");
    
    double tw = engine::neuron_value(index, "tw");
   
    double fail = engine::neuron_value(index, "fail");
    double xi = 1.0/(1 + exp(-(v+30.0)/6.0));
    double a = sqrt(xi)/tau;
    double b = (1- sqrt(xi))/tau;
	double fraction_of_open_channel = (s2/(nc));
	  if (tq < t){
  	fail = 1.0;
  }
  
 if (t> tq+10){
  if (fail == 1.0){
  	if (v > -10){
  	
  		std::random_device sd;
    	std::mt19937_64 gn(sd());
    	std::uniform_real_distribution<double> distibution(0.0, 1.0);
   		double sn = distibution(gn);
   		if (sn < rt){
   			fail = 0.0;
   			//c = c +1;
   			}
   			tq = t +10;
   	}
 }
}   

	double I_cav2 =  G_cav * fraction_of_open_channel * (v - E_cav)*fail;   
       double K = variables[K_index];
        if (K ==0){
 		ts2 = 0.0;}
 	dxdt[K_index] = 1; 
    double rate[4];
 if ( t == ts2 )
    //std::cout << ahp5 << " "<< ahp4 << " "<< ahp1 << std::endl ; 
    {   ts2 = t;
        rate[0] = 2*a*s0;
   		rate[1] = a*s1 + rate[0];
   		rate[2] = 2*b*s2 + rate[1];
   		rate[3] = b*s1 + rate[2];
   		double trate = rate[3];
   		std::random_device sd;
    	std::mt19937_64 gn(sd());
    	std::uniform_real_distribution<double> distibution(/*mean=*/0.0, /*stddev=*/1.0);
   		double rN = distibution(gn);
   		//double tw =roundf(( - log(rN)/trate)*100)/100 ;
   		tw =( - log(rN)/trate) ;
   		//ts22 = t;
   		double tss = ts2 + tw;
   		ts2 = tss;
   		//std::cout << tw << " "<< s2 << std::endl ;
   		//if  (ts2 < t+dt){
   			std::random_device rd;
    		std::mt19937_64 gen(rd());
    		std::uniform_real_distribution<double> distribution(/*mean=*/0.0, /*stddev=*/1.0);
   			double rn = distribution(gen);
   			double r = rn * trate;
   			//std::cout << rate[1] << " "<< r << std::endl ;
   		if (r<rate[0]){
   			s0 = s0-1;
   			s1 += 1;}
   			
   		else if (r<rate[1]){
   			s1 += -1;
   			s2 += 1;}
   			
   		else if (r<rate[2]){
   			s2 += -1;
   			s1 += 1;}
   			
		else{
   			s1 += -1;
   			s0 += 1;
   		 	
         } 	
          
   }
   
   		
  //}
  
 

 //std::cout << c<< " "<< t << std::endl ;
// std::cout << tq<<" "<< fail  <<std::endl ;
    //double fraction_of_open_channel = (s2/(nc));
   double il2 = fraction_of_open_channel;
    //double I_cav2 =  G_cav * fraction_of_open_channel * (v - E_cav);
    //double I_cav2 =  G_cav * fraction_of_open_channel * (v - E_cav)*fail;
   // insilico::engine::neuron_value(index, "fraction_of_open_channel", fraction_of_open_channel);
    insilico::engine::neuron_value(index, "s0", s0);
    insilico::engine::neuron_value(index, "s1", s1);
    insilico::engine::neuron_value(index, "s2", s2);
    insilico::engine::neuron_value(index, "ts2", ts2);
    insilico::engine::neuron_value(index, "tq", tq);
    insilico::engine::neuron_value(index, "fail", fail);
    insilico::engine::neuron_value(index, "I_cav2", I_cav2);
    insilico::engine::neuron_value(index, "il2", il2);
    insilico::engine::neuron_value(index, "tw", tw);
    
  } // function current
}; // class I_CAV

} // insilico

#endif
