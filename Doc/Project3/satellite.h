#ifndef SATELLITE_H
#define SATELLITE_H
#include <math.h>
#include "vec3.h"
#include "matrix.h"
#include "numericalsolver.h"


class Satellite {
public:

    Satellite(double mass, vec3 position, vec3 velocity);

    double getSatelliteMass() const;
    void setSatelliteMass(double mass);

    vec3 getSatellitePosition() const;
    void setSatellitePosition(const vec3 &position);

    vec3 getSatelliteVelocity() const;
    void setSatelliteVelocity(const vec3 &velocity);

    static double getDistanceBetween(Satellite s1, Satellite s2);

private:
    double satelliteMass;
    vec3 satellitePosition;
    vec3 satelliteVelocity;

};

#endif // SATELLITE_H
