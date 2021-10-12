cmake_minimum_required(VERSION 3.10)

# set the project name
project(RayTracer VERSION 0.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the utilities library
add_subdirectory(utilities)

# add the executable
add_executable(RayTracer main.cxx)

target_link_libraries(RayTracer PUBLIC utilities)

# add the binary tree to the search path for include files
# so that we will be able to find all the .hpp files
target_include_directories(RayTracer PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/MathFunctions"
                          )
