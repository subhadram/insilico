from mpl_toolkits.axes_grid1 import host_subplot
import mpl_toolkits.axisartist as AA
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
data = np.genfromtxt('se.dat')
#data1 = np.genfromtxt('np10.dat')
matplotlib.rcParams.update({'font.size': 20})
if 1:

    host = host_subplot(111, axes_class=AA.Axes)
    plt.subplots_adjust(right=0.75)

    par1 = host.twinx()
    par2 = host.twinx()

    offset = 60
    new_fixed_axis = par2.get_grid_helper().new_fixed_axis
    par2.axis["right"] = new_fixed_axis(loc="right",
                                        axes=par2,
                                        offset=(offset, 0))
    for item in ([par1.title, par1.xaxis.label, par1.yaxis.label] +
             par1.get_xticklabels() + par1.get_yticklabels()):item.set_fontsize(30)
    par2.axis["right"].toggle(all=True)

    #host.set_xlim(2000, 4500)
    #host.set_ylim(0, 2)

    host.set_xlabel("Time")
    host.set_ylabel("Voltage1")
    par1.set_ylabel("fr")
    par2.set_ylabel("isyn1")

    p1, = host.plot(data[:,0], data[:,1], label="Voltage")
    p2, = par1.plot(data[:,0], data[:,3], label="h")
    p3, = par2.plot(data[:,0], data[:,5], label="m")

    #par1.set_ylim(0, 4)
    #par2.set_ylim(1, 65)

    host.legend()

    host.axis["left"].label.set_color(p1.get_color())
    par1.axis["right"].label.set_color(p2.get_color())
    par2.axis["right"].label.set_color(p3.get_color())

    plt.draw()
    plt.show()
