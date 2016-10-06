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
    Matrix position;
    Matrix velocity;
    Matrix acceleration;
public:
    //Constructor
    Satellite ();
    Satellite (string name);

    //Setters
    void setMass(double mass);
    void setPosition(Matrix newPosition);
    void setVelocity(Matrix newVelocity);
    void setAcceleration(Matrix newAcceleration);

    //Getters
    double getRelativeDistTo(const Satellite satellite, int axis);
    double getMass();
    string getName();
    Matrix getPosition();
    Matrix getVelocity();
    Matrix getAcceleration();
};

#endif // SATELLITE_H
