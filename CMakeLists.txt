cmake_minimum_required (VERSION 3.10)

set (This chip8)

project (${This})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if (WIN32)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

endif (WIN32)

find_package(SDL2 REQUIRED)

if (UNIX)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
endif (UNIX)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(include)

set(SOURCES 
	src/chip8.cpp
	src/main.cpp
)
add_executable(${This} ${SOURCES})

target_link_libraries(${This} ${SDL2_LIBRARIES})
