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
    if(argc>6){
        double timeSpan;
        int iterations,startIteration;
        string infile,outfile,solarCenter,simulationMethod;
        timeSpan   = atof(argv[1]);
        iterations = int(atof(argv[2]));
        solarCenter = string(argv[3]);
        simulationMethod = string(argv[4]);

        if(solarCenter=="locked") {
            startIteration = 1;
        }else if(solarCenter=="free") {
            startIteration = 0;
        }else {
            cout << "Did not recognize the argument "<<solarCenter<<", running with stationary sun.\n";
            startIteration = 1;
            solarCenter = "locked";
        }

        if(simulationMethod!="euler" && simulationMethod!="verlet" && simulationMethod!="relativistic") {
            cout << "Did not recognize the argument "<<simulationMethod<<", running with verlet method.\n";
            simulationMethod = "verlet";
        }

        infile     = string(argv[5]);
        outfile    = string(argv[6]);

        SolarSystem solarSystem;
        solarSystem.createSolarSystem(infile);
        solarSystem.simulate(timeSpan,iterations,startIteration,simulationMethod,outfile);
        cout << "Running simulation from "<<infile<<" using "<<simulationMethod<<" with a "<<solarCenter<<" sun, over "<<timeSpan<<" years with "<<iterations<<" iterations.\nWriting to "<<outfile<<endl;
        return 0;
    }else{
        cout <<"Write arguments:\n -Time span in years\n -Iterations(example: 1e5)\n -Solar center (locked/free)\n -Simulation method (euler,verlet,relativistic)\n -Inputfile\n -Outputfile\n";
    }
}
