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

#ifndef MODULES_DISPLAY_DISPLAY_MODEL_IMPL_H_
#define MODULES_DISPLAY_DISPLAY_MODEL_IMPL_H_

#include <vector>

#include <boost/numeric/ublas/matrix.hpp>

#include "display/display_model.h"

namespace chip8 {

class DisplayModelImpl : public DisplayModel {
 public:
  DisplayModelImpl(std::size_t width, std::size_t height);

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

}  // namespace chip8
#endif  // MODULES_DISPLAY_DISPLAY_MODEL_IMPL_H_
