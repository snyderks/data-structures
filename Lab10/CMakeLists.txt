cmake_minimum_required(VERSION 3.6)
project(Lab10)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BTree.h Node.h)
add_executable(Lab10 ${SOURCE_FILES})