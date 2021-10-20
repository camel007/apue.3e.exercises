cmake_minimum_required(VERSION 3.10.0)

project(chapter4)

file(GLOB src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach(src ${src_files})
	get_filename_component(exe ${src} NAME_WE)
	message(STATUS ${exe})
	add_executable(${exe} ${src})
endforeach()