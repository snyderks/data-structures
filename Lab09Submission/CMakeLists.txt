cmake_minimum_required(VERSION 3.6)
project(Lab09)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp HashTable.h Student.cpp Student.h ChainedHashTable.h)
add_executable(Lab09 ${SOURCE_FILES})