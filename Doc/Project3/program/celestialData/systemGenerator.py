# -*- coding: utf-8 -*-
"""
Created on Sat Oct 15 11:31:45 2016

@author: sindrerb
"""

celestials = ["sun","mercury","venus","earth","mars","jupiter","saturn","uranus","neptune"]

outfilename = "solarSystem.txt"

output = open(outfilename,'w')

for celestial in celestials:
    filename = celestial+".txt"
    data = open(filename,'r')
    n=0
    output.write(celestial+'\t')
    line = data.readline()
    Mass = -1
    while(Mass==-1 and n<10):
        line = data.readline()
        Mass = line.find('Mass')
        n+=1
        
    exponentint = line.find('^',Mass)+1
    massint = line.find('kg',exponentint)
    mantissaint = line.find('=',Mass)+1
    solarmass = 0;
    if(mantissaint == 0):
        mantissaint = massint+8
  
    if(celestial=="sun"):
        solarexp = int(line[exponentint:massint])
        solarmantissa = float(line[mantissaint:mantissaint+8])
        output.write('1.0000e00 \t')
    else:
        celestialexp = int(line[exponentint:massint])-solarexp
        celestialmantissa = float(line[mantissaint:mantissaint+8])/solarmantissa
        
        output.write(str(celestialmantissa)+'e'+str(celestialexp)+'\t')

    while(data.readline()[0:2]!='$$' and n<100):
        n+=1
    line = data.readline()[52:193]
    pos = line[:70]
    vel = line[70:].split(',')
    vel = [float(x)*365.25 for x in vel]
    vel = ',  '.join([str(x) for x in vel])
    line = pos +"  "+ vel
    line = line.replace(",", " ")    
    line = line.replace("E", "e")    
    output.write(line+'\n')
output.close()
