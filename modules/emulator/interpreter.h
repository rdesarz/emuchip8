#ifndef CHIP_INTERPRETER_H
#define CHIP_INTERPRETER_H
#include "emulator/memory.h"
 
namespace chip8
{
namespace interpreter
{


void returnFromSubroutine(memory::ProgramCounter& pc, 
                          memory::StackPointer& stack_ptr,
                          memory::Stack& stack);

void jumpToLocation(uint16_t address,
                    memory::ProgramCounter& pc);

void callSubroutineAt(uint16_t address,
                      memory::ProgramCounter& pc, 
                      memory::StackPointer& stack_ptr,
                      memory::Stack& stack);

} /// interpreter
} /// chip8
#endif
