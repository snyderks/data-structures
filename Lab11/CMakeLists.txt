cmake_minimum_required(VERSION 3.6)
project(Lab11)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp DirectedGraph.cpp DirectedGraph.h Node.cpp Node.h)
add_executable(Lab11 ${SOURCE_FILES})