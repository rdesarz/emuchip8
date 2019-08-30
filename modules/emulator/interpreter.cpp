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


void skipNextInstructionIfEqual(uint8_t value,
                                std::size_t register_id,
                                const std::vector<GeneralRegister>& registers,
                                ProgramCounter& pc)
{
    if(registers[register_id].get() == value)
    {
        pc + 2;
    }
}

void skipNextInstructionIfNotEqual(uint8_t value,
                                   std::size_t register_id,
                                   const std::vector<GeneralRegister>& registers,
                                   ProgramCounter& pc)
{
    if(registers[register_id].get() != value)
    {
        pc + 2;
    }
}

void skipNextInstructionIfRegistersEqual(std::size_t register_1_id,
                                         std::size_t register_2_id,
                                         const std::vector<memory::GeneralRegister>& registers,
                                         memory::ProgramCounter& pc)
{
    if(registers[register_1_id].get() == registers[register_2_id].get())
    {
        pc + 2;
    }

}

void storeInRegister(uint8_t value,
                     std::size_t register_id,
                     std::vector<memory::GeneralRegister>& registers)
{
    registers[register_id].set(value);
}

void addToRegister(uint8_t value,
                   std::size_t register_id,
                   std::vector<memory::GeneralRegister>& registers)
{
    registers[register_id] += value;
}

}
}
