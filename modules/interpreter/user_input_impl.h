#ifndef USER_INPUT_IMPL_H
#define USER_INPUT_IMPL_H

#include <unordered_map>

#include <SDL.h>       

#include "interpreter/user_input.h"

namespace chip8
{

// Map a Chip8 input to a SDL keycode
class SDLInputToKeyMap
{
public:
    SDLInputToKeyMap();
    std::optional<SDL_Keycode> toKey(InputId input_id) const;
private:
    std::unordered_map<InputId, SDL_Keycode> m_input_to_key;
};


// SDL User input controller
class SDLKeyboardUserInputController : public UserInputController
{
public:
    SDLKeyboardUserInputController(const SDLInputToKeyMap& key_to_input_map);
    bool processEvent(const SDL_Event& event);
    virtual std::optional<InputState> getInputState(InputId input_id) override;
private: 
    std::unordered_map<SDL_Keycode, InputState> m_keys_state;
    const SDLInputToKeyMap& m_input_to_key_map;
};

// User input controller for tests
class TestUserInputController : public UserInputController
{
public:
    TestUserInputController();
    bool setInputState(InputId input_id, InputState input_state);
    virtual std::optional<InputState> getInputState(InputId input_id) override;
private: 
    std::unordered_map<InputId, InputState> m_inputs_state;
};

} /// chip8
#endif
