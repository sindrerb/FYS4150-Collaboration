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

SCENARIO( "Testing updateForces();","[acceleration]" ) {
    GIVEN( "System with three satellites" ) {
        SolarSystem system;
        system.createSatellite(10, vec3(0,0,0), vec3(0,0,0));
        system.createSatellite(1, vec3(1,1,1), vec3(1,1,1));
        system.createSatellite(2, vec3(2,2,2), vec3(2,2,2));
        system.setMethod("euler");
        system.setStartIteration( 1 );
        double timeSpan = 10; // Years
        int iterations = 10000;
        double timeStep = timeSpan/iterations;
        system.setTimeStep( timeStep );
        system.setHalfTimeStep( timeStep * 0.5);
        system.setHalfTimeStepSquared( timeStep * timeStep * 0.5 );

        WHEN( "updating forces for all planets (0 stationary)" ) {
            THEN ("Old acceleration gets value of new acceleration") {
                for (int i = 0; i < system.numberofsatellites(); i++  ) {
                    system.updateForces();
                }

                vector<Satellite> satellites = system.satellites();
                Satellite satellite1 = satellites[0];
                Satellite satellite2 = satellites[1];
                Satellite satellite3 = satellites[2];

                REQUIRE( satellite1.g_old_acceleration.x() == satellite1.g_new_acceleration.x() );
                REQUIRE( satellite1.g_old_acceleration.y() == satellite1.g_new_acceleration.y() );
                REQUIRE( satellite1.g_old_acceleration.z() == satellite1.g_new_acceleration.z() );

                REQUIRE( satellite2.g_old_acceleration.x() == satellite2.g_new_acceleration.x() );
                REQUIRE( satellite2.g_old_acceleration.y() == satellite2.g_new_acceleration.y() );
                REQUIRE( satellite2.g_old_acceleration.z() == satellite2.g_new_acceleration.z() );

                REQUIRE( satellite3.g_old_acceleration.x() == satellite3.g_new_acceleration.x() );
                REQUIRE( satellite3.g_old_acceleration.y() == satellite3.g_new_acceleration.y() );
                REQUIRE( satellite3.g_old_acceleration.z() == satellite3.g_new_acceleration.z() );
            }
        }
    }
}

SCENARIO( "Testing computational function","[computational]"  ) {
    GIVEN( "System with three satellites" ) {
        SolarSystem system;
        system.createSatellite(10, vec3(0,0,0), vec3(0,0,0));
        system.createSatellite(1, vec3(1,1,1), vec3(1,1,1));
        system.createSatellite(2, vec3(2,2,2), vec3(2,2,2));
        system.setMethod("euler");
        system.setStartIteration( 1 );
        double timeSpan = 10; // Years
        int iterations = 10000;
        double timeStep = timeSpan/iterations;
        system.setTimeStep( timeStep );
        system.setHalfTimeStep( timeStep * 0.5);
        system.setHalfTimeStepSquared( timeStep * timeStep * 0.5 );

        WHEN( "shifting Acceleration" ) {
            THEN ("Old acceleration gets value of new acceleration") {
                system.shiftAccelerations();
                vector<Satellite> satellites = system.satellites();
                Satellite satellite1 = satellites[0];
                Satellite satellite2 = satellites[1];
                Satellite satellite3 = satellites[2];

                REQUIRE( satellite1.g_old_acceleration.x() == satellite1.g_new_acceleration.x() );
                REQUIRE( satellite1.g_old_acceleration.y() == satellite1.g_new_acceleration.y() );
                REQUIRE( satellite1.g_old_acceleration.z() == satellite1.g_new_acceleration.z() );

                REQUIRE( satellite2.g_old_acceleration.x() == satellite2.g_new_acceleration.x() );
                REQUIRE( satellite2.g_old_acceleration.y() == satellite2.g_new_acceleration.y() );
                REQUIRE( satellite2.g_old_acceleration.z() == satellite2.g_new_acceleration.z() );

                REQUIRE( satellite3.g_old_acceleration.x() == satellite3.g_new_acceleration.x() );
                REQUIRE( satellite3.g_old_acceleration.y() == satellite3.g_new_acceleration.y() );
                REQUIRE( satellite3.g_old_acceleration.z() == satellite3.g_new_acceleration.z() );
            }
        }

        AND_WHEN( "updating position using Euler" ) {
            THEN ("position changes") {
                system.updatePositionsEuler();
                vector<Satellite> satellites = system.satellites();
                Satellite satellite1 = satellites[0];
                Satellite satellite2 = satellites[1];
                Satellite satellite3 = satellites[2];

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

        AND_WHEN( "updating velocity using Euler" ) {
            THEN ("velocity changes") {
                system.updateVelocitiesEuler();
                vector<Satellite> satellites = system.satellites();
                Satellite satellite1 = satellites[0];
                Satellite satellite2 = satellites[1];
                Satellite satellite3 = satellites[2];

                REQUIRE( satellite1.g_velocity.x() == 0 );
                REQUIRE( satellite1.g_velocity.y() == 0 );
                REQUIRE( satellite1.g_velocity.z() == 0 );

                REQUIRE( satellite2.g_velocity.x() == 1 );
                REQUIRE( satellite2.g_velocity.y() == 1 );
                REQUIRE( satellite2.g_velocity.z() == 1 );

                REQUIRE( satellite3.g_velocity.x() == 2 );
                REQUIRE( satellite3.g_velocity.y() == 2 );
                REQUIRE( satellite3.g_velocity.z() == 2 );
            }
        }

        system.updateForces();

        AND_WHEN( "updating position using Verlet" ) {
            THEN ("position changes") {
                system.updatePositionsVerlet();
                vector<Satellite> satellites = system.satellites();
                Satellite satellite1 = satellites[0];
                Satellite satellite2 = satellites[1];
                Satellite satellite3 = satellites[2];

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

        AND_WHEN( "updating velocity using Verlet" ) {
            THEN ("velocity changes") {
                system.updateVelocitiesVerlet();
                vector<Satellite> satellites = system.satellites();
                Satellite satellite1 = satellites[0];
                Satellite satellite2 = satellites[1];
                Satellite satellite3 = satellites[2];

                REQUIRE( satellite1.g_velocity.x() == 0 );
                REQUIRE( satellite1.g_velocity.y() == 0 );
                REQUIRE( satellite1.g_velocity.z() == 0 );

                REQUIRE( satellite2.g_velocity.x() != 1 );
                REQUIRE( satellite2.g_velocity.y() != 1 );
                REQUIRE( satellite2.g_velocity.z() != 1 );

                REQUIRE( satellite3.g_velocity.x() != 2 );
                REQUIRE( satellite3.g_velocity.y() != 2 );
                REQUIRE( satellite3.g_velocity.z() != 2 );
            }
        }
    }
}

SCENARIO( "Check that potential and kinetic energy is conserved", "[Energies]" ) {
    GIVEN( "System with two satellites" ) {
        SolarSystem system;

        system.createSatellite(1, vec3(0,0,0), vec3(0,0,0));
        system.createSatellite(3e-6, vec3(1,0,0), vec3(0,2*M_PI,0) );

        system.setMethod("euler");
        system.setStartIteration( 1 );
        double timeSpan = 10; // Years
        int iterations = 100000;
        double timeStep = timeSpan/iterations;
        system.setTimeStep( timeStep );
        system.setHalfTimeStep( timeStep * 0.5);
        system.setHalfTimeStepSquared( timeStep * timeStep * 0.5 );

        double kineticEnergyTwoSatelliteSystem = system.kineticEnergy();
        double potentialEnergyTwoSatelliteSystem = system.potentialEnergy();
        double totalEnergyTwoSatelliteSystem = system.totalEnergy();
        THEN( "Energies is calculated from constructor" ) {
            REQUIRE( system.kineticEnergy() != 0 );
            REQUIRE( system.potentialEnergy() != 0 );
            REQUIRE( system.totalEnergy() <= 0 );
        }

        system.createSatellite(954e-6, vec3(-5.2, 0, 0), vec3(0, -2.75 ,0));
        double kineticEnergyThreeSatelliteSystem = system.kineticEnergy();
        double potentialEnergyThreeSatelliteSystem = system.potentialEnergy();
        double totalEnergyThreeSatelliteSystem = system.totalEnergy();

        WHEN( "Another planet is added to the system" ) {
            THEN( "Energies of the new system change" ){
                REQUIRE( system.kineticEnergy() != 0 );
                REQUIRE( system.potentialEnergy() != 0 );
                REQUIRE( system.totalEnergy() <= 0 );
                REQUIRE( kineticEnergyTwoSatelliteSystem != kineticEnergyThreeSatelliteSystem );
                REQUIRE( potentialEnergyTwoSatelliteSystem != potentialEnergyThreeSatelliteSystem );
                REQUIRE( totalEnergyTwoSatelliteSystem != totalEnergyThreeSatelliteSystem );
            }
            AND_WHEN( "Simulating satellite motion over a period of 10 yeras" ) {
                double TotalEnergyBeforeSimulation = system.totalEnergy();
                system.testSimulater( timeSpan, iterations, system.startIteration(), system.method() );
                system.calculateEnergies();
                double TotalEnergyAfterSimulation = system.totalEnergy();
                THEN( "Total energy is conserved (with an error less than 1e-4)") {
                    REQUIRE( TotalEnergyBeforeSimulation == Approx(TotalEnergyAfterSimulation).epsilon(1e-4)  );
                }
            }
        }
    }
}

