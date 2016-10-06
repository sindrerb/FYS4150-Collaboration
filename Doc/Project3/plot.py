# -*- coding: utf-8 -*-
"""
FYS4150 - Computational Physics

Written by: Sindre Rannem Bilden
"""

import numpy as np
import matplotlib.pyplot as plt


earth = np.loadtxt("./build/earth", dtype = 'float', skiprows = 2)
jupiter = np.loadtxt("./build/jupiter",dtype = 'float', skiprows = 2)

#plt.xlim(-1,1); plt.ylim(-1,1)
plt.xlabel("x [AU]"); plt.ylabel("y [AU]");
plt.scatter(earth[0,0],earth[0,1], color='blue')
plt.scatter(0,0,color='yellow',s=100)
plt.scatter(jupiter[0,0],jupiter[0,1], color='red', s=50)
plt.plot(jupiter[:,0],jupiter[:,1],'r')
plt.plot(earth[:,0],earth[:,1],'b')
plt.savefig('test.png')
