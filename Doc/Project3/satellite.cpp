#include "satellite.h"

Satellite::Satellite()
{

}

void Satellite::setPos(double x, double y, double z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Satellite::setMass(double m) {
    MASS = m;

}

double Satellite::getRelativeDist(const Satellite ball) {
    double R,dx,dy,dz;
    dx = posX-ball.posX;
    dy = posY-ball.posY;
    dz = posZ-ball.posZ;

    R = sqrt(dx*dx + dy*dy + dz*dz)

    return R;
}
