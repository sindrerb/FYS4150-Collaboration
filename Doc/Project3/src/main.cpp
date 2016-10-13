#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
//#include "matrix.h"
#include "vec3.h"
#include "solarsystem.h"
#include "satellite.h"
#include "numericalsolver.h"

using namespace std;

int main(){

    SolarSystem solarSystem;    // Create instance of SolarSystem
    solarSystem.createSolarSystem("solarsystem.txt");
//    solarSystem.simulate(10,1000,"OUTPUT.txt");
    vector<Satellite> &satellites = solarSystem.g_satellites;
    Satellite &sun = satellites[0];
    double sunmass = sun.mass();
    cout << sunmass << endl;
    cout << "balle" << endl;
    cout << 2*1e30<< endl;

    return 0;
}

