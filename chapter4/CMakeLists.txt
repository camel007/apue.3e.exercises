cmake_minimum_required(VERSION 3.10.0)

project(chapter4)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

file(GLOB src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach(src ${src_files})
	get_filename_component(exe ${src} NAME_WE)
	add_executable(${exe} ${src})
	target_link_libraries(${exe} libapue.a)
endforeach()