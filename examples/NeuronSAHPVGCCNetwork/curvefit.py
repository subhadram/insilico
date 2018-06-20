import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from pylab import *
import matplotlib
#data = np.genfromtxt('sp10.dat')
matplotlib.rcParams.update({'font.size': 20})
data = genfromtxt('ourn.dat')
#data1 = genfromtxt('bf300.dat')
#data2 = genfromtxt('bf1000.dat')

def func(x, a, b, c):
    return a * np.exp(-b * x) + c

# define the data to be fit with some noise

xdata = data[:,0]
#y = func(xdata, 2.5, 1.3, 0.5)
#y_noise = 0.2 * np.random.normal(size=xdata.size)
ydata = data[:,4]
plt.plot(xdata, ydata, 'b-', label='data')

# Fit for the parameters a, b, c of the function `func`

popt, pcov = curve_fit(func, xdata, ydata)
plt.plot(xdata, func(xdata, *popt), 'r-', label='fit')

# Constrain the optimization to the region of ``0 < a < 3``, ``0 < b < 2``
# and ``0 < c < 1``:

popt, pcov = curve_fit(func, xdata, ydata, bounds=(0, [3., 2., 1.]))
plt.plot(xdata, func(xdata, *popt), 'g--', label='fit-with-bounds')

plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.show()
