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

    // Class functions for initsializing systems(<vector>) of satellites
    void createSolarSystem(std::string inputfile);
    void createSatellite(double mass, vec3 position, vec3 velocity);

    // Computational functions
    void shiftAccelerations();
    void clearNewAccelerations();
    void updatePositionsEuler();
    void updateVelocitiesEuler();
    void updatePositionsVerlet();
    void updateVelocitiesVerlet();
    void updateForces();
    void simulate(double finaltime, int iterations, int startIteration, std::string method, std::string outputfile);
    vec3 gravitationalForce(Satellite planetA,Satellite planetB);
    double perihelionAngle (Satellite planet);

    //File handeling functions
    void printHeader(double time, int iterations, std::string outputfile);
    void printPositions(double time,std::string outputfile);
    void printPerihelionAngle (string outputfile);
    //void printPerihelionAngle (Satellite planet, string outputfile);

    // Setters and Getters for member variables
    std::vector<Satellite> satellites() const;
    int numberofsatellites() const;
    void setNumberofsatellites(int numberofsatellites);
    double timeStep() const;
    void setTimeStep(double timeStep);
    double halfTimeStep() const;
    void setHalfTimeStep(double halfTimeStep);
    double halfTimeStepSquared() const;
    void setHalfTimeStepSquared(double halfTimeStepSquared);
    std::string method() const;
    void setMethod(const std::string &method);
    int startIteration() const;
    void setStartIteration(int startIteration);

private:
    // member variables
    std::vector<Satellite> m_satellites;
    std::vector<std::string> m_names;
    std::string m_method;
    int m_numberofsatellites;
    int m_startIteration;
    double m_timeStep;
    double m_halfTimeStep;
    double m_halfTimeStepSquared;
    //double m_perihelionPrevious;
    //double m_perihelionNext;
    double FOUR_PI_SQUARED = 64*atan(1)*atan(1);
    double SPEED_OF_LIGHT = 173*365; //[AU/Yr]
    double PERIHELION_DISTANCE = 0.3075; //[AU]
    double PERIHELION_MAX = 0.3076;

};

#endif // SOLARSYSTEM_H
