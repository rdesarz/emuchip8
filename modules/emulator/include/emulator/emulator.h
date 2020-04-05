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

#ifndef MODULES_INTERPRETER_EMULATOR_H_
#define MODULES_INTERPRETER_EMULATOR_H_

// std
#include <istream>
#include <memory>
#include <vector>

#include "memory.h"

namespace chip8 {

class DisplayController;
class UserInputController;
class ControlUnit;
class InstructionDecoder;
class Clock;

class Emulator {
 public:
  Emulator(std::istream& rom,
           std::unique_ptr<DisplayController> display_controller,
           UserInputController* ui_controller);

  virtual ~Emulator();

  void update();

 private:
  void clockCycle();
  void decrementDelayTimer();

 private:
  // Memory components
  ProgramCounter m_pc;
  StackPointer m_stack_ptr;
  IndexRegister m_index_reg;
  DelayTimerRegister m_delay_timer_reg;
  SoundTimerRegister m_sound_timer_reg;
  Stack m_stack;
  std::vector<GeneralRegister> m_registers;
  RAM m_ram;

  // Controllers
  UserInputController* m_ui_controller;
  std::unique_ptr<Clock> m_clock;
  std::unique_ptr<DisplayController> m_display_controller;
  std::unique_ptr<ControlUnit> m_ctrl_unit;
  std::unique_ptr<InstructionDecoder> m_instruction_decoder;
};

}  // namespace chip8
#endif  // MODULES_INTERPRETER_EMULATOR_H_
