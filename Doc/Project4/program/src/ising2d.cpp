#include "ising2d.h"



Ising2D::Ising2D() {
    m_nSpin=0;
    **m_lattice = 0;
    ***m_pseudoLattice = 0;
    *m_w = 0;
    *m_expectationValues = 0;
    *m_histogramList = 0;
    m_energy = 0;
    m_magneticMoment = 0;
}

Ising2D::Ising2D(int spins) {
    m_nSpin = spins;
    m_energy = 0;
}

void Ising2D::initializeGroundStateLattice() {
    // Initialize lattice with values
    m_lattice = new int*[m_nSpin];
    for(int i = 0; i<m_nSpin;i++) {
        m_lattice[i] = new int[m_nSpin];
        for(int j = 0; j<m_nSpin;j++) {
            m_lattice[i][j] = 1;
        }
    }
    m_energy = -2*m_nSpin*m_nSpin;
    m_magneticMoment = m_nSpin*m_nSpin;
    //Pseudo lattice containting pointers to the original lattice
    int corner = 0;
    //Initialize pseudo lattice with empty pointers
    m_pseudoLattice = new int**[m_nSpin+2];
    for(int i = 0; i<m_nSpin+2;i++) {
        m_pseudoLattice[i] = new int*[m_nSpin+2];
        for(int j = 0; j<m_nSpin+2;j++) {
            m_pseudoLattice[i][j] = NULL;
        }
    }
    //Set pointers to lattice
    for(int i = 1; i<m_nSpin+1;i++) {
        for(int j = 1; j<m_nSpin+1;j++) {
            m_pseudoLattice[i][j] = &m_lattice[i-1][j-1];
        }
    }
    for(int i = 1; i<m_nSpin+1;i++) {
        m_pseudoLattice[0][i] = &m_lattice[m_nSpin-1][i-1];
        m_pseudoLattice[m_nSpin+1][i] = &m_lattice[0][i-1];
        m_pseudoLattice[i][0] = &m_lattice[i-1][m_nSpin-1];
        m_pseudoLattice[i][m_nSpin+1] = &m_lattice[i-1][0];
    }
    m_pseudoLattice[0][0] = &corner;
    m_pseudoLattice[0][m_nSpin+1] = &corner;
    m_pseudoLattice[m_nSpin+1][0] = &corner;
    m_pseudoLattice[m_nSpin+1][m_nSpin+1] = &corner;

//    for(int i = 0; i<nSpin+2;i++) {
//        for(int j = 0; j<nSpin+2;j++) {
//            printf("%i  ", *pseudoLattice[i][j]);
//        }  printf("\n");
//    }
}

void Ising2D::initializeRandomStateLattice() {
    // Initialize lattice with values
    m_lattice = new int*[m_nSpin];
    int spin;
    for(int i = 0; i<m_nSpin;i++) {
        m_lattice[i] = new int[m_nSpin];
        for(int j = 0; j<m_nSpin;j++) {
            spin = rand()%2;
            m_lattice[i][j] = spin*2-1;
        }
    }
    //Pseudo lattice containting pointers to the original lattice
    int corner = 0;
    //Initialize pseudo lattice with empty pointers
    m_pseudoLattice = new int**[m_nSpin+2];
    for(int i = 0; i<m_nSpin+2;i++) {
        m_pseudoLattice[i] = new int*[m_nSpin+2];
        for(int j = 0; j<m_nSpin+2;j++) {
            m_pseudoLattice[i][j] = NULL;
        }
    }
    //Set pointers to lattice
    for(int i = 1; i<m_nSpin+1;i++) {
        for(int j = 1; j<m_nSpin+1;j++) {
            m_pseudoLattice[i][j] = &m_lattice[i-1][j-1];
        }
    }
    for(int i = 1; i<m_nSpin+1;i++) {
        m_pseudoLattice[0][i] = &m_lattice[m_nSpin-1][i-1];
        m_pseudoLattice[m_nSpin+1][i] = &m_lattice[0][i-1];
        m_pseudoLattice[i][0] = &m_lattice[i-1][m_nSpin-1];
        m_pseudoLattice[i][m_nSpin+1] = &m_lattice[i-1][0];
    }
    m_pseudoLattice[0][0] = &corner;
    m_pseudoLattice[0][m_nSpin+1] = &corner;
    m_pseudoLattice[m_nSpin+1][0] = &corner;
    m_pseudoLattice[m_nSpin+1][m_nSpin+1] = &corner;

    m_energy = 0;
    m_magneticMoment = 0;
    for(int ix = 1; ix<m_nSpin+1;ix++) {
        for(int iy = 1; iy<m_nSpin+1;iy++) {
            m_energy += 2*(*m_pseudoLattice[ix][iy])*((*m_pseudoLattice[ix+1][iy])+(*m_pseudoLattice[ix-1][iy])+(*m_pseudoLattice[ix][iy+1])+(*m_pseudoLattice[ix][iy-1]));
            m_magneticMoment += (*m_pseudoLattice[ix][iy]);
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
    for(int i = 0; i<m_nSpin; i++) {
        m_lattice[i] = NULL;
        delete[] m_lattice[i];
        }
    for(int i = 0; i<m_nSpin+2 ; i++) {
        for(int j = 0; j<m_nSpin+2;j++) {
            m_pseudoLattice[i][j] = NULL;
            delete[] m_pseudoLattice[i][j];
        }
        m_pseudoLattice[i] = NULL;
        delete[] m_pseudoLattice[i];
    }
    m_pseudoLattice = NULL;
}

double *Ising2D::metropolis(int start, int end, double temperature){
    // Initialize the seed and call the Mersienne algo
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // Set up the uniform distribution for x \in [[0, 1]
    std::uniform_real_distribution<double> randomGenerator(0.0,1.0);
    // Set up array for possible energy transitions
    m_w = new double[17];
    for( int de =-8; de <= 8; de++) m_w[de+8] = 0;
    for( int de =-8; de <= 8; de+=4) m_w[de+8] = exp(-de/temperature);

    // Initialize storage variables
    m_expectationValues = new double[5];
    for( int i=0; i<5; i++) m_expectationValues[i]=0;



    // Do Monte Carlo calculations
    int energyDelta;
    for (int cycles = start; cycles <= end; cycles++){
      for(int x =1; x < m_nSpin+1; x++) {
        for (int y= 1; y < m_nSpin+1; y++){

          // Chose a random spin to flip
          int ix = (int) (randomGenerator(gen)*(double)m_nSpin)+1;
          int iy = (int) (randomGenerator(gen)*(double)m_nSpin)+1;

          // Calculate the energy difference of flipping the chosen spin
          energyDelta =  2*(*m_pseudoLattice[ix][iy])*((*m_pseudoLattice[ix+1][iy])+(*m_pseudoLattice[ix-1][iy])+(*m_pseudoLattice[ix][iy+1])+(*m_pseudoLattice[ix][iy-1]));
          // Perform the Metropolis criteria
          if ( randomGenerator(gen) <= m_w[energyDelta+8] ) {
            // Flip the spin
            m_lattice[ix-1][iy-1] *= -1.0;
            // Save new properties
            m_magneticMoment += (double) 2*(*m_pseudoLattice[ix][iy]);
            m_energy += (double) energyDelta;
          }
        }
      }

      // Add values to storage for local node
      m_expectationValues[0] += m_energy;
      m_expectationValues[1] += m_energy*m_energy;
      m_expectationValues[2] += m_magneticMoment;
      m_expectationValues[3] += m_magneticMoment*m_magneticMoment;
      m_expectationValues[4] += fabs(m_magneticMoment);
    }
    return m_expectationValues;
}

int *Ising2D::histogram(std::string outputFile, int start, int end, double temperature) {
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
    m_w = new double[17];
    for( int de =-8; de <= 8; de++) m_w[de+8] = 0;
    for( int de =-8; de <= 8; de+=4) m_w[de+8] = exp(-de/temperature);

    // Initialize histogram
    m_histogramList = new int[m_nSpin*m_nSpin];
    for( int i=0; i<m_nSpin*m_nSpin; i++) m_histogramList[i]=0;
    int energyMax = 2*m_nSpin*m_nSpin;
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
      for(int x =1; x < m_nSpin+1; x++) {
        for (int y= 1; y < m_nSpin+1; y++){

          // Chose a random spin to flip
          int ix = (int) (randomGenerator(gen)*(double)m_nSpin)+1;
          int iy = (int) (randomGenerator(gen)*(double)m_nSpin)+1;

          // Calculate the energy difference of flipping the chosen spin
          energyDelta =  2*(*m_pseudoLattice[ix][iy])*((*m_pseudoLattice[ix+1][iy])+(*m_pseudoLattice[ix-1][iy])+(*m_pseudoLattice[ix][iy+1])+(*m_pseudoLattice[ix][iy-1]));

          // Perform the Metropolis criteria
          if ( randomGenerator(gen) <= m_w[energyDelta+8] ) {
            // Flip the spin
            m_lattice[ix-1][iy-1] *= -1.0;
            // Save new properties
            m_magneticMoment += (double) 2*(*m_pseudoLattice[ix][iy]);
            m_energy += (double) energyDelta;

           // Log the number of accepted tries
            triesAccepted ++;
          }

          // Log the number of tries in total
          triesTotal ++;

          // Add the new energy in a histogram
          histPosition = (m_energy+energyMax)/4;
          m_histogramList[histPosition] ++;
        }
      }
      counterOutput++;
      if(counterOutput == counterMax) {
        ofile.open(outputFile,std::ios_base::app);
        ofile<<std::setw(15) << triesTotal; //DET ER FEIL HER!!
        ofile<<std::setw(15) << triesAccepted;
        ofile<<std::setw(15) << ((double) triesAccepted/triesTotal);
        ofile<<std::setw(15) << m_energy;
        ofile<<std::setw(15) << m_energy/triesTotal << std::endl;
        counterOutput = 0;
        ofile.close();
      }
    }
    return m_histogramList;
}


void Ising2D::initializeOutputHistogram(std::string outputFile,int totalMonteCarloCycles, int equilibriumCycle) {
    outputFile.append("hist");
    std::ofstream ofile;
    ofile.open(outputFile);
    ofile << "Histogram over energy occurence in a lattice with "<<m_nSpin<<" spins with "<<totalMonteCarloCycles<<" Monte Carlo samples."<< std::endl;
    ofile << "Counting from the "<<equilibriumCycle<<" MC-Cycle, assumed to represent equlibrium."<< std::endl;
    ofile << std::setw(15) << "T";
    ofile << std::setw(15) << "E (J)" << std::endl;
    ofile << std::setw(15) << 0;
    for(int energyCounter = -2*m_nSpin*m_nSpin; energyCounter <= 2*m_nSpin*m_nSpin; energyCounter+=4) {
        ofile << std::setw(15) << energyCounter;
    }
    ofile << std::endl;
    ofile.close();
}

void Ising2D::writeHistogram(std::string outputFile,int temperature, int *totalHistogram) {
    outputFile.append("hist");
    std::ofstream ofile;
    ofile.open(outputFile, std::ios_base::app);
    ofile << std::setw(15) << temperature;
    for(int i = 0; i <= m_nSpin*m_nSpin; i++) {
        ofile << std::setw(15) << totalHistogram[i];
    }
    ofile << std::endl;
    ofile.close();
}


void Ising2D::initializeOutput(std::string outputFile,int totalMonteCarloCycles) {
    std::ofstream ofile;
    ofile.open(outputFile);
    ofile << "Ising model with "<<m_nSpin<<" spins and "<<totalMonteCarloCycles<<" Monte Carlo samples."<< std::endl;
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
  double Evariance = (E2_ExpectationValues- E_ExpectationValues*E_ExpectationValues)/m_nSpin/m_nSpin;
  double Mvariance = (M2_ExpectationValues - Mabs_ExpectationValues*Mabs_ExpectationValues)/m_nSpin/m_nSpin;
  ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
  ofile << std::setw(15) << std::setprecision(8) << temperature;
  ofile << std::setw(15) << std::setprecision(8) << E_ExpectationValues/m_nSpin/m_nSpin;
  ofile << std::setw(15) << std::setprecision(8) << Evariance/temperature/temperature;
  ofile << std::setw(15) << std::setprecision(8) << M_ExpectationValues/m_nSpin/m_nSpin;
  ofile << std::setw(15) << std::setprecision(8) << Mvariance/temperature;
  ofile << std::setw(15) << std::setprecision(8) << Mabs_ExpectationValues/m_nSpin/m_nSpin;
  ofile << std::setw(15) << std::setprecision(8) << acceptanceRate/m_nSpin/m_nSpin << std::endl;
  ofile.close();
}


//Setters
void Ising2D::setSpin(int spins) {
    m_nSpin = spins;
}

//Getters
int Ising2D::getSpin() {
    return m_nSpin;
}

int **Ising2D::getLattice() const {
    return m_lattice;
}

