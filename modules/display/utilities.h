/** 
 * Copyright (c) Romain Desarzens
 * All rights reserved. 
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef MODULES_DISPLAY_UTILITIES_H_
#define MODULES_DISPLAY_UTILITIES_H_

#include "boost/serialization/strong_typedef.hpp"

namespace chip8 {

static const std::uint8_t alpha_min = 0;
static const std::uint8_t alpha_max = 255;

class Color {
 public:
  explicit Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
      : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {}
  explicit Color(uint8_t red, uint8_t green, uint8_t blue)
      : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha_min) {}
  uint8_t red() { return m_red; }
  uint8_t green() { return m_green; }
  uint8_t blue() { return m_blue; }
  uint8_t alpha() { return m_alpha; }

 private:
  uint8_t m_red;
  uint8_t m_green;
  uint8_t m_blue;
  uint8_t m_alpha;
};

Color makeBlack();
Color makeWhite();

}  // chip8

#endif  // MODULES_DISPLAY_UTILITIES_H_
