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

#include "control_unit.h"
#include "units.h"

namespace chip8 {

register_id_t getRegX(instruction_t instruction);
register_id_t getRegY(instruction_t instruction);
byte_t getLastByte(instruction_t instruction);
nibble_t getLastNibble(instruction_t instruction);
address_t getAddress(instruction_t instruction);

class InstructionDecoder {
 public:
  explicit InstructionDecoder(ControlUnit* ctrl_unit);
  void decode(instruction_t instruction);

 private:
  ControlUnit* m_ctrl_unit;
};

}  // namespace chip8
#endif  // MODULES_INTERPRETER_INSTRUCTION_DECODER_H_