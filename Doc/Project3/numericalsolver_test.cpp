//#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "numericalsolver.h"
#include "vec3.h"
#include "satellite.h"

TEST_CASE("Creating satellit13e") {
    Satellite satellite;
    vec3 vec;
    SECTION ( "Create satellite object with position, velocity and mass" );
    INFO ( "FAILED to set position" ) satellite.setSatellitePosition(vec3(1,1,1));
    INFO ( "FAILED to set velocity" )satellite.setSatelliteVelocity(vec3(1,2,3));
    INFO ( "FAILED to set mass" )satellite.setSatelliteMass(10);
    CAPTURE ( satellite.getSatellitePosition() );
    CAPTURE ( satellite.getSatelliteVelocity() );
    CAPTURE ( satellite.getSatelliteMass() );
//    CHECK ( satellite.getSatellitePosition() == vec(1,1,1) );
//    CHECK ( satellite.getSatelliteVelocity() == vec(1,2,3) );
    CHECK ( satellite.getSatelliteMass() == 50) ;
  }

//TEST_CASE("Numerical solver") {
//    SECTION ( "Testing euler" );
//    INFO ( "FAILED to calculate positive values" ) NumericalSolver.solveEuler(vec3(1,1,1),vec3(1,1,1),1)
//    INFO ( "FAILED to calculate negative values" ) NumericalSolver.solveEuler(vec3(1,1,1),vec3(1,1,1),1)

//    CAPTURE ( NumericalSolver. );
//    CAPTURE ( satellite.getSatelliteVelocity() );
//    CAPTURE ( satellite.getSatelliteMass() );
////    CHECK ( satellite.getSatellitePosition() == vec(1,1,1) );
////    CHECK ( satellite.getSatelliteVelocity() == vec(1,2,3) );
//    CHECK ( satellite.getSatelliteMass() == 10) ;
//  }
