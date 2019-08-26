#include "emulator/interpreter.h"

namespace chip8
{
namespace interpreter
{


void returnFromSubroutine(memory::ProgramCounter& pc, 
                          memory::StackPointer& stack_ptr,
                          memory::Stack& stack)
{
    pc.set(stack[stack_ptr.get()]);
    --stack_ptr;  
}

void jumpToLocation(uint16_t address,
                    memory::ProgramCounter& pc)
{
    pc = address;
}

void callSubroutineAt(uint16_t address,
                      memory::ProgramCounter& pc, 
                      memory::StackPointer& stack_ptr,
                      memory::Stack& stack)
{
    ++stack_ptr;
    stack[stack_ptr.get()] = pc.get();
    pc.set(address);
}


}
}
