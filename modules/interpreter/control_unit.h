#ifndef CHIP_CONTROL_UNIT_H
#define CHIP_CONTROL_UNIT_H
#include "interpreter/memory.h"
#include "interpreter/display.h"
 
namespace chip8
{
namespace ctrlunit
{

BOOST_STRONG_TYPEDEF(std::size_t, RegisterId)

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
                                    RegisterId reg);
    
    void skipNextInstructionIfNotEqual(uint8_t value,
                                       RegisterId reg);
    
    void skipNextInstructionIfRegistersEqual(RegisterId reg_x,
                                             RegisterId reg_y);
    
    void storeInRegister(uint8_t value,
                         RegisterId reg);
    
    void addToRegister(uint8_t value,
                       RegisterId reg);
    
    void storeRegisterInRegister(RegisterId reg_x,
                                 RegisterId reg_y);
    
    void bitwiseOr(RegisterId reg_x,
                   RegisterId reg_y);
    
    void bitwiseAnd(RegisterId reg_x,
                    RegisterId reg_y);
    
    void bitwiseXor(RegisterId reg_x,
                    RegisterId reg_y);
    
    void addRegisterToRegister(RegisterId reg_x, 
                               RegisterId reg_y);
    
    void subtractRegisterToRegister(RegisterId reg_x, 
                                    RegisterId reg_y);
    
    void shiftRight(RegisterId reg);
    
    void shiftLeft(RegisterId reg);
    
    void skipNextInstructionIfRegistersNotEqual(RegisterId reg_x,
                                                RegisterId reg_y);
    
    void storeInMemoryAddressRegister(uint16_t value);
    
    void setPCToV0PlusValue(uint16_t value);
    
    void registerEqualRandomValue(uint8_t value,
                                  RegisterId reg);
    
    void displayOnScreen(uint16_t n_bytes_to_read,
                         RegisterId reg_x,
                         RegisterId reg_y);
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
