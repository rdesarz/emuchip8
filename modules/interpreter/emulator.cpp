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

#include <iomanip>
#include <iostream>
#include <utility>

#include "interpreter/control_unit_impl.h"
#include "interpreter/emulator.h"

namespace chip8 {

Emulator::Emulator(std::istream &rom,
                   std::unique_ptr<DisplayController> display_controller,
                   UserInputController *ui_controller)
    : m_clock([]() { return std::chrono::system_clock::now(); }),
      m_display_controller(std::move(display_controller)),
      m_ui_controller(ui_controller),
      m_registers(16),
      m_ctrl_unit(new ControlUnitImpl(m_pc, m_stack_ptr, m_index_reg,
                                      m_delay_timer_reg, m_sound_timer_reg,
                                      m_stack, m_registers, m_ram,
                                      *m_display_controller, *m_ui_controller)),
      m_instruction_decoder(m_ctrl_unit.get()) {

  // TODO: throw exception if load fails
  loadProgramFromStream(m_ram, rom);

  // The clock cycle will be executed at 500Hz
  m_clock.registerCallback([this]() { this->clockCycle(); }, 500);

  m_pc = 0x200;
  m_stack_ptr = 0x0;
}

void Emulator::update() { m_clock.tick(); }

void Emulator::clockCycle() {
  // Fetch Opcode
  instruction_t instruction{static_cast<uint16_t>(m_ram[m_pc] << 8 | m_ram[m_pc + 1]) };
  // Dump instruction
  std::cout << "Executed instruction: " << std::setfill('0') << std::setw(4) << std::hex << instruction << "\n";
  // Decode and execute instruction
  m_instruction_decoder.decode(instruction);
  // Increment PC
  m_pc+=2;

  // TODO(Romain Desarzens): remove those lines at end of the integration
  // m_display_controller->setPixel(std::rand() % 64, std::rand() % 32, 1);

  // // Check if the key 0 is pressed
  // if (m_ui_controller->getInputState(InputId::INPUT_0) == InputState::ON) {
  //   std::cout << "0 Key pressed" << std::endl;
  //   m_display_controller->clear();
  // }
}

}  // namespace chip8
