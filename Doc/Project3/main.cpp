#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <satellite.h>
#include <matrix.h>

using namespace std;
ofstream ofile;

Matrix euler(Matrix vector, Matrix derivative,double step){
    Matrix newVector;
    newVector = vector + derivative*step;
    return newVector;
}

Matrix verlet(Matrix vector, Matrix derivative,double step){
    Matrix newVector;
    newVector = vector + derivative*step;
    return newVector;
}

Matrix accerelation(Matrix position, double distance){
    Matrix acc;
    acc = position*(-39.4761/(distance*distance*distance));
//    acc.print("acc");
    return acc;
}

int main(){
    string filename = "Pos.txt";
    double h = 1E-5;
    Satellite sun("sun"),mercury("mercury"),venus("venus"),earth("earth"),mars("mars"),jupiter("jupiter"),saturn("saturn"),uranus("uranus"),neptun("neptun"),pluto("pluto");
    Satellite object[2] = { sun , earth };
//    Matrix initialPosSun,initialPosEarth, initialVelEarth;
//    initialVelEarth.setOnes(3,1);
//    initialVelEarth = initialVelEarth *0.2;
//    initialPosSun.setZeros(3,1);
//    initialPosEarth.setOnes(3,1);
//    sun.setPosition(initialPosSun);
//    earth.setPosition(initialPosEarth);
//    earth.setVelocity(initialVelEarth);

    int numberOfSatellites = sizeof(object)/sizeof(*object);

    Matrix position, velocity;
    position.setZeros(3,1);
    velocity.setZeros(3,1);
    string line;
    for(int i = 0; i< numberOfSatellites;i++){
        ifstream satelliteData("../"+object[i].getName()+"_pos.txt");
        int j = 0;
        while(getline(satelliteData,line,',')){
            if(j>=26 && j<=28){
                position.setElement(j-26,0,stof(line));
            }else if(j>=29 && j<=31){
                velocity.setElement(j-29,0,stof(line));
            }
            j++;
        }
        object[i].setPosition(position);
        object[i].setVelocity(velocity);
    }



    int i = 1;
    Matrix pos, vel, sunPos;
//    pos.setZeros(3,1);
//    object[0].setPosition(pos);
//    vel.setZeros(3,1);
//    pos.setElement(0,0,1);
//    vel.setElement(1,0,6.28);  //2pi??

//    object[i].setPosition(pos);
//    object[i].setVelocity(vel);

    ofile.open(filename);
    ofile << "Position \n  x \t y \t z " << endl;
    ofile.close();

    double R;
    for(int j = 0; j<1E5; j++) {
        pos = object[i].getPosition();
        vel = object[i].getVelocity();
//        pos.print("pos");
//        vel.print("vel");
        R = object[i].getRelativeDistTo(object[0],0);
        object[i].setPosition(euler(pos,vel,h));
        object[i].setVelocity(euler(vel,accerelation(pos,R),h));
        pos = object[i].getPosition();
        pos.printToFile(filename);
    }




}
