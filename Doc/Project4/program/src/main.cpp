#include "mpi/mpi.h"
#include "ising2d.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

ofstream ofile;

int main(int argc, char *argv[])
{
    string filename;
    int numprocs, myRank, nSpin;
    int monteCarloCycles;
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
        filename.append(argv[2]);
        nSpin = atoi(argv[2]);
        monteCarloCycles = atol(argv[3]);
        initTemp = atof(argv[4]);
        finalTemp = atof(argv[5]);
        tempStep = atof(argv[6]);
        cout << "Writes to " << filename << endl;
    }

    // Broadcast common variables to all nodes
    MPI_Bcast (&monteCarloCycles, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast (&nSpin, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&initTemp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast (&finalTemp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast (&tempStep, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int intervals = monteCarloCycles/numprocs;
    int myLoopStart = myRank*intervals+1;
    int myLoopEnd = (myRank+1)*intervals;
    if ((myRank == numprocs-1)&&(myLoopEnd<monteCarloCycles)) { myLoopEnd = monteCarloCycles;}

    Ising2D ising(nSpin);
    if(myRank == 0) {
        ising.initializeOutput(filename,monteCarloCycles);
    }
    ising.InitializeLattice();

    for(double temperature = initTemp; temperature<finalTemp; temperature+= tempStep) {
        cout << "My rank is "<<myRank<<" and i run from "<<myLoopStart<<" to "<<myLoopEnd<<endl;
        myAverage = ising.Metropolis(myLoopStart,myLoopEnd,temperature);
        for(int i = 0; i<5; i++) {
            MPI_Reduce(&myAverage[i],&totalAverage[i],1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        }
        if(myRank == 0) {
            ising.writeOutput(filename,monteCarloCycles,temperature,totalAverage);
        }
    }
    ising.delteLattice();
    MPI_Finalize();
    return 0;
}
