#ifndef CHIP_CONTROL_UNIT_H
#define CHIP_CONTROL_UNIT_H
#include "interpreter/memory.h"
#include "interpreter/display.h"
 
namespace chip8
{
namespace ctrlunit
{

class ControlUnit
{
public:
    ControlUnit(memory::ProgramCounter& pc,
                memory::StackPointer& stack_ptr,
                memory::MemoryAddressRegister& mem_add_reg,
                memory::Stack& stack,
                std::vector<memory::GeneralRegister>& registers,
                memory::RAM& ram,
                display::Display<bool>& display);

    void returnFromSubroutine();
    
    void jumpToLocation(uint16_t address);
    
    void callSubroutineAt(uint16_t address);
    
    void skipNextInstructionIfEqual(uint8_t value,
                                    std::size_t register_id);
    
    void skipNextInstructionIfNotEqual(uint8_t value,
                                       std::size_t register_id);
    
    void skipNextInstructionIfRegistersEqual(std::size_t register_1_id,
                                             std::size_t register_2_id);
    
    void storeInRegister(uint8_t value,
                         std::size_t register_id);
    
    void addToRegister(uint8_t value,
                       std::size_t register_id);
    
    void storeRegisterInRegister(std::size_t register_x_id,
                                 std::size_t register_y_id);
    
    void bitwiseOr(std::size_t register_x_id,
                   std::size_t register_y_id);
    
    void bitwiseAnd(std::size_t register_x_id,
                    std::size_t register_y_id);
    
    void bitwiseXor(std::size_t register_x_id,
                    std::size_t register_y_id);
    
    void addRegisterToRegister(std::size_t register_x_id, 
                               std::size_t register_y_id);
    
    void subtractRegisterToRegister(std::size_t register_x_id, 
                                    std::size_t register_y_id);
    
    void shiftRight(std::size_t register_id);
    
    void shiftLeft(std::size_t register_id);
    
    void skipNextInstructionIfRegistersNotEqual(std::size_t register_1_id,
                                                std::size_t register_2_id);
    
    void storeInMemoryAddressRegister(uint16_t value);
    
    void setPCToV0PlusValue(uint16_t value);
    
    void registerEqualRandomValue(uint8_t value,
                                  std::size_t register_id);
    
    void displayOnScreen(uint16_t n_bytes_to_read,
                         std::size_t register_x_id,
                         std::size_t register_y_id);
private:
    memory::ProgramCounter& m_pc;
    memory::StackPointer& m_stack_ptr;
    memory::MemoryAddressRegister& m_mem_add_reg;
    memory::Stack& m_stack;
    std::vector<memory::GeneralRegister>& m_registers;
    memory::RAM& m_ram;
    display::Display<bool>& m_display;
};
} /// ctrlunit
} /// chip8
#endif
