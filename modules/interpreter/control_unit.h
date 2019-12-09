#ifndef MODULES_INTERPRETER_CONTROL_UNIT_H_
#define MODULES_INTERPRETER_CONTROL_UNIT_H_

#include <vector>

#include "display/display_controller.h"
#include "interpreter/memory.h"
#include "interpreter/user_input.h"

namespace chip8 {

BOOST_STRONG_TYPEDEF(std::size_t, RegisterId)

class ControlUnit {
 public:
  virtual void returnFromSubroutine() = 0;

  virtual void jumpToLocation(uint16_t address) = 0;

  virtual void callSubroutineAt(uint16_t address) = 0;

  virtual void skipNextInstructionIfEqual(uint8_t value, RegisterId reg) = 0;

  virtual void skipNextInstructionIfNotEqual(uint8_t value, RegisterId reg) = 0;

  virtual void skipNextInstructionIfRegistersEqual(RegisterId reg_x,
                                                   RegisterId reg_y) = 0;

  virtual void storeInRegister(uint8_t value, RegisterId reg) = 0;

  virtual void addToRegister(uint8_t value, RegisterId reg) = 0;

  virtual void storeRegisterInRegister(RegisterId reg_x, RegisterId reg_y) = 0;

  virtual void bitwiseOr(RegisterId reg_x, RegisterId reg_y) = 0;

  virtual void bitwiseAnd(RegisterId reg_x, RegisterId reg_y) = 0;

  virtual void bitwiseXor(RegisterId reg_x, RegisterId reg_y) = 0;

  virtual void addRegisterToRegister(RegisterId reg_x, RegisterId reg_y) = 0;

  virtual void subtractRegisterToRegister(RegisterId reg_x,
                                          RegisterId reg_y) = 0;

  virtual void shiftRight(RegisterId reg) = 0;

  virtual void shiftLeft(RegisterId reg) = 0;

  virtual void skipNextInstructionIfRegistersNotEqual(RegisterId reg_x,
                                                      RegisterId reg_y) = 0;

  virtual void storeInMemoryAddressRegister(uint16_t value) = 0;

  virtual void setPCToV0PlusValue(uint16_t value) = 0;

  virtual void registerEqualRandomValue(uint8_t value, RegisterId reg) = 0;

  virtual void displayOnScreen(uint16_t n_bytes_to_read, RegisterId reg_x,
                               RegisterId reg_y) = 0;

  virtual void checkIfKeyPressed(RegisterId reg_x) = 0;

  virtual void checkIfKeyNotPressed(RegisterId reg_x) = 0;

  virtual void waitForKeyPressed(RegisterId reg_x) = 0;
};

class ControlUnitImpl : public ControlUnit {
 public:
  ControlUnitImpl(ProgramCounter& pc, StackPointer& stack_ptr,
                  MemoryAddressRegister& mem_add_reg, Stack& stack,
                  std::vector<GeneralRegister>& registers, RAM& ram,
                  DisplayController& display, UserInputController& ui_ctrler);

  void returnFromSubroutine() override;

  void jumpToLocation(uint16_t address) override;

  void callSubroutineAt(uint16_t address) override;

  void skipNextInstructionIfEqual(uint8_t value, RegisterId reg) override;

  void skipNextInstructionIfNotEqual(uint8_t value, RegisterId reg) override;

  void skipNextInstructionIfRegistersEqual(RegisterId reg_x,
                                           RegisterId reg_y) override;

  void storeInRegister(uint8_t value, RegisterId reg) override;

  void addToRegister(uint8_t value, RegisterId reg) override;

  void storeRegisterInRegister(RegisterId reg_x, RegisterId reg_y) override;

  void bitwiseOr(RegisterId reg_x, RegisterId reg_y) override;

  void bitwiseAnd(RegisterId reg_x, RegisterId reg_y) override;

  void bitwiseXor(RegisterId reg_x, RegisterId reg_y) override;

  void addRegisterToRegister(RegisterId reg_x, RegisterId reg_y) override;

  void subtractRegisterToRegister(RegisterId reg_x, RegisterId reg_y) override;

  void shiftRight(RegisterId reg) override;

  void shiftLeft(RegisterId reg) override;

  void skipNextInstructionIfRegistersNotEqual(RegisterId reg_x,
                                              RegisterId reg_y) override;

  void storeInMemoryAddressRegister(uint16_t value) override;

  void setPCToV0PlusValue(uint16_t value) override;

  void registerEqualRandomValue(uint8_t value, RegisterId reg) override;

  void displayOnScreen(uint16_t n_bytes_to_read, RegisterId reg_x,
                       RegisterId reg_y) override;

  void checkIfKeyPressed(RegisterId reg_x) override;

  void checkIfKeyNotPressed(RegisterId reg_x) override;

  void waitForKeyPressed(RegisterId reg_x) override;

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
