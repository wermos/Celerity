cmake_minimum_required(VERSION 3.10)

# set the project name
project(RayTracer VERSION 0.4)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the utilities library
add_subdirectory(../utilities utilities)

file(GLOB_RECURSE SOURCES
	CONFIGURE_DEPENDS
	src/*.cxx
	)

	file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES TRUE
	CONFIGURE_DEPENDS
	include/*[^hpp] # The idea is to include all the `files' inside include/ as
					# well as the directories, but to exclude all the .hpp
					# files. (The assumption is that the directories only cont-
					# ain .hpp files.)
	)

# add the executable
add_executable(RayTracer ${SOURCES})

#message(STATUS "The value of INCLUDE_DIRS is ${INCLUDE_DIRS}")
target_include_directories(RayTracer PUBLIC ${INCLUDE_DIRS} PUBLIC include)

target_link_libraries(RayTracer PUBLIC utilities)
