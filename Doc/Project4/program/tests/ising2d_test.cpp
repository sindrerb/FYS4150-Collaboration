#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/ising2d.h"
//#include <time.h>

SCENARIO("Checking lattice creation") {

    Ising2D ising = Ising2D();
    ising.setSpin(2);
    GIVEN("A 2x2 lattice") {
        WHEN("Initializing ground state") {
            ising.initializeGroundStateLattice();
            THEN( "All spinns have value 1(spin up)" ) {
                REQUIRE( ising.getLattice()[0][0] == 1 );
                REQUIRE( ising.getLattice()[1][0] == 1 );
                REQUIRE( ising.getLattice()[0][1] == 1 );
                REQUIRE( ising.getLattice()[1][1] == 1 );
            }
        }
        AND_WHEN("Initializing random state") {
            ising.initializeRandomStateLattice();
            THEN( "All spinns should be 1 or -1" ) {
                if (ising.getLattice()[0][0] != 1) {
                    REQUIRE( ising.getLattice()[0][0] == -1);
                } if  (ising.getLattice()[0][0] != -1) {
                    REQUIRE( ising.getLattice()[0][0] == 1);
                } if (ising.getLattice()[1][0] != 1) {
                    REQUIRE( ising.getLattice()[1][0] == -1);
                } if  (ising.getLattice()[1][0] != -1) {
                    REQUIRE( ising.getLattice()[1][0] == 1);
                } if (ising.getLattice()[0][1] != 1) {
                    REQUIRE( ising.getLattice()[0][1] == -1);
                } if  (ising.getLattice()[0][1] != -1) {
                    REQUIRE( ising.getLattice()[0][1] == 1);
                } if (ising.getLattice()[1][1] != 1) {
                    REQUIRE( ising.getLattice()[1][1] == -1);
                } if (ising.getLattice()[1][1] != -1) {
                    REQUIRE( ising.getLattice()[1][1] == 1);
                }
            }
        }
    }
}

//SCENARIO( "Checking Ground state energy" ) {
//    Ising2D ising = Ising2D();
//    ising.setSpin(2);
//    GIVEN("A 2x2 lattice") {
//        WHEN("Initializing ground state") {
//            ising.initializeGroundStateLattice();
//            THEN( "Energy should equal 2*n*n = 8" ) {
//                REQUIRE( ising.getEnergy() == 8 );
//            }
//        }
//    }
//}



//SCENARIO("Checking lattice creation") {

//    Ising2D ising = Ising2D();
//    ising.setSpin(2);
//    GIVEN("A 2x2 lattice") {
//        WHEN("Initializing ground state") {
//            ising.initializeGroundStateLattice();
//            THEN( "All spinns have value 1(spin up)" ) {
//                REQUIRE( ising.getLattice()[0][0] == 1 );
//                REQUIRE( ising.getLattice()[1][0] == 1 );
//                REQUIRE( ising.getLattice()[0][1] == 1 );
//                REQUIRE( ising.getLattice()[1][1] == 1 );
//            }
//        }
//    }
//}





//SCENARIO( "Creating satellite objects" ) {

//    GIVEN( "Satellite created from empty constructor Satellite();" ) {
//        Satellite satellite = Satellite();

//        WHEN( "When calling member variables" ) {
//            vec3 position = satellite.position();
//            vec3 velocity = satellite.velocity();
//            THEN( "All equal Zero" ) {

//                REQUIRE( satellite.mass() == 0 );
//                REQUIRE( position.x() == 0 );
//                REQUIRE( position.y() == 0 );
//                REQUIRE( position.z() == 0 );
//                REQUIRE( velocity.x() == 0 );
//                REQUIRE( velocity.y() == 0 );
//                REQUIRE( velocity.z() == 0 );
//            }
//        }

//        AND_WHEN( "calling global variables" ) {

//            THEN( "All equal Zero" ) {

//                REQUIRE( satellite.position().x() == 0 );
//                REQUIRE( satellite.position().y() == 0 );
//                REQUIRE( satellite.position().z() == 0 );
//                REQUIRE( satellite.velocity().x() == 0 );
//                REQUIRE( satellite.velocity().y() == 0 );
//                REQUIRE( satellite.velocity().z() == 0 );
//            }
//        }
//    }

//    GIVEN( "Satellite created from Satellite(mass, position, velocity);") {
//        Satellite satellite = Satellite( 10, vec3(1,2,3), vec3(2,4,6)  );

//        WHEN( "When calling member variables" ) {
//            vec3 position = satellite.position();
//            vec3 velocity = satellite.velocity();

//            THEN( "All equal argument values" ) {
//                REQUIRE( satellite.mass() == 10 );
//                REQUIRE( position.x() == 1 );
//                REQUIRE( position.y() == 2 );
//                REQUIRE( position.z() == 3 );
//                REQUIRE( velocity.x() == 2 );
//                REQUIRE( velocity.y() == 4 );
//                REQUIRE( velocity.z() == 6 );
//            }
//        }
//    }
//}

//SCENARIO( "Calculating relative distance" ) {

//    GIVEN( "Two satellites" ) {
//        Satellite satellite1 = Satellite( 10, vec3(0,0,0), vec3(0,0,0) );
//        Satellite satellite2 = Satellite( 10, vec3(1,1,1), vec3(1,1,1)  );
//        WHEN( "calculating ralative distance between" ) {
//            double relativeDistance = satellite1.relativeDistanceTo( satellite2 );
//            THEN( "return double" ) {
//                REQUIRE( relativeDistance == sqrt(3) );
//            }
//        }
//    }
//}
