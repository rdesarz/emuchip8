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
#include "interpreter/instruction_interpreter.h"

using namespace chip8;

class TestInstructionInterpreterFixture : public ::testing::Test {
 protected:
  TestInstructionInterpreterFixture()
      : instruction_interpreter(&mock_ctrl_unit) {}

  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter;
};

TEST_F(TestInstructionInterpreterFixture, InterpretJumpInstruction) {
  instruction_interpreter.interpret(0x1001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 1);
}

TEST_F(TestInstructionInterpreterFixture, InterpretCallInstruction) {
  instruction_interpreter.interpret(0x2001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 2);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSkipNextInstructionIfEq) {
  instruction_interpreter.interpret(0x3001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 3);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSkipNextInstructionIfNotEq) {
  instruction_interpreter.interpret(0x4001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 4);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSkipNextInstructionIfRegEq) {
  instruction_interpreter.interpret(0x5001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 5);
}

TEST_F(TestInstructionInterpreterFixture, InterpretStoreInRegister) {
  instruction_interpreter.interpret(0x6001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 6);
}

TEST_F(TestInstructionInterpreterFixture, InterpretAddToRegister) {
  instruction_interpreter.interpret(0x7001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 7);
}

TEST_F(TestInstructionInterpreterFixture, InterpretStoreRegInReg) {
  instruction_interpreter.interpret(0x8000);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 8);
}

TEST_F(TestInstructionInterpreterFixture, InterpretBitwiseOr) {
  instruction_interpreter.interpret(0x8001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 9);
}
TEST_F(TestInstructionInterpreterFixture, InterpretBitwiseAnd) {
  instruction_interpreter.interpret(0x8002);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 10);
}

TEST_F(TestInstructionInterpreterFixture, InterpretBitwiseXor) {
  instruction_interpreter.interpret(0x8003);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 11);
}

TEST_F(TestInstructionInterpreterFixture, InterpretAddRegToReg) {
  instruction_interpreter.interpret(0x8004);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 12);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSubRegXToRegY) {
  instruction_interpreter.interpret(0x8005);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 13);
}

TEST_F(TestInstructionInterpreterFixture, InterpretShiftRight) {
  instruction_interpreter.interpret(0x8006);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 14);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSubRegYToRegX) {
  instruction_interpreter.interpret(0x8007);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 13);
}

TEST_F(TestInstructionInterpreterFixture, InterpretShiftLeft) {
  instruction_interpreter.interpret(0x800E);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 15);
}

TEST_F(TestInstructionInterpreterFixture,
       skipNextInstructionIfRegistersNotEqual) {
  instruction_interpreter.interpret(0x9000);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 16);
}

TEST_F(TestInstructionInterpreterFixture,
       InterpretStoreInMemoryAddressRegister) {
  instruction_interpreter.interpret(0xA001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 17);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSetPCToV0PlusValue) {
  instruction_interpreter.interpret(0xB001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 18);
}

TEST_F(TestInstructionInterpreterFixture, InterpretRandomInstruction) {
  instruction_interpreter.interpret(0xC001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 19);
}

TEST_F(TestInstructionInterpreterFixture, InterpretDisplayOnScreen) {
  instruction_interpreter.interpret(0xD001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 20);
}

TEST_F(TestInstructionInterpreterFixture, InterpretCheckIfKeyPressed) {
  instruction_interpreter.interpret(0xE19E);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 21);
}

TEST_F(TestInstructionInterpreterFixture, InterpretCheckIfKeyNotPressed) {
  instruction_interpreter.interpret(0xE1A1);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 22);
}

TEST_F(TestInstructionInterpreterFixture, InterpretWaitForKeyPressed) {
  instruction_interpreter.interpret(0xF10A);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 23);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSetDelayTimer) {
  instruction_interpreter.interpret(0xF115);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 24);
}

TEST_F(TestInstructionInterpreterFixture, InterpretSetSoundTimer) {
  instruction_interpreter.interpret(0xF118);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 25);
}

TEST_F(TestInstructionInterpreterFixture, InterpretAddToIndex) {
  instruction_interpreter.interpret(0xF11E);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 26);
}

TEST_F(TestInstructionInterpreterFixture, InterpretStoreSprite) {
  instruction_interpreter.interpret(0xF129);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 27);
}

TEST_F(TestInstructionInterpreterFixture, InterpretStoreBCD) {
  instruction_interpreter.interpret(0xF133);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 28);
}

TEST_F(TestInstructionInterpreterFixture, InterpretStoreMultipleReg) {
  instruction_interpreter.interpret(0xF155);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 29);
}

TEST_F(TestInstructionInterpreterFixture, InterpretReadMultipleReg) {
  instruction_interpreter.interpret(0xF165);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 30);
}
