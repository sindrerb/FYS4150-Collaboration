#ifndef SATELLITE_H
#define SATELLITE_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Satellite
{
private:
    string myName;
    double Mass;
//    double *possition = new double[3];
    double Xpos;
    double Ypos;
    double Zpos;

public:

    //Constructor
    Satellite(string name);

    //Setters
    void setMass(double M);
    void setPos(double X,double Y,double Z);

    //Getters
    double getRelativeDist(const Satellite ball);
    string getName();
};

#endif // SATELLITE_H
