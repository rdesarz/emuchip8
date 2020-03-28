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

BOOST_STRONG_TYPEDEF(std::uint16_t, RegisterId)

class ControlUnit {
 public:
  virtual void clearDisplay() = 0;

  virtual void returnFromSubroutine() = 0;

  virtual void jumpToLocation(uint16_t address) = 0;

  virtual void callSubroutineAt(uint16_t address) = 0;

  virtual void skipNextInstructionIfEqual(uint8_t value, RegisterId reg) = 0;

  virtual void skipNextInstructionIfNotEqual(uint8_t value, RegisterId reg) = 0;

  virtual void skipNextInstructionIfRegistersEqual(RegisterId reg_x,
                                                   RegisterId reg_y) = 0;

  virtual void storeInRegister(uint8_t value, RegisterId reg) = 0;

  virtual void addToRegister(uint8_t value, RegisterId reg) = 0;

  virtual void storeRegisterInRegister(RegisterId reg_x, RegisterId reg_y) = 0;

  virtual void bitwiseOr(RegisterId reg_x, RegisterId reg_y) = 0;

  virtual void bitwiseAnd(RegisterId reg_x, RegisterId reg_y) = 0;

  virtual void bitwiseXor(RegisterId reg_x, RegisterId reg_y) = 0;

  virtual void addRegisterToRegister(RegisterId reg_x, RegisterId reg_y) = 0;

  virtual void subtractRegisterToRegister(RegisterId reg_x,
                                          RegisterId reg_y) = 0;

  virtual void shiftRight(RegisterId reg) = 0;

  virtual void shiftLeft(RegisterId reg) = 0;

  virtual void skipNextInstructionIfRegistersNotEqual(RegisterId reg_x,
                                                      RegisterId reg_y) = 0;

  virtual void storeInMemoryAddressRegister(uint16_t value) = 0;

  virtual void setPCToV0PlusValue(uint16_t value) = 0;

  virtual void registerEqualRandomValue(uint8_t value, RegisterId reg) = 0;

  virtual void displayOnScreen(uint16_t n_bytes_to_read, RegisterId reg_x,
                               RegisterId reg_y) = 0;

  virtual void storeDelayTimer(RegisterId reg_x) = 0;

  virtual void checkIfKeyPressed(RegisterId reg_x) = 0;

  virtual void checkIfKeyNotPressed(RegisterId reg_x) = 0;

  virtual void waitForKeyPressed(RegisterId reg_x) = 0;

  virtual void setDelayTimerRegister(RegisterId reg_x) = 0;

  virtual void setSoundTimerRegister(RegisterId reg_x) = 0;

  virtual void addToIndexReg(RegisterId reg_x) = 0;

  virtual void setIndexRegToSpriteLocation(RegisterId reg_x) = 0;

  virtual void storeBCDRepresentation(RegisterId reg_x) = 0;

  virtual void storeMultipleRegister(RegisterId reg_x) = 0;

  virtual void readMultipleRegister(RegisterId reg_x) = 0;
};

}  // namespace chip8
#endif  // MODULES_INTERPRETER_CONTROL_UNIT_H_
