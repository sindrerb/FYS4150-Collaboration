#include "satellite.h"
#include <math.h>

using namespace std;

Satellite::Satellite(string name)
{
    myName = name;
}

void Satellite::setPos(double X,double Y,double Z){
    Xpos = X;
    Ypos = Y;
    Zpos = Z;
}

void Satellite::setMass(double M){
    Mass = M;
}

double Satellite::getRelativeDist(const Satellite ball){
    double R,dX,dY,dZ;
    dX = Xpos-ball.Xpos;
    dY = Ypos-ball.Ypos;
    dZ = Zpos-ball.Zpos;
    R = sqrt(dX*dX + dY*dY + dZ*dZ);
    return R;
}
string Satellite::getName(){
    return myName;
}
