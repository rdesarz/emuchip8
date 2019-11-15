#ifndef CHIP_CONTROL_UNIT_H
#define CHIP_CONTROL_UNIT_H

#include <bitset>
#include "display/display_controller.h"
#include "interpreter/memory.h"
#include "interpreter/user_input.h"

namespace chip8 {

BOOST_STRONG_TYPEDEF(std::size_t, RegisterId)

class InstructionInterpreter {
  public:
    InstructionInterpreter() = default;
    void interpret(uint16_t instruction);
};

class ControlUnit {
 public:
  ControlUnit(ProgramCounter& pc, StackPointer& stack_ptr,
              MemoryAddressRegister& mem_add_reg, Stack& stack,
              std::vector<GeneralRegister>& registers, RAM& ram,
              DisplayController& display, UserInputController& ui_ctrler);

  virtual void returnFromSubroutine();

  virtual void jumpToLocation(uint16_t address);

  virtual void callSubroutineAt(uint16_t address);

  virtual void skipNextInstructionIfEqual(uint8_t value, RegisterId reg);

  virtual void skipNextInstructionIfNotEqual(uint8_t value, RegisterId reg);

  virtual void skipNextInstructionIfRegistersEqual(RegisterId reg_x, RegisterId reg_y);

  virtual void storeInRegister(uint8_t value, RegisterId reg);

  virtual void addToRegister(uint8_t value, RegisterId reg);

  virtual void storeRegisterInRegister(RegisterId reg_x, RegisterId reg_y);

  virtual void bitwiseOr(RegisterId reg_x, RegisterId reg_y);

  virtual void bitwiseAnd(RegisterId reg_x, RegisterId reg_y);

  virtual void bitwiseXor(RegisterId reg_x, RegisterId reg_y);

  virtual void addRegisterToRegister(RegisterId reg_x, RegisterId reg_y);

  virtual void subtractRegisterToRegister(RegisterId reg_x, RegisterId reg_y);

  virtual void shiftRight(RegisterId reg);

  virtual void shiftLeft(RegisterId reg);

  virtual void skipNextInstructionIfRegistersNotEqual(RegisterId reg_x,
                                                      RegisterId reg_y);

  virtual void storeInMemoryAddressRegister(uint16_t value);

  virtual void setPCToV0PlusValue(uint16_t value);

  virtual void registerEqualRandomValue(uint8_t value, RegisterId reg);

  virtual void displayOnScreen(uint16_t n_bytes_to_read, RegisterId reg_x,
                               RegisterId reg_y);

  virtual void checkIfKeyPressed(RegisterId reg_x);

  virtual void checkIfKeyNotPressed(RegisterId reg_x);

  virtual void waitForKeyPressed(RegisterId reg_x);

 private:
  ProgramCounter& m_pc;
  StackPointer& m_stack_ptr;
  MemoryAddressRegister& m_mem_add_reg;
  Stack& m_stack;
  std::vector<GeneralRegister>& m_registers;
  RAM& m_ram;
  DisplayController& m_display_ctrler;
  UserInputController& m_ui_ctrler;
};

// template<typename Type>
// class BitMask {
//   public:
//     BitMask() = default;
// 
//     void set(std::size_t from, std::size_t to, bool val = true) {
//       for (std::size_t i=from;i<to;++i)
//       {
//         m_mask.set(i, val);
//       }
//     }
// 
//     std::bitset<Size> get() { return m_mask; }
// 
//   private:
//     Type m_mask;
// };
// 
// template<typename Type>
// class Instruction {
//   public:
//     explicit Instruction(Type instruction) : m_instruction(instruction) {}
// 
//     template
//     Instruction subset(std::size_t from, std::size_t to) {
//       BitMask<T> mask;
//       mask.setBits<true>(from, to);
//       return Instruction(m_instruction & mask.get());
//     }
// 
//     bool operator==(const Instruction& rhs) {
//       bool is_same = true;
//       for (std::size_t i=0;i<std::numeric_limits<T>::digits;++i) {
//         is_same &= ((m_instruction & (1 << i)) == (rhs.m_instruction & (1 << i)));
//       }
//       return is_same;
//     }
// 
//   private:
//     std::bitset<std::numeric_limits<Type>::digits> m_instruction;
// };
// 
// template<typename T>
// void execute(Instruction<T> instruction, ControlUnit& ctrl_unit)
// {
//   if(instruction == Instruction<T>(0x00E0))
//   {
//     std::cout << "Clear display" << std::endl;
//   }
//   else if(instruction == Instruction<T>(0x00EE)) {
//     std::cout << "Return from subroutine" << std::endl;
//   }
//   else if(instruction.subset(12, 16) == Instruction<T>(0xF000).subset(12, 16)) {
//     std::cout << "Test" << std::endl;
//   }
// }

}  /// chip8
#endif
