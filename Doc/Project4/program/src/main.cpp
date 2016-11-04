/*
   Program to solve the two-dimensional Ising model
   with zero external field and no parallelization
   The coupling constant J is set to J = 1
   Boltzmann's constant = 1, temperature has thus dimension energy
   Metropolis aolgorithm  is used as well as periodic boundary conditions.
   The code needs an output file on the command line and the variables mcs, nspins,
   initial temp, final temp and temp step.
   Run as
   ./executable Outputfile numberof spins number of MC cycles initial temp final temp tempstep
   ./test.x Lattice 100 10000000 2.1 2.4 0.01
   Compile and link as
   c++ -O3 -std=c++11 -Rpass=loop-vectorize -o Ising.x IsingModel.cpp -larmadillo
*/

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <armadillo>
#include <string>
using namespace  std;
using namespace arma;
// output file
ofstream ofile;

// inline function for PeriodicBoundary boundary conditions
inline int periodicBoundary(int i, int limit, int add) {return (i+limit+add) % (limit); }

void InitializeGroundState(int, int **, double&, double&);  // Function to initialise energy and magnetization
void Metropolis(int, long, double, double *);               // The metropolis algorithm including the loop over Monte Carlo cycles
void WriteResultstoFile(double, int, double, double *);        // prints to file the results of the calculations

// Main program begins here

int main(int argc, char* argv[])
{
  string filename;
  int nSpins;
  long monteCarloCycles;
  double initialTemperature, finalTemperature, temperatureStep;
  if (argc <= 6) {
    cout << "Bad Usage: " << argv[0] <<
      " read output file, Number of spins, MC cycles, initial and final temperature and tempurate step" << endl;
    exit(1);
  }
  if (argc > 6) {
    filename=argv[1];
    nSpins = atoi(argv[2]);
    monteCarloCycles = atoi(argv[3]);
    initialTemperature = atof(argv[4]);
    finalTemperature = atof(argv[5]);
    temperatureStep = atof(argv[6]);
  }
  // Declare new file name and add lattice size to file name
  string outputFile = filename;
  string argument = to_string(nSpins);
  outputFile.append(argument);
  ofile.open(outputFile);
  // Start Monte Carlo sampling by looping over the selcted Temperatures
  for (double Temperature = initialTemperature; Temperature <= finalTemperature; Temperature+=temperatureStep){
      double *expectationValues = new double[5];
      for(int i =0;i<5;i++){ expectationValues[i]=0;}
        // Start Monte Carlo computation and get expectation values
      Metropolis(nSpins, monteCarloCycles, Temperature, expectationValues);
      //
      WriteResultstoFile((double) nSpins, monteCarloCycles, Temperature, expectationValues);
  }
  ofile.close();  // close output file
  return 0;
}

// The Monte Carlo part with the Metropolis algo with sweeps over the lattice
void Metropolis(int nSpins, long monteCarloCycles, double temperature, double *expectationValues)
{
  // Initialize the seed and call the Mersienne algo
  std::random_device rd;
  std::mt19937_64 gen(rd());
  // Set up the uniform distribution for x \in [[0, 1]
  std::uniform_real_distribution<double> randomGenerator(0.0,1.0);
  // Initialize the lattice spin values
  int **lattice = new int*[nSpins];
  for(int i=0; i<nSpins ; i++) {
      lattice[i] = new int[nSpins];
      for(int j=0; j<nSpins ; j++) {
          lattice[i][j] = 1;
      }
  }

  //    initialize energy and magnetization
  double energy = 0.;     double magneticMoment = 0.;
  // initialize array for expectation values
  InitializeGroundState(nSpins, lattice, energy, magneticMoment);
  // setup array for possible energy changes
  double *w = new double[17];
  for( int de =-8; de <= 8; de++) w[de+8] = 0;
  for( int de =-8; de <= 8; de+=4) w[de+8] = exp(-de/temperature);
  // Start Monte Carlo cycles
  for (int cycles = 1; cycles <= monteCarloCycles; cycles++){
    // The sweep over the lattice, looping over all spin sites
    for(int x =0; x < nSpins; x++) {
      for (int y= 0; y < nSpins; y++){
    int ix = (int) (randomGenerator(gen)*(double)nSpins);
    int iy = (int) (randomGenerator(gen)*(double)nSpins);
    int deltaE =  2*lattice[ix][iy]*
      (lattice[ix][periodicBoundary(iy,nSpins,-1)]+
       lattice[periodicBoundary(ix,nSpins,-1)][iy] +
       lattice[ix][periodicBoundary(iy,nSpins,1)] +
       lattice[periodicBoundary(ix,nSpins,1)][iy]);
    if ( randomGenerator(gen) <= w[deltaE+8] ) {
      lattice[ix][iy] *= -1.0;  // flip one spin and accept new spin config
      magneticMoment += (double) 2*lattice[ix][iy];
      energy += (double) deltaE;
      }
     }
     }
    // update expectation values  for local node
    expectationValues[0] += energy;
    expectationValues[1] += energy*energy;
    expectationValues[2] += magneticMoment;
    expectationValues[3] += magneticMoment*magneticMoment;
    expectationValues[4] += fabs(magneticMoment);
  }
} // end of Metropolis sampling over spins

// function to initialise energy, spin matrix and magnetization
void InitializeGroundState(int nSpins, int **spinLattice,  double& energy, double& magneticMoment) {
  // setup spin matrix and initial magnetization
  for(int x =0; x < nSpins; x++) {
    for (int y= 0; y < nSpins; y++){
      spinLattice[x][y] = 1; // spin orientation for the ground state
      magneticMoment +=  (double) spinLattice[x][y];
    }
  }
  // setup initial energy
  for(int x =0; x < nSpins; x++) {
    for (int y= 0; y < nSpins; y++){
      energy -=  (double) spinLattice[x][y]*
    (spinLattice[periodicBoundary(x,nSpins,-1)][y] +
     spinLattice[x][periodicBoundary(y,nSpins,-1)]);
    }
  }
}// end function initialise



void WriteResultstoFile(double nSpins, int monteCarloCycles, double temperature, double * expectationValues)
{
  double norm = 1.0/((double) (monteCarloCycles));  // divided by  number of cycles
  double E_ExpectationValues = expectationValues[0]*norm;
  double E2_ExpectationValues = expectationValues[1]*norm;
  double M_ExpectationValues = expectationValues[2]*norm;
  double M2_ExpectationValues = expectationValues[3]*norm;
  double Mabs_ExpectationValues = expectationValues[4]*norm;
  // all expectation values are per spin, divide by 1/NSpins/NSpins
  double Evariance = (E2_ExpectationValues- E_ExpectationValues*E_ExpectationValues)/nSpins/nSpins;
  double Mvariance = (M2_ExpectationValues - Mabs_ExpectationValues*Mabs_ExpectationValues)/nSpins/nSpins;
  ofile << setiosflags(ios::showpoint | ios::uppercase);
  ofile << setw(15) << setprecision(8) << temperature;
  ofile << setw(15) << setprecision(8) << E_ExpectationValues/nSpins/nSpins;
  ofile << setw(15) << setprecision(8) << Evariance/temperature/temperature;
  ofile << setw(15) << setprecision(8) << M_ExpectationValues/nSpins/nSpins;
  ofile << setw(15) << setprecision(8) << Mvariance/temperature;
  ofile << setw(15) << setprecision(8) << Mabs_ExpectationValues/nSpins/nSpins << endl;
} // end output function
