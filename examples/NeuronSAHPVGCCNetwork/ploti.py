from pylab import *

data = genfromtxt('out26.dat')

#plot(data[:,0],data[:,2], label='V')
plot(data[:,0],data[:,6])
xlim (0, 100)
xlabel('t (msec)')
ylabel('fraction of open channels')

legend()
show()
savefig('sahp1.jpg', format='jpg', dpi=150)