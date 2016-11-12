# -*- coding: utf-8 -*-
"""
Created on Thu Nov 10 18:05:42 2016

@author: sindrerb
"""
import matplotlib.pyplot as plt
import numpy as np

j = 2
S = 'G'

filename = "./release/histogram/eq20"+S+"R1_0T"
labels = [r"Cycles","accepted",r"$n_a/cycles$",r"$\langle E\rangle$",r"$\langle E\rangle/cycles$",r"$\langle |M|\rangle$",r"$\langle \left|M\right|\rangle/cycles$"]

T10 = np.loadtxt("./release/equilibrium/latt_Eq_20_"+S+"1.000000eq",dtype='float', skiprows=2,usecols=[0,j])[:500]
T17 = np.loadtxt("./release/equilibrium/latt_Eq_20_"+S+"1.700000eq",dtype='float', skiprows=2,usecols=[0,j])[:500]
T24 = np.loadtxt("./release/equilibrium/latt_Eq_20_"+S+"2.400000eq",dtype='float', skiprows=2,usecols=[0,j])[:500]

plt.style.use("ggplot")
fig = plt.figure(figsize=(15,10))
fig.suptitle("Time development of activity from ground state", size=20)

ax1 = fig.add_subplot(3,2,(1,2))
ax2 = fig.add_subplot(3,2,(3,4))
ax3 = fig.add_subplot(3,2,(5,6))

ax1.set_xlim(min(T10[:,0]),max(T10[:,0])-1)
ax2.set_xlim(min(T10[:,0]),max(T10[:,0])-1)
ax3.set_xlim(min(T10[:,0]),max(T10[:,0])-1)



ax1.plot(T10[:,0],T10[:,1],label="T=1.0",color='red')
ax2.plot(T17[:,0],T17[:,1],label="T=1.7",color='blue')
ax3.plot(T24[:,0],T24[:,1],label="T=2.4",color='purple')

ax1.set_ylabel(labels[j],size=20)
ax2.set_ylabel(labels[j],size=20)
ax3.set_ylabel(labels[j],size=20)

ax3.set_xlabel("Time [Monte Carlo sweeps]", size=15)

ax1.legend()
ax2.legend()
ax3.legend()

fig.savefig("EqActivity"+S+".eps",bbox_inches='tight',format='eps')