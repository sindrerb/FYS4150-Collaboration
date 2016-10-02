# -*- coding: utf-8 -*-
"""
Plots eigenvectors with corresponding eigenvalues
Created on Tue Sep 27 21:03:32 2016
@author: sindrerb
Last edited by: sindrerb
"""

import numpy as np
import matplotlib.pyplot as plt

N = 3
M = np.loadtxt("./build/eigenvecsN500", dtype = 'float', skiprows = 3)
X = np.loadtxt("./build/eigenvecsN500", dtype = 'float', skiprows = 1)[0,:]
E = np.loadtxt("./build/eigenvalsN500", dtype = 'float', skiprows = 2)

time = False

linestyles = ['-','--',':','-.']
if(not time):
    plt.xlim(0,6);
    plt.title(" ")
    plt.xlabel(r"$\rho$",size=20); plt.ylabel(r"$|u(\rho)|^2$",size=20)
    for i in range(0,N):
        plt.plot(X,abs(M[:,i])**2,color='black',linestyle=linestyles[i],label=r"$E_%i=%.4f$" %(i,E[i]))
    
    plt.legend()
else:
    t = np.loadtxt("./build/iterationtable", dtype = 'float', skiprows = 1)
    T = np.linspace(0,400,1000)
    plt.ylabel("Iterations");plt.xlabel("Meshpoints N")
    plt.plot(T,5.0/4*T**2,color='black',linestyle=':')
    plt.plot(t[:,0],t[:,1],'o',color='black')
    plt.legend()
