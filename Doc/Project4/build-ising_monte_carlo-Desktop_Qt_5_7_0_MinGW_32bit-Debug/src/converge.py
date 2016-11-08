# -*- coding: utf-8 -*-
"""
Created on Tue Nov 08 16:35:03 2016

@author: sindrerb
"""

import matplotlib.pyplot as plt
import numpy as np

dat = np.loadtxt("outPutfile.txt")

#plt.plot(dat[:,0],dat[:,1])
plt.plot(dat[:,0],dat[:,3])
plt.show()