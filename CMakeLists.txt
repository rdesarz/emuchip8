cmake_minimum_required(VERSION 3.1)

project(chip8_emulator)

set (CMAKE_CXX_STANDARD 11)

## GTest
find_package(GTest REQUIRED)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


## Header
include_directories("$(PROJECT_SOURCE_DIR)/modules/")

## Libraries
add_library(disassembler modules/disassembler/disassembler.cpp)
add_library(instructions_set modules/disassembler/instructions_set.cpp)

## Executables
# add_executable(main app/main.cpp)

## Unit tests
add_executable( memory_test tests/TEST_memory.cpp )
target_link_libraries( memory_test ${GTEST_BOTH_LIBRARIES} pthread )
add_test( NAME memory_test COMMAND memory_test )
