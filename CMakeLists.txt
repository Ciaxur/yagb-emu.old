cmake_minimum_required(VERSION 3.15)
project(yagb_emu)

set(CMAKE_CXX_STANDARD 17)

# Setup Compiler Flags
set(CMAKE_CXX_FLAGS "-Wall")


# Find SDL2 OpenGL BOOST
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
find_package(SDL2 REQUIRED COMPONENTS main)
find_package(Boost REQUIRED COMPONENTS program_options REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS} ${SDL2main_INCLUDE_DIRS} 
    ${OPENGL_INCLUDE_DIR} 
    ${CMAKE_BINARY_DIR}
    ${Boost_INCLUDE_DIR})
add_executable(
    yagb_emu 
    src/main.cpp 
    src/Cartridge.cpp include/Cartridge.h
    src/Memory.cpp include/Memory.h
    src/PPU.cpp include/PPU.h
    src/CPU.cpp include/CPU.h)
target_link_libraries(yagb_emu 
    ${SDL2_LIBS} 
    ${OPENGL_LIBRARIES}
    ${Boost_LIBRARIES})
