# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bluefog/Documents/dev/alpha

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bluefog/Documents/dev/alpha/build

# Include any dependencies generated for this target.
include spike/code/CMakeFiles/pinhole.dir/depend.make

# Include the progress variables for this target.
include spike/code/CMakeFiles/pinhole.dir/progress.make

# Include the compile flags for this target's objects.
include spike/code/CMakeFiles/pinhole.dir/flags.make

spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o: spike/code/CMakeFiles/pinhole.dir/flags.make
spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o: ../spike/code/pinhole.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bluefog/Documents/dev/alpha/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o"
	cd /home/bluefog/Documents/dev/alpha/build/spike/code && /usr/lib/ccache/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pinhole.dir/pinhole.cpp.o -c /home/bluefog/Documents/dev/alpha/spike/code/pinhole.cpp

spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pinhole.dir/pinhole.cpp.i"
	cd /home/bluefog/Documents/dev/alpha/build/spike/code && /usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bluefog/Documents/dev/alpha/spike/code/pinhole.cpp > CMakeFiles/pinhole.dir/pinhole.cpp.i

spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pinhole.dir/pinhole.cpp.s"
	cd /home/bluefog/Documents/dev/alpha/build/spike/code && /usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bluefog/Documents/dev/alpha/spike/code/pinhole.cpp -o CMakeFiles/pinhole.dir/pinhole.cpp.s

spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o.requires:
.PHONY : spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o.requires

spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o.provides: spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o.requires
	$(MAKE) -f spike/code/CMakeFiles/pinhole.dir/build.make spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o.provides.build
.PHONY : spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o.provides

spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o.provides.build: spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o

# Object files for target pinhole
pinhole_OBJECTS = \
"CMakeFiles/pinhole.dir/pinhole.cpp.o"

# External object files for target pinhole
pinhole_EXTERNAL_OBJECTS =

pinhole: spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o
pinhole: spike/code/CMakeFiles/pinhole.dir/build.make
pinhole: spike/code/CMakeFiles/pinhole.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../pinhole"
	cd /home/bluefog/Documents/dev/alpha/build/spike/code && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pinhole.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
spike/code/CMakeFiles/pinhole.dir/build: pinhole
.PHONY : spike/code/CMakeFiles/pinhole.dir/build

spike/code/CMakeFiles/pinhole.dir/requires: spike/code/CMakeFiles/pinhole.dir/pinhole.cpp.o.requires
.PHONY : spike/code/CMakeFiles/pinhole.dir/requires

spike/code/CMakeFiles/pinhole.dir/clean:
	cd /home/bluefog/Documents/dev/alpha/build/spike/code && $(CMAKE_COMMAND) -P CMakeFiles/pinhole.dir/cmake_clean.cmake
.PHONY : spike/code/CMakeFiles/pinhole.dir/clean

spike/code/CMakeFiles/pinhole.dir/depend:
	cd /home/bluefog/Documents/dev/alpha/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bluefog/Documents/dev/alpha /home/bluefog/Documents/dev/alpha/spike/code /home/bluefog/Documents/dev/alpha/build /home/bluefog/Documents/dev/alpha/build/spike/code /home/bluefog/Documents/dev/alpha/build/spike/code/CMakeFiles/pinhole.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : spike/code/CMakeFiles/pinhole.dir/depend
