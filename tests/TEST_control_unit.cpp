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

#include "fixtures.h"
#include "interpreter/control_unit.h"
#include "interpreter/user_input_impl.h"

using namespace chip8;

TEST_F(TestControlUnitFixture, ClearDisplay) {
  model.setPixelValue(0, 0, 1);

  ctrl_unit.clearDisplay();

  EXPECT_EQ(model.getPixelValue(0, 0), 0);
}

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
  index_reg = 0x14;

  ctrl_unit.storeInMemoryAddressRegister(0x2);

  EXPECT_EQ(index_reg, 0x2);
}

TEST_F(TestControlUnitFixture, SetPCToValuePlusV0) {
  pc = 0x4;
  registers[0] = 0x1;

  ctrl_unit.setPCToV0PlusValue(0x2);

  EXPECT_EQ(pc, 0x3);
}

TEST_F(TestControlUnitFixture, DisplayOneByteOnScreen) {
  ram[0x400] = 0b11111111;
  index_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(1, RegisterId(0), RegisterId(1));

  EXPECT_EQ(model.getPixelValue(0, 0), 1);
}

TEST_F(TestControlUnitFixture, DisplaySeveralSpritesOnScreen) {
  ram[0x400] = 0b11111111;
  ram[0x401] = 0b11111111;
  ram[0x402] = 0b11111111;
  index_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(3, RegisterId(0), RegisterId(1));

  EXPECT_EQ(model.getPixelValue(0, 24), 0);
  EXPECT_EQ(model.getPixelValue(0, 25), 0);
}

TEST_F(TestControlUnitFixture, DisplaySpriteOnScreenFlagIsTrue) {
  ram[0x400] = 0b11111111;
  index_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(1, RegisterId(0), RegisterId(1));

  EXPECT_EQ(registers[0xF], 1);
}

TEST_F(TestControlUnitFixture, DisplayOnScreenWithoutModificationFlagIsFalse) {
  ram[0x400] = 0b000000000;
  index_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(1, RegisterId(0), RegisterId(1));

  EXPECT_EQ(registers[0xF], 0);
}

TEST_F(TestControlUnitFixture, StoreDelayTimerRegisterValue) {
  registers[1] = 0x3;
  delay_timer_reg = 0x5;

  ctrl_unit.storeDelayTimer(RegisterId(1));

  EXPECT_EQ(registers[1], 5);
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

TEST_F(TestControlUnitFixture, SetDelayTimerRegister) {
  delay_timer_reg = 0x10;
  registers[1] = 0x20;

  ctrl_unit.setDelayTimerRegister(RegisterId(1));

  EXPECT_EQ(delay_timer_reg, 0x20);
}

TEST_F(TestControlUnitFixture, SetSoundTimerRegister) {
  sound_timer_reg = 0x10;
  registers[1] = 0x20;

  ctrl_unit.setSoundTimerRegister(RegisterId(1));

  EXPECT_EQ(sound_timer_reg, 0x20);
}

TEST_F(TestControlUnitFixture, addToIndexReg) {
  index_reg = 0x2;
  registers[1] = 0x3;

  ctrl_unit.addToIndexReg(RegisterId(1));

  EXPECT_EQ(index_reg, 0x5);
}

TEST_F(TestControlUnitFixture, storeBCDRepresentation) {
  index_reg = 0x450;
  registers[1] = 123;

  ctrl_unit.storeBCDRepresentation(RegisterId(1));

  EXPECT_EQ(ram[0x450], 3);
  EXPECT_EQ(ram[0x451], 2);
  EXPECT_EQ(ram[0x452], 1);
}

TEST_F(TestControlUnitFixture, storeMultipleRegisters) {
  index_reg = 0x450;
  registers[0] = 1;
  registers[1] = 2;
  registers[2] = 3;

  ctrl_unit.storeMultipleRegister(RegisterId(2));

  EXPECT_EQ(ram[0x450], 1);
  EXPECT_EQ(ram[0x451], 2);
  EXPECT_EQ(ram[0x452], 3);
}

TEST_F(TestControlUnitFixture, readMultipleRegisters) {
  index_reg = 0x450;
  ram[0x450] = 1;
  ram[0x451] = 2;
  ram[0x452] = 3;

  ctrl_unit.readMultipleRegister(RegisterId(2));

  EXPECT_EQ(registers[0], 1);
  EXPECT_EQ(registers[1], 2);
  EXPECT_EQ(registers[2], 3);
}

TEST_F(TestControlUnitFixture, setSpriteLocation) {
  index_reg = 0x2;
  registers[2] = 0xA;

  ctrl_unit.setIndexRegToSpriteLocation(RegisterId(2));

  EXPECT_EQ(index_reg, A_SPRITE_OFFSET);
}