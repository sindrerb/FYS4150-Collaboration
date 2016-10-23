#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
//#include "matrix.h"
#include "vec3.h"
#include "solarsystem.h"
#include "satellite.h"
#include "numericalsolver.h"

using namespace std;

int main(int argc, char *argv[]){
//    if(argc>6){
        double timeSpan, timeStep;
        int startIteration;
        string infile,outfile,solarCenter,simulationMethod;
//        timeSpan   = atof(argv[1]);
//        iterations = int(atof(argv[2]));
//        startIteration = atoi(argv[3]);
//        simulationMethod = string(argv[4]);

        cout << "********************************************************************************" << endl;
        cout << "                       SOLAR SYSTEM SIMULATER 9000                              " << endl;
        cout << "********************************************************************************" << endl;
        cout << "USAGE INFO" << endl;

        cout << "Type preffered simulation method ( \"euler\", \"verlet\" or \"relativistic\" ) : " ;
        cin >> simulationMethod ;

        cout << "Type 0 - for moving sun. Type 1 - for stationary sun: " ;
        cin >> startIteration;

        cout << "Type simulation time in years: " ;
        cin >> timeSpan;

        cout << "\n Values that work well\n\t euler: 1e-6 \n\t verlet: 1e-4 \n\t relativistic: 1e-9)" << endl; ;
        cout << "Type preffered time step : ";
        cin >> timeStep;

        if(simulationMethod!="euler" && simulationMethod!="verlet" && simulationMethod!="relativistic") {
            cout << "Did not recognize the argument "<<simulationMethod<<", running with verlet method.\n";
            simulationMethod = "verlet";
        }

        infile     = "solarSystem.txt";//string(argv[5]);
        outfile    = "testOutput.txt";//string(argv[6]);

        int iterations = timeSpan/timeStep;

        cout << "********************************************************************************" << endl;
        cout << "                               SIMULATING                                       " << endl;
        cout << "********************************************************************************" << endl;
        cout << "\nSimulating system from: "<<infile<<" \n\t using:\t "<<simulationMethod<<"\n\t over:\t "<<timeSpan<<" years\n\t with:\t "<<iterations<<" iterations.\n" << endl;

        SolarSystem solarSystem;
        solarSystem.createSolarSystem(infile);
        solarSystem.simulate(timeSpan,iterations,startIteration,simulationMethod,outfile);
        cout << "Wrote information to: "<< outfile << endl;
//        cout << "Running simulation from "<<infile<<" using "<<simulationMethod<<" with "<<startIteration<<" locked objects, over "<<timeSpan<<" years with "<<iterations<<" iterations.\nWriting to "<<outfile<<endl;
        return 0;
//    } else {
//        cout <<"Write arguments:\n -Time span in years\n -Iterations(example: 1e5)\n -Number of locked objects (N first planets in inputfile))\n -Simulation method (euler,verlet,relativistic)\n -Inputfile\n -Outputfile\n";
//    }
}
