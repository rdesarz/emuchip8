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

#ifndef MODULES_DISPLAY_DISPLAY_CONTROLLER_H_
#define MODULES_DISPLAY_DISPLAY_CONTROLLER_H_

#include <memory>
#include <vector>

#include <boost/numeric/ublas/matrix.hpp>
#include "display_model.h"
#include "display_view.h"
#include "units.h"

namespace chip8 {

// Generate a vector of bit representing a sprite
std::vector<std::uint8_t> byteToSprite(uint8_t byte);

class DisplayController {
 public:
  DisplayController(DisplayModel* model, DisplayView* view);

  // Set a pixel value following the logic of the chip 8 emulator
  bool setPixel(column_t col, row_t row, uint8_t value);
  // Set a sprite value following the logic of the chip 8 emulator
  bool setSprite(column_t col, row_t row, std::vector<uint8_t> sprite);
  // Clear the complete display_ui
  void clear();

 private:
  DisplayModel* m_model;
  DisplayView* m_view;
};

}  // namespace chip8
#endif  // MODULES_DISPLAY_DISPLAY_CONTROLLER_H_
