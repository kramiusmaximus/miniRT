# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/markartyukh/CLionProjects/miniRT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/markartyukh/CLionProjects/miniRT/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/miniRT.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/miniRT.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/miniRT.dir/flags.make

CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.o: CMakeFiles/miniRT.dir/flags.make
CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.o: ../srcs/intersect_shapes.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.o   -c /Users/markartyukh/CLionProjects/miniRT/srcs/intersect_shapes.c

CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/markartyukh/CLionProjects/miniRT/srcs/intersect_shapes.c > CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.i

CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/markartyukh/CLionProjects/miniRT/srcs/intersect_shapes.c -o CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.s

CMakeFiles/miniRT.dir/srcs/light.c.o: CMakeFiles/miniRT.dir/flags.make
CMakeFiles/miniRT.dir/srcs/light.c.o: ../srcs/light.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/miniRT.dir/srcs/light.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniRT.dir/srcs/light.c.o   -c /Users/markartyukh/CLionProjects/miniRT/srcs/light.c

CMakeFiles/miniRT.dir/srcs/light.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniRT.dir/srcs/light.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/markartyukh/CLionProjects/miniRT/srcs/light.c > CMakeFiles/miniRT.dir/srcs/light.c.i

CMakeFiles/miniRT.dir/srcs/light.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniRT.dir/srcs/light.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/markartyukh/CLionProjects/miniRT/srcs/light.c -o CMakeFiles/miniRT.dir/srcs/light.c.s

CMakeFiles/miniRT.dir/srcs/math.c.o: CMakeFiles/miniRT.dir/flags.make
CMakeFiles/miniRT.dir/srcs/math.c.o: ../srcs/math.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/miniRT.dir/srcs/math.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniRT.dir/srcs/math.c.o   -c /Users/markartyukh/CLionProjects/miniRT/srcs/math.c

CMakeFiles/miniRT.dir/srcs/math.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniRT.dir/srcs/math.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/markartyukh/CLionProjects/miniRT/srcs/math.c > CMakeFiles/miniRT.dir/srcs/math.c.i

CMakeFiles/miniRT.dir/srcs/math.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniRT.dir/srcs/math.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/markartyukh/CLionProjects/miniRT/srcs/math.c -o CMakeFiles/miniRT.dir/srcs/math.c.s

CMakeFiles/miniRT.dir/srcs/rendering.c.o: CMakeFiles/miniRT.dir/flags.make
CMakeFiles/miniRT.dir/srcs/rendering.c.o: ../srcs/rendering.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/miniRT.dir/srcs/rendering.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniRT.dir/srcs/rendering.c.o   -c /Users/markartyukh/CLionProjects/miniRT/srcs/rendering.c

CMakeFiles/miniRT.dir/srcs/rendering.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniRT.dir/srcs/rendering.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/markartyukh/CLionProjects/miniRT/srcs/rendering.c > CMakeFiles/miniRT.dir/srcs/rendering.c.i

CMakeFiles/miniRT.dir/srcs/rendering.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniRT.dir/srcs/rendering.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/markartyukh/CLionProjects/miniRT/srcs/rendering.c -o CMakeFiles/miniRT.dir/srcs/rendering.c.s

CMakeFiles/miniRT.dir/srcs/scene.c.o: CMakeFiles/miniRT.dir/flags.make
CMakeFiles/miniRT.dir/srcs/scene.c.o: ../srcs/scene.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/miniRT.dir/srcs/scene.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniRT.dir/srcs/scene.c.o   -c /Users/markartyukh/CLionProjects/miniRT/srcs/scene.c

CMakeFiles/miniRT.dir/srcs/scene.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniRT.dir/srcs/scene.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/markartyukh/CLionProjects/miniRT/srcs/scene.c > CMakeFiles/miniRT.dir/srcs/scene.c.i

CMakeFiles/miniRT.dir/srcs/scene.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniRT.dir/srcs/scene.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/markartyukh/CLionProjects/miniRT/srcs/scene.c -o CMakeFiles/miniRT.dir/srcs/scene.c.s

CMakeFiles/miniRT.dir/srcs/surface_vectors.c.o: CMakeFiles/miniRT.dir/flags.make
CMakeFiles/miniRT.dir/srcs/surface_vectors.c.o: ../srcs/surface_vectors.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/miniRT.dir/srcs/surface_vectors.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniRT.dir/srcs/surface_vectors.c.o   -c /Users/markartyukh/CLionProjects/miniRT/srcs/surface_vectors.c

CMakeFiles/miniRT.dir/srcs/surface_vectors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniRT.dir/srcs/surface_vectors.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/markartyukh/CLionProjects/miniRT/srcs/surface_vectors.c > CMakeFiles/miniRT.dir/srcs/surface_vectors.c.i

CMakeFiles/miniRT.dir/srcs/surface_vectors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniRT.dir/srcs/surface_vectors.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/markartyukh/CLionProjects/miniRT/srcs/surface_vectors.c -o CMakeFiles/miniRT.dir/srcs/surface_vectors.c.s

CMakeFiles/miniRT.dir/srcs/trace_ray.c.o: CMakeFiles/miniRT.dir/flags.make
CMakeFiles/miniRT.dir/srcs/trace_ray.c.o: ../srcs/trace_ray.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/miniRT.dir/srcs/trace_ray.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniRT.dir/srcs/trace_ray.c.o   -c /Users/markartyukh/CLionProjects/miniRT/srcs/trace_ray.c

CMakeFiles/miniRT.dir/srcs/trace_ray.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniRT.dir/srcs/trace_ray.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/markartyukh/CLionProjects/miniRT/srcs/trace_ray.c > CMakeFiles/miniRT.dir/srcs/trace_ray.c.i

CMakeFiles/miniRT.dir/srcs/trace_ray.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniRT.dir/srcs/trace_ray.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/markartyukh/CLionProjects/miniRT/srcs/trace_ray.c -o CMakeFiles/miniRT.dir/srcs/trace_ray.c.s

CMakeFiles/miniRT.dir/srcs/utils.c.o: CMakeFiles/miniRT.dir/flags.make
CMakeFiles/miniRT.dir/srcs/utils.c.o: ../srcs/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/miniRT.dir/srcs/utils.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniRT.dir/srcs/utils.c.o   -c /Users/markartyukh/CLionProjects/miniRT/srcs/utils.c

CMakeFiles/miniRT.dir/srcs/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniRT.dir/srcs/utils.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/markartyukh/CLionProjects/miniRT/srcs/utils.c > CMakeFiles/miniRT.dir/srcs/utils.c.i

CMakeFiles/miniRT.dir/srcs/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniRT.dir/srcs/utils.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/markartyukh/CLionProjects/miniRT/srcs/utils.c -o CMakeFiles/miniRT.dir/srcs/utils.c.s

CMakeFiles/miniRT.dir/srcs/visual.c.o: CMakeFiles/miniRT.dir/flags.make
CMakeFiles/miniRT.dir/srcs/visual.c.o: ../srcs/visual.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/miniRT.dir/srcs/visual.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniRT.dir/srcs/visual.c.o   -c /Users/markartyukh/CLionProjects/miniRT/srcs/visual.c

CMakeFiles/miniRT.dir/srcs/visual.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniRT.dir/srcs/visual.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/markartyukh/CLionProjects/miniRT/srcs/visual.c > CMakeFiles/miniRT.dir/srcs/visual.c.i

CMakeFiles/miniRT.dir/srcs/visual.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniRT.dir/srcs/visual.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/markartyukh/CLionProjects/miniRT/srcs/visual.c -o CMakeFiles/miniRT.dir/srcs/visual.c.s

CMakeFiles/miniRT.dir/main.c.o: CMakeFiles/miniRT.dir/flags.make
CMakeFiles/miniRT.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/miniRT.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniRT.dir/main.c.o   -c /Users/markartyukh/CLionProjects/miniRT/main.c

CMakeFiles/miniRT.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniRT.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/markartyukh/CLionProjects/miniRT/main.c > CMakeFiles/miniRT.dir/main.c.i

CMakeFiles/miniRT.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniRT.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/markartyukh/CLionProjects/miniRT/main.c -o CMakeFiles/miniRT.dir/main.c.s

# Object files for target miniRT
miniRT_OBJECTS = \
"CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.o" \
"CMakeFiles/miniRT.dir/srcs/light.c.o" \
"CMakeFiles/miniRT.dir/srcs/math.c.o" \
"CMakeFiles/miniRT.dir/srcs/rendering.c.o" \
"CMakeFiles/miniRT.dir/srcs/scene.c.o" \
"CMakeFiles/miniRT.dir/srcs/surface_vectors.c.o" \
"CMakeFiles/miniRT.dir/srcs/trace_ray.c.o" \
"CMakeFiles/miniRT.dir/srcs/utils.c.o" \
"CMakeFiles/miniRT.dir/srcs/visual.c.o" \
"CMakeFiles/miniRT.dir/main.c.o"

# External object files for target miniRT
miniRT_EXTERNAL_OBJECTS =

miniRT: CMakeFiles/miniRT.dir/srcs/intersect_shapes.c.o
miniRT: CMakeFiles/miniRT.dir/srcs/light.c.o
miniRT: CMakeFiles/miniRT.dir/srcs/math.c.o
miniRT: CMakeFiles/miniRT.dir/srcs/rendering.c.o
miniRT: CMakeFiles/miniRT.dir/srcs/scene.c.o
miniRT: CMakeFiles/miniRT.dir/srcs/surface_vectors.c.o
miniRT: CMakeFiles/miniRT.dir/srcs/trace_ray.c.o
miniRT: CMakeFiles/miniRT.dir/srcs/utils.c.o
miniRT: CMakeFiles/miniRT.dir/srcs/visual.c.o
miniRT: CMakeFiles/miniRT.dir/main.c.o
miniRT: CMakeFiles/miniRT.dir/build.make
miniRT: ../mlx/libmlx.a
miniRT: CMakeFiles/miniRT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable miniRT"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/miniRT.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/miniRT.dir/build: miniRT

.PHONY : CMakeFiles/miniRT.dir/build

CMakeFiles/miniRT.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/miniRT.dir/cmake_clean.cmake
.PHONY : CMakeFiles/miniRT.dir/clean

CMakeFiles/miniRT.dir/depend:
	cd /Users/markartyukh/CLionProjects/miniRT/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/markartyukh/CLionProjects/miniRT /Users/markartyukh/CLionProjects/miniRT /Users/markartyukh/CLionProjects/miniRT/cmake-build-debug /Users/markartyukh/CLionProjects/miniRT/cmake-build-debug /Users/markartyukh/CLionProjects/miniRT/cmake-build-debug/CMakeFiles/miniRT.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/miniRT.dir/depend

