#include "DroneSimulation.hpp"
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeodesicLine.hpp>
#include <GeographicLib/Constants.hpp>

DroneSimulation::DroneSimulation(const Geolocation &origin_location, const Geolocation &destination_location,
                                 const double &speed_m_s)
    : origin_location_(origin_location),
      destination_location_(destination_location),
      speed_m_s_(speed_m_s),
      is_location_set_(true),
      is_simulation_started_(false) {}

DroneSimulation::DroneSimulation(void) : is_location_set_(false), is_simulation_started_(false) {}

DroneSimulation::~DroneSimulation() {}

bool DroneSimulation::start(void) {
    if (!is_location_set_ || is_simulation_started_) {
        return false;
    }

    start_time_ = std::chrono::steady_clock::now();
    is_simulation_started_ = true;
    return true;
}

bool DroneSimulation::stop(void) {
    is_simulation_started_ = false;
    return true;
}

bool DroneSimulation::isStarted(void) { return is_simulation_started_; }

void DroneSimulation::setDroneSimulationData(const Geolocation &origin_location,
                                             const Geolocation &destination_location, const double &speed_m_s) {
    origin_location_ = origin_location;
    destination_location_ = destination_location;
    speed_m_s_ = speed_m_s;
    is_location_set_ = true;
}

void DroneSimulation::setSpeed(const double &speed_m_s) {
    speed_m_s_ = speed_m_s;
}

double DroneSimulation::getTotalDistanceMeters(void) const {
    if (!is_simulation_started_) {
        return 0.0F;
    }

    const GeographicLib::Geodesic& geodesic = GeographicLib::Geodesic::WGS84();
    double distance_m = 0.0F;

    geodesic.Inverse(origin_location_.lat, origin_location_.lon, destination_location_.lat,
                     destination_location_.lon, distance_m);

    return distance_m;
}

bool DroneSimulation::getCurrentDroneLocation(Geolocation &current_location) {
    const GeographicLib::Geodesic& geodesic = GeographicLib::Geodesic::WGS84();
    GeographicLib::GeodesicLine line = geodesic.InverseLine(origin_location_.lat, origin_location_.lon,
                                                            destination_location_.lat, destination_location_.lon);

    line.Position(getTraveledDistanceMeters(), current_location.lat, current_location.lon);
    return true;
}

double DroneSimulation::getTraveledDistanceMeters(void) {
    if (!is_simulation_started_) {
        return 0.0F;
    }

    return (getElapsedTimeSeconds() * speed_m_s_);
}

int64_t DroneSimulation::getElapsedTimeSeconds(void) {
    auto elapsed_time =
        std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time_);
    return (elapsed_time.count());
}
