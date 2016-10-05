# -*- coding: utf-8 -*-
"""
FYS4150 - Computational Physics

Written by: Sindre Rannem Bilden
"""

import numpy as np
import matplotlib.pyplot as plt


pos = np.loadtxt("./build/Pos.txt", dtype = 'float', skiprows = 2)
x = pos[:,0]
y = pos[:,1]
plt.xlim(-1,1); plt.ylim(-1,1)
plt.scatter(x[0],y[0])
plt.plot(x,y,'b')
