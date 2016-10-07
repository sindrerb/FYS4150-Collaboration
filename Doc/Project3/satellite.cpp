#include "satellite.h"

double Satellite::getSatelliteMass() const
{
    return satelliteMass;
}

void Satellite::setSatelliteMass(double value)
{
    satelliteMass = value;
}

Satellite::Satellite(double mass, vec3 position, vec3 velocity) {
    satelliteMass = mass;
    satellitePosition = position;
    satelliteVelocity = velocity;
}


