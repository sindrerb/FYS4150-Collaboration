#ifndef ISING2D_H
#define ISING2D_H
#include "matrix.h"

class Ising2D
{
public:
    Ising2D();
    void InitializeGroundState(int nSpin, Matrix lattice,double &energy, double &magneticMoment);
    // Will a random state converge faster than ground state? I think so..
    void InitializeRandomState(int nSpin, Matrix lattice, double &energy, double &magneticMoment);
    void Metropolis(int nSpin,int maxCycles, double temperature);
};

#endif // ISING2D_H
