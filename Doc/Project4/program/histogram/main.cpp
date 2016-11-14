#include "mpi.h"
#include "../src/ising2d.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

ofstream ofile;

int main(int argc, char *argv[])
{
    string filename;
    char state;
    int numprocs, myRank, nSpin;
    int monteCarloCycles, equilibrium;
    double initTemp, finalTemp, tempStep;
    double initTime=0, finalTime=0, totalTime=0;

    // Initialize MPI
    MPI_Init (&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    if(myRank ==  0 && argc <= 8) {
        cout << "Bad usage: " << argv[0] << "\n Read:\n Name of output file\n Number of spins\n Initial state (G=ground or R=random)\n Number of samples\n Equilibrium time (cycles)\n Initial temperature\n Final temperature\n Temperature step\n \n";
        exit(1);
    }
    if(myRank == 0 && argc > 8) {
        filename = argv[1];
        filename.append(argv[2]);
        nSpin = atoi(argv[2]);
        state = *argv[3];
        monteCarloCycles = atoi(argv[4]);
        equilibrium = atoi(argv[5]);
        initTemp = atof(argv[6]);
        finalTemp = atof(argv[7]);
        tempStep = atof(argv[8]);
        cout << "Writes to " << filename << " with state "<<state<<endl;
    }
    unsigned long *myHistogram = new unsigned long[nSpin*nSpin];
    unsigned long *totalHistogram = new unsigned long[nSpin*nSpin];

    // Broadcast common variables to all nodes
    MPI_Bcast (&myHistogram, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast (&totalHistogram, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Bcast (&monteCarloCycles, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast (&state, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
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
        initTime = MPI_Wtime();
        ising.initializeOutputHistogram(filename,monteCarloCycles,0.25*monteCarloCycles);
    }
    if(state == 'R'){
        ising.initializeRandomStateLattice();
    } else {
        ising.initializeGroundStateLattice();
        if(myRank == 0 && state != 'G'){
            cout << "Did not recognize "<<state<<" as an initial state, running with ground state."<<endl;
        }
    }
    for(double temperature = initTemp; temperature<finalTemp; temperature+= tempStep) {
        myHistogram = ising.histogram(filename, myLoopStart,myLoopEnd, temperature);
        for(int i = 0; i<nSpin*nSpin; i++) {
            MPI_Reduce(&myHistogram[i],&totalHistogram[i],1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        }
        if(myRank == 0) {
            ising.writeHistogram(filename,temperature,totalHistogram);
        }
    }
    if(myRank == 0) {
        finalTime = MPI_Wtime();
        totalTime = finalTime-initTime;
        cout << "Computed in "<<totalTime<<" seconds, using "<<numprocs<<" processes."<<endl;
    }
    ising.delteLattice();
    MPI_Finalize();
    return 0;
}
