#ifndef SATELLITE_H
#define SATELLITE_H
#include <math.h>
#include "vec3.h"
#include "matrix.h"
#include "numericalsolver.h"


class Satellite {
public:
    Satellite();
    Satellite(double mass, vec3 position, vec3 velocity);

    double mass() const;
    vec3 position() const;
    vec3 velocity() const;
    vec3 acceleration() const;
    vec3 accelerationOld() const;

    void setMass(double mass);
    void setPosition(const vec3 &position);
    void setVelocity(const vec3 &velocity);
    void setAcceleration(const vec3 &acceleration);
    void setAccelerationOld(const vec3 &accelerationOld);

    double relativeDistanceTo(const Satellite &satelliteName );




private:
    double m_mass;
    vec3 m_position;
    vec3 m_velocity;
    vec3 m_acceleration;
    vec3 m_accelerationOld;
};

#endif // SATELLITE_H
