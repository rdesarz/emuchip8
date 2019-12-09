#include "interpreter/control_unit.h"

#include <cstdlib>
#include <limits>

namespace chip8 {

// Mask
static const uint16_t MASK_PREFIX = 0xF000;
static const uint16_t MASK_POSTFIX = 0x000F;
static const uint16_t MASK_ADDRESS = 0x0FFF;
static const uint16_t MASK_X_REG = 0x0F00;
static const uint16_t MASK_Y_REG = 0x00F0;
static const uint16_t MASK_NIBBLE = 0x000F;
static const uint16_t MASK_BYTE = 0x00FF;

// Prefix
static const uint16_t PREFIX_SYS_INST = 0x0000;
static const uint16_t PREFIX_JUMP = 0x1000;
static const uint16_t PREFIX_CALL = 0x2000;
static const uint16_t PREFIX_SKIP_IF_EQ_VALUE = 0x3000;
static const uint16_t PREFIX_SKIP_IF_NEQ_VALUE = 0x4000;
static const uint16_t PREFIX_SKIP_IF_REG_EQ = 0x5000;
static const uint16_t PREFIX_SET_REG = 0x6000;
static const uint16_t PREFIX_ADD_REG = 0x7000;
static const uint16_t PREFIX_STORE_REG = 0x8000;
static const uint16_t PREFIX_SKIP_IF_REG_NEQ = 0x9000;
static const uint16_t PREFIX_SET_INDEX = 0xA000;
static const uint16_t PREFIX_JUMP_OFFSET = 0xB000;
static const uint16_t PREFIX_RANDOM = 0xC000;
static const uint16_t PREFIX_DISPLAY = 0xD000;
static const uint16_t PREFIX_KEYS = 0xE000;
static const uint16_t PREFIX_SINGLE_REG = 0xF000;

// Postfix
static const uint16_t POSTFIX_STORE_REG_IN_REG = 0x0000;
static const uint16_t POSTFIX_OR = 0x0001;
static const uint16_t POSTFIX_AND = 0x0002;
static const uint16_t POSTFIX_XOR = 0x0003;
static const uint16_t POSTFIX_ADD_REG_TO_REG = 0x0004;
static const uint16_t POSTFIX_SUB_REG_TO_REG = 0x0005;
static const uint16_t POSTFIX_SHR = 0x0006;
static const uint16_t POSTFIX_SUBN = 0x0007;
static const uint16_t POSTFIX_SHL = 0x000E;


InstructionInterpreter::InstructionInterpreter(ControlUnit* ctrl_unit)
    : m_ctrl_unit(ctrl_unit) {}

void InstructionInterpreter::interpret(uint16_t instruction) {
  uint16_t prefix = instruction & MASK_PREFIX;

  switch (prefix) {
    case PREFIX_JUMP:
      m_ctrl_unit->jumpToLocation(instruction & MASK_ADDRESS);
      break;
    case PREFIX_CALL:
      m_ctrl_unit->callSubroutineAt(instruction & MASK_ADDRESS);
      break;
    case PREFIX_SKIP_IF_EQ_VALUE:
      m_ctrl_unit->skipNextInstructionIfEqual(
          instruction & MASK_X_REG, RegisterId(instruction & MASK_BYTE));
      break;
    case PREFIX_SKIP_IF_NEQ_VALUE:
      m_ctrl_unit->skipNextInstructionIfNotEqual(
          instruction & MASK_X_REG, RegisterId(instruction & MASK_BYTE));
      break;
    case PREFIX_SKIP_IF_REG_EQ:
      m_ctrl_unit->skipNextInstructionIfRegistersEqual(
          RegisterId(instruction & MASK_X_REG),
          RegisterId(instruction & MASK_Y_REG));
      break;
    case PREFIX_SET_REG:
      m_ctrl_unit->storeInRegister(instruction & MASK_BYTE,
                                   RegisterId(instruction & MASK_X_REG));
      break;
    case PREFIX_ADD_REG:
      m_ctrl_unit->addToRegister(instruction & MASK_BYTE,
                                 RegisterId(instruction & MASK_X_REG));
      break;
    case PREFIX_SKIP_IF_REG_NEQ:
      m_ctrl_unit->skipNextInstructionIfRegistersNotEqual(
          RegisterId(instruction & MASK_X_REG),
          RegisterId(instruction & MASK_Y_REG));
      break;
    case PREFIX_SET_INDEX:
      m_ctrl_unit->storeInMemoryAddressRegister(instruction & MASK_ADDRESS);
      break;
    case PREFIX_JUMP_OFFSET:
      m_ctrl_unit->setPCToV0PlusValue(instruction & MASK_ADDRESS);
      break;
    case PREFIX_RANDOM:
      m_ctrl_unit->registerEqualRandomValue(
          instruction & MASK_X_REG, RegisterId(instruction & MASK_BYTE));
      break;
    case PREFIX_DISPLAY:
      m_ctrl_unit->displayOnScreen(instruction & MASK_NIBBLE,
                                   RegisterId(instruction & MASK_X_REG),
                                   RegisterId(instruction & MASK_Y_REG));
      break;
    case PREFIX_STORE_REG: {
      uint16_t postfix = instruction & MASK_POSTFIX;
      switch (postfix) {
        case POSTFIX_STORE_REG_IN_REG:
          m_ctrl_unit->storeRegisterInRegister(
              RegisterId(instruction & MASK_X_REG),
              RegisterId(instruction & MASK_Y_REG));
          break;
        case POSTFIX_OR:
          m_ctrl_unit->bitwiseOr(RegisterId(instruction & MASK_X_REG),
                                 RegisterId(instruction & MASK_Y_REG));
          break;
        case POSTFIX_AND:
          m_ctrl_unit->bitwiseAnd(RegisterId(instruction & MASK_X_REG),
                                  RegisterId(instruction & MASK_Y_REG));
          break;
        case POSTFIX_XOR:
          m_ctrl_unit->bitwiseXor(RegisterId(instruction & MASK_X_REG),
                                  RegisterId(instruction & MASK_Y_REG));
          break;
        case POSTFIX_ADD_REG_TO_REG:
          m_ctrl_unit->addRegisterToRegister(
              RegisterId(instruction & MASK_X_REG),
              RegisterId(instruction & MASK_Y_REG));
          break;
        case POSTFIX_SUB_REG_TO_REG:
          m_ctrl_unit->subtractRegisterToRegister(
              RegisterId(instruction & MASK_X_REG),
              RegisterId(instruction & MASK_Y_REG));
          break;
        case POSTFIX_SHR:
          m_ctrl_unit->shiftRight(RegisterId(instruction & MASK_X_REG));
          break;
        case POSTFIX_SUBN:
          m_ctrl_unit->subtractRegisterToRegister(
              RegisterId(instruction & MASK_Y_REG),
              RegisterId(instruction & MASK_X_REG));
          break;
        case POSTFIX_SHL:
          m_ctrl_unit->shiftLeft(RegisterId(instruction & MASK_X_REG));
          break;
      }
      break;
    }

    case PREFIX_SYS_INST:
      // TODO(Romain Desarzens) : implement
      break;
    case PREFIX_KEYS:
      // TODO(Romain Desarzens) : implement
      break;
    case PREFIX_SINGLE_REG:
      // TODO(Romain Desarzens) : implement
      break;
  }
}

ControlUnitImpl::ControlUnitImpl(ProgramCounter& pc, StackPointer& stack_ptr,
                                 MemoryAddressRegister& mem_add_reg,
                                 Stack& stack,
                                 std::vector<GeneralRegister>& registers,
                                 RAM& ram, DisplayController& display_ctrler,
                                 UserInputController& ui_ctrler)
    : m_pc(pc),
      m_stack_ptr(stack_ptr),
      m_mem_add_reg(mem_add_reg),
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

}  // namespace chip8
