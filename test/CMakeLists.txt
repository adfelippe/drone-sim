cmake_minimum_required(VERSION 3.10)
project(test_done_sim)

set(CMAKE_CXX_STANDARD 17)

# Include
include_directories(../src)

# Find libs
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_library(LIBS_PTHREAD NAMES pthread)
find_library(LIBS_GEOGRAPHIC NAMES Geographic)

add_executable(run_tests
               ../src/DroneSimulation.cpp
               test_drone_sim.cpp)

target_link_libraries(run_tests 
                      ${GTEST_LIBRARIES}
                      ${LIBS_PTHREAD}
                      ${LIBS_GEOGRAPHIC})

