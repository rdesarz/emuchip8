#ifndef CONTROL_UNIT_FIXTURES_H
#define CONTROL_UNIT_FIXTURES_H

#include "interpreter/control_unit.h"

namespace chip8 {

struct MockControlUnit : public ControlUnit {
  void returnFromSubroutine() override { id_called_function = 1; }

  void jumpToLocation(uint16_t address) override { id_called_function = 1; }

  void callSubroutineAt(uint16_t address) override { id_called_function = 2; }

  void skipNextInstructionIfEqual(uint8_t value, RegisterId reg) override {
    id_called_function = 3;
  }

  void skipNextInstructionIfNotEqual(uint8_t value, RegisterId reg) override {
    id_called_function = 4;
  }

  void skipNextInstructionIfRegistersEqual(RegisterId reg_x,
                                           RegisterId reg_y) override {
    id_called_function = 5;
  }

  void storeInRegister(uint8_t value, RegisterId reg) override {
    id_called_function = 6;
  }

  void addToRegister(uint8_t value, RegisterId reg) override {
    id_called_function = 7;
  }

  void storeRegisterInRegister(RegisterId reg_x, RegisterId reg_y) override {
    id_called_function = 8;
  }

  void bitwiseOr(RegisterId reg_x, RegisterId reg_y) override {
    id_called_function = 9;
  }

  void bitwiseAnd(RegisterId reg_x, RegisterId reg_y) override {
    id_called_function = 10;
  }

  void bitwiseXor(RegisterId reg_x, RegisterId reg_y) override {
    id_called_function = 11;
  }

  void addRegisterToRegister(RegisterId reg_x, RegisterId reg_y) override {
    id_called_function = 12;
  }

  void subtractRegisterToRegister(RegisterId reg_x, RegisterId reg_y) override {
    id_called_function = 13;
  }

  void shiftRight(RegisterId reg) override { id_called_function = 14; }

  void shiftLeft(RegisterId reg) override { id_called_function = 15; }

  void skipNextInstructionIfRegistersNotEqual(RegisterId reg_x,
                                              RegisterId reg_y) override {
    id_called_function = 16;
  }

  void storeInMemoryAddressRegister(uint16_t value) override {
    id_called_function = 17;
  }

  void setPCToV0PlusValue(uint16_t value) override { id_called_function = 18; }

  void registerEqualRandomValue(uint8_t value, RegisterId reg) override {
    id_called_function = 19;
  }

  void displayOnScreen(uint16_t n_bytes_to_read, RegisterId reg_x,
                       RegisterId reg_y) override {
    id_called_function = 20;
  }

  void checkIfKeyPressed(RegisterId reg_x) override { id_called_function = 21; }

  void checkIfKeyNotPressed(RegisterId reg_x) override {
    id_called_function = 22;
  }

  void waitForKeyPressed(RegisterId reg_x) override { id_called_function = 23; }

  int id_called_function;
};

}  // namespace chip8
#endif
