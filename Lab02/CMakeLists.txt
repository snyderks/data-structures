cmake_minimum_required(VERSION 3.6)
project(Lab02)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES task1/task1.cpp)
set(BUILD task1)
add_executable(${BUILD} ${SOURCE_FILES})

set(SOURCE_FILES task2/task2.cpp)
set(BUILD task2)
add_executable(${BUILD} ${SOURCE_FILES})

set(SOURCE_FILES task3/task3.cpp task3/Product.cpp task3/Product.h)
set(BUILD task3)
add_executable(${BUILD} ${SOURCE_FILES})