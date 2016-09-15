from pylab import*
from scipy.integrate import quad
import numpy as np
import os


file = np.loadtxt("../programs/build_d/run10", dtype = 'float', skiprows = 2, usecols = (0,1,2))

file_lenght = str(len(file)-2)
file_header = "Number of iterations " + file_lenght
#print file , file_lenght


#Plotting
fig = figure()
grid(True, which = 'both')#, ls= '-')
grid('on')

plot(file[:,0],file[:,1],'r-', label = '$approx.\ solution$ ') 
plot(file[:,0],file[:,2],'b-', label = '$exact\ solution$ ') 

xlabel(r'$x$', size = 20,labelpad= 5 )
ylabel(r'$f(x)$',size = 20, labelpad = 5)
title(file_header)
legend()
fig.savefig('b_run10.png')
show()
