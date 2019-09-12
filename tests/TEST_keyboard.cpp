#include "gtest/gtest.h"
#include "interpreter/keyboard.h"

using namespace chip8::inputs;

TEST(KeyboardInput, updateWithNewFKey) {
    Keyboard keyboard;
    std::array<KeyState, 16> input{KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::UP,
                                   KeyState::DOWN};
      
    keyboard.update(input);
 
    EXPECT_EQ(KeyState::UP, keyboard.getKeyState(KeyId::ZERO));
    EXPECT_EQ(KeyState::DOWN, keyboard.getKeyState(KeyId::F));
}

