#include "solarsystem.h"
#include "satellite.h"

SolarSystem::SolarSystem() {

}

Satellite& SolarSystem::createSatellite(double mass, vec3 position, vec3 velocity) {
    m_satellites.push_back( Satellite(mass, position, velocity) );
    return m_satellites.back();
}

Satellite &SolarSystem::createSunEarth() {
    int NUMBER_OF_ITERATIONS = 100;
    double START_TIME = 0;
    double END_TIME = 10;
    double stepLength = (END_TIME - START_TIME)/NUMBER_OF_ITERATIONS;
    double SOLAR_MASS = 2 * exp(30);
    double EARTH_MASS = 6 * exp(24);
    Satellite &sun = SolarSystem::createSatellite( SOLAR_MASS, vec3(0,0,0), vec3(0,0,0) );       // Initializes satelliteObject
    Satellite &earth = SolarSystem::createSatellite( EARTH_MASS, vec3(10,5,2), vec3(2,4,6) );     // Initializes satelliteObject
}

std::vector<Satellite> &SolarSystem::satellites() {
    return m_satellites;
}
