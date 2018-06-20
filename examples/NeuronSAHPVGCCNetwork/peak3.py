from pylab import *
import numpy as np
from matplotlib import pyplot


# Get peak of data and store it in file
#data = genfromtxt('/media/subhadra/b8f700e2-a56b-4e3c-ba5d-d4a7ab6f5d56/centos6.3/arun/Subhadra/our.dat')
#data1 = genfromtxt('/media/subhadra/b8f700e2-a56b-4e3c-ba5d-d4a7ab6f5d56/centos6.3/arun/Subhadra/cw.dat')

data = genfromtxt('df.dat')
data1 = genfromtxt('df2.dat')
#data2 = genfromtxt('u1000.dat')

#v1 = data[:,1]
#v2 = data[:,2]
#t = data[:,0]
ca1 = data[:,3]
ca2 = data1[:,3]
#of1 = data[:,7]
#of2 = data1[:,5]
#c1 =  data[:,5]
#c2 =  data1[:,7]


#tw = list(set(tw))
#tw1 = list(set(tw1))
#tw2 = list(set(tw2))
#tww = np.array(tw)
#tww1 = np.array(tw1)
#tww2 = np.array(tw2)
dt = []
for i in range(1,len(data)-1):
    if (((data[i,1]>data[i-1,1])&(data[i,1]>data[i+1,1]))&(data[i,1]>0.1)):
        dt.append(data[i,0])
        
dt = np.array(dt)
ds = []

for i in range(1,len(data1)-1):
    if (((data1[i,1]>data1[i-1,1])&(data1[i,1]>data1[i+1,1]))&(data1[i,1]>0.1)):
        ds.append(data1[i,0])
        
tt = []
ts = []
ds = np.array(ds)
print len(ds)
print len(dt)
"""
for i in range(1,len(dt)-3):
	if ((dt[i+1] - dt[i])> 40.0):
		tt.append((dt[i+1] - dt[i]))  
		
for i in range(1,len(ds)-3):
	if ((ds[i+1] - ds[i])> 40.0):
		ts.append((ds[i+1] - ds[i]))  
		
   
        
ts = np.array(ts[:36])
tt = np.array(tt[:36])
ca1 = np.array(tt)
ca2 = np.array(ts)
ca1m = np.mean(tt)
ca2m = np.mean(ts)
ca1s = np.std(tt)
ca2s = np.std(ts)
ca1c = ca1s/ca1m
ca2c = ca2s/ca2m
print len(tt), len(ts)
print ca1m,ca1s,ca1c
print ca2m,ca2s,ca2c
"""
