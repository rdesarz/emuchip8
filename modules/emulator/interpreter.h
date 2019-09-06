#ifndef CHIP_INTERPRETER_H
#define CHIP_INTERPRETER_H
#include "emulator/memory.h"
#include "emulator/display.h"
 
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

void skipNextInstructionIfEqual(uint8_t value,
                                std::size_t register_id,
                                const std::vector<memory::GeneralRegister>& registers,
                                memory::ProgramCounter& pc);

void skipNextInstructionIfNotEqual(uint8_t value,
                                   std::size_t register_id,
                                   const std::vector<memory::GeneralRegister>& registers,
                                   memory::ProgramCounter& pc);

void skipNextInstructionIfRegistersEqual(std::size_t register_1_id,
                                         std::size_t register_2_id,
                                         const std::vector<memory::GeneralRegister>& registers,
                                         memory::ProgramCounter& pc);

void storeInRegister(uint8_t value,
                     std::size_t register_id,
                     std::vector<memory::GeneralRegister>& registers);

void addToRegister(uint8_t value,
                   std::size_t register_id,
                   std::vector<memory::GeneralRegister>& registers);

void storeRegisterInRegister(std::size_t register_x_id,
                             std::size_t register_y_id,
                             std::vector<memory::GeneralRegister>& registers);

void bitwiseOr(std::size_t register_x_id,
               std::size_t register_y_id,
               std::vector<memory::GeneralRegister>& registers);

void bitwiseAnd(std::size_t register_x_id,
                std::size_t register_y_id,
                std::vector<memory::GeneralRegister>& registers);

void bitwiseXor(std::size_t register_x_id,
                std::size_t register_y_id,
                std::vector<memory::GeneralRegister>& registers);

void addRegisterToRegister(std::size_t register_x_id, 
                           std::size_t register_y_id,
                           std::vector<memory::GeneralRegister>& registers);

void subtractRegisterToRegister(std::size_t register_x_id, 
                                std::size_t register_y_id,
                                std::vector<memory::GeneralRegister>& registers);

void shiftRight(std::size_t register_id,
                std::vector<memory::GeneralRegister>& registers);

void shiftLeft(std::size_t register_id,
               std::vector<memory::GeneralRegister>& registers);

void skipNextInstructionIfRegistersNotEqual(std::size_t register_1_id,
                                            std::size_t register_2_id,
                                            const std::vector<memory::GeneralRegister>& registers,
                                            memory::ProgramCounter& pc);

void storeInMemoryAddressRegister(uint16_t value,
                                  memory::MemoryAddressRegister& mem_add_reg);

void setPCToV0PlusValue(uint16_t value,
                        const std::vector<memory::GeneralRegister>& registers,
                        memory::ProgramCounter& pc);

void registerEqualRandomValue(uint8_t value,
                              std::size_t register_id,
                              std::vector<memory::GeneralRegister> registers);

void displayOnScreen(uint16_t n_bytes_to_read,
                     std::size_t register_x_id,
                     std::size_t register_y_id,
                     std::vector<memory::GeneralRegister>& registers,
                     memory::MemoryAddressRegister& mem_add_reg,
                     memory::RAM& ram,
                     display::Display<bool>& display);
                                                   

} /// interpreter
} /// chip8
#endif
