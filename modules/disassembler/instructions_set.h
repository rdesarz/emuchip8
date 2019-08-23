#include <unordered_map>

namespace chip8
{


struct Instruction
{
    std::uint8_t value = 0;
    std::string description = ""; 
};

extern const std::unordered_map<std::string, Instruction> instructions_set; 


}
