# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build

# Include any dependencies generated for this target.
include CMakeFiles/mtkflasher.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mtkflasher.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mtkflasher.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mtkflasher.dir/flags.make

CMakeFiles/mtkflasher.dir/main.c.obj: CMakeFiles/mtkflasher.dir/flags.make
CMakeFiles/mtkflasher.dir/main.c.obj: D:/_Prj/Test_Code/MC60_Prog/MediaTekFlasher/main.c
CMakeFiles/mtkflasher.dir/main.c.obj: CMakeFiles/mtkflasher.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mtkflasher.dir/main.c.obj"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mtkflasher.dir/main.c.obj -MF CMakeFiles\mtkflasher.dir\main.c.obj.d -o CMakeFiles\mtkflasher.dir\main.c.obj -c D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\main.c

CMakeFiles/mtkflasher.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mtkflasher.dir/main.c.i"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\main.c > CMakeFiles\mtkflasher.dir\main.c.i

CMakeFiles/mtkflasher.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mtkflasher.dir/main.c.s"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\main.c -o CMakeFiles\mtkflasher.dir\main.c.s

# Object files for target mtkflasher
mtkflasher_OBJECTS = \
"CMakeFiles/mtkflasher.dir/main.c.obj"

# External object files for target mtkflasher
mtkflasher_EXTERNAL_OBJECTS =

mtkflasher.exe: CMakeFiles/mtkflasher.dir/main.c.obj
mtkflasher.exe: CMakeFiles/mtkflasher.dir/build.make
mtkflasher.exe: Flasher/libFLASHER.a
mtkflasher.exe: Flasher/libSERIAL.a
mtkflasher.exe: CMakeFiles/mtkflasher.dir/linklibs.rsp
mtkflasher.exe: CMakeFiles/mtkflasher.dir/objects1.rsp
mtkflasher.exe: CMakeFiles/mtkflasher.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable mtkflasher.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mtkflasher.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mtkflasher.dir/build: mtkflasher.exe
.PHONY : CMakeFiles/mtkflasher.dir/build

CMakeFiles/mtkflasher.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mtkflasher.dir\cmake_clean.cmake
.PHONY : CMakeFiles/mtkflasher.dir/clean

CMakeFiles/mtkflasher.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\CMakeFiles\mtkflasher.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mtkflasher.dir/depend

