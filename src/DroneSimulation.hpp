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

    DroneSimulation(const Geolocation &origin_location, const Geolocation &destination_location,
                    const double &speed_m_s);
    DroneSimulation(void);
    virtual ~DroneSimulation();

    bool start(void);
    bool stop(void);
    bool isStarted(void);
    void setDroneSimulationData(const Geolocation &origin_location, const Geolocation &destination_location,
                                const double &speed_m_s);
    void setSpeed(const double &speed_m_s);
    double getTotalDistanceMeters(void) const;
    bool getCurrentDroneLocation(Geolocation &current_location);
    double getTraveledDistanceMeters(void);

private:
    int64_t getElapsedTimeSeconds(void);

    Geolocation origin_location_;
    Geolocation destination_location_;
    double speed_m_s_;
    bool is_location_set_;
    bool is_simulation_started_;
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
};
