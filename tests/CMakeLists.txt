cmake_minimum_required (VERSION 3.0)

project (chip8tests)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set (CHIP8_DIR "~/chip8")

set (SOURCE_DIR ${CHIP8_DIR}/src)

set (TEST_DIR ${CHIP8_DIR}/tests)

include_directories(${CHIP8_DIR}/include)

set (SOURCES ${SOURCE_DIR}/chip8.cpp ${TEST_DIR}/validate_roms.cpp)

link_libraries(stdc++fs)

add_executable(${PROJECT_NAME} ${SOURCES})


