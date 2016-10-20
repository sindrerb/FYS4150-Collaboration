import numpy as np
import matplotlib.pyplot as plt

files = ["jup1.txt","jup10.txt","jup1000.txt"]
labels = ["1","10","1000"]
lines = [':','--','-','-.-']

for fileN in range(0,len(files)):
    data = open("./debug/src/"+files[fileN])
    celestials = data.read().splitlines()[1]
    celestials = celestials.split()[1:]
    
    plt.subplot(len(files),1,fileN+1)
    system = np.loadtxt("./debug/src/"+files[fileN], dtype = 'float',delimiter=",", skiprows = 2)
    plt.scatter(0,0,c='y',s=50)
    for i in range(2,len(celestials)):
        plt.plot(system[:,3*i+1],system[:,3*i+2],lines[fileN],color='black',label='$M=%s M_J$' %(labels[fileN]))
    
    plt.legend()
plt.xlim(-1.5,1.5)
plt.ylim(-1.5,1.5)
plt.show()
