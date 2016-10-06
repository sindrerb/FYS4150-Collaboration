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
    string satelliteName;
    double satelliteMass;
    Matrix satellitePosition;
    Matrix satelliteVelocity;
    double posX;
    double posY;
    double posZ;

public:
    Satellite ();                   //Constructor
    Satellite(string name);         //Overload constructor

    //Setters
    void setSatelliteName(string name);
    void setSatelliteMass(double mass);
    void setPosZ(double zCoordinate);
    void setPosY(double yCoordinate);
    void setPosX(double xCoordinate);
    void setSatellitePosition(Matrix position);

    //Getters

    string getSatelliteName() const;
    double getSatelliteMass() const;
    double getPosZ() const;
    double getPosY() const;
    double getPosX() const;
    Matrix getSatellitePosition() const;
    double getRelativeDist(const Satellite name);

};

#endif // SATELLITE_H
