#ifndef SATELLITE_H
#define SATELLITE_H
#include <iostream>
#include <matrix.h>
#include <fstream>
#include <string>

using namespace std;
typedef double real;

class Satellite
{
private:
    Matrix position,velocity,potential;
    position.setZeros(1,3);
    velocity.setZeros(1,3);
    potential.setZeros(1,3);
public:
    Satellite();
    setMass();
    setPosition();
};

#endif // SATELLITE_H
