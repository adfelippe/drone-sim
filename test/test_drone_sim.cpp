#include <gtest/gtest.h>
#include <thread>
#include <chrono>
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

    EXPECT_TRUE(simulation.start());
    EXPECT_TRUE(simulation.isStarted());
}

TEST(TestDroneSim, GivenAKnownStartingAndDestinationLocation_WhenGettingDistanceInMeters_ThenValueIsAsExpected) {
    DroneSimulation::Geolocation starting_location;
    starting_location.lat = 24.4427496;
    starting_location.lon = 54.5754511;
    starting_location.alt = 200.0;
    DroneSimulation::Geolocation destination_location;
    destination_location.lat = 25.2556164;
    destination_location.lon = 55.3650570;
    destination_location.alt = 200.0;
    double speed_m_s = 20;
    double expected_distance_m = 120318.817;

    DroneSimulation simulation(starting_location, destination_location, speed_m_s);
    simulation.start();
    EXPECT_NEAR(expected_distance_m, simulation.getTotalDistanceMeters(), 0.1);

    // New locations
    starting_location.lat = 40.6;
    starting_location.lon = -73.8;
    starting_location.alt = 200.0;

    destination_location.lat = 51.6;
    destination_location.lon = 0.5;
    destination_location.alt = 200.0;

    expected_distance_m = 5617606.442;

    simulation.stop();
    simulation.setDroneSimulationData(starting_location, destination_location, speed_m_s);
    simulation.start();
    EXPECT_NEAR(expected_distance_m, simulation.getTotalDistanceMeters(), 0.1);

    // New locations
    starting_location.lat = 25.656745;
    starting_location.lon = -93.8658742;
    starting_location.alt = 200.0;

    destination_location.lat = -1.6231587;
    destination_location.lon = -25.6685478;
    destination_location.alt = 200.0;

    expected_distance_m = 7919320.732;

    simulation.stop();
    simulation.setDroneSimulationData(starting_location, destination_location, speed_m_s);
    simulation.start();
    EXPECT_NEAR(expected_distance_m, simulation.getTotalDistanceMeters(), 0.1);
}

TEST(TestDroneSim, TestDroneSimulationMovement) {
    DroneSimulation::Geolocation starting_location;
    starting_location.lat = 24.4427496;
    starting_location.lon = 54.5754511;
    starting_location.alt = 200.0;

    DroneSimulation::Geolocation destination_location;
    destination_location.lat = 25.2556164;
    destination_location.lon = 55.3650570;
    destination_location.alt = 200.0;

    double speed_m_s = 12031.8;

    DroneSimulation simulation(starting_location, destination_location, speed_m_s);
    simulation.start();

    uint32_t i;
    DroneSimulation::Geolocation current_location;
    for (i = 0; i < 15; ++i) {
        simulation.getCurrentDroneLocation(current_location);
        std::cout << "Current simulated drone position: " << current_location.lat << ", " << current_location.lon
                  << std::setprecision(13) <<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
