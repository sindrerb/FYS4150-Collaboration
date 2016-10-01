# -*- coding: utf-8 -*-
"""
Test of conserved orthogonality
Created on Tue Sep 27 21:03:32 2016
@author: sindrerb
Last edited by: sindrerb
"""

import numpy as np
import matplotlib.pyplot as plt

N = [50,100,200,300,400]#,500]
plt.title("Convergence test of N")
for n in N:
    M = np.loadtxt("./build/eigenvecsN"+str(n), dtype = 'float', skiprows = 1)
    E = np.loadtxt("./build/eigenvalsN"+str(n), dtype = 'float', skiprows = 2)
    X = E[1,:]
    E = E[0,:]
    plt.plot(X,abs(M[:,0])**2,label="N=%i" %(n))
    
plt.legend()
"""
t = np.loadtxt("./build/iterationtable", dtype = 'float', skiprows = 1)

T = np.linspace(0,400,1000)
plt.ylabel("Iterations");plt.xlabel("Meshpoints NxN")
plt.plot(T,5.0/4*T**2,'r')
plt.plot(t[:,0],t[:,1],'bo')
"""