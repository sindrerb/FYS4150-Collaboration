#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "matrix.h"
#include "vec3.h"
#include "solarsystem.h"
#include "satellite.h"
#include "numericalsolver.h"
using namespace std;

int main(){

    int NUMBER_OF_ITERATIONS = 100;
    double START_TIME = 0;
    double END_TIME = 10;
    double stepLength = (END_TIME - START_TIME)/NUMBER_OF_ITERATIONS;
    double SOLAR_MASS = 1000;
    double EARTH_MASS = 10;

    SolarSystem solarSystem;

    Satellite &sun = solarSystem.createSatellite( SOLAR_MASS, vec3(0,0,0), vec3(0,0,0) );       // Initializes satelliteObject
    Satellite &earth = solarSystem.createSatellite( EARTH_MASS, vec3(1,2,3), vec3(2,4,6) );     // Initializes satelliteObject

    vector<Satellite> &satelliteObjects = solarSystem.satellites();     //Gets satelites from SolarSystem.

    Satellite &satellite = satelliteObjects[1]; // Set satellite to [n] object created in SolarSystem.

    NumericalSolver numericalSolver;

    // Uses Eulers method to find next position for satellite Object[n]
    satellite.setSatellitePosition(numericalSolver.solveEuler(satellite.satellitePosition, satellite.satelliteVelocity, stepLength) );

    //Print result for satelliteObject[n]
    cout << satellite.satelliteMass << "\n"
         << satellite.satellitePosition << "\n"
         << satellite.satelliteVelocity << endl;

//EULER TEST
    //    double someStepLength = 2;
    //    vec3 eulerTestVector1(2,3,4);
    //    vec3 eulerTestVector2(4,3,2);
    //    vec3 resultFromEuler;
    //    resultFromEuler = numericalSolver.solveEuler( eulerTestVector1, eulerTestVector2, someStepLength);
    //    cout << resultFromEuler << endl;

    return 0;
}
