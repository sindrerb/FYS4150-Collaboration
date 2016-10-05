#include "satellite.h"
#include <math.h>

//Constructor
Satellite::Satellite (string name) {
    myName = name;
}

//Setters
void Satellite::setMass(double mass) {
    myMass = mass;
}

void Satellite::setPosition(Matrix newPosition) {
    position = newPosition;
}

void Satellite::setVelocity(Matrix newVelocity) {
    velocity = newVelocity;
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
    Diff = position-satellite.position;
    distance = sqrt(Diff(0,0)*Diff(0,0)+Diff(0,1)*Diff(0,1)+Diff(0,2)*Diff(0,2));

    return distance;
}

double Satellite::getMass() {
    return myMass;
}

string Satellite::getName() {
    return myName;
}

Matrix Satellite::getPosition() {
    return position;
}

Matrix Satellite::getVelocity() {
    return velocity;
}
