cmake_minimum_required(VERSION 3.10)

# set the project name
project(utilities VERSION 0.5)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES
	CONFIGURE_DEPENDS
	src/*.cxx)

file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES TRUE
	CONFIGURE_DEPENDS
	./*/include
	)

add_library(utilities ${SOURCES})

target_include_directories(utilities PUBLIC ${INCLUDE_DIRS} PUBLIC include)
#target_include_directories(utilities PUBLIC math/include)

#include the header-only stb library in the search path
target_include_directories(utilities PUBLIC stb)
