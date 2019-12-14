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
