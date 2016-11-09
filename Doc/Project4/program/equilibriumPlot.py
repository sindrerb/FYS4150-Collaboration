# -*- coding: utf-8 -*-
"""
Created on Tue Nov  8 11:37:40 2016

@author: sindrerb
"""
filename = "./release/histogram/latt20eq"

cols = [0,2]
import matplotlib.pyplot as plt
import numpy as np

labels=np.loadtxt(filename,dtype='string', usecols=cols)[1,:]
rnd = np.loadtxt(filename,dtype='float', skiprows=2,usecols=cols)
#rnd = np.loadtxt("./benchmarks/convergence20G",dtype='float', skiprows=1,usecols=cols)

fig = plt.figure()
plt.title("Calculations from a random state at T=1")

for i in range(1,len(labels)):
    plt.subplot(len(labels)-1,1,i)
    #plt.ylabel(labels[i])
    plt.ylim(min(rnd[:,i])-abs(min(rnd[:,i]))*0.01,max(rnd[:,i])+abs(max(rnd[:,i]))*0.01)
    plt.plot(rnd[:,0],rnd[:,i])
#plt.xlabel(labels[0])
plt.ylabel("Accepted tries")
plt.xlabel("Total tries")