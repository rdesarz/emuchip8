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

#ifndef MODULES_INTERPRETER_CONTROL_UNIT_H_
#define MODULES_INTERPRETER_CONTROL_UNIT_H_

// std
#include <vector>

#include "emulator/units.h"

namespace chip8 {

BOOST_STRONG_TYPEDEF(
    std::uint16_t,
    register_id_t)  ///< Stores the id of a register [reg 0,...,reg F]

/*!
 * @class ControlUnit
 * Interface with all the methods to reproduce Chip-8 instructions
 */
class ControlUnit {
 public:
  /*!
   * CLS - reset all pixels of the display.
   */
  virtual void clearDisplay() = 0;

  /*!
   * RET - jump back to the instruction address that was stored in the top of
   * the stack
   */
  virtual void returnFromSubroutine() = 0;

  /*!
   * JP - jump to instruction stored at address
   * @param address memory address to reach
   */
  virtual void jumpToLocation(address_t address) = 0;

  /*!
   * CALL - call a subroutine at address and store the current PC value on the
   * stack
   * @param address
   */
  virtual void callSubroutineAt(address_t address) = 0;

  /*!
   * SE - Skip next instruction if value = registers[reg]
   * @param value
   * @param reg id of the register
   */
  virtual void skipNextInstructionIfEqual(byte_t value, register_id_t reg) = 0;

  /*!
   * SNE - Skip next instruction if value != registers[reg]
   * @param value
   * @param reg id of the register
   */
  virtual void skipNextInstructionIfNotEqual(byte_t value,
                                             register_id_t reg) = 0;

  /*!
   * SE - Skip next instruction if register X equals to register Y
   * @param reg_x id of register X
   * @param reg_y id of the register Y
   */
  virtual void skipNextInstructionIfRegistersEqual(register_id_t reg_x,
                                                   register_id_t reg_y) = 0;

  /*!
   * LD - Store value in register
   * @param value
   * @param reg id of the register in which to store the value
   */
  virtual void storeInRegister(byte_t value, register_id_t reg) = 0;

  /*!
   * ADD - Add value to register
   * @param value
   * @param reg id of the register to which the value is added
   */
  virtual void addToRegister(byte_t value, register_id_t reg) = 0;

  /*!
   * LD - Store register Y in register X
   * @param reg_x id of register X
   * @param reg_y id of register Y
   */
  virtual void storeRegisterInRegister(register_id_t reg_x,
                                       register_id_t reg_y) = 0;

  /*!
   * OR - Store result of bitwise OR between register X and register Y in
   * register X
   * @param reg_x id of register x
   * @param reg_y id of register y
   */
  virtual void bitwiseOr(register_id_t reg_x, register_id_t reg_y) = 0;

  /*!
   * AND - Store result of bitwise AND between register X and register Y in
   * register X
   * @param reg_x id of register x
   * @param reg_y id of register y
   */
  virtual void bitwiseAnd(register_id_t reg_x, register_id_t reg_y) = 0;

  /*!
   * XOR - Store result of bitwise XOR between register X and register Y in
   * register X
   * @param reg_x id of register x
   * @param reg_y id of register y
   */
  virtual void bitwiseXor(register_id_t reg_x, register_id_t reg_y) = 0;

  /*!
   * ADD - Add register Y to register X
   * @param reg_x id of register X
   * @param reg_y id of register Y
   */
  virtual void addRegisterToRegister(register_id_t reg_x,
                                     register_id_t reg_y) = 0;

  /*!
   * SUB - Subtract register Y to register X
   * @param reg_x id of register X
   * @param reg_y id of register Y
   */
  virtual void subtractRegYToRegX(register_id_t reg_x, register_id_t reg_y) = 0;

  /*!
   * SUBN - Subtract register X to register Y
   * @param reg_x id of register X
   * @param reg_y id of register Y
   */
  virtual void subtractRegXToRegY(register_id_t reg_x, register_id_t reg_y) = 0;

  /*!
   * SHR - Shift register to the right
   * @param reg id of the register to shift
   */
  virtual void shiftRight(register_id_t reg) = 0;

  /*!
   * SHL - Shift register to the left
   * @param reg id of the register to shift
   */
  virtual void shiftLeft(register_id_t reg) = 0;

  /*!
   * SNE - Skip next instruction if register X is different from register Y
   * @param reg_x id of register X
   * @param reg_y id of the register Y
   */
  virtual void skipNextInstructionIfRegistersNotEqual(register_id_t reg_x,
                                                      register_id_t reg_y) = 0;

  /*!
   * LD - Store value in memory address register
   * @param value address to store
   */
  virtual void storeInMemoryAddressRegister(address_t value) = 0;

  /*!
   * JP - Set the program counter to reg 0 + value
   * @param value
   */
  virtual void setPCToV0PlusValue(address_t value) = 0;

  /*!
   * RND - Perform a bitwise XOR between value and a random value and to it in the
   * indicated register
   * @param value
   * @param reg id of the register in which to store the result of the operation
   */
  virtual void registerEqualRandomValue(uint8_t value, register_id_t reg) = 0;

  /*!
   * DRW - Display n_bytes starting from the address stored in the memory address
   * register at coordinates indicated by register X and register Y
   * @param n_bytes_to_read number of bytes to display (equivalent to sprites)
   * @param reg_x id of the register X
   * @param reg_y id of the register Y
   */
  virtual void displayOnScreen(uint16_t n_bytes_to_read, register_id_t reg_x,
                               register_id_t reg_y) = 0;

  /*!
   * LD - Store the delay timer value in register X
   * @param reg_x id of the register X
   */
  virtual void storeDelayTimer(register_id_t reg_x) = 0;

  /*!
   * SKP - Skip next instruction if the key with value stored in register X is
   * pressed.
   * @param reg_x id of the register X
   */
  virtual void skipNextInstructionIfKeyPressed(register_id_t reg_x) = 0;

  /*!
   * SKNP - Skip next instruction if the key with value stored in register X is not
   * pressed.
   * @param reg_x id of the register X
   */
  virtual void skipNextInstructionIfKeyNotPressed(register_id_t reg_x) = 0;

  /*!
   * LD - Wait for a key to be pressed. Store the value of the pressed key in
   * register X
   * @param reg_x id of register X
   */
  virtual void waitForKeyPressed(register_id_t reg_x) = 0;

  /*!
   * Set the value of delay timer to value of register X
   * @param reg_x id of register X
   */
  virtual void setDelayTimerRegister(register_id_t reg_x) = 0;

  /*!
   * Set the value of sound timer to value of register X
   * @param reg_x id of register Y
   */
  virtual void setSoundTimerRegister(register_id_t reg_x) = 0;

  /*!
   * Add to memory index register the value of register X
   * @param reg_x address of register X
   */
  virtual void addToIndexReg(register_id_t reg_x) = 0;

  /*!
   * Set the value of the index register to the memory address of hexadecimal
   * character corresponding to register x
   * @param reg_x id of register X
   */
  virtual void setIndexRegToSpriteLocation(register_id_t reg_x) = 0;

  /*!
   * Store the BCD representation of register X in memory starting at memory
   * index (hundreds, tens and digit)
   * @param reg_x id of register X
   */
  virtual void storeBCDRepresentation(register_id_t reg_x) = 0;

  /*!
   * Store the value of register 0 to register X in memory starting at the
   * address indicated by the memory address register
   * @param reg_x id of register X
   */
  virtual void storeMultipleRegister(register_id_t reg_x) = 0;

  /*!
   * Store to register 0 to register X the value of memory starting at the
   * address indicated by the memory address register
   * @param reg_x id of register X
   */
  virtual void readMultipleRegister(register_id_t reg_x) = 0;
};

}  // namespace chip8
#endif  // MODULES_INTERPRETER_CONTROL_UNIT_H_
