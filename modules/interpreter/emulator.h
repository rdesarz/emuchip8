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

#ifndef MODULES_INTERPRETER_EMULATOR_H_
#define MODULES_INTERPRETER_EMULATOR_H_

#include <istream>
#include <memory>

#include "interpreter/memory.h"
#include "interpreter/rom_loader.h"

#include "display/display_controller.h"
#include "display/display_model.h"
#include "display/display_view.h"

namespace chip8 {

class Emulator {
 public:
  Emulator(std::istream& rom,
           std::unique_ptr<DisplayController> display_controller);

  void tick();

 private:
  std::unique_ptr<DisplayController> m_display_controller;
  RAM m_ram;
};

}  // namespace chip8
#endif  // MODULES_INTERPRETER_EMULATOR_H_
