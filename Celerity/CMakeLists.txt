cmake_minimum_required(VERSION 3.10)

# set the project name
project(Celerity VERSION 0.7)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

# xsimd build flags
# TODO: Remove this stopgap and use proper CMake to compile xsimd.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_COMPILER_IS_GNUCXX)
    # this flag only works on Clang and GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

# add the utilities library
add_subdirectory(../utilities utilities)

file(GLOB_RECURSE SOURCES
	CONFIGURE_DEPENDS
	src/*.cxx
)

# add the executable
add_executable(Celerity ${SOURCES})

target_include_directories(Celerity PUBLIC include)

target_include_directories(Celerity PUBLIC ../shared)

target_link_libraries(Celerity PUBLIC utilities)
target_link_libraries(Celerity PUBLIC ${CMAKE_THREAD_LIBS_INIT})
