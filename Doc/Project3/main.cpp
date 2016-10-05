#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include "satellite.h"
#include "matrix.h"

using namespace std;

Matrix euler(Matrix vector, Matrix derivative,double step){
    Matrix newVector;
    newVector = vector + derivative*step;
    return newVector;
}

void initializeSatellite(Satellite satellite){
    string satelliteName = satellite.getName();
    ifstream satelliteData(satelliteName+"_pos.txt");
    string line;
    int i = 0;
    Matrix position, velocity;
    position.setZeros(1,3);
    velocity.setZeros(1,3);
    while(getline(satelliteData,line,',')){
        if(i>=26 && i<=28){
            cout << i << "\t";
            cout << line << endl;
            position.setElement(0,i-26,stod(line));
        }else if(i>=29 && i<=31){
            velocity.setElement(0,i-29,stod(line));
        }
        i++;
    }
}

int main(){
    double h = 0.01;
    Satellite sun("sun"),mercury("mercury"),venus("venus"),earth("earth"),mars("mars"),jupiter("jupiter"),saturn("saturn"),uranus("uranus"),neptun("neptun"),pluto("pluto");
    Satellite solarSystem[1] = { earth };
    Matrix initialPosSun,initialPosEarth;
    initialPosSun.setZeros(1,3);
    initialPosEarth.setOnes(1,3);
    sun.setPosition(initialPosSun);
    earth.setPosition(initialPosEarth);


    earth.getPosition().print("Earth pos");
    earth.getVelocity().print("Earth vel");
    //earth.setPosition(euler(earth.getPosition(),h));




//    cout << earth.getRelativeDistTo(sun) <<endl;

//    int numberOfSatellites = sizeof(solarSystem)/sizeof(*solarSystem);
//    for(int i = 0; i< numberOfSatellites;i++){
//        initializeSatellite(solarSystem[i]);
//    }

    return 0;
}
