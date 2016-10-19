#include "solarsystem.h"
#include "satellite.h"
#include <iostream>
#include <string>
#include <fstream>


SolarSystem::SolarSystem() {
    m_satellites.empty();
}

void SolarSystem::createSatellite(double mass, vec3 position, vec3 velocity) {
    m_satellites.push_back( Satellite(mass, position, velocity*365) );
    m_numberofsatellites += 1;
    //return m_satellites.back();
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
        createSatellite( mass, vec3(posX,posY,posZ), vec3(veloX,veloY,veloZ));
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

void SolarSystem::updatePositionsEuler() {
    for (int i = m_startIteration; i < m_numberofsatellites; i++) {
        m_satellites[i].g_position =  NumericalSolver::solveEuler(m_satellites[i].g_position,m_satellites[i].g_velocity,m_timeStep);
    }
}

void SolarSystem::updatePositionsVerlet() {
    for (int i = m_startIteration; i < m_numberofsatellites; i++) {
        m_satellites[i].g_position =  NumericalSolver::solveVerletPos(m_satellites[i].g_position,m_satellites[i].g_velocity,m_satellites[i].g_new_acceleration,m_timeStep,m_halfTimeStepSquared);
    }
}

void SolarSystem::updateVelocitiesEuler(){
    for (int i = m_startIteration; i < m_numberofsatellites; i++) {
        m_satellites[i].g_velocity = NumericalSolver::solveEuler(m_satellites[i].g_velocity,m_satellites[i].g_old_acceleration,m_timeStep);
    }
}

void SolarSystem::updateVelocitiesVerlet(){
    for (int i = m_startIteration; i < m_numberofsatellites; i++) {
        m_satellites[i].g_velocity = NumericalSolver::solveVerletVel(m_satellites[i].g_velocity,m_satellites[i].g_old_acceleration,m_satellites[i].g_new_acceleration,m_halfTimeStep);
    }
}

void SolarSystem::updateForces(){
    shiftAccelerations();
    clearNewAccelerations();
    vec3 gravity;
    for(int i=m_startIteration;i<m_numberofsatellites;i++) {
        if(m_startIteration==1){
            gravity = gravitationalForce(m_satellites[i],m_satellites[0]);
            m_satellites[i].g_new_acceleration -= gravity;
        }
        for(int j=i+1;j<m_numberofsatellites;j++) {
            gravity = gravitationalForce(m_satellites[i],m_satellites[j]);

            m_satellites[i].g_new_acceleration -= gravity*m_satellites[j].mass();
            m_satellites[j].g_new_acceleration += gravity*m_satellites[i].mass();
        }
    }
    //m_satellites[1].g_new_acceleration.print();
}

vec3 SolarSystem::gravitationalForce(Satellite planetA,Satellite planetB){
    vec3 force;
    double R = planetA.relativeDistanceTo(planetB);
    force = FOUR_PI_SQUARED*(planetA.g_position-planetB.g_position)/(R*R*R);
    if(m_method == "relativistic"){
        double RC = R*SPEED_OF_LIGHT;
        vec3 angularMomentum = planetA.g_position.cross(planetA.g_velocity);
        force = force*(1+(3*angularMomentum.lengthSquared())/(RC*RC));
    }
    return force;
}

void SolarSystem::simulate(double finaltime, int iterations,int startIteration,std::string method, std::string outputfile){
    printHeader(finaltime,iterations,outputfile);
    double duration;
    m_method = method;
    m_startIteration = startIteration;
    m_timeStep = finaltime/iterations;
    m_halfTimeStep = m_timeStep*0.5;
    m_halfTimeStepSquared = m_timeStep*m_timeStep*0.5;
    duration = 0;
    updateForces();
    while(duration<finaltime) {
        updatePositions();
        updateForces();
        updateVelocities();
        printPositions(duration,outputfile);
        duration += m_timeStep;
    }
}


//Setters and getters for membervariables
std::vector<Satellite> SolarSystem::satellites() const
{
    return m_satellites;
}

int SolarSystem::numberofsatellites() const
{
    return m_numberofsatellites;
}

void SolarSystem::setNumberofsatellites(int numberofsatellites)
{
    m_numberofsatellites = numberofsatellites;
}

double SolarSystem::timeStep() const
{
    return m_timeStep;
}

void SolarSystem::setTimeStep(double timeStep)
{
    m_timeStep = timeStep;
}

double SolarSystem::halfTimeStep() const
{
    return m_halfTimeStep;
}

void SolarSystem::setHalfTimeStep(double halfTimeStep)
{
    m_halfTimeStep = halfTimeStep;
}

double SolarSystem::halfTimeStepSquared() const
{
    return m_halfTimeStepSquared;
}

void SolarSystem::setHalfTimeStepSquared(double halfTimeStepSquared)
{
    m_halfTimeStepSquared = halfTimeStepSquared;
}

