#include "satellite.h"

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

double Satellite::getDistanceBetween(Satellite s1, Satellite s2) {
    vec3 distanceVector = s1.getSatellitePosition() - s2.getSatellitePosition();
    double dr = distanceVector.length();
    return dr;
}




