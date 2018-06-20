import numpy as np
import math as mt
import matplotlib.pyplot as plt
from scipy.integrate import odeint
from pylab import *

matplotlib.rcParams.update({'font.size': 24})
locator_params(axis='y', nbins=4)
locator_params(axis='x', nbins=4)
v = np.arange(-70.0,70.0,1.0)
ymin = []
ymax = []
#a = 0.0

def deriv(y, t,s,v):
	s = y[0]
	rho = (1.0 + mt.tanh(v/4.0))/2.0
	ds = (rho/0.3)*(1.0 - s) - (1.0/8.9)*s
	return [ds]

i = 0
be = []
for f in v:
	time = np.arange(0.0, 100,0.01)
	yinit = np.array([0.3])
	pars = (0,f)
	y = odeint(deriv, yinit, time, pars)
	z = (y[:,0])
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
plt.xlim(-70,70)
#plt.plot(b, ymax[:,0], label = "Voltage maximum",color = 'blue')
#plt.plot(b, ymin[:,1], 'b')
#plt.plot(b, ymax[:,1], 'b')
plt.xlabel('V (mV)' ,fontsize = 24)
plt.ylabel('s (synaptic gating variable)' ,fontsize = 24)
plt.legend()
#plt.title("Synaptic activation" ,fontsize = 20) 
plt.hold
plt.show()

