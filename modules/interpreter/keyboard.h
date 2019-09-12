#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <array>
 
namespace chip8
{
namespace inputs
{

enum class KeyId
{
    ZERO, ONE, TWO, THREE, FOUR, FIVE,
    SIX, SEVEN, EIGHT, NINE, 
    A, B, C, D, E, F,
    N_KEYS
};

enum class KeyState
{
   UP,
   DOWN
};

class Keyboard
{
public:
    KeyState getKeyState(KeyId key_id);
    void update(const std::array<KeyState, static_cast<std::size_t>(KeyId::N_KEYS)>& input);
private:
    std::array<KeyState, static_cast<std::size_t>(KeyId::N_KEYS) > m_keys_state;
};



} /// inputs
} /// chip8
#endif
