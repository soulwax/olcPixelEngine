# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/pi/workspace/PixelEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/workspace/PixelEngine

# Utility rule file for ExperimentalUpdate.

# Include the progress variables for this target.
include CMakeFiles/ExperimentalUpdate.dir/progress.make

CMakeFiles/ExperimentalUpdate:
	/usr/bin/ctest -D ExperimentalUpdate

ExperimentalUpdate: CMakeFiles/ExperimentalUpdate
ExperimentalUpdate: CMakeFiles/ExperimentalUpdate.dir/build.make

.PHONY : ExperimentalUpdate

# Rule to build all files generated by this target.
CMakeFiles/ExperimentalUpdate.dir/build: ExperimentalUpdate

.PHONY : CMakeFiles/ExperimentalUpdate.dir/build

CMakeFiles/ExperimentalUpdate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ExperimentalUpdate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ExperimentalUpdate.dir/clean

CMakeFiles/ExperimentalUpdate.dir/depend:
	cd /home/pi/workspace/PixelEngine && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/workspace/PixelEngine /home/pi/workspace/PixelEngine /home/pi/workspace/PixelEngine /home/pi/workspace/PixelEngine /home/pi/workspace/PixelEngine/CMakeFiles/ExperimentalUpdate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ExperimentalUpdate.dir/depend

