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
include 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/compiler_depend.make

# Include the progress variables for this target.
include 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/progress.make

# Include the compile flags for this target's objects.
include 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/flags.make

3rdParty/openal-soft/CMakeFiles/alhrtf.dir/examples/alhrtf.c.o: 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/flags.make
3rdParty/openal-soft/CMakeFiles/alhrtf.dir/examples/alhrtf.c.o: /home/m4kulatura/Documents/GitHub/kektech/deps/openal-soft/examples/alhrtf.c
3rdParty/openal-soft/CMakeFiles/alhrtf.dir/examples/alhrtf.c.o: 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/m4kulatura/Documents/GitHub/kektech/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/examples/alhrtf.c.o"
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/openal-soft && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/examples/alhrtf.c.o -MF CMakeFiles/alhrtf.dir/examples/alhrtf.c.o.d -o CMakeFiles/alhrtf.dir/examples/alhrtf.c.o -c /home/m4kulatura/Documents/GitHub/kektech/deps/openal-soft/examples/alhrtf.c

3rdParty/openal-soft/CMakeFiles/alhrtf.dir/examples/alhrtf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/alhrtf.dir/examples/alhrtf.c.i"
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/openal-soft && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/m4kulatura/Documents/GitHub/kektech/deps/openal-soft/examples/alhrtf.c > CMakeFiles/alhrtf.dir/examples/alhrtf.c.i

3rdParty/openal-soft/CMakeFiles/alhrtf.dir/examples/alhrtf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/alhrtf.dir/examples/alhrtf.c.s"
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/openal-soft && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/m4kulatura/Documents/GitHub/kektech/deps/openal-soft/examples/alhrtf.c -o CMakeFiles/alhrtf.dir/examples/alhrtf.c.s

# Object files for target alhrtf
alhrtf_OBJECTS = \
"CMakeFiles/alhrtf.dir/examples/alhrtf.c.o"

# External object files for target alhrtf
alhrtf_EXTERNAL_OBJECTS =

bin/alhrtf: 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/examples/alhrtf.c.o
bin/alhrtf: 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/build.make
bin/alhrtf: /usr/lib64/libsndfile.so
bin/alhrtf: lib/libex-common.a
bin/alhrtf: /usr/lib64/libm.so
bin/alhrtf: bin/libopenal.so.1.23.1
bin/alhrtf: 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/m4kulatura/Documents/GitHub/kektech/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../bin/alhrtf"
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/openal-soft && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alhrtf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
3rdParty/openal-soft/CMakeFiles/alhrtf.dir/build: bin/alhrtf
.PHONY : 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/build

3rdParty/openal-soft/CMakeFiles/alhrtf.dir/clean:
	cd /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/openal-soft && $(CMAKE_COMMAND) -P CMakeFiles/alhrtf.dir/cmake_clean.cmake
.PHONY : 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/clean

3rdParty/openal-soft/CMakeFiles/alhrtf.dir/depend:
	cd /home/m4kulatura/Documents/GitHub/kektech/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/m4kulatura/Documents/GitHub/kektech /home/m4kulatura/Documents/GitHub/kektech/deps/openal-soft /home/m4kulatura/Documents/GitHub/kektech/build /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/openal-soft /home/m4kulatura/Documents/GitHub/kektech/build/3rdParty/openal-soft/CMakeFiles/alhrtf.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : 3rdParty/openal-soft/CMakeFiles/alhrtf.dir/depend

