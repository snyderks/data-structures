cmake_minimum_required(VERSION 3.6)
project(Lab05)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Stable.h Horse.cpp Horse.h Animal.cpp Animal.h)
add_executable(Lab05 ${SOURCE_FILES})