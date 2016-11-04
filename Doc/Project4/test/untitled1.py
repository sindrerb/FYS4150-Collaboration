# -*- coding: utf-8 -*-
"""
Created on Tue Sep 13 08:00:25 2016
FYS3110 - Problem set 3
@author: sindrerb
"""
import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import expm

g=1; V=4; N=20; hbar = 1.0
I = np.identity(N)

def hamiltonian(N):#Construction an hamiltonian matrix 
    H = np.zeros([N,N])     #Hamlitonian matrix
    potential = -V*I*I[0,:] #The potential located at atom 0 

    red = np.zeros([N,N])   #  |i><i+1| term
    inc = np.zeros([N,N])   #|i+1><i|   term
    for i in range(0,N-1):  #Assign values to a matrix
        red[i,i+1] = 1;     
        inc[i+1,i] = 1;

    for i in range(0,N):    #Constructing the hamiltonian matrix
        H += -g*(red*I[:,i] +  inc*I[:,i])
    return H  + potential


"""Task C"""
eig = np.linalg.eig(hamiltonian(N))

groundstate = eig[1][:,0]
#Writing energy diagram

plt.xticks([]); plt.ylabel('Arb. energy')           
plt.scatter(np.ones(N),eig[0],marker='_',s=10000)   
plt.scatter(1,min(eig[0]),color='r',marker='_',s=20000,label="E0 = %.2f" %(min(eig[0])))   
plt.legend(markerscale=0.1, scatterpoints=1); plt.show()

"""Task D"""

def Prob(Psi):
    P = np.ones(N) 
    for i in range(0,N):    #Summation of total overlap
        P[i] = np.inner(Psi,I[:,i])**2
    return P

P_matrix = Prob(groundstate)
#print P_matrix
print "The probability for state 0 is %.7f, for state 1 it is %.7f" %(P_matrix[0], P_matrix[1])


"""Task E"""

X = np.zeros((N,N))
for i in range(0,N):
    X[i][i]=i

def expectation(Omega,Psi):
    return np.sum(np.inner(Prob(Psi),X))

print "The expectation value for X in the ground state is %.4f " %(expectation(X,groundstate))

"""Task F"""

def time_operator(t,t0):
    H = hamiltonian(N)
    return expm(-1.0j*H*(t-t0)/hbar)

#Computing time evolvment of PsiG

n=1000
ProbT=np.zeros((n,N))
ExpX = np.zeros(n)
Psi = eig[1][0]
T = np.linspace(0,4,n)
t = T[1]
O = time_operator(t,0)
for i in range(0,n):
    ProbT[i][:] = np.dot(Prob(Psi),np.ones(N))
    ExpX[i] = expectation(X,Psi)
    Psi = np.dot(O,Psi)
    #print Psi

    
plt.subplot(2,1,1)
plt.ylabel("Probability $P_0(t)$")
plt.plot(T,ProbT[:,0])
plt.subplot(2,1,2)
plt.ylabel("Expexted possition $<X(t)>$"),plt.xlabel("Time t")
plt.plot(T,ExpX)

