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

#ifndef TESTS_CONTROL_UNIT_FIXTURES_H_
#define TESTS_CONTROL_UNIT_FIXTURES_H_

#include "interpreter/control_unit.h"

namespace chip8 {

struct MockControlUnit : public ControlUnit {
  void clearDisplay() override { id_called_function = -1; }

  void returnFromSubroutine() override { id_called_function = 0; }

  void jumpToLocation(address_t address) override { id_called_function = 1; }

  void callSubroutineAt(address_t address) override { id_called_function = 2; }

  void skipNextInstructionIfEqual(byte_t value, register_id_t reg) override {
    id_called_function = 3;
  }

  void skipNextInstructionIfNotEqual(byte_t value, register_id_t reg) override {
    id_called_function = 4;
  }

  void skipNextInstructionIfRegistersEqual(register_id_t reg_x,
                                           register_id_t reg_y) override {
    id_called_function = 5;
  }

  void storeInRegister(byte_t value, register_id_t reg) override {
    id_called_function = 6;
  }

  void addToRegister(byte_t value, register_id_t reg) override {
    id_called_function = 7;
  }

  void storeRegisterInRegister(register_id_t reg_x,
                               register_id_t reg_y) override {
    id_called_function = 8;
  }

  void bitwiseOr(register_id_t reg_x, register_id_t reg_y) override {
    id_called_function = 9;
  }

  void bitwiseAnd(register_id_t reg_x, register_id_t reg_y) override {
    id_called_function = 10;
  }

  void bitwiseXor(register_id_t reg_x, register_id_t reg_y) override {
    id_called_function = 11;
  }

  void addRegisterToRegister(register_id_t reg_x,
                             register_id_t reg_y) override {
    id_called_function = 12;
  }

  void subtractRegYToRegX(register_id_t reg_x, register_id_t reg_y) override {
    id_called_function = 13;
  }

  void subtractRegXToRegY(register_id_t reg_x, register_id_t reg_y) override {
    id_called_function = 32;
  }

  void shiftRight(register_id_t reg) override { id_called_function = 14; }

  void shiftLeft(register_id_t reg) override { id_called_function = 15; }

  void skipNextInstructionIfRegistersNotEqual(register_id_t reg_x,
                                              register_id_t reg_y) override {
    id_called_function = 16;
  }

  void storeInMemoryAddressRegister(address_t value) override {
    id_called_function = 17;
  }

  void setPCToV0PlusValue(address_t value) override { id_called_function = 18; }

  void registerEqualRandomValue(uint8_t value, register_id_t reg) override {
    id_called_function = 19;
  }

  void displayOnScreen(uint16_t n_bytes_to_read, register_id_t reg_x,
                       register_id_t reg_y) override {
    id_called_function = 20;
  }

  void storeDelayTimer(register_id_t reg_x) override { id_called_function = 31; }

  void skipNextInstructionIfKeyPressed(register_id_t reg_x) override { id_called_function = 21; }

  void skipNextInstructionIfKeyNotPressed(register_id_t reg_x) override {
    id_called_function = 22;
  }

  void waitForKeyPressed(register_id_t reg_x) override { id_called_function = 23; }

  void setDelayTimerRegister(register_id_t reg_x) { id_called_function = 24; }

  void setSoundTimerRegister(register_id_t reg_x) { id_called_function = 25; }

  void addToIndexReg(register_id_t reg_x) override { id_called_function = 26; }

  void setIndexRegToSpriteLocation(register_id_t reg_x) override {
    id_called_function = 27;
  }

  void storeBCDRepresentation(register_id_t reg_x) override {
    id_called_function = 28;
  }

  void storeMultipleRegister(register_id_t reg_x) override {
    id_called_function = 29;
  }

  void readMultipleRegister(register_id_t reg_x) override {
    id_called_function = 30;
  }

  int id_called_function;
};

}  // namespace chip8
#endif  // TESTS_CONTROL_UNIT_FIXTURES_H_
