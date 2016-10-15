import numpy as np
import matplotlib.pyplot as plt

filename = "OUTPUT.txt"

data = open("./debug/"+filename)
celestials = data.read().splitlines()[1]
celestials = celestials.split()[1:]

system = np.loadtxt("./debug/"+filename, dtype = 'float',delimiter=",", skiprows = 2)
plt.scatter(0,0,c='y',s=50)
for i in range(1,len(celestials)):
    plt.plot(system[:,3*i+1],system[:,3*i+2],':',label='%s' %(celestials[i]).title())

plt.legend()
plt.show()
