cmake_minimum_required(VERSION 3.10)

# set the project name
project(RayTracer VERSION 0.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the utilities library
add_subdirectory(../utilities utilities)

# add the executable
add_executable(RayTracer main.cxx)

target_link_libraries(RayTracer PUBLIC utilities)
