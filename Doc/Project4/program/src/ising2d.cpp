#include "ising2d.h"

Ising2D::Ising2D() {
    nSpin = 0;
    magneticMoment=0;
    energy = 0;
}

Ising2D::Ising2D(int spins) {
    nSpin = spins;
    magneticMoment=0;
    energy = 0;
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
                printf(" %i ",spin);
            }
            printf("\n");
        }
        magneticMoment = nSpin*nSpin;
        energy = -2*nSpin*nSpin;
        printf("%f\t%f \n",magneticMoment,energy);
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
                printf(" %i ",spin);
            }
            printf("\n");
        }
        printf("%f\t%f \n",magneticMoment,energy);
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
