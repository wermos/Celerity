cmake_minimum_required(VERSION 3.10)

# set the project name
project(RayTracer VERSION 0.4.3)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add a Profile build type to generate runtime information
# Update the documentation string of CMAKE_BUILD_TYPE for GUIs
set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
	"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Profile."
  	FORCE)

# Do a #define PROFILE so that the conditionally included code is actually included.
if (CMAKE_BUILD_TYPE STREQUAL "Profile")
	set(CMAKE_BUILD_TYPE Release)
	add_compile_definitions(PROFILE)
endif()

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
target_include_directories(RayTracer PUBLIC include)
foreach(DIR ${INCLUDE_DIRS})
	#message(STATUS "${DIR} was just added to target_include_directories.")
	target_include_directories(RayTracer PUBLIC ${DIR})
endforeach()

target_include_directories(RayTracer PUBLIC ../shared)

target_link_libraries(RayTracer PUBLIC utilities)
