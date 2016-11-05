#ifndef ISING2D_H
#define ISING2D_H
#include <random>
#include <iostream>
#include <fstream>
#include <iomanip>

class Ising2D
{
private:
    int nSpin=0;
    int **lattice;
    int ***pseudoLattice;
    double *w;
    double *expectationValues;
    double energy;
    double magneticMoment;


public:
    Ising2D();
    Ising2D(int spins);
    void InitializeLattice();
    double* Metropolis(int start, int end, double temperature);
    void delteLattice();
    void initializeOutput(std::string outputFile,int totalMonteCarloCycles);
    void writeOutput(std::string outputFile,int totalMonteCarloCycles, double temperature, double *totalResult);
};

#endif // ISING2D_H
