#include "DroneSimulation.hpp"

DroneSimulation::DroneSimulation(Geolocation starting_location, Geolocation destination_location, double speed_m_s) :
    starting_location_(starting_location),
    destination_location_(destination_location),
    speed_m_s_(speed_m_s),
    is_location_set_(true),
    is_simulation_started_(false) {}
    
DroneSimulation::DroneSimulation(void) : 
    is_location_set_(false), 
    is_simulation_started_(false) {}

DroneSimulation::~DroneSimulation() {}

bool DroneSimulation::start(void) {
    if (!is_location_set_) {
        return false;
    }

    start_time_sec_ = std::chrono::steady_clock::now();
    is_simulation_started_ = true;
    return true;
}

bool DroneSimulation::isStarted(void) {
    return is_simulation_started_;
}