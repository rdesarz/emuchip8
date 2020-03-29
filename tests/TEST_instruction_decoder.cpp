/**
 * Copyright (c) Romain Desarzens
 * All rights reserved.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "gtest/gtest.h"

#include "control_unit_fixture.h"
#include "interpreter/instruction_decoder.h"

using namespace chip8;

class TestInstructionInterpreterFixture : public ::testing::Test {
 protected:
  TestInstructionInterpreterFixture() : instruction_decoder(&mock_ctrl_unit) {}

  MockControlUnit mock_ctrl_unit;
  InstructionDecoder instruction_decoder;
};

TEST_F(TestInstructionInterpreterFixture, ClearDisplay) {
  instruction_decoder.decode(instruction_t(0x00E0));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, -1);
}

TEST_F(TestInstructionInterpreterFixture, ReturnFromSubroutine) {
  instruction_decoder.decode(instruction_t(0x00EE));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 0);
}

TEST_F(TestInstructionInterpreterFixture, InterpretJumpInstruction) {
  instruction_decoder.decode(instruction_t(0x1001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 1);
}

TEST_F(TestInstructionInterpreterFixture, InterpretCallInstruction) {
  instruction_decoder.decode(instruction_t(0x2001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 2);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSkipNextInstructionIfEq) {
  instruction_decoder.decode(instruction_t(0x3001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 3);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSkipNextInstructionIfNotEq) {
  instruction_decoder.decode(instruction_t(0x4001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 4);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSkipNextInstructionIfRegEq) {
  instruction_decoder.decode(instruction_t(0x5001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 5);
}

TEST_F(TestInstructionInterpreterFixture, InterpretStoreInRegister) {
  instruction_decoder.decode(instruction_t(0x6001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 6);
}

TEST_F(TestInstructionInterpreterFixture, InterpretAddToRegister) {
  instruction_decoder.decode(instruction_t(0x7001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 7);
}

TEST_F(TestInstructionInterpreterFixture, InterpretStoreRegInReg) {
  instruction_decoder.decode(instruction_t(0x8000));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 8);
}

TEST_F(TestInstructionInterpreterFixture, InterpretBitwiseOr) {
  instruction_decoder.decode(instruction_t(0x8001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 9);
}
TEST_F(TestInstructionInterpreterFixture, InterpretBitwiseAnd) {
  instruction_decoder.decode(instruction_t(0x8002));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 10);
}

TEST_F(TestInstructionInterpreterFixture, InterpretBitwiseXor) {
  instruction_decoder.decode(instruction_t(0x8003));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 11);
}

TEST_F(TestInstructionInterpreterFixture, InterpretAddRegToReg) {
  instruction_decoder.decode(instruction_t(0x8004));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 12);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSubRegXToRegY) {
  instruction_decoder.decode(instruction_t(0x8005));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 13);
}

TEST_F(TestInstructionInterpreterFixture, InterpretShiftRight) {
  instruction_decoder.decode(instruction_t(0x8006));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 14);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSubRegYToRegX) {
  instruction_decoder.decode(instruction_t(0x8007));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 32);
}

TEST_F(TestInstructionInterpreterFixture, InterpretShiftLeft) {
  instruction_decoder.decode(instruction_t(0x800E));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 15);
}

TEST_F(TestInstructionInterpreterFixture,
       skipNextInstructionIfRegistersNotEqual) {
  instruction_decoder.decode(instruction_t(0x9000));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 16);
}

TEST_F(TestInstructionInterpreterFixture,
       InterpretStoreInMemoryAddressRegister) {
  instruction_decoder.decode(instruction_t(0xA001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 17);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSetPCToV0PlusValue) {
  instruction_decoder.decode(instruction_t(0xB001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 18);
}

TEST_F(TestInstructionInterpreterFixture, InterpretRandomInstruction) {
  instruction_decoder.decode(instruction_t(0xC001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 19);
}

TEST_F(TestInstructionInterpreterFixture, InterpretDisplayOnScreen) {
  instruction_decoder.decode(instruction_t(0xD001));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 20);
}

TEST_F(TestInstructionInterpreterFixture, InterpretCheckIfKeyPressed) {
  instruction_decoder.decode(instruction_t(0xE19E));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 21);
}

TEST_F(TestInstructionInterpreterFixture, InterpretCheckIfKeyNotPressed) {
  instruction_decoder.decode(instruction_t(0xE1A1));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 22);
}

TEST_F(TestInstructionInterpreterFixture, InterpretWaitForKeyPressed) {
  instruction_decoder.decode(instruction_t(0xF10A));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 23);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSetDelayTimer) {
  instruction_decoder.decode(instruction_t(0xF115));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 24);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSetSoundTimer) {
  instruction_decoder.decode(instruction_t(0xF118));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 25);
}

TEST_F(TestInstructionInterpreterFixture, InterpretAddToIndex) {
  instruction_decoder.decode(instruction_t(0xF11E));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 26);
}

TEST_F(TestInstructionInterpreterFixture, InterpretStoreSprite) {
  instruction_decoder.decode(instruction_t(0xF129));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 27);
}

TEST_F(TestInstructionInterpreterFixture, InterpretStoreBCD) {
  instruction_decoder.decode(instruction_t(0xF133));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 28);
}

TEST_F(TestInstructionInterpreterFixture, InterpretStoreMultipleReg) {
  instruction_decoder.decode(instruction_t(0xF155));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 29);
}

TEST_F(TestInstructionInterpreterFixture, InterpretReadMultipleReg) {
  instruction_decoder.decode(instruction_t(0xF165));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 30);
}

TEST_F(TestInstructionInterpreterFixture, StoreDelayTimer) {
  instruction_decoder.decode(instruction_t(0xF107));

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 31);
}

TEST(getSubPartOfInstruction, getRegX) {
  instruction_t instruction{0x1811};

  auto result = getRegX(instruction);

  EXPECT_EQ(RegisterId(0x8), result);
}

TEST(getSubPartOfInstruction, getRegY) {
  instruction_t instruction{0x1181};

  auto result = getRegY(instruction);

  EXPECT_EQ(RegisterId(0x8), result);
}

TEST(getSubPartOfInstruction, getLastByte) {
  instruction_t instruction{0xFF89};

  auto result = getLastByte(instruction);

  EXPECT_EQ(result, 0x89);
}

TEST(getSubPartOfInstruction, getLastNibble) {
  instruction_t instruction{0xFF89};

  auto result = getLastNibble(instruction);

  EXPECT_EQ(result, 0x9);
}

TEST(getSubPartOfInstruction, getAddress) {
  instruction_t instruction{0xF189};

  auto result = getAddress(instruction);

  EXPECT_EQ(result, 0x189);
}