import numpy as np
import matplotlib.pyplot as plt


sun = np.loadtxt("OUTPUT.txt", dtype = 'float',delimiter=",", skiprows = 2, usecols=[1,2,3])
earth = np.loadtxt("OUTPUT.txt", dtype = 'float',delimiter=",", skiprows = 2, usecols=[4,5,6])
print "test"

plt.plot(earth[:,0],earth[:,1],'-')
plt.show()