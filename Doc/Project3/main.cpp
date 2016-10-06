#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "satellite.h"
#include "matrix.h"
#include "solarsystem.h"

using namespace std;



int main(){

    int NUMBER_OF_ITERATIONS = 1000;
    double START_TIME = 0;
    double END_TIME = 100;
    int stepLength = (END_TIME - START_TIME)/NUMBER_OF_ITERATIONS;

    Matrix velocitySun;
    Matrix positionSun;
    Matrix velocityEarth;
    Matrix positionEarth;

//  Satellite sun("Sun", positionSun, velocitySun);
//    Satellite earth("Earth", positionEarth, velocityEarth);

//    Matrix velocity;
//    velocity.setZeros(4,5);
//    velocity.setElement(1,0,5);
//    velocity.print("velocity");
//    string satelliteName;

//    cout << "Type a planet name: ";
//    cin >> satelliteName;

//    Satellite satelite1(satelliteName);

//    cout << "You made planet: " << satelite1.getName() <<endl;
}
