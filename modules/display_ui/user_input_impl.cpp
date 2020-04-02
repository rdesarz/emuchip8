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

#include "user_input_impl.h"

namespace chip8 {

SDLInputToKeyMap::SDLInputToKeyMap() {
  // TODO(Romain Desarzens) : make the mapping between keys and
  // input dynamic
  m_input_to_key[InputId::INPUT_0] = SDLK_x;
  m_input_to_key[InputId::INPUT_1] = SDLK_1;
  m_input_to_key[InputId::INPUT_2] = SDLK_2;
  m_input_to_key[InputId::INPUT_3] = SDLK_3;
  m_input_to_key[InputId::INPUT_4] = SDLK_q;
  m_input_to_key[InputId::INPUT_5] = SDLK_w;
  m_input_to_key[InputId::INPUT_6] = SDLK_e;
  m_input_to_key[InputId::INPUT_7] = SDLK_a;
  m_input_to_key[InputId::INPUT_8] = SDLK_s;
  m_input_to_key[InputId::INPUT_9] = SDLK_d;
  m_input_to_key[InputId::INPUT_A] = SDLK_y;
  m_input_to_key[InputId::INPUT_B] = SDLK_c;
  m_input_to_key[InputId::INPUT_C] = SDLK_4;
  m_input_to_key[InputId::INPUT_D] = SDLK_r;
  m_input_to_key[InputId::INPUT_E] = SDLK_f;
  m_input_to_key[InputId::INPUT_F] = SDLK_v;
}

std::optional<SDL_Keycode> SDLInputToKeyMap::toKey(InputId input_id) const {
  try {
    return m_input_to_key.at(input_id);
  } catch (std::out_of_range& e) {
    return std::optional<SDL_Keycode>();
  }
}

SDLKeyboardUserInputController::SDLKeyboardUserInputController(
    const SDLInputToKeyMap& input_to_key_map)
    : m_input_to_key_map(input_to_key_map) {
  m_keys_state[SDLK_x] = InputState::OFF;
  m_keys_state[SDLK_1] = InputState::OFF;
  m_keys_state[SDLK_2] = InputState::OFF;
  m_keys_state[SDLK_3] = InputState::OFF;
  m_keys_state[SDLK_q] = InputState::OFF;
  m_keys_state[SDLK_w] = InputState::OFF;
  m_keys_state[SDLK_e] = InputState::OFF;
  m_keys_state[SDLK_a] = InputState::OFF;
  m_keys_state[SDLK_s] = InputState::OFF;
  m_keys_state[SDLK_d] = InputState::OFF;
  m_keys_state[SDLK_y] = InputState::OFF;
  m_keys_state[SDLK_c] = InputState::OFF;
  m_keys_state[SDLK_4] = InputState::OFF;
  m_keys_state[SDLK_r] = InputState::OFF;
  m_keys_state[SDLK_f] = InputState::OFF;
  m_keys_state[SDLK_v] = InputState::OFF;
}

bool SDLKeyboardUserInputController::processEvent(const SDL_Event& event) {
  if (event.type == SDL_KEYUP) {
    try {
      m_keys_state.at(event.key.keysym.sym) = InputState::OFF;
      return true;
    } catch (std::out_of_range&) {
      return false;
    }
  } else if (event.type == SDL_KEYDOWN) {
    try {
      m_keys_state.at(event.key.keysym.sym) = InputState::ON;
      return true;
    } catch (std::out_of_range&) {
      return false;
    }
  } else {
    return false;
  }
}

std::optional<InputState> SDLKeyboardUserInputController::getInputState(
    InputId input_id) {
  auto key_id = m_input_to_key_map.toKey(input_id);
  if (key_id) {
    return m_keys_state.at(*key_id);
  } else {
    return std::optional<InputState>();
  }
}



}  // namespace chip8
