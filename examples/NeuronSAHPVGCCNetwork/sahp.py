import numpy as np
import math as mt
import matplotlib.pyplot as plt
from scipy.integrate import odeint
from pylab import *
x = np.arange(-6,1,0.1)
Ca_conc = np.power(10.0, x)
#Ca_conc = np.arange(0.0,0.002,0.00001)
print Ca_conc

ymin = []
ymax = []
#a = 0.0
matplotlib.rcParams.update({'font.size': 24})
locator_params(axis='y', nbins=4)
locator_params(axis='x', nbins=1)
def deriv(y, t,s,Ca_conc):
	R = y[0]
	CA1R = y[1]
	CA2R = y[2]
	CA3R = y[3]
	CA4R = y[4]
	O = y[5]
	rb = 4.0
	ru = 0.0005
	ro = 0.6
	rc = 0.4
	dR = (ru*CA1R) - (4.0*rb*R*Ca_conc); 
	dCA1R = (4.0*rb*R*Ca_conc) - (ru*CA1R) + (2.0*ru*CA2R) - (3.0*rb*Ca_conc*CA1R);
	dCA2R = (3.0*rb*CA1R*Ca_conc) - (2.0*ru*CA2R) + (3.0*ru*CA3R) - (2.0*rb*CA2R*Ca_conc);
	dCA3R = (2.0*rb*CA2R*Ca_conc) - (3.0*ru*CA3R) + (4.0*ru*CA4R) - (rb*CA3R*Ca_conc);
	dCA4R = (rb*CA3R*Ca_conc) - (4.0*ru*CA4R) + (rc*O) - (ro*CA4R);
	dO = (ro*CA4R) - (rc*O);
	return [dR,dCA1R,dCA2R,dCA3R,dCA4R,dO]

i = 0
be = []
for f in Ca_conc:
	time = np.arange(0.0, 20000,0.01)
	yinit = np.array([0.1, 0.1, 0.1,0.1,0.3,0.3])
	pars = (0,f)
	y = odeint(deriv, yinit, time, pars)
	#plt.plot(time,y[:,5], label = f)
	z = (y[:,5]/(y[:,0]+y[:,1]+y[:,2]+y[:,3]+y[:,4]+y[:,5]))
	#plt.plot(time,z, label = f)
	ymin.append(z[-1])
	be.append(f)
	#print f,ee		

	

ymin = np.array(ymin)
be = np.array(be)
"""   
b = 1.2
for x in np.linspace(0.0,8,40):
	time = np.arange(0.0, 2000,0.01)
	yinit = np.array([x,2.0])
	y = odeint(deriv,yinit,time, args=(b,))
	plt.plot(y[:,0],y[:,1])
	
"""


plt.plot(be, ymin,linewidth = 2.0)
#plt.plot(b, ymax[:,0], label = "Voltage maximum",color = 'blue')
#plt.plot(b, ymin[:,1], 'b')
#plt.plot(b, ymax[:,1], 'b')
plt.xscale('log')
plt.xlabel('Ca_Conc mM' ,fontsize = 24)
plt.ylabel('Open fraction of sAHP ' ,fontsize = 24)
plt.legend()
#plt.title("Activation of ahp" ,fontsize = 20) 
plt.hold
plt.show()
