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
                                    std::size_t register_id)

{
    if(m_registers[register_id] == value)
    {
        m_pc += 2;
    }
}

void ControlUnit::skipNextInstructionIfNotEqual(uint8_t value,
                                                std::size_t register_id)
{
    if(m_registers[register_id] != value)
    {
        m_pc += 2;
    }
}

void ControlUnit::skipNextInstructionIfRegistersEqual(std::size_t register_1_id,
                                                      std::size_t register_2_id)
{
    if(m_registers[register_1_id] == m_registers[register_2_id])
    {
        m_pc += 2;
    }
}

void ControlUnit::storeInRegister(uint8_t value,
                     std::size_t register_id)
{
    m_registers[register_id] = value;
}

void ControlUnit::addToRegister(uint8_t value,
                   std::size_t register_id)
{
    m_registers[register_id] += value;
}

void ControlUnit::storeRegisterInRegister(std::size_t register_x_id,
                             std::size_t register_y_id)
{
    m_registers[register_x_id] = m_registers[register_y_id];
}

void ControlUnit::bitwiseOr(std::size_t register_x_id,
               std::size_t register_y_id)
{
    m_registers[register_x_id] = (m_registers[register_x_id] | m_registers[register_y_id]);
}

void ControlUnit::bitwiseAnd(std::size_t register_x_id,
                std::size_t register_y_id)
{
    m_registers[register_x_id] = (m_registers[register_x_id] & m_registers[register_y_id]);
}

void ControlUnit::bitwiseXor(std::size_t register_x_id,
                std::size_t register_y_id)
{
    m_registers[register_x_id] = (m_registers[register_x_id] ^ m_registers[register_y_id]);
}

void ControlUnit::addRegisterToRegister(std::size_t register_x_id, 
                           std::size_t register_y_id)
{
    std::uint16_t result = static_cast<std::uint16_t>(m_registers[register_x_id]) 
                             + static_cast<std::uint16_t>(m_registers[register_y_id]);

    if (result <= std::numeric_limits<std::uint8_t>::max())
    {
        m_registers[register_x_id] = static_cast<std::uint8_t>(result);
        m_registers[0xF] = 0; 
    }
    else
    {
        m_registers[register_x_id] = static_cast<std::uint8_t>(result);
        m_registers[0xF] = 1; 
    }
}

void ControlUnit::subtractRegisterToRegister(std::size_t register_x_id, 
                                std::size_t register_y_id)
{
    m_registers[0xF] = m_registers[register_x_id] < m_registers[register_y_id] ? 1 : 0;
    m_registers[register_x_id] = m_registers[register_x_id] - m_registers[register_y_id];
}


void ControlUnit::shiftRight(std::size_t register_id)
{

    m_registers[0xF] =  (m_registers[register_id] & 0b00000001);
    m_registers[register_id] = m_registers[register_id] >> 1;
}

void ControlUnit::shiftLeft(std::size_t register_id)
{
    if (m_registers[register_id] & 0b10000000)
    {
        m_registers[0xF] = 1;
    }
    else
    {
        m_registers[0xF] = 0;
    }

    m_registers[register_id] = m_registers[register_id] << 1;
}

void ControlUnit::skipNextInstructionIfRegistersNotEqual(std::size_t register_1_id,
                                            std::size_t register_2_id)
{
    if(m_registers[register_1_id] != m_registers[register_2_id])
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
                              std::size_t register_id)
{
    srand (time(NULL));
    auto random_value = rand() % 256;
    m_registers[register_id] = (value & random_value);
}

void ControlUnit::displayOnScreen(uint16_t n_bytes_to_read,
                     std::size_t register_x_id,
                     std::size_t register_y_id)
{
    m_display.setSprite({m_registers[register_x_id], m_registers[register_y_id]}, display::makeSprite(m_ram[m_mem_add_reg]));
}

}
}
