# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/m4kulatura/Documents/GitHub/kektech-c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/m4kulatura/Documents/GitHub/kektech-c/build

# Utility rule file for ContinuousConfigure.

# Include any custom commands dependencies for this target.
include 3rdParty/libogg/CMakeFiles/ContinuousConfigure.dir/compiler_depend.make

# Include the progress variables for this target.
include 3rdParty/libogg/CMakeFiles/ContinuousConfigure.dir/progress.make

3rdParty/libogg/CMakeFiles/ContinuousConfigure:
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg && /usr/bin/ctest -D ContinuousConfigure

ContinuousConfigure: 3rdParty/libogg/CMakeFiles/ContinuousConfigure
ContinuousConfigure: 3rdParty/libogg/CMakeFiles/ContinuousConfigure.dir/build.make
.PHONY : ContinuousConfigure

# Rule to build all files generated by this target.
3rdParty/libogg/CMakeFiles/ContinuousConfigure.dir/build: ContinuousConfigure
.PHONY : 3rdParty/libogg/CMakeFiles/ContinuousConfigure.dir/build

3rdParty/libogg/CMakeFiles/ContinuousConfigure.dir/clean:
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousConfigure.dir/cmake_clean.cmake
.PHONY : 3rdParty/libogg/CMakeFiles/ContinuousConfigure.dir/clean

3rdParty/libogg/CMakeFiles/ContinuousConfigure.dir/depend:
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/m4kulatura/Documents/GitHub/kektech-c /home/m4kulatura/Documents/GitHub/kektech-c/deps/libogg /home/m4kulatura/Documents/GitHub/kektech-c/build /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg/CMakeFiles/ContinuousConfigure.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : 3rdParty/libogg/CMakeFiles/ContinuousConfigure.dir/depend

