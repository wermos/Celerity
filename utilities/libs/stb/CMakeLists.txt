cmake_minimum_required(VERSION 3.10)

# set the project name
project(stb_image VERSION 1.16)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(stb_image INTERFACE stb_image_library.hpp)

target_include_directories(stb_image INTERFACE .)
