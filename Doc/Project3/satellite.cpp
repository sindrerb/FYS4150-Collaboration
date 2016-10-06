#include "satellite.h"
#include <string>
#include <matrix.h>
#include <math.h>

Satellite::Satellite(){
    satelliteMass = 0;
    satelliteVelocity.setZeros(1,3);
    satellitePosition.setZeros(1,3);
}

Satellite::Satellite(string name) {
    satelliteName = name;
}

Satellite::Satellite(string name, Matrix position, Matrix velocity) {
    satelliteName = name;
    satelliteVelocity.setColumn(0,velocity);
    satellitePosition.setColumn(0,position);
}

string Satellite::getName() const {
    return satelliteName;
}

void Satellite::setName(string name) {
    satelliteName = name;
}

double Satellite::getMass() const {
    return satelliteMass;
}

void Satellite::setMass(double mass) {
    satelliteMass = mass;
}

Matrix Satellite::getPosition() const {
    return satellitePosition;
}

void Satellite::setPosition(Matrix position) {
    satellitePosition = position;
}

Matrix Satellite::getVelocity() const {
    return satelliteVelocity;
}

void Satellite::setVelocity(const Matrix &value) {
    satelliteVelocity = value;
}

//double Satellite::getRelativeDist(const Satellite name) {
//    double R,dx,dy,dz;
//    dx = satellitePosition.get - name.posX;
//    dy = posY - name.posY;
//    dz = posZ - name.posZ;
//    R = sqrt(dx*dx + dy*dy + dz*dz);
//    return R;
//}
