# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /opt/clion-2019.1.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.1.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/2_task.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/2_task.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2_task.dir/flags.make

CMakeFiles/2_task.dir/main.cpp.o: CMakeFiles/2_task.dir/flags.make
CMakeFiles/2_task.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2_task.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/2_task.dir/main.cpp.o -c /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/main.cpp

CMakeFiles/2_task.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2_task.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/main.cpp > CMakeFiles/2_task.dir/main.cpp.i

CMakeFiles/2_task.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2_task.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/main.cpp -o CMakeFiles/2_task.dir/main.cpp.s

CMakeFiles/2_task.dir/kmp_search.cpp.o: CMakeFiles/2_task.dir/flags.make
CMakeFiles/2_task.dir/kmp_search.cpp.o: ../kmp_search.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/2_task.dir/kmp_search.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/2_task.dir/kmp_search.cpp.o -c /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/kmp_search.cpp

CMakeFiles/2_task.dir/kmp_search.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2_task.dir/kmp_search.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/kmp_search.cpp > CMakeFiles/2_task.dir/kmp_search.cpp.i

CMakeFiles/2_task.dir/kmp_search.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2_task.dir/kmp_search.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/kmp_search.cpp -o CMakeFiles/2_task.dir/kmp_search.cpp.s

# Object files for target 2_task
2_task_OBJECTS = \
"CMakeFiles/2_task.dir/main.cpp.o" \
"CMakeFiles/2_task.dir/kmp_search.cpp.o"

# External object files for target 2_task
2_task_EXTERNAL_OBJECTS =

2_task: CMakeFiles/2_task.dir/main.cpp.o
2_task: CMakeFiles/2_task.dir/kmp_search.cpp.o
2_task: CMakeFiles/2_task.dir/build.make
2_task: CMakeFiles/2_task.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable 2_task"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2_task.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2_task.dir/build: 2_task

.PHONY : CMakeFiles/2_task.dir/build

CMakeFiles/2_task.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2_task.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2_task.dir/clean

CMakeFiles/2_task.dir/depend:
	cd /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/cmake-build-debug /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/cmake-build-debug /home/michael/Documents/Informatics/3_sem/Home_Tasks/2_task/cmake-build-debug/CMakeFiles/2_task.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2_task.dir/depend

