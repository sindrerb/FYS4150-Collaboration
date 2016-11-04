#include "mpi/mpi.h"
#include "ising2d.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    string filename;
    int numprocs, myRank, nSpin;
    long monteCarloCycles;
    double *myAverage, *totalAverage;
    double initTemp, finalTemp, tempStep;

    // Initialize MPI
    MPI_Init (&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    if(myRank ==  0 && argc <= 6) {
        cout << "Bad usage: " << argv[0] << ", read outputfile, number of spins, number of samples, initial temperature, final temp., temp. step.";
        exit(1);
    }
    if(myRank == 0 && argc > 6) {
        filename = argv[1];
        nSpin = atoi(argv[2]);
        monteCarloCycles = atol(argv[3]);
        initTemp = atof(argv[4]);
        finalTemp = atof(argv[5]);
        tempStep = atof(argv[6]);
    }
    int intervals = monteCarloCycles/numprocs;
    int myLoopStart = myRank*intervals+1;
    int myLoopEnd = myRank*intervals;
    if ((myRank == numprocs-1)&&(myLoopEnd<monteCarloCycles)) myLoopEnd = monteCarloCycles;
    Ising2D ising(nSpin);
    ising.InitializeLattice();
    myAverage = ising.Metropolis(0,monteCarloCycles,initTemp);

    MPI_Reduce(&myAverage[5],&totalAverage,5,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(myRank == 0) {
        ising.output(filename,monteCarloCycles,initTemp,myAverage);
    }
    ising.delteLattice();
    MPI_Finalize();
}
