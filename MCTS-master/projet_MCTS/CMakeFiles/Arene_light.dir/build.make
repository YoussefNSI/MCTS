# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS"

# Include any dependencies generated for this target.
include CMakeFiles/Arene_light.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Arene_light.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Arene_light.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Arene_light.dir/flags.make

CMakeFiles/Arene_light.dir/MCTS.cpp.o: CMakeFiles/Arene_light.dir/flags.make
CMakeFiles/Arene_light.dir/MCTS.cpp.o: MCTS.cpp
CMakeFiles/Arene_light.dir/MCTS.cpp.o: CMakeFiles/Arene_light.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Arene_light.dir/MCTS.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Arene_light.dir/MCTS.cpp.o -MF CMakeFiles/Arene_light.dir/MCTS.cpp.o.d -o CMakeFiles/Arene_light.dir/MCTS.cpp.o -c "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/MCTS.cpp"

CMakeFiles/Arene_light.dir/MCTS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Arene_light.dir/MCTS.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/MCTS.cpp" > CMakeFiles/Arene_light.dir/MCTS.cpp.i

CMakeFiles/Arene_light.dir/MCTS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Arene_light.dir/MCTS.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/MCTS.cpp" -o CMakeFiles/Arene_light.dir/MCTS.cpp.s

CMakeFiles/Arene_light.dir/arbitre.cpp.o: CMakeFiles/Arene_light.dir/flags.make
CMakeFiles/Arene_light.dir/arbitre.cpp.o: arbitre.cpp
CMakeFiles/Arene_light.dir/arbitre.cpp.o: CMakeFiles/Arene_light.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Arene_light.dir/arbitre.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Arene_light.dir/arbitre.cpp.o -MF CMakeFiles/Arene_light.dir/arbitre.cpp.o.d -o CMakeFiles/Arene_light.dir/arbitre.cpp.o -c "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/arbitre.cpp"

CMakeFiles/Arene_light.dir/arbitre.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Arene_light.dir/arbitre.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/arbitre.cpp" > CMakeFiles/Arene_light.dir/arbitre.cpp.i

CMakeFiles/Arene_light.dir/arbitre.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Arene_light.dir/arbitre.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/arbitre.cpp" -o CMakeFiles/Arene_light.dir/arbitre.cpp.s

CMakeFiles/Arene_light.dir/main.cpp.o: CMakeFiles/Arene_light.dir/flags.make
CMakeFiles/Arene_light.dir/main.cpp.o: main.cpp
CMakeFiles/Arene_light.dir/main.cpp.o: CMakeFiles/Arene_light.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Arene_light.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Arene_light.dir/main.cpp.o -MF CMakeFiles/Arene_light.dir/main.cpp.o.d -o CMakeFiles/Arene_light.dir/main.cpp.o -c "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/main.cpp"

CMakeFiles/Arene_light.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Arene_light.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/main.cpp" > CMakeFiles/Arene_light.dir/main.cpp.i

CMakeFiles/Arene_light.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Arene_light.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/main.cpp" -o CMakeFiles/Arene_light.dir/main.cpp.s

# Object files for target Arene_light
Arene_light_OBJECTS = \
"CMakeFiles/Arene_light.dir/MCTS.cpp.o" \
"CMakeFiles/Arene_light.dir/arbitre.cpp.o" \
"CMakeFiles/Arene_light.dir/main.cpp.o"

# External object files for target Arene_light
Arene_light_EXTERNAL_OBJECTS = \
"/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/joueurs/joueur_MCTS.o" \
"/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/jeu.o"

Arene_light: CMakeFiles/Arene_light.dir/MCTS.cpp.o
Arene_light: CMakeFiles/Arene_light.dir/arbitre.cpp.o
Arene_light: CMakeFiles/Arene_light.dir/main.cpp.o
Arene_light: joueurs/joueur_MCTS.o
Arene_light: jeu.o
Arene_light: CMakeFiles/Arene_light.dir/build.make
Arene_light: joueurs/libjoueurs.a
Arene_light: CMakeFiles/Arene_light.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Arene_light"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Arene_light.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Arene_light.dir/build: Arene_light
.PHONY : CMakeFiles/Arene_light.dir/build

CMakeFiles/Arene_light.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Arene_light.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Arene_light.dir/clean

CMakeFiles/Arene_light.dir/depend:
	cd "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS" "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS" "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS" "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS" "/home/celian/Documents/Obsidian/Université/L3 INFORMATIQUE/Initiation à la programmation de systèmes intelligents/projet_MCTS/CMakeFiles/Arene_light.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Arene_light.dir/depend

