#include "satellite.h"

Satellite::Satellite() {
    m_mass = 0;
    m_position.setToZero();
    m_velocity.setToZero();
    m_acceleration.setToZero();
    m_accelerationOld.setToZero();
}

Satellite::Satellite(double mass, vec3 position, vec3 velocity) {
    m_mass = mass;
    m_position = position;
    m_velocity = velocity;
}

double Satellite::relativeDistanceTo(Satellite &satelliteName) {
    vec3 distanceVector = position() - satelliteName.position();
    double dr = distanceVector.length();
    return dr;
}

/****************************************/
/*          Setters and getters         */
/****************************************/
void Satellite::setPosition(const vec3 &position) {
    m_position = position;
}

void Satellite::setVelocity(const vec3 &velocity) {
    m_velocity = velocity;
}

vec3 &Satellite::acceleration() {
    return m_acceleration;
}

void Satellite::setAcceleration(const vec3 &acceleration) {
    m_acceleration = acceleration;
}

vec3 &Satellite::accelerationOld() {
    return m_accelerationOld;
}

void Satellite::setAccelerationOld(const vec3 &accelerationOld) {
    m_accelerationOld = accelerationOld;
}

double Satellite::mass() const {
    return m_mass;
}

vec3 &Satellite::position() {
    return m_position;
}

vec3 &Satellite::velocity() {
    return m_velocity;
}

void Satellite::setMass(double mass) {
    m_mass = mass;
}
