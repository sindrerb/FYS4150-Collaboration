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
W = ['0.010','0.500','1.000','5.000']
plt.xlim(0,5)
plt.ylabel(r"$|u(\rho)|^2$",size=20); plt.xlabel(r"$\rho$",size=20)
for w in W:
    M = np.loadtxt("./build/freq/eigenvecsF"+str(w), dtype = 'float', skiprows = 1)
    E = np.loadtxt("./build/freq/eigenvalsF"+str(w), dtype = 'float', skiprows = 2)
    X = E[1,:]
    E = E[0,:]
    plt.plot(X,abs(M[:,0])**2,label=r"$\omega_f=%s$" %(w))
plt.legend()