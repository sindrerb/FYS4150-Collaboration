#include "satellite.h"

Satellite::Satellite() {
    m_mass = 0;
    m_position = vec3(0,0,0);
    m_velocity = vec3(0,0,0);

    g_position = m_position;
    g_velocity = m_velocity;
    g_acceleration = vec3(0,0,0);
    g_force = vec3(0,0,0);
}

Satellite::Satellite(double mass, vec3 position, vec3 velocity) {
    m_mass = mass;
    m_position = position;
    m_velocity = velocity;
}

double Satellite::mass() const {
    return m_mass;
}

void Satellite::setMass(double mass) {
    m_mass = mass;
}

vec3 Satellite::relativeDistanceVector(const Satellite &satelliteName) {
    vec3 distanceVector = g_position - satelliteName.g_position;
    return distanceVector;
}

double Satellite::relativeDistanceTo(const Satellite &satelliteName) {
    vec3 distanceVector = g_position - satelliteName.g_position;
    double dr = distanceVector.length();
    return dr;
}





