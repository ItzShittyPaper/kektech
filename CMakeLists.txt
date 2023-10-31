cmake_minimum_required(VERSION 3.14)
project (kektech)

# C++11 minimum is required for this engine.
set (CMAKE_CXX_STANDARD 14)

# Setup output directories.
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(${CMAKE_CURRENT_LIST_DIR})

# Include the dependencies.
add_subdirectory (deps/libmodplug ${CMAKE_BINARY_DIR}/3rdParty/libmodplug)
add_subdirectory (deps/libogg ${CMAKE_BINARY_DIR}/3rdParty/libogg)
add_subdirectory (deps/opus ${CMAKE_BINARY_DIR}/3rdParty/opus)
add_subdirectory (deps/sdl2 ${CMAKE_BINARY_DIR}/3rdParty/sdl2)

set(SDL2MIXERXSDL2DIR ${CMAKE_CURRENT_LIST_DIR}/deps/sdl2)
set(ModPlug_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/deps/libmodplug/src)
set(ModPlug_LIBRARY ${CMAKE_CURRENT_LIST_DIR}/deps/libmodplug)

add_subdirectory (deps/sdl2-image ${CMAKE_BINARY_DIR}/3rdParty/sdl2-image)
add_subdirectory (deps/sdl2-mixer-x ${CMAKE_BINARY_DIR}/3rdParty/sdl2-mixer-x)
add_subdirectory (deps/sdl2-ttf ${CMAKE_BINARY_DIR}/3rdParty/sdl2-ttf)

# Something something fix.
set(SDL2_IMAGE_INSTALL OFF)
set(SDL2_DISABLE_INSTALL OFF)
set(SDL_MIXER_X_STATIC  ON)
set(SDL_MIXER_X_SHARED  OFF)

# Create executable and source files
add_executable(kektech main.cpp main.h config.h input.h input.cpp libs.h map.h map.cpp render.h render.cpp audio.h audio.cpp ui.h ui.cpp save.h save.cpp vector.h)
#add_library(kektech main.cpp main.h config.h input.h input.cpp libs.h map.h map.cpp render.h render.cpp audio.h audio.cpp ui.h ui.cpp save.h save.cpp vector.h)
add_library (client.o client/engine.h client/client_render.h client/client_render.cpp client/client_main.h client/client_main.cpp client/dialog.h client/dialog.cpp client/snake.h client/snake.cpp)

# Let's link finally.
target_link_libraries(kektech client.o SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static SDL2_ttf::SDL2_ttf-static SDL2_mixer_ext_Static ogg modplug opus)
target_link_libraries(client.o SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static SDL2_ttf::SDL2_ttf-static SDL2_mixer_ext_Static ogg modplug opus)


