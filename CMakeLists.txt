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

# Required modules
include(GoogleTest)
include(CTest)

## Libraries
add_library(emulator
        modules/emulator/src/emulator.cpp
        modules/emulator/src/control_unit_impl.cpp
        modules/emulator/src/memory.cpp
        modules/emulator/src/clock.cpp
        modules/emulator/src/rom_loader.cpp
        modules/emulator/src/instruction_decoder.cpp
        modules/emulator/src/display_controller.cpp)
target_include_directories(emulator PUBLIC ${PROJECT_SOURCE_DIR}/modules/emulator/include)
target_link_libraries(emulator PUBLIC CONAN_PKG::boost)
target_compile_features(emulator PRIVATE cxx_std_17)

add_library(display_ui
        modules/display_ui/src/display_model_impl.cpp
        modules/display_ui/src/utilities.cpp
        modules/display_ui/src/pixel.cpp
        modules/display_ui/src/display_view_impl.cpp
        modules/display_ui/src/window.cpp
        modules/display_ui/src/user_input_impl.cpp)
target_include_directories(display_ui PUBLIC ${PROJECT_SOURCE_DIR}/modules/display_ui/include)
target_link_libraries(display_ui PUBLIC CONAN_PKG::sdl2 CONAN_PKG::boost emulator)
target_compile_features(display_ui PUBLIC cxx_std_17)


## Executables
add_executable(emuchip8 app/main.cpp)
target_link_libraries(emuchip8 display_ui emulator)


## Tests
add_executable(test_emulator
        tests/TEST_memory.cpp
        tests/TEST_control_unit.cpp
        tests/TEST_display.cpp
        tests/TEST_clock.cpp
        tests/TEST_rom_loader.cpp
        tests/TEST_instruction_decoder.cpp)
target_link_libraries(test_emulator CONAN_PKG::gtest pthread emulator)
target_compile_features(test_emulator PRIVATE cxx_std_17)
add_test(NAME test_emulator COMMAND test_emulator)
gtest_discover_tests(test_emulator)