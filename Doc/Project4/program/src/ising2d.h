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
    unsigned long *histogramList;
    double energy;
    double magneticMoment;


public:
    Ising2D();
    Ising2D(int spins);

    //Various initial states
    void initializeRandomStateLattice();
    void initializeGroundStateLattice();

    double* metropolis(int start, int end, double temperature);
    unsigned long* histogram(std::string outputFile, int start, int end, double temperature);
    void equilibrium(std::string outputFile, int totalMonteCarloCycles, double temperature);
    void delteLattice();
    void initializeOutput(std::string outputFile,int totalMonteCarloCycles);
    void writeOutput(std::string outputFile,int totalMonteCarloCycles, double temperature, double *totalResult);

    void initializeOutputHistogram(std::string outputFile,int totalMonteCarloCycles, int equilibriumCycle);
    void writeHistogram(std::string outputFile,double temperature, unsigned long *totalHistogram);

    //Setters
    void setSpin(int spins);

    //Getters
    int getSpin();
    int **getLattice() const;
    double getEnergy() const;
    int ***getPseudoLattice() const;
};

#endif // ISING2D_H
