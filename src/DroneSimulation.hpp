#pragma once

#include <chrono>

class DroneSimulation {
public:
    struct Geolocation {
        virtual ~Geolocation() {}

        double lat;
        double lon;
        double alt;
    };

    DroneSimulation(Geolocation starting_location, Geolocation destination_location, double speed_m_s);
    DroneSimulation(void);
    virtual ~DroneSimulation();

    bool start(void);
    bool isStarted(void);

private:
    Geolocation starting_location_;
    Geolocation destination_location_;
    double speed_m_s_;
    bool is_location_set_;
    bool is_simulation_started_;
    std::chrono::time_point<std::chrono::steady_clock> start_time_sec_;
};