#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "matrix.h"
#include "vec3.h"
#include "solarsystem.h"
#include "satellite.h"
using namespace std;

int main(){

    int NUMBER_OF_ITERATIONS = 1000;
    double START_TIME = 0;
    double END_TIME = 100;
    int stepLength = (END_TIME - START_TIME)/NUMBER_OF_ITERATIONS;
    double SOLAR_MASS = 1000;
    double EARTH_MASS = 10;
    SolarSystem solarSystem;

    Satellite &sun = solarSystem.createSatellite( SOLAR_MASS, vec3(0,0,0), vec3(0,0,0) ); // Initializes satelliteObject
    Satellite &earth = solarSystem.createSatellite( EARTH_MASS, vec3(1,2,3), vec3(2,4,6) ); // Initializes satelliteObject
    vector<Satellite> &satelliteObjects = solarSystem.satellites();

    Satellite &satellite = satelliteObjects[1]; // Set satellite to [n] object created in SolarSystem.

    cout << satellite.satelliteMass << "\n"
         << satellite.satellitePosition << "\n"
         << satellite.satelliteVelocity << endl;
    return 0;
}
