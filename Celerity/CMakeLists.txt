cmake_minimum_required(VERSION 3.10)

# set the project name
project(Celerity VERSION 0.5)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_THREAD_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED) # TODO: Make this optional

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
add_executable(Celerity ${SOURCES})

target_include_directories(Celerity PUBLIC include)
foreach(DIR ${INCLUDE_DIRS})
	target_include_directories(Celerity PUBLIC ${DIR})
endforeach()

# -Werror
target_compile_options(Celerity PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /wd4100 /wd4189>
	$<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
	$<$<CXX_COMPILER_ID:Clang>:-Weverything> 
)

target_include_directories(Celerity PUBLIC ../shared)

target_link_libraries(Celerity PUBLIC utilities)
target_link_libraries(Celerity PUBLIC ${CMAKE_THREAD_LIBS_INIT})
