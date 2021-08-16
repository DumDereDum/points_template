cmake_minimum_required(VERSION 2.8)

project(hello_world)
set(SOURCE_EXE src/Colors.cpp
	src/pointed_voxel.h
	src/templete_colored_voxel.h
	src/templete_uncolored_voxel.h)
add_executable(main ${SOURCE_EXE})
