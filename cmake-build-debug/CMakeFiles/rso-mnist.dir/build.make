# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /snap/clion/152/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/152/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mdl/CLionProjects/NeuralNetworkC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/rso-mnist.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rso-mnist.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rso-mnist.dir/flags.make

CMakeFiles/rso-mnist.dir/src/main.c.o: CMakeFiles/rso-mnist.dir/flags.make
CMakeFiles/rso-mnist.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/rso-mnist.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/rso-mnist.dir/src/main.c.o -c /home/mdl/CLionProjects/NeuralNetworkC/src/main.c

CMakeFiles/rso-mnist.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rso-mnist.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mdl/CLionProjects/NeuralNetworkC/src/main.c > CMakeFiles/rso-mnist.dir/src/main.c.i

CMakeFiles/rso-mnist.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rso-mnist.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mdl/CLionProjects/NeuralNetworkC/src/main.c -o CMakeFiles/rso-mnist.dir/src/main.c.s

CMakeFiles/rso-mnist.dir/src/Util.c.o: CMakeFiles/rso-mnist.dir/flags.make
CMakeFiles/rso-mnist.dir/src/Util.c.o: ../src/Util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/rso-mnist.dir/src/Util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/rso-mnist.dir/src/Util.c.o -c /home/mdl/CLionProjects/NeuralNetworkC/src/Util.c

CMakeFiles/rso-mnist.dir/src/Util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rso-mnist.dir/src/Util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mdl/CLionProjects/NeuralNetworkC/src/Util.c > CMakeFiles/rso-mnist.dir/src/Util.c.i

CMakeFiles/rso-mnist.dir/src/Util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rso-mnist.dir/src/Util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mdl/CLionProjects/NeuralNetworkC/src/Util.c -o CMakeFiles/rso-mnist.dir/src/Util.c.s

CMakeFiles/rso-mnist.dir/src/structures.c.o: CMakeFiles/rso-mnist.dir/flags.make
CMakeFiles/rso-mnist.dir/src/structures.c.o: ../src/structures.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/rso-mnist.dir/src/structures.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/rso-mnist.dir/src/structures.c.o -c /home/mdl/CLionProjects/NeuralNetworkC/src/structures.c

CMakeFiles/rso-mnist.dir/src/structures.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rso-mnist.dir/src/structures.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mdl/CLionProjects/NeuralNetworkC/src/structures.c > CMakeFiles/rso-mnist.dir/src/structures.c.i

CMakeFiles/rso-mnist.dir/src/structures.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rso-mnist.dir/src/structures.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mdl/CLionProjects/NeuralNetworkC/src/structures.c -o CMakeFiles/rso-mnist.dir/src/structures.c.s

CMakeFiles/rso-mnist.dir/src/calculs.c.o: CMakeFiles/rso-mnist.dir/flags.make
CMakeFiles/rso-mnist.dir/src/calculs.c.o: ../src/calculs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/rso-mnist.dir/src/calculs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/rso-mnist.dir/src/calculs.c.o -c /home/mdl/CLionProjects/NeuralNetworkC/src/calculs.c

CMakeFiles/rso-mnist.dir/src/calculs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rso-mnist.dir/src/calculs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mdl/CLionProjects/NeuralNetworkC/src/calculs.c > CMakeFiles/rso-mnist.dir/src/calculs.c.i

CMakeFiles/rso-mnist.dir/src/calculs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rso-mnist.dir/src/calculs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mdl/CLionProjects/NeuralNetworkC/src/calculs.c -o CMakeFiles/rso-mnist.dir/src/calculs.c.s

CMakeFiles/rso-mnist.dir/src/functionsIO.c.o: CMakeFiles/rso-mnist.dir/flags.make
CMakeFiles/rso-mnist.dir/src/functionsIO.c.o: ../src/functionsIO.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/rso-mnist.dir/src/functionsIO.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/rso-mnist.dir/src/functionsIO.c.o -c /home/mdl/CLionProjects/NeuralNetworkC/src/functionsIO.c

CMakeFiles/rso-mnist.dir/src/functionsIO.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rso-mnist.dir/src/functionsIO.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mdl/CLionProjects/NeuralNetworkC/src/functionsIO.c > CMakeFiles/rso-mnist.dir/src/functionsIO.c.i

CMakeFiles/rso-mnist.dir/src/functionsIO.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rso-mnist.dir/src/functionsIO.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mdl/CLionProjects/NeuralNetworkC/src/functionsIO.c -o CMakeFiles/rso-mnist.dir/src/functionsIO.c.s

CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.o: CMakeFiles/rso-mnist.dir/flags.make
CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.o: ../src/fonctionsRso.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.o -c /home/mdl/CLionProjects/NeuralNetworkC/src/fonctionsRso.c

CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mdl/CLionProjects/NeuralNetworkC/src/fonctionsRso.c > CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.i

CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mdl/CLionProjects/NeuralNetworkC/src/fonctionsRso.c -o CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.s

# Object files for target rso-mnist
rso__mnist_OBJECTS = \
"CMakeFiles/rso-mnist.dir/src/main.c.o" \
"CMakeFiles/rso-mnist.dir/src/Util.c.o" \
"CMakeFiles/rso-mnist.dir/src/structures.c.o" \
"CMakeFiles/rso-mnist.dir/src/calculs.c.o" \
"CMakeFiles/rso-mnist.dir/src/functionsIO.c.o" \
"CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.o"

# External object files for target rso-mnist
rso__mnist_EXTERNAL_OBJECTS =

rso-mnist: CMakeFiles/rso-mnist.dir/src/main.c.o
rso-mnist: CMakeFiles/rso-mnist.dir/src/Util.c.o
rso-mnist: CMakeFiles/rso-mnist.dir/src/structures.c.o
rso-mnist: CMakeFiles/rso-mnist.dir/src/calculs.c.o
rso-mnist: CMakeFiles/rso-mnist.dir/src/functionsIO.c.o
rso-mnist: CMakeFiles/rso-mnist.dir/src/fonctionsRso.c.o
rso-mnist: CMakeFiles/rso-mnist.dir/build.make
rso-mnist: CMakeFiles/rso-mnist.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable rso-mnist"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rso-mnist.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rso-mnist.dir/build: rso-mnist

.PHONY : CMakeFiles/rso-mnist.dir/build

CMakeFiles/rso-mnist.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rso-mnist.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rso-mnist.dir/clean

CMakeFiles/rso-mnist.dir/depend:
	cd /home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mdl/CLionProjects/NeuralNetworkC /home/mdl/CLionProjects/NeuralNetworkC /home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug /home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug /home/mdl/CLionProjects/NeuralNetworkC/cmake-build-debug/CMakeFiles/rso-mnist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rso-mnist.dir/depend

