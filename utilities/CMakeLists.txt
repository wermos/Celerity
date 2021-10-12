cmake_minimum_required(VERSION 3.10)

# set the project name
project(Utilities VERSION 0.5)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(vec3 vec3.cxx)
add_library(ray ray.hpp)
add_library(color color.cxx)
