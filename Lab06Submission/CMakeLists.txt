cmake_minimum_required(VERSION 3.6)
project(Lab06)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES mainSinglePlayer.cpp Stack.h)
add_executable(SinglePlayer ${SOURCE_FILES})

SET(SOURCE_FILES mainTwoPlayer.cpp Stack.h Disk.cpp Disk.h)
add_executable(TwoPlayer ${SOURCE_FILES})

SET(SOURCE_FILES mainSinglePlayerWithTrackedSteps.cpp Stack.h Queue.h)
add_executable(SinglePlayerWithTrackedSteps ${SOURCE_FILES})