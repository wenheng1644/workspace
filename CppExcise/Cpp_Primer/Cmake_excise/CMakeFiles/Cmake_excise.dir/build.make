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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise

# Include any dependencies generated for this target.
include CMakeFiles/Cmake_excise.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Cmake_excise.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Cmake_excise.dir/flags.make

CMakeFiles/Cmake_excise.dir/main.cpp.obj: CMakeFiles/Cmake_excise.dir/flags.make
CMakeFiles/Cmake_excise.dir/main.cpp.obj: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Cmake_excise.dir/main.cpp.obj"
	C:/Compiler/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Cmake_excise.dir/main.cpp.obj -c D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise/main.cpp

CMakeFiles/Cmake_excise.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cmake_excise.dir/main.cpp.i"
	C:/Compiler/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise/main.cpp > CMakeFiles/Cmake_excise.dir/main.cpp.i

CMakeFiles/Cmake_excise.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cmake_excise.dir/main.cpp.s"
	C:/Compiler/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise/main.cpp -o CMakeFiles/Cmake_excise.dir/main.cpp.s

# Object files for target Cmake_excise
Cmake_excise_OBJECTS = \
"CMakeFiles/Cmake_excise.dir/main.cpp.obj"

# External object files for target Cmake_excise
Cmake_excise_EXTERNAL_OBJECTS =

Cmake_excise.exe: CMakeFiles/Cmake_excise.dir/main.cpp.obj
Cmake_excise.exe: CMakeFiles/Cmake_excise.dir/build.make
Cmake_excise.exe: CMakeFiles/Cmake_excise.dir/linklibs.rsp
Cmake_excise.exe: CMakeFiles/Cmake_excise.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Cmake_excise.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/Cmake_excise.dir/objects.a
	C:/Compiler/mingw64/bin/ar.exe cr CMakeFiles/Cmake_excise.dir/objects.a @CMakeFiles/Cmake_excise.dir/objects1.rsp
	C:/Compiler/mingw64/bin/c++.exe -pthread -Wl,--whole-archive CMakeFiles/Cmake_excise.dir/objects.a -Wl,--no-whole-archive -o Cmake_excise.exe -Wl,--out-implib,libCmake_excise.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/Cmake_excise.dir/linklibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/Cmake_excise.dir/build: Cmake_excise.exe

.PHONY : CMakeFiles/Cmake_excise.dir/build

CMakeFiles/Cmake_excise.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Cmake_excise.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Cmake_excise.dir/clean

CMakeFiles/Cmake_excise.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise D:/MyGitHub/workspace/CppExcise/Cpp_Primer/Cmake_excise/CMakeFiles/Cmake_excise.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Cmake_excise.dir/depend

