#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <satellite.h>
#include <matrix.h>

using namespace std;
ofstream ofile;

Matrix euler(Matrix vector, Matrix derivative,double step) { //Solving next step using Euler Forward method
    Matrix newVector;
    newVector = vector + derivative*step;
    return newVector;
}

Matrix verlet(Matrix vector, Matrix derivative,double step) { //Solving next step using Verlet velocity method
    Matrix newVector;
    newVector = vector + derivative*step;
    return newVector;
}

Matrix accerelation(Matrix position, double distance){  // Calculates acceleration relation between two objects
    Matrix acc;
    acc = position*(-39.4761/(distance*distance*distance));
//    acc.print("acc");
    return acc;
}

int main(){
    /*##########    ALL PLANETS AND MOONS       ############*/
    Satellite sun("sun"),mercury("mercury"),venus("venus"),earth("earth"),mars("mars"),jupiter("jupiter"),saturn("saturn"),uranus("uranus"),neptun("neptun"),pluto("pluto");

    /*########     USER INPUT     #########*/
    //Satellite object[2] = { sun , earth };  //List of the objects that are in use, the Sun must be the first element
    string filename = "PositionFile.txt";
    double finalTime, N;
    finalTime = 1.0;
    N = 1E2;
    int task = 1;

    double timeStep = finalTime/N;
    Matrix initialPos,initialVel;
    double mass;
    //Set up system with only Sun and Earth
    initialPos.setZeros(3,1);
    initialVel.setZeros(3,1);
    mass = 10E6;

    sun.setPosition(initialPos);
    sun.setVelocity(initialVel);
    sun.setMass(mass);

    initialPos.setElement(0,0,1);
    initialVel.setElement(1,0,6.28);  //2pi??
    mass = 1;

    earth.setPosition(initialPos);
    earth.setVelocity(initialVel);
    earth.setMass(mass);

    Satellite object[2] = { sun , earth };  //List of the objects that are in use, the Sun must be the first element

//        /*##### Set up system with Sun, Earth and Jupiter */
//        initialPos.setZeros(3,1);
//        initialVel.setZeros(3,1);
//        mass = 10E6;

//        sun.setPosition(initialPos);
//        sun.setVelocity(initialVel);
//        sun.setMass(mass);

//        initialPos.setElement(0,0,1);
//        initialVel.setElement(1,0,6.28);  //2pi??
//        mass = 1;

//        earth.setPosition(initialPos);
//        earth.setVelocity(initialVel);
//        earth.setMass(mass);

//        initialPos.setElement(0,0,4);
//        initialVel.setElement(1,0,6.28);  //2pi??
//        mass = 10E2;

//        jupiter.setPosition(initialPos);
//        jupiter.setVelocity(initialVel);
//        jupiter.setMass(mass);

//        Satellite object[3] = { sun , earth , jupiter};  //List of the objects that are in use, the Sun must be the first element
//        /*##### Sets up the whole solar system */
//        Satellite object[10] = { sun , mercury, venus, earth ,mars , jupiter, saturn, uranus, neptun ,pluto};  //List of the objects that are in use, the Sun must be the first element

//        int numberOfSatellites = sizeof(object)/sizeof(*object);

//        initialPos.setZeros(3,1);
//        initialVel.setZeros(3,1);
//        string line;
//        for(int i = 0; i< numberOfSatellites;i++){  //Loop over data from NASA
//            ifstream satelliteData("../"+object[i].getName()+"_pos.txt");
//            int j = 0;
//            while(getline(satelliteData,line,',')){
//                if(j>=26 && j<=28){
//                    initialPos.setElement(j-26,0,stof(line));
//                }else if(j>=29 && j<=31){
//                    initialVel.setElement(j-29,0,stof(line));
//                }
//                j++;
//            }
//            object[i].setPosition(initialPos);
//            object[i].setVelocity(initialVel);
//        }
//        string partLine;
//        int stringPos;
//        ifstream satelliteData("../"+object[0].getName()+".txt");
//        int j = 0;
//        while(getline(satelliteData,line,'\n')) {
//            cout << j << "\t";
//            cout << line << endl;
//            j++;
//            if(j==4) {
//                stringPos = line.find ('=');
//                cout << stringPos << endl;

//                }
//            }
//    }

    int i = 1;
    Matrix pos, vel;
    pos.setZeros(3,1);
    vel.setZeros(3,1);

    ofile.open(filename);
    ofile << "Position \n  x \t y \t z " << endl;
    ofile.close();

    double R,time;
    time = 0;
    while(time < finalTime) {
        pos = object[i].getPosition();
        vel = object[i].getVelocity();
        R = object[i].getRelativeDistTo(object[0],0);
        object[i].setPosition(euler(pos,vel,timeStep));
        object[i].setVelocity(euler(vel,accerelation(pos,R),timeStep));
        pos = object[i].getPosition();
        pos.printToFile(filename);
        time += timeStep;
    }
}
