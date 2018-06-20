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
	S0 = y[0]
	S1 = y[1]
	S2 = y[2]
	Ca_conc = y[3]
	xi = 1.0/(1.0 + mt.exp(-(v+30.0)/6.0))
	tau = 2.5
	E_cav = 25.0
	gc = .15
	al = 0.0002
	a = mt.sqrt(xi)/tau
	I_cav = gc*(S2/(S0+S1+S2))*(v - E_cav)
	b = (1.0- mt.sqrt(xi))/tau
	ds0 = (-2*a*S0) + (b*S1)
	ds1 = (-b*S1)+(-a*S1)+(2*a*S0)+(2*b*S2)
	ds2 = (a*S1) - (2*b*S2)
	ds3 = (-1.0*I_cav*al) - (Ca_conc)/14.0
	return [ds0,ds1,ds2,ds3]

i = 0
be = []
ca = []
for f in v:
	time = np.arange(0.0, 100,0.01)
	yinit = np.array([0.1,0.5,0.4,0.0])
	pars = (0,f)
	y = odeint(deriv, yinit, time, pars)
	z = (y[:,2]/(y[:,0]+y[:,1]+y[:,2]))
	w = y[:,3]
	#plt.plot(time,w, label = f)
	#plt.plot(time,z, label = f)
	ymin.append(z[-1])
	ca.append(w[-1])
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
#plt.plot(be, ca,linewidth = 2.0)
plt.xlim(-70,70)
#plt.plot(b, ymax[:,0], label = "Voltage maximum",color = 'blue')
#plt.plot(b, ymin[:,1], 'b')
#plt.plot(b, ymax[:,1], 'b')
plt.xlabel('V (mV)' ,fontsize = 24)
plt.ylabel('fraction of open calcium channels' ,fontsize = 24)
plt.legend(loc = "best")
#plt.title("Synaptic activation" ,fontsize = 20) 
plt.hold
plt.show()

