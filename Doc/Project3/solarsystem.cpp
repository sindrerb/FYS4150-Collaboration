#include "solarsystem.h"

SolarSystem::SolarSystem() {

}

Satellite SolarSystem::getBodies() const {
    return bodies;
}

void SolarSystem::setBodies(const Satellite &body) {
    bodies = body;
}




