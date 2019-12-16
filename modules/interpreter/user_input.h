/** 
 * Copyright (c) Romain Desarzens
 * All rights reserved. 
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef MODULES_INTERPRETER_USER_INPUT_H_
#define MODULES_INTERPRETER_USER_INPUT_H_

#include <optional>

namespace chip8 {

// Enum definition
enum class InputState { OFF, ON };

enum class InputId {
  INPUT_ERROR = -1,
  INPUT_0,
  INPUT_1,
  INPUT_2,
  INPUT_3,
  INPUT_4,
  INPUT_5,
  INPUT_6,
  INPUT_7,
  INPUT_8,
  INPUT_9,
  INPUT_A,
  INPUT_B,
  INPUT_C,
  INPUT_D,
  INPUT_E,
  INPUT_F,
  INPUT_SIZE
};

// UserInputController
class UserInputController {
 public:
  UserInputController() = default;
  virtual std::optional<InputState> getInputState(InputId input_id) = 0;
};

template <typename T>
InputId toInputId(T value) {
  switch (value) {
    case 0x0:
      return InputId::INPUT_0;
    case 0x1:
      return InputId::INPUT_1;
    case 0x2:
      return InputId::INPUT_2;
    case 0x3:
      return InputId::INPUT_3;
    case 0x4:
      return InputId::INPUT_4;
    case 0x5:
      return InputId::INPUT_5;
    case 0x6:
      return InputId::INPUT_6;
    case 0x7:
      return InputId::INPUT_7;
    case 0x8:
      return InputId::INPUT_8;
    case 0x9:
      return InputId::INPUT_9;
    case 0xA:
      return InputId::INPUT_A;
    case 0xB:
      return InputId::INPUT_B;
    case 0xC:
      return InputId::INPUT_C;
    case 0xD:
      return InputId::INPUT_D;
    case 0xE:
      return InputId::INPUT_E;
    case 0xF:
      return InputId::INPUT_F;
    default:
      return InputId::INPUT_ERROR;
  }
}

}  /// namespace chip8
#endif  // MODULES_INTERPRETER_USER_INPUT_H_
