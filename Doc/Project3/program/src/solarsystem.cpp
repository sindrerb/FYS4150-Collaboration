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
    m_numberofsatellites += 1;
    return m_satellites.back();
}

void SolarSystem::createSolarSystem(std::string inputfile) {
    m_numberofsatellites = 0;
    m_satellites.clear();  // Clear m_satellites (vector of Satellites)

    // Delcare inital values from file
    std::fstream myfile(inputfile , std::ios_base::in);
    if(!myfile.good()) {
        std::cout << "Error reading file " << inputfile << ". Make sure it is in executable dir" << endl;
        terminate();
    }
    std::string name;
    double mass , posX, posY, posZ, veloX, veloY, veloZ;
    while (myfile >> name >> mass >> posX >> posY >> posZ >> veloX >> veloY >> veloZ) {
        m_names.push_back(name);
        std::cout << name<<"\t " <<"P:"<< posX <<" "<< posY<<" " << posZ<<"\t" <<"V:"<< veloX<<" " << veloY<<" " << veloZ << endl;
        Satellite &name = createSatellite( mass, vec3(posX,posY,posZ), vec3(veloX,veloY,veloZ));
    }
}
void SolarSystem::printHeader(double time, int iterations, std::string outputfile){
    std::ofstream outfile(outputfile);
    outfile << "Simulation of solar system over "<<time<<" years, with "<<iterations<<" iterations.\n";
    outfile << "Time \t";
    for(int i=0; i<m_numberofsatellites;i++) {
        outfile << m_names[i] << "\t \t";
    }
    outfile << "\n";
    outfile.close();
}

void SolarSystem::printPositions(double time,std::string outputfile){
    std::ofstream outfile(outputfile,std::ios::app);
    outfile << time;
    for(int i=0; i<m_numberofsatellites;i++) {
        outfile <<",\t"<< m_satellites[i].g_position[0]<<","<<m_satellites[i].g_position[1]<<","<<m_satellites[i].g_position[2];
    }
    outfile << "\n";
    outfile.close();
}


void SolarSystem::shiftAccelerations() {
    for(int i=0;i<m_numberofsatellites;i++) {
        m_satellites[i].g_old_acceleration =  m_satellites[i].g_new_acceleration;
    }
}

void SolarSystem::clearNewAccelerations() {
    for(int i=0;i<m_numberofsatellites;i++) {
        m_satellites[i].g_new_acceleration = vec3(0,0,0);
    }
}

void SolarSystem::updatePositions() {
    vec3 test;
    for(int i=0;i<m_numberofsatellites;i++) {
        m_satellites[i].g_position =  NumericalSolver::solveVerletPos(m_satellites[i].g_position,m_satellites[i].g_velocity,m_satellites[i].g_new_acceleration,m_timestep);
    }
}

void SolarSystem::updateVelocities(){
    for(int i=0;i<m_numberofsatellites;i++) {
        m_satellites[i].g_velocity = NumericalSolver::solveVerletVel(m_satellites[i].g_velocity,m_satellites[i].g_old_acceleration,m_satellites[i].g_new_acceleration,m_timestep);
    }
}

void SolarSystem::updateForces(){
    shiftAccelerations();
    clearNewAccelerations();
    vec3 gravity;
    for(int i=0;i<m_numberofsatellites;i++) {
        for(int j=i+1;j<m_numberofsatellites;j++) {
            gravity = gravitationalForce(m_satellites[i],m_satellites[j]);

            m_satellites[i].g_new_acceleration -= gravity*m_satellites[j].getMass();
            m_satellites[j].g_new_acceleration += gravity*m_satellites[i].getMass();
        }
    }
    //m_satellites[1].g_new_acceleration.print();
}

vec3 SolarSystem::gravitationalForce(Satellite planetA,Satellite planetB){
    vec3 force;
    double R = planetA.relativeDistanceTo(planetB);
    force = FOUR_PI_SQUARED*(planetA.g_position-planetB.g_position)/(R*R*R);
    return force;
}

void SolarSystem::simulate(double finaltime, int iterations, std::string outputfile){
    printHeader(finaltime,iterations,outputfile);
    double timestep, duration;
    m_timestep = finaltime/iterations;
    duration = 0;
    updateForces();
    while(duration<finaltime) {
        updatePositions();
        updateForces();
        updateVelocities();
        printPositions(duration,outputfile);
        duration += m_timestep;
    }
}
