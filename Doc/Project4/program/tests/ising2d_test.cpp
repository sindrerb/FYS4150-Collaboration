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
        WHEN("Initializing random state") {
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

SCENARIO( "Checking Ground state energy" ) {
    Ising2D ising = Ising2D();
    ising.setSpin(2);
    GIVEN("A 2x2 lattice") {
        WHEN("Initializing ground state") {
            ising.initializeGroundStateLattice();
            THEN( "Energy should equal 2*n*n = 8" ) {
                REQUIRE( ising.getEnergy() == -8 );
            }
        }
    }
}

SCENARIO( "Checking energies for random initialized lattice","[random]" ) {
    Ising2D ising = Ising2D();
    ising.setSpin(2);
    WHEN("Initializing random state") {
        ising.initializeRandomStateLattice();

        bool energyFalse = false;
        int spinSum = ising.getLattice()[0][0] + ising.getLattice()[1][0] + ising.getLattice()[0][1] + ising.getLattice()[1][1];
        if (spinSum == 4) {
            THEN("With spin sum = 4, Energy = -8") {
                REQUIRE ( ising.getEnergy() == -8);
            }
        }else if (spinSum == 2) {
            THEN("With spin sum = 2, Energy = 0") {
                REQUIRE ( ising.getEnergy() == 0);
            }
        }else if (spinSum == -2) {
            THEN("With spin sum = -2, Energy = 0") {
                REQUIRE ( ising.getEnergy() == 0);
            }
        }else if (spinSum == -4) {
            THEN("With spin sum = -4, Energy = -8") {
                REQUIRE ( ising.getEnergy() == -8  );
            }
        }else if (spinSum == 0) {
            if( ising.getEnergy() == 0 || ising.getEnergy() == 8) {
                THEN("With spin sum = 0, Energy = -8 or 0 (true)") {
                    bool energy = true;
                    REQUIRE(energy == true);
                }
            }
        } else {
            bool result = true;
            REQUIRE_FALSE( result );
        }
    }
}

SCENARIO("Check pseudo lattice") {
    Ising2D ising = Ising2D();
    ising.setSpin(2);
    ising.initializeGroundStateLattice();
    WHEN("2x2 lattice in ground state (all spin up = 1)") {
        THEN("Pseudolattice should have all spin up") {

            REQUIRE(ising.getPseudoLattice()[1][0] == &ising.getLattice()[0][1]);
            REQUIRE(ising.getPseudoLattice()[0][1] == &ising.getLattice()[1][0]);

            REQUIRE(ising.getPseudoLattice()[2][0] == &ising.getLattice()[1][1]);
            REQUIRE(ising.getPseudoLattice()[3][1] == &ising.getLattice()[0][0]);

            REQUIRE(ising.getPseudoLattice()[2][0] == &ising.getLattice()[1][1]);
            REQUIRE(ising.getPseudoLattice()[1][3] == &ising.getLattice()[0][0]);

            REQUIRE(ising.getPseudoLattice()[3][2] == &ising.getLattice()[0][1]);
            REQUIRE(ising.getPseudoLattice()[2][3] == &ising.getLattice()[1][0]);

            REQUIRE(*ising.getPseudoLattice()[0][0] == 0);
            REQUIRE(*ising.getPseudoLattice()[3][0] == 0);
            REQUIRE(*ising.getPseudoLattice()[0][3] == 0);
            REQUIRE(*ising.getPseudoLattice()[3][3] == 0);
            REQUIRE(ising.getPseudoLattice()[0][0] == ising.getPseudoLattice()[3][3]);
            REQUIRE(ising.getPseudoLattice()[0][0] == ising.getPseudoLattice()[3][0]);
            REQUIRE(ising.getPseudoLattice()[0][0] == ising.getPseudoLattice()[0][3]);
        }
    }

    AND_WHEN("2x2 lattice in random state") {
        ising.initializeRandomStateLattice();
        THEN("Pseudolattice should point to values in lattice") {

            REQUIRE(ising.getPseudoLattice()[1][0] == &ising.getLattice()[0][1]);
            REQUIRE(ising.getPseudoLattice()[0][1] == &ising.getLattice()[1][0]);

            REQUIRE(ising.getPseudoLattice()[2][0] == &ising.getLattice()[1][1]);
            REQUIRE(ising.getPseudoLattice()[3][1] == &ising.getLattice()[0][0]);

            REQUIRE(ising.getPseudoLattice()[2][0] == &ising.getLattice()[1][1]);
            REQUIRE(ising.getPseudoLattice()[1][3] == &ising.getLattice()[0][0]);

            REQUIRE(ising.getPseudoLattice()[3][2] == &ising.getLattice()[0][1]);
            REQUIRE(ising.getPseudoLattice()[2][3] == &ising.getLattice()[1][0]);

            REQUIRE(*ising.getPseudoLattice()[0][0] == 0);
            REQUIRE(*ising.getPseudoLattice()[3][0] == 0);
            REQUIRE(*ising.getPseudoLattice()[0][3] == 0);
            REQUIRE(*ising.getPseudoLattice()[3][3] == 0);
            REQUIRE(ising.getPseudoLattice()[0][0] == ising.getPseudoLattice()[3][3]);
            REQUIRE(ising.getPseudoLattice()[0][0] == ising.getPseudoLattice()[3][0]);
            REQUIRE(ising.getPseudoLattice()[0][0] == ising.getPseudoLattice()[0][3]);
        }
    }
}

