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

    const vec3 &getSatellitePosition() const;
    void setSatellitePosition(const vec3 &position);

    vec3 getSatelliteVelocity() const;
    void setSatelliteVelocity(const vec3 &velocity);

    vec3 getSatelliteAcceleration() const;
    void setSatelliteAcceleration(const vec3 &acceleration);

    static double getDistanceBetween(const Satellite &s1, const Satellite &s2 );

    double relativeDistanceTo(const Satellite &satelliteName );

    void nextPositionEuler( vec3 initialPosition, vec3 initialVelocity, double timeStep );
    void nextVelocityEuler( vec3 initialAcceleration, double timesStep );
    void nextPositionVerlet( vec3 initialPosition, vec3 initialVelocity, vec3 initialAcceleration, double stimeStep );
    void nextVelocityVerlet( vec3 initialAcceleration, double timesStep );
    void nextAcceleration( Satellite satelliteName );

private:
    double m_mass;
    vec3 m_position;
    vec3 m_velocity;
    vec3 m_acceleration;
    vec3 m_force;
};

#endif // SATELLITE_H
