include(FetchContent)

FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL
  GIT_TAG        release-2.30.5
  GIT_PROGRESS   FALSE
  GIT_SHALLOW    ON
)

FetchContent_Declare(
  SDL2_IMAGE
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
  GIT_TAG        release-2.8.2
  GIT_PROGRESS   FALSE
  GIT_SHALLOW    ON
)

FetchContent_Declare(
  SDL2_TTF
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
  GIT_TAG        release-2.20.0
  GIT_PROGRESS   FALSE
  GIT_SHALLOW    ON
)

FetchContent_Declare(
  SDL2_MIXER
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
  GIT_TAG        release-2.8.0
  GIT_PROGRESS   FALSE
  GIT_SHALLOW    ON
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "disable shared libs for SDL2")
set(SDL2MIXER_OPUS OFF CACHE BOOL "disable support for opus music")
set(SDL2MIXER_MOD  OFF CACHE BOOL "disable support for loading MOD music")

FetchContent_MakeAvailable(SDL2 SDL2_IMAGE SDL2_TTF SDL2_MIXER)
