cmake_minimum_required(VERSION 3.15)
project(yagb_emu)

set(CMAKE_CXX_STANDARD 17)

# Setup Compiler Flags
set(CMAKE_CXX_FLAGS "-Wall")


# Find SDL2 and OpenGL
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
find_package(SDL2 REQUIRED COMPONENTS main)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2main_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${CMAKE_BINARY_DIR})
add_executable(yagb_emu src/main.cpp)
target_link_libraries(yagb_emu ${SDL2_LIBS} ${OPENGL_LIBRARIES})
