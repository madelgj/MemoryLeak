# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/madel/Desktop/University/Industrial informatics/memoryleak"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/madel/Desktop/University/Industrial informatics/memoryleak/build"

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_memoryleak_interactions.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_memoryleak_interactions.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_memoryleak_interactions.dir/flags.make

tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o: tests/CMakeFiles/test_memoryleak_interactions.dir/flags.make
tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o: ../tests/test_memoryleak_interactions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/madel/Desktop/University/Industrial informatics/memoryleak/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o"
	cd "/home/madel/Desktop/University/Industrial informatics/memoryleak/build/tests" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o -c "/home/madel/Desktop/University/Industrial informatics/memoryleak/tests/test_memoryleak_interactions.cpp"

tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.i"
	cd "/home/madel/Desktop/University/Industrial informatics/memoryleak/build/tests" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/madel/Desktop/University/Industrial informatics/memoryleak/tests/test_memoryleak_interactions.cpp" > CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.i

tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.s"
	cd "/home/madel/Desktop/University/Industrial informatics/memoryleak/build/tests" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/madel/Desktop/University/Industrial informatics/memoryleak/tests/test_memoryleak_interactions.cpp" -o CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.s

tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o.requires:

.PHONY : tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o.requires

tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o.provides: tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o.requires
	$(MAKE) -f tests/CMakeFiles/test_memoryleak_interactions.dir/build.make tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o.provides.build
.PHONY : tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o.provides

tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o.provides.build: tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o


# Object files for target test_memoryleak_interactions
test_memoryleak_interactions_OBJECTS = \
"CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o"

# External object files for target test_memoryleak_interactions
test_memoryleak_interactions_EXTERNAL_OBJECTS =

tests/test_memoryleak_interactions: tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o
tests/test_memoryleak_interactions: tests/CMakeFiles/test_memoryleak_interactions.dir/build.make
tests/test_memoryleak_interactions: lib/libgtest_maind.a
tests/test_memoryleak_interactions: libMemoryLeakLib.a
tests/test_memoryleak_interactions: lib/libgtestd.a
tests/test_memoryleak_interactions: tests/CMakeFiles/test_memoryleak_interactions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/madel/Desktop/University/Industrial informatics/memoryleak/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_memoryleak_interactions"
	cd "/home/madel/Desktop/University/Industrial informatics/memoryleak/build/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_memoryleak_interactions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_memoryleak_interactions.dir/build: tests/test_memoryleak_interactions

.PHONY : tests/CMakeFiles/test_memoryleak_interactions.dir/build

tests/CMakeFiles/test_memoryleak_interactions.dir/requires: tests/CMakeFiles/test_memoryleak_interactions.dir/test_memoryleak_interactions.cpp.o.requires

.PHONY : tests/CMakeFiles/test_memoryleak_interactions.dir/requires

tests/CMakeFiles/test_memoryleak_interactions.dir/clean:
	cd "/home/madel/Desktop/University/Industrial informatics/memoryleak/build/tests" && $(CMAKE_COMMAND) -P CMakeFiles/test_memoryleak_interactions.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_memoryleak_interactions.dir/clean

tests/CMakeFiles/test_memoryleak_interactions.dir/depend:
	cd "/home/madel/Desktop/University/Industrial informatics/memoryleak/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/madel/Desktop/University/Industrial informatics/memoryleak" "/home/madel/Desktop/University/Industrial informatics/memoryleak/tests" "/home/madel/Desktop/University/Industrial informatics/memoryleak/build" "/home/madel/Desktop/University/Industrial informatics/memoryleak/build/tests" "/home/madel/Desktop/University/Industrial informatics/memoryleak/build/tests/CMakeFiles/test_memoryleak_interactions.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_memoryleak_interactions.dir/depend

