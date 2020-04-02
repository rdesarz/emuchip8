cmake_minimum_required(VERSION 3.12)

project(emuchip8)

if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.15/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE
        conanfile.txt
        BASIC_SETUP CMAKE_TARGETS)

include(GoogleTest)
include(CTest)

## Libraries
add_library(lib_emulator
        modules/interpreter/emulator.cpp
        modules/interpreter/control_unit_impl.cpp
        modules/interpreter/memory.cpp
        modules/interpreter/clock.cpp
        modules/interpreter/rom_loader.cpp
        modules/interpreter/instruction_decoder.cpp
        modules/display/display_controller.cpp)
target_include_directories(lib_emulator PUBLIC ${PROJECT_SOURCE_DIR}/modules/)
target_link_libraries(lib_emulator PRIVATE CONAN_PKG::boost)
target_compile_features(lib_emulator PRIVATE cxx_std_17)

add_library(lib_display
        modules/display/display_model_impl.cpp
        modules/display/utilities.cpp
        modules/display/pixel.cpp
        modules/display/display_view_impl.cpp
        modules/display/window.cpp)
target_include_directories(lib_display PRIVATE ${PROJECT_SOURCE_DIR}/modules/)
target_link_libraries(lib_display PUBLIC CONAN_PKG::sdl2 PRIVATE CONAN_PKG::boost)
target_compile_features(lib_display PRIVATE cxx_std_17)

add_library(user_input_impl modules/interpreter/user_input_impl.cpp)
target_include_directories(user_input_impl PRIVATE ${PROJECT_SOURCE_DIR}/modules/)
target_link_libraries(user_input_impl PUBLIC CONAN_PKG::sdl2 PRIVATE CONAN_PKG::boost)
target_compile_features(user_input_impl PUBLIC cxx_std_17)

## Executables
add_executable(emuchip8 app/main.cpp)
target_link_libraries(emuchip8 lib_display user_input_impl lib_emulator CONAN_PKG::sdl2)
target_include_directories(emuchip8 PRIVATE ${PROJECT_SOURCE_DIR}/modules/)

## Unit tests
add_executable(test_lib_emulator
        tests/TEST_memory.cpp
        tests/TEST_control_unit.cpp
        tests/TEST_display.cpp
        tests/TEST_clock.cpp
        tests/TEST_rom_loader.cpp
        tests/TEST_instruction_decoder.cpp)
target_link_libraries(test_lib_emulator CONAN_PKG::gtest pthread lib_emulator user_input_impl)
target_compile_features(test_lib_emulator PUBLIC cxx_std_17)
add_test(NAME test_lib_emulator COMMAND test_lib_emulator)
gtest_discover_tests(test_lib_emulator)
