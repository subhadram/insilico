from mpl_toolkits.axes_grid1 import host_subplot
import mpl_toolkits.axisartist as AA
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
data = np.genfromtxt('switch.dat')
#data1 = np.genfromtxt('np10.dat')
matplotlib.rcParams.update({'font.size': 24})
if 1:

    host = host_subplot(111, axes_class=AA.Axes)
    plt.subplots_adjust(right=0.75)

    par1 = host.twinx()
  
    host.set_xlim(4000,4040)
    #host.set_ylim(0, 2)
    host.locator_params(axis='y', nbins=4)
    host.locator_params(axis='x', nbins=2)
    par1.locator_params(axis='y', nbins=2)
    host.set_xlabel("Time")
    host.set_ylabel("Voltage (mV)")
    par1.set_ylabel("Calcium current (muA/cm^2)")
    #par2.set_ylabel("isyn1")
    par1.locator_params(axis='y', nbins=4)
    par1.locator_params(axis='x', nbins=2)
    p1, = host.plot(data[:,0], data[:,2],)
    p2, = par1.plot(data[:,0], -1.0*data[:,4],linewidth = 2.0)
    #p2, = par1.plot(data[:,0], data[:,3],linewidth = 1.5,label = "h")
    #p2, = par1.plot(data[:,0], data[:,4],linewidth = 1.5,label = "n")
    #p3, = par2.plot(data[:,0], data[:,5], label="m")

    #par1.set_ylim(-100, 10)
    #par2.set_ylim(1, 65)

    host.legend(loc ="best")

    host.axis["left"].label.set_color(p1.get_color())
    par1.axis["right"].label.set_color(p2.get_color())
    #par2.axis["right"].label.set_color(p3.get_color())

    plt.draw()
    plt.show()
