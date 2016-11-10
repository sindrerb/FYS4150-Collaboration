# -*- coding: utf-8 -*-
"""
Created on Sun Oct 30 15:25:18 2016

@author: sindrerb
"""

import numpy as np
import matplotlib.pyplot as plt


#print 'E = ', E(1)/4, 'Cv = ', CV(1)/4, 'X = ', chi(1)/4;

filename = "4c_L20_T2.4_e7.txt"

cols = [0,1,2,3,4,5,6,7,8,9,10]
alldata = np.loadtxt(filename, skiprows = 1 ,usecols = cols)
labels = np.loadtxt(filename, dtype = 'string', usecols = cols)[0,:]


#print alldata
plt.plot(alldata[0,:],alldata[10,:])
plt.show()

"""
print labels
#print len(alldata[:,0])
data = np.zeros((9,len(alldata[0,:])))
#print data
for i in range(len(alldata[:,0])):
	#print alldata[i,:]
	for j in range(1,10):
	#print alldata[i,0]
		if (alldata[i,0] == j):
			data[j-1,:] += alldata[i,:]
			#print data[j-1,:]

#print data


for k in range(9):
	divident = data[k,0]/(k+1)
	data[k] = data[k]/divident
print data[:,0]

fig = plt.figure()
plt.title("Convergence test for 20X20 from ground state at T=1")
for i in range(1,len(labels)):
	plt.subplot(len(labels)-1,1,i)
	plt.ylabel(labels[i])
	#plt.xscale('log')
	#plt.ylim(min(data[:,i])-abs(min(data[:,i]))*0.01,max(data[:,i])+abs(max(data[:,i]))*0.01)
	plt.plot(data[:,0],data[:,i])
plt.xlabel(labels[0])

plt.show()


num = [-1.992, -1.9956, -1.99781, -1.997105, -1.9971527, -1.9971469,]
MC  = [   1E1,     1E2,      1E3,       1E4,        1E5,        1E6,       1E7,    1E8]
data = np.loadtxt("./debug/src/lattice20",usecols=(0,1))
#data = np.loadtxt("/home/sindrerb/testIsingBuild/testIsing.txt",usecols=(0,1))

print data[1]


plt.plot(MC,num,'--',color='black',label='Numerical')
plt.plot(MC,an[0],':',color='black',label='analytical')
plt.xlabel('Monte Carlo cycles')
plt.ylabel(r'$\langle$E$\rangle$')
plt.legend()
#x=np.linspace(data[0,0],data[-1,0],1000)
x = np.linspace(0,4,1000)
#plt.plot(x,E(x),'--',label="An")

#plt.plot(x,Energy2(x)*2/100000,'-.',label="An2")
Cv = CV(x)
#plt.plot(x,Cv/max(Cv),label="Cv")
Chi = chi(x)
#plt.plot(x,Chi/max(Chi),label="Analytic")

plt.ylabel("Energy J")
plt.xlabel("Temp. J/k")
#plt.plot(data[:,0],data[:,1],label="Numeric")
plt.legend()
"""