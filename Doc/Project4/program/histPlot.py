# -*- coding: utf-8 -*-
"""
Created on Wed Nov  9 08:50:14 2016

@author: sindrerb
"""

import matplotlib.pyplot as plt
import numpy as np

dat = np.loadtxt("./release/histogram/lattice5hist",skiprows=3)

temp = dat[:,0]
energy = dat[0,1:]
hist = dat[1,1:]
plt.xticks(np.linspace(energy[0],energy[-1],len(energy)))
plt.xlim(energy[hist>0][0],energy[hist>0][-1]+4)
print max(hist)
plt.ylim(0,max(hist)*1.01)
plt.step(energy,hist,where='mid')
