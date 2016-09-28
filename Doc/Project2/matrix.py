# -*- coding: utf-8 -*-
"""
Test of conserved orthogonality
Created on Tue Sep 27 21:03:32 2016
@author: sindrerb
Last edited by: sindrerb
"""

import numpy as np
import matplotlib.pyplot as plt


def ortho(N):
    M = np.loadtxt("./build_sindrerb/unitTest"+str(N), dtype = 'float', skiprows = 3)
    maxval = 0
    for i in range(0,len(M[:,1])):
        for j in range(0,len(M[1,:])):
            temp = np.dot(M[:,i],M[:,j])
            if (maxval < temp and i!=j):
                maxval = temp
    return maxval
    
for N in range(50,450,50):
    print(ortho(N))