#include "solarsystem.h"
#include "satellite.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <math.h>


SolarSystem::SolarSystem() {    // Initializes all member variables
    m_satellites.empty();
    m_numberofsatellites = 0;
    m_names.empty();
    m_timeStep = 0;
    m_halfTimeStep = 0;
    m_halfTimeStepSquared = 0;
    m_startIteration = 0;
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_totalEnergy = 0;
    m_angularMomentum.setToZero();
    m_centerOfMass.setToZero();
}

void SolarSystem::createSatellite(double mass, vec3 position, vec3 velocity) {
    m_satellites.push_back( Satellite(mass, position, velocity) );
    m_numberofsatellites += 1;
    calculateEnergies();    // Updates the energy of the system
    calculateAngularMomentum();
}

void SolarSystem::createSolarSystem(std::string inputfile) {
    m_satellites.clear();       // Clear m_satellites
    m_numberofsatellites = 0;
    std::fstream myfile(inputfile , std::ios_base::in); // Delcare inital values from file
    if(!myfile.good()) {        // Check if missing file
        std::cout << "Error reading file " << inputfile << ". Make sure it is in executable dir" << endl;
        terminate();        // Updates the energy of the system
    }

    std::string name;
    double mass , posX, posY, posZ, veloX, veloY, veloZ;
    while (myfile >> name >> mass >> posX >> posY >> posZ >> veloX >> veloY >> veloZ) {
        m_names.push_back(name);
        createSatellite( mass, vec3(posX,posY,posZ), vec3(veloX,veloY,veloZ));
    }
    calculateEnergies();
    calculateAngularMomentum();
}

void SolarSystem::simulate(double finaltime, int iterations,int startIteration,std::string method, std::string outputfile){
    double duration;
    m_method = method;
    m_startIteration = startIteration;
    m_timeStep = finaltime/iterations;
    m_halfTimeStep = m_timeStep*0.5;
    m_halfTimeStepSquared = m_timeStep*m_timeStep*0.5;
    duration = 0;
    if (m_method == "euler" ) {         // Check computational method
        printHeader(finaltime,iterations,outputfile);
        updateForces();
        while(duration<finaltime) {
            updatePositionsEuler();
            updateForces();
            updateVelocitiesEuler();
            printPositions(duration,outputfile);
            duration += m_timeStep;
        }
    } else if ( m_method == "perihelion" ) {
        printHeader(finaltime,iterations,outputfile);
        m_vectorPrevious = satellites()[1].position();
        updateForces();
        while ( duration < finaltime ) {
            updatePositionsVerlet();
            updateForces();
            updateVelocitiesVerlet();
            findPerihelionPosition( outputfile );
            //printPositions ( duration , outputfile );
            duration += m_timeStep;
        }
    } else {
        printHeader(finaltime,iterations,outputfile);
        updateForces();
        while(duration<finaltime) {
            updatePositionsVerlet();
            updateForces();
            updateVelocitiesVerlet();
            printPositions(duration,outputfile);
            duration += m_timeStep;
        }
    }
}

/****************************************/
/*     Computational Functions          */
/****************************************/
void SolarSystem::shiftAccelerations() {
    for (int i = m_startIteration; i < m_numberofsatellites; i++) {
        m_satellites[i].setAccelerationOld( m_satellites[i].acceleration() );
    }
}

void SolarSystem::clearNewAccelerations() {
    for (int i = m_startIteration; i < m_numberofsatellites; i++) {
        m_satellites[i].setAcceleration( vec3(0,0,0) );
    }
}

void SolarSystem::updatePositionsEuler() {
    for (int i = m_startIteration; i < m_numberofsatellites; i++) {
        m_satellites[i].setPosition( NumericalSolver::solveEuler(m_satellites[i].position(), m_satellites[i].velocity(), m_timeStep) );
    }
}

void SolarSystem::updatePositionsVerlet() {
    for (int i = m_startIteration; i < m_numberofsatellites; i++) {
        m_satellites[i].setPosition( NumericalSolver::solveVerletPos(m_satellites[i].position(), m_satellites[i].velocity(), m_satellites[i].acceleration(), m_timeStep, m_halfTimeStepSquared) );
    }
}

void SolarSystem::updateVelocitiesEuler(){
    for (int i = m_startIteration; i < m_numberofsatellites; i++) {
        m_satellites[i].setVelocity( NumericalSolver::solveEuler(m_satellites[i].velocity(), m_satellites[i].accelerationOld(), m_timeStep) );
    }
}

void SolarSystem::updateVelocitiesVerlet(){
    for (int i = m_startIteration; i < m_numberofsatellites; i++) {
        m_satellites[i].setVelocity( NumericalSolver::solveVerletVel(m_satellites[i].velocity(), m_satellites[i].accelerationOld(), m_satellites[i].acceleration(), m_halfTimeStep) );
    }
}

void SolarSystem::updateForces(){       // Calculate forces and update satellite accelerations ( F = ma )
    shiftAccelerations();               // Enables use of Verlets method
    clearNewAccelerations();
    vec3 gravity;
    for (int i = m_startIteration; i < m_numberofsatellites; i++) {     // Run over a set of satellites
        for ( int k = 0; k < m_startIteration; k++) {                   // Enable stationary satellites
            gravity = gravitationalForce( m_satellites[i], m_satellites[k] );
            m_satellites[i].acceleration() -= gravity * m_satellites[k].mass();
        }

        for (int j = i+1; j < m_numberofsatellites; j++) {              // Run over the other satellites in the system
            gravity = gravitationalForce( m_satellites[i], m_satellites[j] );
            m_satellites[i].acceleration() -= gravity * m_satellites[j].mass();
            m_satellites[j].acceleration() += gravity * m_satellites[i].mass();
        }
    }
}

vec3 SolarSystem::gravitationalForce( Satellite planetA, Satellite planetB ) {
    vec3 force;
    double R = planetA.relativeDistanceTo( planetB );
    force = FOUR_PI_SQUARED * ( planetA.position() - planetB.position() )/( R*R*R );
    if (m_method == "relativistic" || m_method == "perihelion") {
        double RC = R * SPEED_OF_LIGHT;
        vec3 angularMomentum = planetA.position().cross(planetA.velocity());
        force = force * ( 1 + ( 3 * angularMomentum.lengthSquared() ) / ( RC*RC) ) ;
    }
    return force;
}

void SolarSystem::calculateEnergies() {     // Calculates kinetic and potential energy of system
    double G = FOUR_PI_SQUARED;
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;

    for (int i=0; i < m_numberofsatellites; i++) {
        for (int j=i+1; j<m_numberofsatellites; j++) {
            double relativeDistance = m_satellites[i].relativeDistanceTo( m_satellites[j] );                // Distance between bodies
            m_potentialEnergy -= G * m_satellites[i].mass() * m_satellites[j].mass() / relativeDistance ;   // Potential energy to total
        }
        m_kineticEnergy += 0.5 * m_satellites[i].mass() * m_satellites[i].velocity().lengthSquared();       // And kinetic energy
    }
    calculateTotalEnergy();
}

void SolarSystem::calculateTotalEnergy() {
    m_totalEnergy = m_kineticEnergy + m_potentialEnergy;
}

void SolarSystem::calculateCenterOfMass() {
    m_centerOfMass.setToZero();
    double totalMassOfSystem = 0;
    for (int i = 0; i < m_numberofsatellites; i++) {
        totalMassOfSystem += m_satellites[i].mass();
        for ( int j = 0; j <m_numberofsatellites; j++) {
            m_centerOfMass += m_satellites[j].position() * m_satellites[j].mass();
        }
    }
    m_centerOfMass = m_centerOfMass / totalMassOfSystem;
}

void SolarSystem::calculateAngularMomentum() {
    m_angularMomentum.setToZero();   // set angular momentum to zero
    calculateCenterOfMass();
    for (int i = 0; i < m_numberofsatellites; i++) {
        vec3 distanceVetor = m_satellites[i].position() - m_centerOfMass;
        m_angularMomentum += distanceVetor.cross( m_satellites[i].position() * m_satellites[i].mass() ) ;
    }
}

void SolarSystem::findPerihelionPosition( std::string outputfile ) {
    double currentDistance = m_satellites[1].relativeDistanceTo( m_satellites[0] );
//    vec3 currentPositionVector = m_satellites[1].position();
    if ( currentDistance > m_previousDistance && m_previousDistance < m_previousPreviousDistance ) {
        m_perihelionAngle = atan2( m_vectorPrevious.y() , m_vectorPrevious.x() ) * ARCSECONDS_SCALE;
        m_perihelionPosition = m_vectorPrevious;
        printPerihelionAngleToFile( outputfile );
    }
    m_previousPreviousDistance = m_previousDistance;
    m_previousDistance = currentDistance;
    m_vectorPrevious = m_satellites[1].position();
}

/****************************************/
/*          PRINT FUNCTIONS             */
/****************************************/
void SolarSystem::printHeader(double time, int iterations, std::string outputfile){
    std::ofstream outfile(outputfile);
    outfile << "Simulation of solar system over " << time << " years, with "<< iterations <<" iterations, using " << m_method << "´s method." << endl;
    outfile << "Time \t";
    for (int i = 0; i < m_numberofsatellites; i++) {
        outfile << m_names[i] << "\t \t";
    }
    outfile << "\n";
    outfile.close();
}

void SolarSystem::printPositions(double time,std::string outputfile){
    std::ofstream outfile(outputfile,std::ios::app);
    outfile << time;
    for (int i = 0; i < m_numberofsatellites; i++) {
        outfile << ",\t" << m_satellites[i].position().x() << "," << m_satellites[i].position().y() << "," << m_satellites[i].position().z();
    }
    outfile << "\n";
    outfile.close();
}

void SolarSystem::printPerihelionAngleToFile(std::string outputfile) {
    std::fstream outfile(outputfile, std::ios::app);
    outfile << std::setprecision(9) << "angle: " << m_perihelionAngle << "\t distance: " << m_previousDistance << "\t Position(x,y,z): " << m_perihelionPosition.x() << " , " << m_perihelionPosition.y() << " , " << m_perihelionPosition.z() << endl;
    outfile.close();
}

/****************************************/
/*          Setters and getters         */
/****************************************/
std::vector<Satellite> &SolarSystem::satellites()  {
    return m_satellites;
}

int SolarSystem::numberofsatellites() const {
    return m_satellites.size();
}

void SolarSystem::setNumberofsatellites(int numberofsatellites){
    m_numberofsatellites = numberofsatellites;
}

double SolarSystem::timeStep() const {
    return m_timeStep;
}

void SolarSystem::setTimeStep(double timeStep) {
    m_timeStep = timeStep;
}

double SolarSystem::halfTimeStep() const {
    return m_halfTimeStep;
}

void SolarSystem::setHalfTimeStep(double halfTimeStep) {
    m_halfTimeStep = halfTimeStep;
}

double SolarSystem::halfTimeStepSquared() const {
    return m_halfTimeStepSquared;
}

void SolarSystem::setHalfTimeStepSquared(double halfTimeStepSquared) {
    m_halfTimeStepSquared = halfTimeStepSquared;
}

std::string SolarSystem::method() const {
    return m_method;
}

void SolarSystem::setMethod(const std::string &method) {
    m_method = method;
}

int SolarSystem::startIteration() const {
    return m_startIteration;
}

void SolarSystem::setStartIteration(int startIteration) {
    m_startIteration = startIteration;
}

double SolarSystem::kineticEnergy() const {
    return m_kineticEnergy;
}

void SolarSystem::setKineticEnergy(double kineticEnergy) {
    m_kineticEnergy = kineticEnergy;
}

double SolarSystem::potentialEnergy() const {
    return m_potentialEnergy;
}

void SolarSystem::setPotentialEnergy(double potentialEnergy) {
    m_potentialEnergy = potentialEnergy;
}

double SolarSystem::totalEnergy() const {
    return m_totalEnergy;
}

void SolarSystem::setTotalEnergy(double totalEnergy) {
    m_totalEnergy = totalEnergy;
}

vec3 SolarSystem::angularMomentum() const {
    return m_angularMomentum;
}

void SolarSystem::setAngularMomentum(vec3 angularMomentum) {
    m_angularMomentum = angularMomentum;
}

vec3 SolarSystem::centerOfMass() const {
    return m_centerOfMass;
}

void SolarSystem::setCenterOfMass(const vec3 &centerOfMass) {
    m_centerOfMass = centerOfMass;
}

/****************************************/
/*        Function for unit tests       */
/****************************************/
void SolarSystem::testSimulater(double finaltime, int iterations,int startIteration,std::string method) { // Removed file handeling, enabeling unit test
    double duration;
    m_method = method;
    m_startIteration = startIteration;
    m_timeStep = finaltime/iterations;
    m_halfTimeStep = m_timeStep*0.5;
    m_halfTimeStepSquared = m_timeStep*m_timeStep*0.5;
    duration = 0;
    if (m_method == "euler" ) {         // Check computational method
        //printHeader(finaltime,iterations,outputfile);
        updateForces();
        while(duration<finaltime) {
            updatePositionsEuler();
            updateForces();
            updateVelocitiesEuler();
            //printPositions(duration,outputfile);
            duration += m_timeStep;
        }
    } else {
        //printHeader(finaltime,iterations,outputfile);
        updateForces();
        while(duration<finaltime) {
            updatePositionsVerlet();
            updateForces();
            updateVelocitiesVerlet();
            //printPositions(duration,outputfile);
            duration += m_timeStep;
        }
    }
    calculateAngularMomentum();
}




