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
  TestDisplayModel() : m_pixels(64, 32) { m_pixels.clear(); }

  void setPixelValue(column_t col, row_t row, uint8_t value) override {
    m_pixels(col, row) = value;
  }

  uint8_t getPixelValue(column_t col, row_t row) const override {
    return m_pixels(col, row);
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
  TestDisplayFixture() : display(&model, &view) {}

  TestDisplayModel model;
  TestDisplayView view;
  DisplayController display;
};

class TestControlUnitFixture : public ::testing::Test {
 protected:
  TestControlUnitFixture()
      : display_ctrler(&model, &view),
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
  TestDisplayView view;
  DisplayController display_ctrler;
  TestUserInputController ui_ctrler;
  ControlUnitImpl ctrl_unit;
};

}  // namespace chip8
#endif  // TESTS_FIXTURES_H_
