cmake_minimum_required(VERSION 3.10)

project(math VERSION 0.5)

file(GLOB_RECURSE SOURCES
	src/*.cxx)

add_library(math ${SOURCES})

target_include_directories(math PUBLIC include)
