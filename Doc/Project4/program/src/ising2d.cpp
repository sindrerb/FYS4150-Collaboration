#include "ising2d.h"

Ising2D::Ising2D() {
    nSpin = 0;
    magneticMoment=0;
    energy = 0;
    for( int i = 0; i < 5; i++) average[i] = 0.;
}

Ising2D::Ising2D(int spins) {
    nSpin = spins;
    magneticMoment=0;
    energy = 0;
    for( int i = 0; i < 5; i++) average[i] = 0.;
}

void Ising2D::InitializeGroundState() {
    if(nSpin>0){
        int spin;
        lattice = new int*[nSpin];
        for(int i = 0;i<nSpin;i++){
            spin = 1;
            lattice[i] = new int[nSpin];
            for(int j = 0;j<nSpin;j++){
                lattice[i][j] = spin;
                //printf(" %i ",spin); //Just for debug
            }
            //printf("\n"); //Just for debug
        }
        magneticMoment = nSpin*nSpin;
        energy = -2*nSpin*nSpin;
        //printf("%f\t%f \n",magneticMoment,energy); //Just for debug
    } else {
        printf("Bad usage of InitializeGroundState, number of spin is zero or negative.");
    }
}

void Ising2D::InitializeRandomState() {
    //spinLattice.setOnes(nSpin,nSpin);
    int spin;
    if(nSpin>0){
        lattice = new int*[nSpin];
        for(int i = 0;i<nSpin;i++){
            lattice[i] = new int[nSpin];
            for(int j = 0;j<nSpin;j++){
                spin = rand()%2;
                spin = spin*2-1;
                lattice[i][j] = spin;
                magneticMoment += spin;
                //printf(" %i ",spin); //Just for debug
            }
            //printf("\n"); //Just for debug
        }
        //printf("---------\n"); //Just for debug
        for(int i = 0;i<nSpin;i++){
            for(int j = 0;j<nSpin;j++){
                energy -= lattice[i][j]*(lattice[periodic(i,nSpin,-1)][j]+lattice[i][periodic(j,nSpin,-1)]);
            }
            //printf("\n");
        }
        //printf("M=%f\t E=%f \n",magneticMoment,energy); //Just for debug
    } else {
        printf("Bad usage of InitializeRandomState, number of spin is zero or negative.");
    }
}

void Ising2D::delteLattice(){
    if(nSpin>0){
        for (int i = 0; i < nSpin; i++) {
            delete[] lattice[i];
        }
        delete[] lattice;
        lattice = NULL;
    }
}

void Ising2D::generate(int start, int end, double temperature){
    //Initialize and precalculate probabilities
    for( int de =-8; de <= 8; de++) w[de+8] = 0;
    for( int de =-8; de <= 8; de+=4) {
        printf("%f   ",exp(-de/temperature));
        w[de+8] = exp(-de/temperature);
    }
    printf("\n");

    //Initialize average
    for( int i = 0; i < 5; i++) average[i] = 0.0;

    for (int cycles = start; cycles <= end; cycles++){
        //Initialize energy and magnetic moment for each cycle
        energy = 0;
        magneticMoment = 0;
        InitializeGroundState();
        Metropolis();
        delteLattice();
        //Update average values locally
        average[0] += energy;
        average[1] += energy*energy;
        average[2] += magneticMoment;
        average[3] += magneticMoment*magneticMoment;
        average[4] += fabs(magneticMoment);
        //printf("E:%f E2:%f M:%f M2:%f abs(M):%f \n",average[0],average[1],average[2],average[3],average[4]);
    }

}

double *Ising2D::fetch(){
    return average;
}

void Ising2D::Metropolis(){
    if(nSpin>0){
        int deltaE, rand_i,rand_j;
        int counter = 0;
        for(int i = 0;i<nSpin;i++){
            for(int j = 0;j<nSpin;j++){
                rand_i = (int) (rand()%nSpin);
                rand_j = (int) (rand()%nSpin);
                deltaE =  2*lattice[rand_i][rand_j]*
                     (lattice[rand_i][periodic(rand_j,nSpin,-1)]+
                     lattice[periodic(rand_i,nSpin,-1)][rand_j] +
                     lattice[rand_i][periodic(rand_j,nSpin,1)] +
                     lattice[periodic(rand_i,nSpin,1)][rand_j]);

                printf("dE=%i, P:%.8f  <= w: %f \n",deltaE,(rand()%nSpin)/nSpin),(w[deltaE+8]);
                if ( (double) (rand()%nSpin)/nSpin <= w[deltaE+8] ) {
                    lattice[rand_i][rand_j] *= -1;  // flip one spin and accept new spin config
                    magneticMoment += (double) 2*lattice[rand_i][rand_j];
                    energy += (double) fabs(deltaE);
                }
                //printf("C:%i  ,E:%f \n",counter,energy);
                //counter++;
            }
        }
    } else {
        printf("Bad usage of Metropolis, number of spin is zero or negative.");
    }
}

