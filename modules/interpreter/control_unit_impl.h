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

#ifndef MODULES_INTERPRETER_CONTROL_UNIT_IMPL_H_
#define MODULES_INTERPRETER_CONTROL_UNIT_IMPL_H_

#include <random>
#include <vector>

#include "display/display_controller.h"
#include "interpreter/control_unit.h"
#include "interpreter/memory.h"
#include "interpreter/user_input.h"

namespace chip8 {

template <class Distribution>
class RandomNumberGenerator {
 public:
  RandomNumberGenerator(int min_value, int max_value)
      : m_random_engine(m_random_device()),
        m_distribution(min_value, max_value) {}

  int generateNumber() { return m_distribution(m_random_engine); }

 private:
  std::random_device m_random_device;
  std::mt19937 m_random_engine;
  Distribution m_distribution;
};

using UniformRandomNumberGenerator =
    RandomNumberGenerator<std::uniform_int_distribution<int>>;

class ControlUnitImpl : public ControlUnit {
 public:
  ControlUnitImpl(ProgramCounter& pc, StackPointer& stack_ptr,
                  IndexRegister& index_reg, DelayTimerRegister& delay_timer_reg,
                  SoundTimerRegister& sound_timer_reg, Stack& stack,
                  std::vector<GeneralRegister>& registers, RAM& ram,
                  DisplayController& display, UserInputController& ui_ctrler);

  void clearDisplay() override;

  void returnFromSubroutine() override;

  void jumpToLocation(uint16_t address) override;

  void callSubroutineAt(uint16_t address) override;

  void skipNextInstructionIfEqual(uint8_t value, RegisterId reg) override;

  void skipNextInstructionIfNotEqual(uint8_t value, RegisterId reg) override;

  void skipNextInstructionIfRegistersEqual(RegisterId reg_x,
                                           RegisterId reg_y) override;

  void storeInRegister(uint8_t value, RegisterId reg) override;

  void addToRegister(uint8_t value, RegisterId reg) override;

  void storeRegisterInRegister(RegisterId reg_x, RegisterId reg_y) override;

  void bitwiseOr(RegisterId reg_x, RegisterId reg_y) override;

  void bitwiseAnd(RegisterId reg_x, RegisterId reg_y) override;

  void bitwiseXor(RegisterId reg_x, RegisterId reg_y) override;

  void addRegisterToRegister(RegisterId reg_x, RegisterId reg_y) override;

  void subtractRegisterToRegister(RegisterId reg_x, RegisterId reg_y) override;

  void shiftRight(RegisterId reg) override;

  void shiftLeft(RegisterId reg) override;

  void skipNextInstructionIfRegistersNotEqual(RegisterId reg_x,
                                              RegisterId reg_y) override;

  void storeInMemoryAddressRegister(uint16_t value) override;

  void setPCToV0PlusValue(uint16_t value) override;

  void registerEqualRandomValue(uint8_t value, RegisterId reg) override;

  void displayOnScreen(uint16_t n_bytes_to_read, RegisterId reg_x,
                       RegisterId reg_y) override;

  void storeDelayTimer(RegisterId reg_x) override;

  void checkIfKeyPressed(RegisterId reg_x) override;

  void checkIfKeyNotPressed(RegisterId reg_x) override;

  void waitForKeyPressed(RegisterId reg_x) override;

  void setDelayTimerRegister(RegisterId reg_x) override;

  void setSoundTimerRegister(RegisterId reg_x) override;

  void addToIndexReg(RegisterId reg_x) override;

  void setIndexRegToSpriteLocation(RegisterId reg_x) override;

  void storeBCDRepresentation(RegisterId reg_x) override;

  void storeMultipleRegister(RegisterId reg_x) override;

  void readMultipleRegister(RegisterId reg_x) override;

 private:
  ProgramCounter& m_pc;
  StackPointer& m_stack_ptr;
  IndexRegister& m_index_reg;
  DelayTimerRegister& m_delay_timer_reg;
  SoundTimerRegister& m_sound_timer_reg;
  Stack& m_stack;
  std::vector<GeneralRegister>& m_registers;
  RAM& m_ram;
  DisplayController& m_display_ctrler;
  UserInputController& m_ui_ctrler;
  UniformRandomNumberGenerator m_rand_num_generator;
};

}  // namespace chip8
#endif  // MODULES_INTERPRETER_CONTROL_UNIT_IMPL_H_
