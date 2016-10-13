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


private:
    // member variables
    std::vector<Satellite> m_satellites;
    std::vector<std::string> m_names;

};

#endif // SOLARSYSTEM_H
