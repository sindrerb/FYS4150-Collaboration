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
    if(argc>4){
        double timeSpan;
        int iterations;
        string infile,outfile;
        timeSpan   = atof(argv[1]);
        iterations = int(atof(argv[2]));
        infile     = string(argv[3]);
        outfile    = string(argv[4]);

        SolarSystem solarSystem;
        solarSystem.createSolarSystem(infile);
        solarSystem.simulate(timeSpan,iterations,outfile);
        cout << "Running simulation from "<<infile<<" over "<<timeSpan<<" years with "<<iterations<<" iterations.\nWriting to "<<outfile<<endl;
        return 0;
    }else{
        cout <<"Write arguments:\n -Time span\n -Iterations\n -Inputfile\n -Outputfile\n";
    }
}

