#ifndef INCLUDED_I_CAV2
#define INCLUDED_I_CAV2

#include "insilico/core/engine.hpp"
#include "math.h" 
namespace insilico {

class I_cav2 {
 public:
  static void current(state_type &variables, state_type &dxdt, const double t, const unsigned index)
 {
    double G_cav =  0.15, E_cav = 25,tau = 2.5;
    //unsigned v1_index = insilico::engine::neuron_index(0, "v");
    //unsigned v2_index = insilico::engine::neuron_index(1, "v");
    // unsigned K_index = engine::neuron_index(index, "K");
    unsigned v1_index = insilico::engine::neuron_index(0, "v");
    unsigned v2_index = insilico::engine::neuron_index(1, "v");
    double v1 = variables[v1_index];
    double v2 = variables[v2_index];
    double nc = engine::neuron_value(0, "nc");
    double rt = engine::neuron_value(0, "rt");
    double ts2 = engine::neuron_value(1, "ts2");
    double s10 = engine::neuron_value(0, "s0");
     double s20 = engine::neuron_value(1, "s0");
     double tw = engine::neuron_value(1, "tw");
     //double tw = engine::neuron_value(1, "tw");
    double s11 = engine::neuron_value(0, "s1");
     double s21 = engine::neuron_value(1, "s1");
    double s12 = engine::neuron_value(0, "s2");
    double s22 = engine::neuron_value(1, "s2");
    double tstop = engine::neuron_value(1, "tstop");
	//double fraction_of_open_channel1 = ((nc));
	//double fraction_of_open_channel2 = ((nc));
	//v1 = -65.0;
	 //v2 = -65.0;
	double x1i = 1.0/(1.0 + exp(-(v1+30.0)/6.0));
    double a1 = sqrt(x1i)/tau;
    double b1 = (1.0- sqrt(x1i))/tau;
    double x2i = 1.0/(1.0 + exp(-(v2+30.0)/6.0));
    double a2 = sqrt(x2i)/tau;
    double b2 = (1.0- sqrt(x2i))/tau;


	double rate[8];
	 
 //if ( t == ts2 ){
// if  (tstop == ts2){
    //std::cout << v1 << " "<< s12 << " "<< v2 << std::endl ; 
   	 	  
        rate[0] = 2*a1*s10;
   		rate[1] = a1*s11 + rate[0];
   		rate[2] = 2*b1*s12 + rate[1];
   		rate[3] = b1*s11 + rate[2];
   		rate[4] = 2*a2*s20 + rate[3];
   		rate[5] = a2*s21 + rate[4];
   		rate[6] = 2*b2*s22 + rate[5];
   		rate[7] = b2*s21 + rate[6];
   		double trate = rate[7];
   		std::random_device sd;
    	std::mt19937_64 gn(sd());
    	std::uniform_real_distribution<double> distibution(/*mean=*/0.0, /*stddev=*/1.0);
   		double rn = distibution(gn);
   		double r = rn * trate;
   		//double tw =roundf(( - log(rN)/trate)*100)/100 ;
   		
   		if (r<rate[0]){
   			s10 = s10-1;
   			s11 += 1;}
   			
   		else if (r<rate[1]){
   			s11 += -1;
   			s12 += 1;}
   			
   		else if (r<rate[2]){
   			s12 += -1;
   			s11 += 1;}
   			
		else if (r<rate[3]){
   			s11 += -1;
   			s10 += 1;}
   			
   		else if (r<rate[4]){
   			s20 += -1;
   			s21 += 1;}
   			
   		else if (r<rate[5]){
   			s21 += -1;
   			s22 += 1;}
   			
   		else if (r<rate[6]){
   			s22 += -1;
   			s21 += 1;}
   			
   		else{
   			s21 += -1;
   			s20 += 1;}
   		// }	
   		
   		
   		//}
   	//std::cout << tw << " "<< s2 << std::endl ;
    
			if (ts2 == tstop){ 
   		   	x1i = 1.0/(1.0 + exp(-(v1+30.0)/6.0));
    	   	a1 = sqrt(x1i)/tau;
    	   	b1 = (1.0- sqrt(x1i))/tau;
    		x2i = 1.0/(1.0 + exp(-(v2+30.0)/6.0));
    		a2 = sqrt(x2i)/tau;
    		b2 = (1.0- sqrt(x2i))/tau;
    		rate[0] = 2*a1*s10;
   			rate[1] = a1*s11 + rate[0];
   			rate[2] = 2*b1*s12 + rate[1];
   			rate[3] = b1*s11 + rate[2];
   			rate[4] = 2*a2*s20 + rate[3];
   			rate[5] = a2*s21 + rate[4];
   			rate[6] = 2*b2*s22 + rate[5];
   			rate[7] = b2*s21 + rate[6];
   			trate = rate[7];
   			std::random_device rd;
    		std::mt19937_64 gen(rd());
    		std::uniform_real_distribution<double> distribution(/*mean=*/0.0, /*stddev=*/1.0);
   			double rN = distribution(gen);
   			
   			tw =( - log(rN)/trate) ;
   		//ts22 = t;
   		//double tm = tw;
   		double tss = ts2 + tw;
   		ts2 = tstop + tw;
   		   //insilico::engine::neuron_value(1, "tw", tm);
    //insilico::engine::neuron_value(0, "tw", tm);
        //insilico::engine::neuron_value(0, "ts2", ts2);
    //insilico::engine::neuron_value(1, "ts2", ts2);
 
   			
 }
 //double tm = tw;
  		   insilico::engine::neuron_value(1, "tw", tw);
    insilico::engine::neuron_value(0, "tw", tw);
        insilico::engine::neuron_value(0, "ts2", ts2);
    insilico::engine::neuron_value(1, "ts2", ts2);
 
 
     		// std::cout << 3<< " "<<tw<< " "<<ts2 << " " << tstop <<" " << v2 <<" "<< s22 <<std::endl ;  	    	 	
      //std::cout << ts2<< " "<< std::endl ;   
   //std::cout << s20<< " "<< s21 << " "<< s22 <<" "<<v1<< std::endl ;
    double fraction_of_open_channel1 = ((s12/nc));
	double fraction_of_open_channel2 = ((s22/nc));
   
   double il22 = fraction_of_open_channel2;
   double il12 = fraction_of_open_channel1;
    //double I_cav2 =  G_cav * fraction_of_open_channel * (v - E_cav);
    double I_cav12 =  G_cav * fraction_of_open_channel1 * (v1 - E_cav);
    double I_cav22 =  G_cav * fraction_of_open_channel2 * (v2 - E_cav);
    
   // insilico::engine::neuron_value(index, "fraction_of_open_channel", fraction_of_open_channel);
    insilico::engine::neuron_value(0, "s0", s10);
    insilico::engine::neuron_value(0, "s1", s11);
    insilico::engine::neuron_value(0, "s2", s12);
    //insilico::engine::neuron_value(0, "ts2", ts2);
    //insilico::engine::neuron_value(1, "ts2", ts2);
    //insilico::engine::neuron_value(0, "tq", tq);
    //insilico::engine::neuron_value(index, "fail1", fail);
    insilico::engine::neuron_value(0, "I_cav2", I_cav12);
    insilico::engine::neuron_value(0, "il2", il12);
    //insilico::engine::neuron_value(1, "tw", tw);
    //insilico::engine::neuron_value(0, "tw", tw);
        insilico::engine::neuron_value(1, "s0", s20);
    insilico::engine::neuron_value(1, "s1", s21);
    insilico::engine::neuron_value(1, "s2", s22);
    //nsilico::engine::neuron_value(1, "tq", tq);
    //insilico::engine::neuron_value(1, "fail2", fail);
    insilico::engine::neuron_value(1, "I_cav2", I_cav22);
    insilico::engine::neuron_value(1, "il2", il22);
    //insilico::engine::neuron_value(index, "tw", tw);
    
  } // function current
       
                                                          
}; // class I_CAV

} // insilico

#endif
