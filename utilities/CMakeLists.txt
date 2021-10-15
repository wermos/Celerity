cmake_minimum_required(VERSION 3.10)

# set the project name
project(utilities VERSION 0.5)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(math)

file(GLOB_RECURSE SOURCES
	src/*.cxx)

add_library(utilities ${SOURCES})

target_link_libraries(utilities PUBLIC math)

target_include_directories(utilities PUBLIC include)
target_include_directories(utilities PUBLIC math/include)

#include the header only stb library in the search path
target_include_directories(utilities PUBLIC stb)
