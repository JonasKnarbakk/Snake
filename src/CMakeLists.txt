# List of all the source files in the project
FILE(GLOB SRC
    "Main.cpp"
    "GameManager.cpp"
    "InputManager.cpp"
    "Timer.cpp"
    "SDL/SDLBmp.cpp"
    "SDL/SDLError.cpp"
    "SDL/SDLManager.cpp"
    "Handlers/MusicHandler.cpp"
    )

# Create the executable form listed cpp files
ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})

# Make it so the binary is put in the bin folder of the root directory
SET_TARGET_PROPERTIES( ${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${${PROJECT_NAME}_SOURCE_DIR}/bin)

# SDL2
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${${PROJECT_NAME}_SOURCE_DIR}/Modules")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}
                            ${SDL2_IMAGE_LIBRARIES}
                            ${SDL2_TTF_LIBRARIES}
                            ${SDL2_MIXER_LIBRARIES})
