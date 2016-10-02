# -*- coding: utf-8 -*-
"""
Test of conserved orthogonality
Created on Tue Sep 27 21:03:32 2016
@author: sindrerb
Last edited by: sindrerb
"""

import numpy as np
import matplotlib.pyplot as plt

N = 3
plt.xlim(0,6);
plt.title(" ")
plt.xlabel(r"$\rho$",size=20); plt.ylabel(r"$|u(\rho)|^2$",size=20)
M = np.loadtxt("./build/eigenvecsN500", dtype = 'float', skiprows = 2)
X = np.loadtxt("./build/eigenvecsN500", dtype = 'float', skiprows = 1)[0,:]
E = np.loadtxt("./build/eigenvalsN500", dtype = 'float', skiprows = 2)

for i in range(0,N):
    plt.plot(X,abs(M[:,i])**2,label="E=%.4f" %(E[i]))
    
plt.legend()

"""
t = np.loadtxt("./build/iterationtable", dtype = 'float', skiprows = 1)

T = np.linspace(0,400,1000)
plt.ylabel("Iterations");plt.xlabel("Meshpoints NxN")
plt.plot(T,5.0/4*T**2,'r')
plt.plot(t[:,0],t[:,1],'bo')
"""