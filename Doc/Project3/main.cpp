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

Matrix acceleration(Matrix position, double distance){  // Calculates acceleration relation between two objects
    Matrix acc;
    acc = position*(-39.4761/(distance*distance*distance));
//    acc.print("acc");
    return acc;
}

int main(){
    /*##########    ALL PLANETS AND MOONS       ############*/
//    Satellite sun("sun"),mercury("mercury"),venus("venus"),earth("earth"),mars("mars"),jupiter("jupiter"),saturn("saturn"),uranus("uranus"),neptun("neptun"),pluto("pluto");
    double SUN_MASS = 1000;
    Matrix initialPos(0,0,0), initialVel(0,0,0), initialAcc(0,0,0);
    Satellite sun("Sun",SUN_MASS,initialPos,initialVel,initialAcc);

    double EARTH_MASS = 0.00300150829;
    Matrix earthInitialPos(0,0,1), earthInitialVel(1,0,6.28), earthInitialAcc(0,0,0);
    Satellite earth("Earth",EARTH_MASS,earthInitialPos,earthInitialVel,earthInitialAcc);

    /*########     USER INPUT     #########*/
    Satellite object[2] = { sun , earth };  //List of the objects that are in use, the Sun must be the first element
    string filename = "PositionFile.txt";
    double finalTime, N;
    finalTime = 30;
    N = 1E5;

   double timeStep = finalTime/N;
//    Matrix initialPos,initialVel,initialAcc;
//    double mass;
    //Set up system with only Sun and Earth
//    initialPos.setZeros(3,1);
//    initialVel.setZeros(3,1);
//    initialAcc.setZeros(3,1);

//    mass = 1000;
//    sun.setPosition(initialPos);
//    sun.setVelocity(initialVel);
//    sun.setAcceleration(initialAcc);
//    sun.setMass(mass);

//    Matrix initialVel(0,0,0);
//    Matrix initialAcc(0,0,0);


//    initialPos.setElement(0,0,1);
//    initialVel.setElement(1,0,6.28);  //2pi??
//    mass = 0.00300150829;

//    earth.setPosition(initialPos);
//    earth.setVelocity(initialVel);
//    earth.setAcceleration(initialAcc);
//    earth.setMass(mass);

//    initialPos.setElement(0,0,10);
//    initialVel.setElement(1,0,2);  //2pi??
//    mass = 0.954248366;

//    jupiter.setPosition(initialPos);
//    jupiter.setVelocity(initialVel);
//    jupiter.setAcceleration(initialAcc);
//    jupiter.setMass(mass);

//    Satellite object[3] = { sun , earth , jupiter};  //List of the objects that are in use, the Sun must be the first element

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

    Matrix pos, vel, acc, zeroColumn;
    zeroColumn.setZeros(3,1);
    pos = zeroColumn;
    vel = zeroColumn;
    acc = zeroColumn;

//    for(int i = 1; i<numberOfSatellites; i++){
//        ofile.open(object[i].getName());
//        ofile << object[i].getName() << " position \n  x \t y \t z " << endl;
//        ofile.close();
//    }
    double R,time;
    time = 0;
int numberOfSatellites = 2;
    Matrix i_acc, j_acc, j_pos;
    i_acc.setZeros(3,1);
    j_acc.setZeros(3,1);
    j_pos.setZeros(3,1);
    double i_m,j_m;
    while(time < finalTime) {
        for(int i = 1; i<numberOfSatellites; i++) {
            pos = object[i].getPosition();
            vel = object[i].getVelocity();
            R = object[i].getRelativeDistTo(object[0],0);
            acc = acceleration(pos,R);
            i_acc = object[i].getAcceleration();
            object[i].setAcceleration(j_acc+acc);
            if(numberOfSatellites>2) {
                for(int j = i+1; j<numberOfSatellites; j++) {
                    j_pos = object[j].getPosition();
                    R = object[i].getRelativeDistTo(object[j],0);
                    acc = acceleration(pos-j_pos,R);
                    i_m = object[i].getMass();
                    j_m = object[j].getMass();
                    i_acc = object[i].getAcceleration();
                    j_acc = object[j].getAcceleration();
                    object[i].setAcceleration(i_acc+acc*j_m);
                    object[j].setAcceleration(j_acc+acc*i_m);
                }
            }
            acc = object[i].getAcceleration();
            object[i].setPosition(euler(pos,vel,timeStep));
            object[i].setVelocity(euler(vel,acc,timeStep));
        }
        for(int i = 1; i<numberOfSatellites; i++){
            object[i].setAcceleration(zeroColumn);
            pos = object[i].getPosition();
            pos.printToFile(object[i].getName());
        }
        time += timeStep;
    }
}
