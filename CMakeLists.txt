# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's Snaze

project(snaze)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(snaze ${PROJECT_SOURCE_DIR}/src/snaze.cpp)


# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")