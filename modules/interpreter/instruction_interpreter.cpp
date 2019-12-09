#include "interpreter/instruction_interpreter.h"

#include <cstdint>

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

} // namespace chip8