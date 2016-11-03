# -*- coding: utf-8 -*-
"""
Created on Sun Oct 30 15:25:18 2016

@author: sindrerb
"""

import numpy as np
import matplotlib.pyplot as plt



def Z(T):
    return 4*np.cosh(8*T)+12

def E(T):
    return 32.0*(np.sinh(8*T))/Z(T)

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
data = np.loadtxt("./debug/src/test.txt",usecols=(0,2))
#data = np.loadtxt("/home/sindrerb/testIsingBuild/testIsing.txt",usecols=(0,1))

print E(0)

x=np.linspace(data[0,0],data[-1,0])
plt.plot(x,E(x),'--',label="An")

#plt.plot(x,Energy2(x)*2/100000,'-.',label="An2")
Cv = CV(x)
#plt.plot(x,Cv/max(Cv),label="Cv")
Chi = chi(x)
#plt.plot(x,Chi/max(Chi),label="Analytic")

plt.ylabel("Energy J")
plt.xlabel("Temp. J/k")
plt.plot(data[:,0],data[:,1],label="Numeric")
plt.legend()
