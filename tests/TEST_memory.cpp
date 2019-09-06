#include "gtest/gtest.h"
#include "interpreter/memory.h"

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

    EXPECT_EQ(result, 0b11001111);
}

TEST(Register, bitwiseAndOperator)
{
    Register<uint8_t> register_1{0b11001111};
    Register<uint8_t> register_2{0b00001111};

    auto result = register_1 & register_2;

    EXPECT_EQ(result, 0b00001111);
}

TEST(Register, bitwiseXorOperator)
{
    Register<uint8_t> register_1{0b11001111};
    Register<uint8_t> register_2{0b00001111};

    auto result = register_1 ^ register_2;

    EXPECT_EQ(result, 0b11000000);
}

TEST(Register, assignRegisterToRegister)
{
    Register<uint8_t> register_1{0x1};
    Register<uint8_t> register_2{0x2};

    register_1 = register_2;

    EXPECT_EQ(register_1, 0x2);
}

TEST(Register, additionBetweenRegister)
{
    Register<uint8_t> register_1{0x2};
    Register<uint8_t> register_2{0x2};

    register_1 = register_2 + register_1;

    EXPECT_EQ(register_1, 0x4);
    EXPECT_EQ(register_2, 0x2);
}
