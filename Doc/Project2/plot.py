# -*- coding: utf-8 -*-
"""
Test of conserved orthogonality
Created on Tue Sep 27 21:03:32 2016
@author: sindrerb
Last edited by: sindrerb
"""

import numpy as np
import matplotlib.pyplot as plt


N = 1
M = np.loadtxt("./build_sindrerb/eigenvecs", dtype = 'float', skiprows = 1)
E = np.loadtxt("./build_sindrerb/eigenvals", dtype = 'float', skiprows = 2)
X = E[1,:]
E = E[0,:]

for i in range(0,N):#len(M[:,0])):
    plt.plot(X,M[:,i],label="E=%.4f" %(E[i]))
    
plt.legend()