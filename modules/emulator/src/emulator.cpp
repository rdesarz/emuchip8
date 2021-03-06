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

// std
#include <iomanip>
#include <iostream>
#include <utility>

#include "emulator/emulator.h"

#include "emulator/control_unit_impl.h"
#include "emulator/display_controller.h"
#include "emulator/display_model.h"
#include "emulator/display_view.h"
#include "emulator/instruction_decoder.h"
#include "emulator/rom_loader.h"
#include "emulator/user_input.h"
#include "emulator/clock.h"

namespace chip8 {

Emulator::Emulator(std::istream &rom,
                   std::unique_ptr<DisplayController> display_controller,
                   UserInputController *ui_controller)
    : m_clock(new Clock([]() { return std::chrono::system_clock::now(); })),
      m_display_controller(std::move(display_controller)),
      m_ui_controller(ui_controller),
      m_registers(16),
      m_ctrl_unit(new ControlUnitImpl(m_pc, m_stack_ptr, m_index_reg,
                                      m_delay_timer_reg, m_sound_timer_reg,
                                      m_stack, m_registers, m_ram,
                                      *m_display_controller, *m_ui_controller)),
      m_instruction_decoder(new InstructionDecoder(m_ctrl_unit.get())) {
  // Load the program
  // TODO: throw exception if load fails
  loadProgramFromStream(m_ram, rom);

  // Load the sprites in memory
  storeSpriteInMemory(m_ram);

  // Register callbacks that will drive the emulator
  m_clock->registerCallback([this]() { this->clockCycle(); }, 600);
  m_clock->registerCallback([this]() { this->decrementDelayTimer(); }, 60);

  // Init components
  m_pc = 0x200;
  m_stack_ptr = 0x0;
  m_delay_timer_reg = 0x0;
}

Emulator::~Emulator() = default;

void Emulator::update() { m_clock->tick(); }

void Emulator::decrementDelayTimer() {
  if (m_delay_timer_reg != 0) {
    --m_delay_timer_reg;
  }
}

void Emulator::clockCycle() {
  // Fetch Opcode
  instruction_t instruction{
      static_cast<uint16_t>(m_ram[m_pc] << 8 | m_ram[m_pc + 1])};

  // Dump instruction
  std::cout << "Executed instruction: " << std::setfill('0') << std::setw(4)
            << std::hex << instruction << "\n";

  // Decode and execute instruction
  m_instruction_decoder->decode(instruction);

  // Increment PC
  m_pc += 2;
}

}  // namespace chip8
