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

#ifndef MODULES_INTERPRETER_USER_INPUT_IMPL_H_
#define MODULES_INTERPRETER_USER_INPUT_IMPL_H_

#include <unordered_map>

#include <SDL.h>

#include "emulator/user_input.h"

namespace chip8 {

// Map a Chip8 input to a SDL keycode
class SDLInputToKeyMap {
 public:
  SDLInputToKeyMap();
  std::optional<SDL_Keycode> toKey(InputId input_id) const;

 private:
  std::unordered_map<InputId, SDL_Keycode> m_input_to_key;
};

// SDL User input controller
class SDLKeyboardUserInputController : public UserInputController {
 public:
  explicit SDLKeyboardUserInputController(
      const SDLInputToKeyMap& key_to_input_map);
  bool processEvent(const SDL_Event& event);
  std::optional<InputState> getInputState(InputId input_id) override;

 private:
  std::unordered_map<SDL_Keycode, InputState> m_keys_state;
  const SDLInputToKeyMap& m_input_to_key_map;
};



}  // namespace chip8
#endif  // MODULES_INTERPRETER_USER_INPUT_IMPL_H_
