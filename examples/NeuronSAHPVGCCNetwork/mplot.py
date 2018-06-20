import numpy as np
import matplotlib.pyplot as plt
from pylab import *
data = genfromtxt('det.dat')
matplotlib.rcParams.update({'font.size': 20})
fig, ax1 = plt.subplots()
t = data[:,0]
s1 = data[:,1]
locator_params(axis='y', nbins=4)
locator_params(axis='x', nbins=4)
ax1.plot(t, s1, 'b-')
ax1.set_xlabel('time (msec)')
ax1.set_xlim(0,100)
ax1.set_ylim(-80,50)
# Make the y-axis label and tick labels match the line color.
ax1.set_ylabel('Voltage (mV)', color='b')
for tl in ax1.get_yticklabels():
    tl.set_color('b')


ax2 = ax1.twinx()
s2 = data[:,3]
ax2.plot(t, s2,color='green',lw =2)
ax2.set_xlim(300,650)
locator_params(axis='y', nbins=4)
locator_params(axis='x', nbins=4)
#ax2.set_ylim(0.21,0.24)
ax2.set_ylabel('I_cav', color='green')
for tl in ax2.get_yticklabels():
    tl.set_color('g')
plt.show()
