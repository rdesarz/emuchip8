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
  model.setPixelValue(column_t(0), row_t(0), 1);

  ctrl_unit.clearDisplay();

  EXPECT_EQ(model.getPixelValue(column_t(0), row_t(0)), 0);
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

  ctrl_unit.jumpToLocation(address_t(0x12));

  // Jump right before the instruction because PC will be incremented during the
  // loop
  EXPECT_EQ(pc, 0x10);
}

TEST_F(TestControlUnitFixture, callSubroutineAt) {
  pc = 0x4;
  stack_ptr = 0x0;

  ctrl_unit.callSubroutineAt(address_t(0x12));

  // Jump right before the instruction because PC will be incremented during the
  // loop
  EXPECT_EQ(pc, 0x10);
  EXPECT_EQ(stack_ptr, 0x1);
  EXPECT_EQ(stack[stack_ptr], 0x4);
}

TEST_F(TestControlUnitFixture, jumpBecauseValueAndRegisterAreEqual) {
  pc = 0x4;
  registers[1] = 0x2;

  ctrl_unit.skipNextInstructionIfEqual(byte_t(0x2), register_id_t(1));

  EXPECT_EQ(pc, 0x6);
}

TEST_F(TestControlUnitFixture, jumpBecauseValueAndRegisterAreNotEqual) {
  pc = 0x4;
  registers[1] = 0x1;

  ctrl_unit.skipNextInstructionIfEqual(byte_t(0x2), register_id_t(1));

  EXPECT_EQ(pc, 0x4);
}

TEST_F(TestControlUnitFixture, DontJumpBecauseValueAndRegisterAreEqual) {
  pc = 0x4;
  registers[1] = 0x2;

  ctrl_unit.skipNextInstructionIfNotEqual(byte_t(0x2), register_id_t(1));

  EXPECT_EQ(pc, 0x4);
}

TEST_F(TestControlUnitFixture, DontJumpBecauseValueAndRegisterAreNotEqual) {
  pc = 0x4;
  registers[1] = 0x1;

  ctrl_unit.skipNextInstructionIfNotEqual(byte_t(0x2), register_id_t(1));

  EXPECT_EQ(pc, 0x6);
}

TEST_F(TestControlUnitFixture, JumpBecauseTwoRegistersAreEqual) {
  pc = 0x4;
  registers[1] = 0x1;
  registers[0] = 0x1;

  ctrl_unit.skipNextInstructionIfRegistersEqual(register_id_t(0),
                                                register_id_t(1));

  EXPECT_EQ(pc, 0x6);
}

TEST_F(TestControlUnitFixture, StoreInRegister) {
  ctrl_unit.storeInRegister(byte_t(0x2), register_id_t(1));

  EXPECT_EQ(registers[1], 0x2);
}

TEST_F(TestControlUnitFixture, AddToRegister) {
  registers[1] = 0x2;

  ctrl_unit.addToRegister(byte_t(0x2), register_id_t(1));

  EXPECT_EQ(registers[1], 0x4);
}

TEST_F(TestControlUnitFixture, storeRegisterInRegister) {
  registers[0] = 0x6;
  registers[1] = 0x2;

  ctrl_unit.storeRegisterInRegister(register_id_t(1), register_id_t(0));

  EXPECT_EQ(registers[0], 0x6);
  EXPECT_EQ(registers[1], 0x6);
}

TEST_F(TestControlUnitFixture, bitwiseOR) {
  registers[0] = 0b11001111;
  registers[1] = 0b00001111;

  ctrl_unit.bitwiseOr(register_id_t(1), register_id_t(0));

  EXPECT_EQ(registers[1], 0b11001111);
}

TEST_F(TestControlUnitFixture, bitwiseAnd) {
  registers[0] = 0b11001111;
  registers[1] = 0b00001111;

  ctrl_unit.bitwiseAnd(register_id_t(1), register_id_t(0));

  EXPECT_EQ(registers[1], 0b00001111);
}

TEST_F(TestControlUnitFixture, bitwiseXor) {
  registers[0] = 0b11001111;
  registers[1] = 0b00001111;

  ctrl_unit.bitwiseXor(register_id_t(1), register_id_t(0));

  EXPECT_EQ(registers[1], 0b11000000);
}

TEST_F(TestControlUnitFixture, addRegisterToRegisterBelowLimit) {
  registers[0] = 0x2;
  registers[1] = 0x2;

  ctrl_unit.addRegisterToRegister(register_id_t(1), register_id_t(0));

  EXPECT_EQ(registers[1], 0x4);
  EXPECT_EQ(registers[0xF], 0x0);
}

TEST_F(TestControlUnitFixture, addRegisterToRegisterAboveLimit) {
  registers[0] = 245;
  registers[1] = 20;

  ctrl_unit.addRegisterToRegister(register_id_t(1), register_id_t(0));

  EXPECT_EQ(registers[1], static_cast<std::uint8_t>(245 + 20));
  EXPECT_EQ(registers[0xF], 0x1);
}

TEST_F(TestControlUnitFixture, subtractRegYToRegXNominal) {
  registers[0] = 20;
  registers[1] = 245;

  ctrl_unit.subtractRegYToRegX(register_id_t(1), register_id_t(0));

  EXPECT_EQ(registers[1], 225);
  EXPECT_EQ(registers[0xF], 0x1);
}

TEST_F(TestControlUnitFixture, subtractRegYToRegXBelowZero) {
  registers[0] = 245;
  registers[1] = 20;

  ctrl_unit.subtractRegYToRegX(register_id_t(1), register_id_t(0));

  EXPECT_EQ(registers[1], static_cast<uint8_t>(20 - 245));
  EXPECT_EQ(registers[0xF], 0x0);
}

TEST_F(TestControlUnitFixture, subtractRegXToRegYNominal) {
  registers[0] = 245;
  registers[1] = 20;

  ctrl_unit.subtractRegXToRegY(register_id_t(1), register_id_t(0));

  EXPECT_EQ(registers[1], 225);
  EXPECT_EQ(registers[0xF], 0x1);
}

TEST_F(TestControlUnitFixture, subtractRegXToRegYBelowZero) {
  registers[0] = 20;
  registers[1] = 245;

  ctrl_unit.subtractRegXToRegY(register_id_t(1), register_id_t(0));

  EXPECT_EQ(registers[1], static_cast<uint8_t>(20 - 245));
  EXPECT_EQ(registers[0xF], 0x0);
}

TEST_F(TestControlUnitFixture, shiftRightLSBZero) {
  registers[0] = 0b00000010;

  ctrl_unit.shiftRight(register_id_t(0));

  EXPECT_EQ(registers[0], 0b00000001);
  EXPECT_EQ(registers[0xF], 0x0);
}

TEST_F(TestControlUnitFixture, shiftRightLSBOne) {
  registers[0] = 0b00000011;

  ctrl_unit.shiftRight(register_id_t(0));

  EXPECT_EQ(registers[0], 0b00000001);
  EXPECT_EQ(registers[0xF], 0x1);
}

TEST_F(TestControlUnitFixture, shiftLeftMSBZero) {
  registers[0] = 0b00000010;

  ctrl_unit.shiftLeft(register_id_t(0));

  EXPECT_EQ(registers[0], 0b00000100);
  EXPECT_EQ(registers[0xF], 0x0);
}

TEST_F(TestControlUnitFixture, shiftLeftMSBOne) {
  registers[0] = 0b10000001;

  ctrl_unit.shiftLeft(register_id_t(0));

  EXPECT_EQ(registers[0], 0b00000010);
  EXPECT_EQ(registers[0xF], 0x1);
}

TEST_F(TestControlUnitFixture, JumpBecauseTwoRegistersAreNotEqual) {
  pc = 0x4;
  registers[1] = 0x3;
  registers[0] = 0x1;

  ctrl_unit.skipNextInstructionIfRegistersNotEqual(register_id_t(0),
                                                   register_id_t(1));

  EXPECT_EQ(pc, 0x6);
}

TEST_F(TestControlUnitFixture, StoreInMemoryAddressRegister) {
  index_reg = 0x14;

  ctrl_unit.storeInMemoryAddressRegister(address_t(0x2));

  EXPECT_EQ(index_reg, 0x2);
}

TEST_F(TestControlUnitFixture, SetPCToValuePlusV0) {
  pc = 0x4;
  registers[0] = 0x1;

  ctrl_unit.setPCToV0PlusValue(address_t(0x2));

  EXPECT_EQ(pc, 0x1);
}

TEST_F(TestControlUnitFixture, DisplayOneByteOnScreen) {
  ram[0x400] = 0b11111111;
  index_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(1, register_id_t(0), register_id_t(1));

  EXPECT_EQ(model.getPixelValue(column_t(0), row_t(0)), 1);
}

TEST_F(TestControlUnitFixture, DisplaySeveralSpritesOnScreen) {
  ram[0x400] = 0b11111111;
  ram[0x401] = 0b11111111;
  ram[0x402] = 0b11111111;
  index_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(3, register_id_t(0), register_id_t(1));

  EXPECT_EQ(model.getPixelValue(column_t(8), row_t(0)), 0);
  EXPECT_EQ(model.getPixelValue(column_t(1), row_t(3)), 0);
}

TEST_F(TestControlUnitFixture, DisplayEightSpritesOnScreen) {
  for (std::size_t i = 0; i < 8; ++i) {
    ram[i + 0x400] = 0b11111111;
  }
  index_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(8, register_id_t(0), register_id_t(1));

  EXPECT_EQ(model.getPixelValue(column_t(1), row_t(0)), 1);
  EXPECT_EQ(model.getPixelValue(column_t(1), row_t(7)), 1);
}

TEST_F(TestControlUnitFixture, DisplaySpriteOnScreenFlagIsTrue) {
  ram[0x400] = 0b11111111;
  index_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(1, register_id_t(0), register_id_t(1));

  EXPECT_EQ(registers[0xF], 1);
}

TEST_F(TestControlUnitFixture, DisplayOnScreenWithoutModificationFlagIsFalse) {
  ram[0x400] = 0b000000000;
  index_reg = 0x400;
  registers[0] = 0x0;
  registers[1] = 0x0;

  ctrl_unit.displayOnScreen(1, register_id_t(0), register_id_t(1));

  EXPECT_EQ(registers[0xF], 0);
}

TEST_F(TestControlUnitFixture, StoreDelayTimerRegisterValue) {
  registers[1] = 0x3;
  delay_timer_reg = 0x5;

  ctrl_unit.storeDelayTimer(register_id_t(1));

  EXPECT_EQ(registers[1], 5);
}

TEST_F(TestControlUnitFixture, CheckIfKeyPressedFalseCase) {
  registers[1] = 0x1;
  pc = 0x2;

  ctrl_unit.skipNextInstructionIfKeyPressed(register_id_t(1));

  EXPECT_EQ(pc, 0x2);
}

TEST_F(TestControlUnitFixture, CheckIfKeyPressedTrueCase) {
  registers[1] = 0x1;
  pc = 0x2;
  ui_ctrler.setInputState(InputId::INPUT_1, InputState::ON);

  ctrl_unit.skipNextInstructionIfKeyPressed(register_id_t(1));

  EXPECT_EQ(pc, 0x4);
}

TEST_F(TestControlUnitFixture, CheckIfKeyNotPressedFalseCase) {
  registers[1] = 0x1;
  pc = 0x2;

  ctrl_unit.skipNextInstructionIfKeyNotPressed(register_id_t(1));

  EXPECT_EQ(pc, 0x4);
}

TEST_F(TestControlUnitFixture, CheckIfKeyNotPressedTrueCase) {
  registers[1] = 0x1;
  pc = 0x2;
  ui_ctrler.setInputState(InputId::INPUT_1, InputState::ON);

  ctrl_unit.skipNextInstructionIfKeyNotPressed(register_id_t(1));

  EXPECT_EQ(pc, 0x2);
}

TEST_F(TestControlUnitFixture, WaitForKeyPressedTrueCase) {
  registers[1] = 0x0;
  pc = 0x2;
  ui_ctrler.setInputState(InputId::INPUT_1, InputState::ON);

  ctrl_unit.waitForKeyPressed(register_id_t(1));

  EXPECT_EQ(pc, 0x2);
  EXPECT_EQ(registers[1], 0x1);
}

TEST_F(TestControlUnitFixture, WaitForKeyPressedFalseCase) {
  registers[1] = 0x0;
  pc = 0x2;

  ctrl_unit.waitForKeyPressed(register_id_t(1));

  EXPECT_EQ(pc, 0x0);
}

TEST_F(TestControlUnitFixture, SetDelayTimerRegister) {
  delay_timer_reg = 0x10;
  registers[1] = 0x20;

  ctrl_unit.setDelayTimerRegister(register_id_t(1));

  EXPECT_EQ(delay_timer_reg, 0x20);
}

TEST_F(TestControlUnitFixture, SetSoundTimerRegister) {
  sound_timer_reg = 0x10;
  registers[1] = 0x20;

  ctrl_unit.setSoundTimerRegister(register_id_t(1));

  EXPECT_EQ(sound_timer_reg, 0x20);
}

TEST_F(TestControlUnitFixture, addToIndexReg) {
  index_reg = 0x2;
  registers[1] = 0x3;

  ctrl_unit.addToIndexReg(register_id_t(1));

  EXPECT_EQ(index_reg, 0x5);
}

TEST_F(TestControlUnitFixture, storeBCDRepresentation) {
  index_reg = 0x450;
  registers[1] = 123;

  ctrl_unit.storeBCDRepresentation(register_id_t(1));

  EXPECT_EQ(ram[0x450], 3);
  EXPECT_EQ(ram[0x451], 2);
  EXPECT_EQ(ram[0x452], 1);
}

TEST_F(TestControlUnitFixture, storeMultipleRegisters) {
  index_reg = 0x450;
  registers[0] = 1;
  registers[1] = 2;
  registers[2] = 3;

  ctrl_unit.storeMultipleRegister(register_id_t(2));

  EXPECT_EQ(ram[0x450], 1);
  EXPECT_EQ(ram[0x451], 2);
  EXPECT_EQ(ram[0x452], 3);
}

TEST_F(TestControlUnitFixture, readMultipleRegisters) {
  index_reg = 0x450;
  ram[0x450] = 1;
  ram[0x451] = 2;
  ram[0x452] = 3;

  ctrl_unit.readMultipleRegister(register_id_t(2));

  EXPECT_EQ(registers[0], 1);
  EXPECT_EQ(registers[1], 2);
  EXPECT_EQ(registers[2], 3);
}

TEST_F(TestControlUnitFixture, setSpriteLocation) {
  index_reg = 0x2;
  registers[2] = 0xA;

  ctrl_unit.setIndexRegToSpriteLocation(register_id_t(2));

  EXPECT_EQ(index_reg, A_SPRITE_OFFSET);
}