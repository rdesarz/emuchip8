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

#include "interpreter/instruction_decoder.h"

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

// Postfix system instructions
static const uint16_t POSTFIX_CLEAR_DISPLAY = 0x00E0;
static const uint16_t POSTFIX_RET_FROM_SUBROUTINE = 0x00EE;

// Postfix registers
static const uint16_t POSTFIX_STORE_REG_IN_REG = 0x0000;
static const uint16_t POSTFIX_OR = 0x0001;
static const uint16_t POSTFIX_AND = 0x0002;
static const uint16_t POSTFIX_XOR = 0x0003;
static const uint16_t POSTFIX_ADD_REG_TO_REG = 0x0004;
static const uint16_t POSTFIX_SUB_REG_TO_REG = 0x0005;
static const uint16_t POSTFIX_SHR = 0x0006;
static const uint16_t POSTFIX_SUBN = 0x0007;
static const uint16_t POSTFIX_SHL = 0x000E;

// Postfix keys instruction
static const uint16_t POSTFIX_SKIP_NEXT_IF_PRESSED = 0x009E;
static const uint16_t POSTFIX_SKIP_NEXT_IF_NOT_PRESSED = 0x00A1;

// Postfix single registers
static const uint16_t POSTFIX_STORE_DELAY_TIMER = 0x0007;
static const uint16_t POSTFIX_WAIT_FOR_KEY_PRESS = 0x000A;
static const uint16_t POSTFIX_SET_DELAY_TIMER = 0x0015;
static const uint16_t POSTFIX_SET_SOUND_TIMER = 0x0018;
static const uint16_t POSTFIX_ADD_TO_INDEX = 0X001E;
static const uint16_t POSTFIX_SET_INDEX_TO_SPRITE_LOC = 0x0029;
static const uint16_t POSTFIX_STORE_BCD = 0x0033;
static const uint16_t POSTFIX_STORE_REG_IN_MEM = 0x0055;
static const uint16_t POSTFIX_READ_REG_TO_MEM = 0x0065;

InstructionDecoder::InstructionDecoder(ControlUnit* ctrl_unit)
    : m_ctrl_unit(ctrl_unit) {}

void InstructionDecoder::decode(uint16_t instruction) {
  uint16_t prefix = instruction & MASK_PREFIX;

  switch (prefix) {
    case PREFIX_SYS_INST: {
      uint16_t postfix = instruction & MASK_BYTE;
      switch (postfix) {
        case POSTFIX_CLEAR_DISPLAY:
          m_ctrl_unit->clearDisplay();
          break;
        case POSTFIX_RET_FROM_SUBROUTINE:
          m_ctrl_unit->returnFromSubroutine();
          break;
      }
    } break;
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
    case PREFIX_KEYS: {
      uint16_t postfix = instruction & MASK_BYTE;
      switch (postfix) {
        case POSTFIX_SKIP_NEXT_IF_PRESSED:
          m_ctrl_unit->checkIfKeyPressed(RegisterId(instruction & MASK_X_REG));
          break;
        case POSTFIX_SKIP_NEXT_IF_NOT_PRESSED:
          m_ctrl_unit->checkIfKeyNotPressed(
              RegisterId(instruction & MASK_Y_REG));
          break;
      }
      break;
    }
    case PREFIX_SINGLE_REG: {
      uint16_t postfix = instruction & MASK_BYTE;
      switch (postfix) {
        case POSTFIX_STORE_DELAY_TIMER:
          m_ctrl_unit->storeDelayTimer(RegisterId(instruction & MASK_X_REG));
          break;
        case POSTFIX_WAIT_FOR_KEY_PRESS:
          m_ctrl_unit->waitForKeyPressed(RegisterId(instruction & MASK_X_REG));
          break;
        case POSTFIX_SET_DELAY_TIMER:
          m_ctrl_unit->setDelayTimerRegister(
              RegisterId(instruction & MASK_X_REG));
          break;
        case POSTFIX_SET_SOUND_TIMER:
          m_ctrl_unit->setSoundTimerRegister(
              RegisterId(instruction & MASK_X_REG));
          break;
        case POSTFIX_ADD_TO_INDEX:
          m_ctrl_unit->addToIndexReg(RegisterId(instruction & MASK_X_REG));
          break;
        case POSTFIX_SET_INDEX_TO_SPRITE_LOC:
          m_ctrl_unit->setIndexRegToSpriteLocation(
              RegisterId(instruction & MASK_X_REG));
          break;
        case POSTFIX_STORE_BCD:
          m_ctrl_unit->storeBCDRepresentation(
              RegisterId(instruction & MASK_X_REG));
          break;
        case POSTFIX_STORE_REG_IN_MEM:
          m_ctrl_unit->storeMultipleRegister(
              RegisterId(instruction & MASK_X_REG));
          break;
        case POSTFIX_READ_REG_TO_MEM:
          m_ctrl_unit->readMultipleRegister(
              RegisterId(instruction & MASK_X_REG));
          break;
      }
      break;
    }
  }
}
}  // namespace chip8
