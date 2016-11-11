#include "../src/ising2d.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

ofstream ofile;

int main(int argc, char *argv[])
{
    string filebase, filename;
    char state;
    int nSpin;
    int equilibrium;
    double initTemp, finalTemp, tempStep;

    if(argc <= 7) {
        cout << "Bad usage: " << argv[0] << "\n Read:\n Name of output file\n Number of spins\n Initial state (G=ground or R=random)\n Number of samples\n Initial temperature\n Final temperature\n Temperature step\n \n";
        exit(1);
    }
    if(argc > 7) {
        filebase = argv[1];
        filebase.append("_Eq_");
        filebase.append(argv[2]);
        nSpin = atoi(argv[2]);
        state = *argv[3];
        filebase.append("_");
        filebase.append(argv[3]);
        equilibrium = atol(argv[4]);
        initTemp = atof(argv[5]);
        finalTemp = atof(argv[6]);
        tempStep = atof(argv[7]);
        cout << "Writes to " << filebase << " with state "<<state<<endl;
    }

    Ising2D ising(nSpin);

    if(state == 'R'){
        ising.initializeRandomStateLattice();
    } else {
        ising.initializeGroundStateLattice();
    }
    for(double temperature = initTemp; temperature<finalTemp; temperature+= tempStep) {
        filename = filebase + to_string(temperature);
        ising.equilibrium(filename, equilibrium,temperature);
    }

    ising.delteLattice();
    return 0;
}
