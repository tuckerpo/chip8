cmake_minimum_required (VERSION 3.0)

project (chip8)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_MODULE_PATH "CMakeModules")

set (SDL2_PATH "C:/SDL2-2.0.8")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

set(SOURCES chip8.cpp main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})