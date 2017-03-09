cmake_minimum_required(VERSION 3.6)
project(Lab04)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Animal.cpp Animal.h Fish.cpp Fish.h Horse.cpp Horse.h)
add_executable(Lab04 ${SOURCE_FILES})