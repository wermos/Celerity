cmake_minimum_required(VERSION 3.10)

# set the project name
project(imageWriters VERSION 0.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES
	src/*.cxx)

# add the library files
add_library(imageWriters ${SOURCES})

target_include_directories(imageWriters PUBLIC include)
