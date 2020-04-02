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

#include "display_controller.h"
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
    RandomNumberGenerator<std::uniform_int_distribution<uint8_t>>;

class ControlUnitImpl : public ControlUnit {
 public:
  ControlUnitImpl(ProgramCounter& pc, StackPointer& stack_ptr,
                  IndexRegister& index_reg, DelayTimerRegister& delay_timer_reg,
                  SoundTimerRegister& sound_timer_reg, Stack& stack,
                  std::vector<GeneralRegister>& registers, RAM& ram,
                  DisplayController& display, UserInputController& ui_ctrler);

  void clearDisplay() override;

  void returnFromSubroutine() override;

  void jumpToLocation(address_t address) override;

  void callSubroutineAt(address_t address) override;

  void skipNextInstructionIfEqual(byte_t value, register_id_t reg) override;

  void skipNextInstructionIfNotEqual(byte_t value, register_id_t reg) override;

  void skipNextInstructionIfRegistersEqual(register_id_t reg_x,
                                           register_id_t reg_y) override;

  void storeInRegister(byte_t value, register_id_t reg) override;

  void addToRegister(byte_t value, register_id_t reg) override;

  void storeRegisterInRegister(register_id_t reg_x,
                               register_id_t reg_y) override;

  void bitwiseOr(register_id_t reg_x, register_id_t reg_y) override;

  void bitwiseAnd(register_id_t reg_x, register_id_t reg_y) override;

  void bitwiseXor(register_id_t reg_x, register_id_t reg_y) override;

  void addRegisterToRegister(register_id_t reg_x, register_id_t reg_y) override;

  void subtractRegYToRegX(register_id_t reg_x, register_id_t reg_y) override;

  void subtractRegXToRegY(register_id_t reg_x, register_id_t reg_y) override;

  void shiftRight(register_id_t reg) override;

  void shiftLeft(register_id_t reg) override;

  void skipNextInstructionIfRegistersNotEqual(register_id_t reg_x,
                                              register_id_t reg_y) override;

  void storeInMemoryAddressRegister(address_t value) override;

  void setPCToV0PlusValue(address_t value) override;

  void registerEqualRandomValue(uint8_t value, register_id_t reg) override;

  void displayOnScreen(uint16_t n_bytes_to_read, register_id_t reg_x,
                       register_id_t reg_y) override;

  void storeDelayTimer(register_id_t reg_x) override;

  void skipNextInstructionIfKeyPressed(register_id_t reg_x) override;

  void skipNextInstructionIfKeyNotPressed(register_id_t reg_x) override;

  void waitForKeyPressed(register_id_t reg_x) override;

  void setDelayTimerRegister(register_id_t reg_x) override;

  void setSoundTimerRegister(register_id_t reg_x) override;

  void addToIndexReg(register_id_t reg_x) override;

  void setIndexRegToSpriteLocation(register_id_t reg_x) override;

  void storeBCDRepresentation(register_id_t reg_x) override;

  void storeMultipleRegister(register_id_t reg_x) override;

  void readMultipleRegister(register_id_t reg_x) override;

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
