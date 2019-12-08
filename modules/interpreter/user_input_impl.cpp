#include "interpreter/user_input_impl.h"

namespace chip8 {

SDLInputToKeyMap::SDLInputToKeyMap() {
  // TODO(Romain Desarzens) : make the mapping between keys and
  // input dynamic
  m_input_to_key[InputId::INPUT_0] = SDLK_0;
  m_input_to_key[InputId::INPUT_1] = SDLK_1;
  m_input_to_key[InputId::INPUT_2] = SDLK_2;
  m_input_to_key[InputId::INPUT_3] = SDLK_3;
  m_input_to_key[InputId::INPUT_4] = SDLK_4;
  m_input_to_key[InputId::INPUT_5] = SDLK_5;
  m_input_to_key[InputId::INPUT_6] = SDLK_6;
  m_input_to_key[InputId::INPUT_7] = SDLK_7;
  m_input_to_key[InputId::INPUT_8] = SDLK_8;
  m_input_to_key[InputId::INPUT_9] = SDLK_9;
  m_input_to_key[InputId::INPUT_A] = SDLK_q;
  m_input_to_key[InputId::INPUT_B] = SDLK_w;
  m_input_to_key[InputId::INPUT_C] = SDLK_e;
  m_input_to_key[InputId::INPUT_D] = SDLK_r;
  m_input_to_key[InputId::INPUT_E] = SDLK_t;
  m_input_to_key[InputId::INPUT_F] = SDLK_z;
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
  m_keys_state[SDLK_0] = InputState::OFF;
  m_keys_state[SDLK_1] = InputState::OFF;
  m_keys_state[SDLK_2] = InputState::OFF;
  m_keys_state[SDLK_3] = InputState::OFF;
  m_keys_state[SDLK_4] = InputState::OFF;
  m_keys_state[SDLK_5] = InputState::OFF;
  m_keys_state[SDLK_6] = InputState::OFF;
  m_keys_state[SDLK_7] = InputState::OFF;
  m_keys_state[SDLK_8] = InputState::OFF;
  m_keys_state[SDLK_9] = InputState::OFF;
  m_keys_state[SDLK_q] = InputState::OFF;
  m_keys_state[SDLK_w] = InputState::OFF;
  m_keys_state[SDLK_e] = InputState::OFF;
  m_keys_state[SDLK_r] = InputState::OFF;
  m_keys_state[SDLK_t] = InputState::OFF;
  m_keys_state[SDLK_z] = InputState::OFF;
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

TestUserInputController::TestUserInputController() {
  m_inputs_state[InputId::INPUT_0] = InputState::OFF;
  m_inputs_state[InputId::INPUT_1] = InputState::OFF;
  m_inputs_state[InputId::INPUT_2] = InputState::OFF;
  m_inputs_state[InputId::INPUT_3] = InputState::OFF;
  m_inputs_state[InputId::INPUT_4] = InputState::OFF;
  m_inputs_state[InputId::INPUT_5] = InputState::OFF;
  m_inputs_state[InputId::INPUT_6] = InputState::OFF;
  m_inputs_state[InputId::INPUT_7] = InputState::OFF;
  m_inputs_state[InputId::INPUT_8] = InputState::OFF;
  m_inputs_state[InputId::INPUT_9] = InputState::OFF;
  m_inputs_state[InputId::INPUT_A] = InputState::OFF;
  m_inputs_state[InputId::INPUT_B] = InputState::OFF;
  m_inputs_state[InputId::INPUT_C] = InputState::OFF;
  m_inputs_state[InputId::INPUT_D] = InputState::OFF;
  m_inputs_state[InputId::INPUT_E] = InputState::OFF;
  m_inputs_state[InputId::INPUT_F] = InputState::OFF;
}

bool TestUserInputController::setInputState(InputId input_id,
                                            InputState input_state) {
  try {
    m_inputs_state.at(input_id) = input_state;
    return true;
  } catch (std::out_of_range& e) {
    return false;
  }
}

std::optional<InputState> TestUserInputController::getInputState(
    InputId input_id) {
  try {
    return m_inputs_state.at(input_id);
  } catch (std::out_of_range& e) {
    std::optional<InputState>();
  }
}

}  /// namespace chip8
