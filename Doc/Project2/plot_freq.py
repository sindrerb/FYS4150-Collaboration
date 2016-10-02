# -*- coding: utf-8 -*-
"""
Test of conserved orthogonality
Created on Tue Sep 27 21:03:32 2016
@author: sindrerb
Last edited by: sindrerb
"""

import numpy as np
import matplotlib.pyplot as plt
w = '2.50'

plt.title(r"$\omega_r= %s$" %(w),size=20)
plt.ylabel(r"$|u(\rho)|^2$",size=20); plt.xlabel(r"$\rho$",size=20)
M0 = np.loadtxt("./build/freq/eigenvecsF"+str(w), dtype = 'float', skiprows = 3)
MC = np.loadtxt("./build/freq/eigenvecsF"+str(w)+"Columb", dtype = 'float', skiprows = 3)
E  = np.loadtxt("./build/freq/eigenvecsF"+str(w), dtype = 'float', skiprows = 1)
print M0[:,0]
X = E[0,:]
plt.plot(X,abs(M0[:,0])**2,'-',color='black',label=r"No interaction")
plt.plot(X,abs(MC[:,0])**2,'--',color='black',label=r"Ineraction")
plt.legend()