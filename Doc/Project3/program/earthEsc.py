import numpy as np
import matplotlib.pyplot as plt

files = ["e6-28.txt","e7.txt","e8-88.txt"]
labels = ["6.28AU/Yr","7AU/Yr","8.8857AU/Yr"]
lines = ['-','--',':']
for fileN in range(0,len(files)):
    data = open("./debug/src/"+files[fileN])
    celestials = data.read().splitlines()[1]
    celestials = celestials.split()[1:]
    
    system = np.loadtxt("./debug/src/"+files[fileN], dtype = 'float',delimiter=",", skiprows = 2)
    plt.scatter(0,0,c='y',s=50)
    for i in range(1,len(celestials)):
        plt.plot(system[:,3*i+1],system[:,3*i+2],lines[fileN],color='black',label='$v_0=%s$' %(labels[fileN]))
    
    plt.legend()
plt.show()
