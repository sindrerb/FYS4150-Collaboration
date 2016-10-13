#include "solarsystem.h"
#include "satellite.h"
#include <iostream>
#include <string>
#include <fstream>


SolarSystem::SolarSystem() {
    m_satellites.empty();
}

Satellite& SolarSystem::createSatellite(double mass, vec3 position, vec3 velocity) {
    m_satellites.push_back( Satellite(mass, position, velocity) );
    return m_satellites.back();
}

Satellite &SolarSystem::createSolarSystem(std::string inputfile) {
    m_satellites.clear();  // Clear m_satellites (vector of Satellites)

    // Delcare inital values from file
    std::fstream myfile(inputfile , std::ios_base::in);
    if(!myfile.good()) {
        std::cout << "Error reading file " << inputfile << ". Make sure it is in executable dir" << endl;
        terminate();
    }
    std::string name;
    double mass , massEXP, posX, posY, posZ, veloX, veloY, veloZ;
    while (myfile >> name >> mass >> massEXP >> posX >> posY >> posZ >> veloX >> veloY >> veloZ) {
        m_names.push_back(name);
        Satellite &name = createSatellite( mass*exp(massEXP), vec3(posX,posY,posZ), vec3(veloX,veloY,veloZ));

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
