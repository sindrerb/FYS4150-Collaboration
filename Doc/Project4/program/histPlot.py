# -*- coding: utf-8 -*-
"""
Created on Wed Nov  9 08:50:14 2016

@author: sindrerb
"""

import matplotlib.pyplot as plt
import numpy as np


for i,L in enumerate(['1_7']):#,'1_0','2_4'
    dat = np.loadtxt("./release/histogram/hist20G"+L+"T",skiprows=3)
    temp = dat[1,0]
    energy = dat[0,1:]
    hist = dat[1,1:]
    #plt.xticks(np.linspace(energy[0],energy[-1],len(energy)))
    plt.xlim(energy[0],-650)
    #plt.yscale('log')
    #plt.ylim(0,max(hist)*1.01)
    #plt.ylim(0,1)
    plt.step(energy,hist/sum(abs(hist)),where='mid',label='T='+str(temp))

plt.legend()
plt.ylabel("Probability P(E)")
plt.xlabel("Energy [J]")