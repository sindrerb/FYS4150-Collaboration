#include "solarsystem.h"
#include "satellite.h"
#include <iostream>
#include <string>
#include <fstream>


SolarSystem::SolarSystem() {
    m_satellites.empty();
}

Satellite& SolarSystem::createSatellite(double mass, vec3 position, vec3 velocity) {
    m_satellites.push_back( Satellite(mass, position, velocity) );
    return m_satellites.back();
}

Satellite &SolarSystem::createSunEarth() {

    SolarSystem::m_satellites.clear();  // Clear m_satellites (vector of Satellites)

    // Declare initial values (the hard way)
    int NUMBER_OF_ITERATIONS = 100;
    double START_TIME = 0;
    double END_TIME = 10;
    double stepLength = (END_TIME - START_TIME)/NUMBER_OF_ITERATIONS;
    double SOLAR_MASS = 2 * exp(30);
    double EARTH_MASS = 6 * exp(24);

    Satellite &sun = SolarSystem::createSatellite( SOLAR_MASS, vec3(0,0,0), vec3(0,0,0) );       // Initializes satelliteObject
    Satellite &earth = SolarSystem::createSatellite( EARTH_MASS, vec3(10,5,2), vec3(2,4,6) );     // Initializes satelliteObject
}

Satellite &SolarSystem::createSolarSystem(std::string fileName) {
    SolarSystem::m_satellites.clear();  // Clear m_satellites (vector of Satellites)

    // Delcare inital values from file
    std::fstream myfile(fileName , std::ios_base::in);
    std::string name;
    double mass , massEXP, posX, posY, posZ, veloX, veloY, veloZ;
    while (myfile >> name >> mass >> massEXP >> posX >> posY >> posZ >> veloX >> veloY >> veloZ) {
        Satellite &name = SolarSystem::createSatellite( mass*exp(massEXP), vec3(posX,posY,posZ), vec3(veloX,veloY,veloZ));
    }
}

std::vector<Satellite> &SolarSystem::satellites() {
    return m_satellites;
}
