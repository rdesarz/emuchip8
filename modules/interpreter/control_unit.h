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

#ifndef MODULES_INTERPRETER_CONTROL_UNIT_H_
#define MODULES_INTERPRETER_CONTROL_UNIT_H_

#include <vector>

#include "display/display_controller.h"
#include "interpreter/memory.h"
#include "interpreter/user_input.h"

namespace chip8 {

BOOST_STRONG_TYPEDEF(std::uint16_t, register_id_t)

class ControlUnit {
 public:
  virtual void clearDisplay() = 0;

  virtual void returnFromSubroutine() = 0;

  virtual void jumpToLocation(address_t address) = 0;

  virtual void callSubroutineAt(address_t address) = 0;

  virtual void skipNextInstructionIfEqual(byte_t value, register_id_t reg) = 0;

  virtual void skipNextInstructionIfNotEqual(byte_t value,
                                             register_id_t reg) = 0;

  virtual void skipNextInstructionIfRegistersEqual(register_id_t reg_x,
                                                   register_id_t reg_y) = 0;

  virtual void storeInRegister(byte_t value, register_id_t reg) = 0;

  virtual void addToRegister(byte_t value, register_id_t reg) = 0;

  virtual void storeRegisterInRegister(register_id_t reg_x,
                                       register_id_t reg_y) = 0;

  virtual void bitwiseOr(register_id_t reg_x, register_id_t reg_y) = 0;

  virtual void bitwiseAnd(register_id_t reg_x, register_id_t reg_y) = 0;

  virtual void bitwiseXor(register_id_t reg_x, register_id_t reg_y) = 0;

  virtual void addRegisterToRegister(register_id_t reg_x,
                                     register_id_t reg_y) = 0;

  virtual void subtractRegYToRegX(register_id_t reg_x, register_id_t reg_y) = 0;

  virtual void subtractRegXToRegY(register_id_t reg_x, register_id_t reg_y) = 0;

  virtual void shiftRight(register_id_t reg) = 0;

  virtual void shiftLeft(register_id_t reg) = 0;

  virtual void skipNextInstructionIfRegistersNotEqual(register_id_t reg_x,
                                                      register_id_t reg_y) = 0;

  virtual void storeInMemoryAddressRegister(address_t value) = 0;

  virtual void setPCToV0PlusValue(address_t value) = 0;

  virtual void registerEqualRandomValue(uint8_t value, register_id_t reg) = 0;

  virtual void displayOnScreen(uint16_t n_bytes_to_read, register_id_t reg_x,
                               register_id_t reg_y) = 0;

  virtual void storeDelayTimer(register_id_t reg_x) = 0;

  virtual void skipNextInstructionIfKeyPressed(register_id_t reg_x) = 0;

  virtual void skipNextInstructionIfKeyNotPressed(register_id_t reg_x) = 0;

  virtual void waitForKeyPressed(register_id_t reg_x) = 0;

  virtual void setDelayTimerRegister(register_id_t reg_x) = 0;

  virtual void setSoundTimerRegister(register_id_t reg_x) = 0;

  virtual void addToIndexReg(register_id_t reg_x) = 0;

  virtual void setIndexRegToSpriteLocation(register_id_t reg_x) = 0;

  virtual void storeBCDRepresentation(register_id_t reg_x) = 0;

  virtual void storeMultipleRegister(register_id_t reg_x) = 0;

  virtual void readMultipleRegister(register_id_t reg_x) = 0;
};

}  // namespace chip8
#endif  // MODULES_INTERPRETER_CONTROL_UNIT_H_
