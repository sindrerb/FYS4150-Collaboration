#include "satellite.h"

//Constructor
Satellite::Satellite () {
    satelliteMass = 0;
}

//Setters
Satellite::Satellite(string name) {
    satelliteName = name;
}

void Satellite::setMass(double mass) {
    satelliteMass = mass;
}

void Satellite::setPosition(Matrix newPosition) {
    satellitePosition = newPosition;
}

void Satellite::setVelocity(Matrix newVelocity) {
    satelliteVelocity = newVelocity;
}

//Getters
double Satellite::getRelativeDistTo(const Satellite satellite, int axis) {
    double distance;
    Matrix Diff, Axis;
    if(axis !=0){
        if(axis<=3){
            Axis.setZeros(3,3);
            Axis.setElement(axis,axis,1);
        }else{
            cout << "Error, axis dimention too large.";
        }
    }else{
        Axis.setIdentity(3);
    }
    Diff = satellitePosition-satellite.satellitePosition;

    distance = sqrt(Diff(0,0)*Diff(0,0)+Diff(0,1)*Diff(0,1)+Diff(0,2)*Diff(0,2));

    return distance;
}

double Satellite::getMass() {
    return satelliteMass;
}

string Satellite::getName() {
    return satelliteName;
}

Matrix Satellite::getPosition() {
    return satellitePosition;
}

Matrix Satellite::getVelocity() {
    return satelliteVelocity;
}
