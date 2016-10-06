#ifndef SATELLITE_H
#define SATELLITE_H
#include <iostream>
#include <matrix.h>
#include <fstream>
#include <string>

using namespace std;

class Satellite
{
private:
    string myName;
    double myMass;
    Matrix position, velocity;
    position.setZeros(3,1);
    velocity.setZeros(3,1);
public:
    //Constructor
    Satellite ();
    Satellite (string name);

    //Setters
    void setMass(double mass);
    void setPosition(Matrix newPosition);
    void setVelocity(Matrix newVelocity);

    //Getters
    double getRelativeDistTo(const Satellite satellite, int axis);
    double getMass();
    string getName();
    Matrix getPosition();
    Matrix getVelocity();
};

#endif // SATELLITE_H
