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
include Flasher/CMakeFiles/SERIAL.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Flasher/CMakeFiles/SERIAL.dir/compiler_depend.make

# Include the progress variables for this target.
include Flasher/CMakeFiles/SERIAL.dir/progress.make

# Include the compile flags for this target's objects.
include Flasher/CMakeFiles/SERIAL.dir/flags.make

Flasher/CMakeFiles/SERIAL.dir/Serial.c.obj: Flasher/CMakeFiles/SERIAL.dir/flags.make
Flasher/CMakeFiles/SERIAL.dir/Serial.c.obj: D:/_Prj/Test_Code/MC60_Prog/MediaTekFlasher/Flasher/Serial.c
Flasher/CMakeFiles/SERIAL.dir/Serial.c.obj: Flasher/CMakeFiles/SERIAL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Flasher/CMakeFiles/SERIAL.dir/Serial.c.obj"
	cd /d D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\Flasher && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Flasher/CMakeFiles/SERIAL.dir/Serial.c.obj -MF CMakeFiles\SERIAL.dir\Serial.c.obj.d -o CMakeFiles\SERIAL.dir\Serial.c.obj -c D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\Flasher\Serial.c

Flasher/CMakeFiles/SERIAL.dir/Serial.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SERIAL.dir/Serial.c.i"
	cd /d D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\Flasher && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\Flasher\Serial.c > CMakeFiles\SERIAL.dir\Serial.c.i

Flasher/CMakeFiles/SERIAL.dir/Serial.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SERIAL.dir/Serial.c.s"
	cd /d D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\Flasher && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\Flasher\Serial.c -o CMakeFiles\SERIAL.dir\Serial.c.s

# Object files for target SERIAL
SERIAL_OBJECTS = \
"CMakeFiles/SERIAL.dir/Serial.c.obj"

# External object files for target SERIAL
SERIAL_EXTERNAL_OBJECTS =

Flasher/libSERIAL.a: Flasher/CMakeFiles/SERIAL.dir/Serial.c.obj
Flasher/libSERIAL.a: Flasher/CMakeFiles/SERIAL.dir/build.make
Flasher/libSERIAL.a: Flasher/CMakeFiles/SERIAL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libSERIAL.a"
	cd /d D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\Flasher && $(CMAKE_COMMAND) -P CMakeFiles\SERIAL.dir\cmake_clean_target.cmake
	cd /d D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\Flasher && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SERIAL.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Flasher/CMakeFiles/SERIAL.dir/build: Flasher/libSERIAL.a
.PHONY : Flasher/CMakeFiles/SERIAL.dir/build

Flasher/CMakeFiles/SERIAL.dir/clean:
	cd /d D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\Flasher && $(CMAKE_COMMAND) -P CMakeFiles\SERIAL.dir\cmake_clean.cmake
.PHONY : Flasher/CMakeFiles/SERIAL.dir/clean

Flasher/CMakeFiles/SERIAL.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\Flasher D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\Flasher D:\_Prj\Test_Code\MC60_Prog\MediaTekFlasher\build\Flasher\CMakeFiles\SERIAL.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Flasher/CMakeFiles/SERIAL.dir/depend

