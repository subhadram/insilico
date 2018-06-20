import sys
import math
import json
import numpy as np
import multiprocessing as mp


def oneEC(trial):
    nNeurons = 2
    dt = 0.005
    t = np.arange(0.0,10000.0,dt)

    TRIAL = str(trial)

    outfile = open("ec_2N_trial_%s_005.isf"%TRIAL,"w")
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
        str_randVec = ['%0.2f'%x for x in randVec]
        strToFile += ","
        
        strToFile += comma_str.join(str_randVec)

        #for j in range(nNeurons):
        #    strToFile += str(randVec[j])
        #    strToFile += ","
        strToFile += "\n"

    outfile.write(strToFile)
    outfile.close()


pool = mp.Pool(3)

pool.map(oneEC,range(3))

