# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/dev/github/playingCardsLib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/dev/github/playingCardsLib/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/playingCardsLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/playingCardsLib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/playingCardsLib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/playingCardsLib.dir/flags.make

CMakeFiles/playingCardsLib.dir/library.cpp.o: CMakeFiles/playingCardsLib.dir/flags.make
CMakeFiles/playingCardsLib.dir/library.cpp.o: /mnt/c/dev/github/playingCardsLib/library.cpp
CMakeFiles/playingCardsLib.dir/library.cpp.o: CMakeFiles/playingCardsLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/dev/github/playingCardsLib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/playingCardsLib.dir/library.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/playingCardsLib.dir/library.cpp.o -MF CMakeFiles/playingCardsLib.dir/library.cpp.o.d -o CMakeFiles/playingCardsLib.dir/library.cpp.o -c /mnt/c/dev/github/playingCardsLib/library.cpp

CMakeFiles/playingCardsLib.dir/library.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/playingCardsLib.dir/library.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/dev/github/playingCardsLib/library.cpp > CMakeFiles/playingCardsLib.dir/library.cpp.i

CMakeFiles/playingCardsLib.dir/library.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/playingCardsLib.dir/library.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/dev/github/playingCardsLib/library.cpp -o CMakeFiles/playingCardsLib.dir/library.cpp.s

# Object files for target playingCardsLib
playingCardsLib_OBJECTS = \
"CMakeFiles/playingCardsLib.dir/library.cpp.o"

# External object files for target playingCardsLib
playingCardsLib_EXTERNAL_OBJECTS =

libplayingCardsLib.a: CMakeFiles/playingCardsLib.dir/library.cpp.o
libplayingCardsLib.a: CMakeFiles/playingCardsLib.dir/build.make
libplayingCardsLib.a: CMakeFiles/playingCardsLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/dev/github/playingCardsLib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libplayingCardsLib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/playingCardsLib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/playingCardsLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/playingCardsLib.dir/build: libplayingCardsLib.a
.PHONY : CMakeFiles/playingCardsLib.dir/build

CMakeFiles/playingCardsLib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/playingCardsLib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/playingCardsLib.dir/clean

CMakeFiles/playingCardsLib.dir/depend:
	cd /mnt/c/dev/github/playingCardsLib/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/dev/github/playingCardsLib /mnt/c/dev/github/playingCardsLib /mnt/c/dev/github/playingCardsLib/cmake-build-debug /mnt/c/dev/github/playingCardsLib/cmake-build-debug /mnt/c/dev/github/playingCardsLib/cmake-build-debug/CMakeFiles/playingCardsLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/playingCardsLib.dir/depend

