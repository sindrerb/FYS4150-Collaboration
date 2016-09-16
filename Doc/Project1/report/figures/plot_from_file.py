from pylab import*
from scipy.integrate import quad
import numpy as np
import os


file = np.loadtxt("../programs/build_b/run1e2", dtype = 'float', skiprows = 2, usecols = (0,1,2))

file_lenght = str(len(file)-2)
file_header = "Number of iterations " + file_lenght
#print file , file_lenght


#Plotting
fig = figure()
grid(True, which = 'both')#, ls= '-')
grid('on')

plot(file[:,0],file[:,1],'r-', label = '$Nummerical\ approx.$ ') 
plot(file[:,0],file[:,2],'b-', label = '$Exact\ solution$ ') 

xlabel(r'$x$', size = 20,labelpad= 5 )
ylabel(r'$u(x)$',size = 20, labelpad = 5)
title(file_header)
legend()
fig.savefig('b-run1e2.png')
show()
