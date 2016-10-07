#include "solarsystem.h"

SolarSystem::SolarSystem() {

}

Satellite& SolarSystem::createSatellite(double mass, vec3 position, vec3 velocity) {
    m_satellites.push_back( Satellite(mass, position, velocity) );
    return m_satellites.back();
}

double SolarSystem::relativeDistanceBetween() {

}

std::vector<Satellite> &SolarSystem::satellites() {
    return m_satellites;
}
