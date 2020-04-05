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

#ifndef MODULES_INTERPRETER_INSTRUCTION_DECODER_H_
#define MODULES_INTERPRETER_INSTRUCTION_DECODER_H_

#include "units.h"

namespace chip8 {

class ControlUnit;

/*!
 * Return the value of the X register provided in the function
 * @param instruction
 * @return reg x value
 */
register_id_t getRegX(instruction_t instruction);

/*!
 * Return the value of the Y register provided in the function
 * @param instruction
 * @return reg y value
 */
register_id_t getRegY(instruction_t instruction);

/*!
 * Return the last byte contained in the instruction
 * @param instruction
 * @return byte value
 */
byte_t getLastByte(instruction_t instruction);

/*!
 * Return the nibble (4 byte value)contained in the instruction
 * @param instruction
 * @return nibble value
 */
nibble_t getLastNibble(instruction_t instruction);

/*!
 * Return the address (12 bytes value) contained in the instruction
 * @param instruction
 * @return address
 */
address_t getAddress(instruction_t instruction);

/*!
 * Helper class to decode and interpret Chip-8 instruction
 */
class InstructionDecoder {
 public:
  /*!
   * Constructor
   * @param ctrl_unit pointer to control unit implementing the different
   * instructions of the emulator
   */
  explicit InstructionDecoder(ControlUnit* ctrl_unit);

  /*!
   *Decode the instruction and calls the corresponding method in the control
   *unit
   * @param instruction instruction to decode
   */
  void decode(instruction_t instruction);

 private:
  ControlUnit* m_ctrl_unit;
};

}  // namespace chip8
#endif  // MODULES_INTERPRETER_INSTRUCTION_DECODER_H_
