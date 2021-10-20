cmake_minimum_required(VERSION 3.10.0)
project(apue.3e.exercies)

option(BUILD_ALL "build all exercises" ON)

if(${BUILD_ALL})
    add_subdirectory(chapter4) 
endif()