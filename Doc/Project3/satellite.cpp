#include "satellite.h"

Satellite::Satellite() {
}

Satellite::Satellite(double mass, vec3 position, vec3 velocity) {
    satelliteMass = mass;
    satellitePosition = position;
    satelliteVelocity = velocity;
}

double Satellite::getSatelliteMass() const {
    return satelliteMass;
}

void Satellite::setSatelliteMass(double mass) {
    satelliteMass = mass;
}

vec3 Satellite::getSatellitePosition() const {
    return satellitePosition;
}

void Satellite::setSatellitePosition(const vec3 &position) {
    satellitePosition = position;
}

vec3 Satellite::getSatelliteVelocity() const {
    return satelliteVelocity;
}

void Satellite::setSatelliteVelocity(const vec3 &velocity) {
    satelliteVelocity = velocity;
}

vec3 Satellite::getSatelliteAcceleration() const {
    return satelliteAcceleration;
}

void Satellite::setSatelliteAcceleration(const vec3 &acceleration) {
    satelliteAcceleration = acceleration;
}

double Satellite::getDistanceBetween(Satellite s1, Satellite s2) {
    vec3 distanceVector = s1.getSatellitePosition() - s2.getSatellitePosition();
    double dr = distanceVector.length();
    return dr;
}

double Satellite::relativeDistanceTo(Satellite satelliteName) {
    vec3 distanceVector = this->getSatellitePosition() - satelliteName.getSatellitePosition();
    double dr = distanceVector.length();
    return dr;
}

vec3 Satellite::calculateNewPosition(vec3 initialPosition, vec3 initialVelocity, double timeStep) {
    satellitePosition = NumericalSolver::solveEuler(initialPosition,initialVelocity, timeStep );
}

vec3 Satellite::calculateNewVelocity( vec3 initialAcceleration, double timeStep) {
    vec3 initialVelocity = NumericalSolver::solveEuler(satellitePosition, satelliteVelocity, timeStep );
    satelliteVelocity = NumericalSolver::solveEuler( initialVelocity, initialAcceleration, timeStep );
}

vec3 Satellite::calculateNewAccelleration( vec3 initalPosition, double relativeDistance ) {
    double scalar = - (4*M_PI*M_PI) / ( relativeDistance * relativeDistance * relativeDistance );
    satelliteAcceleration = scalar * initalPosition;
}





