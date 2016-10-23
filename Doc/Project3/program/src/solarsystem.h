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
    void calculateEnergies();
    void calculateTotalEnergy();
    void calculateCenterOfMass();
    void calculateAngularMomentum();
    void findPerihelionPosition();
    vec3 gravitationalForce(Satellite planetA,Satellite planetB);

    //File handeling functions
    void printHeader(double time, int iterations, std::string outputfile);
    void printPositions(double time,std::string outputfile);
    void printPerihelionAngleToFile(string outputfile);

    // Getters
    std::vector<Satellite> &satellites();

    std::string method() const;
    int numberofsatellites() const;
    int startIteration() const;
    double timeStep() const;
    double halfTimeStep() const;
    double halfTimeStepSquared() const;
    double kineticEnergy() const;
    double potentialEnergy() const;
    double totalEnergy() const;
    vec3 angularMomentum() const;
    vec3 centerOfMass() const;

    // Setters
    void setMethod(const std::string &method);
    void setNumberofsatellites(int numberofsatellites);
    void setStartIteration(int startIteration);
    void setTimeStep(double timeStep);
    void setHalfTimeStep(double halfTimeStep);
    void setHalfTimeStepSquared(double halfTimeStepSquared);
    void setKineticEnergy(double kineticEnergy);
    void setPotentialEnergy(double potentialEnergy);
    void setTotalEnergy(double totalEnergy);
    void setAngularMomentum(vec3 angularMomentum);
    void setCenterOfMass(const vec3 &centerOfMass);

    // Test functions
    void testSimulater(double finaltime, int iterations, int startIteration, std::string method);

private:
    // Constants
    double FOUR_PI_SQUARED = 64*atan(1)*atan(1);
    double SPEED_OF_LIGHT = 173*365;
    double ARCSECONDS_SCALE = 206264.806;

    // member variables
    std::vector<Satellite> m_satellites;
    std::vector<std::string> m_names;
    std::string m_method;
    int m_numberofsatellites;
    int m_startIteration;
    double m_timeStep;
    double m_halfTimeStep;
    double m_halfTimeStepSquared;
    double m_kineticEnergy;
    double m_potentialEnergy;
    double m_totalEnergy;
    double m_perihelionAngle = 0;
    double m_previousDistance = 1;
    double m_previousPreviousDistance = 1;
    vec3 m_vectorPrevious;
    vec3 m_angularMomentum;
    vec3 m_centerOfMass;
};

#endif // SOLARSYSTEM_H
