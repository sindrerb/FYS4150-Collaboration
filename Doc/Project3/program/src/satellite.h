#ifndef SATELLITE_H
#define SATELLITE_H
#include <math.h>
#include "vec3.h"
#include "matrix.h"
#include "numericalsolver.h"


class Satellite {
public:
    vec3 g_position;
    vec3 g_velocity;
    vec3 g_new_acceleration;
    vec3 g_old_acceleration;

    Satellite();
    Satellite(double mass, vec3 position, vec3 velocity);

    double mass() const;
    vec3 position() const;
    vec3 velocity() const;
    void setMass(double mass);

    double relativeDistanceTo(const Satellite &satelliteName );

private:
    double m_mass;
    vec3 m_position;
    vec3 m_velocity;
};

#endif // SATELLITE_H
