#include "catch.hpp"
#include "../src/solarsystem.h"
#include "../src/vec3.h"
#include <time.h>

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

                REQUIRE( satellite1.accelerationOld().x() == satellite1.acceleration().x() );
                REQUIRE( satellite1.accelerationOld().y() == satellite1.acceleration().y() );
                REQUIRE( satellite1.accelerationOld().z() == satellite1.acceleration().z() );

                REQUIRE( satellite2.accelerationOld().x() == satellite2.acceleration().x() );
                REQUIRE( satellite2.accelerationOld().y() == satellite2.acceleration().y() );
                REQUIRE( satellite2.accelerationOld().z() == satellite2.acceleration().z() );

                REQUIRE( satellite3.accelerationOld().x() == satellite3.acceleration().x() );
                REQUIRE( satellite3.accelerationOld().y() == satellite3.acceleration().y() );
                REQUIRE( satellite3.accelerationOld().z() == satellite3.acceleration().z() );
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

                REQUIRE( satellite1.accelerationOld().x() == satellite1.acceleration().x() );
                REQUIRE( satellite1.accelerationOld().y() == satellite1.acceleration().y() );
                REQUIRE( satellite1.accelerationOld().z() == satellite1.acceleration().z() );

                REQUIRE( satellite2.accelerationOld().x() == satellite2.acceleration().x() );
                REQUIRE( satellite2.accelerationOld().y() == satellite2.acceleration().y() );
                REQUIRE( satellite2.accelerationOld().z() == satellite2.acceleration().z() );

                REQUIRE( satellite3.accelerationOld().x() == satellite3.acceleration().x() );
                REQUIRE( satellite3.accelerationOld().y() == satellite3.acceleration().y() );
                REQUIRE( satellite3.accelerationOld().z() == satellite3.acceleration().z() );
            }
        }

        AND_WHEN( "updating position using Euler" ) {
            THEN ("position changes") {
                system.updatePositionsEuler();
                vector<Satellite> satellites = system.satellites();
                Satellite satellite1 = satellites[0];
                Satellite satellite2 = satellites[1];
                Satellite satellite3 = satellites[2];

                REQUIRE( satellite1.position().x() == 0 );
                REQUIRE( satellite1.position().y() == 0 );
                REQUIRE( satellite1.position().z() == 0 );

                REQUIRE( satellite2.position().x() != 1 );
                REQUIRE( satellite2.position().y() != 1 );
                REQUIRE( satellite2.position().z() != 1 );

                REQUIRE( satellite3.position().x() != 2 );
                REQUIRE( satellite3.position().y() != 2 );
                REQUIRE( satellite3.position().z() != 2 );
            }
        }

        AND_WHEN( "updating velocity using Euler" ) {
            THEN ("velocity changes") {
                system.updateVelocitiesEuler();
                vector<Satellite> satellites = system.satellites();
                Satellite satellite1 = satellites[0];
                Satellite satellite2 = satellites[1];
                Satellite satellite3 = satellites[2];

                REQUIRE( satellite1.velocity().x() == 0 );
                REQUIRE( satellite1.velocity().y() == 0 );
                REQUIRE( satellite1.velocity().z() == 0 );

                REQUIRE( satellite2.velocity().x() == 1 );
                REQUIRE( satellite2.velocity().y() == 1 );
                REQUIRE( satellite2.velocity().z() == 1 );

                REQUIRE( satellite3.velocity().x() == 2 );
                REQUIRE( satellite3.velocity().y() == 2 );
                REQUIRE( satellite3.velocity().z() == 2 );
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

                REQUIRE( satellite1.position().x() == 0 );
                REQUIRE( satellite1.position().y() == 0 );
                REQUIRE( satellite1.position().z() == 0 );

                REQUIRE( satellite2.position().x() != 1 );
                REQUIRE( satellite2.position().y() != 1 );
                REQUIRE( satellite2.position().z() != 1 );

                REQUIRE( satellite3.position().x() != 2 );
                REQUIRE( satellite3.position().y() != 2 );
                REQUIRE( satellite3.position().z() != 2 );
            }
        }

        AND_WHEN( "updating velocity using Verlet" ) {
            THEN ("velocity changes") {
                system.updateVelocitiesVerlet();
                vector<Satellite> satellites = system.satellites();
                Satellite satellite1 = satellites[0];
                Satellite satellite2 = satellites[1];
                Satellite satellite3 = satellites[2];

                REQUIRE( satellite1.velocity().x() == 0 );
                REQUIRE( satellite1.velocity().y() == 0 );
                REQUIRE( satellite1.velocity().z() == 0 );

                REQUIRE( satellite2.velocity().x() != 1 );
                REQUIRE( satellite2.velocity().y() != 1 );
                REQUIRE( satellite2.velocity().z() != 1 );

                REQUIRE( satellite3.velocity().x() != 2 );
                REQUIRE( satellite3.velocity().y() != 2 );
                REQUIRE( satellite3.velocity().z() != 2 );
            }
        }
    }
}

SCENARIO( "Check that potential and kinetic energy is conserved", "[energies]" ) {
    GIVEN( "System with two satellites" ) {
        SolarSystem system;

        system.createSatellite(1, vec3(0,0,0), vec3(0,0,0));
        system.createSatellite(3e-6, vec3(1,0,0), vec3(0,2*M_PI,0) );

        system.setMethod("verlet");
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
            AND_WHEN( "Simulating satellite motion over a period of 10 yeras, using Verlets method" ) {
                double TotalEnergyBeforeSimulation = system.totalEnergy();

                std::clock_t start;
                double calculationTime;
                start = std::clock();

                system.testSimulater( timeSpan, iterations, system.startIteration(), system.method() );

                calculationTime = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

                system.calculateEnergies();

                double TotalEnergyAfterSimulation = system.totalEnergy();
                THEN( "Total energy is conserved (with an error less than 1e-4)") {
                    REQUIRE( TotalEnergyBeforeSimulation == Approx(TotalEnergyAfterSimulation).epsilon(1e-4)  );
                    std::cout << "Simulation time: " << calculationTime << " s." << endl;
                    std::cout << "For system consisting of " << system.numberofsatellites() << " sattelites over " << timeSpan << " years, with a timestep of " << timeStep << " s. "<< endl;
                }
            }
        }
    }
}

SCENARIO( "Checking that angular momementum is conserved", "[angularMomentum]" ) {
    GIVEN( "Three satellite system" ) {
        SolarSystem system;

        system.createSatellite(1, vec3(-2,0,0), vec3(2,1,0));
        system.createSatellite(3e-6, vec3(1,0,0), vec3(0,2*M_PI,0) );
        system.createSatellite(954e-6, vec3(-5.2, 0, 0), vec3(0, -2.75 ,0));

        system.setMethod("verlet");
        system.setStartIteration( 1 );
        double timeSpan = 10; // Years
        int iterations = 100000;
        double timeStep = timeSpan/iterations;
        system.setTimeStep( timeStep );
        system.setHalfTimeStep( timeStep * 0.5);
        system.setHalfTimeStepSquared( timeStep * timeStep * 0.5 );

        WHEN( "Simulating over given time" ) {
            vec3 angularMomentumBeforeSimulation = system.angularMomentum();
            vec3 centerOfMassBeforeSimulation = system.centerOfMass();

            system.testSimulater( timeSpan, iterations, system.startIteration(), system.method() );

            vec3 angularMomentumAfterSimulation = system.angularMomentum();
            vec3 centerOfMassAfterSimulation = system.centerOfMass();
            THEN( "Angular momentum should be conserved (with epislon 1e-10)" ) {
                REQUIRE ( system.numberofsatellites() == 3  );
                REQUIRE( angularMomentumAfterSimulation.x() == Approx( angularMomentumBeforeSimulation.x() ).epsilon( 1e-10 ) ) ;
                REQUIRE( angularMomentumAfterSimulation.y() == Approx( angularMomentumBeforeSimulation.y() ).epsilon( 1e-10 ) ) ;
                REQUIRE( angularMomentumAfterSimulation.z() == Approx( angularMomentumBeforeSimulation.z() ).epsilon( 1e-10 ) ) ;
                cout << "Center of mass \n\t before:\t" << centerOfMassBeforeSimulation << "\n\t and after:\t" << centerOfMassAfterSimulation << endl;
                cout << "Angular momentum \n\t before:\t " << angularMomentumBeforeSimulation << "\n\t and after:\t " << angularMomentumAfterSimulation << endl;
            }
        }
    }
}

SCENARIO( "Comparing computation time for Euler and Verlet", "[timer]") {
    GIVEN( "Three satellite system" ) {
        SolarSystem system;

        system.createSatellite(1, vec3(-2,0,0), vec3(2,1,0));
        system.createSatellite(3e-6, vec3(1,0,0), vec3(0,2*M_PI,0) );
        system.createSatellite(954e-6, vec3(-5.2, 0, 0), vec3(0, -2.75 ,0));

        system.setStartIteration( 1 );
        double timeSpan = 10; // Years
        int iterations = 100000;
        double timeStep = timeSpan/iterations;
        system.setTimeStep( timeStep );
        system.setHalfTimeStep( timeStep * 0.5);
        system.setHalfTimeStepSquared( timeStep * timeStep * 0.5 );


        WHEN( "Simulating with Euler" ) {
            system.setMethod("euler");
            std::clock_t start;
            double calculationTime1 = 0;
            start = std::clock();
            for ( int i = 0; i < 10; i++) {
                system.testSimulater( timeSpan, iterations, system.startIteration(), system.method() );
                calculationTime1 =+ ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
            }
            calculationTime1 = calculationTime1 / 10;


            AND_WHEN( "Simulating with Verlet" ) {
                system.setMethod("verlet");

                THEN( "simulation times equal" ) {
                    double calculationTime2 = 0;
                    start = std::clock();
                    for ( int i = 0; i < 10; i++) {
                        system.testSimulater( timeSpan, iterations, system.startIteration(), system.method() );
                        calculationTime2 += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
                    }
                    calculationTime2 = calculationTime2 / 10;

                    REQUIRE( calculationTime1 != calculationTime2 );
                    std::cout << "Simulates 10 times over 10 years with timestep 1e-4 seconds " << endl;
                    std::cout << "Average simulation times using:" << endl;
                    std::cout << "\t Euler: \t" << calculationTime1 << " s." << endl;
                    std::cout << "\t Verlet: \t" << calculationTime2 << " s." << endl;
                    std::cout << "\t differance: \t" << abs( calculationTime2 - calculationTime1 ) << " s." << endl;
                    std::cout << " Verlet is on average "  << calculationTime1/calculationTime2 * 100 << " % faster than Euler with the given parameters." << endl;
                }
            }
        }
    }
}

