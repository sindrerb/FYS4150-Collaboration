#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <iostream>
#include "vec3.h"
#include "satellite.h"
#include "matrix.h"

class SolarSystem
{
public:
    // Constructors
    SolarSystem();
    Satellite &createSatellite(double mass, vec3 position, vec3 velocity);

    // Create vecor array of satellite objects
    std::vector<Satellite> &satellites();

    // Class functions for initsializing systems(<vector>) of satellites
    Satellite &createSunEarth();
    Satellite &createSolarSystem(std::string fileName);


    //Evolve the system
    void simulate(int N);

private:
    // member variables
    std::vector<Satellite> m_satellites;

};

#endif // SOLARSYSTEM_H
