# -*- coding: utf-8 -*-
"""
Created on Thu Nov 10 18:47:56 2016

@author: sindrerb
"""

import matplotlib.pyplot as plt
import numpy as np

def fit(x,y):
    p = np.polyfit(x,y,4)
    return np.polyval(p,x)    
    
j = 2
plt.style.use("ggplot")
fig = plt.figure(figsize=(15,20))
ax1 = fig.add_subplot(4,1,1)
ax2 = fig.add_subplot(4,1,2)
ax3 = fig.add_subplot(4,1,3)
ax4 = fig.add_subplot(4,1,4)

fig.suptitle("Probability distributions at different temperature",size=20)

S40 = np.loadtxt("./data/spin40",skiprows=3)
S60 = np.loadtxt("./data/spin60",skiprows=3)
S100 = np.loadtxt("./data/spin100",skiprows=3)
S140 = np.loadtxt("./data/spin140",skiprows=3)

TC40C = S40[S40[:,2]==max(S40[:,2])][0,0]
TC60C = S60[S60[:,2]==max(S60[:,2])][0,0]
TC100C = S100[S100[:,2]==max(S100[:,2])][0,0]
TC140C = S140[S140[:,2]==max(S140[:,2])][0,0]

TCC = np.array([TC40C,TC60C,TC100C,TC140C])


TC40M = S40[S40[:,4]==max(S40[:,4])][0,0]
TC60M = S60[S60[:,4]==max(S60[:,4])][0,0]
TC100M = S100[S100[:,4]==max(S100[:,4])][0,0]
TC140M = S140[S140[:,4]==max(S140[:,4])][0,0]

TCM = np.array([TC40M,TC60M,TC100M,TC140M])

S = np.array([40.0,60.0,100.0,140.0])

print TCC
print TCM

a = np.array([0.0,0.0,0.0,0.0])
for i in range(len(a)):
    a[i] = (1.0/S[i]-TCC[i])
print "TCC=",np.mean(a)
print 1+np.mean(a)/2.269

a = np.array([0.0,0.0,0.0,0.0])
for i in range(len(a)):
    a[i] = (1.0/S[i]-TCM[i])
print "TCM=",np.mean(a)
print 1+np.mean(a)/2.269

a = np.array([0.0,0.0,0.0,0.0])
for i in range(len(a)):
    a[i] = (1.0/S[i]-(TCM[i]+TCC[i])/2)
print "TCM=",np.mean(a)
print 1+np.mean(a)/2.269

#scatter
ax1.plot(S40[:,0],fit(S40[:,0],S40[:,1]),color='red')
ax1.plot(S60[:,0],fit(S60[:,0],S60[:,1]),color='blue')
ax1.plot(S100[:,0],fit(S100[:,0],S100[:,1]),color='purple')
ax1.plot(S140[:,0],fit(S140[:,0],S140[:,1]),color='green')
ax1.scatter(S40[:,0],S40[:,1],label='n=40',color='red',marker='^')
ax1.scatter(S60[:,0],S60[:,1],label='n=60',color='blue',marker='d')
ax1.scatter(S100[:,0],S100[:,1],label='n=100',color='purple',marker='x')
ax1.scatter(S140[:,0],S140[:,1],label='n=140',color='green',marker='s')
#scatter
ax2.plot()
ax2.plot(S40[:,0],fit(S40[:,0],S40[:,5]),':',color='red')
ax2.plot(S60[:,0],fit(S60[:,0],S60[:,5]),':',color='blue')
ax2.plot(S100[:,0],fit(S100[:,0],S100[:,5]),':',color='purple')
ax2.plot(S140[:,0],fit(S140[:,0],S140[:,5]),':',color='green')
ax2.scatter(S40[:,0],S40[:,5],label='n=40',color='red',marker='^')
ax2.scatter(S60[:,0],S60[:,5],label='n=60',color='blue',marker='d')
ax2.scatter(S100[:,0],S100[:,5],label='n=100',color='purple',marker='x')
ax2.scatter(S140[:,0],S140[:,5],label='n=140',color='green',marker='s')
#scatter
ax3.plot(S40[:,0],fit(S40[:,0],S40[:,2]),color='red')
ax3.plot(S60[:,0],fit(S60[:,0],S60[:,2]),color='blue')
ax3.plot(S100[:,0],fit(S100[:,0],S100[:,2]),color='purple')
ax3.plot(S140[:,0],fit(S140[:,0],S140[:,2]),color='green')
ax3.scatter(S40[:,0],S40[:,2],label='n=40',color='red',marker='^')
ax3.scatter(S60[:,0],S60[:,2],label='n=60',color='blue',marker='d')
ax3.scatter(S100[:,0],S100[:,2],label='n=100',color='purple',marker='x')
ax3.scatter(S140[:,0],S140[:,2],label='n=140',color='green',marker='s')
#scatter
ax4.plot(S40[:,0],fit(S40[:,0],S40[:,4]),color='red')
ax4.plot(S60[:,0],fit(S60[:,0],S60[:,4]),color='blue')
ax4.plot(S100[:,0],fit(S100[:,0],S100[:,4]),color='purple')
ax4.plot(S140[:,0],fit(S140[:,0],S140[:,4]),color='green')
ax4.scatter(S40[:,0],S40[:,4],label='n=40',color='red',marker='^')
ax4.scatter(S60[:,0],S60[:,4],label='n=60',color='blue',marker='d')
ax4.scatter(S100[:,0],S100[:,4],label='n=100',color='purple',marker='x')
ax4.scatter(S140[:,0],S140[:,4],label='n=140',color='green',marker='s')

ax1.set_ylabel(r"$\langle E \rangle$",size=20)
ax2.set_ylabel(r"$\langle |M| \rangle$",size=20)
ax3.set_ylabel(r"$C_V$",size=20)
ax4.set_ylabel(r"$\chi$",size=20)

ax4.set_xlabel("Temperature T [$J/k$]",size=16)

ax1.legend()
ax2.legend()
ax3.legend()
ax4.legend()

#fig.savefig("PhaseTrans.eps",bbox_inches='tight',format='eps')



