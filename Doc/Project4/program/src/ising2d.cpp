#include "ising2d.h"

Ising2D::Ising2D() {

}

Ising2D::Ising2D(int spins) {
    nSpin = spins;
    energy = 0;

}

void Ising2D::InitializeLattice() {
    // Initialize lattice with values
    lattice = new int*[nSpin];
    for(int i = 0; i<nSpin;i++) {
        lattice[i] = new int[nSpin];
        for(int j = 0; j<nSpin;j++) {
            lattice[i][j] = 1;
        }
    }
    energy = -2*nSpin*nSpin;
    magneticMoment = nSpin*nSpin;
    //Pseudo lattice containting pointers to the original lattice
    int corner = 0;
    //Initialize pseudo lattice with empty pointers
    pseudoLattice = new int**[nSpin+2];
    for(int i = 0; i<nSpin+2;i++) {
        pseudoLattice[i] = new int*[nSpin+2];
        for(int j = 0; j<nSpin+2;j++) {
            pseudoLattice[i][j] = NULL;
        }
    }
    //Set pointers to lattice
    for(int i = 1; i<nSpin+1;i++) {
        for(int j = 1; j<nSpin+1;j++) {
            pseudoLattice[i][j] = &lattice[i-1][j-1];
        }
    }
    for(int i = 1; i<nSpin+1;i++) {
        pseudoLattice[0][i] = &lattice[nSpin-1][i-1];
        pseudoLattice[nSpin+1][i] = &lattice[0][i-1];
        pseudoLattice[i][0] = &lattice[i-1][nSpin-1];
        pseudoLattice[i][nSpin+1] = &lattice[i-1][0];
    }
    pseudoLattice[0][0] = &corner;
    pseudoLattice[0][nSpin+1] = &corner;
    pseudoLattice[nSpin+1][0] = &corner;
    pseudoLattice[nSpin+1][nSpin+1] = &corner;

//    for(int i = 0; i<nSpin+2;i++) {
//        for(int j = 0; j<nSpin+2;j++) {
//            printf("%i  ", *pseudoLattice[i][j]);
//        }  printf("\n");
//    }
}

void Ising2D::delteLattice(){
//    for(int i = 0; i<nSpin+2;i++) {
//        for(int j = 0; j<nSpin+2;j++) {
//            printf("%i  ", *pseudoLattice[i][j]);
//        }  printf("\n");
//    }
    for(int i = 0; i<nSpin; i++) {
        lattice[i] = NULL;
        delete[] lattice[i];
        }
    for(int i = 0; i<nSpin+2 ; i++) {
        for(int j = 0; j<nSpin+2;j++) {
            pseudoLattice[i][j] = NULL;
            delete[] pseudoLattice[i][j];
        }
        pseudoLattice[i] = NULL;
        delete[] pseudoLattice[i];
    }
    pseudoLattice = NULL;
}

double *Ising2D::Metropolis(int start, int end, double temperature){
    // Initialize the seed and call the Mersienne algo
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // Set up the uniform distribution for x \in [[0, 1]
    std::uniform_real_distribution<double> randomGenerator(0.0,1.0);
    // Set up array for possible energy transitions
    w = new double[17];
    for( int de =-8; de <= 8; de++) w[de+8] = 0;
    for( int de =-8; de <= 8; de+=4) w[de+8] = exp(-de/temperature);

    // Initialize storage variables
    expectationValues = new double[5];
    for( int i=0; i<5; i++) expectationValues[i]=0;

    // Do Monte Carlo calculations
    for (int cycles = start; cycles <= end; cycles++){
      for(int x =1; x < nSpin+1; x++) {
        for (int y= 1; y < nSpin+1; y++){

          // Chose a random spin to flip
          int ix = (int) (randomGenerator(gen)*(double)nSpin)+1;
          int iy = (int) (randomGenerator(gen)*(double)nSpin)+1;

          // Calculate the energy difference of flipping the chosen spin
          int deltaE =  2*(*pseudoLattice[ix][iy])*((*pseudoLattice[ix+1][iy])+(*pseudoLattice[ix-1][iy])+(*pseudoLattice[ix][iy+1])+(*pseudoLattice[ix][iy-1]));
          // Perform the Metropolis criteria
          if ( randomGenerator(gen) <= w[deltaE+8] ) {
            // Flip the spin
            lattice[ix-1][iy-1] *= -1.0;
            // Save new properties
            magneticMoment += (double) 2*(*pseudoLattice[ix][iy]);
            energy += (double) deltaE;
          }
        }
      }

      // Update expectation values  for local node
      expectationValues[0] += energy;
      expectationValues[1] += energy*energy;
      expectationValues[2] += magneticMoment;
      expectationValues[3] += magneticMoment*magneticMoment;
      expectationValues[4] += fabs(magneticMoment);
    }
    return expectationValues;
}

void Ising2D::output(std::string outputFile, int totalMonteCarloCycles, double temperature, double *totalResult) {
  std::ofstream ofile;
  ofile.open(outputFile);
  double norm = 1.0/((double) (totalMonteCarloCycles));  // divided by  number of cycles
  double E_ExpectationValues = totalResult[0]*norm;
  double E2_ExpectationValues = totalResult[1]*norm;
  double M_ExpectationValues = totalResult[2]*norm;
  double M2_ExpectationValues = totalResult[3]*norm;
  double Mabs_ExpectationValues = totalResult[4]*norm;
  // all expectation values are per spin, divide by 1/NSpins/NSpins
  double Evariance = (E2_ExpectationValues- E_ExpectationValues*E_ExpectationValues)/nSpin/nSpin;
  double Mvariance = (M2_ExpectationValues - Mabs_ExpectationValues*Mabs_ExpectationValues)/nSpin/nSpin;
  ofile << setiosflags(std::ios::showpoint | std::ios::uppercase);
  ofile << std::setw(15) << std::setprecision(8) << temperature;
  ofile << std::setw(15) << std::setprecision(8) << E_ExpectationValues/nSpin/nSpin;
  ofile << std::setw(15) << std::setprecision(8) << Evariance/temperature/temperature;
  ofile << std::setw(15) << std::setprecision(8) << M_ExpectationValues/nSpin/nSpin;
  ofile << std::setw(15) << std::setprecision(8) << Mvariance/temperature;
  ofile << std::setw(15) << std::setprecision(8) << Mabs_ExpectationValues/nSpin/nSpin << std::endl;
} // end output function
