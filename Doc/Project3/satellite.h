#ifndef SATELLITE_H
#define SATELLITE_H
#include <iostream>
#include <matrix.h>
#include <fstream>
#include <string>

using namespace std;

class Satellite
{

public:
//Constructors
    Satellite ();
    Satellite(string name);
    Satellite(string name, Matrix position, Matrix velocity);

//Setters
    void setName(string name);
    void setMass(double mass);
    void setPosition(Matrix position);

//Getters
    string getName() const;
    double getMass() const;
    Matrix getPosition() const;
    double getRelativeDist(const Satellite name);
    Matrix getVelocity() const;
    void setVelocity(const Matrix &value);

private:
    string satelliteName;
    double satelliteMass;
    Matrix satellitePosition;
    Matrix satelliteVelocity;
};


#endif // SATELLITE_H
