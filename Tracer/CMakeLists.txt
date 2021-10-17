cmake_minimum_required(VERSION 3.10)

# set the project name
project(RayTracer VERSION 0.2)

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
	./*/include
	)


# add the executable
add_executable(RayTracer ${SOURCES})

#target_include_directories(RayTracer PUBLIC ../../utilities/stb)
target_include_directories(RayTracer PUBLIC ${INCLUDE_DIRS})

target_link_libraries(RayTracer PUBLIC utilities)
