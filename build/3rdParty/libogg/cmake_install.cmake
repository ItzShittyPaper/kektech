# Install script for directory: /home/m4kulatura/Documents/GitHub/kektech/deps/libogg

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/home/m4kulatura/Documents/GitHub/kektech/build/lib/libogg.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ogg" TYPE FILE FILES
    "/home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/libogg/include/ogg/config_types.h"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/include/ogg/ogg.h"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/include/ogg/os_types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/Ogg/OggTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/Ogg/OggTargets.cmake"
         "/home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/libogg/CMakeFiles/Export/78112e1570107022430ea2fa1f506cba/OggTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/Ogg/OggTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/Ogg/OggTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/Ogg" TYPE FILE FILES "/home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/libogg/CMakeFiles/Export/78112e1570107022430ea2fa1f506cba/OggTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/Ogg" TYPE FILE FILES "/home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/libogg/CMakeFiles/Export/78112e1570107022430ea2fa1f506cba/OggTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/Ogg" TYPE FILE FILES
    "/home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/libogg/OggConfig.cmake"
    "/home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/libogg/OggConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/pkgconfig" TYPE FILE FILES "/home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/libogg/ogg.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/libogg/html" TYPE FILE FILES
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/framing.html"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/index.html"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/oggstream.html"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/ogg-multiplex.html"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/fish_xiph_org.png"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/multiplex1.png"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/packets.png"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/pages.png"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/stream.png"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/vorbisword2.png"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/white-ogg.png"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/white-xifish.png"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/rfc3533.txt"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/rfc5334.txt"
    "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/skeleton.html"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/libogg/html" TYPE DIRECTORY FILES "/home/m4kulatura/Documents/GitHub/kektech/deps/libogg/doc/libogg")
endif()

