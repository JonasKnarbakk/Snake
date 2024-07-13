# Minimum version of cmake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Snake)

# Set the compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Create the executable
add_executable(
  ${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp
)

# Add the lib & src directory to the project
add_subdirectory(lib)
add_subdirectory(src)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${SDL2_SOURCE_DIR}/include
  ${SDL2_image_SOURCE_DIR}/include
  ${SDL2_ttf_SOURCE_DIR}/
  ${SDL2_mixer_SOURCE_DIR}/include
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  SDL2::SDL2-static
  SDL2_image
  SDL2_ttf
  SDL2_mixer
)

# Add custom make commands for running the binary
add_custom_target(run)
add_custom_command(
  TARGET run
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMAND ${Snake_BINARY_DIR}/Snake
)

# Uncomment this to print all cmake variables after configure step
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
  message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
