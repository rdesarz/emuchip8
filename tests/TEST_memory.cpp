#include "gtest/gtest.h"
#include "emulator/memory.h"

using namespace chip8::memory;

TEST(Memory, Initialization) {
    RAM memory;
 
    EXPECT_EQ(0, memory[8]);
}

TEST(Register, bitwiseOrOperator)
{
    Register<uint8_t> register_1{0b11001111};
    Register<uint8_t> register_2{0b00001111};

    auto result = register_1 | register_2;

    EXPECT_EQ(result.get(), 0b11001111);
}

TEST(Register, assignRegisterToRegister)
{
    Register<uint8_t> register_1{0x1};
    Register<uint8_t> register_2{0x2};

    register_1 = register_2;

    EXPECT_EQ(register_1.get(), 0x2);
}
