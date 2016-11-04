#include "ising2d.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    string filename = "test3";
    int nSpin = 2;
    long monteCarlo = 100000000;
    double *myAverage;
    double temp = 1;

    Ising2D test(nSpin);

    test.InitializeLattice();
    myAverage = test.Metropolis(0,monteCarlo,temp);
    test.output(filename,monteCarlo,temp,myAverage);
    test.delteLattice();
}
