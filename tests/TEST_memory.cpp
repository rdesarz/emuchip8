/** 
 * Copyright (c) Romain Desarzens
 * All rights reserved. 
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "gtest/gtest.h"
#include "emulator/memory.h"

using namespace chip8;

TEST(Memory, Initialization) {
  RAM memory;

  EXPECT_EQ(0, memory[8]);
}

TEST(Register, bitwiseOrOperator) {
  Register<uint8_t> register_1{0b11001111};
  Register<uint8_t> register_2{0b00001111};

  auto result = register_1 | register_2;

  EXPECT_EQ(result, 0b11001111);
}

TEST(Register, bitwiseAndOperator) {
  Register<uint8_t> register_1{0b11001111};
  Register<uint8_t> register_2{0b00001111};

  auto result = register_1 & register_2;

  EXPECT_EQ(result, 0b00001111);
}

TEST(Register, bitwiseXorOperator) {
  Register<uint8_t> register_1{0b11001111};
  Register<uint8_t> register_2{0b00001111};

  auto result = register_1 ^ register_2;

  EXPECT_EQ(result, 0b11000000);
}

TEST(Register, assignRegisterToRegister) {
  Register<uint8_t> register_1{0x1};
  Register<uint8_t> register_2{0x2};

  register_1 = register_2;

  EXPECT_EQ(register_1, 0x2);
}

TEST(Register, additionBetweenRegister) {
  Register<uint8_t> register_1{0x2};
  Register<uint8_t> register_2{0x2};

  register_1 = register_2 + register_1;

  EXPECT_EQ(register_1, 0x4);
  EXPECT_EQ(register_2, 0x2);
}
