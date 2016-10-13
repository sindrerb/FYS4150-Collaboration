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

    // Class functions for initsializing systems(<vector>) of satellites
    Satellite &createSunEarth();
    Satellite &createSolarSystem(std::string inputfile);

    //File handeling
    void printHeader(double time, int iterations, std::string outputfile);
    void printPositions(double time,std::string outputfile);

    //Evolve the system
    void simulate(double finaltime, int iterations, std::string outputfile);

    // Calculate energy of the system
    void resetForces();
    void calculateForces();
    void calculateEnergies();

    //Global variables
    double g_kineticEnergy;
    double g_potentialEnergy;
    vec3 angularMomentum;
    std::vector<Satellite> g_satellites;

private:
    // member variables
    std::vector<Satellite> m_satellites;
    std::vector<std::string> m_names;
    double SOLAR_MASS = 1000;

};

#endif // SOLARSYSTEM_H
