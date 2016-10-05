#ifndef SATELLITE_H
#define SATELLITE_H
#include <iostream>
#include <matrix.h>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

class Satellite {

public:
    //Constructor
    Satellite ();

    // Overload Constructor
    Satellite(string name);
    //Setters
    void setMass(double m);
    void setPosition(double x,  double y, double z);
    void setPosX(double x);
    void setPosY(double y);
    void setPosZ(double z);

    //Getters
    string getName() const;
    double getRelativeDistance(const Satellite ball);

private:
    string satelliteName;
    double satelliteMass;
    double satelliteVelocity;
    double posX;
    double posY;
    double posZ;

};

#endif // SATELLITE_H
