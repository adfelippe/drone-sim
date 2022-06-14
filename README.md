# drone-sim
## Drone Position Simulator

This is a simple Drone Position Simulator which relies on the C++ [GeographicLib](https://geographiclib.sourceforge.io/C++/doc/index.html) to calculate positions based on an origin location, destination location, speed and time.

The position is estimated using the geodesic points algorithms from the [GeographicLib](https://geographiclib.sourceforge.io/C++/doc/index.html) simply by calculating the distance from origin to destination for a given point in time after the simulation started. 

### Dependencies:

- GTest (For tests)
- CMake (For tests)
- GeographicLib

### Installation on Ubuntu:
```bash
sudo apt install cmake libgtest-dev libgeographic-dev
```

### Compile and run unit tests:
```bash
$ cd test
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
```

### How to use:
Just copy .hpp and .cpp files to your project and compile as needed.

### Example:
```cpp
DroneSimulation::Geolocation starting_location;
starting_location.lat = 24.4427496;
starting_location.lon = 54.5754511;
starting_location.alt = 200.0;

DroneSimulation::Geolocation destination_location;
destination_location.lat = 25.2556164;
destination_location.lon = 55.3650570;
destination_location.alt = 200.0;

double speed_m_s = 20;

DroneSimulation simulation(starting_location, destination_location, speed_m_s);
simulation.start();

DroneSimulation::Geolocation current_location;
simulation.getCurrentDroneLocation(current_location);

std::cout << "Current simulated drone location: " << current_location.lat << ", " << current_location.lon << std::endl;
```
