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
