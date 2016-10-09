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

    SolarSystem solarSystem;    // Create instance of SolarSystem

    solarSystem.createSunEarth();       // Create Sun-Earth system (vecor<Satellites>) from member function in Solarsystem
    vector<Satellite> &sunEarthSatellites = solarSystem.satellites();   // Access satellite objects from vector<Satellites> in SolarSystem
    double distance2 = Satellite::getDistanceBetween(sunEarthSatellites[0],sunEarthSatellites[1]);  // calculate distance between sun(sunEarthSatellites[0]) and earth(sunEarthSatellites[1])
    cout << "distance: "<< distance2 << endl;

    solarSystem.createSolarSystem("solarsystem.txt");           // Create solarSystem objects from file
    vector<Satellite> &solarSystemSatellites = solarSystem.satellites();
    double distance = Satellite::getDistanceBetween(solarSystemSatellites[0],solarSystemSatellites[1]);
    cout << "distance: " << distance <<endl;


//********** TESTING CRAP *************


    //    Satellite &sun = solarSystem.createSatellite( SOLAR_MASS, vec3(0,0,0), vec3(0,0,0) );       // Initializes satelliteObject
    //    Satellite &earth = solarSystem.createSatellite( EARTH_MASS, vec3(10,5,2), vec3(2,4,6) );     // Initializes satelliteObject
    //    double distance = Satellite::getDistanceBetween(sun,earth);
    //    cout << "distance: " << distance << endl;


// Create vector of satellites
    //    vector<Satellite> &satelliteObjects = solarSystem.satellites();     //Gets satelites from SolarSystem.

    //    Satellite &satellite = satelliteObjects[1]; // Set satellite to [n] object created in SolarSystem.

    // Uses Eulers method to find next position for satellite Object[n]
    //    satellite.setSatellitePosition(NumericalSolver::solveEuler(satellite.getSatellitePosition(), satellite.getSatelliteVelocity(), stepLength) );

//    //Print result for satelliteObject[n]
    //    cout << satellite.getSatelliteMass() << "\n"
    //         << satellite.getSatellitePosition() << "\n"
    //         << satellite.getSatelliteVelocity() << endl;
    //    cout << sun.getSatellitePosition() << endl;


 //EULER TEST
    //    double someStepLength = 2;
    //    vec3 eulerTestVector1(2,3,4);
    //    vec3 eulerTestVector2(4,3,2);
    //    vec3 resultFromEuler;
    //    resultFromEuler = numericalSolver.solveEuler( eulerTestVector1, eulerTestVector2, someStepLength);
    //    cout << resultFromEuler << endl;

    return 0;
}
