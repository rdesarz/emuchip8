#include "emulator/interpreter.h"

using namespace chip8::memory;

namespace chip8
{
namespace interpreter
{


void returnFromSubroutine(ProgramCounter& pc, 
                          StackPointer& stack_ptr,
                          Stack& stack)
{
    pc.set(stack[stack_ptr.get()]);
    --stack_ptr;  
}

void jumpToLocation(uint16_t address,
                    ProgramCounter& pc)
{
    pc = address;
}

void callSubroutineAt(uint16_t address,
                      ProgramCounter& pc, 
                      StackPointer& stack_ptr,
                      Stack& stack)
{
    ++stack_ptr;
    stack[stack_ptr.get()] = pc.get();
    pc.set(address);
}


void skipNextInstructionIfEqual(uint16_t value,
                                std::size_t register_id,
                                std::vector<GeneralRegister> registers,
                                ProgramCounter& pc)
{
    if(registers[register_id].get() == value)
    {
        pc + TwoBytesValue(2);
    }
}


}
}
