#include "gtest/gtest.h"

#include "control_unit_fixture.h"
#include "interpreter/instruction_interpreter.h"

using namespace chip8;

TEST(TestInstructionInterpreter, InterpretJumpInstruction) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x1001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 1);
}

TEST(TestInstructionInterpreter, InterpretCallInstruction) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x2001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 2);
}

TEST(TestInstructionInterpreter, InterpretSkipNextInstructionIfEq) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x3001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 3);
}

TEST(TestInstructionInterpreter, InterpretSkipNextInstructionIfNotEq) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x4001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 4);
}

TEST(TestInstructionInterpreter, InterpretSkipNextInstructionIfRegEq) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x5001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 5);
}

TEST(TestInstructionInterpreter, InterpretStoreInRegister) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x6001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 6);
}

TEST(TestInstructionInterpreter, InterpretAddToRegister) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x7001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 7);
}

TEST(TestInstructionInterpreter, InterpretStoreRegInReg) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x8000);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 8);
}

TEST(TestInstructionInterpreter, InterpretBitwiseOr) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x8001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 9);
}
TEST(TestInstructionInterpreter, InterpretBitwiseAnd) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x8002);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 10);
}

TEST(TestInstructionInterpreter, InterpretBitwiseXor) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x8003);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 11);
}

TEST(TestInstructionInterpreter, InterpretAddRegToReg) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x8004);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 12);
}

TEST(TestInstructionInterpreter, InterpretSubRegXToRegY) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x8005);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 13);
}

TEST(TestInstructionInterpreter, InterpretShiftRight) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x8006);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 14);
}

TEST(TestInstructionInterpreter, InterpretSubRegYToRegX) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x8007);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 13);
}

TEST(TestInstructionInterpreter, InterpretShiftLeft) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x800E);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 15);
}

TEST(TestInstructionInterpreter, skipNextInstructionIfRegistersNotEqual) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0x9000);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 16);
}

TEST(TestInstructionInterpreter, InterpretStoreInMemoryAddressRegister) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0xA001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 17);
}

TEST(TestInstructionInterpreter, InterpretSetPCToV0PlusValue) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0xB001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 18);
}

TEST(TestInstructionInterpreter, InterpretRandomInstruction) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0xC001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 19);
}

TEST(TestInstructionInterpreter, InterpretDisplayOnScreen) {
  MockControlUnit mock_ctrl_unit;
  InstructionInterpreter instruction_interpreter(&mock_ctrl_unit);

  instruction_interpreter.interpret(0xD001);

  EXPECT_EQ(mock_ctrl_unit.id_called_function, 20);
}
