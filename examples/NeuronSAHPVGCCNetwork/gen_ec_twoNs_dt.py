import sys
import math
import json
import numpy as np
import multiprocessing as mp


def oneEC(l_pars):
    nNeurons = 2
    dt = l_pars[0]
    trial = l_pars[1] 
    #dt = 0.005
    t = np.arange(0.0,100000.0,dt)
    DT = str(dt)
    TRIAL = str(trial)

    outfile = open("/media/subhadra/b8f700e2-a56b-4e3c-ba5d-d4a7ab6f5d56/centos6.3/arun/Subhadra/ext/ec_files/ec_2N_dt_%s_trial_%s.isf"%(DT,TRIAL),"w")
    strToFile = ""
    strToFile += "time"
    for i in range(nNeurons):
        strToFile += ","
        strToFile +=str(i)
    strToFile += "\n"

    np.random.seed(trial)

    comma_str = ","
    for i in range(len(t)):
        strToFile += str(t[i])
        randVec = np.random.randn(nNeurons)
        str_randVec = ['%0.4f'%x for x in randVec]
        strToFile += ","
        
        strToFile += comma_str.join(str_randVec)

        #for j in range(nNeurons):
        #    strToFile += str(randVec[j])
        #    strToFile += ","
        strToFile += "\n"

    outfile.write(strToFile)
    outfile.close()


pool = mp.Pool(3)
l_inps = [ [dt,trial]  for dt in np.arange(0.001,0.03,0.001) for trial in range(3)]
pool.map(oneEC,l_inps)

