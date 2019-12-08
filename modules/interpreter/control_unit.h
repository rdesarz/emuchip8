#ifndef MODULES_INTERPRETER_CONTROL_UNIT_H_
#define MODULES_INTERPRETER_CONTROL_UNIT_H_

#include <vector>

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

  virtual void skipNextInstructionIfRegistersEqual(RegisterId reg_x,
                                                   RegisterId reg_y);

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

}  // namespace chip8
#endif  // MODULES_INTERPRETER_CONTROL_UNIT_H_
