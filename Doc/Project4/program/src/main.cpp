#include <iostream>
#include "matrix.h"
#include "mpi.h"
#include <fstream>
#include "ising2d.h"

using namespace std;

// output file
ofstream ofile;

int main(int argc, char *argv[])
{
    char *outfilename;
    srand(time(NULL));
    long random = rand(); //Random seed
    int my_rank,n_processes;
    Ising2D ising(2);

    //  MPI initializations
    MPI_Init (&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &n_processes);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0 && argc <= 1) {
      cout << "Bad Usage: " << argv[0] <<
        " read output file" << endl;
      exit(1);
    }
    if (my_rank == 0 && argc > 1) {
      outfilename=argv[1];
      ofile.open(outfilename);
    }

    srand(random-my_rank);
    printf( "Running process %d of %d processes\n", my_rank, n_processes);
    ising.InitializeRandomState();
    //ising.InitializeGroundState();

    ising.delteLattice();
    MPI_Finalize();
    ofile.close();
    return 0;
}
