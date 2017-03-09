cmake_minimum_required(VERSION 3.6)
project(Lab_01)

set(CMAKE_CXX_STANDARD 11)

set(BUILD task1)
set(SOURCE_FILES task1.cpp)
add_executable(${BUILD} ${SOURCE_FILES})

set(BUILD task2)
set(SOURCE_FILES task2.cpp)
add_executable(${BUILD} ${SOURCE_FILES})

set(BUILD task3)
set(SOURCE_FILES task3.cpp)
add_executable(${BUILD} ${SOURCE_FILES})