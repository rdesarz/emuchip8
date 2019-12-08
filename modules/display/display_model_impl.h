#ifndef DISPLAY_MODEL_IMPL_H
#define DISPLAY_MODEL_IMPL_H

#include <vector>

#include <boost/numeric/ublas/matrix.hpp>

#include "display/display_model.h"

namespace chip8 {

class DisplayModelImpl : public DisplayModel {
 public:
  DisplayModelImpl(std::size_t width, std::size_t height);

  void setPixelValue(std::size_t x, std::size_t y,
                     uint8_t value) override {
    m_pixels(x, y) = value;
  }

  uint8_t getPixelValue(std::size_t x, std::size_t y) const override {
    return m_pixels(x, y);
  }

  std::size_t getWidth() const override { return m_pixels.size1(); }

  std::size_t getHeight() const override { return m_pixels.size2(); }

 private:
  boost::numeric::ublas::matrix<uint8_t> m_pixels;
};

}  /// chip8
#endif
