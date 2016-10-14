#include "solarsystem.h"
#include "satellite.h"
#include <iostream>
#include <string>
#include <fstream>


SolarSystem::SolarSystem() {
    g_satellites.empty();
}

Satellite& SolarSystem::createSatellite(double mass, vec3 position, vec3 velocity) {
    g_satellites.push_back( Satellite(mass, position, velocity) );
    return g_satellites.back();
}

Satellite &SolarSystem::createSolarSystem(std::string inputfile) {
    g_satellites.clear();  // Clear m_satellites (vector of Satellites)

    // Delcare inital values from file
    std::fstream myfile(inputfile , std::ios_base::in);
    if(!myfile.good()) {
        std::cout << "Error reading file " << inputfile << ". Make sure it is in executable dir" << std::endl;
        std::terminate();
    }
    std::string name;
    double mass , posX, posY, posZ, veloX, veloY, veloZ;
    while (myfile >> name >> mass >> posX >> posY >> posZ >> veloX >> veloY >> veloZ) {
        m_names.push_back(name);
        Satellite &name = createSatellite( mass, vec3(posX,posY,posZ), vec3(veloX,veloY,veloZ));
    }
}
void SolarSystem::printHeader(double time, int iterations, std::string outputfile){
    std::ofstream outfile(outputfile);
    outfile << "Simulation of solar system over "<<time<<" years, with "<<iterations<<" iterations.\n";
    outfile << "Time \t";
    for(int i=0; i<m_names.size();i++) {
        outfile << m_names[i] << "\t \t";
    }
    outfile << "\n";
    outfile.close();
}

void SolarSystem::printPositions(double time,std::string outputfile){
    std::ofstream outfile(outputfile,std::ios::app);
    outfile << time;
    for(int i=0; i<m_satellites.size();i++) {
        outfile <<",\t"<< m_satellites[i].g_position[0]<<","<<m_satellites[i].g_position[1]<<","<<m_satellites[i].g_position[2];
    }
    outfile << "\n";
    outfile.close();
}

void SolarSystem::simulate(double finaltime, int iterations, std::string outputfile){
    printHeader(finaltime,iterations,outputfile);
    double timestep, duration;
    timestep = finaltime/iterations;
    duration = 0;
    while(duration<finaltime) {
        printPositions(duration,outputfile);
        duration += timestep;
    }
}

void SolarSystem::calculateEnergies() {
    const double G = 4*M_PI*M_PI;
    g_kineticEnergy = 0;
    g_potentialEnergy = 0;
    angularMomentum.zeros();

    for (int i=0; i<g_satellites.size(); i++) {
        Satellite satellite1 = g_satellites[i];

        for (int j=i+1; j<g_satellites.size(); j++) {
            Satellite satellite2 = g_satellites[j];

            vec3 distanceVector = satellite1.relativeDistanceVector( satellite2 );
            double distance = distanceVector.length();
            g_potentialEnergy += -G * satellite1.mass() * satellite2.mass() / distance;
        }
        g_kineticEnergy += 0.5 * satellite1.mass() * satellite1.g_velocity.lengthSquared();
    }
}

void SolarSystem::calculateForces() {
    //Sett all forces to zero
    resetForces();
    //Sum over all satellites in the system, calculating forces.
    for (int i=0; i<g_satellites.size(); i++) {
        Satellite satellite1 = g_satellites[i];

        for (int j=i+1; j<g_satellites.size(); j++) {
            Satellite satellite2 = g_satellites[j];

            vec3 distanceVector = satellite1.relativeDistanceVector( satellite2 );
            double distance = distanceVector.length();
            double forceScalar = ( satellite1.mass() * satellite2.mass()) / ( distance * distance * distance);
            vec3 forceVector = forceScalar * distanceVector;
            satellite1.g_force += forceVector;
        }
    }
}

void SolarSystem::resetForces() {
    for ( int i =0; i<= g_satellites.size(); i++) {
        Satellite satellite = g_satellites[i];
        satellite.g_force.zeros();
    }
}
