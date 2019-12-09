#include "gtest/gtest.h"

#include "fixtures.h"
#include "interpreter/control_unit.h"
#include "interpreter/user_input_impl.h"

using namespace chip8;

TEST_F(TestControlUnitFixture, returnFromSubroutine) {
  pc = 0x1;
  stack_ptr = 0x1;
  stack[0x1] = 0x4;

  ctrl_unit.returnFromSubroutine();

  EXPECT_EQ(stack_ptr, 0x0);
  EXPECT_EQ(pc, 0x4);
}

TEST_F(TestControlUnitFixture, jumpToLocation) {
  pc = 0x0;

  ctrl_unit.jumpToLocation(0x12);

  EXPECT_EQ(pc, 0x12);
}

TEST_F(TestControlUnitFixture, callSubroutineAt) {
  pc = 0x4;
  stack_ptr = 0x0;

  ctrl_unit.callSubroutineAt(0x12);

  EXPECT_EQ(pc, 0x12);
  EXPECT_EQ(stack_ptr, 0x1);
  EXPECT_EQ(stack[stack_ptr], 0x4);
}

TEST_F(TestControlUnitFixture, jumpBecauseValueAndRegisterAreEqual) {
  pc = 0x4;
  registers[1] = 0x2;

  ctrl_unit.skipNextInstructionIfEqual(0x2, RegisterId(1));

  EXPECT_EQ(pc, 0x6);
}

TEST_F(TestControlUnitFixture, jumpBecauseValueAndRegisterAreNotEqual) {
  pc = 0x4;
  registers[1] = 0x1;

  ctrl_unit.skipNextInstructionIfEqual(0x2, RegisterId(1));

  EXPECT_EQ(pc, 0x4);
}

TEST_F(TestControlUnitFixture, DontJumpBecauseValueAndRegisterAreEqual) {
  pc = 0x4;
  registers[1] = 0x2;

  ctrl_unit.skipNextInstructionIfNotEqual(0x2, RegisterId(1));

  EXPECT_EQ(pc, 0x4);
}

TEST_F(TestControlUnitFixture, DontJumpBecauseValueAndRegisterAreNotEqual) {
  pc = 0x4;
  registers[1] = 0x1;

  ctrl_unit.skipNextInstructionIfNotEqual(0x2, RegisterId(1));

  EXPECT_EQ(pc, 0x6);
}

TEST_F(TestControlUnitFixture, JumpBecauseTwoRegistersAreEqual) {
  pc = 0x4;
  registers[1] = 0x1;
  registers[0] = 0x1;

  ctrl_unit.skipNextInstructionIfRegistersEqual(RegisterId(0), RegisterId(1));

  EXPECT_EQ(pc, 0x6);
}

TEST_F(TestControlUnitFixture, StoreInRegister) {
  ctrl_unit.storeInRegister(0x2, RegisterId(1));

  EXPECT_EQ(registers[1], 0x2);
}

TEST_F(TestControlUnitFixture, AddToRegister) {
  registers[1] = 0x2;

  ctrl_unit.addToRegister(0x2, RegisterId(1));

  EXPECT_EQ(registers[1], 0x4);
}

TEST_F(TestControlUnitFixture, storeRegisterInRegister) {
  registers[0] = 0x6;
  registers[1] = 0x2;

  ctrl_unit.storeRegisterInRegister(RegisterId(1), RegisterId(0));

  EXPECT_EQ(registers[0], 0x6);
  EXPECT_EQ(registers[1], 0x6);
}

TEST_F(TestControlUnitFixture, bitwiseOR) {
  registers[0] = 0b11001111;
  registers[1] = 0b00001111;

  ctrl_unit.bitwiseOr(RegisterId(1), RegisterId(0));

  EXPECT_EQ(registers[1], 0b11001111);
}

TEST_F(TestControlUnitFixture, bitwiseAnd) {
  registers[0] = 0b11001111;
  registers[1] = 0b00001111;

  ctrl_unit.bitwiseAnd(RegisterId(1), RegisterId(0));

  EXPECT_EQ(registers[1], 0b00001111);
}

TEST_F(TestControlUnitFixture, bitwiseXor) {
  registers[0] = 0b11001111;
  registers[1] = 0b00001111;

  ctrl_unit.bitwiseXor(RegisterId(1), RegisterId(0));

  EXPECT_EQ(registers[1], 0b11000000);
}

TEST_F(TestControlUnitFixture, addRegisterToRegisterBelowLimit) {
  registers[0] = 0x2;
  registers[1] = 0x2;

  ctrl_unit.addRegisterToRegister(RegisterId(1), RegisterId(0));

  EXPECT_EQ(registers[1], 0x4);
  EXPECT_EQ(registers[0xF], 0x0);
}

TEST_F(TestControlUnitFixture, addRegisterToRegisterAboveLimit) {
  registers[0] = 245;
  registers[1] = 20;

  ctrl_unit.addRegisterToRegister(RegisterId(1), RegisterId(0));

  EXPECT_EQ(registers[1], static_cast<std::uint8_t>(245 + 20));
  EXPECT_EQ(registers[0xF], 0x1);
}

TEST_F(TestControlUnitFixture, subtractRegisterToRegisterNominal) {
  registers[0] = 20;
  registers[1] = 245;

  ctrl_unit.subtractRegisterToRegister(RegisterId(1), RegisterId(0));

  EXPECT_EQ(registers[1], 225);
  EXPECT_EQ(registers[0xF], 0x0);
}

TEST_F(TestControlUnitFixture, subtractRegisterToRegisterBelowZero) {
  registers[0] = 245;
  registers[1] = 20;

  ctrl_unit.subtractRegisterToRegister(RegisterId(1), RegisterId(0));

  EXPECT_EQ(registers[1], static_cast<uint8_t>(20 - 245));
  EXPECT_EQ(registers[0xF], 0x1);
}

TEST_F(TestControlUnitFixture, shiftRightLSBZero) {
  registers[0] = 0b00000010;

  ctrl_unit.shiftRight(RegisterId(0));

  EXPECT_EQ(registers[0], 0b00000001);
  EXPECT_EQ(registers[0xF], 0x0);
}

TEST_F(TestControlUnitFixture, shiftRightLSBOne) {
  registers[0] = 0b00000011;

  ctrl_unit.shiftRight(RegisterId(0));

  EXPECT_EQ(registers[0], 0b00000001);
  EXPECT_EQ(registers[0xF], 0x1);
}

TEST_F(TestControlUnitFixture, shiftLeftMSBZero) {
  registers[0] = 0b00000010;

  ctrl_unit.shiftLeft(RegisterId(0));

  EXPECT_EQ(registers[0], 0b00000100);
  EXPECT_EQ(registers[0xF], 0x0);
}

TEST_F(TestControlUnitFixture, shiftLeftMSBOne) {
  registers[0] = 0b10000001;

  ctrl_unit.shiftLeft(RegisterId(0));

  EXPECT_EQ(registers[0], 0b00000010);
  EXPECT_EQ(registers[0xF], 0x1);
}

TEST_F(TestControlUnitFixture, JumpBecauseTwoRegistersAreNotEqual) {
  pc = 0x4;
  registers[1] = 0x3;
  registers[0] = 0x1;

  ctrl_unit.skipNextInstructionIfRegistersNotEqual(RegisterId(0),
                                                   RegisterId(1));

  EXPECT_EQ(pc, 0x6);
}

TEST_F(TestControlUnitFixture, StoreInMemoryAddressRegister) {
  mem_add_reg = 0x14;

  ctrl_unit.storeInMemoryAddressRegister(0x2);

  EXPECT_EQ(mem_add_reg, 0x2);
}

TEST_F(TestControlUnitFixture, SetPCToValuePlusV0) {
  pc = 0x4;
  registers[0] = 0x1;

  ctrl_unit.setPCToV0PlusValue(0x2);

  EXPECT_EQ(pc, 0x3);
}

TEST_F(TestControlUnitFixture, DisplayOneByteOnScreen) {
  ram[0x400] = 0b11111111;
  mem_add_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(1, RegisterId(0), RegisterId(1));

  EXPECT_EQ(model.getPixelValue(0, 0), 1);
}

TEST_F(TestControlUnitFixture, DisplaySeveralSpritesOnScreen) {
  ram[0x400] = 0b11111111;
  ram[0x401] = 0b11111111;
  ram[0x402] = 0b11111111;
  mem_add_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(3, RegisterId(0), RegisterId(1));

  EXPECT_EQ(model.getPixelValue(0, 24), 0);
  EXPECT_EQ(model.getPixelValue(0, 25), 0);
}

TEST_F(TestControlUnitFixture, DisplaySpriteOnScreenFlagIsTrue) {
  ram[0x400] = 0b11111111;
  mem_add_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(1, RegisterId(0), RegisterId(1));

  EXPECT_EQ(registers[0xF], 1);
}

TEST_F(TestControlUnitFixture, DisplayOnScreenWithoutModificationFlagIsFalse) {
  ram[0x400] = 0b000000000;
  mem_add_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(1, RegisterId(0), RegisterId(1));

  EXPECT_EQ(registers[0xF], 0);
}

TEST_F(TestControlUnitFixture, CheckIfKeyPressedFalseCase) {
  registers[1] = 0x1;
  pc = 0x2;

  ctrl_unit.checkIfKeyPressed(RegisterId(1));

  EXPECT_EQ(pc, 0x2);
}

TEST_F(TestControlUnitFixture, CheckIfKeyPressedTrueCase) {
  registers[1] = 0x1;
  pc = 0x2;
  ui_ctrler.setInputState(InputId::INPUT_1, InputState::ON);

  ctrl_unit.checkIfKeyPressed(RegisterId(1));

  EXPECT_EQ(pc, 0x4);
}

TEST_F(TestControlUnitFixture, CheckIfKeyNotPressedFalseCase) {
  registers[1] = 0x1;
  pc = 0x2;

  ctrl_unit.checkIfKeyNotPressed(RegisterId(1));

  EXPECT_EQ(pc, 0x4);
}

TEST_F(TestControlUnitFixture, CheckIfKeyNotPressedTrueCase) {
  registers[1] = 0x1;
  pc = 0x2;
  ui_ctrler.setInputState(InputId::INPUT_1, InputState::ON);

  ctrl_unit.checkIfKeyNotPressed(RegisterId(1));

  EXPECT_EQ(pc, 0x2);
}

TEST_F(TestControlUnitFixture, WaitForKeyPressedTrueCase) {
  registers[1] = 0x0;
  pc = 0x2;
  ui_ctrler.setInputState(InputId::INPUT_1, InputState::ON);

  ctrl_unit.waitForKeyPressed(RegisterId(1));

  EXPECT_EQ(pc, 0x2);
  EXPECT_EQ(registers[1], 0x1);
}

TEST_F(TestControlUnitFixture, WaitForKeyPressedFalseCase) {
  registers[1] = 0x0;
  pc = 0x2;

  ctrl_unit.waitForKeyPressed(RegisterId(1));

  EXPECT_EQ(pc, 0x1);
}

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
