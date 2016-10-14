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
    void createSolarSystem(std::string inputfile);

    //File handeling
    void printHeader(double time, int iterations, std::string outputfile);
    void printPositions(double time,std::string outputfile);

    //Interactions
    void shiftAccelerations();
    void clearNewAccelerations();
    void updatePositions();
    void updateVelocities();
    void updateForces();

    vec3 gravitationalForce(Satellite planetA,Satellite planetB);

    //Evolve the system
    void simulate(double finaltime, int iterations, std::string outputfile);


private:
    // member variables
    std::vector<Satellite> m_satellites;
    std::vector<std::string> m_names;
    int m_numberofsatellites;
    double m_timeStep;
    double m_timeStepSquared = m_timeStep*m_timeStep;
    double FOUR_PI_SQUARED = 64*atan(1)*atan(1);

};

#endif // SOLARSYSTEM_H
