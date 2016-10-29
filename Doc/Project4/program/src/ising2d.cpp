#include "ising2d.h"

Ising2D::Ising2D()
{

}

void Ising2D::InitializeGroundState(){
    //spinLattice.setOnes(nSpin,nSpin);
    magneticMoment = nSpin*nSpin;
    energy = -2*nSpin*nSpin;
}

void Ising2D::InitializeRandomState(){
    //spinLattice.setOnes(nSpin,nSpin);
    int spin;
    for(int i = 0;i<nSpin;i++){
        for(int j = 0;j<nSpin;j++){
            spin = 1;
            //spinLattice.setElement(i,j,spin);
            magneticMoment = nSpin*nSpin;
        }
    }
}
