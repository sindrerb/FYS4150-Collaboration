# -*- coding: utf-8 -*-
"""
Created on Sat Oct 22 08:36:10 2016

@author: sindrerb
"""

import matplotlib.pyplot as plt
import numpy as np

Data = np.loadtxt('accuaracyTbl.txt',delimiter='&')

#plt.title('Offset from analytical path after one year',size=15)
plt.ylabel('Offset [AU]',size=15); plt.xlabel('Number of iterations per year',size=15)
plt.xscale('log');plt.yscale('log')
plt.plot(Data[:,0],Data[:,1],'o:',color='blue',markersize=7,label='Euler')
plt.plot(Data[:,0],Data[:,2],'v:',color='green',markersize=7,label='Verlet')
plt.legend()
plt.plot()

