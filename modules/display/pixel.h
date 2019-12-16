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

#ifndef MODULES_DISPLAY_PIXEL_H_
#define MODULES_DISPLAY_PIXEL_H_

#include <SDL.h>
#include <SDL_rect.h>
#include "boost/serialization/strong_typedef.hpp"

#include "display/utilities.h"

namespace chip8 {

namespace pixel {

BOOST_STRONG_TYPEDEF(std::size_t, Width);
BOOST_STRONG_TYPEDEF(std::size_t, Height);

class Position {
 public:
  explicit Position(std::size_t x, std::size_t y) : m_x(x), m_y(y) {}
  std::size_t x() { return m_x; }
  std::size_t y() { return m_y; }

 private:
  std::size_t m_x;
  std::size_t m_y;
};

BOOST_STRONG_TYPEDEF(std::uint64_t, ScaleFactor);
static const ScaleFactor unitary_scale = ScaleFactor(1);

class Pixel {
 public:
  Pixel(SDL_Renderer* renderer, Position pos)
      : m_renderer(renderer),
        m_position(pos),
        m_color(makeBlack()),
        m_scale_factor(unitary_scale) {}
  Pixel(SDL_Renderer* renderer, Position pos, Color color)
      : m_renderer(renderer),
        m_position(pos),
        m_color(color),
        m_scale_factor(unitary_scale) {}
  Pixel(SDL_Renderer* renderer, Position pos, Color color,
        ScaleFactor scale_factor)
      : m_renderer(renderer),
        m_position(pos),
        m_color(color),
        m_scale_factor(scale_factor) {}

  void setPosition(Position pos) { m_position = pos; }

  void setColor(Color color) { m_color = color; }

  void setScaleFactor(ScaleFactor scale_factor) {
    m_scale_factor = scale_factor;
  }

  void render();

 private:
  SDL_Renderer* m_renderer;
  SDL_Rect m_rect;
  Position m_position;
  Color m_color;
  ScaleFactor m_scale_factor;
};

}  // namespace pixel
}  // namespace chip8

#endif  // MODULES_DISPLAY_PIXEL_H_
