#include "mpi.h"
#include "ising2d.h"
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
    int monteCarloCycles;
    double *myAverage = new double[6];
    double *totalAverage = new double[6];
    double initTemp, finalTemp, tempStep;
    double initTime=0, finalTime=0, totalTime=0;

    // Initialize MPI
    MPI_Init (&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    if(myRank ==  0 && argc <= 7) {
        cout << "Bad usage: " << argv[0] << "\n Read:\n Name of output file\n Number of spins\n Initial state (G=ground or R=random)\n Number of samples\n Initial temperature\n Final temperature\n Temperature step\n \n";
        exit(1);
    }
    if(myRank == 0 && argc > 7) {
        filename = argv[1];
        filename.append(argv[2]);
        nSpin = atoi(argv[2]);
        state = *argv[3];
        monteCarloCycles = atol(argv[4]);
        initTemp = atof(argv[5]);
        finalTemp = atof(argv[6]);
        tempStep = atof(argv[7]);
        filename.append("_");
        filename.append(argv[3]);
        filename.append("_");
        filename.append(argv[4]);
        filename.append("_");
        filename.append(argv[5]);
        filename.append("_");
        filename.append(argv[6]);
        filename.append("_");
        filename.append(argv[7]);
        filename.append(".txt");
        cout << "Writes to " << filename << " with state "<<state<<endl;
    }

    // Broadcast common variables to all nodes
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
        ising.initializeOutput(filename,monteCarloCycles);
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
        myAverage = ising.metropolis(myLoopStart,myLoopEnd,temperature);
        for(int i = 0; i<6; i++) {
            MPI_Reduce(&myAverage[i],&totalAverage[i],1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        }
        if(myRank == 0) {
            ising.writeOutput(filename,monteCarloCycles,temperature,totalAverage);
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

    delete[] totalAverage;
    delete[] myAverage;
}
