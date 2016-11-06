#include "ising2d.h"
#include <string>
#include <iostream>
#include <math.h>
#include "time.h"

using namespace std;

int main()
{
    //Solving task 4b finding MC convergence for 2x2 spins
    long monteCarlo; //Start # MC cicles
    int N = 9;
    int nSpin = 2;
    for(int i = 1; i <= N; i++){
        string filename = "test";

        for(int j = 1; j <= i; j++){
            monteCarlo = pow(10,i);
        }
        cout << "Running test " << i << " with " << monteCarlo << " MC cicles." << endl;
        double *myAverage;
        double temp = 1;
        Ising2D test(nSpin);

        clock_t time;
        time = clock();
        test.InitializeLattice();
        myAverage = test.Metropolis(0,monteCarlo, temp);
        time = clock() - time;
        test.output(time, filename, i, monteCarlo, temp, myAverage);
        test.delteLattice();
        cout << "test nr. " << i << " with " << monteCarlo << " cycles took " << time/1000 << " sek." << endl;
    }
}
