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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/han/cs184-final-project/build/partio-download

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/han/cs184-final-project/build/partio-download

# Utility rule file for partio-download.

# Include the progress variables for this target.
include CMakeFiles/partio-download.dir/progress.make

CMakeFiles/partio-download: CMakeFiles/partio-download-complete


CMakeFiles/partio-download-complete: partio-download-prefix/src/partio-download-stamp/partio-download-install
CMakeFiles/partio-download-complete: partio-download-prefix/src/partio-download-stamp/partio-download-mkdir
CMakeFiles/partio-download-complete: partio-download-prefix/src/partio-download-stamp/partio-download-download
CMakeFiles/partio-download-complete: partio-download-prefix/src/partio-download-stamp/partio-download-patch
CMakeFiles/partio-download-complete: partio-download-prefix/src/partio-download-stamp/partio-download-configure
CMakeFiles/partio-download-complete: partio-download-prefix/src/partio-download-stamp/partio-download-build
CMakeFiles/partio-download-complete: partio-download-prefix/src/partio-download-stamp/partio-download-install
CMakeFiles/partio-download-complete: partio-download-prefix/src/partio-download-stamp/partio-download-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/han/cs184-final-project/build/partio-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'partio-download'"
	/usr/local/Cellar/cmake/3.19.2/bin/cmake -E make_directory /Users/han/cs184-final-project/build/partio-download/CMakeFiles
	/usr/local/Cellar/cmake/3.19.2/bin/cmake -E touch /Users/han/cs184-final-project/build/partio-download/CMakeFiles/partio-download-complete
	/usr/local/Cellar/cmake/3.19.2/bin/cmake -E touch /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/src/partio-download-stamp/partio-download-done

partio-download-prefix/src/partio-download-stamp/partio-download-install: partio-download-prefix/src/partio-download-stamp/partio-download-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/han/cs184-final-project/build/partio-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No install step for 'partio-download'"
	cd /Users/han/cs184-final-project/build/partio-build && /usr/local/Cellar/cmake/3.19.2/bin/cmake -E echo_append
	cd /Users/han/cs184-final-project/build/partio-build && /usr/local/Cellar/cmake/3.19.2/bin/cmake -E touch /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/src/partio-download-stamp/partio-download-install

partio-download-prefix/src/partio-download-stamp/partio-download-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/han/cs184-final-project/build/partio-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'partio-download'"
	/usr/local/Cellar/cmake/3.19.2/bin/cmake -E make_directory /Users/han/cs184-final-project/build/partio-src
	/usr/local/Cellar/cmake/3.19.2/bin/cmake -E make_directory /Users/han/cs184-final-project/build/partio-build
	/usr/local/Cellar/cmake/3.19.2/bin/cmake -E make_directory /Users/han/cs184-final-project/build/partio-download/partio-download-prefix
	/usr/local/Cellar/cmake/3.19.2/bin/cmake -E make_directory /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/tmp
	/usr/local/Cellar/cmake/3.19.2/bin/cmake -E make_directory /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/src/partio-download-stamp
	/usr/local/Cellar/cmake/3.19.2/bin/cmake -E make_directory /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/src
	/usr/local/Cellar/cmake/3.19.2/bin/cmake -E make_directory /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/src/partio-download-stamp
	/usr/local/Cellar/cmake/3.19.2/bin/cmake -E touch /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/src/partio-download-stamp/partio-download-mkdir

partio-download-prefix/src/partio-download-stamp/partio-download-download: partio-download-prefix/src/partio-download-stamp/partio-download-gitinfo.txt
partio-download-prefix/src/partio-download-stamp/partio-download-download: partio-download-prefix/src/partio-download-stamp/partio-download-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/han/cs184-final-project/build/partio-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'partio-download'"
	cd /Users/han/cs184-final-project/build && /usr/local/Cellar/cmake/3.19.2/bin/cmake -P /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/tmp/partio-download-gitclone.cmake
	cd /Users/han/cs184-final-project/build && /usr/local/Cellar/cmake/3.19.2/bin/cmake -E touch /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/src/partio-download-stamp/partio-download-download

partio-download-prefix/src/partio-download-stamp/partio-download-patch: partio-download-prefix/src/partio-download-stamp/partio-download-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/han/cs184-final-project/build/partio-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Performing patch step for 'partio-download'"
	cd /Users/han/cs184-final-project/build/partio-src && /usr/local/bin/git apply /Users/han/cs184-final-project/Deps/partio.patch
	cd /Users/han/cs184-final-project/build/partio-src && /usr/local/Cellar/cmake/3.19.2/bin/cmake -E touch /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/src/partio-download-stamp/partio-download-patch

partio-download-prefix/src/partio-download-stamp/partio-download-configure: partio-download-prefix/tmp/partio-download-cfgcmd.txt
partio-download-prefix/src/partio-download-stamp/partio-download-configure: partio-download-prefix/src/partio-download-stamp/partio-download-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/han/cs184-final-project/build/partio-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No configure step for 'partio-download'"
	cd /Users/han/cs184-final-project/build/partio-build && /usr/local/Cellar/cmake/3.19.2/bin/cmake -E echo_append
	cd /Users/han/cs184-final-project/build/partio-build && /usr/local/Cellar/cmake/3.19.2/bin/cmake -E touch /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/src/partio-download-stamp/partio-download-configure

partio-download-prefix/src/partio-download-stamp/partio-download-build: partio-download-prefix/src/partio-download-stamp/partio-download-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/han/cs184-final-project/build/partio-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No build step for 'partio-download'"
	cd /Users/han/cs184-final-project/build/partio-build && /usr/local/Cellar/cmake/3.19.2/bin/cmake -E echo_append
	cd /Users/han/cs184-final-project/build/partio-build && /usr/local/Cellar/cmake/3.19.2/bin/cmake -E touch /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/src/partio-download-stamp/partio-download-build

partio-download-prefix/src/partio-download-stamp/partio-download-test: partio-download-prefix/src/partio-download-stamp/partio-download-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/han/cs184-final-project/build/partio-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'partio-download'"
	cd /Users/han/cs184-final-project/build/partio-build && /usr/local/Cellar/cmake/3.19.2/bin/cmake -E echo_append
	cd /Users/han/cs184-final-project/build/partio-build && /usr/local/Cellar/cmake/3.19.2/bin/cmake -E touch /Users/han/cs184-final-project/build/partio-download/partio-download-prefix/src/partio-download-stamp/partio-download-test

partio-download: CMakeFiles/partio-download
partio-download: CMakeFiles/partio-download-complete
partio-download: partio-download-prefix/src/partio-download-stamp/partio-download-build
partio-download: partio-download-prefix/src/partio-download-stamp/partio-download-configure
partio-download: partio-download-prefix/src/partio-download-stamp/partio-download-download
partio-download: partio-download-prefix/src/partio-download-stamp/partio-download-install
partio-download: partio-download-prefix/src/partio-download-stamp/partio-download-mkdir
partio-download: partio-download-prefix/src/partio-download-stamp/partio-download-patch
partio-download: partio-download-prefix/src/partio-download-stamp/partio-download-test
partio-download: CMakeFiles/partio-download.dir/build.make

.PHONY : partio-download

# Rule to build all files generated by this target.
CMakeFiles/partio-download.dir/build: partio-download

.PHONY : CMakeFiles/partio-download.dir/build

CMakeFiles/partio-download.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/partio-download.dir/cmake_clean.cmake
.PHONY : CMakeFiles/partio-download.dir/clean

CMakeFiles/partio-download.dir/depend:
	cd /Users/han/cs184-final-project/build/partio-download && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/han/cs184-final-project/build/partio-download /Users/han/cs184-final-project/build/partio-download /Users/han/cs184-final-project/build/partio-download /Users/han/cs184-final-project/build/partio-download /Users/han/cs184-final-project/build/partio-download/CMakeFiles/partio-download.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/partio-download.dir/depend

