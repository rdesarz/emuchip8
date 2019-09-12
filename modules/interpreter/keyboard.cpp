#include "interpreter/keyboard.h"


namespace chip8
{
namespace inputs
{

KeyState Keyboard::getKeyState(KeyId key_id)
{
    return m_keys_state[static_cast<std::size_t>(key_id)];
}

void Keyboard::update(const std::array<KeyState, static_cast<std::size_t>(KeyId::N_KEYS)>& input)
{
    m_keys_state = input;
}

}
}
