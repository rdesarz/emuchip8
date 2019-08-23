#include <vector>
#include <string>

#include "disassembler/instructions_set.h"

namespace chip8
{


class Disassembler
{
public:
    Disassembler(const std::string& binary_code);
    virtual ~Disassembler(); 
private:
    std::vector<Instruction> m_instructions;

};

} /// chip8
