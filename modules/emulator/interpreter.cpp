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
}
}
