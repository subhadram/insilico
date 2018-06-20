from __future__ import division
import numpy as np
import matplotlib.pyplot as plt
from pylab import *
#import numpy as np
from matplotlib import pyplot

matplotlib.rcParams.update({'font.size': 24})
locator_params(axis='y', nbins=3)
locator_params(axis='x', nbins=4)
# Get peak of data and store it in file
data = genfromtxt('ccc.dat')
t = np.array(data[:,1])
sp = np.fft.fft(t)
#freq = np.fft.fftfreq(t.shape[-1])
#data = np.random.rand(301) - 0.5
ps = np.abs(np.fft.fft(t))**2

#time_step = 1 / 30
freq = np.fft.fftfreq(t.size)
freq = 1000.0*freq
idx = np.argsort(freq)

plt.plot(freq[idx], ps[idx])
"""
dat = genfromtxt('f01.dat')
tt = np.array(dat[:,1])
spa = np.fft.fft(tt)
#freqs = np.fft.fftfreq(tt.shape[-1])
#data = np.random.rand(301) - 0.5
psa = np.abs(np.fft.fft(tt))**2

#time_step = 1 / 30
freqs = np.fft.fftfreq(t.size)
freqs = 1000.0*freqs
idy = np.argsort(freqs)

plt.plot(freqs[idy], psa[idy])
"""
plt.show()

