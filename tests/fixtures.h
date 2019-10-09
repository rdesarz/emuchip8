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

  virtual void setPixelValue(std::size_t x, std::size_t y,
                             uint8_t value) override {
    m_pixels(x, y) = value;
  }

  virtual uint8_t getPixelValue(std::size_t x, std::size_t y) const override {
    return m_pixels(x, y);
  }

  virtual std::size_t getWidth() const override { return m_pixels.size1(); }

  virtual std::size_t getHeight() const override { return m_pixels.size2(); }

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
  ControlUnit ctrl_unit;
};

}  // namespace chip8
#endif
