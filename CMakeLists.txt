# Minimum version of cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Set the project name
PROJECT(Snake)

# Set the compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
 
# Add the src directory to the project
ADD_SUBDIRECTORY(src)

# Add custom make commands for running the binary
ADD_CUSTOM_TARGET(run)
ADD_CUSTOM_COMMAND(TARGET run COMMAND ./bin/Snake)
