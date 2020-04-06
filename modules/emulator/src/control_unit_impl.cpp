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

// std
#include <limits>

#include "emulator/control_unit_impl.h"

namespace chip8 {

ControlUnitImpl::ControlUnitImpl(
    ProgramCounter& pc, StackPointer& stack_ptr, IndexRegister& mem_add_reg,
    DelayTimerRegister& delay_timer_reg, SoundTimerRegister& sound_timer_reg,
    Stack& stack, std::vector<GeneralRegister>& registers, RAM& ram,
    DisplayController& display_ctrler, UserInputController& ui_ctrler)
    : m_pc(pc),
      m_stack_ptr(stack_ptr),
      m_index_reg(mem_add_reg),
      m_delay_timer_reg(delay_timer_reg),
      m_sound_timer_reg(sound_timer_reg),
      m_stack(stack),
      m_registers(registers),
      m_ram(ram),
      m_display_ctrler(display_ctrler),
      m_ui_ctrler(ui_ctrler),
      m_rand_num_generator(0, 255) {}

void ControlUnitImpl::clearDisplay() { m_display_ctrler.clear(); }

void ControlUnitImpl::returnFromSubroutine() {
  m_pc = m_stack[m_stack_ptr];
  --m_stack_ptr;
}

void ControlUnitImpl::jumpToLocation(address_t address) { m_pc = address - 2; }

void ControlUnitImpl::callSubroutineAt(address_t address) {
  ++m_stack_ptr;
  m_stack[m_stack_ptr] = m_pc;
  m_pc = address - 2;
}

void ControlUnitImpl::skipNextInstructionIfEqual(byte_t value,
                                                 register_id_t reg) {
  if (m_registers[reg] == value) {
    m_pc += 2;
  }
}

void ControlUnitImpl::skipNextInstructionIfNotEqual(byte_t value,
                                                    register_id_t reg) {
  if (m_registers[reg] != value) {
    m_pc += 2;
  }
}

void ControlUnitImpl::skipNextInstructionIfRegistersEqual(register_id_t reg_x,
                                                          register_id_t reg_y) {
  if (m_registers[reg_x] == m_registers[reg_y]) {
    m_pc += 2;
  }
}

void ControlUnitImpl::storeInRegister(byte_t value, register_id_t reg) {
  m_registers[reg] = value;
}

void ControlUnitImpl::addToRegister(byte_t value, register_id_t reg) {
  m_registers[reg] += value;
}

void ControlUnitImpl::storeRegisterInRegister(register_id_t reg_x,
                                              register_id_t reg_y) {
  m_registers[reg_x] = m_registers[reg_y];
}

void ControlUnitImpl::bitwiseOr(register_id_t reg_x, register_id_t reg_y) {
  m_registers[reg_x] = (m_registers[reg_x] | m_registers[reg_y]);
}

void ControlUnitImpl::bitwiseAnd(register_id_t reg_x, register_id_t reg_y) {
  m_registers[reg_x] = (m_registers[reg_x] & m_registers[reg_y]);
}

void ControlUnitImpl::bitwiseXor(register_id_t reg_x, register_id_t reg_y) {
  m_registers[reg_x] = (m_registers[reg_x] ^ m_registers[reg_y]);
}

void ControlUnitImpl::addRegisterToRegister(register_id_t reg_x,
                                            register_id_t reg_y) {
  std::uint16_t result = static_cast<std::uint16_t>(m_registers[reg_x]) +
                         static_cast<std::uint16_t>(m_registers[reg_y]);

  if (result <= std::numeric_limits<std::uint8_t>::max()) {
    m_registers[0xF] = 0;
  } else {
    m_registers[0xF] = 1;
  }

  m_registers[reg_x] = static_cast<std::uint8_t>(result);
}

void ControlUnitImpl::subtractRegYToRegX(register_id_t reg_x,
                                         register_id_t reg_y) {
  m_registers[0xF] = m_registers[reg_x] > m_registers[reg_y] ? 1 : 0;
  m_registers[reg_x] = m_registers[reg_x] - m_registers[reg_y];
}

void ControlUnitImpl::subtractRegXToRegY(register_id_t reg_x,
                                         register_id_t reg_y) {
  m_registers[0xF] = m_registers[reg_y] > m_registers[reg_x] ? 1 : 0;
  m_registers[reg_x] = m_registers[reg_y] - m_registers[reg_x];
}

void ControlUnitImpl::shiftRight(register_id_t reg) {
  m_registers[0xF] = (m_registers[reg] & 0b00000001);
  m_registers[reg] = m_registers[reg] >> 1;
}

void ControlUnitImpl::shiftLeft(register_id_t reg) {
  if (m_registers[reg] & 0b10000000) {
    m_registers[0xF] = 1;
  } else {
    m_registers[0xF] = 0;
  }

  m_registers[reg] = m_registers[reg] << 1;
}

void ControlUnitImpl::skipNextInstructionIfRegistersNotEqual(
    register_id_t reg_x, register_id_t reg_y) {
  if (m_registers[reg_x] != m_registers[reg_y]) {
    m_pc += 2;
  }
}

void ControlUnitImpl::storeInMemoryAddressRegister(address_t value) {
  m_index_reg = value;
}

void ControlUnitImpl::setPCToV0PlusValue(address_t value) {
  m_pc = value + m_registers[0] - 2;
}

void ControlUnitImpl::registerEqualRandomValue(uint8_t value,
                                               register_id_t reg) {
  m_registers[reg] = (value & m_rand_num_generator.generateNumber());
}

void ControlUnitImpl::displayOnScreen(uint16_t n_bytes_to_read,
                                      register_id_t reg_x,
                                      register_id_t reg_y) {
  bool any_pixel_modified = false;
  for (uint16_t i = 0; i < n_bytes_to_read; ++i) {
    any_pixel_modified |= m_display_ctrler.setSprite(
        column_t(m_registers[reg_x]), row_t(m_registers[reg_y] + i),
        byteToSprite(m_ram[m_index_reg + i]));
  }

  if (any_pixel_modified) {
    m_registers[0xF] = 1;
  } else {
    m_registers[0xF] = 0;
  }
}

void ControlUnitImpl::storeDelayTimer(register_id_t reg_x) {
  m_registers[reg_x] = m_delay_timer_reg;
}

void ControlUnitImpl::skipNextInstructionIfKeyPressed(register_id_t reg_x) {
  if (m_ui_ctrler.getInputState(toInputId(m_registers[reg_x])) ==
      InputState::ON) {
    m_pc += 2;
  }
}

void ControlUnitImpl::skipNextInstructionIfKeyNotPressed(register_id_t reg_x) {
  if (m_ui_ctrler.getInputState(toInputId(m_registers[reg_x])) ==
      InputState::OFF) {
    m_pc += 2;
  }
}

void ControlUnitImpl::waitForKeyPressed(register_id_t reg_x) {
  for (std::size_t index = 0;
       index < static_cast<std::size_t>(InputId::INPUT_SIZE); ++index) {
    if (m_ui_ctrler.getInputState(toInputId(index)) == InputState::ON) {
      m_registers[reg_x] = index;
      return;
    }
  }

  m_pc -= 2;
}

void ControlUnitImpl::setDelayTimerRegister(register_id_t reg_x) {
  m_delay_timer_reg = m_registers[reg_x];
}

void ControlUnitImpl::setSoundTimerRegister(register_id_t reg_x) {
  m_sound_timer_reg = m_registers[reg_x];
}

void ControlUnitImpl::addToIndexReg(register_id_t reg_x) {
  m_index_reg += m_registers[reg_x];
}

void ControlUnitImpl::setIndexRegToSpriteLocation(register_id_t reg_x) {
  m_index_reg = SPRITE_OFFSET * m_registers[reg_x];
}

void ControlUnitImpl::storeBCDRepresentation(register_id_t reg_x) {
  m_ram[m_index_reg + 2] = m_registers[reg_x] % 10;
  m_ram[m_index_reg + 1] =
      (m_registers[reg_x] % 100 - m_ram[m_index_reg + 2]) / 10;
  m_ram[m_index_reg] = (m_registers[reg_x] % 1000 -
                        m_ram[m_index_reg + 1] * 10 - m_ram[m_index_reg + 2]) /
                       100;
}

void ControlUnitImpl::storeMultipleRegister(register_id_t reg_x) {
  for (register_id_t reg_id(0); reg_id <= reg_x; ++reg_id) {
    m_ram[m_index_reg + reg_id] = m_registers[reg_id];
  }
}

void ControlUnitImpl::readMultipleRegister(register_id_t reg_x) {
  for (register_id_t reg_id(0); reg_id <= reg_x; ++reg_id) {
    m_registers[reg_id] = m_ram[reg_id + m_index_reg];
  }
}

}  // namespace chip8
