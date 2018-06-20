#ifndef I_SAHP2
#define I_SAHP2

#include "insilico/core/engine.hpp"
#include "random"
namespace insilico {

class I_sahp2 {
 public:

  static void current(state_type &variables, state_type &dxdt, const double t, int index)
 {
    
    double E_sahp  = -77.0;
 
   
    unsigned v1_index = insilico::engine::neuron_index(0, "v");
    unsigned v2_index = insilico::engine::neuron_index(1, "v");
  
    
    unsigned Ca_conc1_index = insilico::engine::neuron_index(0, "Ca_conc");
    unsigned Ca_conc2_index = insilico::engine::neuron_index(1, "Ca_conc");
    
    
    double Ca_conc1 = variables[Ca_conc1_index];
    double Ca_conc2 = variables[Ca_conc2_index];
    double v1 = variables[v1_index];
    double v2 = variables[v2_index];
    
    
    double rb = engine::neuron_value(1, "rb");
    double tstop = engine::neuron_value(1, "tstop");
    double ns = engine::neuron_value(1, "ns");
    double ahp10 = engine::neuron_value(0, "ahp0");
    double ahp11 = engine::neuron_value(0, "ahp1");
    double ahp12 = engine::neuron_value(0, "ahp2");
    double ahp13 = engine::neuron_value(0, "ahp3");
    double ahp14 = engine::neuron_value(0, "ahp4");
    double ahp15 = engine::neuron_value(0, "ahp5");
    double ahp20 = engine::neuron_value(1, "ahp0");
    double ahp21 = engine::neuron_value(1, "ahp1");
    double ahp22 = engine::neuron_value(1, "ahp2");
    double ahp23 = engine::neuron_value(1, "ahp3");
    double ahp24 = engine::neuron_value(1, "ahp4");
    double ahp25 = engine::neuron_value(1, "ahp5");
    double ts2 = engine::neuron_value(1, "ts2");
    
   
    double gahp = 0.4;
    double ru = 0.5E-3;
    double ro = 0.600;
    double rc = 0.400;
   
    double rate[20];
    
 
   
        rate[0] = 4*rb*Ca_conc1*ahp10;
   		rate[1] = 3*rb*Ca_conc1*ahp11+ rate[0];
   		rate[2] = 2*rb*Ca_conc1*ahp12+ rate[1];
   		rate[3] = 1*rb*Ca_conc1*ahp13+ rate[2];
   		rate[4] = ro*ahp14+ rate[3];
   		rate[5] = rc*ahp15+ rate[4];
   		rate[6] = 4*ru*ahp14+ rate[5];
   		rate[7] = 3*ru*ahp13+ rate[6];
   		rate[8] = 2*ru*ahp12+ rate[7];
   		rate[9] = ru*ahp11+ rate[8];
   		rate[10] = 4*rb*Ca_conc2*ahp20+ rate[9];
   		rate[11] = 3*rb*Ca_conc2*ahp21+ rate[10];
   		rate[12] = 2*rb*Ca_conc2*ahp22+ rate[11];
   		rate[13] = 1*rb*Ca_conc2*ahp23+ rate[12];
   		rate[14] = ro*ahp24+ rate[13];
   		rate[15] = rc*ahp25+ rate[14];
   		rate[16] = 4*ru*ahp24+ rate[15];
   		rate[17] = 3*ru*ahp23+ rate[16];
   		rate[18] = 2*ru*ahp22+ rate[17];
   		rate[19] = ru*ahp21+ rate[18];
   		double trate = rate[19];
   		
   		
   			std::random_device rd;
    		std::mt19937_64 gen(rd());
    		std::uniform_real_distribution<double> distribution(/*mean=*/0.0, /*stddev=*/1.0);
   			double rn = distribution(gen);
   			double r = rn * trate;
   	
   		if (r<rate[0]){
   			ahp10 = ahp10-1;
   			ahp11 += 1;}
   			
   		else if (r<rate[1]){
   			ahp11 += -1;
   			ahp12 += 1;}
   			
   		else if (r<rate[2]){
   			ahp12 += -1;
   			ahp13 += 1;}
   			
		else if (r<rate[3]){
   			ahp13 += -1;
   			ahp14 += 1;}
   			
   		else if (r<rate[4]){
   			ahp14 += -1;
   			ahp15 += 1;} 
   			
   		else if (r<rate[5]){
   			ahp15 += -1;
   			ahp14 += 1;}
   			
   		else if (r<rate[6]){
   			ahp14 += -1;
   			ahp13 += 1;}
   			  	
   		else if (r<rate[7]){
   			ahp13 += -1;
   			ahp12 += 1;}
   			
   		else if (r<rate[8]){
   			ahp12 += -1;
   			ahp11 += +1;}
   			
   		else if (r<rate[9]){
   			ahp11 += -1;
   			ahp10 += +1;}
   			 	
         else if (r<rate[10]){
   			ahp20 = ahp20-1;
   			ahp21 += 1;}
   			
   		else if (r<rate[11]){
   			ahp21 += -1;
   			ahp22 += 1;}
   			
   		else if (r<rate[12]){
   			ahp22 += -1;
   			ahp23 += 1;}
   			
		else if (r<rate[13]){
   			ahp23 += -1;
   			ahp24 += 1;}
   			
   		else if (r<rate[14]){
   			ahp24 += -1;
   			ahp25 += 1;} 
   			
   		else if (r<rate[15]){
   			ahp25 += -1;
   			ahp24 += 1;}
   			
   		else if (r<rate[16]){
   			ahp24 += -1;
   			ahp23 += 1;}
   			  	
   		else if (r<rate[17]){
   			ahp23 += -1;
   			ahp22 += 1;}
   			
   		else if (r<rate[18]){
   			ahp22 += -1;
   			ahp21 += +1;}
   			
   		else {
   			ahp21 += -1;
   			ahp20 += +1;} 
   			
   		  if (tstop == ts2){ 	
   		rate[0] = 4*rb*Ca_conc1*ahp10;
   		rate[1] = 3*rb*Ca_conc1*ahp11+ rate[0];
   		rate[2] = 2*rb*Ca_conc1*ahp12+ rate[1];
   		rate[3] = 1*rb*Ca_conc1*ahp13+ rate[2];
   		rate[4] = ro*ahp14+ rate[3];
   		rate[5] = rc*ahp15+ rate[4];
   		rate[6] = 4*ru*ahp14+ rate[5];
   		rate[7] = 3*ru*ahp13+ rate[6];
   		rate[8] = 2*ru*ahp12+ rate[7];
   		rate[9] = ru*ahp11+ rate[8];
   		rate[10] = 4*rb*Ca_conc2*ahp20+ rate[9];
   		rate[11] = 3*rb*Ca_conc2*ahp21+ rate[10];
   		rate[12] = 2*rb*Ca_conc2*ahp22+ rate[11];
   		rate[13] = 1*rb*Ca_conc2*ahp23+ rate[12];
   		rate[14] = ro*ahp24+ rate[13];
   		rate[15] = rc*ahp25+ rate[14];
   		rate[16] = 4*ru*ahp24+ rate[15];
   		rate[17] = 3*ru*ahp23+ rate[16];
   		rate[18] = 2*ru*ahp22+ rate[17];
   		rate[19] = ru*ahp21+ rate[18];
   		 trate = rate[19];
   		std::random_device sd;
    	std::mt19937_64 gn(sd());
    	std::uniform_real_distribution<double> distibution(/*mean=*/0.0, /*stddev=*/1.0);
   		double rN = distibution(gn);
   		double tw =( - log(rN)/trate) ;
   		double tss = ts2 + tw;
   		ts2 = tss;	
 
}
 
  	double open1 = ahp15/ns;
  	double open2 = ahp25/ns;
  
  	double is12 = open1;
  	double is22 = open2;
  		//std::cout << ahp15 << " "<< ts2<< " "<< ahp25 <<  " "<< Ca_conc1 <<std::endl ; 
  	//std::cout << ahp5 << " "<< ahp4 << " "<< ahp3 <<  " "<< J<<std::endl ; 
   double I_sahp12 =   gahp *open1* (v1 - E_sahp);
   double I_sahp22 =   gahp *open2* (v2 - E_sahp);
   insilico::engine::neuron_value(0, "I_sahp2", I_sahp12);
   insilico::engine::neuron_value(0, "open1", open1);
   insilico::engine::neuron_value(0, "ahp0", ahp10);
   insilico::engine::neuron_value(0, "ahp1", ahp11);
   insilico::engine::neuron_value(0, "ahp2", ahp12);
   insilico::engine::neuron_value(0, "ahp3", ahp13);
   insilico::engine::neuron_value(0, "ahp4", ahp14);
   insilico::engine::neuron_value(0, "ahp5", ahp15);
   insilico::engine::neuron_value(0, "ts2", ts2);
   insilico::engine::neuron_value(0, "is2", is12);
   insilico::engine::neuron_value(1, "I_sahp2", I_sahp22);
   insilico::engine::neuron_value(1, "open2", open2);
   insilico::engine::neuron_value(1, "ahp0", ahp20);
   insilico::engine::neuron_value(1, "ahp1", ahp21);
   insilico::engine::neuron_value(1, "ahp2", ahp22);
   insilico::engine::neuron_value(1, "ahp3", ahp23);
   insilico::engine::neuron_value(1, "ahp4", ahp24);
   insilico::engine::neuron_value(1, "ahp5", ahp25);
   insilico::engine::neuron_value(1, "ts2", ts2);
   insilico::engine::neuron_value(1, "is2", is22);
}

    
}; // class I_dxdt[ahp_index]

} // insilico

#endif
