# -*- coding: utf-8 -*-
"""
Created on Tue Nov  8 11:37:40 2016

@author: sindrerb
"""


cols = [0,1,2,3,4,5,6]
import matplotlib.pyplot as plt
import numpy as np


#rnd = np.loadtxt("./benchmarks/convergence20G",dtype='float', skiprows=1,usecols=cols)

fig = plt.figure()
plt.title("Calculations from the ground state")
temps = ['1_0','1_7','2_4']
j = 2
labels = [r"Cycles","accepted",r"$n_a/cycles$",r"$\langle E\rangle$",r"$\langle E\rangle/cycles$",r"$\langle |M|\rangle$",r"$\langle \left|M\right|\rangle/cycles$"]

fig.suptitle("Equilibrium of mean energy at various temperatures",size=20)
for i,T in enumerate(temps):
    filename = "./release/histogram/eq20R"+T+"T"
    
    #labels=np.loadtxt(filename,dtype='string', usecols=cols)[0,:]
    rnd = np.loadtxt(filename,dtype='float', skiprows=2,usecols=cols)[:500]

    plt.subplot(len(temps),1,i+1)
    plt.xlim(rnd[0,0],rnd[-1,0])
    #plt.ylabel(labels[i])
    #plt.ylim(min(rnd[:,j])-abs(min(rnd[:,j]))*0.1,max(rnd[:,j])+abs(max(rnd[:,j]))*0.1)
    plt.plot(rnd[:,0],rnd[:,j],label='$T=$ %.1f $J/k$' %(1+i*0.7))
    plt.ylabel(labels[j],size=16)
    plt.legend(loc='best')
#plt.xlabel(labels[0])

plt.xlabel("Total cycles",size=15)
plt.savefig("EqAcceptR",bbox_inches='tight',format='eps')
