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
CMAKE_SOURCE_DIR = /home/m4kulatura/Documents/GitHub/kektech

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/m4kulatura/Documents/GitHub/kektech/build

# Utility rule file for ExperimentalCoverage.

# Include any custom commands dependencies for this target.
include 3rdParty/libogg/CMakeFiles/ExperimentalCoverage.dir/compiler_depend.make

# Include the progress variables for this target.
include 3rdParty/libogg/CMakeFiles/ExperimentalCoverage.dir/progress.make

3rdParty/libogg/CMakeFiles/ExperimentalCoverage:
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/libogg && /usr/bin/ctest -D ExperimentalCoverage

ExperimentalCoverage: 3rdParty/libogg/CMakeFiles/ExperimentalCoverage
ExperimentalCoverage: 3rdParty/libogg/CMakeFiles/ExperimentalCoverage.dir/build.make
.PHONY : ExperimentalCoverage

# Rule to build all files generated by this target.
3rdParty/libogg/CMakeFiles/ExperimentalCoverage.dir/build: ExperimentalCoverage
.PHONY : 3rdParty/libogg/CMakeFiles/ExperimentalCoverage.dir/build

3rdParty/libogg/CMakeFiles/ExperimentalCoverage.dir/clean:
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/libogg && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalCoverage.dir/cmake_clean.cmake
.PHONY : 3rdParty/libogg/CMakeFiles/ExperimentalCoverage.dir/clean

3rdParty/libogg/CMakeFiles/ExperimentalCoverage.dir/depend:
	cd /home/m4kulatura/Documents/GitHub/kektech/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/m4kulatura/Documents/GitHub/kektech /home/m4kulatura/Documents/GitHub/kektech/deps/libogg /home/m4kulatura/Documents/GitHub/kektech/build /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/libogg /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/libogg/CMakeFiles/ExperimentalCoverage.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : 3rdParty/libogg/CMakeFiles/ExperimentalCoverage.dir/depend

