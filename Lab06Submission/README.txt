If you have CMake, run it on this directory:

cmake .

Then build the projects with the generated makefile. The build names are below.
Task 2: SinglePlayer
Task 3: TwoPlayer
Task 4: SinglePlayerWithTrackedSteps

Or compile each project with g++:

Task 2:
g++ mainSinglePlayer.cpp Stack.h

Task 3:
g++ mainTwoPlayer.cpp Stack.h Disk.cpp Disk.h

Task 4:
g++ mainSinglePlayerWithTrackedSteps.cpp Stack.h Queue.h
