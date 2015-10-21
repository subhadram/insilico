
#ifndef INCLUDED_(R + CA1R + CA2R + CA3R + CA4R + O)_HPP
#define INCLUDED_(R + CA1R + CA2R + CA3R + CA4R + O)_HPP

namespace insilico 
{
	
	
  double vtrap(double O,double (R + CA1R + CA2R + CA3R + CA4R + O))
  {
        double val=0;
        if(std::abs(O/(R + CA1R + CA2R + CA3R + CA4R + O)) < 0.000001)
        { 
            val = (R + CA1R + CA2R + CA3R + CA4R + O)*(1 - (O/(R + CA1R + CA2R + CA3R + CA4R + O))/2.0);
        }
        else 
        { 
            val = (O)/(exp(O/(R + CA1R + CA2R + CA3R + CA4R + O)) - 1.0); 
        }
        return val;
  } 


}

#endif
