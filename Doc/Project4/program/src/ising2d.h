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
    int *histogramList;
    double energy;
    double magneticMoment;


public:
    Ising2D();
    Ising2D(int spins);

    //Various initial states
    void initializeRandomStateLattice();
    void initializeGroundStateLattice();

    double* metropolis(int start, int end, double temperature);
    int* histogram(std::string outputFile, int start, int end, double temperature);
    void delteLattice();
    void initializeOutput(std::string outputFile,int totalMonteCarloCycles);
    void writeOutput(std::string outputFile,int totalMonteCarloCycles, double temperature, double *totalResult);

    void initializeOutputHistogram(std::string outputFile,int totalMonteCarloCycles, int equilibriumCycle);
    void writeHistogram(std::string outputFile,int temperature, int *totalHistogram);

    //Setters
    void setSpin(int spins);

    //Getters
    int getSpin();
};

#endif // ISING2D_H
