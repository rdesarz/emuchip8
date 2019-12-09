#ifndef FIXTURES_H
#define FIXTURES_H

#include "gtest/gtest.h"

#include "display/display_controller.h"
#include "display/display_model.h"
#include "display/display_view.h"

#include "interpreter/control_unit.h"
#include "interpreter/user_input_impl.h"

namespace chip8 {

class TestDisplayModel : public DisplayModel {
 public:
  TestDisplayModel(std::size_t width, std::size_t height)
      : m_pixels(width, height) {
    m_pixels.clear();
  }

  void setPixelValue(std::size_t x, std::size_t y, uint8_t value) override {
    m_pixels(x, y) = value;
  }

  uint8_t getPixelValue(std::size_t x, std::size_t y) const override {
    return m_pixels(x, y);
  }

  std::size_t getWidth() const override { return m_pixels.size1(); }

  std::size_t getHeight() const override { return m_pixels.size2(); }

 private:
  boost::numeric::ublas::matrix<uint8_t> m_pixels;
};

class TestDisplayView : public DisplayView {
 public:
  virtual void render(){};
};

class TestDisplayFixture : public ::testing::Test {
 protected:
  TestDisplayFixture()
      : model(64, 32), view(new TestDisplayView), display(model, view) {}

  TestDisplayModel model;
  std::shared_ptr<TestDisplayView> view;
  DisplayController display;
};

class TestControlUnitFixture : public ::testing::Test {
 protected:
  TestControlUnitFixture()
      : model(64, 32),
        view(new TestDisplayView()),
        display_ctrler(model, view),
        ctrl_unit(pc, stack_ptr, mem_add_reg, stack, registers, ram,
                  display_ctrler, ui_ctrler),
        registers(16) {}

  ProgramCounter pc;
  StackPointer stack_ptr;
  MemoryAddressRegister mem_add_reg;
  Stack stack;
  std::vector<GeneralRegister> registers;
  RAM ram;
  TestDisplayModel model;
  std::shared_ptr<TestDisplayView> view;
  DisplayController display_ctrler;
  TestUserInputController ui_ctrler;
  ControlUnitImpl ctrl_unit;
};

struct MockControlUnit : public ControlUnit {
  void returnFromSubroutine() override {}

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
