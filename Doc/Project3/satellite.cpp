#include "satellite.h"
#include <string>
#include <matrix.h>
#include <math.h>

Satellite::Satellite(){
    satelliteMass = 0;
}

Satellite::Satellite(string name) {
    satelliteName = name;
}

string Satellite::getSatelliteName() const {
    return satelliteName;
}

void Satellite::setSatelliteName(string name) {
    satelliteName = name;
}

double Satellite::getSatelliteMass() const {
    return satelliteMass;
}

void Satellite::setSatelliteMass(double mass) {
    satelliteMass = mass;
}

double Satellite::getPosZ() const {
    return posZ;
}

void Satellite::setPosZ(double zCoordinate) {
    posZ = zCoordinate;
}

double Satellite::getPosY() const {
    return posY;
}

void Satellite::setPosY(double yCoordinate) {
    posY = yCoordinate;
}

double Satellite::getPosX() const {
    return posX;
}

void Satellite::setPosX(double xCoordinate) {
    posX = xCoordinate;
}

Matrix Satellite::getSatellitePosition() const {
    return satellitePosition;
}

void Satellite::setSatellitePosition(Matrix position) {
    satellitePosition = position;
}

double Satellite::getRelativeDist(const Satellite name) {
    double R,dx,dy,dz;
    dx = posX - name.posX;
    dy = posY - name.posY;
    dz = posZ - name.posZ;
    R = sqrt(dx*dx + dy*dy + dz*dz);
    return R;
}
