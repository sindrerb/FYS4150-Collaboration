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
    void setSatelliteMass(double value);

private:


};

#endif // SATELLITE_H
