cmake_minimum_required(VERSION 3.1)

project(chip8_emulator)

set (CMAKE_CXX_STANDARD 11)

find_package (Boost 1.58.0 REQUIRED COMPONENTS serialization)
if (Boost_FOUND)
  include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()

## GTest
find_package(GTest REQUIRED)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories("$(PROJECT_SOURCE_DIR)/modules/")

## Libraries
add_library(memory modules/emulator/memory.cpp)
target_link_libraries (memory ${Boost_LIBRARIES})
add_library(interpreter modules/emulator/interpreter.cpp)
target_link_libraries (memory ${Boost_LIBRARIES})
add_library(display modules/emulator/display.cpp)
target_link_libraries (display ${Boost_LIBRARIES})


## Executables
# add_executable(main app/main.cpp)

## Unit tests
add_executable( memory_test tests/TEST_memory.cpp )
target_link_libraries( memory_test ${GTEST_BOTH_LIBRARIES} pthread memory display)
add_test( NAME memory_test COMMAND memory_test)

add_executable( interpreter_test tests/TEST_interpreter.cpp )
target_link_libraries( interpreter_test interpreter ${GTEST_BOTH_LIBRARIES} pthread memory display)
add_test( NAME interpreter_test COMMAND interpreter_test)

add_executable( display_test tests/TEST_display.cpp )
target_link_libraries( display_test ${GTEST_BOTH_LIBRARIES} pthread memory display)
add_test( NAME display_test COMMAND display_test)
