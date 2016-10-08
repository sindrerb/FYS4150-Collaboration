#include "solarsystem.h"
#include "satellite.h"

SolarSystem::SolarSystem() {

}

Satellite& SolarSystem::createSatellite(double mass, vec3 position, vec3 velocity) {
    m_satellites.push_back( Satellite(mass, position, velocity) );
    return m_satellites.back();
}

std::vector<Satellite> &SolarSystem::satellites() {
    return m_satellites;
}
