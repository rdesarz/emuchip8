#ifndef USER_INPUT_H
#define USER_INPUT_H

namespace chip8
{
namespace userinput
{

// Enum definition
enum class InputState
{
    OFF,
    ON
};

enum class InputId
{
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
    INPUT_F
};

// UserInputController
class UserInputController
{
public:
    UserInputController() = default;
    virtual std::optional<InputState> getInputState(InputId input_id) = 0;
};

} /// userinput
} /// chip8
#endif
