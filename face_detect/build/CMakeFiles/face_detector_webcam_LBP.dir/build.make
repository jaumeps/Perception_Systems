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
CMAKE_SOURCE_DIR = /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect/build

# Include any dependencies generated for this target.
include CMakeFiles/face_detector_webcam_LBP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/face_detector_webcam_LBP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/face_detector_webcam_LBP.dir/flags.make

CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o: CMakeFiles/face_detector_webcam_LBP.dir/flags.make
CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o: ../src/face_detector_webcam_LBP.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o -c /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect/src/face_detector_webcam_LBP.cpp

CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect/src/face_detector_webcam_LBP.cpp > CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.i

CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect/src/face_detector_webcam_LBP.cpp -o CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.s

CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o.requires:

.PHONY : CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o.requires

CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o.provides: CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o.requires
	$(MAKE) -f CMakeFiles/face_detector_webcam_LBP.dir/build.make CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o.provides.build
.PHONY : CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o.provides

CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o.provides.build: CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o


# Object files for target face_detector_webcam_LBP
face_detector_webcam_LBP_OBJECTS = \
"CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o"

# External object files for target face_detector_webcam_LBP
face_detector_webcam_LBP_EXTERNAL_OBJECTS =

face_detector_webcam_LBP: CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o
face_detector_webcam_LBP: CMakeFiles/face_detector_webcam_LBP.dir/build.make
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_face.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_text.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_video.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
face_detector_webcam_LBP: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
face_detector_webcam_LBP: CMakeFiles/face_detector_webcam_LBP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable face_detector_webcam_LBP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/face_detector_webcam_LBP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/face_detector_webcam_LBP.dir/build: face_detector_webcam_LBP

.PHONY : CMakeFiles/face_detector_webcam_LBP.dir/build

CMakeFiles/face_detector_webcam_LBP.dir/requires: CMakeFiles/face_detector_webcam_LBP.dir/src/face_detector_webcam_LBP.cpp.o.requires

.PHONY : CMakeFiles/face_detector_webcam_LBP.dir/requires

CMakeFiles/face_detector_webcam_LBP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/face_detector_webcam_LBP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/face_detector_webcam_LBP.dir/clean

CMakeFiles/face_detector_webcam_LBP.dir/depend:
	cd /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect/build /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect/build /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/face_detect/build/CMakeFiles/face_detector_webcam_LBP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/face_detector_webcam_LBP.dir/depend

