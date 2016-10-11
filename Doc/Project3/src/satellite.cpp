#include "satellite.h"

Satellite::Satellite() {
    m_mass = 0;
    m_position = vec3(0,0,0);
    m_velocity = vec3(0,0,0);
    m_acceleration = vec3(0,0,0);
    m_force = vec3(0,0,0);
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

const vec3 &Satellite::getSatellitePosition() const {
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

double Satellite::getDistanceBetween(const Satellite &s1, const Satellite &s2) {
    vec3 distanceVector = s1.getSatellitePosition() - s2.getSatellitePosition();
    double dr = distanceVector.length();
    return dr;
}

double Satellite::relativeDistanceTo(const Satellite &satelliteName) {
    vec3 distanceVector = this->getSatellitePosition() - satelliteName.getSatellitePosition();
    double dr = distanceVector.length();
    return dr;
}

void Satellite::nextPositionEuler(vec3 initialPosition, vec3 initialVelocity, double timeStep) {
    m_position = NumericalSolver::solveEuler(initialPosition,initialVelocity, timeStep );
}

void Satellite::nextVelocityEuler( vec3 initialAcceleration, double timeStep) {
    vec3 initialVelocity = NumericalSolver::solveEuler(m_position, m_velocity, timeStep );
    m_velocity = NumericalSolver::solveEuler( initialVelocity, initialAcceleration, timeStep );
}

void Satellite::nextPositionVerlet(vec3 initialPosition, vec3 initialVelocity, vec3 initialAcceleration, double timeStep) {
    double timeStepSquared = timeStep*timeStep;
    m_position = NumericalSolver::solveVerletPos( initialPosition, initialVelocity, initialAcceleration, timeStep, timeStepSquared );
}

void Satellite::nextVelocityVerlet(vec3 initialAcceleration, double timesStep) {

}

void Satellite::nextAcceleration(Satellite satelliteName) {
    double distance = relativeDistanceTo( satelliteName );
    double scalar = - (4*M_PI*M_PI) / ( distance * distance * distance);
    m_acceleration = scalar * this->getSatellitePosition();
}





