#include "ising2d.h"

Ising2D::Ising2D() {

}

Ising2D::Ising2D(int spins) {
    nSpin = spins;
    energy = 0;
}

void Ising2D::initializeGroundStateLattice() {
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

void Ising2D::initializeRandomStateLattice() {
    // Initialize lattice with values
    lattice = new int*[nSpin];
    int spin;
    for(int i = 0; i<nSpin;i++) {
        lattice[i] = new int[nSpin];
        for(int j = 0; j<nSpin;j++) {
            spin = rand()%2;
            lattice[i][j] = spin*2-1;
        }
    }
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

    energy = 0;
    magneticMoment = 0;
    for(int ix = 1; ix<nSpin+1;ix++) {
        for(int iy = 1; iy<nSpin+1;iy++) {
            energy += 2*(*pseudoLattice[ix][iy])*((*pseudoLattice[ix+1][iy])+(*pseudoLattice[ix-1][iy])+(*pseudoLattice[ix][iy+1])+(*pseudoLattice[ix][iy-1]));
            magneticMoment += (*pseudoLattice[ix][iy]);
        }
    }

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

double *Ising2D::metropolis(int start, int end, double temperature){
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
    int energyDelta;
    for (int cycles = start; cycles <= end; cycles++){
      for(int x =1; x < nSpin+1; x++) {
        for (int y= 1; y < nSpin+1; y++){

          // Chose a random spin to flip
          int ix = (int) (randomGenerator(gen)*(double)nSpin)+1;
          int iy = (int) (randomGenerator(gen)*(double)nSpin)+1;

          // Calculate the energy difference of flipping the chosen spin
          energyDelta =  2*(*pseudoLattice[ix][iy])*((*pseudoLattice[ix+1][iy])+(*pseudoLattice[ix-1][iy])+(*pseudoLattice[ix][iy+1])+(*pseudoLattice[ix][iy-1]));
          // Perform the Metropolis criteria
          if ( randomGenerator(gen) <= w[energyDelta+8] ) {
            // Flip the spin
            lattice[ix-1][iy-1] *= -1.0;
            // Save new properties
            magneticMoment += (double) 2*(*pseudoLattice[ix][iy]);
            energy += (double) energyDelta;
          }
        }
      }

      // Add values to storage for local node
      expectationValues[0] += energy;
      expectationValues[1] += energy*energy;
      expectationValues[2] += magneticMoment;
      expectationValues[3] += magneticMoment*magneticMoment;
      expectationValues[4] += fabs(magneticMoment);
    }
    return expectationValues;
}

int *Ising2D::histogram(std::string outputFile, int start, int end,double temperature) {
    //Write equilibrium grahp to this file
    std::ofstream ofile;
    outputFile += "eq";
    ofile.open(outputFile);
    ofile<<std::setw(15) << "tries";
    ofile<<std::setw(15) << "accepted";
    ofile<<std::setw(15) << "a/t";
    ofile<<std::setw(15) << "energy";
    ofile<<std::setw(15) << "e/t" << std::endl;
    ofile.close();

    // Initialize the seed and call the Mersienne algo
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // Set up the uniform distribution for x \in [[0, 1]
    std::uniform_real_distribution<double> randomGenerator(0.0,1.0);
    // Set up array for possible energy transitions
    w = new double[17];
    for( int de =-8; de <= 8; de++) w[de+8] = 0;
    for( int de =-8; de <= 8; de+=4) w[de+8] = exp(-de/temperature);

    // Initialize histogram
    histogramList = new int[nSpin*nSpin];
    for( int i=0; i<nSpin*nSpin; i++) histogramList[i]=0;
    int energyMax = 2*nSpin*nSpin;
    int histPosition; //Used to add one count in the right position

    //Initialize output counter
    int counterOutput = 0;
    int counterMax = 100;

    // Equilibrium conditions
    double triesAccepted = 0;
    double triesTotal = 0;

    // Do Monte Carlo calculations
    int energyDelta;
    for (int cycles = start; cycles <= end; cycles++){
      for(int x =1; x < nSpin+1; x++) {
        for (int y= 1; y < nSpin+1; y++){

          // Chose a random spin to flip
          int ix = (int) (randomGenerator(gen)*(double)nSpin)+1;
          int iy = (int) (randomGenerator(gen)*(double)nSpin)+1;

          // Calculate the energy difference of flipping the chosen spin
          energyDelta =  2*(*pseudoLattice[ix][iy])*((*pseudoLattice[ix+1][iy])+(*pseudoLattice[ix-1][iy])+(*pseudoLattice[ix][iy+1])+(*pseudoLattice[ix][iy-1]));

          // Perform the Metropolis criteria
          if ( randomGenerator(gen) <= w[energyDelta+8] ) {
            // Flip the spin
            lattice[ix-1][iy-1] *= -1.0;
            // Save new properties
            magneticMoment += (double) 2*(*pseudoLattice[ix][iy]);
            energy += (double) energyDelta;

           // Log the number of accepted tries
            triesAccepted ++;
          }

          // Log the number of tries in total
          triesTotal ++;
      }
    }
      // Add the new energy in a histogram
      if ( cycles > (end-start)/3 ) {
          histPosition = ((int) energy+energyMax)/4;
          histogramList[histPosition] += 1;
      }
      counterOutput++;
      if(counterOutput == counterMax) {
        ofile.open(outputFile,std::ios_base::app);
        ofile<<std::setw(15) << cycles;
        ofile<<std::setw(15) << triesAccepted;
        ofile<<std::setw(15) << ((double) triesAccepted/cycles);
        ofile<<std::setw(15) << energy;
        ofile<<std::setw(15) << energy/triesTotal << std::endl;
        counterOutput = 0;
        ofile.close();
      }
    }
    return histogramList;
}


void Ising2D::initializeOutputHistogram(std::string outputFile,int totalMonteCarloCycles, int equilibriumCycle) {
    outputFile.append("hist");
    std::ofstream ofile;
    ofile.open(outputFile);
    ofile << "Histogram over energy occurence in a lattice with "<<nSpin<<" spins with "<<totalMonteCarloCycles<<" Monte Carlo samples."<< std::endl;
    ofile << "Counting from the "<<equilibriumCycle<<" MC-Cycle, assumed to represent equlibrium."<< std::endl;
    ofile << std::setw(15) << "T";
    ofile << std::setw(15) << "E (J)" << std::endl;
    ofile << std::setw(15) << 0;
    for(int energyCounter = -2*nSpin*nSpin; energyCounter <= 2*nSpin*nSpin; energyCounter+=4) {
        ofile << std::setw(15) << energyCounter;
    }
    ofile << std::endl;
    ofile.close();
}

void Ising2D::writeHistogram(std::string outputFile,double temperature, int *totalHistogram) {
    outputFile.append("hist");
    std::ofstream ofile;
    ofile.open(outputFile, std::ios_base::app);
    ofile << std::setw(15) << temperature;
    for(int i = 0; i <= nSpin*nSpin; i++) {
        ofile << std::setw(15) << totalHistogram[i];
    }
    ofile << std::endl;
    ofile.close();
}


void Ising2D::initializeOutput(std::string outputFile,int totalMonteCarloCycles) {
    std::ofstream ofile;
    ofile.open(outputFile);
    ofile << "Ising model with "<<nSpin<<" spins and "<<totalMonteCarloCycles<<" Monte Carlo samples."<< std::endl;
    ofile << std::setw(15) << "T";
    ofile << std::setw(15) << "E";
    ofile << std::setw(15) << "Cv";
    ofile << std::setw(15) << "M";
    ofile << std::setw(15) << "X";
    ofile << std::setw(15) << "abs(M)";
    ofile << std::setw(15) << "Acceptance rate" << std::endl;
    ofile.close();
}

void Ising2D::writeOutput(std::string outputFile, int totalMonteCarloCycles, double temperature, double *totalResult) {
  std::ofstream ofile;
  ofile.open(outputFile, std::ios_base::app);
  double norm = 1.0/((double) (totalMonteCarloCycles));  // divided by  number of cycles
  double E_ExpectationValues = totalResult[0]*norm;
  double E2_ExpectationValues = totalResult[1]*norm;
  double M_ExpectationValues = totalResult[2]*norm;
  double M2_ExpectationValues = totalResult[3]*norm;
  double Mabs_ExpectationValues = totalResult[4]*norm;
  double acceptanceRate = totalResult[5]*norm;
  // all expectation values are per spin, divide by 1/NSpins/NSpins
  double Evariance = (E2_ExpectationValues- E_ExpectationValues*E_ExpectationValues)/nSpin/nSpin;
  double Mvariance = (M2_ExpectationValues - Mabs_ExpectationValues*Mabs_ExpectationValues)/nSpin/nSpin;
  ofile << setiosflags(std::ios::showpoint | std::ios::uppercase);
  ofile << std::setw(15) << std::setprecision(8) << temperature;
  ofile << std::setw(15) << std::setprecision(8) << E_ExpectationValues/nSpin/nSpin;
  ofile << std::setw(15) << std::setprecision(8) << Evariance/temperature/temperature;
  ofile << std::setw(15) << std::setprecision(8) << M_ExpectationValues/nSpin/nSpin;
  ofile << std::setw(15) << std::setprecision(8) << Mvariance/temperature;
  ofile << std::setw(15) << std::setprecision(8) << Mabs_ExpectationValues/nSpin/nSpin;
  ofile << std::setw(15) << std::setprecision(8) << acceptanceRate/nSpin/nSpin << std::endl;
  ofile.close();
}


//Setters
void Ising2D::setSpin(int spins) {
    nSpin = spins;
}

//Getters
int Ising2D::getSpin() {
    return nSpin;
}
