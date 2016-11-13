# -*- coding: utf-8 -*-
"""
Created on Wed Nov  9 08:50:14 2016

@author: sindrerb
"""

import matplotlib.pyplot as plt
import numpy as np
plt.style.use("ggplot")
fig = plt.figure(figsize=(15,10))
ax1 = fig.add_subplot(2,3,1)
ax2 = fig.add_subplot(2,3,2)
ax3 = fig.add_subplot(2,3,3)
ax4 = fig.add_subplot(2,3,(4,6))

fig.suptitle("Probability distributions at different temperature",size=20)

T10 = np.loadtxt("./release/histogram/hist20G1_0T",skiprows=3)
T17 = np.loadtxt("./release/histogram/hist20G1_7T",skiprows=3)
T24 = np.loadtxt("./release/histogram/hist20G2_4T",skiprows=3)



T = T24[:,1:]
Energies = T[0]/400
Occurence = T[1]
variance = 0
avg = 0
for i,E in enumerate(Energies):
    avg += E*Occurence[i]
avg = avg/sum(Occurence)

print avg*400

for i,E in enumerate(Energies):
    variance += Occurence[i]*(E)**2
variance = variance/sum(Occurence)-avg**2
print variance*400

energy = T10[0,1:]/400
T10 = T10[1,1:]
T17 = T17[1,1:]
T24 = T24[1,1:]



T10 = T10/sum(T10)
T17 = T17/sum(T17)
T24 = T24/sum(T24)

ax1.bar(energy[:10],T10[:10],width=0.01,alpha=0.5,color='red',label='T=1.0')
ax2.bar(energy[0:30],T17[0:30],width=0.01,alpha=0.5,color='blue',label='T=1.7')
ax3.bar(energy[25:120],T24[25:120],width=0.01,alpha=0.5,color='purple',label='T=2.4')

maxLim = 125
ax4.bar(energy[:maxLim],T10[:maxLim],width=0.01,alpha=0.5,color='red',label='T=1.0')
ax4.bar(energy[:maxLim],T17[:maxLim],width=0.01,alpha=0.5,color='blue',label='T=1.7')
ax4.bar(energy[:maxLim],T24[:maxLim],width=0.01,alpha=0.5,color='purple',label='T=2.4')

ax4.set_ylim(0,0.15)

ax4.set_xlabel('Energy [$J$]',size=20)
ax1.set_ylabel('Probability $P(E)$',size=20)
ax4.set_ylabel('Probability $P(E)$',size=20)

ax1.legend()
ax2.legend()
ax3.legend()
ax4.legend()

fig.savefig("ProbabilityHist",bbox_inches='tight',format='eps')
