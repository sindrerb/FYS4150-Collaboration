#include "ising2d.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    //Solving task 4b finding MC convergence for 2x2 spins
    long monteCarlo = 10; //Start # MC cicles
    int cicles = 10;
    int N = 3;
    int nSpin = 2;
    for(int i = 1; i <= N; i++){
        string filename = "test";
        cout << i << setw(10) <<monteCarlo << endl;
        for(int j = 1; j <= i; j++){
            monteCarlo = monteCarlo*cicles;
        }

        double *myAverage;
        double temp = 1;
        Ising2D test(nSpin);

        test.InitializeLattice();
        myAverage = test.Metropolis(0,monteCarlo, temp);
        test.output(filename, i, monteCarlo, temp, myAverage);
        test.delteLattice();
        cout << "test nr. " << i << " done." << endl;
    }
}
