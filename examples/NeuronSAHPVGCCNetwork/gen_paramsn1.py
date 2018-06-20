import json
import numpy as np
counter = 0
par_dict = dict()
"""
for iext in np.arange(8,11,0.5):
	for ampn in np.arange(1,2,0.1): 
		for gl in np.arange(0.0,0.4,0.1):
			for trial in range(3):
				par_dict[counter] = [ampn,iext,gl,trial]	
				counter += 1
"""

"""
iext = 10.4
gl = 0.3
ampn = 0.0
for gs in np.arange(0.1,0.3,0.05): 
	for rb in np.arange(0.0,10.0,0.1):
		for trial in range(1):
			par_dict[counter] = [ampn,iext,gl,trial,gs,rb]
			counter += 1
json.dump(par_dict, open("gsrb.txt",'w'))

"""
gl = 0.3
ampn = 0.0
iext = 14.0
gs = 0.4
rb = 4.0
a = 0.0002
gc = 0.15
rt = 0.0

nc =1000
for ns in np.arange(10,1010,10):
	for trial in range(1):
		par_dict[counter] = [ampn,trial,iext,gl,gs,rb,a,gc,rt,nc,ns]	
		counter += 1
json.dump(par_dict, open("ahp10to1000.txt",'w'))


