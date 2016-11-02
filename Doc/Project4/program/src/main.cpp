#include <iostream>
#include "matrix.h"
#include "mpi.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "ising2d.h"

using namespace std;

// output file
ofstream ofile;

void output(int, int, double, double *);

int main(int argc, char *argv[])
{
    char *outfilename;
    srand(time(NULL));
    long random = rand(); //Random seed
    int n_spins,mcs,my_rank,n_processes;
    double total_average[5],initial_temp,final_temp,temp_step;

    //  MPI initializations
    MPI_Init (&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &n_processes);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    if (my_rank == 0 && argc <= 5) {
      cout << "Bad Usage: " << argv[0] <<
        " read output file" << endl;m
      exit(1);
    }
    if (my_rank == 0 && argc > 5) {
      outfilename=argv[1];
      ofile.open(outfilename);
      n_spins = atoi(argv[2]);
      mcs = atoi(argv[3]);
      initial_temp = atof(argv[4]);
      final_temp = atof(argv[5]);
      temp_step = atof(argv[6]);
    }
    Ising2D ising(n_spins);
    double *average = new double[5];

    //Divide cycles over the nodes
    int no_intervalls = mcs/n_processes;
    int myLoopStart = my_rank*no_intervalls + 1;
    int myLoopEnd = (my_rank+1)*no_intervalls;
    if ( (my_rank == n_processes-1) &&( myLoopEnd < mcs) ) myLoopEnd = mcs;

    srand(random-my_rank);

    for ( double temperature = initial_temp; temperature <= final_temp; temperature+=temp_step) {
        ising.generate(myLoopStart,myLoopEnd,temperature);
        average = ising.fetch();
        for(int i = 0; i<5;i++){
            MPI_Reduce(&average[i], &total_average[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        }
        cout << temperature << total_average[0] << endl;
        if(my_rank == 0){
            output(n_spins,mcs,temperature,total_average);
        }
    }
    ofile.close();
    MPI_Finalize();
    return 0;
}

void output(int n_spins, int mcs, double temperature, double *total_average) {
  double norm = 1/((double) (mcs));  // divided by total number of cycles
  double Etotal_average = total_average[0]*norm;
  double E2total_average = total_average[1]*norm;
  double Mtotal_average = total_average[2]*norm;
  double M2total_average = total_average[3]*norm;
  double Mabstotal_average = total_average[4]*norm;
  // all expectation values are per spin, divide by 1/n_spins/n_spins
  double Evariance = (E2total_average- Etotal_average*Etotal_average)/n_spins/n_spins;
  double Mvariance = (M2total_average - Mtotal_average*Mtotal_average)/n_spins/n_spins;
  ofile << setiosflags(ios::showpoint | ios::uppercase);
  ofile << setw(15) << setprecision(8) << temperature;
  ofile << setw(15) << setprecision(8) << Etotal_average/n_spins/n_spins;
  ofile << setw(15) << setprecision(8) << Evariance/temperature/temperature;
  ofile << setw(15) << setprecision(8) << Mtotal_average/n_spins/n_spins;
  ofile << setw(15) << setprecision(8) << Mvariance/temperature;
  ofile << setw(15) << setprecision(8) << Mabstotal_average/n_spins/n_spins << endl;
}
