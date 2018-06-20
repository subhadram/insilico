#!/usr/bin/python
#PBS -J 1-239:1
#PBS -p 1023
import os
import sys
import json
import numpy as np
from pylab import *
import matplotlib

""""
pbs_ar_ind =int(os.getenv("PBS_ARRAY_INDEX"))
#par_dic = json.load(open("param_dict.txt"))
par_dic = json.load(open("/home/subhadra/subhadra/param_sup_np.txt"))
#outfile = open('/home/subhadra/subhadra/hope.dat', 'a')

l_pars = par_dic[str(pbs_ar_ind)]
ampn = l_pars[0]
iext = l_pars[1]
gl = l_pars[2]
trial = l_pars[3]
AMPN = str(ampn)
TRIAL = str(trial)	
IEXT = str(iext)
GL = str(gl)
"""
# Get peak of data and store it in file
data = np.genfromtxt('cwdt2.dat')
data1 = np.genfromtxt('cw2.dat')
tt = []
xx = 0.0
our = np.cumsum(data[:,5])
cw = np.cumsum(data1[:,5])
yy = 0.0
for i in range(1000,2000000):
	xx = xx + (data[i,2]+data[i+1,2])*data[i,3]
	
for i in range(1000,2000000):
	yy = yy + (data1[i,2]+data1[i+1,2])*data1[i,3]
	
print 0.5*xx,0.5*yy
print len(data),len(data1)
plot(data[:,0],our,linewidth = 0.5)
plot(data1[:,0],cw,linewidth = 0.5)
show()
	
