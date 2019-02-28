cmake_minimum_required (VERSION 3.0)

project (chip8)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

if (WIN32)

set(CMAKE_MODULE_PATH "CMakeModules")

endif (WIN32)

find_package(SDL2 REQUIRED)

# Manually pointing to a package kinda ruins the whole point of cmake, no? Oh well.
if (UNIX)
#set (SDL2_INCLUDE_DIR usr/include/SDL2)
#set(SDL2_LIBRARY usr/lib/libSDL2.so)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
endif (UNIX)

#include_directories(${SDL2_INCLUDE_DIR})
include_directories(include)

set(SOURCES 
	src/chip8.cpp 
	src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

if (UNIX)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif (UNIX)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
