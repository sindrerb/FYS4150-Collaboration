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
                printf(" %i ",spin); //Just for debug
            }
            printf("\n"); //Just for debug
        }
        magneticMoment = nSpin*nSpin;
        energy = -2*nSpin*nSpin;
        printf("%f\t%f \n",magneticMoment,energy); //Just for debug
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
                printf(" %i ",spin); //Just for debug
            }
            printf("\n"); //Just for debug
        }
        printf("---------\n"); //Just for debug
        energy = 0;
        for(int i = 0;i<nSpin;i++){
            for(int j = 0;j<nSpin;j++){
                energy -= lattice[i][j]*(lattice[periodic(i,nSpin,-1)][j]+lattice[i][periodic(j,nSpin,-1)]);
            }
            printf("\n");
        }
        printf("M=%f\t E=%f \n",magneticMoment,energy); //Just for debug
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
