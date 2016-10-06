#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include "satellite.h"


class SolarSystem
{
public:
    SolarSystem();    

    Satellite getBodies() const;
    void setBodies(const Satellite &body);

private:
    Satellite bodies;
};

#endif // SOLARSYSTEM_H
