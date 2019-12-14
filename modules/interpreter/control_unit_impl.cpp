#include "interpreter/control_unit_impl.h"

#include <cstdlib>
#include <limits>

namespace chip8 {

ControlUnitImpl::ControlUnitImpl(ProgramCounter& pc, StackPointer& stack_ptr,
                                 MemoryAddressRegister& mem_add_reg,
                                 DelayTimerRegister& delay_timer_reg,
                                 SoundTimerRegister& sound_timer_reg,
                                 Stack& stack,
                                 std::vector<GeneralRegister>& registers,
                                 RAM& ram, DisplayController& display_ctrler,
                                 UserInputController& ui_ctrler)
    : m_pc(pc),
      m_stack_ptr(stack_ptr),
      m_mem_add_reg(mem_add_reg),
      m_delay_timer_reg(delay_timer_reg),
      m_sound_timer_reg(sound_timer_reg),
      m_stack(stack),
      m_registers(registers),
      m_ram(ram),
      m_display_ctrler(display_ctrler),
      m_ui_ctrler(ui_ctrler) {}

void ControlUnitImpl::returnFromSubroutine() {
  m_pc = m_stack[m_stack_ptr];
  --m_stack_ptr;
}

void ControlUnitImpl::jumpToLocation(uint16_t address) { m_pc = address; }

void ControlUnitImpl::callSubroutineAt(uint16_t address) {
  ++m_stack_ptr;
  m_stack[m_stack_ptr] = m_pc;
  m_pc = address;
}

void ControlUnitImpl::skipNextInstructionIfEqual(uint8_t value,
                                                 RegisterId reg) {
  if (m_registers[reg] == value) {
    m_pc += 2;
  }
}

void ControlUnitImpl::skipNextInstructionIfNotEqual(uint8_t value,
                                                    RegisterId reg) {
  if (m_registers[reg] != value) {
    m_pc += 2;
  }
}

void ControlUnitImpl::skipNextInstructionIfRegistersEqual(RegisterId reg_x,
                                                          RegisterId reg_y) {
  if (m_registers[reg_x] == m_registers[reg_y]) {
    m_pc += 2;
  }
}

void ControlUnitImpl::storeInRegister(uint8_t value, RegisterId reg) {
  m_registers[reg] = value;
}

void ControlUnitImpl::addToRegister(uint8_t value, RegisterId reg) {
  m_registers[reg] += value;
}

void ControlUnitImpl::storeRegisterInRegister(RegisterId reg_x,
                                              RegisterId reg_y) {
  m_registers[reg_x] = m_registers[reg_y];
}

void ControlUnitImpl::bitwiseOr(RegisterId reg_x, RegisterId reg_y) {
  m_registers[reg_x] = (m_registers[reg_x] | m_registers[reg_y]);
}

void ControlUnitImpl::bitwiseAnd(RegisterId reg_x, RegisterId reg_y) {
  m_registers[reg_x] = (m_registers[reg_x] & m_registers[reg_y]);
}

void ControlUnitImpl::bitwiseXor(RegisterId reg_x, RegisterId reg_y) {
  m_registers[reg_x] = (m_registers[reg_x] ^ m_registers[reg_y]);
}

void ControlUnitImpl::addRegisterToRegister(RegisterId reg_x,
                                            RegisterId reg_y) {
  std::uint16_t result = static_cast<std::uint16_t>(m_registers[reg_x]) +
                         static_cast<std::uint16_t>(m_registers[reg_y]);

  if (result <= std::numeric_limits<std::uint8_t>::max()) {
    m_registers[reg_x] = static_cast<std::uint8_t>(result);
    m_registers[0xF] = 0;
  } else {
    m_registers[reg_x] = static_cast<std::uint8_t>(result);
    m_registers[0xF] = 1;
  }
}

void ControlUnitImpl::subtractRegisterToRegister(RegisterId reg_x,
                                                 RegisterId reg_y) {
  m_registers[0xF] = m_registers[reg_x] < m_registers[reg_y] ? 1 : 0;
  m_registers[reg_x] = m_registers[reg_x] - m_registers[reg_y];
}

void ControlUnitImpl::shiftRight(RegisterId reg) {
  m_registers[0xF] = (m_registers[reg] & 0b00000001);
  m_registers[reg] = m_registers[reg] >> 1;
}

void ControlUnitImpl::shiftLeft(RegisterId reg) {
  if (m_registers[reg] & 0b10000000) {
    m_registers[0xF] = 1;
  } else {
    m_registers[0xF] = 0;
  }

  m_registers[reg] = m_registers[reg] << 1;
}

void ControlUnitImpl::skipNextInstructionIfRegistersNotEqual(RegisterId reg_x,
                                                             RegisterId reg_y) {
  if (m_registers[reg_x] != m_registers[reg_y]) {
    m_pc += 2;
  }
}

void ControlUnitImpl::storeInMemoryAddressRegister(uint16_t value) {
  m_mem_add_reg = value;
}

void ControlUnitImpl::setPCToV0PlusValue(uint16_t value) {
  m_pc = value + m_registers[0];
}

void ControlUnitImpl::registerEqualRandomValue(uint8_t value, RegisterId reg) {
  srand(time(NULL));
  auto random_value = rand() % 256;
  m_registers[reg] = (value & random_value);
}

void ControlUnitImpl::displayOnScreen(uint16_t n_bytes_to_read,
                                      RegisterId reg_x, RegisterId reg_y) {
  bool any_pixel_modified = false;
  for (uint16_t i = 0; i < n_bytes_to_read; ++i) {
    any_pixel_modified |= m_display_ctrler.setSprite(
        m_registers[reg_x], m_registers[reg_y] + 8 * i,
        makeSprite<uint8_t>(m_ram[m_mem_add_reg + i]));
  }

  if (any_pixel_modified) {
    m_registers[0xF] = 1;
  } else {
    m_registers[0xF] = 0;
  }
}

void ControlUnitImpl::checkIfKeyPressed(RegisterId reg_x) {
  if (m_ui_ctrler.getInputState(toInputId(m_registers[reg_x])) ==
      InputState::ON) {
    m_pc += 2;
  }
}

void ControlUnitImpl::checkIfKeyNotPressed(RegisterId reg_x) {
  if (m_ui_ctrler.getInputState(toInputId(m_registers[reg_x])) !=
      InputState::ON) {
    m_pc += 2;
  }
}

void ControlUnitImpl::waitForKeyPressed(RegisterId reg_x) {
  for (std::size_t index = 0;
       index < static_cast<std::size_t>(InputId::INPUT_SIZE); ++index) {
    if (m_ui_ctrler.getInputState(toInputId(index)) == InputState::ON) {
      m_registers[reg_x] = index;
      return;
    }
  }

  --m_pc;
}

void ControlUnitImpl::setDelayTimerRegister(RegisterId reg_x) {
  m_delay_timer_reg = m_registers[reg_x];
}

void ControlUnitImpl::setSoundTimerRegister(RegisterId reg_x) {
  m_sound_timer_reg = m_registers[reg_x];
}

}  // namespace chip8
