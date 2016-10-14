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
    solarSystem.createSolarSystem("sunEarth.txt");
    solarSystem.simulate(1,1e4,"OUTPUT.txt");
    return 0;
}
