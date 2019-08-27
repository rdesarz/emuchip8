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

void skipNextInstructionIfEqual(uint16_t value,
                                std::size_t register_id,
                                std::vector<memory::GeneralRegister> registers,
                                memory::ProgramCounter& pc);

void skipNextInstructionIfNotEqual(uint16_t value,
                                std::size_t register_id,
                                std::vector<memory::GeneralRegister> registers,
                                memory::ProgramCounter& pc);

} /// interpreter
} /// chip8
#endif
