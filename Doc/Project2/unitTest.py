# -*- coding: utf-8 -*-
"""
Test of conserved orthogonality and normality
Created on Tue Sep 27 21:03:32 2016
@author: sindrerb
Last edited by: sindrerb
"""

import numpy as np

def orthoTest(N):
    M = np.loadtxt("./build/UnitTest"+str(N), dtype = 'float', skiprows = 3)
    maxval = 0
    for i in range(0,len(M[:,1])):
        for j in range(0,len(M[1,:])):
            temp = np.dot(M[:,i],M[:,j])
            if (maxval < temp and i!=j):
                maxval = temp
    return maxval
def normalTest(N):
    M = np.loadtxt("./build/UnitTest"+str(N), dtype = 'float', skiprows = 3)
    maxval = 0
    for i in range(0,len(M[:,1])):
        temp = (1-np.dot(M[:,i],M[:,i]))
        if (maxval < temp):
            maxval = temp
    return maxval
    
print("Off-normality \tOff-orthogonality")
for N in range(1000,13000,1000):
    print(str(normalTest(N))+'\t'+str(orthoTest(N)))