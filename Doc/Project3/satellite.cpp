#include "satellite.h"

Satellite::Satellite() {
    satelliteMass = 0;
    posX = 0;
    posY = 0;
    posZ = 0;
    satelliteMass = 0;
}

Satellite::Satellite(string name) {
    satelliteName = name;
}

void Satellite::setPosition(double x, double y, double z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Satellite::setPosX(double x) {
    posX = x;
}

void Satellite::setPosY(double y) {
    posY = y;
}

void Satellite::setPosZ(double z) {
    posZ = z;
}

void Satellite::setMass(double m) {
    satelliteMass = m;
}

double Satellite::getRelativeDistance(const Satellite ball) {
    double R,dx,dy,dz;
    dx = posX-ball.posX;
    dy = posY-ball.posY;
    dz = posZ-ball.posZ;

    R = sqrt(dx*dx + dy*dy + dz*dz);

    return R;
}

string Satellite::getName() const {
    return satelliteName;
}

