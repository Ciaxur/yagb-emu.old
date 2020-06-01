cmake_minimum_required(VERSION 3.15)
project(TestCases)
set(CMAKE_CXX_STANDARD 17)


# Add Test Cases
add_executable(
    Test1       1-CPU_Instructions.cc
)

# Configure Library
add_library(MyLib
    ../src/Cartridge.cpp    ../include/Cartridge.h
    ../src/Memory.cpp       ../include/Memory.h
    ../src/PPU.cpp          ../include/PPU.h
    ../src/CPU.cpp          ../include/CPU.h
)

# Link them
target_link_libraries(
    Test1
    MyLib
)