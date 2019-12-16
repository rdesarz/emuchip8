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

#include <memory>

#include "display/display_controller.h"

namespace chip8 {

DisplayController::DisplayController(DisplayModel& model,
                                     std::shared_ptr<DisplayView> view)
    : m_model(model), m_view(view) {}

bool DisplayController::setPixel(std::size_t x, std::size_t y, uint8_t value) {
  // Crop if pixel is outside of the screen
  x = x % m_model.getWidth();

  // Check if pixel is modified or not
  uint8_t old_value = m_model.getPixelValue(x, y);
  m_model.setPixelValue(x, y, old_value ^ value);

  return m_model.getPixelValue(x, y) != old_value;
}

bool DisplayController::setSprite(std::size_t x, std::size_t y,
                                  std::vector<uint8_t> sprite) {
  bool any_pixel_modified = false;
  for (uint8_t i = 0; i < 8; ++i) {
    any_pixel_modified |= setPixel(x + i, y, sprite[i]);
  }

  return any_pixel_modified;
}

void DisplayController::clear() { m_model.clear(); }

}  // namespace chip8
