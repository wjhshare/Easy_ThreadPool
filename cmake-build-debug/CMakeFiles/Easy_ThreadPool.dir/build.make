# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Clion2019\CLion 2019.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Clion2019\CLion 2019.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\WorkProject\Easy_ThreadPool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\WorkProject\Easy_ThreadPool\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Easy_ThreadPool.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Easy_ThreadPool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Easy_ThreadPool.dir/flags.make

CMakeFiles/Easy_ThreadPool.dir/main.cpp.obj: CMakeFiles/Easy_ThreadPool.dir/flags.make
CMakeFiles/Easy_ThreadPool.dir/main.cpp.obj: CMakeFiles/Easy_ThreadPool.dir/includes_CXX.rsp
CMakeFiles/Easy_ThreadPool.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\WorkProject\Easy_ThreadPool\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Easy_ThreadPool.dir/main.cpp.obj"
	D:\MinGW64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Easy_ThreadPool.dir\main.cpp.obj -c D:\WorkProject\Easy_ThreadPool\main.cpp

CMakeFiles/Easy_ThreadPool.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Easy_ThreadPool.dir/main.cpp.i"
	D:\MinGW64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\WorkProject\Easy_ThreadPool\main.cpp > CMakeFiles\Easy_ThreadPool.dir\main.cpp.i

CMakeFiles/Easy_ThreadPool.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Easy_ThreadPool.dir/main.cpp.s"
	D:\MinGW64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\WorkProject\Easy_ThreadPool\main.cpp -o CMakeFiles\Easy_ThreadPool.dir\main.cpp.s

CMakeFiles/Easy_ThreadPool.dir/ThreadPool.cpp.obj: CMakeFiles/Easy_ThreadPool.dir/flags.make
CMakeFiles/Easy_ThreadPool.dir/ThreadPool.cpp.obj: CMakeFiles/Easy_ThreadPool.dir/includes_CXX.rsp
CMakeFiles/Easy_ThreadPool.dir/ThreadPool.cpp.obj: ../ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\WorkProject\Easy_ThreadPool\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Easy_ThreadPool.dir/ThreadPool.cpp.obj"
	D:\MinGW64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Easy_ThreadPool.dir\ThreadPool.cpp.obj -c D:\WorkProject\Easy_ThreadPool\ThreadPool.cpp

CMakeFiles/Easy_ThreadPool.dir/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Easy_ThreadPool.dir/ThreadPool.cpp.i"
	D:\MinGW64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\WorkProject\Easy_ThreadPool\ThreadPool.cpp > CMakeFiles\Easy_ThreadPool.dir\ThreadPool.cpp.i

CMakeFiles/Easy_ThreadPool.dir/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Easy_ThreadPool.dir/ThreadPool.cpp.s"
	D:\MinGW64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\WorkProject\Easy_ThreadPool\ThreadPool.cpp -o CMakeFiles\Easy_ThreadPool.dir\ThreadPool.cpp.s

# Object files for target Easy_ThreadPool
Easy_ThreadPool_OBJECTS = \
"CMakeFiles/Easy_ThreadPool.dir/main.cpp.obj" \
"CMakeFiles/Easy_ThreadPool.dir/ThreadPool.cpp.obj"

# External object files for target Easy_ThreadPool
Easy_ThreadPool_EXTERNAL_OBJECTS =

Easy_ThreadPool.exe: CMakeFiles/Easy_ThreadPool.dir/main.cpp.obj
Easy_ThreadPool.exe: CMakeFiles/Easy_ThreadPool.dir/ThreadPool.cpp.obj
Easy_ThreadPool.exe: CMakeFiles/Easy_ThreadPool.dir/build.make
Easy_ThreadPool.exe: CMakeFiles/Easy_ThreadPool.dir/linklibs.rsp
Easy_ThreadPool.exe: CMakeFiles/Easy_ThreadPool.dir/objects1.rsp
Easy_ThreadPool.exe: CMakeFiles/Easy_ThreadPool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\WorkProject\Easy_ThreadPool\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Easy_ThreadPool.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Easy_ThreadPool.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Easy_ThreadPool.dir/build: Easy_ThreadPool.exe

.PHONY : CMakeFiles/Easy_ThreadPool.dir/build

CMakeFiles/Easy_ThreadPool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Easy_ThreadPool.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Easy_ThreadPool.dir/clean

CMakeFiles/Easy_ThreadPool.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\WorkProject\Easy_ThreadPool D:\WorkProject\Easy_ThreadPool D:\WorkProject\Easy_ThreadPool\cmake-build-debug D:\WorkProject\Easy_ThreadPool\cmake-build-debug D:\WorkProject\Easy_ThreadPool\cmake-build-debug\CMakeFiles\Easy_ThreadPool.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Easy_ThreadPool.dir/depend

