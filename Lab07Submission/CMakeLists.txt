cmake_minimum_required(VERSION 3.6)
project(Lab07)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp OrderedList.h OrderedListReverseSearch.h OrderedListOpenSpaces.h)
add_executable(Lab07 ${SOURCE_FILES})