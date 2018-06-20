from pylab import *
import numpy as np
from matplotlib import pyplot

matplotlib.rcParams.update({'font.size': 24})
locator_params(axis='y', nbins=3)
locator_params(axis='x', nbins=4)
# Get peak of data and store it in file
dat = genfromtxt('ccc.dat')
#dat = genfromtxt('0.dat')
data = dat[5000:]

tt = []
dt1 = []
dt2 = []
ls = 0.0
ps = 0.0
for i in range(1,len(data)-1):
	ls = ps
	if ((data[i,1]>20.0)):
		ps = data[i,0]
	if ((ps - ls)>0.5):
		tt.append(data[i,:])
        
tt = np.array(tt)

for j in range(2,len(tt)):
	x = float(tt[j,0]) - float(tt[j-1,0])
	y = float(tt[j-1,0]) - float(tt[j-2,0])
	#print tt[i]
	if x > 2*y :
		#print x
		dt1.append(tt[j,:])
		dt2.append(tt[j-1,:])
    		
print tt
dt1 = np.array(dt1)
dt2 = np.array(dt2)
plot(data[:,0],data[:,1],label = 'Voltage')
plot(tt[:,0],tt[:,1],'ro',label = 'Inter-spike interval')
plot(dt2[:,0],dt2[:,1],'go',label = 'Inter-burst interval')
plot(dt1[:,0],dt1[:,1],'go')
xlim(1000,5000)
ylim(-100,100)
xlabel("Time (msec)")
ylabel("Voltage (mV)")
#plot(dt1[:,0],dt1[:,1],'go',label = 'Peak')
legend(loc='best',fontsize = 20)
show()
"""
# Save peak time to file
#tt = tt[:,3] 
#print tt[5]
np.savetxt('dt.dat', tt, fmt='%.3f')


# Time difference 
#tt = genfromtxt('noise0_tt.dat')
g = np.mean(tt)
print g

dt = []
for j in range(1,len(tt)):
	x = float(tt[j]) - float(tt[j-1])
	#print tt[i]
	if x > 50.0 :
		#print x
		dt.append(x)
    		
    		
    		
#print dt		
    		
dt = np.array(dt)


np.savetxt('switchdt.dat', dt, fmt='%.2f')
meen = np.mean(dt)
vari = np.var(dt)
print meen ,vari


th = genfromtxt('dt.dat')
dh = []
for i in range(1,len(th)):
    dh.append(th[i]-th[i-1])

mn = np.mean(dh)
st = np.std(dh)
    
ts = genfromtxt('5.dat')
ds = []
for i in range(1,len(ts)):
    ds.append(ts[i]-ts[i-1])
    
mn1 = np.mean(ds)
st1 = np.std(ds)

print mn,st
print mn1,st1
  
tu = genfromtxt('1.dat')
du = []
for i in range(1,len(tu)):
    du.append(tu[i]-tu[i-1])
  
tt = genfromtxt('detf.dat')
dt = []
for i in range(1,len(tu)):
    dt.append(tt[i]-tt[i-1])

binBoundaries = np.linspace(0,250,100)
# Histogram of time difference
#n, bins, patches = pyplot.hist(dt, log = True, alpha = 0.3, bins = binBoundaries, facecolor='k',label = "Infinity")
n, bins, patches = pyplot.hist(dh, log = False, alpha = 0.3, bins = binBoundaries, facecolor='r',label = "N = 1000")
n, bins, patches = pyplot.hist(ds, log = False, alpha = 0.3, bins = binBoundaries, facecolor='b',label = "N = 800")
n, bins, patches = pyplot.hist(du, log = True, alpha = 0.3, bins = binBoundaries, facecolor='g',label = "N = 400")
pyplot.legend(loc='upper right')
pyplot.ylabel("#Counts")
pyplot.xlabel("Time difference in consecutive action potentials(msec)")
#plt.hist(numpy.log2(data), log=True, bins=bins)
#freq, bins = np.histogram(ValList,bins)
#dat = zip(*np.histogram(dt,50))
#np.savetxt('hist40.dat', dat, delimiter=' ')
#legend("0.4")
#ylim (1,50)
#xlim (700, 1300)
"""
#plot(range(len(tt)), dt, '.')
#plt.yscale('log')
show()
#savefig('peaks.jpg', format='jpg', dpi=150)
