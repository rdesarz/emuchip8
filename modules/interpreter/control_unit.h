#ifndef CHIP_CONTROL_UNIT_H
#define CHIP_CONTROL_UNIT_H
#include "interpreter/memory.h"
#include "interpreter/user_input.h"
#include "interpreter/display.h"
 
namespace chip8
{

BOOST_STRONG_TYPEDEF(std::size_t, RegisterId)

class ControlUnit
{
public:
    ControlUnit(ProgramCounter& pc,
                StackPointer& stack_ptr,
                MemoryAddressRegister& mem_add_reg,
                Stack& stack,
                std::vector<GeneralRegister>& registers,
                RAM& ram,
                Display<uint8_t>& display,
                UserInputController& ui_ctrler);

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

    void checkIfKeyPressed(RegisterId reg_x);
    
    void checkIfKeyNotPressed(RegisterId reg_x);

private:
    ProgramCounter& m_pc;
    StackPointer& m_stack_ptr;
    MemoryAddressRegister& m_mem_add_reg;
    Stack& m_stack;
    std::vector<GeneralRegister>& m_registers;
    RAM& m_ram;
    Display<uint8_t>& m_display;
    UserInputController& m_ui_ctrler; 
};

} /// chip8
#endif
