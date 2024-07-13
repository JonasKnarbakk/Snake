# List of all the source files in the project
target_sources(
  ${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/GameManager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/InputManager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Timer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SDL/SDLBmp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SDL/SDLError.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SDL/SDLManager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Handlers/MusicHandler.cpp
)

# # Make it so the binary is put in the bin folder of the root directory
# set_target_properties(
#   ${PROJECT_NAME}
#   PROPERTIES
#   RUNTIME_OUTPUT_DIRECTORY
#   ${${PROJECT_NAME}_SOURCE_DIR}/bin
# )

# # SDL2
# set(
#   CMAKE_MODULE_PATH
#   ${CMAKE_MODULE_PATH}
#   ${${PROJECT_NAME}_SOURCE_DIR}/Modules
# )

# find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_ttf REQUIRED)
# find_package(SDL2_mixer REQUIRED)

# target_include_directories(
#   ${PROJECT_NAME}
#   PRIVATE
#   ${SDL2_INCLUDE_DIR}
#   ${SDL2_IMAGE_INCLUDE_DIR}
#   ${SDL2_TTF_INCLUDE_DIR}
#   ${SDL2_MIXER_INCLUDE_DIR}
# )

# target_link_libraries(
#   ${PROJECT_NAME}
#   PRIVATE
#   ${SDL2_LIBRARY}
#   ${SDL2_IMAGE_LIBRARIES}
#   ${SDL2_TTF_LIBRARIES}
#   ${SDL2_MIXER_LIBRARIES}
# )
