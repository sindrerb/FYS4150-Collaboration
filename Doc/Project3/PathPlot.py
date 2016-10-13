import numpy as np
import matplotlib.pyplot as plt


earth = np.loadtxt("OUTPUT.txt", dtype = 'float', skiprows = 2, usecols=(4,5,6))

plt.plot(earth[0],earth[1],'-')
plt.show()