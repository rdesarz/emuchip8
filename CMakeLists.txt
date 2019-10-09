cmake_minimum_required(VERSION 3.7)

project(chip8_emulator)

set (CMAKE_CXX_STANDARD 17)

# Boost
find_package (Boost 1.58.0 REQUIRED COMPONENTS serialization)
if (Boost_FOUND)
  include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()

## GTest
find_package(GTest REQUIRED)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

## SDL
find_package (SDL2 REQUIRED)
include_directories (${SDL2_INCLUDE_DIRS})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)


include_directories("$(PROJECT_SOURCE_DIR)/modules/")
include_directories("$(PROJECT_SOURCE_DIR)/tests/")

## Libraries
add_library(memory modules/interpreter/memory.cpp)
target_link_libraries (memory ${Boost_LIBRARIES})

add_library(control_unit modules/interpreter/control_unit.cpp)
target_link_libraries (control_unit ${Boost_LIBRARIES})

add_library(user_input_impl modules/interpreter/user_input_impl.cpp)
target_link_libraries (user_input_impl ${Boost_LIBRARIES})

add_library(utilities modules/display/utilities.cpp)
target_link_libraries (utilities ${Boost_LIBRARIES})

add_library(pixel modules/display/pixel.cpp)
target_link_libraries (pixel utilities ${Boost_LIBRARIES})

add_library(display_model_impl modules/display/display_model_impl.cpp)
target_link_libraries (display_model_impl ${Boost_LIBRARIES})

add_library(display_view_impl modules/display/display_view_impl.cpp)
target_link_libraries (display_view_impl pixel ${Boost_LIBRARIES})

add_library(display_controller modules/display/display_controller.cpp)
target_link_libraries (display_controller ${Boost_LIBRARIES})

add_library(window modules/display/window.cpp)
target_link_libraries (window ${Boost_LIBRARIES})

## Executables
add_executable(main app/main.cpp)
target_link_libraries (main window display_model_impl display_view_impl display_controller user_input_impl ${SDL2_LIBRARIES})

## Unit tests
add_executable( memory_test tests/TEST_memory.cpp )
target_link_libraries( memory_test ${GTEST_BOTH_LIBRARIES} pthread memory display_controller)
add_test( NAME memory_test COMMAND memory_test)

add_executable( control_unit_test tests/TEST_control_unit.cpp )
target_link_libraries( control_unit_test control_unit ${GTEST_BOTH_LIBRARIES} user_input_impl pthread memory display_controller)
add_test( NAME control_unit COMMAND control_unit_test)

add_executable( display_test tests/TEST_display.cpp )
target_link_libraries( display_test ${GTEST_BOTH_LIBRARIES} pthread memory display_model_impl display_view_impl display_controller)
add_test( NAME display_test COMMAND display_test)
