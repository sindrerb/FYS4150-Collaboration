#include "satellite.h"

Satellite::Satellite() {
}

Satellite::Satellite(double mass, vec3 position, vec3 velocity) {
    m_mass = mass;
    m_position = position;
    m_velocity = velocity;
}

double Satellite::getSatelliteMass() const {
    return m_mass;
}

void Satellite::setSatelliteMass(double mass) {
    m_mass = mass;
}

vec3 Satellite::getSatellitePosition() const {
    return m_position;
}

void Satellite::setSatellitePosition(const vec3 &position) {
    m_position = position;
}

vec3 Satellite::getSatelliteVelocity() const {
    return m_velocity;
}

void Satellite::setSatelliteVelocity(const vec3 &velocity) {
    m_velocity = velocity;
}

vec3 Satellite::getSatelliteAcceleration() const {
    return m_acceleration;
}

void Satellite::setSatelliteAcceleration(const vec3 &acceleration) {
    m_acceleration = acceleration;
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
    m_position = NumericalSolver::solveEuler(initialPosition,initialVelocity, timeStep );
}

vec3 Satellite::calculateNewVelocity( vec3 initialAcceleration, double timeStep) {
    vec3 initialVelocity = NumericalSolver::solveEuler(m_position, m_velocity, timeStep );
    m_velocity = NumericalSolver::solveEuler( initialVelocity, initialAcceleration, timeStep );
}

vec3 Satellite::calculateNewAccelleration( vec3 initalPosition, double relativeDistance ) {
    double scalar = - (4*M_PI*M_PI) / ( relativeDistance * relativeDistance * relativeDistance );
    m_acceleration = scalar * initalPosition;
}





