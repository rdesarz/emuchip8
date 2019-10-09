#ifndef UTILITIES_H
#define UTILITIES_H

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

}  /// chip8

#endif
