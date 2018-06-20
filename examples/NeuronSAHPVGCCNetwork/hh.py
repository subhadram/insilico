import numpy as np
import math as mt
import matplotlib.pyplot as plt
from scipy.integrate import odeint
from pylab import *

matplotlib.rcParams.update({'font.size': 24})
locator_params(axis='y', nbins=4)
locator_params(axis='x', nbins=4)
v = np.arange(-110.0,110.0,0.2)
ymin = []
ymax = []
#a = 0.0
def deriv(y, t,s,v):
	m2 = y[0]
	h2 = y[1]
	n2 = y[2]
	a_m = (0.1*(v+40.0))/(1 - (mt.exp(-0.1*(v+40.0))))
	b_m  = 4.0*mt.exp(-(v+65.0) /18.0)
	a_h = 0.07*mt.exp(-(v+65.0) / 20.0)
	b_h  = 1.0/(1.0 + mt.exp(-0.1 * (v+35.0)))
	a_n = (0.01 * (v+55.0))/(1.0 - (mt.exp(-0.1*(v+55.0))));
	b_n = 0.125*mt.exp(-(v+65.0) / 80.0);
	hm=(a_m*(1.0-m2)-b_m*m2)
	hh=(a_h*(1.0-h2)-b_h*h2)
	hn=(a_n*(1.0 - n2)-b_n * n2)
	return [hm,hh,hn]
"""
def deriv(y, t,s,v):
	m = y[0]
	h = y[1]
	n = y[2]
	alpha_m = (2.5-(0.1 * (v)))/(mt.exp(2.5-(0.1 * (v)))-1.0)
	beta_m  = 4.0*mt.exp(-(v) /18.0)
	alpha_h = 0.07*mt.exp(-(v) / 20.0)
	beta_h  = 1.0/(mt.exp(3.0-(0.1 * (v)))+1)
	alpha_n = (0.1-(0.01 * (v)))/(mt.exp(1.0-(0.1 * (v)))-1.0)
	beta_n = 0.125*mt.exp(-(v) / 80.0)
	dm=(alpha_m*(1.0-m)-beta_m*m)
	dh=(alpha_h*(1.0-h)-beta_h*h)
	dn=(alpha_n*(1.0 - n)-beta_n * n)
	return [dm,dh,dn]
"""
i = 0
be = []
mmm = []
nnn = []
hhh = []
m1 = []
h1 = []
n1 = []
for f in v:
	time = np.arange(0.0, 100.0,0.01)
	yinit = np.array([0.1,.01,.1])
	pars = (0,f)
	y = odeint(deriv, yinit, time, pars)
	#plt.plot(time,y[:,0], label = f)
	mmm.append(y[-1,0])
	hhh.append(y[-1,1])
	nnn.append(y[-1,2])
	be.append(f)
	#print f,mmm, "**********"
		

	


mmm = np.array(mmm)
hhh = np.array(hhh)
nnn = np.array(nnn)
be = np.array(be)
    
"""
b = 1.2
for x in np.linspace(0.0,8,40):
	time = np.arange(0.0, 2000,0.01)
	yinit = np.array([x,2.0])
	y = odeint(deriv,yinit,time, args=(b,))
	plt.plot(y[:,0],y[:,1])
	
"""	


plt.plot(be, mmm, label = "m", linewidth = 2.0)
#plt.plot(be, m1, label = "hh m")
plt.plot(be, hhh, label = "h",linewidth = 2.0)
plt.plot(be, nnn, label = "n",linewidth = 2.0)
#plt.plot(be, n1, label = "hh n")

#plt.plot(be, h1, label = "hh h")

#plt.plot(b, ymax[:,0], label = "Voltage maximum",color = 'blue')
#plt.plot(b, ymin[:,1], 'b')
#plt.plot(b, ymax[:,1], 'b')
plt.xlim(-110,110)
plt.xlabel('V (mV)' ,fontsize = 24)
plt.ylabel('x(V)' ,fontsize = 24)
plt.legend(loc = "best", fontsize = 20)
#plt.title("Neuron models gk and hh" ,fontsize = 18) 
plt.hold
plt.show()

