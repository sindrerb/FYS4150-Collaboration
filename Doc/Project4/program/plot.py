# -*- coding: utf-8 -*-
"""
Created on Sun Oct 30 15:25:18 2016

@author: sindrerb
"""

import numpy as np
import matplotlib.pyplot as plt

def Energy(T):
    return 16.0*(np.exp(8*T)-np.exp(-8*T))

def CV(x):
    return x**-2*(2*np.cosh(x)+1)/(np.cosh(x)+3)**2 #missing one Kb

def chi(x):
    return 40/x

"""
fig, ax = plt.subplots()
x = np.linspace(0.1,10,100)
plt.xlabel('Temp')
plt.ylabel('Cv')
plt.plot(x,CV(x))

fig, ax = plt.subplots()
x = np.linspace(0.1,10,100)
plt.xlabel('Temp')
plt.ylabel(r'$\chi$')
plt.plot(x,chi(x))
"""
data = np.loadtxt("./debug/src/test.txt",usecols=(0,4))

x=np.linspace(data[0,0],data[-1,0])
#plt.plot(x,Energy(x))
Cv = CV(x)
#plt.plot(x,Cv/max(Cv))
Chi = chi(x)
plt.plot(x,Chi/max(Chi))
plt.plot(data[:,0],data[:,1]/max(data[:,1]))
