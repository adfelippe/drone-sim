#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <sstream>
#include "DroneSimulation.hpp"

void printInfoMessage(const std::string& message);

TEST(TestDroneSim, GivenSimulationIsCreatedWithValidParameters_WhenStartingSimulation_ThenItReturnsTrue) {
    DroneSimulation::Geolocation origin_location;
    origin_location.lat = 24.555;
    origin_location.lon = 54.555;
    origin_location.alt = 200.0;

    DroneSimulation::Geolocation destination_location;
    destination_location.lat = 34.555;
    destination_location.lon = 64.555;
    destination_location.alt = 200.0;

    double speed_m_s = 20;

    DroneSimulation simulation(origin_location, destination_location, speed_m_s);

    EXPECT_TRUE(simulation.start());
}

TEST(TestDroneSim, GivenSimulationIsCreatedWithoutParameters_WhenStartingSimulation_ThenItReturnsFalse) {
    DroneSimulation simulation;
    EXPECT_FALSE(simulation.start());
}

TEST(TestDroneSim, GivenSimulationHasStarted_WhenCheckingIfStarted_ThenItReturnsSuccess) {
    DroneSimulation::Geolocation origin_location;
    origin_location.lat = 24.555;
    origin_location.lon = 54.555;
    origin_location.alt = 200.0;

    DroneSimulation::Geolocation destination_location;
    destination_location.lat = 34.555;
    destination_location.lon = 64.555;
    destination_location.alt = 200.0;

    double speed_m_s = 20;

    DroneSimulation simulation(origin_location, destination_location, speed_m_s);

    EXPECT_TRUE(simulation.start());
    EXPECT_TRUE(simulation.isStarted());
}

TEST(TestDroneSim, GivenAKnownStartingAndDestinationLocation_WhenGettingDistanceInMeters_ThenValueIsAsExpected) {
    DroneSimulation::Geolocation origin_location;
    origin_location.lat = 24.4427496;
    origin_location.lon = 54.5754511;
    origin_location.alt = 200.0;
    DroneSimulation::Geolocation destination_location;
    destination_location.lat = 25.2556164;
    destination_location.lon = 55.3650570;
    destination_location.alt = 200.0;
    double speed_m_s = 20;
    double expected_distance_m = 120318.817;

    DroneSimulation simulation(origin_location, destination_location, speed_m_s);
    simulation.start();
    EXPECT_NEAR(expected_distance_m, simulation.getTotalDistanceMeters(), 0.1);

    // New locations
    origin_location.lat = 40.6;
    origin_location.lon = -73.8;
    origin_location.alt = 200.0;

    destination_location.lat = 51.6;
    destination_location.lon = 0.5;
    destination_location.alt = 200.0;

    expected_distance_m = 5617606.442;

    simulation.stop();
    simulation.setDroneSimulationData(origin_location, destination_location, speed_m_s);
    simulation.start();
    EXPECT_NEAR(expected_distance_m, simulation.getTotalDistanceMeters(), 0.1);

    // New locations
    origin_location.lat = 25.656745;
    origin_location.lon = -93.8658742;
    origin_location.alt = 200.0;

    destination_location.lat = -1.6231587;
    destination_location.lon = -25.6685478;
    destination_location.alt = 200.0;

    expected_distance_m = 7919320.732;

    simulation.stop();
    simulation.setDroneSimulationData(origin_location, destination_location, speed_m_s);
    simulation.start();
    EXPECT_NEAR(expected_distance_m, simulation.getTotalDistanceMeters(), 0.1);
}

TEST(TestDroneSim, TestDroneSimulationMovement) {
    DroneSimulation::Geolocation origin_location;
    origin_location.lat = 24.4427496;
    origin_location.lon = 54.5754511;
    origin_location.alt = 200.0;

    DroneSimulation::Geolocation destination_location;
    destination_location.lat = 25.2556164;
    destination_location.lon = 55.3650570;
    destination_location.alt = 200.0;

    double speed_m_s = 12031.8;

    printInfoMessage("Starting drone simulation:");
    DroneSimulation simulation(origin_location, destination_location, speed_m_s);
    simulation.start();
    uint32_t i;
    DroneSimulation::Geolocation current_location;

    for (i = 0; i < 10; ++i) {
        std::ostringstream o_lat, o_lon;
        o_lat.precision(10);
        o_lon.precision(10);
        simulation.getCurrentDroneLocation(current_location);
        o_lat << current_location.lat;
        o_lon << current_location.lon;
        printInfoMessage("Current simulated drone position -> Lat: " + o_lat.str() + ", Lon: " + o_lon.str());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    simulation.getCurrentDroneLocation(current_location);
    printInfoMessage("Checking if drone reached destination on time as expected:");
    EXPECT_NEAR(destination_location.lat, current_location.lat, 0.001)
        << "Failed to reach destination on time - Latidude";
    EXPECT_NEAR(destination_location.lon, current_location.lon, 0.001)
        << "Failed to reach destination on time - Longitude";
}

void printInfoMessage(const std::string& message) {
    std::cout << "[   INFO   ] " << message <<  std::endl;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
