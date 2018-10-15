cmake_minimum_required (VERSION 3.0)

project (chip8romvalidation)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set (SOURCES ../chip8.cpp validate_roms.cpp)

link_libraries(stdc++fs)

add_executable(${PROJECT_NAME} ${SOURCES})


