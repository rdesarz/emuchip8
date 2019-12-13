cmake_minimum_required(VERSION 3.7)

project(chip8_emulator)

set (CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

include_directories("${PROJECT_SOURCE_DIR}/modules/")
include_directories("${PROJECT_SOURCE_DIR}/tests/")

## Libraries
add_library(memory modules/interpreter/memory.cpp)
target_link_libraries (memory CONAN_PKG::boost)

add_library(control_unit modules/interpreter/control_unit.cpp)
target_link_libraries (control_unit CONAN_PKG::boost)

add_library(user_input_impl modules/interpreter/user_input_impl.cpp)
target_link_libraries (user_input_impl CONAN_PKG::boost CONAN_PKG::sdl2)

add_library(utilities modules/display/utilities.cpp)
target_link_libraries (utilities CONAN_PKG::boost)

add_library(pixel modules/display/pixel.cpp)
target_link_libraries (pixel utilities CONAN_PKG::boost CONAN_PKG::sdl2)

add_library(display_model_impl modules/display/display_model_impl.cpp)
target_link_libraries (display_model_impl CONAN_PKG::boost)

add_library(display_view_impl modules/display/display_view_impl.cpp)
target_link_libraries (display_view_impl pixel CONAN_PKG::boost CONAN_PKG::sdl2)

add_library(display_controller modules/display/display_controller.cpp)
target_link_libraries (display_controller CONAN_PKG::boost)

add_library(window modules/display/window.cpp)
target_link_libraries (window CONAN_PKG::boost CONAN_PKG::sdl2)

add_library(clock modules/interpreter/clock.cpp)
target_link_libraries (clock CONAN_PKG::boost)

add_library(rom_loader modules/interpreter/rom_loader.cpp)
target_link_libraries (rom_loader CONAN_PKG::boost)

add_library(instruction_interpreter modules/interpreter/instruction_interpreter.cpp)
target_link_libraries (instruction_interpreter CONAN_PKG::boost)

## Executables
add_executable(main app/main.cpp)
target_link_libraries (main window display_model_impl display_view_impl display_controller user_input_impl CONAN_PKG::sdl2)

## Unit tests
add_executable( memory_test tests/TEST_memory.cpp )
target_link_libraries( memory_test CONAN_PKG::gtest pthread memory display_controller)
add_test( NAME memory_test COMMAND memory_test)

add_executable( control_unit_test tests/TEST_control_unit.cpp )
target_link_libraries( control_unit_test control_unit CONAN_PKG::gtest pthread user_input_impl memory display_controller)
add_test( NAME control_unit COMMAND control_unit_test)
 
add_executable( display_test tests/TEST_display.cpp )
target_link_libraries( display_test CONAN_PKG::gtest pthread memory display_model_impl display_view_impl display_controller)
add_test( NAME display_test COMMAND display_test)

add_executable( clock_test tests/TEST_clock.cpp )
target_link_libraries( clock_test CONAN_PKG::gtest pthread clock)
add_test( NAME clock_test COMMAND clock_test)

add_executable( rom_loader_test tests/TEST_rom_loader.cpp )
target_link_libraries( rom_loader_test CONAN_PKG::gtest pthread rom_loader)
add_test( NAME rom_loader_test COMMAND rom_loader_test)

add_executable( instruction_interpreter_test tests/TEST_instruction_interpreter.cpp )
target_link_libraries( instruction_interpreter_test CONAN_PKG::gtest pthread instruction_interpreter)
add_test( NAME instruction_interpreter_test COMMAND instruction_interpreter_test)
