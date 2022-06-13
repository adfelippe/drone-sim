#include <gtest/gtest.h>
#include "DroneSimulation.hpp"

TEST(TestDroneSim, GivenSimulationIsCreatedWithValidParameters_WhenStartingSimulation_ThenItReturnsTrue) {
    DroneSimulation::Geolocation starting_location;
    starting_location.lat = 24.555;
    starting_location.lon = 54.555;
    starting_location.alt = 200.0;

    DroneSimulation::Geolocation destination_location;
    destination_location.lat = 34.555;
    destination_location.lon = 64.555;
    destination_location.alt = 200.0;

    double speed_m_s = 20;

    DroneSimulation simulation(starting_location, destination_location, speed_m_s);
    

    EXPECT_TRUE(simulation.start());
}

TEST(TestDroneSim, GivenSimulationIsCreatedWithoutParameters_WhenStartingSimulation_ThenItReturnsFalse) {
    DroneSimulation simulation;
    EXPECT_FALSE(simulation.start());
}

TEST(TestDroneSim, GivenSimulationHasStarted_WhenCheckingIfStarted_ThenItReturnsSuccess) {
    DroneSimulation::Geolocation starting_location;
    starting_location.lat = 24.555;
    starting_location.lon = 54.555;
    starting_location.alt = 200.0;

    DroneSimulation::Geolocation destination_location;
    destination_location.lat = 34.555;
    destination_location.lon = 64.555;
    destination_location.alt = 200.0;

    double speed_m_s = 20;

    DroneSimulation simulation(starting_location, destination_location, speed_m_s);
    simulation.start();

    EXPECT_TRUE(simulation.isStarted());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}