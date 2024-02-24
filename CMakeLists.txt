cmake_minimum_required(VERSION 3.14)
project (kektech)

# C++11 minimum is required for this engine.
set (CMAKE_CXX_STANDARD 14)

#set(CMAKE_C_FLAGS "-O1 -ggdb -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include")
#set(CMAKE_CXX_FLAGS "-O1 -ggdb -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include")

set(CMAKE_C_FLAGS "-O1 -ggdb")
set(CMAKE_CXX_FLAGS "-O1 -ggdb")

# Setup output directories.
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include the dependencies.
add_subdirectory (deps/libogg ${CMAKE_BINARY_DIR}/3rdParty/libogg)
add_subdirectory (deps/opus ${CMAKE_BINARY_DIR}/3rdParty/opus)
add_subdirectory (deps/libsndfile ${CMAKE_BINARY_DIR}/3rdParty/libsndfile)
add_subdirectory (deps/sdl2 ${CMAKE_BINARY_DIR}/3rdParty/sdl2)
add_subdirectory (deps/openal-soft ${CMAKE_BINARY_DIR}/3rdParty/openal-soft)

add_subdirectory (deps/sdl2-image ${CMAKE_BINARY_DIR}/3rdParty/sdl2-image)
#add_subdirectory (deps/sdl2-mixer-x ${CMAKE_BINARY_DIR}/3rdParty/sdl2-mixer-x)
add_subdirectory (deps/sdl2-ttf ${CMAKE_BINARY_DIR}/3rdParty/sdl2-ttf)
add_subdirectory (deps/devil/DevIL ${CMAKE_BINARY_DIR}/3rdParty/devil)
add_subdirectory (deps/glm ${CMAKE_BINARY_DIR}/3rdParty/glm)
include_directories (/usr/include/freetype2)

#add_subdirectory (deps/freetype ${CMAKE_BINARY_DIR}/3rdParty/freetype)

find_package(GLEW 2.2 REQUIRED)
find_package(PkgConfig REQUIRED) # Include functions provided by PkgConfig module.
find_package(OpenGL REQUIRED)
find_package(DevIL REQUIRED)
find_package(Freetype REQUIRED)

pkg_check_modules(DBUS REQUIRED dbus-1) # This calls pkgconfig with appropriate arguments
include_directories(${DBUS_INCLUDE_DIRS})
link_directories(${DBUS_LIBRARY_DIRS})

# Something something fix.
set(SDL2_IMAGE_INSTALL OFF)
set(SDL2_DISABLE_INSTALL OFF)

# Create executable and source files
add_executable(kektech main.cpp main.h config.h input.h input.cpp libs.h map.h map.cpp render.h render.cpp audio.h audio.cpp ui.h ui.cpp save.h save.cpp vector.h deps/stb_image.h deps/stb_image.cpp)
#add_library(kektech main.cpp main.h config.h input.h input.cpp libs.h map.h map.cpp render.h render.cpp audio.h audio.cpp ui.h ui.cpp save.h save.cpp vector.h)
add_library (client.o client/engine.h client/client_render.h client/client_render.cpp client/client_main.h client/client_main.cpp client/dialog.h client/dialog.cpp client/snake.h client/snake.cpp)

# Let's link finally.
target_link_libraries(kektech client.o OpenAL::OpenAL SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static SDL2_ttf::SDL2_ttf-static ogg sndfile opus GLEW::GLEW OpenGL::GL DevIL::IL DevIL::ILU glm::glm ${FREETYPE_LIBRARIES} ${DBUS_INCLUDE_DIRS})
target_link_libraries(client.o OpenAL::OpenAL SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static SDL2_ttf::SDL2_ttf-static ogg sndfile opus GLEW::GLEW OpenGL::GL DevIL::IL DevIL::ILU glm::glm ${FREETYPE_LIBRARIES} ${DBUS_INCLUDE_DIRS})
