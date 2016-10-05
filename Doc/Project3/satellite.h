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
    double Mass;
    double Xpos;
    double Ypos;
    double Zpos;

public:
    //Constructor
    Satellite ();

    //Setters
    void setMass(double M);
    void setPos(double X,double Y,double Z);

    //Getters
    double getRelativeDist(const Satellite ball);

};

#endif // SATELLITE_H
