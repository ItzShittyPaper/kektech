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

# Include any dependencies generated for this target.
include 3rdParty/opus/CMakeFiles/test_opus_api.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include 3rdParty/opus/CMakeFiles/test_opus_api.dir/compiler_depend.make

# Include the progress variables for this target.
include 3rdParty/opus/CMakeFiles/test_opus_api.dir/progress.make

# Include the compile flags for this target's objects.
include 3rdParty/opus/CMakeFiles/test_opus_api.dir/flags.make

3rdParty/opus/CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.o: 3rdParty/opus/CMakeFiles/test_opus_api.dir/flags.make
3rdParty/opus/CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.o: /home/m4kulatura/Documents/GitHub/kektech/deps/opus/tests/test_opus_api.c
3rdParty/opus/CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.o: 3rdParty/opus/CMakeFiles/test_opus_api.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/m4kulatura/Documents/GitHub/kektech/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object 3rdParty/opus/CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.o"
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/opus && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT 3rdParty/opus/CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.o -MF CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.o.d -o CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.o -c /home/m4kulatura/Documents/GitHub/kektech/deps/opus/tests/test_opus_api.c

3rdParty/opus/CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.i"
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/opus && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/m4kulatura/Documents/GitHub/kektech/deps/opus/tests/test_opus_api.c > CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.i

3rdParty/opus/CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.s"
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/opus && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/m4kulatura/Documents/GitHub/kektech/deps/opus/tests/test_opus_api.c -o CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.s

# Object files for target test_opus_api
test_opus_api_OBJECTS = \
"CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.o"

# External object files for target test_opus_api
test_opus_api_EXTERNAL_OBJECTS =

bin/test_opus_api: 3rdParty/opus/CMakeFiles/test_opus_api.dir/tests/test_opus_api.c.o
bin/test_opus_api: 3rdParty/opus/CMakeFiles/test_opus_api.dir/build.make
bin/test_opus_api: lib/libopus.a
bin/test_opus_api: 3rdParty/opus/CMakeFiles/test_opus_api.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/m4kulatura/Documents/GitHub/kektech/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../bin/test_opus_api"
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/opus && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_opus_api.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
3rdParty/opus/CMakeFiles/test_opus_api.dir/build: bin/test_opus_api
.PHONY : 3rdParty/opus/CMakeFiles/test_opus_api.dir/build

3rdParty/opus/CMakeFiles/test_opus_api.dir/clean:
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/opus && $(CMAKE_COMMAND) -P CMakeFiles/test_opus_api.dir/cmake_clean.cmake
.PHONY : 3rdParty/opus/CMakeFiles/test_opus_api.dir/clean

3rdParty/opus/CMakeFiles/test_opus_api.dir/depend:
	cd /home/m4kulatura/Documents/GitHub/kektech/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/m4kulatura/Documents/GitHub/kektech /home/m4kulatura/Documents/GitHub/kektech/deps/opus /home/m4kulatura/Documents/GitHub/kektech/build /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/opus /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/opus/CMakeFiles/test_opus_api.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : 3rdParty/opus/CMakeFiles/test_opus_api.dir/depend

