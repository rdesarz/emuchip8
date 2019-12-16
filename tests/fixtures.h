/**
 * Copyright (c) Romain Desarzens
 * All rights reserved.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TESTS_FIXTURES_H_
#define TESTS_FIXTURES_H_

#include <memory>
#include <vector>

#include "gtest/gtest.h"

#include "display/display_controller.h"
#include "display/display_model.h"
#include "display/display_view.h"

#include "interpreter/control_unit.h"
#include "interpreter/control_unit_impl.h"
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

  void clear() override { m_pixels.clear(); }

  std::size_t getWidth() const override { return m_pixels.size1(); }

  std::size_t getHeight() const override { return m_pixels.size2(); }

 private:
  boost::numeric::ublas::matrix<uint8_t> m_pixels;
};

class TestDisplayView : public DisplayView {
 public:
  virtual void render() {}
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
        ctrl_unit(pc, stack_ptr, index_reg, delay_timer_reg, sound_timer_reg,
                  stack, registers, ram, display_ctrler, ui_ctrler),
        registers(16) {}

  ProgramCounter pc;
  StackPointer stack_ptr;
  IndexRegister index_reg;
  Stack stack;
  DelayTimerRegister delay_timer_reg;
  SoundTimerRegister sound_timer_reg;
  std::vector<GeneralRegister> registers;
  RAM ram;
  TestDisplayModel model;
  std::shared_ptr<TestDisplayView> view;
  DisplayController display_ctrler;
  TestUserInputController ui_ctrler;
  ControlUnitImpl ctrl_unit;
};

}  // namespace chip8
#endif  // TESTS_FIXTURES_H_
