#include "catch.hpp"
#include "../src/solarsystem.h"
#include "../src/vec3.h"

SCENARIO( "Creating vector of Satellites in SolarSystem" ) {
    SolarSystem system;
    system.createSatellite(0, vec3(0,0,0), vec3(0,0,0));
    system.createSatellite(1, vec3(1,1,1), vec3(1,1,1));

    GIVEN( "That 2 Satellites where made" ) {
        vector<Satellite> satellites = system.satellites();
        Satellite satellite1 = satellites[0];
        Satellite satellite2 = satellites[1];
        THEN( "vector size equal 2" ){
            REQUIRE( satellites.size() == 2 );
            REQUIRE( satellites.capacity() >= 2 );
        }
    }

    system.createSatellite(2, vec3(2,2,2), vec3(2,2,2));

    GIVEN( "one more is created" ) {
        vector<Satellite> satellites = system.satellites();
        Satellite satellite3 = satellites[2];
        THEN( " one more is added  " ) {
            REQUIRE( satellites.size() == 3 );
            REQUIRE( satellites.capacity() >= 3 );
        }
    }
}

SCENARIO( "Calculating gravitational force" ) {
    SolarSystem system;
    system.createSatellite(0, vec3(0,0,0), vec3(0,0,0));
    system.createSatellite(1, vec3(1,1,1), vec3(1,1,1));

    GIVEN( "Two satellite objects" ) {
        vector<Satellite> satellites = system.satellites();
        Satellite satellite1 = satellites[0];
        Satellite satellite2 = satellites[1];

        WHEN( "Calculating gravitational force" ) {
            vec3 gravitationalForce = system.gravitationalForce( satellite1, satellite2 );

            THEN( "The components of the vecor have the correct value" ) {
                REQUIRE( gravitationalForce.x() == Approx( -7.5976) );
                REQUIRE( gravitationalForce.y() == Approx( -7.5976) );
                REQUIRE( gravitationalForce.z() == Approx( -7.5976) );
            }
        }
    }
}

SCENARIO( "Using functions to update values " ) {
    SolarSystem system;
    system.createSatellite(0, vec3(0,0,0), vec3(0,0,0));
    system.createSatellite(1, vec3(1,1,1), vec3(1,1,1));
    system.createSatellite(2, vec3(2,2,2), vec3(2,2,2));
    system.setMethod("euler");
    double timeSpan = 100;
    int iterations = 1000;
    double timeStep = timeSpan/iterations;
    system.setTimeStep( timeStep );
    system.setHalfTimeStep( timeStep * 0.5);
    system.setHalfTimeStepSquared( timeStep*timeStep*0.5 );

//    system.updateForces();
    system.updatePositionsEuler();
    system.check();
//    system.simulate(timeSpan,iterations,"test.txt");

    GIVEN( "Three satellite objects" ) {
        vector<Satellite> satellites = system.satellites();
        Satellite satellite1 = satellites[0];
        Satellite satellite2 = satellites[1];
        Satellite satellite3 = satellites[2];


        WHEN( "Updating position using velocity verlet" ) {
            REQUIRE( satellite1.g_position.x() == 0 );
            REQUIRE( satellite1.g_position.y() == 0 );
            REQUIRE( satellite1.g_position.z() == 0 );

            REQUIRE( satellite2.g_position.x() != 1 );
            REQUIRE( satellite2.g_position.y() != 1 );
            REQUIRE( satellite2.g_position.z() != 1 );

            REQUIRE( satellite3.g_position.x() != 2 );
            REQUIRE( satellite3.g_position.y() != 2 );
            REQUIRE( satellite3.g_position.z() != 2 );
        }
    }
}
