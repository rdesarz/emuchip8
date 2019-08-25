cmake_minimum_required(VERSION 3.1)

project(chip8_emulator)

set (CMAKE_CXX_STANDARD 11)

## GTest
find_package(GTest REQUIRED)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories("$(PROJECT_SOURCE_DIR)/modules/")

## Libraries
add_library(memory modules/emulator/memory.cpp)
add_library(interpreter modules/emulator/interpreter.cpp)

## Executables
# add_executable(main app/main.cpp)

## Unit tests
add_executable( memory_test tests/TEST_memory.cpp )
target_link_libraries( memory_test ${GTEST_BOTH_LIBRARIES} pthread memory)
add_test( NAME memory_test COMMAND memory_test)

add_executable( interpreter_test tests/TEST_interpreter.cpp )
target_link_libraries( interpreter_test interpreter ${GTEST_BOTH_LIBRARIES} pthread )
add_test( NAME interpreter_test COMMAND interpreter_test)
