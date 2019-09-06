#include "interpreter/control_unit.h"

#include <limits>
#include <cstdlib>

using namespace chip8::memory;

namespace chip8
{
namespace ctrlunit
{



ControlUnit::ControlUnit(memory::ProgramCounter& pc,
                memory::StackPointer& stack_ptr,
                memory::MemoryAddressRegister& mem_add_reg,
                memory::Stack& stack,
                std::vector<memory::GeneralRegister>& registers,
                memory::RAM& ram,
                display::Display<bool>& display) :
      m_pc(pc),
      m_stack_ptr(stack_ptr),
      m_mem_add_reg(mem_add_reg),
      m_stack(stack),
      m_registers(registers),
      m_ram(ram),
      m_display(display)
{
}

void ControlUnit::returnFromSubroutine()
{
    m_pc = m_stack[m_stack_ptr];
    --m_stack_ptr;  
}

void ControlUnit::jumpToLocation(uint16_t address)
{
    m_pc = address;
}

void ControlUnit::callSubroutineAt(uint16_t address)
{
    ++m_stack_ptr;
    m_stack[m_stack_ptr] = m_pc;
    m_pc = address;
}

void ControlUnit::skipNextInstructionIfEqual(uint8_t value,
                                             RegisterId reg)
{
    if(m_registers[reg] == value)
    {
        m_pc += 2;
    }
}

void ControlUnit::skipNextInstructionIfNotEqual(uint8_t value,
                                                RegisterId reg)
{
    if(m_registers[reg] != value)
    {
        m_pc += 2;
    }
}

void ControlUnit::skipNextInstructionIfRegistersEqual(RegisterId reg_x,
                                                      RegisterId reg_y)
{
    if(m_registers[reg_x] == m_registers[reg_y])
    {
        m_pc += 2;
    }
}

void ControlUnit::storeInRegister(uint8_t value,
                                  RegisterId reg)
{
    m_registers[reg] = value;
}

void ControlUnit::addToRegister(uint8_t value,
                                RegisterId reg)
{
    m_registers[reg] += value;
}

void ControlUnit::storeRegisterInRegister(RegisterId reg_x,
                                          RegisterId reg_y)
{
    m_registers[reg_x] = m_registers[reg_y];
}

void ControlUnit::bitwiseOr(RegisterId reg_x,
                            RegisterId reg_y)
{
    m_registers[reg_x] = (m_registers[reg_x] | m_registers[reg_y]);
}

void ControlUnit::bitwiseAnd(RegisterId reg_x,
                             RegisterId reg_y)
{
    m_registers[reg_x] = (m_registers[reg_x] & m_registers[reg_y]);
}

void ControlUnit::bitwiseXor(RegisterId reg_x,
                             RegisterId reg_y)
{
    m_registers[reg_x] = (m_registers[reg_x] ^ m_registers[reg_y]);
}

void ControlUnit::addRegisterToRegister(RegisterId reg_x, 
                                        RegisterId reg_y)
{
    std::uint16_t result = static_cast<std::uint16_t>(m_registers[reg_x]) 
                             + static_cast<std::uint16_t>(m_registers[reg_y]);

    if (result <= std::numeric_limits<std::uint8_t>::max())
    {
        m_registers[reg_x] = static_cast<std::uint8_t>(result);
        m_registers[0xF] = 0; 
    }
    else
    {
        m_registers[reg_x] = static_cast<std::uint8_t>(result);
        m_registers[0xF] = 1; 
    }
}

void ControlUnit::subtractRegisterToRegister(RegisterId reg_x, 
                                             RegisterId reg_y)
{
    m_registers[0xF] = m_registers[reg_x] < m_registers[reg_y] ? 1 : 0;
    m_registers[reg_x] = m_registers[reg_x] - m_registers[reg_y];
}


void ControlUnit::shiftRight(RegisterId reg)
{

    m_registers[0xF] =  (m_registers[reg] & 0b00000001);
    m_registers[reg] = m_registers[reg] >> 1;
}

void ControlUnit::shiftLeft(RegisterId reg)
{
    if (m_registers[reg] & 0b10000000)
    {
        m_registers[0xF] = 1;
    }
    else
    {
        m_registers[0xF] = 0;
    }

    m_registers[reg] = m_registers[reg] << 1;
}

void ControlUnit::skipNextInstructionIfRegistersNotEqual(RegisterId reg_x,
                                                         RegisterId reg_y)
{
    if(m_registers[reg_x] != m_registers[reg_y])
    {
        m_pc += 2;
    }
}

void ControlUnit::storeInMemoryAddressRegister(uint16_t value)
{
    m_mem_add_reg = value;
}

void ControlUnit::setPCToV0PlusValue(uint16_t value)
{
    m_pc = value + m_registers[0];
}

void ControlUnit::registerEqualRandomValue(uint8_t value,
                                           RegisterId reg)
{
    srand (time(NULL));
    auto random_value = rand() % 256;
    m_registers[reg] = (value & random_value);
}

void ControlUnit::displayOnScreen(uint16_t n_bytes_to_read,
                                  RegisterId reg_x,
                                  RegisterId reg_y)
{
    m_display.setSprite({m_registers[reg_x], m_registers[reg_y]}, display::makeSprite(m_ram[m_mem_add_reg]));
}

}
}
