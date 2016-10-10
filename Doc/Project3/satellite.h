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

    double getSatelliteMass() const;
    void setSatelliteMass(double mass);

    vec3 getSatellitePosition() const;
    void setSatellitePosition(const vec3 &position);

    vec3 getSatelliteVelocity() const;
    void setSatelliteVelocity(const vec3 &velocity);

    vec3 getSatelliteAcceleration() const;
    void setSatelliteAcceleration(const vec3 &acceleration);

    static double getDistanceBetween( Satellite s1, Satellite s2 );

    double relativeDistanceTo( Satellite satelliteName );

    vec3 calculateNewPosition( vec3 initialPosition, vec3 initialVelocity, double timeStep );
    vec3 calculateNewVelocity( vec3 initialAcceleration, double timesStep );
    vec3 calculateNewAccelleration( vec3 initalPosition , double relativeDistance );

private:
    double m_mass;
    vec3 m_position;
    vec3 m_velocity;
    vec3 m_acceleration;
    vec3 m_force;
};

#endif // SATELLITE_H
