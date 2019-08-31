#include "emulator/interpreter.h"

#include <limits>

using namespace chip8::memory;

namespace chip8
{
namespace interpreter
{


void returnFromSubroutine(ProgramCounter& pc, 
                          StackPointer& stack_ptr,
                          Stack& stack)
{
    pc = stack[stack_ptr];
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
    stack[stack_ptr] = pc;
    pc = address;
}


void skipNextInstructionIfEqual(uint8_t value,
                                std::size_t register_id,
                                const std::vector<GeneralRegister>& registers,
                                ProgramCounter& pc)
{
    if(registers[register_id] == value)
    {
        pc += 2;
    }
}

void skipNextInstructionIfNotEqual(uint8_t value,
                                   std::size_t register_id,
                                   const std::vector<GeneralRegister>& registers,
                                   ProgramCounter& pc)
{
    if(registers[register_id] != value)
    {
        pc += 2;
    }
}

void skipNextInstructionIfRegistersEqual(std::size_t register_1_id,
                                         std::size_t register_2_id,
                                         const std::vector<memory::GeneralRegister>& registers,
                                         memory::ProgramCounter& pc)
{
    if(registers[register_1_id] == registers[register_2_id])
    {
        pc += 2;
    }
}

void storeInRegister(uint8_t value,
                     std::size_t register_id,
                     std::vector<memory::GeneralRegister>& registers)
{
    registers[register_id] = value;
}

void addToRegister(uint8_t value,
                   std::size_t register_id,
                   std::vector<memory::GeneralRegister>& registers)
{
    registers[register_id] += value;
}

void storeRegisterInRegister(std::size_t register_x_id,
                             std::size_t register_y_id,
                             std::vector<memory::GeneralRegister>& registers)
{
    registers[register_x_id] = registers[register_y_id];
}

void bitwiseOr(std::size_t register_x_id,
               std::size_t register_y_id,
               std::vector<memory::GeneralRegister>& registers)
{
    registers[register_x_id] = (registers[register_x_id] | registers[register_y_id]);
}

void bitwiseAnd(std::size_t register_x_id,
                std::size_t register_y_id,
                std::vector<memory::GeneralRegister>& registers)
{
    registers[register_x_id] = (registers[register_x_id] & registers[register_y_id]);
}

void bitwiseXor(std::size_t register_x_id,
                std::size_t register_y_id,
                std::vector<memory::GeneralRegister>& registers)
{
    registers[register_x_id] = (registers[register_x_id] ^ registers[register_y_id]);
}

void addRegisterToRegister(std::size_t register_x_id, 
                           std::size_t register_y_id,
                           std::vector<memory::GeneralRegister>& registers)
{
    std::uint16_t result = static_cast<std::uint16_t>(registers[register_x_id]) 
                             + static_cast<std::uint16_t>(registers[register_y_id]);

    if (result <= std::numeric_limits<std::uint8_t>::max())
    {
        registers[register_x_id] = static_cast<std::uint8_t>(result);
        registers[0xF] = 0; 
    }
    else
    {
        registers[register_x_id] = static_cast<std::uint8_t>(result);
        registers[0xF] = 1; 
    }
}

void subtractRegisterToRegister(std::size_t register_x_id, 
                                std::size_t register_y_id,
                                std::vector<memory::GeneralRegister>& registers)
{
    registers[0xF] = registers[register_x_id] < registers[register_y_id] ? 1 : 0;
    registers[register_x_id] = registers[register_x_id] - registers[register_y_id];
}


void shiftRight(std::size_t register_id,
                std::vector<memory::GeneralRegister>& registers)
{

    registers[0xF] =  (registers[register_id] & 0b00000001);
    registers[register_id] = registers[register_id] >> 1;
}

void shiftLeft(std::size_t register_id,
               std::vector<memory::GeneralRegister>& registers)
{
    if (registers[register_id] & 0b10000000)
    {
        registers[0xF] = 1;
    }
    else
    {
        registers[0xF] = 0;
    }

    registers[register_id] = registers[register_id] << 1;
}

void skipNextInstructionIfRegistersNotEqual(std::size_t register_1_id,
                                            std::size_t register_2_id,
                                            const std::vector<memory::GeneralRegister>& registers,
                                            memory::ProgramCounter& pc)
{
    if(registers[register_1_id] != registers[register_2_id])
    {
        pc += 2;
    }
}

void storeInMemoryAddressRegister(uint16_t value,
                                  MemoryAddressRegister& mem_add_reg)
{
    mem_add_reg = value;
}

}
}
