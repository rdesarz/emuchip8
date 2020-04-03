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

#include "emulator/display_controller.h"

namespace chip8 {

std::vector<std::uint8_t> byteToSprite(uint8_t byte) {
  std::vector<std::uint8_t> sprite(8);

  for (std::uint8_t i = 0; i < 8; ++i) {
    sprite[7-i] = ((static_cast<uint8_t>(1) << i) & byte) >> i;
  }

  return sprite;
}

DisplayController::DisplayController(DisplayModel* model, DisplayView* view)
    : m_model(model), m_view(view) {}

bool DisplayController::setPixel(column_t col, row_t row,
                                 uint8_t value) {
  // Crop if pixel is outside of the screen
  col = col % m_model->getWidth();

  // Check if pixel is modified or not
  uint8_t old_value = m_model->getPixelValue(column_t(col), row_t(row));
  m_model->setPixelValue(column_t(col), row_t(row), (old_value ^ value) & 0x1);

  return m_model->getPixelValue(column_t(col), row_t(row)) != old_value;
}

bool DisplayController::setSprite(column_t col, row_t row,
                                  std::vector<uint8_t> sprite) {
  bool any_pixel_modified = false;

  // Crop if row is outside of the screen
  row = row % m_model->getHeight();

  for (uint8_t i = 0; i < 8; ++i) {
    any_pixel_modified |= setPixel(column_t(col + i), row, sprite[i]);
  }

  return any_pixel_modified;
}

void DisplayController::clear() { m_model->clear(); }

}  // namespace chip8
