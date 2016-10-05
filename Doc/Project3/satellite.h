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
    double MASS;
    double posX;
    double posY;
    double posZ;

public:
    //Constructor
    Satellite ();

    //Setters
    void setMass(double m);
    void setPos(double x,  double y, double z);

    //Getters
    double getRelativeDist(const Satellite ball);

};

#endif // SATELLITE_H
