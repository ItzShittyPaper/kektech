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

# Include any dependencies generated for this target.
include 3rdParty/libogg/CMakeFiles/ogg.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include 3rdParty/libogg/CMakeFiles/ogg.dir/compiler_depend.make

# Include the progress variables for this target.
include 3rdParty/libogg/CMakeFiles/ogg.dir/progress.make

# Include the compile flags for this target's objects.
include 3rdParty/libogg/CMakeFiles/ogg.dir/flags.make

3rdParty/libogg/CMakeFiles/ogg.dir/src/bitwise.c.o: 3rdParty/libogg/CMakeFiles/ogg.dir/flags.make
3rdParty/libogg/CMakeFiles/ogg.dir/src/bitwise.c.o: /home/m4kulatura/Documents/GitHub/kektech-c/deps/libogg/src/bitwise.c
3rdParty/libogg/CMakeFiles/ogg.dir/src/bitwise.c.o: 3rdParty/libogg/CMakeFiles/ogg.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/m4kulatura/Documents/GitHub/kektech-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object 3rdParty/libogg/CMakeFiles/ogg.dir/src/bitwise.c.o"
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT 3rdParty/libogg/CMakeFiles/ogg.dir/src/bitwise.c.o -MF CMakeFiles/ogg.dir/src/bitwise.c.o.d -o CMakeFiles/ogg.dir/src/bitwise.c.o -c /home/m4kulatura/Documents/GitHub/kektech-c/deps/libogg/src/bitwise.c

3rdParty/libogg/CMakeFiles/ogg.dir/src/bitwise.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ogg.dir/src/bitwise.c.i"
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/m4kulatura/Documents/GitHub/kektech-c/deps/libogg/src/bitwise.c > CMakeFiles/ogg.dir/src/bitwise.c.i

3rdParty/libogg/CMakeFiles/ogg.dir/src/bitwise.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ogg.dir/src/bitwise.c.s"
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/m4kulatura/Documents/GitHub/kektech-c/deps/libogg/src/bitwise.c -o CMakeFiles/ogg.dir/src/bitwise.c.s

3rdParty/libogg/CMakeFiles/ogg.dir/src/framing.c.o: 3rdParty/libogg/CMakeFiles/ogg.dir/flags.make
3rdParty/libogg/CMakeFiles/ogg.dir/src/framing.c.o: /home/m4kulatura/Documents/GitHub/kektech-c/deps/libogg/src/framing.c
3rdParty/libogg/CMakeFiles/ogg.dir/src/framing.c.o: 3rdParty/libogg/CMakeFiles/ogg.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/m4kulatura/Documents/GitHub/kektech-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object 3rdParty/libogg/CMakeFiles/ogg.dir/src/framing.c.o"
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT 3rdParty/libogg/CMakeFiles/ogg.dir/src/framing.c.o -MF CMakeFiles/ogg.dir/src/framing.c.o.d -o CMakeFiles/ogg.dir/src/framing.c.o -c /home/m4kulatura/Documents/GitHub/kektech-c/deps/libogg/src/framing.c

3rdParty/libogg/CMakeFiles/ogg.dir/src/framing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ogg.dir/src/framing.c.i"
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/m4kulatura/Documents/GitHub/kektech-c/deps/libogg/src/framing.c > CMakeFiles/ogg.dir/src/framing.c.i

3rdParty/libogg/CMakeFiles/ogg.dir/src/framing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ogg.dir/src/framing.c.s"
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/m4kulatura/Documents/GitHub/kektech-c/deps/libogg/src/framing.c -o CMakeFiles/ogg.dir/src/framing.c.s

# Object files for target ogg
ogg_OBJECTS = \
"CMakeFiles/ogg.dir/src/bitwise.c.o" \
"CMakeFiles/ogg.dir/src/framing.c.o"

# External object files for target ogg
ogg_EXTERNAL_OBJECTS =

lib/libogg.a: 3rdParty/libogg/CMakeFiles/ogg.dir/src/bitwise.c.o
lib/libogg.a: 3rdParty/libogg/CMakeFiles/ogg.dir/src/framing.c.o
lib/libogg.a: 3rdParty/libogg/CMakeFiles/ogg.dir/build.make
lib/libogg.a: 3rdParty/libogg/CMakeFiles/ogg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/m4kulatura/Documents/GitHub/kektech-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library ../../lib/libogg.a"
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg && $(CMAKE_COMMAND) -P CMakeFiles/ogg.dir/cmake_clean_target.cmake
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ogg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
3rdParty/libogg/CMakeFiles/ogg.dir/build: lib/libogg.a
.PHONY : 3rdParty/libogg/CMakeFiles/ogg.dir/build

3rdParty/libogg/CMakeFiles/ogg.dir/clean:
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg && $(CMAKE_COMMAND) -P CMakeFiles/ogg.dir/cmake_clean.cmake
.PHONY : 3rdParty/libogg/CMakeFiles/ogg.dir/clean

3rdParty/libogg/CMakeFiles/ogg.dir/depend:
	cd /home/m4kulatura/Documents/GitHub/kektech-c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/m4kulatura/Documents/GitHub/kektech-c /home/m4kulatura/Documents/GitHub/kektech-c/deps/libogg /home/m4kulatura/Documents/GitHub/kektech-c/build /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/libogg/CMakeFiles/ogg.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : 3rdParty/libogg/CMakeFiles/ogg.dir/depend

