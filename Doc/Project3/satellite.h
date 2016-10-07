#ifndef SATELLITE_H
#define SATELLITE_H
#include <math.h>
#include "vec3.h"
#include "matrix.h"


class Satellite {
public:
    double satelliteMass;
    vec3 satellitePosition;
    vec3 satelliteVelocity;
    Satellite(double mass, vec3 position, vec3 velocity);

    double getSatelliteMass() const;
    void setSatelliteMass(double mass);

    vec3 getSatellitePosition() const;
    void setSatellitePosition(const vec3 &position);

    vec3 getSatelliteVelocity() const;
    void setSatelliteVelocity(const vec3 &velocity);

private:


};

#endif // SATELLITE_H
