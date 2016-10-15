#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/satellite.h"
#include "../src/vec3.h"


SCENARIO( "Creating satellite objects" ) {

    GIVEN( "Satellite created from empty constructor Satellite();" ) {
        Satellite satellite = Satellite();

        WHEN( "When calling member variables" ) {
            vec3 position = satellite.position();
            vec3 velocity = satellite.velocity();
            THEN( "All equal Zero" ) {

                REQUIRE( satellite.mass() == 0 );
                REQUIRE( position.x() == 0 );
                REQUIRE( position.y() == 0 );
                REQUIRE( position.z() == 0 );
                REQUIRE( velocity.x() == 0 );
                REQUIRE( velocity.y() == 0 );
                REQUIRE( velocity.z() == 0 );
            }
        }

        AND_WHEN( "calling global variables" ) {

            THEN( "All equal Zero" ) {

                REQUIRE( satellite.g_position.x() == 0 );
                REQUIRE( satellite.g_position.y() == 0 );
                REQUIRE( satellite.g_position.z() == 0 );
                REQUIRE( satellite.g_velocity.x() == 0 );
                REQUIRE( satellite.g_velocity.y() == 0 );
                REQUIRE( satellite.g_velocity.z() == 0 );
            }
        }
    }

    GIVEN( "Satellite created from Satellite(mass, position, velocity);") {
        Satellite satellite = Satellite( 10, vec3(1,2,3), vec3(2,4,6)  );

        WHEN( "When calling member variables" ) {
            vec3 position = satellite.position();
            vec3 velocity = satellite.velocity();

            THEN( "All equal argument values" ) {
                REQUIRE( satellite.mass() == 10 );
                REQUIRE( position.x() == 1 );
                REQUIRE( position.y() == 2 );
                REQUIRE( position.z() == 3 );
                REQUIRE( velocity.x() == 2 );
                REQUIRE( velocity.y() == 4 );
                REQUIRE( velocity.z() == 6 );
            }
        }
    }
}

SCENARIO( "Calculating relative distance" ) {

    GIVEN( "Two satellites" ) {
        Satellite satellite1 = Satellite( 10, vec3(0,0,0), vec3(0,0,0) );
        Satellite satellite2 = Satellite( 10, vec3(1,1,1), vec3(1,1,1)  );
        WHEN( "calculating ralative distance between" ) {
            double relativeDistance = satellite1.relativeDistanceTo( satellite2 );
            THEN( "return double" ) {
                REQUIRE( relativeDistance == sqrt(3) );
            }
        }
    }
}





//TEST_CASE("Creating satellite") {
//    Satellite satellite;
//    vec3 vec;
////    SECTION ( "Create satellite object with position, velocity and mass" ) {};
////    INFO ( "FAILED to set position" ) satellite.setSatellitePosition(vec3(1,1,1));
////    INFO ( "FAILED to set velocity" )satellite.setSatelliteVelocity(vec3(1,2,3));
////    INFO ( "FAILED to set mass" )satellite.setSatelliteMass(20);
////    CAPTURE ( satellite.getSatellitePosition() );
////    CAPTURE ( satellite.getSatelliteVelocity() );
//    CAPTURE ( satellite.getMass() );

////    REQUIRE( satellite.getSatellitePosition().approxEqual(vec3(1,1,1) ));

////    CHECK ( satellite.getSatellitePosition() == vec(1,1,1) );
////    CHECK ( satellite.getSatelliteVelocity() == vec(1,2,3) );
//    CHECK ( satellite.getMass() == 10) ;
//  }
