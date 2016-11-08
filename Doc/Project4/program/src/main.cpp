#include "ising2d.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    string filename = "test3";
    int nSpin = 20;
    long monteCarlo = 10000;
    double *hist = new double[2*nSpin*nSpin];
    double *tothist = new double[2*nSpin*nSpin];
    double temp = 2;

    Ising2D test(nSpin);

    test.InitializeLattice();
    hist = test.histogram(monteCarlo,temp);
    for(int i = 0; i<2*nSpin*nSpin;i++) {
        cout << hist[i] << " ";
    }
    test.output(filename,monteCarlo,temp,hist);
    test.delteLattice();
}
