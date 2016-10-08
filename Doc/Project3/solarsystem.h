#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <iostream>
#include "vec3.h"
#include "satellite.h"
#include "matrix.h"

class SolarSystem
{
public:
    SolarSystem();
    Satellite &createSatellite(double mass, vec3 position, vec3 velocity);

    std::vector<Satellite> &satellites();
    Satellite &createSunEarth();
private:
    std::vector<Satellite> m_satellites;
};

#endif // SOLARSYSTEM_H
