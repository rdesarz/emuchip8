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

#include "display_ui/display_view_impl.h"

#include <vector>

using namespace chip8::pixel;

namespace chip8 {

void SDLDisplayView::render() {
  if (getRenderer() == nullptr) {
    return;
  }

  for (std::size_t col = 0; col < m_model->getWidth(); ++col) {
    for (std::size_t row = 0; row < m_model->getHeight(); ++row) {
      if (m_model->getPixelValue(column_t(col), row_t(row)) == 0) {
        Pixel pixel(getRenderer(), Position(col, row), makeBlack(),
                    ScaleFactor(10));
        pixel.render();
      } else {
        Pixel pixel(getRenderer(), Position(col, row), makeWhite(),
                    ScaleFactor(10));
        pixel.render();
      }
    }
  }
}
}  // namespace chip8
